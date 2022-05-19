#include "client.h"

NPTYPE* ssipc_open()
{
    #ifdef _WIN32
    HANDLE hPipe = CreateFile(
        TEXT("\\\\.\\pipe\\ssnpipe"),
        GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if(hPipe == INVALID_HANDLE_VALUE)
        return NULL;

    return hPipe;
    #endif
}

int ssipc_write(NPTYPE hPipe, char cmd, char* argv)
{
    #ifdef _WIN32
    char msg[128] = {cmd};
    strcpy(msg, argv);
    BOOL result = WriteFile(
        hPipe,
        (wchar_t*)msg,
        wcslen((wchar_t*)msg) * sizeof(wchar_t),
        0,
        NULL 
    );
    if(!result) 
        return GetLastError();
    #endif

    return 0;
}