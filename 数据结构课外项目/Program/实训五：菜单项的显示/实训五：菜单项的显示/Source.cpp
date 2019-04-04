#include"conio.h"
#include<stdio.h>
#include<windows.h>
#include<string.h>
#define EnterKey      0x0d
#define UpCursor      38
#define LeftCursor    37
#define RightCursor   39
#define DownCursor    40
#define AltXKey       18
#define EscKey        27
#define SelectAttr    0x20        //ѡ�е�����
#define NoSelectAttr  0x70       //δѡ�е�����
#define SystemBorder  0x17       //δѡ�е�����
#define BorderColor   0x30       //δѡ�е�����
#define MainMenuLine  1          //���˵���ʾ�Ŀ�ʼ��
#define MainMenuCount 8          //���˵������Ŀ
#define MaxWindowWidth 80        //��Ļ���
#define NumberOfTotalSign 9
#define NumberOfEachLineSign 3
#define UpLeftSigh 0xDA
#define UpRightSign 0xBF
#define DownLeftSign 0xC0
#define DownRightSign 0xD9
#define BlankSign 0x20
#define RowSign 0xB3
#define LineSign 0xC4
#define TSign 0xC2
#define UpLeftX 0
#define UpLeftY 1
#define DownRightX 79
#define DownRightY 25
#define Color1 BLUE
#define Color2 LIGHTGRAY
int Sign[NumberOfTotalSign] = { UpLeftSigh,LineSign,UpRightSign,RowSign,BlankSign,RowSign,DownLeftSign,LineSign,DownRightSign };
int smallSign[NumberOfTotalSign] = { TSign,LineSign,TSign,RowSign,BlankSign,RowSign,DownLeftSign,LineSign,DownRightSign };
typedef signed short int ShortInt;

///////////////////////////////////
/////     ɫ�ʱ߿���        /////
///////////////////////////////////

void ShowALineOfBox(int upleftX, int upleftY, int breadth, int s[NumberOfEachLineSign], int color1, int color2)
{
	int x, *p;
	p = s;
	gotoxy(upleftX, upleftY);
	textbackground(color1);
	printf("%c", *p);
	for (x = 0; x<breadth - 2; x++)
	{
		textbackground(color2);
		printf("%c", *(p + 1));
	}
	textbackground(color1);
	printf("%c", *(p + 2));
	textbackground(BLACK);
}
void ShowBox(int upleftX, int upleftY, int downrightX, int downrightY, int s[NumberOfTotalSign], int color1, int color2)
{
	int y;
	ShowALineOfBox(upleftX, upleftY, downrightX - upleftX + 1, &s[0], color1, color1);
	for (y = 1; y <= downrightY - upleftY - 1; y++)
	{
		ShowALineOfBox(upleftX, upleftY + y, downrightX - upleftX + 1, &s[NumberOfEachLineSign], color1, color2);
	}
	ShowALineOfBox(upleftX, downrightY, downrightX - upleftX + 1, &s[2 * NumberOfEachLineSign], color1, color1);
}


//�˵��ṹ�嶨��
typedef struct MenuItemStru {
	ShortInt SubMenuItemCount;          //�Ӳ˵�����Ŀ
	ShortInt SubMenuItemWidth;          //�Ӳ˵��Ŀ��
	MenuItemStru * SubMenuItemAddr;     //�Ӳ˵����ݽṹ��ַ
	ShortInt MenuItemStrWidth;          //���˵����ַ�������
	char *   MenuItemStrAddr;           //���˵�����ַ�����ַ
};

typedef struct MenuSelectStru {
	ShortInt MenuIndex, MenuItemTotal;     //ѡ��˵��е�����
	MenuItemStru * pMenu;                 //��Ӧ���˵�/�Ӳ˵������ݽṹ��ַ
	PCHAR_INFO AddrOfSaveText;            //���������˵�����Ŀռ�
	bool  PullDownMenu;                   //�����˵��з���ʾ
	ShortInt left, top, right, bottom;
};

