#ifndef __TABLET_MODE_H
#define __TABLET_MODE_H

#include <UErrno/uerrno.h>

#include <Windows.h>
#include <stdint.h>

error_t checkArguments(int argc, wchar_t* argv[]);

HRESULT getTabletModeInterface(IUnknown* shellIntf, void** intf);
HRESULT triggerTabletMode(uint32_t mode);
HRESULT getTabletMode(DWORD* mode);
HRESULT releaseInterface(LPVOID* intf);

#endif 
