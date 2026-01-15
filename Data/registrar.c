#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

MessageBox(NULL, "Hiciste clic en el icono de RAM", "Aviso del Sistema", MB_OK | MB_ICONINFORMATION);
#define WM_TRAYICON (WM_USER + 1)
int main(int argc, char *argv[]) {

    NOTIFYICONDATAA nid = {};


int segundos = (argc > 2) ? atoi(argv[2]) : 1;

  HWND h = FindWindowA("ConsoleWindowClass", NULL);
 nid.cbSize = sizeof(nid);
 nid.hWnd = h;
nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;

    nid.uCallbackMessage = WM_TRAYICON;
 nid.hIcon = (HICON)LoadImage(NULL, "min.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE |  LR_VGACOLOR);
if (!nid.hIcon){
nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
} 

    char *nombre = (argc > 1) ? argv[1] : "default.txt";
int uso_a = -1;

 Shell_NotifyIcon(NIM_ADD, &nid);

    while (1) {

       


        MEMORYSTATUSEX mem;
        mem.dwLength = sizeof(mem);
        GlobalMemoryStatusEx(&mem);
        int uso = (int)mem.dwMemoryLoad;
if (uso == uso_a ){
FILE *archivo = fopen(nombre, "a");
if (archivo) {
fprintf(archivo, "X");
fclose(archivo);
}
}else{

snprintf(nid.szTip, 128, "Uso de RAM: %d%%", uso);
 Shell_NotifyIcon(NIM_MODIFY, &nid);

        FILE *archivo = fopen(nombre, "a");
        if (archivo) {
            fprintf(archivo, "%d%%", uso);
            fclose(archivo);
        }
}

uso_a  = uso;
        Sleep(segundos*1000);
    }
    return 0;
}