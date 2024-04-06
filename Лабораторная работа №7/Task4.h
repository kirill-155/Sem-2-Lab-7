#pragma once
#define _USE_MATH_DEFINES
#include "Head.h"
#include <corecrt_math_defines.h>

int equation = 3;

bool equation_a(point p) {
	return p.x >= -1 && p.x <= 1 && 0 <= p.y && p.y <= pow(p.x, 2) / (2 - pow(p.x, 4));
}

bool equation_b(point p) {
	return p.x >= -2 * M_PI / 3 && p.x <= 2 * M_PI / 3 && (0 <= p.y && p.y <= pow(sin(p.x), 3) || 0 >= p.y && p.y >= pow(sin(p.x), 3));
}

bool equation_c(point p) {
	return p.x >= 3 && p.x <= 11 && (0 <= p.y && p.y <= 1.0 / (4 * p.x * p.x - 9) || 0 >= p.y && p.y >= 1.0 / (4 * p.x * p.x - 9));
}

bool equation_d(point p) {
	return p.x >= -1 && p.x <= 1 && (0 <= p.y && p.y <= pow(M_E, 2 * p.x - 1) / pow(M_E, p.x) || 0 >= p.y && p.y >= pow(M_E, 2 * p.x - 1) / pow(M_E, p.x));
}

void solve4()
{
	display();

	int k = 1000000;
	point p;
	int cnt = 0;
	double S = 0;
	double R, G, B;
	double a = 0, b = 0;
	double ay = -2, by = 2;

	switch (equation) {
	case 0:
	{
		Scale = 600;

		a = -1, b = 1;
		for (int i = 0; i < k; i++)
		{
			p.rand_point2(a, b, ay, by);
			if (equation_a(p))
			{
				cnt++;
				double R, G, B;
				rand_RGB(R, G, B);
				draw_point(p, R, G, B, 2);
			}
		}
		break;
	}
	case 1:
	{
		Scale = 300;

		a = -2 * M_PI / 3, b = 2 * M_PI / 3;
		for (int i = 0; i < k; i++)
		{
			p.rand_point2(a, b, ay, by);
			if (equation_b(p))
			{
				cnt++;
				rand_RGB(R, G, B);
				draw_point(p, R, G, B, 1);
			}
		}
		break;
	}
	case 2:
	{
		Scale = 80;

		a = 3, b = 11;
		rand_RGB(R, G, B);
		for (int i = 0; i < k; i++)
		{
			p.rand_point2(a, b, ay, by);
			if (equation_c(p))
			{
				cnt++;
				draw_point(p, R, G, B, 2);
			}
		}
		break;
	}
	case 3:
	{
		Scale = 600;

		a = -1, b = 1;
		for (int i = 0; i < k; i++)
		{
			p.rand_point2(a, b, ay, by);

			if (equation_d(p))
			{
				cnt++;
				rand_RGB(R, G, B);
				draw_point(p, R, G, B, 2);
			}
		}
		break;
	}
	}
	S = cnt * 1.0 * (b - a) * (by - ay) / k;
	Scale = 80;
	cout << S << "\n";
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		// Действие при нажатии клавиши ESC
		exit(0);
		break;
	case 'a':
		if (equation == 0)
			equation = 3;
		else
			equation--;
		break;
	case 'd':
		if (equation == 3)
			equation = 0;
		else
			equation++;
		break;
	}
	solve4();
}

void task4(int argc, char** argv)
{
	Scale = 80;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Лабораторная работа 7. Задание 4. Вариант 11");
	init();
	OXY();
	glutDisplayFunc(solve4);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}