//char * S_S_Box  ="�Ŀ�����";
char * S_S_Box = "�Ŀ� ����";
char * T_S_Box = "��³ ����";
char * B_S_Box = "�Ŀ� ����";

//     File�Ӳ˵��ַ���
char * LoadStr = "Load     F3";
char * PickStr = "Pick Alt-F3";
char * NewStr = "New";
char * SaveStr = "Save     F2";
char * WriteStr = "Write to";
char * DirStr = "Diretory";
char * ChangeStr = "Change Dir";
char * OsStr = "Os Shell";
char * QuitStr = "Quit  Alx-X";
//     Run �Ӳ˵��ַ���
char * RunSubStr = "Run           Ctrl-F9";
char * ProgStr = "Program reset Ctrl-F2";
char * GotoStr = "Go To cursor       F4";
char * TraceStr = "Trace into         F7";
char * StepStr = "Step over          F8";
char * UserStr = "User Screen    Alt-F5";
//    Compile�Ӳ˵��ַ���
char * CompileStr = "Compile to OBJ";
char * MakeStr = "Make EXE file";
char * LinkStr = "Link EXE file";
char * BuildStr = "Build all";
char * PrimaryStr = "Primary C file";
char * GetInfoStr = "Get info";
//    project�Ӳ˵��ַ���
char * ProjectStr = "Project name";
char * BreakStr = "Break make on";
char * AutoStr = "Auto dependencies";
char * ClearStr = "Clear project";
char * RemoveStr = "Remove messages";
//    Options�Ӳ˵��ַ���
char * CompilerStr = "Compiler";
char * LinkerStr = "Linker";
char * EnvironStr = "Environment";
char * DirectStr = "Directories";
char * ArgumentStr = "Arguments";
//    comiler parameter�Ӳ˵��ַ���
char * ModelStr = "Model";
char * DefinesStr = "Defines";
char * CodeStr = "Code generation";
char * OptimStr = "Optimization";
char * SourceStr = "Source";
char * ErrorsStr = "Errors";
char * NamesStr = "Names";
//    Link�Ӳ˵��ַ���
char * MapStr = "Map file";
char * InitialStr = "Initialize segments";
char * DefaultStr = "Default library";
char * WarnStr = "Warn duplicate symbols";
char * StackStr = "Stack warning";
char * CaseStr = "Case-sensitive link";
//   Environment�Ӳ˵��ַ���
char * MessageStr = "Message Tracking";
char * KeepStr = "Keep messages";
char * ConfigStr = "Config auto save";
char * EditAutoStr = "Edit auto save";
char * BackupStr = "Backup files";
char * TabSizeStr = "Tab Size";
char * ZoomedStr = "Zoomed windows";
char * ScreenStr = "Screen size";
//   Directory�Ӳ˵��ַ���
char * IncludeStr = "Include directories";
char * LibraryStr = "Library directories";
char * OutputStr = "Output directories";
char * TurboCStr = "Turbo C directory";
char * PickFStr = "Pick file name";
char * CurrentPStr = "Current pick file";
//   Argument�Ӳ˵��ַ���
char * SaveOptStr = "Save options";
char * RetriStr = "Retrieve options";
//   Debug�Ӳ˵��ַ���
char * EvaluteStr = "Evalute    Ctrl-F4";
char * CallStkStr = "Call stack Ctrl-F3";
char * FindFunStr = "Find function";
char * RefreshStr = "Refresh display";
char * DisplayStr = "Display swapping";
char * SourceDStr = "Source debugging";
//   Break/Watch�Ӳ˵��ַ���
char * AddWatStr = "Add watch Ctrl-F7";
char * DeleteStr = "Delete watch";
char * EditWatStr = "Edit watch";
char * RemAllStr = "Remove all watches";
char * ToggleStr = "Toggle breakpoint Ctrl-F8";
char * ClrAllStr = "Clear all breakpoints";
char * ViewStr = "View next breakpoint";


