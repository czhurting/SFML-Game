#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<math.h>
//
//template<typename T>
//struct Vector2
//{
//    T x;
//    T y;
//    Vector2(T x, T y) :x(x), y(y) {}
//};
//
//int main()
//{
//    // 1. 开个大窗口 (800x600)，默认样式
//    initgraph(1280, 768);
//
//    Vector2<int> Origin(300, 300);
//
//    BeginBatchDraw();
//
//    while (true)
//    {
//        ExMessage message;
//        while (peekmessage(&message))
//        {
//            if (message.message == WM_MOUSEMOVE)
//            {
//                Origin.x = message.x;
//                Origin.y = message.y;
//            }
//        }
//        cleardevice();
//        solidcircle(Origin.x,Origin.y, 50);
//        FlushBatchDraw();
//        Sleep(60.f/1000.f);
//    }
//
//    EndBatchDraw();
//}


enum struct Node
{
	None = 0,
	X = 1,
	O = 2
};

Node CheckWin(Node board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i][i] == Node::None) continue;
		if ((board[i][0] == board[i][1] && board[i][0] == board[i][2]) || (board[0][i] == board[1][i] && board[0][i] == board[2][i]))
			return board[i][i];
	}
	if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[2][0] == board[1][1] && board[1][1] == board[0][2]))
		return board[1][1];
	return Node::None;
}

bool CheckNoWin(Node board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == Node::None)
				return 0;
		}
	}
	return 1;
}

int main()
{
	initgraph(600, 600, 255);
	constexpr int width = 200;
	Node board[3][3] =
	{
		{Node::None,Node::None,Node::None},
		{Node::None,Node::None,Node::None},
		{Node::None,Node::None,Node::None}
	};
	int x = 0;
	int y = 0;
	Node Player = Node::O;
	BeginBatchDraw();
	while (true)
	{
		ExMessage msg;
		while (peekmessage(&msg))
		{
			if (msg.message==WM_MOUSEMOVE)
			{
				x = msg.x;
				y = msg.y;
			}
			if (msg.message == WM_LBUTTONDOWN)
			{
				int boardx = msg.x / width;
				int boardy = msg.y / width;
				if (board[boardx][boardy] != Node::None) continue;
				board[boardx][boardy] = Player;
				switch (Player)
				{
				case Node::O:
				{
					Player = Node::X;
				}break;
				case Node::X:
				{
					Player = Node::O;
				}break;
				}
			}
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE)
				{
					closegraph();
				}
			}
		}
		Node win=
		CheckWin(board);
		bool ping=
		CheckNoWin(board);

		cleardevice();

		fillcircle(x, y, 5);
		for (int i = 0; i < 3; i++) 
		{
			for (int j = 0; j < 3; j++) 
			{
				int centerX = i * width + width / 2;
				int centerY = j * width + width / 2;

				if (board[i][j] == Node::X) {
					line(centerX - 40, centerY - 40, centerX + 40, centerY + 40);
					line(centerX + 40, centerY - 40, centerX - 40, centerY + 40);
				}
				else if (board[i][j] == Node::O) {
					circle(centerX, centerY, 80);
				}
			}
		}
		FlushBatchDraw();
		Sleep(1000/120);

		if (win != Node::None || ping)
		{
			if (win==Node::None)
			{
				MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
			}
			else if(win==Node::O)
			{
				MessageBox(GetHWnd(), _T("O 玩家获胜"), _T("游戏结束"), MB_OK);
			}
			else if (win == Node::X)
			{
				MessageBox(GetHWnd(), _T("X 玩家获胜"), _T("游戏结束"), MB_OK);
			}
			break;
		}
	}

	EndBatchDraw();
}