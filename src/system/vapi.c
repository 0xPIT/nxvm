/* This file is a part of NXVM project. */

#include "stdio.h"
#include "stdarg.h"
#include "windows.h"

#include "../vmachine/vmachine.h"

#include "vlog.h"
#include "vapi.h"

#define VAPI_QDFDD
#define VAPI_QDKEYB

#ifdef VAPI_QDFDD
#include "../vmachine/qdfdd.h"
#define vfdd qdfdd
#else
#include "../vmachine/vfdd.h"
#endif

#ifdef VAPI_QDKEYB
#include "../vmachine/qdkeyb.h"
#define vkeybRecvKeyPress qdkeybRecvKeyPress
#define vkeybVarFlag0 qdkeybVarFlag0
#define vkeybVarFlag1 qdkeybVarFlag1
#define vkeybGetShift qdkeybGetShift
#define vkeybGetAlt   qdkeybGetAlt
#define vkeybGetCtrl  qdkeybGetCtrl
#define VKEYB_FLAG0_A_INSERT  QDKEYB_FLAG0_A_INSERT
#define VKEYB_FLAG0_A_CAPLCK  QDKEYB_FLAG0_A_CAPLCK
#define VKEYB_FLAG0_A_NUMLCK  QDKEYB_FLAG0_A_NUMLCK
#define VKEYB_FLAG0_A_SCRLCK  QDKEYB_FLAG0_A_SCRLCK
#define VKEYB_FLAG0_D_ALT     QDKEYB_FLAG0_D_ALT
#define VKEYB_FLAG0_D_CTRL    QDKEYB_FLAG0_D_CTRL
#define VKEYB_FLAG0_D_LSHIFT  QDKEYB_FLAG0_D_LSHIFT
#define VKEYB_FLAG0_D_RSHIFT  QDKEYB_FLAG0_D_RSHIFT
#define VKEYB_FLAG1_D_INSERT  QDKEYB_FLAG1_D_INSERT
#define VKEYB_FLAG1_D_CAPLCK  QDKEYB_FLAG1_D_CAPLCK
#define VKEYB_FLAG1_D_NUMLCK  QDKEYB_FLAG1_D_NUMLCK
#define VKEYB_FLAG1_D_SCRLCK  QDKEYB_FLAG1_D_SCRLCK
#define VKEYB_FLAG1_D_PAUSE   QDKEYB_FLAG1_D_PAUSE
#define VKEYB_FLAG1_D_SYSRQ   QDKEYB_FLAG1_D_SYSRQ
#define VKEYB_FLAG1_D_LALT    QDKEYB_FLAG1_D_LALT
#define VKEYB_FLAG1_D_LCTRL   QDKEYB_FLAG1_D_LCTRL
#else
#include "../vmachine/vkeyb.h"
#endif

/* Console Print */
int vapiPrint(const char *format, ...)
{// prints string out of vdisplay, i.e. in a outside console
	int nWrittenBytes = 0;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	nWrittenBytes = vfprintf(stdout, format,arg_ptr);
	//nWrittenBytes = vsprintf(stringBuffer,format,arg_ptr);
	va_end(arg_ptr);
	return nWrittenBytes;
}
void vapiPrintByte(unsigned char n)
{
	char c;
	int i;
	for(i = 1;i >= 0;--i) {
		c = ((n>>(i*4))&0x0f)+0x30;
		if(c > 0x39) c += 0x27;
		vapiPrint("%c",c);
	}
}
void vapiPrintWord(unsigned short n)
{
	char c;
	int i;
	for(i = 3;i >= 0;--i) {
		c = ((n>>(i*4))&0x0f)+0x30;
		if(c > 0x39) c += 0x27;
		vapiPrint("%c",c);
	}
}
void vapiPrintAddr(unsigned short segment,unsigned short offset)
{vapiPrintWord(segment);vapiPrint(":");vapiPrintWord(offset);}
void vapiPause()
{
	fflush(stdin);
	vapiPrint("Press ENTER to continue . . .\n");
	getchar();
}
void vapiSleep(unsigned int milisec)
{
	Sleep(milisec);
}

/* Win32 Application Window Operations */
HINSTANCE hInstance;
LPCWSTR szWindowClass = L"nxvm";
LPCWSTR szTitle = L"Neko's x86 Virtual Machine";
DWORD ThreadIdDisplay;
DWORD ThreadIdKernel;
HWND hWnd;