//////////////////////////////////////
//     File�Ӳ˵��ṹ             //
//////////////////////////////////////
MenuItemStru FileSubM[9] = { { 0,0,0,PickStr - LoadStr - 1,LoadStr },
{ 0,0,0,NewStr - PickStr - 1,PickStr },
{ 0,0,0,SaveStr - NewStr - 1,NewStr },
{ 0,0,0,WriteStr - SaveStr - 1,SaveStr },
{ 0,0,0,DirStr - WriteStr - 1,WriteStr },
{ 0,0,0,ChangeStr - DirStr - 1,DirStr },
{ 0,0,0,OsStr - ChangeStr - 1,ChangeStr },
{ 0,0,0,QuitStr - OsStr - 1,OsStr },
{ 0,0,0,RunSubStr - QuitStr - 1,QuitStr } };

//////////////////////////////////////
//     Run �Ӳ˵��ṹ              //
//////////////////////////////////////
MenuItemStru RunSubM[6] = { { 0,0,0,ProgStr - RunSubStr - 1,RunSubStr },
{ 0,0,0,GotoStr - ProgStr - 1,ProgStr },
{ 0,0,0,TraceStr - GotoStr - 1,GotoStr },
{ 0,0,0,StepStr - TraceStr - 1,TraceStr },
{ 0,0,0,UserStr - StepStr - 1,StepStr },
{ 0,0,0,CompileStr - UserStr - 1,UserStr } };

//////////////////////////////////////
//    Compile�Ӳ˵����ݽṹ����     //
//////////////////////////////////////
MenuItemStru CompSubM[6] = { { 0,0,0,MakeStr - CompileStr - 1,CompileStr },
{ 0,0,0,LinkStr - MakeStr - 1,MakeStr },
{ 0,0,0,BuildStr - LinkStr - 1,LinkStr },
{ 0,0,0,PrimaryStr - BuildStr - 1,BuildStr },
{ 0,0,0,GetInfoStr - PrimaryStr - 1,PrimaryStr },
{ 0,0,0,ProjectStr - GetInfoStr - 1,GetInfoStr } };

//////////////////////////////////////
//    project�Ӳ˵����ݽṹ����     //
//////////////////////////////////////
MenuItemStru ProjSubM[5] = { { 0,0,0,BreakStr - ProjectStr - 1,ProjectStr },
{ 0,0,0,AutoStr - BreakStr - 1,BreakStr },
{ 0,0,0,ClearStr - AutoStr - 1,AutoStr },
{ 0,0,0,RemoveStr - ClearStr - 1,ClearStr },
{ 0,0,0,CompilerStr - RemoveStr - 1,RemoveStr } };

///////////////////////////////////////////////////////////////////////
// Options�Ӳ˵����ݽṹ����                                         //
//�ò˵��������comiler parameter                                    //
//              Link                                                 //
//              Environment                                          //
//              Directory                                            //
//              Argument                                             //
///////////////////////////////////////////////////////////////////////
//    comiler parameter�Ӳ˵����ݽṹ����     //
MenuItemStru CompPSubM[7] = { { 0,0,0,DefinesStr - ModelStr - 1,ModelStr },
{ 0,0,0,CodeStr - DefinesStr - 1,DefinesStr },
{ 0,0,0,OptimStr - CodeStr - 1,CodeStr },
{ 0,0,0,SourceStr - OptimStr - 1,OptimStr },
{ 0,0,0,ErrorsStr - SourceStr - 1,SourceStr },
{ 0,0,0,NamesStr - ErrorsStr - 1,ErrorsStr },
{ 0,0,0,MapStr - NamesStr - 1,NamesStr } };

//    Link�Ӳ˵����ݽṹ����     //
MenuItemStru LinkerSubM[6] = { { 0,0,0,InitialStr - MapStr - 1,MapStr },
{ 0,0,0,DefaultStr - InitialStr - 1,InitialStr },
{ 0,0,0,WarnStr - DefaultStr - 1,DefaultStr },
{ 0,0,0,StackStr - WarnStr - 1,WarnStr },
{ 0,0,0,CaseStr - StackStr - 1,StackStr },
{ 0,0,0,MessageStr - CaseStr - 1,CaseStr } };

