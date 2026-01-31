/*
* 所需文件
* 注：我这里用的SFML
*/
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Graphics/Font.hpp>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<iostream>
#include<array>
#include<vector>
/*
* 可以这么写，但不推荐
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
*/

//状态机
enum struct 状态机
{
	游戏开始,
	游戏结束
};

//玩家状态
enum struct 玩家
{
	O = 0,
	X = 1
};

int main()
{
	//初始化窗口
	sf::RenderWindow 窗口(sf::VideoMode{ { 600,600} }, "");
	//设置光标
	sf::CircleShape 鼠标光标(5);
	鼠标光标.setPosition({ 300,300 });
	鼠标光标.setOrigin({ 5, 5 });

	const sf::Angle rocate1 = sf::degrees(45), rocate2 = sf::degrees(-45);

	std::array<sf::RectangleShape, 4> 绘画棋盘;

	for (int i=0;i<4;i++)
	{
		if (i > 1) 
			绘画棋盘[i].setSize({ 10,600 });
		else if (i <= 1) 
			绘画棋盘[i].setSize({ 600,10 });
	}

	绘画棋盘[0].setPosition({ 0,200 });
	绘画棋盘[1].setPosition({ 0,400 });
	绘画棋盘[2].setPosition({ 200,0 });
	绘画棋盘[3].setPosition({ 400,0 });

	std::vector<std::array<sf::RectangleShape, 2>> 叉的数量;

	std::vector<sf::CircleShape> 圆的数量;

	//棋盘
	char 棋盘[3][4] =
	{
		{' ',' ',' ','\0'},
		{' ',' ',' ','\0'},
		{' ',' ',' ','\0'}
	};
	
	//设置状态
	玩家 玩家状态 = 玩家::X;

	//预设宽高
	int 格子宽度 = 600 / 3;
	int 格子高度 = 600 / 3;

	//限制帧数
	窗口.setFramerateLimit(60);

	int count = 9;

	//主循环
	while (窗口.isOpen())
	{
		//事件检测
		while (const std::optional 事件 = 窗口.pollEvent())
		{
			//关闭按钮
			if (事件->is<sf::Event::Closed>())
			{
				窗口.close();
			}
			//键盘事件
			if (事件->is<sf::Event::KeyPressed>())
			{
				if (事件->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
					窗口.close();
			}
			//鼠标事件
			if (事件->is<sf::Event::MouseButtonPressed>())
			{
				if (事件->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
				{
					//先算点在哪
					int 表格行数 = 事件->getIf<sf::Event::MouseButtonPressed>()->position.y / 格子宽度;
					int 表格列数 = 事件->getIf<sf::Event::MouseButtonPressed>()->position.x / 格子高度;
					//如果有位置了就跳过
					if (棋盘[表格行数][表格列数] != ' ') continue;

					//检测为O还是X
					if (玩家状态 == 玩家::O) 
					{
						count--;
						棋盘[表格行数][表格列数] = 'O';
						圆的数量.push_back(sf::CircleShape(100));
						圆的数量[圆的数量.size() - 1].setPosition(sf::Vector2f( (表格列数 * 200+5 ),(表格行数 * 200 +5 )));
						玩家状态 = 玩家::X;
					}
					else if (玩家状态 == 玩家::X) 
					{
						count--;
						棋盘[表格行数][表格列数] = 'X';
						玩家状态 = 玩家::O;
						叉的数量.push_back(std::array<sf::RectangleShape, 2>());
						叉的数量[叉的数量.size() - 1][0].setPosition( sf::Vector2f((float)(表格列数 * 200 + 100), (float)(表格行数 * 200 + 100)) );
						叉的数量[叉的数量.size() - 1][0].setSize({ 200.f, 10.f });
						叉的数量[叉的数量.size() - 1][0].setOrigin({ 100.f, 5.f });
						叉的数量[叉的数量.size() - 1][0].setRotation(rocate1);
						叉的数量[叉的数量.size() - 1][0].setFillColor(sf::Color::White);
						叉的数量[叉的数量.size() - 1][1].setPosition(sf::Vector2f((float)(表格列数 * 200 + 100), (float)(表格行数 * 200 + 100)));
						叉的数量[叉的数量.size() - 1][1].setSize({ 200.f, 10.f });
						叉的数量[叉的数量.size() - 1][1].setOrigin({ 100.f, 5.f });
						叉的数量[叉的数量.size() - 1][1].setRotation(rocate2);
						叉的数量[叉的数量.size() - 1][1].setFillColor(sf::Color::White);
					}

					if (
						(棋盘[0][0] == 棋盘[1][1] && 棋盘[0][0] == 棋盘[2][2]) ||
						(棋盘[2][0] == 棋盘[1][1] && 棋盘[2][0] == 棋盘[0][2])
						)
					{
						if (棋盘[1][1] == ' ') continue;
						//我在思考怎么使用sf::Text，暂时用它代替
						std::cout << "获胜者是：" << 棋盘[1][1];
						窗口.close();
					}
					else
					{
						for (int i = 0; i < 3; i++)
						{
							if ((棋盘[i][0] == 棋盘[i][1] && 棋盘[i][0] == 棋盘[i][2]) || (棋盘[0][i] == 棋盘[1][i] && 棋盘[0][i] == 棋盘[2][i]))
							{
								if (棋盘[i][i] == ' ') 
								{
									continue;
								}
								//我在思考怎么使用sf::Text，暂时用它代替
								std::cout << "获胜者是：" << 棋盘[i][i];
								窗口.close();
							}
						}
						if (count == 0)
						{
							std::cout << "平局";
							窗口.close();
						}
					}
					//井字棋逻辑
				}
			}
		}

		//获取鼠标位置
		sf::Vector2i 鼠标位置 = sf::Mouse::getPosition(窗口);
		//设置鼠标光标位置
		鼠标光标.setPosition({ static_cast<float>(鼠标位置.x),static_cast<float>(鼠标位置.y) });

		//清除上一帧
		窗口.clear();
		//绘制
		窗口.draw(鼠标光标);
		for (auto& i : 绘画棋盘)
			窗口.draw(i);
		for (auto& j : 叉的数量)
		{
			窗口.draw(j[0]);
			窗口.draw(j[1]);
		}
		for (auto& k : 圆的数量)
		{
			窗口.draw(k);
		}
		//更新
		窗口.display();
	}
	system("pause");
}