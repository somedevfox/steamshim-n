#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <string>

typedef struct 
{
    char cmd;
    std::string args;
} SSIPC_Message;

class SSIPC
{
    private:
        #ifdef _WIN32
        HANDLE hPipe;
        SSIPC_Message oldMessage;
        #endif
    public:
        SSIPC();
        ~SSIPC();

        void Send(int cmd, char** args);
        SSIPC_Message* Recv();
};