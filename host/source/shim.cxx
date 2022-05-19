#include <stdlib.h>
#include <pthread.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "ipc.hxx"

#include <steam/steam_api.h>

#define APP_PATH "X:\\steamshim-n\\client\\c\\example\\build\\steamshim-n-example.exe"

#ifdef SS_DEBUG
#define debug printf
#else
void debug(char* msg) {
    (void)msg;
}
#endif

enum SteamShimCommands
{
    SetAchievement,
    GetAchievement,
    UpdateRichPresence
};

int main(int argc, char** argv) {
    debug("SteamShim-N Starting Up. Initializing Steamworks API");

    /*
    * If Steamworks API Initialization Fails
    * Show message containing possible problems for that to user and exit
    */
    if(!SteamAPI_Init()) {
        #ifdef _WIN32
        printf("Steamworks API Initialization failed!\n");
        printf("Here's list of problems with this kind of error:\n");
        printf("\t- Your Steam Client isn't running\n");
        printf("\t- Steam couldn't identify game, it's either missing steam_appid.txt file or appid is not set into SteamShim-N. Contact developer for assistance!\n");
        printf("\t- Somehow, game isn't running under the same user as Steam Client\n");
        printf("\t- You don't own game you're trying to play\n");
        printf("\t- App you're trying to launch isn't yet released to public\n");
        #else
        printf("Steamworks API Initialization failed!");
        printf("Here's list of problems with this kind of error:");
        printf("\t- Your Steam Client isn't running");
        printf("\t- Steam couldn't identify game, it's either missing steam_appid.txt file or appid is not set into SteamShim-N. Contact developer for assistance!");
        printf("\t- Somehow, game isn't running under the same user as Steam Client");
        printf("\t- You don't own game you're trying to play");
        printf("\t- App you're trying to launch isn't yet released to public");
        #endif
        exit(1);
    } else {
        debug("Steamworks API Initialization - Success!");
    }

    SSIPC ipc;

    // Start game
    debug("Launching game...");
    #ifdef _WIN32
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInformation, sizeof(processInformation));

    if(!CreateProcess(
        NULL,               // No module name,
        APP_PATH,           // Command line
        NULL,               // Process handle
        NULL,               // Thread handle
        FALSE,              // No handle inheritance
        0,                  // No Creation Flags
        NULL,               // Use parent's env block
        NULL,               // Use parent's starting dir
        &startupInfo,
        &processInformation
    ))
    {
        printf("Fatal Error: Failed to launch game.\n\tWin32 Error: %s\n", GetLastError());
    }
    #endif

    while(true)
    {
        SSIPC_Message* msg = ipc.Recv();
        if(msg == NULL)
            continue;

        printf("%c", msg->cmd);
    }

    // Close process and thread handle
    #ifdef _WIN32
    CloseHandle(processInformation.hProcess);
    CloseHandle(processInformation.hThread);
    #endif
    return 0;
}