//   Environment�Ӳ˵����ݽṹ����  //
MenuItemStru EnvironSubM[8] = { { 0,0,0,KeepStr - MessageStr - 1,MessageStr },
{ 0,0,0,ConfigStr - KeepStr - 1,KeepStr },
{ 0,0,0,EditAutoStr - ConfigStr - 1,ConfigStr },
{ 0,0,0,BackupStr - EditAutoStr - 1,EditAutoStr },
{ 0,0,0,TabSizeStr - BackupStr - 1,BackupStr },
{ 0,0,0,ZoomedStr - TabSizeStr - 1,TabSizeStr },
{ 0,0,0,ScreenStr - ZoomedStr - 1,ZoomedStr },
{ 0,0,0,ScreenStr - ScreenStr - 1,ScreenStr } };

//   Directory�Ӳ˵����ݽṹ����   //
MenuItemStru DirectSubM[6] = { { 0,0,0,LibraryStr - IncludeStr - 1,IncludeStr },
{ 0,0,0,OutputStr - LibraryStr - 1,LibraryStr },
{ 0,0,0,TurboCStr - OutputStr - 1,OutputStr },
{ 0,0,0,PickFStr - TurboCStr - 1,TurboCStr },
{ 0,0,0,CurrentPStr - PickFStr - 1,PickFStr },
{ 0,0,0,SaveOptStr - CurrentPStr - 1,CurrentPStr } };

//   Argument  �Ӳ˵����ݽṹ����   //
MenuItemStru ArgumentSubM[2] = { { 0,0,0,RetriStr - SaveOptStr - 1,SaveOptStr },
{ 0,0,0,EvaluteStr - RetriStr - 1,RetriStr } };

//////////////////////////////////////
//    Option�Ӳ˵����ݽṹ����      //
//////////////////////////////////////
MenuItemStru OptSubM[5] = { { 7,OptimStr - CodeStr - 1,CompPSubM,LinkerStr - CompilerStr - 1,CompilerStr },
{ 5,StackStr - WarnStr - 1,LinkerSubM,EnvironStr - LinkerStr - 1,LinkerStr },
{ 5,EditAutoStr - ConfigStr - 1,EnvironSubM,DirectStr - EnvironStr - 1,EnvironStr },
{ 5,OutputStr - LibraryStr - 1,DirectSubM,ArgumentStr - DirectStr - 1,DirectStr },
{ 2,EvaluteStr - RetriStr - 1,ArgumentSubM,ModelStr - ArgumentStr - 1,ArgumentStr } };

//////////////////////////////////////
//   Debug  �Ӳ˵����ݽṹ����     //
//////////////////////////////////////
MenuItemStru DebSubM[6] = { { 0,0,0,CallStkStr - EvaluteStr - 1,EvaluteStr },
{ 0,0,0,FindFunStr - CallStkStr - 1,CallStkStr },
{ 0,0,0,RefreshStr - FindFunStr - 1,FindFunStr },
{ 0,0,0,DisplayStr - RefreshStr - 1,RefreshStr },
{ 0,0,0,SourceDStr - DisplayStr - 1,DisplayStr },
{ 0,0,0,AddWatStr - SourceDStr - 1,SourceDStr } };

//////////////////////////////////////
//   Break/Watch�Ӳ˵����ݽṹ����  //
//////////////////////////////////////
MenuItemStru WatSubM[7] = { { 0,0,0,DeleteStr - AddWatStr - 1,AddWatStr },
{ 0,0,0,EditWatStr - DeleteStr - 1,DeleteStr },
{ 0,0,0,RemAllStr - EditWatStr - 1,EditWatStr },
{ 0,0,0,ToggleStr - RemAllStr - 1,RemAllStr },
{ 0,0,0,ClrAllStr - ToggleStr - 1,ToggleStr },
{ 0,0,0,ViewStr - ClrAllStr - 1,ClrAllStr },
{ 0,0,0,20,ViewStr } };//

					   //////////////////////////////////////
					   //         ���˵����ݽṹ����       //
					   //////////////////////////////////////
