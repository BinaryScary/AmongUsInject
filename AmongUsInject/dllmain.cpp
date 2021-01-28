// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>

void SpeedHack() {
    // create a reference to the library we plan on using
    auto hLib = LoadLibraryA("GameAssembly.dll");
    // create pointer to address with offsets
    uintptr_t* player_typeinfo = (uintptr_t*)((uintptr_t)hLib + 0x01C57F7C);
    uintptr_t* physics = (uintptr_t*)(*player_typeinfo + 0x5C);
    uintptr_t* properties = (uintptr_t*)(*physics + 0x4);
    uintptr_t* speed = (uintptr_t*)(*properties + 0x14);
    // change player speed
    *(float*)speed = 5.0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
                           DisableThreadLibraryCalls(hModule);
                           HANDLE hThread = CreateThread(nullptr, 0,
                               (LPTHREAD_START_ROUTINE)SpeedHack, hModule, 0, 0);
                           if (hThread != nullptr)
                               CloseHandle(hThread);
                           break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

