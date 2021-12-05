#include "global.h"
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <windows.system.h>

using namespace std;

void menu(global g);

int main()
{
	setlocale(LC_ALL, "ru");
	global g;

	cout << "Московский трафик\n\n";
	
	if (!g.ConnectToDB()) return 0;

	g.calc_corners();

	double* b = new double[2];
	b[0] = 37.8;
	b[1] = 56;

	double* b1 = new double[2];
	b1[0] = 37.5;
	b1[1] = 55.8;

	g.take_cars("2021-11-29 17:00:00", "2021-11-29 17:20:00", b, b1);

	for (size_t i = 0; i < N*N; i++)
	{
		for (size_t j = 0; j < N*N; j++)
			cout << g.matrix_directions[i][j] << ' ';
		cout << '\n';
	}

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

