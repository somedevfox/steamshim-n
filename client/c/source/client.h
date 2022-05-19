#ifdef _WIN32
#include <windows.h>
#endif

typedef struct 
{
    int cmd;
    char** args;
} SSIPC_Message;

#ifdef _WIN32
#define NPTYPE HANDLE
#endif

NPTYPE* ssipc_open();
int ssipc_write(NPTYPE hPipe, char cmd, char* argv);