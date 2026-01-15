#define _WIN32_WINNT 0x0500
#include <windows.h> 
#include <tlhelp32.h>
#include <stdlib.h>
#include "globales.h"
#include <stdio.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define ID_LISTA 501
#define ID_BOTON_MATAR 502
HWND hLista;
HWND hBotonMatar;
#define inputsegundo 601
#define inputnombrefile 602
#define ID1 101
#define ID2 102
#define ID3 103
char nombredearchivo[256] = "RegistroRAM.pqt";
char segundos[256] = "6000";
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SubWindowProcedure (HWND, UINT, WPARAM, LPARAM);
wchar_t Mainwindow[] = L"Estilos";
HWND boton1;
HWND boton2;
HWND boton3;
HWND ventana1;
HWND ventana2apps;
HWND ventana3registro;
HFONT hFuenteModerna;
MSG mensajecomunica;
WNDCLASSEXW estilo1;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SubWindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RegistroWindowProcedure(HWND, UINT, WPARAM, LPARAM); 
void MatarProcesoPorNombre(const wchar_t* nombre); 

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    estilo1.hInstance = hThisInstance;
    estilo1.lpszClassName = Mainwindow;
    estilo1.lpfnWndProc = WindowProcedure;
    estilo1.style = CS_DBLCLKS;
    estilo1.cbSize = sizeof (WNDCLASSEXW);
    estilo1.hIcon = LoadIcon (NULL, IDI_QUESTION);
    estilo1.hIconSm = LoadIcon (NULL, IDI_INFORMATION);
    estilo1.hCursor = LoadCursor (NULL, IDC_ARROW);
    estilo1.lpszMenuName = NULL;
    estilo1.cbClsExtra = 0;
    estilo1.cbWndExtra = 0;
    estilo1.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(45, 45, 48));

    hFuenteModerna = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                             DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");


WNDCLASSEXW estiloSub = {0};
    estiloSub.cbSize = sizeof(WNDCLASSEXW);
    estiloSub.lpszClassName = L"SubVentanaClase";
    estiloSub.lpfnWndProc = SubWindowProcedure;
    estiloSub.hInstance = hThisInstance;
    estiloSub.hCursor = LoadCursor(NULL, IDC_ARROW);
    estiloSub.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(30, 30, 30));
    RegisterClassExW(&estiloSub);


