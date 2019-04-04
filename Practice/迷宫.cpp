#include <iostream>
#include <assert.h>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <string>
#include<stdio.h>
using namespace std;
struct Coord {
	int r;
	int c;
}Begin = { 1,1 }, Over = { 8,8 };

typedef struct {
	int ord;
	Coord seat;
	int di;
}SElemType;

string pathmaze[10] =
{
	"0000000000",
	"0110111010",
	"0110111010",
	"0111100110",
	"0100011110",
	"0111011110",
	"0101110110",
	"0100010010",
	"0011111110",
	"0000000000"
};
int Pass(string *MyMaze, Coord CurPos);
void FootPrint(string *MyMaze, Coord CurPos);
void MarkPrint(string *MyMaze, Coord CurPos);
Coord NextPos(Coord CurPos, int Dir);
int MazePath(string *maze, Coord start, Coord end)
{
	
	typedef stack<SElemType> _STACK;
	_STACK S;
	SElemType e;
	Coord curpos;
	int curstep;
	curpos = start;
	curstep = 1;
	do
	{
		if (Pass(maze, curpos))
		{
			FootPrint(maze, curpos);
			e.di = 1;
			e.ord = curstep;
			e.seat = curpos;
			S.push(e);
			if (curpos.r == end.r && curpos.c == end.c)
			{
				return (true);
			}
			curpos = NextPos(curpos, 1);
			curstep++;
		}
		else
		{
			if (!S.empty())
			{
				e=S.top();
				S.pop();
				while (e.di == 4 && !S.empty())
				{
					MarkPrint(maze, e.seat);
					e=S.top();
					S.pop();
				}
				if (e.di<4)
				{
					e.di++;
					S.push(e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!S.empty());
	return false;
}

int Pass(string *MyMaze, Coord CurPos)
{
	if (MyMaze[CurPos.r][CurPos.c] == '1')
		return 1;
	else return 0;
}


void FootPrint(string *MyMaze, Coord CurPos) {
	MyMaze[CurPos.r][CurPos.c] = '*';
}

void MarkPrint(string *MyMaze, Coord CurPos) {
	MyMaze[CurPos.r][CurPos.c] = '!';
}

Coord NextPos(Coord CurPos, int Dir) {
	Coord ReturnPos;
	switch (Dir) {
	case 1:
		ReturnPos.r = CurPos.r+1;
		ReturnPos.c = CurPos.c;
		break;
	case 2:
		ReturnPos.r = CurPos.r;
		ReturnPos.c = CurPos.c+1;
		break;
	case 3:
		ReturnPos.r = CurPos.r-1;
		ReturnPos.c = CurPos.c;
		break;
	case 4:
		ReturnPos.r = CurPos.r;
		ReturnPos.c = CurPos.c-1;
		break;
	}
	return ReturnPos;
}

int main()
{
    int i;
	MazePath(pathmaze, Begin, Over);
	for (i=0;i<10;i++)
	{
		cout<<pathmaze[i]<<endl;
	}
}

