#include "global.h"
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <windows.system.h>

using namespace std;

void menu();

int main()
{
	setlocale(LC_ALL, "ru");
	global g;

	cout << "Московский трафик\n\n";
	
	if (!g.ConnectToDB()) return 0;

	g.calc_corners();



	//Sleep(1000);

	//menu(g);
	
	return 0;
}

void menu(global g)
{
	INT8 menu = 1;
	
	while (menu)
	{
		system("cls");
		cout << "Московский трафик\nКоординаты:\nВерхний правый: [" << g.right_up[0] << " : " << g.right_up[1] << "]\n";
		cout << "Нижний левый: [" << g.left_down[0] << " : " << g.left_down[1] << "]\n";

		cout << "1. Статистика устройств;" << endl;
		cout << "2. Информация о потоках;" << endl;
		cout << "0. Выход;" << endl;
		cin >> menu;
	}
}

