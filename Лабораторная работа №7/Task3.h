#pragma once
#include "Head.h"

bool is_graph(point a) {
	return pow(a.x, 5) - pow(a.y, 5) <= -2 && a.x - a.y <= -1;
}

void solve3()
{
	display();

	int k = 1000000;
	point a;
	int cnt = 0;
	for (int i = 0; i < k; i++)
	{
		a.rand_point(2, 2, 100);
		if (is_graph(a))
		{
			cnt++;
			double R, G, B;
			R = ((rand() % 18) - 6) / 10.0;
			G = ((rand() % 18) - 4) / 10.0;
			B = ((rand() % 18) - 3) / 10.0;
			draw_point(a, R, G, B, 1);
		}
	}
	double S = cnt * 1.0 / k * 16;
	cout << S;
}

void task3(int argc, char** argv)
{
	Scale = 300;
	vector<point> A = { {-2,-2},{-2,2},{2,2},{2,-2} };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Лабораторная работа 7. Задание 3. Вариант 14");
	init();
	OXY();
	draw_line(A, 0.5, 0);
	glutDisplayFunc(solve3);
	glutMainLoop();
}