static void KeyboardMakeStatus(UINT message, WPARAM wParam, LPARAM lParam)
{
	vkeybVarFlag0 = 0x00;
	vkeybVarFlag1 = 0x00;
	if(message == WM_KEYDOWN || message == WM_SYSKEYDOWN) {
		switch(wParam) { //�������ͨ�ַ�����flag2��0 
		case VK_INSERT: SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_INSERT);break;
		case VK_CAPITAL:SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_CAPLCK);break;
		case VK_NUMLOCK:SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_NUMLCK);break;
		case VK_SCROLL: SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_SCRLCK);break;
		case VK_PAUSE:  SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_PAUSE); break;
			//����ɨ��Sys req ���Ĵ���
		case VK_MENU:   SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_LALT); break;
			//�����ˡ������͵����������alt��Ҳ����˵���ұ�Ҳ����Ӧ�����ǲ�Ҫ��~~
		case VK_CONTROL:SetBit(vkeybVarFlag1, VKEYB_FLAG1_D_LCTRL); break;
			//ͬ��
		default: break;
		}
	} // else: keyUp, sysKeyUp, ���ܼ�ȫ��������û�а���״̬
	//ˢ�¹��ܼ���ǰ״̬
	if (GetKeyState(VK_INSERT)  < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_A_INSERT);
	if (GetKeyState(VK_CAPITAL) < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_A_CAPLCK);
	if (GetKeyState(VK_NUMLOCK) < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_A_NUMLCK);
	if (GetKeyState(VK_SCROLL)  < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_A_SCRLCK);
	if (GetKeyState(VK_MENU)    < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_D_ALT);
	if (GetKeyState(VK_CONTROL) < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_D_CTRL);
	if (GetKeyState(VK_LSHIFT)  < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_D_LSHIFT);
	if (GetKeyState(VK_RSHIFT)  < 0) SetBit(vkeybVarFlag0, VKEYB_FLAG0_D_RSHIFT);
}
static void KeyboardMakeChar(WPARAM wParam, LPARAM lParam)
{
	unsigned short ascii = (unsigned short)(((lParam & 0xffff0000) >> 8) | wParam);
	while(vkeybRecvKeyPress(ascii)) vapiSleep(10);
}
static void KeyboardMakeKey(UINT message, WPARAM wParam, LPARAM lParam)
{
	unsigned short ascii = (unsigned short)((lParam & 0xffff0000)>>8);
	if (WM_SYSKEYDOWN == message || WM_KEYDOWN == message) {
		switch(wParam) {
		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12://F1~~F12
			if(vkeybGetShift)      ascii += 0x1900;
			else if(vkeybGetAlt)   ascii += 0x2d00;
			else if (vkeybGetCtrl) ascii += 0x2300;
			vkeybRecvKeyPress(ascii);
			break;
		case VK_ESCAPE://ESC
		case VK_PRIOR://pageUP
		case VK_NEXT://pageDown
		case VK_END:
		case VK_HOME:
		case VK_LEFT:
		case VK_UP:
		case VK_RIGHT:
		case VK_DOWN:
			 vkeybRecvKeyPress(ascii);
		     break;
		default://ʣ�µ��ַ�������alt����ctl����ͨ�ַ��ȣ�����updateKBStatus����˵���ͨ�ַ�
			KeyboardMakeStatus(message, wParam, lParam);
			if (wParam>= 0x41 && wParam<=0x41+'Z'-'A') {
				if (vkeybGetAlt)  vkeybRecvKeyPress(ascii);
				if (vkeybGetCtrl) vkeybRecvKeyPress(ascii + wParam - 0x41);
				//������ǰ���ctrl�����ǰ���alt
			}
			break;
		}
		
	}
	else //keyUp, sysKeyUp
		KeyboardMakeStatus(message, wParam, lParam);
}

#define TIMER_PAINT   0
#define TIMER_RTC     1
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message) {
	case WM_CREATE:
		SetTimer(hWnd, TIMER_PAINT, 50, NULL);
		SetTimer(hWnd, TIMER_RTC,   55, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		break;
	case WM_TIMER:
		switch (wParam) {
		case TIMER_PAINT:
			break;
		case TIMER_RTC:
			break;
		default: break;
		}
		break;
 	case WM_PAINT:
 		/*OnPaint();*/
		break;
	case WM_SIZE:
		/*rect.right=lParam & 0xffff;
		rect.bottom=lParam / 0x10000;*/
		break;
	case WM_SIZING:
		break;
	case WM_CHAR:
		KeyboardMakeChar(wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		KeyboardMakeKey(message, wParam, lParam);
		break;
	case WM_SETFOCUS:
		KeyboardMakeStatus(WM_KEYUP, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
static ATOM ThreadDisplayRegisterClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(8);//(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;
	return RegisterClassEx(&wcex);
}
static BOOL ThreadDisplayInitInstance(HINSTANCE hInstance, int nCmdShow)
{
	DWORD dwStyle = WS_THICKFRAME | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
		            WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	hWnd = CreateWindow(szWindowClass, szTitle, dwStyle, CW_USEDEFAULT, 0,
	                    888, 484, NULL, NULL, hInstance, NULL);
	                           /* window size is 888 x 484 for "Courier New" */
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return TRUE;
}
static DWORD WINAPI ThreadDisplay(LPVOID lpParam)
{
	MSG msg;
	hInstance = GetModuleHandle(NULL);
	ThreadDisplayRegisterClass();
	ThreadDisplayInitInstance(hInstance, 0);
	while (vmachine.flagrun && GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	vmachine.flagrun = 0x00;
	return 0;
}
static DWORD WINAPI ThreadKernel(LPVOID lpParam)
{
	vlogInit();
	vmachineRunLoop();
	vlogFinal();
	return 0;
}
void vapiDisplayPaint()
{}
void vapiCreateDisplay()
{
	CreateThread(NULL, 0, ThreadDisplay, NULL, 0, &ThreadIdDisplay);
}
void vapiCreateKernel()
{
	CreateThread(NULL, 0, ThreadKernel, NULL, 0, &ThreadIdKernel);
}

/* Floppy Disk Drive Operations */
void vapiInsertFloppyDisk(const char *fname)
{
	size_t count;
	FILE *image = fopen(fname, "rb");
	if (image) {
		count = fread((void *)vfdd.base, sizeof(unsigned char),
		              0x00168000, image);
		vfdd.flagexist = 0x01;
		fclose(image);
		vapiPrint("Floppy disk inserted.\n");
	} else
		vapiPrint("Cannot read floppy image from '%s'.\n", fname);
}
void vapiRemoveFloppyDisk(const char *fname)
{
	size_t count;
	FILE *image;
	image = fopen(fname, "wb");
	if(image) {
		if (!vfdd.flagro)
			count = fwrite((void *)vfdd.base, sizeof(unsigned char),
			               0x00168000, image);
		vfdd.flagexist = 0x00;
		fclose(image);
		vapiPrint("Floppy disk removed.\n");
	} else
		vapiPrint("Cannot write floppy image to '%s'.\n", fname);
}