WNDCLASSEXW estiloRegistro = {0};
estiloRegistro.cbSize = sizeof(WNDCLASSEXW);
estiloRegistro.lpszClassName = L"RegistroVentanaClase";
estiloRegistro.lpfnWndProc = RegistroWindowProcedure; 
estiloRegistro.hInstance = hThisInstance;
estiloRegistro.hCursor = LoadCursor(NULL, IDC_ARROW);
estiloRegistro.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(30, 30, 30));
RegisterClassExW(&estiloRegistro);

    if (!RegisterClassExW (&estilo1))
        return 0;

    ventana1 = CreateWindowExW (
           0,
           Mainwindow,
           L"LighterRAM windows x86 x64",
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,400,70,644, 575,HWND_DESKTOP,NULL,hThisInstance,NULL);
    ShowWindow (ventana1, nCmdShow);
    ShowWindow(GetConsoleWindow(), SW_HIDE );

    while (GetMessageW (&mensajecomunica, NULL, 0, 0))
    {
        TranslateMessage(&mensajecomunica);
        DispatchMessageW(&mensajecomunica);
    }
 
    return mensajecomunica.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND ventana1, UINT mensajecomunica, WPARAM wParam, LPARAM lParam)
{
    switch (mensajecomunica)
    {
        case WM_CLOSE:
            DeleteObject(hFuenteModerna);
            DestroyWindow(ventana1);
            break;

        case WM_DESTROY:
            KillTimer(ventana1, 1);
            PostQuitMessage(0);
            break;

       case WM_CREATE:
            boton1 = CreateWindowExW(0, L"button", L"Registrar uso", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 10, 10, 110, 30, ventana1, (HMENU)ID1, GetModuleHandle(NULL), 0);
     
            boton2 = CreateWindowExW(0, L"button", L"Apps en 2º Plano", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 130, 10, 140, 30, ventana1, (HMENU)ID2, GetModuleHandle(NULL), 0);

            SendMessage(boton1, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
            SendMessage(boton2, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
            SetTimer(ventana1, 1, 1000, NULL);
            break;
         
         case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(ventana1, &ps);

            MEMORYSTATUSEX mem;
            mem.dwLength = sizeof(mem);
            GlobalMemoryStatusEx(&mem);
            int uso = (int)mem.dwMemoryLoad; 

            HBRUSH hBG = CreateSolidBrush(RGB(30, 30, 30));
            RECT rectGrafico = {10, 60, 260, 90}; 
            FillRect(hdc, &rectGrafico, hBG);

            HBRUSH hBarra = CreateSolidBrush(RGB(0, 200, 0));
            RECT rectUso = {10, 60, 10 + (uso * 2.5), 90}; 
            FillRect(hdc, &rectUso, hBarra);

            wchar_t txtRAM[25];
            wsprintfW(txtRAM, L"RAM en uso: %d%%", uso);
            SelectObject(hdc, hFuenteModerna);
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);
            TextOutW(hdc, 10, 95, txtRAM, lstrlenW(txtRAM));

            DeleteObject(hBG);
            DeleteObject(hBarra);
            EndPaint(ventana1, &ps);
        }
        break;

        case WM_TIMER:
            InvalidateRect(ventana1, NULL, TRUE); 
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID1){
               ventana3registro = CreateWindowExW(
            0, 
            L"RegistroVentanaClase", 
            L"Registro de Uso de Sistema", 
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
            CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, 
            ventana1, 
            NULL, GetModuleHandle(NULL), NULL
        );
            }
             if (LOWORD(wParam) == ID2){
                HWND hSub = CreateWindowExW(
            0, 
            L"SubVentanaClase", 
            L"Lista de Aplicaciones", 
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
            CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, 
            ventana1, 
            NULL, GetModuleHandle(NULL), NULL
        );
            }
            break;





        case WM_SETCURSOR:
            if ((HWND)wParam == boton1 || (HWND)wParam == boton2) {
                SetCursor(LoadCursor(NULL, IDC_HAND));
                return TRUE;
            }
            break;

        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
            HBRUSH hFondo = CreateSolidBrush(RGB(45, 45, 48));
            FillRect(pdis->hDC, &pdis->rcItem, hFondo);
            DeleteObject(hFondo);
            HBRUSH hBrush = CreateSolidBrush(RGB(68, 68, 68));
            HPEN hPen = CreatePen(PS_SOLID, 5, RGB(77, 77,77)); 
            
            SelectObject(pdis->hDC, hBrush);
            SelectObject(pdis->hDC, hPen);

            RoundRect(pdis->hDC, pdis->rcItem.left, pdis->rcItem.top, 
                      pdis->rcItem.right, pdis->rcItem.bottom, 15, 15);
            
            SetTextColor(pdis->hDC, RGB(255, 255, 255));
            SetBkMode(pdis->hDC, TRANSPARENT);

            wchar_t texto[50];
            GetWindowTextW(pdis->hwndItem, texto, 50);
            DrawTextW(pdis->hDC, texto, -1, &pdis->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            return TRUE;
        }

        default:
            return DefWindowProcW (ventana1, mensajecomunica, wParam, lParam);
    }
    return 0;


    
}

