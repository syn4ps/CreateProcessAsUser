// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <windows.h>
#include <stdio.h>
#include <userenv.h>

/*
void DisplayError(const char *pszAPI)
{
    LPVOID lpvMessageBuffer;
    //LPWSTR pszAPI;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpvMessageBuffer, 0, NULL);

    //
    //... now display this string
    //
    printf("ERROR: API        = %s.\n", pszAPI);
    wprintf(L"       error code = %d.\n", GetLastError());
    wprintf(L"       message    = %s.\n", (LPWSTR)lpvMessageBuffer);

    //
    // Free the buffer allocated by the system
    //
    LocalFree(lpvMessageBuffer);

    ExitProcess(GetLastError());
}
*/
int wmain(int argc, WCHAR* argv[])
{
    HANDLE hToken;
    DWORD dwSize;
    LPVOID lpvEnv;
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFO si = { 0 };
    WCHAR szUserProfile[256] = L"";

    si.cb = sizeof(STARTUPINFO);
    if (!LogonUser(L"syn", L".", L"sa2pc", LOGON32_LOGON_BATCH, LOGON32_PROVIDER_DEFAULT, &hToken)) {
        wprintf(L"Logon Failed");
    }
    else {
        wprintf(L"Logon Success");
        /*
        BOOL CreateProcessWithTokenW(
            HANDLE                hToken,
            DWORD                 dwLogonFlags,
            LPCWSTR               lpApplicationName,
            LPWSTR                lpCommandLine,
            DWORD                 dwCreationFlags,
            LPVOID                lpEnvironment,
            LPCWSTR               lpCurrentDirectory,
            LPSTARTUPINFOW        lpStartupInfo,
            LPPROCESS_INFORMATION lpProcessInformation
        );
        */
        if (!CreateProcessWithTokenW(
            hToken,
            LOGON_NETCREDENTIALS_ONLY,
            NULL,
            const_cast<LPWSTR>(L"c:\windows\system32\cmd.exe"),
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &si,
            &pi
        )) {
            wprintf(L"CreateProcessWithTocken Fail");
        }

    }
 
        
    
    /*
    DWORD     dwSize;
    HANDLE    hToken;
    LPVOID    lpvEnv;
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFOW        si = { 0 };
    WCHAR               szUserProfile[256] = L"";

    si.cb = sizeof(STARTUPINFO);

    if (argc != 4)
    {
        wprintf(L"Usage: %s [user@domain] [password] [cmd]", argv[0]);
        wprintf(L"\n\n");
        return;
    }

    //
    // TO DO: change NULL to '.' to use local account database
    //
    if (!LogonUserW(argv[1], NULL, argv[2], LOGON32_LOGON_INTERACTIVE,
        LOGON32_PROVIDER_DEFAULT, &hToken))
        DisplayError("LogonUser");

    if (!CreateEnvironmentBlock(&lpvEnv, hToken, TRUE))
        DisplayError("CreateEnvironmentBlock");

    dwSize = sizeof(szUserProfile) / sizeof(WCHAR);

    if (!GetUserProfileDirectory(hToken, szUserProfile, &dwSize))
        DisplayError("GetUserProfileDirectory");

    //
    // TO DO: change NULL to '.' to use local account database
    //
    if (!CreateProcessWithLogonW(argv[1], NULL, argv[2],
        LOGON_WITH_PROFILE, NULL, argv[3],
        CREATE_UNICODE_ENVIRONMENT, lpvEnv, szUserProfile,
        &si, &pi))
        DisplayError("CreateProcessWithLogonW");

    if (!DestroyEnvironmentBlock(lpvEnv))
        DisplayError("DestroyEnvironmentBlock");

    CloseHandle(hToken);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread); */
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
