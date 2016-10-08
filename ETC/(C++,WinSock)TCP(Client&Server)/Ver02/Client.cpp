#include <windows.h>
#include <TCHAR.H>
#include "resource.h"
#include <list>
#include <ctime>
#include <cstdio>
using namespace std;
#define OFFSET 10 //
#define WM_ASYNC WM_USER+2

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
	TCHAR str[100];
	BOOL string;

}Shape;
struct Chat // 채팅 추가
{
	TCHAR text[100];

};

template <typename T>
struct SendStruct
{
	int Packnum;
	T use;

};
class Is_Delete : public unary_function <Shape, bool>
{
private:
	Shape src;
public:
	Is_Delete(list<Shape> ::reverse_iterator src) {
		this->src = *src;
	}
	bool operator()(Shape& dest) {
		if (dest.hPen == src.hPen &&
			dest.hBrush == src.hBrush &&
			dest.St.x == src.St.x &&
			dest.Ed.x == src.Ed.x &&
			dest.pFunc == src.pFunc &&
			dest.bColor == src.pColor)
			return true;
		return false;
	}
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
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("Client Window"),
		WS_OVERLAPPEDWINDOW,
		400,
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
	static WSADATA wsadata;
	static SOCKET s, cs;
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static HDC hdc, memdc;	
	static HBITMAP hbitmap,oldmap;
	PAINTSTRUCT ps;
	static int StX, StY;
	static int EdX, EdY;
	static list <Shape> temp;
	static Shape temp1;
	static Shape copyShape;
	static bool selected;
	static bool drag;
	static bool edit;
	static bool copy; //
	CHOOSECOLOR COLOR;
	CHOOSEFONT FONT;
	static COLORREF tmp[16];
	OPENFILENAME SFN;
	OPENFILENAME OFN;
	static list<Shape> ::reverse_iterator sltIter;
	TCHAR str[100], lpstrFile[100] = _T("");
	TCHAR filter[] = _T("Every File(*.*) \0*.*\0Text File\0*.txt;*.doc\0");
	TCHAR lpstrFileName[100] = _T("");
	static HMENU hMenu, hSubMenu, hDrawSubmenu, hWorkSubmenu;
	static Chat chat;
	static int chatcount; // 채팅 추가
	static int ctcut;
	static int plus;
	static RECT rt;
	int size, msgLen;
	char testbuf[100000];
	static list<Chat> chatlist;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rt);		
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.s_addr = inet_addr("192.168.0.121");
		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) == -1) return 0;
		temp.clear();
		selected = false; //
		drag = false;
		edit = false;
		copy = false;
		for (int i = 0; i < 16; i++)
			tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
		hMenu = GetMenu(hwnd); 
		hDrawSubmenu = GetSubMenu(hMenu, 0);//
		hSubMenu = GetSubMenu(hMenu, 3);
		hWorkSubmenu = GetSubMenu(hMenu, 4); //
		EnableMenuItem(hWorkSubmenu, ID_DRAWPAINT, MF_GRAYED); //
		EnableMenuItem(hSubMenu, ID_COPY, MF_GRAYED);
		EnableMenuItem(hSubMenu, ID_PASTE, MF_GRAYED);
		chatcount = 0;
		WSAAsyncSelect(s, hwnd, WM_ASYNC, FD_READ);
		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) == -1) return 0;
		break;

	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		hbitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		oldmap = (HBITMAP)SelectObject(memdc, hbitmap);

		for (list<Shape> ::iterator iterPos = temp.begin();
		iterPos != temp.end(); ++iterPos)
		{
			SelectObject(memdc, (*iterPos).hBrush);
			SelectObject(memdc, (*iterPos).hPen);
			if ((*iterPos).pFunc)
				(*iterPos).pFunc(memdc, (*iterPos).St.x, (*iterPos).St.y, (*iterPos).Ed.x, (*iterPos).Ed.y);
			else
			{
				MoveToEx(memdc, (*iterPos).St.x, (*iterPos).St.y, NULL);
				LineTo(memdc, (*iterPos).Ed.x, (*iterPos).Ed.y);
			}
		}
		if (drag)
		{
			SelectObject(memdc, temp1.hBrush);
			SelectObject(memdc, temp1.hPen);
			if (temp1.pFunc)
				temp1.pFunc(memdc, temp1.St.x, temp1.St.y, temp1.Ed.x, temp1.Ed.y);
			else
			{
				MoveToEx(memdc, temp1.St.x, temp1.St.y, NULL);
				LineTo(memdc, temp1.Ed.x, temp1.Ed.y);
			}
		}
		if (edit && selected && (temp.size() != 0))
		{
			Rectangle(memdc, StX - 3, StY - 3, StX + 3, StY + 3);
			Rectangle(memdc, EdX - 3, EdY - 3, EdX + 3, EdY + 3);
			if ((*sltIter).pFunc)
			{
				Rectangle(memdc, EdX - 3, StY - 3, EdX + 3, StY + 3);
				Rectangle(memdc, StX - 3, EdY - 3, StX + 3, EdY + 3);
			}
		}
		SelectObject(memdc, GetStockObject(WHITE_BRUSH));
		Rectangle(memdc, 500, 0, 780, 450);
		TextOut(memdc, 501, 430, chat.text, wcslen(chat.text));
		int cnty = 0;
		list<Chat>::iterator iterp = chatlist.begin();
		for (int i = 0; i < plus; i++) {
			iterp++;
		}
		for (iterp;
		iterp != chatlist.end(); ++iterp) {
			TextOut(memdc, 501, 1 + (cnty * 20), iterp->text, wcslen(iterp->text));
			cnty++;
			ctcut++;
			if (ctcut > 21)
				plus++;
		}
		ctcut = 0;

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, memdc, 0, 0, SRCCOPY);
		DeleteObject(SelectObject(memdc, oldmap));
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
	}
		break;
	case WM_ASYNC:
		switch (lParam) {
		case FD_READ:
			msgLen = recv(s, testbuf, sizeof(char) * 1000, 0);
			int * asd = (int*)testbuf;
			if (*asd == 1) {
				SendStruct<Shape> sst = *(SendStruct<Shape>*) testbuf;
				sst.use.hPen = CreatePen(PS_SOLID, 1, sst.use.pColor);
				sst.use.hBrush = CreateSolidBrush(sst.use.bColor);
				temp.push_back(sst.use);
			}
			else if (*asd == 2) {
				SendStruct<Chat> sst = *(SendStruct<Chat>*) testbuf;
				chatlist.push_back(sst.use);
				InvalidateRgn(hwnd, NULL, true);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		if (!edit)
		{
			if (!drag)
			{
				temp1.St.x = LOWORD(lParam);
				temp1.St.y = HIWORD(lParam);
				temp1.Ed.x = LOWORD(lParam);
				temp1.Ed.y = HIWORD(lParam);
				drag = true;
			}
		}
		else
		{
			for (sltIter = temp.rbegin();
			sltIter != temp.rend(); ++sltIter)
			{
				if (((*sltIter).St.x > (*sltIter).Ed.x)
					&& ((*sltIter).St.y > (*sltIter).Ed.y)) //우하단에서 좌상단으로 그릴 시
				{
					StX = (*sltIter).Ed.x;
					StY = (*sltIter).Ed.y;
					EdX = (*sltIter).St.x;
					EdY = (*sltIter).St.y;
				}
				else if (((*sltIter).St.x > (*sltIter).Ed.x)
					&& ((*sltIter).St.y < (*sltIter).Ed.y)) //우상단에서 좌하단으로 그릴 시
				{
					StX = (*sltIter).Ed.x;
					StY = (*sltIter).St.y;
					EdX = (*sltIter).St.x;
					EdY = (*sltIter).Ed.y;
				}
				else if (((*sltIter).St.x < (*sltIter).Ed.x)
					&& ((*sltIter).St.y < (*sltIter).Ed.y)) //좌상단에서 우하단으로 그릴 시
				{
					StX = (*sltIter).St.x;
					StY = (*sltIter).St.y;
					EdX = (*sltIter).Ed.x;
					EdY = (*sltIter).Ed.y;
				}
				else if (((*sltIter).St.x < (*sltIter).Ed.x)
					&& ((*sltIter).St.y >(*sltIter).Ed.y)) //좌하단에서 우상단으로 그릴 시
				{
					StX = (*sltIter).St.x;
					StY = (*sltIter).Ed.y;
					EdX = (*sltIter).Ed.x;
					EdY = (*sltIter).St.y;
				}
				if (((EdX - StX) > (LOWORD(lParam) - StX))
					&& ((EdY - StY) > (HIWORD(lParam) - StY))
					&& ((LOWORD(lParam) > StX) && (HIWORD(lParam) > StY))
					)
				{
					selected = true;
					EnableMenuItem(hSubMenu, ID_COPY, MF_ENABLED);//
					break;
				}
				else
				{
					selected = false;
					EnableMenuItem(hSubMenu, ID_COPY, MF_GRAYED);//
					if (!copy) {
						EnableMenuItem(hSubMenu, ID_PASTE, MF_GRAYED);//
					}
				}
			}
			InvalidateRgn(hwnd, NULL, true);
		}
		break;
	case WM_LBUTTONUP:
		if (drag)
		{
			temp1.Ed.x = LOWORD(lParam);
			temp1.Ed.y = HIWORD(lParam);
			temp.push_back(temp1);
			drag = false;

			InvalidateRgn(hwnd, NULL, true);
			SendStruct<Shape> sst = { 1 , temp1 };
			send(s, (char*)&sst, sizeof(SendStruct<Shape>), 0);
		}
		break;
	case WM_MOUSEMOVE:
		if (drag)
		{
			if (temp1.FREE)
			{
				temp1.St.x = temp1.Ed.x;
				temp1.St.y = temp1.Ed.y;
				temp1.Ed.x = LOWORD(lParam);
				temp1.Ed.y = HIWORD(lParam);
				temp.push_back(temp1);
				SendStruct<Shape> sst = { 1 , temp1 };
				send(s, (char*)&sst, sizeof(SendStruct<Shape>), 0);
			}
			else
			{
				temp1.Ed.x = LOWORD(lParam);
				temp1.Ed.y = HIWORD(lParam);
			}
			InvalidateRgn(hwnd, NULL, true);

		}

		break;
	case WM_CHAR: // 채팅 추가
	{
		if (wParam == VK_RETURN) {
			SendStruct<Chat> sst = { 2, chat };
			send(s, (char*)&sst, sizeof(SendStruct<Chat>), 0);
			chatcount = 0;
		}
		else if (wParam == VK_BACK) {
			if (chatcount > 0)
				chatcount--;
		}
		else {
			if (chatcount < 32)
				chat.text[chatcount++] = wParam;
		}
		chat.text[chatcount] = NULL;
		InvalidateRgn(hwnd, NULL, true);
		break;
	}
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_DELETE:
			if (selected) {
				temp.remove_if(Is_Delete(sltIter));
				InvalidateRgn(hwnd, NULL, true);
			}
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LINE:
			temp1.pFunc = NULL;
			temp1.string = false;
			temp1.FREE = false;
			break;
		case ID_CIRCLE:
			temp1.pFunc = Ellipse;
			temp1.string = false;
			temp1.FREE = false;
			break;
		case ID_RECTANGLE:
			temp1.pFunc = Rectangle;
			temp1.string = false;
			temp1.FREE = false;
			break;
		case ID_POLYLINE:
			temp1.pFunc = NULL;
			temp1.FREE = true;
			temp1.string = false;
			break;
		case ID_FONTDLG:
			temp1.pFunc = NULL;
			temp1.string = true;
			temp1.FREE = false;
			break;
		case ID_PEN:
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.Flags = CC_FULLOPEN;
			COLOR.lpCustColors = tmp;
			if (ChooseColor(&COLOR) != 0)
			{
				temp1.pColor = COLOR.rgbResult;
				temp1.hPen = CreatePen(PS_SOLID, 1, temp1.pColor);
			}

			break;
		case ID_BRUSH:
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.Flags = CC_FULLOPEN;
			COLOR.lpCustColors = tmp;
			if (ChooseColor(&COLOR) != 0)
			{
				temp1.bColor = COLOR.rgbResult;
				temp1.hBrush = CreateSolidBrush(temp1.bColor);
			}
			break;
		case ID_FILESAVE:
			memset(&SFN, 0, sizeof(OPENFILENAME));
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hwnd;
			SFN.lpstrFilter = filter;
			SFN.lpstrFile = lpstrFile;
			SFN.nMaxFile = 100;
			SFN.lpstrInitialDir = _T(".");
			if (GetSaveFileName(&SFN) != 0) {
				SaveToFile(SFN.lpstrFile, temp);
			}
			break;
		case ID_COPY:
			if (selected) {//
				copyShape = *sltIter;
				EnableMenuItem(hSubMenu, ID_PASTE, MF_ENABLED);
				copy = true;
			}
			break;
		case ID_PASTE://
			copyShape.St.x += OFFSET;//
			copyShape.St.y += OFFSET;//
			copyShape.Ed.x += OFFSET;//
			copyShape.Ed.y += OFFSET;//
			InvalidateRgn(hwnd, NULL, true);//
			break;
		case ID_FILELOAD:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 100;
			OFN.lpstrInitialDir = _T(".");
			if (GetSaveFileName(&OFN) != 0) {
				LoadToFile(OFN.lpstrFile, temp);
			}
			InvalidateRgn(hwnd, NULL, true);
			break;
		case ID_DRAWPAINT:
			edit = false;
			EnableMenuItem(hSubMenu, ID_COPY, MF_GRAYED); //
			if (!copy)
				EnableMenuItem(hSubMenu, ID_PASTE, MF_GRAYED); //
			EnableMenuItem(hWorkSubmenu, ID_EDITPAINT, MF_ENABLED); //
			EnableMenuItem(hWorkSubmenu, ID_DRAWPAINT, MF_GRAYED); //
			EnableMenuItem(hDrawSubmenu, ID_RECTANGLE, MF_ENABLED);//
			EnableMenuItem(hDrawSubmenu, ID_CIRCLE, MF_ENABLED);
			EnableMenuItem(hDrawSubmenu, ID_LINE, MF_ENABLED);//
			InvalidateRgn(hwnd, NULL, true); //
			break;
		case ID_EDITPAINT:
			edit = true;
			EnableMenuItem(hWorkSubmenu, ID_DRAWPAINT, MF_ENABLED);
			EnableMenuItem(hWorkSubmenu, ID_EDITPAINT, MF_GRAYED);//
			EnableMenuItem(hDrawSubmenu, ID_RECTANGLE, MF_GRAYED);//
			EnableMenuItem(hDrawSubmenu, ID_CIRCLE, MF_GRAYED);//
			EnableMenuItem(hDrawSubmenu, ID_LINE, MF_GRAYED);//
			break;
		}
		break;
	case WM_DESTROY:
		closesocket(s);
		WSACleanup();
		DeleteObject(temp1.hBrush);
		DeleteObject(temp1.hPen);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}