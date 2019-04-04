#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

struct text_info {
    unsigned char winleft;
    unsigned char wintop;
    unsigned char winright;
    unsigned char winbottom;
    unsigned char attribute;
    unsigned char normattr;
    unsigned char currmode;
    unsigned char screenheight;
    unsigned char screenwidth;
    unsigned char curx;
    unsigned char cury;
};

enum COLORS {
    /*  dark colors     */
    BLACK,          
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    /*  light colors    */
    DARKGRAY, /* "light black" */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};
#define BLINK   0x80    /*  blink bit; doesn't work yet  */

#define _NOCURSOR      0
#define _SOLIDCURSOR   1
#define _NORMALCURSOR  2

/* 19 of 31 functions implemented, 62% */

int _conio_kbhit();
void _set_screen_lines(int nlines);
void _setcursortype(int _type);                                                 /* done */
void blinkvideo();
char *cgets(char *_str);                                 /* how does it work? */
void clreol();                                           /* what does it do? */
void clrscr();                                                                  /* done */
#define cprintf printf                                                          /* done */
int cputs(const char *_str);                                                    /* done */
#define cscanf scanf                                                            /* done */
void delline();
#define getch getchar                                                           /* done */
int getche();                                                                   /* done */
int gettext(int _left, int _top, int _right, int _bottom, void *_destin);
void gettextinfo(struct text_info *_r);                                         /* done */
void gotoxy(int x, int y);                                                      /* done */
void gppconio_init();                                                           /* done; does nothing */
void highvideo();                                                               /* maybe */
void insline();                                                                 /* done */
void intensevideo();
void lowvideo();
int movetext(int _left, int _top, int _right, int _bottom,
             int _destleft, int _desttop);
void normvideo();
int putch(int _c);                                                              /* done */
int puttext(int _left, int _top, int _right, int _bottom, void *_source);
void textattr(int _attr);                                                       /* done */
void textbackground(int _color);                                                /* done */
void textcolor(int _color);                                                     /* done */
void textmode(int _mode);
int ungetch(int);
int wherex();                                                                   /* done */
int wherey();                                                                   /* done */
void window(int _left, int _top, int _right, int _bottom);                      /* done */

#ifdef __cplusplus
}
#endif


int __FOREGROUND = LIGHTGRAY;
int __BACKGROUND = BLACK;

typedef struct {
	WORD VKey, AscChar;
}KeyValueStru;

void _setcursortype(int _type) {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	if (_type == _NOCURSOR)
		Info.bVisible = FALSE;
	else if (_type == _SOLIDCURSOR)
		Info.dwSize = 100;
	else if (_type == _NORMALCURSOR)
		Info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void clreol() {

}

void clrscr() {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;

	coord.X = 0;
	coord.Y = 0;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X * info.dwSize.Y, coord, &written);
	SetConsoleOutputCP(437); // 设置代码页，=437（英文），=936（简体中文）
	gotoxy(0, 0);
}

int cputs(const char *_str) {
	printf("%s\n", _str);
	return 0;
}

int getche() {
	int ch;
	ch = getch();
	printf("%c\n", ch);
	return ch;
}

int gettext(int _left, int _top, int _right, int _bottom, void * _destin)
{
	return 0;
}

KeyValueStru ReadKeyPush()
{
	INPUT_RECORD _InRec;
	DWORD _NumRead;
	KeyValueStru KeyValue;
	KeyValue.VKey = 0; KeyValue.AscChar = 0;

	if (!ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &_InRec, 1, &_NumRead))
		return KeyValue;
	if (_InRec.EventType != KEY_EVENT)
		return KeyValue;
	if (_InRec.Event.KeyEvent.bKeyDown == 0)
		return KeyValue;
	KeyValue.VKey = _InRec.Event.KeyEvent.wVirtualKeyCode;
	KeyValue.AscChar = _InRec.Event.KeyEvent.uChar.AsciiChar;
	return KeyValue;
}

KeyValueStru kbhit()
{
	KeyValueStru KeyValue;
	while (1)
	{
		KeyValue = ReadKeyPush();
		if (KeyValue.VKey != 0 || KeyValue.AscChar != 0) //使用ReadKeyDown()捕获按键弹起的VK_CODE
		{
			return(KeyValue);
			break;
		}
	}
}

void gettextinfo(struct text_info *_r) {
	CONSOLE_SCREEN_BUFFER_INFO Info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
	_r->winleft = Info.srWindow.Left;
	_r->winright = Info.srWindow.Right;
	_r->wintop = Info.srWindow.Top;
	_r->winbottom = Info.srWindow.Bottom;
	_r->attribute = Info.wAttributes;
	_r->normattr = LIGHTGRAY | BLACK;
	/*  _r->currmode = ; */ /* What is currmode? */
	_r->screenheight = Info.dwSize.Y;
	_r->screenwidth = Info.dwSize.X;
	_r->curx = wherex();
	_r->cury = wherey();
}

void puttext(int _left, int _top, int _right, int _bottom, PCHAR_INFO _source)
{
	COORD Corner, dwBufferSize;
	SMALL_RECT MyRect;
	Corner.X = _right - _left + 1;
	Corner.Y = _bottom - _top + 1;
	dwBufferSize.X = 0;
	dwBufferSize.Y = 0;
	MyRect.Left = _left; MyRect.Top = _top;
	MyRect.Right = _right; MyRect.Bottom = _bottom;
	WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), _source, Corner, dwBufferSize, &MyRect);
}

void gettext(int _left, int _top, int _right, int _bottom, PCHAR_INFO _target)
{
	COORD Corner, dwBufferSize;
	SMALL_RECT MyRect;
	Corner.X = _right - _left + 1;
	Corner.Y = _bottom - _top + 1;
	dwBufferSize.X = 0;
	dwBufferSize.Y = 0;
	MyRect.Left = _left; MyRect.Top = _top;
	MyRect.Right = _right; MyRect.Bottom = _bottom;
	ReadConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), _target, Corner, dwBufferSize, &MyRect);
}

void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void gppconio_init() {
	/* Do nothing */
}

void highvideo() {
	if (__FOREGROUND <= BROWN)
		textcolor(__FOREGROUND + 9);
	if (__BACKGROUND <= BROWN)
		textbackground(__BACKGROUND + 9);
}

void insline() {
	printf("\n");
}

int putch(int _c) {
	printf("%c", _c);
	return _c;
}

void textattr(int _attr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _attr);
	//  printf ("%d\n", text_info.screenheight);
}

void textbackground(int _color) {
	if (_color == BLINK)
		_color = WHITE;
	__BACKGROUND = _color;
	textattr(__FOREGROUND | (_color <<4));
}

void textcolor(int _color) {
	if (_color == BLINK)
		_color = WHITE;
	__FOREGROUND = _color;
	textattr(_color | __BACKGROUND);
}

int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.X;
}

int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition.Y - 2;
}

void window(int _left, int _top, int _right, int _bottom) {
	SMALL_RECT R;
	R.Left = _left;
	R.Top = _top;
	R.Right = _right;
	R.Bottom = _bottom;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &R);
	gotoxy(_left, _top);
}
