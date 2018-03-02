#include <TabletMode/TabletMode.h>

#include <UErrno/uerrno.h>
#include <Windows.h>

#include <iostream>
#include <string>

using WString = std::wstring;

int wmain(int argc, wchar_t* argv[]) {
    std::cout << ":: Checking arguments." << "\r\n";

    error_t resCode = E_FN_SUCCESS;

    resCode = checkArguments(argc, argv);
    if (resCode != E_FN_SUCCESS) {
        std::cout << ":: Err :: Bad arguments." << "\r\n";
        return resCode;
    }

    int option = _wtoi(argv[1]);


    std::cout << ":: Initializing COM." << "\r\n";
    resCode = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(resCode)) {
        std::cout << ":: Err :: Failed to initalize COM." << "\r\n";
        return resCode;
    }

    std::string mode;
    if (option == 1) {
        mode = "ON";
    } else {
        mode = "OFF";
    }
    std::cout << ":: Trying to set tablet mode: " << mode << ".\r\n";
    resCode = triggerTabletMode(option);
    if (FAILED(resCode)) {
        std::cout << ":: Err :: Failed to set tablet mode." << mode << ".\r\n";
    }

    std::cout << ":: Freeing resources" << "\r\n";
    // Free COM resources.
    CoUninitialize();

    return resCode;
}
