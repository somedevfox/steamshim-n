#include "ipc.hxx"

#include <stdio.h>

SSIPC::SSIPC()
{
    #ifdef _WIN32
    SSIPC::hPipe = CreateNamedPipe(
        TEXT("\\\\.\\pipe\\ssnpipe"),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        1024 * 16,
        1024 * 16,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL
    );
    // Check if pipe has been successfully created
    if(SSIPC::hPipe == NULL || SSIPC::hPipe == INVALID_HANDLE_VALUE)
    {
        printf("Fatal Error: Failed to create named pipe\n\tWin32 Error: %s", GetLastError());
        exit(1);
    }

    /*BOOL result = ConnectNamedPipe(
        SSIPC::hPipe,
        NULL
    );
    if(!result) {
        printf("Fatal Error: Failed to connect to named pipe\n\tWin32 Error: %s\n", GetLastError());
        exit(1);
    }*/

    #endif
}

SSIPC::~SSIPC()
{

}

void SSIPC::Send(int cmd, char** args)
{
    #ifdef _WIN32

    #endif
}

SSIPC_Message* SSIPC::Recv()
{
    SSIPC_Message msg;
    #ifdef _WIN32
    char buffer[128];
    DWORD bytes;
    ReadFile(
        SSIPC::hPipe,
        buffer,
        127 * sizeof(wchar_t),
        &bytes,
        NULL
    );
    msg.cmd = buffer[0];
    buffer[bytes/sizeof(wchar_t)] = '\0';
    for(int i=1;i<bytes;i++) {
        msg.args += buffer[i];
    }
    printf("CMD: %c\nARGV: %s\n", msg.cmd, msg.args);
    #endif

    if(msg.cmd == SSIPC::oldMessage.cmd && msg.args == SSIPC::oldMessage.args)
        return 0;

    return &msg;
}