char * FileStr = "File";
char * EditStr = "Edit";
char * RunStr = "Run";
char * CompStr = "Compile";
char * ProjStr = "Project";
char * OptStr = "Options";
char * DebStr = "Debug";
char * WatStr = "Break/Watch";
int MainMenuItemCol[MainMenuCount] = { 0x02,0x0a,0x12,0x18,0x24,0x2f,0x39,0x41 };         //���˵�����ʾ����λ��

																						  //ʵѵ�������˵�����,MyMenu��ʵ����ʱ�����飬��������ʵ�ɴ�����MainMenu�����еõ�
char * MyMenu[MainMenuCount] = { FileStr,EditStr,RunStr,CompStr,ProjStr,OptStr,DebStr,WatStr };

MenuItemStru MainMenu[MainMenuCount] = { { 0x09,NewStr - PickStr - 1,FileSubM,EditStr - FileStr - 1,FileStr },
{ 0x0 ,00, 0,RunStr - EditStr - 1,EditStr },
{ 0x06,GotoStr - ProgStr - 1,RunSubM ,CompStr - RunStr - 1,RunStr },
{ 0x06,GetInfoStr - PrimaryStr - 1,CompSubM,ProjStr - CompStr - 1,CompStr },
{ 0x05,ClearStr - AutoStr - 1,ProjSubM,OptStr - ProjStr - 1,ProjStr },
{ 0x05,ArgumentStr - DirectStr - 1,OptSubM,11,OptStr },
{ 0x06,FindFunStr - CallStkStr - 1,DebSubM ,OptStr - DebStr - 1,DebStr },
{ 0x07,ClrAllStr - ToggleStr - 1,WatSubM ,DebStr - WatStr - 1,WatStr }, };

//ѡ����ʷ������
CHAR_INFO SecondSave[300], FirstSave[300];
MenuSelectStru His[3] = { { 0,8,MainMenu,0,false,0,0,0,0 },
{ 0,9,FileSubM,FirstSave,false,2,2,12,10 },
{ 0,0,0,SecondSave,false,0,0,0,0 } };
int Layer;  //��ǰ�˵������Ĳ� 


ShortInt SelectLayer = 0;
KeyValueStru CurrentKey;


int leftspace;
COORD coordcurrent;
void CalculatePosition()
{
	int j;
	j = strlen(His[Layer].pMenu[His[Layer].MenuIndex].MenuItemStrAddr);
	if (Layer == 0)
	{
		coordcurrent.X = MainMenuItemCol[His[Layer].MenuIndex];
		coordcurrent.Y = His[Layer].top;
	}
	else
	{
		coordcurrent.X = His[Layer].left;
		coordcurrent.Y = His[Layer].top + His[Layer].MenuIndex;
		leftspace = His[Layer].right - His[Layer].left + 1 - j;
	}
}

void reprintbackbox()
{
	if (Layer == 0)
	{
		gotoxy(0, 0);
		textattr(0x70);
		printf("%80s", " ");
	}
	else
	{
		ShowBox(His[Layer].left - 1, His[Layer].top - 1, His[Layer].right + 1, His[Layer].bottom + 1, smallSign, Color1, Color2);
	}
}


void ShowMenu()
{
	int i;
	int CurColor = SelectAttr;
	reprintbackbox();
	CalculatePosition();
	gotoxy(coordcurrent.X, coordcurrent.Y);
	textattr(CurColor);
	printf("%s", His[Layer].pMenu[His[Layer].MenuIndex].MenuItemStrAddr);
	for (i = 0; i < leftspace; i++)
	{
		printf("%s", " ");
	}
	CurColor = NoSelectAttr;

}



int main()
{
	clrscr();
	ShowBox(UpLeftX, UpLeftY, DownRightX, DownRightY, Sign, Color1, Color2);
	Layer = 0;
	His[Layer].MenuIndex = 4;
	ShowMenu();
	kbhit();
	His[Layer].MenuIndex = 6;
	ShowMenu();
	kbhit();
	Layer = 1;
	His[Layer].MenuIndex = 4;
	ShowMenu(); 
	kbhit();
	His[Layer].MenuIndex = 6;
	ShowMenu();
	getchar();
}

