#include <TabletMode/TabletMode.h>
#include <atlbase.h>
#include <Servprov.h>

error_t checkArguments(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        return E_FN_INVAL;
    }

    int option = _wtoi(argv[1]);

    if (option != 0 && option != 1) {
        return E_FN_INVAL;
    }

    return E_FN_SUCCESS;
}

HRESULT getImmersiveShellInterface(IUnknown** intf) {
    if (intf == NULL) {
        return E_FN_INVAL;
    }

    error_t resCode = E_FN_SUCCESS;
    CLSID immersiveShell;

    resCode =
        CLSIDFromString(
            CComBSTR(OLESTR("{C2F03A33-21F5-47FA-B4BB-156362A2F239}")),
            &immersiveShell
        );
    if (FAILED(resCode)) {
        return resCode;
    }

    resCode =
        CoCreateInstance(
            immersiveShell,
            NULL,
            CLSCTX_SERVER,
            __uuidof(IUnknown),
            (void**)intf
        );

    return resCode;
}

HRESULT getTabletModeInterface(IUnknown* shellIntf, void** intf) {
    if (intf == NULL) {
        return E_FN_INVAL;
    }

    error_t resCode = E_FN_SUCCESS;

    IServiceProvider* servProvider = NULL;
    resCode =
        shellIntf->QueryInterface<IServiceProvider>(
            &servProvider
        );
    if (FAILED(resCode)) {
        return resCode;
    }

    GUID immersiveShellCLSID;
    GUID immersiveShellIID;

    resCode =
        CLSIDFromString(
            CComBSTR(OLESTR("{4fda780a-acd2-41f7-b4f2-ebe674c9bf2a}")),
            &immersiveShellCLSID
        );
    if (FAILED(resCode)) {
        return resCode;
    }

    resCode =
        CLSIDFromString(
            CComBSTR(OLESTR("{4fda780a-acd2-41f7-b4f2-ebe674c9bf2a}")),
            &immersiveShellIID
        );
    if (FAILED(resCode)) {
        return resCode;
    }

    resCode = servProvider->QueryService(
        immersiveShellCLSID,
        immersiveShellIID,
        intf
    );

    return resCode;
}

HRESULT releaseInterface(PVOID* intf) {
    return ((IUnknown*)intf)->Release();
}

HRESULT triggerTabletMode(uint32_t mode) {
    HRESULT resCode = E_FN_SUCCESS;

    IUnknown* immersiveIntf = NULL;
    uint64_t tabletIntf = 0;

    resCode = getImmersiveShellInterface(&immersiveIntf);
    if (FAILED(resCode)) {
        return resCode;
    }

    resCode = getTabletModeInterface(immersiveIntf, (void**)&tabletIntf);
    if (FAILED(resCode)) {
        goto Cleanup;
    }

    uint64_t* vptr =  *(uint64_t**)tabletIntf;

    DWORD(*setTabletMode)(uint64_t*,DWORD,DWORD) =
        (DWORD(*)(uint64_t*,DWORD,DWORD))vptr[4];

    resCode = setTabletMode((uint64_t*)tabletIntf, mode, 4);

Cleanup:
    if (tabletIntf != 0) {
        releaseInterface((LPVOID*)tabletIntf);
    }
    if (immersiveIntf != NULL) {
        releaseInterface((LPVOID*)immersiveIntf);
    }

    return resCode;
}

HRESULT getTabletMode(DWORD* mode) {
    if (mode == NULL) {
        return E_FN_INVAL;
    }

    HRESULT resCode = E_FN_SUCCESS;

    IUnknown* immersiveIntf = NULL;
    uint64_t tabletIntf = 0;

    resCode = getImmersiveShellInterface(&immersiveIntf);
    if (FAILED(resCode)) {
        return resCode;
    }

    resCode = getTabletModeInterface(immersiveIntf, (void**)&tabletIntf);
    if (FAILED(resCode)) {
        goto Cleanup;
    }

    uint64_t* vptr =  *(uint64_t**)tabletIntf;

    DWORD(*getTabletMode)(uint64_t*,DWORD*) =
        (DWORD(*)(uint64_t*,DWORD*))vptr[3];

    resCode = getTabletMode((uint64_t*)tabletIntf, mode);

Cleanup:
    if (tabletIntf != 0) {
        releaseInterface((LPVOID*)tabletIntf);
    }
    if (immersiveIntf != NULL) {
        releaseInterface((LPVOID*)immersiveIntf);
    }

    return resCode;
}

