#include <windows.h>
#include <TCHAR.H>
#include <stdio.h>
#include "resource.h"
#include <list>
#include <ctime>
#include <cstdio>
#define WM_ASYNC WM_USER+2
#define OFFSET 10 //
enum Client { A, B, C };
using namespace std;
typedef struct _shape
{
	HBRUSH hBrush;
	HPEN hPen;
	POINT St;
	POINT Ed;
	BOOL(_stdcall* pFunc)(HDC, int, int, int, int);
	COLORREF bColor, pColor;
	HFONT hFont;
	LOGFONT LogFont;
	BOOL FREE;
}Shape;
struct Chat
{
	TCHAR Text[100];
};
template <typename T>
struct SendStruct {
	int Packnum;
	T use;
};

void LoadToFile(TCHAR filename[], list<Shape>& slist)
{
	FILE *fPtr;
	Shape temp;
	slist.clear();
	_tfopen_s(&fPtr, filename, _T("r"));
	while (fscanf_s(fPtr, "%d %d %d %d %p %d %d\n", &(temp.St.x),
		&(temp.St.y), &(temp.Ed.x), &(temp.Ed.y), &(temp.pFunc), &(temp.bColor), &(temp.pColor)) != EOF)
		slist.push_back(temp);
	for (list<Shape> ::iterator iterPos = slist.begin();
	iterPos != slist.end(); ++iterPos) {
		if ((*iterPos).bColor != 0)
			(*iterPos).hBrush = CreateSolidBrush((*iterPos).bColor);
		if ((*iterPos).pColor != 0)
			(*iterPos).hPen = CreatePen(PS_SOLID, 1, (*iterPos).pColor);
	}
	fclose(fPtr);
}
void SaveToFile(TCHAR filename[], list<Shape>& slist)
{
	FILE *fPtr;
	_tfopen_s(&fPtr, filename, _T("w"));
	for (list<Shape> ::iterator iterPos = slist.begin();
	iterPos != slist.end(); ++iterPos)
	{
		fprintf(fPtr, "%d %d %d %d %p %d %d\n", (*iterPos).St.x,
			(*iterPos).St.y, (*iterPos).Ed.x, (*iterPos).Ed.y, (*iterPos).pFunc, (*iterPos).bColor, (*iterPos).pColor);
	}
	fclose(fPtr);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("Server Window"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		510,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static WSADATA wsadata;
	static SOCKET s, cs;
	static SOCKADDR_IN addr = { 0 }, c_addr;
	int size, msgLen;
	static int ctcut;
	static int plus;
	static Shape RxData;
	static list <Shape> temp;
	static list<Chat> chatlist;
	char testbuf[100000];
	static SOCKET client[6] = {NULL,};
	int i = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		ctcut = 0;
		plus = 0;
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.s_addr = inet_addr("192.168.0.121");
		bind(s, (LPSOCKADDR)&addr, sizeof(addr));
		WSAAsyncSelect(s, hwnd, WM_ASYNC, FD_ACCEPT);
		if (listen(s, 5) == -1) return 0;

		break;
	case WM_ASYNC:
		hdc = BeginPaint(hwnd, &ps);
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			cs = accept(s, (LPSOCKADDR)&c_addr, &size);
			WSAAsyncSelect(cs, hwnd, WM_ASYNC, FD_READ);
			break;                
		case FD_READ:
			msgLen = recv(wParam, testbuf, 100000, 0);
			for (int i = 0; i < 6; i++) {
				if (client[i] == NULL) {
					client[i] = wParam;
					break;
				}
				else if (client[i] == wParam)
					break;
				
			}			
			int * asd = (int*)testbuf;
			if (*asd == 1) {
				SendStruct<Shape> sst = *(SendStruct<Shape>*) testbuf;

				sst.use.hPen = CreatePen(PS_SOLID, 1, sst.use.pColor);
				sst.use.hBrush = CreateSolidBrush(sst.use.bColor);
				temp.push_back(sst.use);
				for (int i = 0; i < 6; i++) {
					if (client[i] != NULL)
						send(client[i], (char*)&sst, sizeof(SendStruct<Shape>), 0);
				}

			}
			else if (*asd == 2) {
				SendStruct<Chat> sst = *(SendStruct<Chat>*) testbuf;
				chatlist.push_back(sst.use);
				for (int i = 0; i < 6; i++) {
					if(client[i] != NULL)
					send(client[i], (char*)&sst, sizeof(SendStruct<Chat>), 0);
				}
				InvalidateRgn(hwnd, NULL, true);
				break;
			}

			testbuf[msgLen] = NULL;
			InvalidateRgn(hwnd, NULL, true);
			break;
		}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, 500, 0, 780, 450);
		int cnty = 0;
		list<Chat>::iterator iterp = chatlist.begin();
		for (int i = 0; i < plus; i++) {
			iterp++;
		}
		for (iterp;
		iterp != chatlist.end(); ++iterp) {
			TextOut(hdc, 501, 1 + (cnty * 20), iterp->Text, wcslen(iterp->Text));
			cnty++;
			ctcut++;
			if (ctcut > 21)
				plus++;
		}
		ctcut = 0;
		for (list<Shape> ::iterator iterPos = temp.begin();
		iterPos != temp.end(); ++iterPos)
		{

			SelectObject(hdc, (*iterPos).hBrush);
			SelectObject(hdc, (*iterPos).hPen);

			if ((*iterPos).pFunc)
				(*iterPos).pFunc(hdc, (*iterPos).St.x, (*iterPos).St.y, (*iterPos).Ed.x, (*iterPos).Ed.y);
			else
			{
				MoveToEx(hdc, (*iterPos).St.x, (*iterPos).St.y, NULL);
				LineTo(hdc, (*iterPos).Ed.x, (*iterPos).Ed.y);
			}
		}
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
		closesocket(s);
		WSACleanup();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