LRESULT CALLBACK SubWindowProcedure(HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
    switch (mensaje)
    {
        case WM_CREATE:
        {
      
            hLista = CreateWindowExW(WS_EX_CLIENTEDGE, L"LISTBOX", NULL, 
                        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_HASSTRINGS, 
                        10, 10, 360, 200, hwnd, (HMENU)ID_LISTA, NULL, NULL);

            hBotonMatar = CreateWindowExW(0, L"BUTTON", L"Finalizar Tarea", 
                            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                            10, 220, 150, 30, hwnd, (HMENU)ID_BOTON_MATAR, NULL, NULL);
            
            SendMessage(hLista, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
            SendMessage(hBotonMatar, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);

            HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            PROCESSENTRY32W pe;
            pe.dwSize = sizeof(pe);
            if (Process32FirstW(hSnapshot, &pe)) {
                do {
                    SendMessageW(hLista, LB_ADDSTRING, 0, (LPARAM)pe.szExeFile);
                } while (Process32NextW(hSnapshot, &pe));
            }
            CloseHandle(hSnapshot);
        }
        break;

        case WM_COMMAND:
        {
            if (LOWORD(wParam) == ID_BOTON_MATAR) {
                int index = (int)SendMessage(hLista, LB_GETCURSEL, 0, 0);
                if (index != LB_ERR) {
                    wchar_t nombreProceso[MAX_PATH];
                    SendMessageW(hLista, LB_GETTEXT, index, (LPARAM)nombreProceso);
                    
                    MatarProcesoPorNombre(nombreProceso);

                    MessageBoxW(hwnd, L"Intento de finalización enviado.", nombreProceso, MB_OK | MB_ICONINFORMATION);

                    SendMessage(hLista, LB_DELETESTRING, index, 0);
                }
            }
        }
        break;


        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        default:
            return DefWindowProcW(hwnd, mensaje, wParam, lParam);
    }

    
    return 0;
}




LRESULT CALLBACK RegistroWindowProcedure(HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam) {


    static HWND inputsegundos;
    static HWND inputnamefile;

    switch (mensaje) {
        case WM_CREATE: {
            HWND hTexto = CreateWindowExW(0, L"STATIC", L"Resgistra el RAM usado en el sistema", 
                            WS_CHILD | WS_VISIBLE, 
                            10, 10, 300, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hTexto, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
 
             inputsegundos = CreateWindowExW(
                            WS_EX_CLIENTEDGE,
                            L"EDIT",
                            L"60", 
                            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER, 
                            10, 35, 40, 25, 
                            hwnd, (HMENU)inputsegundo, GetModuleHandle(NULL), NULL);

inputnamefile = CreateWindowExW(
                            WS_EX_CLIENTEDGE,
                            L"EDIT",
                            L"RegistroRAM.txt", 
                            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL , 
                            10, 65, 150, 25, 
                            hwnd, (HMENU)inputnombrefile, GetModuleHandle(NULL), NULL);



boton3 = CreateWindowExW(0, L"button", L"ejecutar", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 10,115, 120, 30, hwnd, (HMENU)ID3, GetModuleHandle(NULL), 0); 
                            











            SendMessage(inputsegundos, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
              SendMessage(inputnamefile, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
            SendMessage(boton3, WM_SETFONT, (WPARAM)hFuenteModerna, TRUE);
            break;
        }
case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;

            HBRUSH hBrush = CreateSolidBrush(RGB(68, 68, 68));
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100)); 
            
            SelectObject(pdis->hDC, hBrush);
            SelectObject(pdis->hDC, hPen);
            RoundRect(pdis->hDC, pdis->rcItem.left, pdis->rcItem.top, 
 pdis->rcItem.right, pdis->rcItem.bottom, 10, 10);
 
            SetTextColor(pdis->hDC, RGB(255, 255, 255));
            SetBkMode(pdis->hDC, TRANSPARENT);

            wchar_t texto[50];
            GetWindowTextW(pdis->hwndItem, texto, 50);
            DrawTextW(pdis->hDC, texto, -1, &pdis->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            return TRUE;
        }


             case WM_COMMAND:
        {

            
            if (LOWORD(wParam) == ID3) {
char argumentos[512];
GetWindowTextA(inputnamefile, nombredearchivo, sizeof(nombredearchivo));
GetWindowTextA(inputsegundos, segundos, sizeof(nombredearchivo));

char Archivo[256];

FILE *archivo;
archivo = fopen(nombredearchivo, "w");
snprintf(argumentos, sizeof(argumentos), "%s %s", nombredearchivo, segundos);
ShellExecuteA(NULL, "open", "registrar.exe", argumentos, NULL, SW_SHOW);

            }
            break;
        }


        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        default:
            return DefWindowProcW(hwnd, mensaje, wParam, lParam);
    }
    return 0;
}


void MatarProcesoPorNombre(const wchar_t* nombre) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(pe);

    if (Process32FirstW(hSnap, &pe)) {
        do {
            if (wcscmp(pe.szExeFile, nombre) == 0) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (hProc) {
                    TerminateProcess(hProc, 0);
                    CloseHandle(hProc);
                }
            }
        } while (Process32NextW(hSnap, &pe));
    }
    CloseHandle(hSnap);
}