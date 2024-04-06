#pragma once
#include "Head.h"

int nu = 7, m = 18;
double R = 0.25;

void rand_points(vector<point>& A, int n)
{
	A.push_back({ (rand() % W * 2) - W,(rand() % H * 2) - H });
	A.push_back({ (rand() % W * 2) - W,(rand() % H * 2) - H });
	while (A.size() < n)
	{
		A.push_back({ (rand() % W * 2) - W,(rand() % H * 2) - H });
		for (int i = 2; i < A.size(); i++)
		{
			if (abs(A[i - 2].line(A[i - 1], A[A.size() - 1])) < 0.00001)
			{
				A[A.size() - 1] = { (rand() % W * 2) - W,(rand() % H * 2) - H };
				i = 1;
			}
		}
	}
}

void rand_M(vector<point>& A, point& p)
{
	int r = rand() % m;
	int it = 0;
	int mod = m % nu;
	int d = m / nu;
	for (int i = 0; i < nu; i++)
	{
		r -= d + (nu - mod == i);
		if (r < 0)
		{
			it = i;
			break;
		}
	}
	/*switch (r)
	{
	case 0:
	case 1:it = 0;
		break;
	case 2:
	case 3:it = 1;
		break;
	case 4:
	case 5:it = 2;
		break;
	case 6:
	case 7:
	case 8:it = 3;
		break;
	case 9:
	case 10:
	case 11:it = 4;
		break;
	case 12:
	case 13:
	case 14:it = 5;
		break;
	case 15:
	case 16:
	case 17:it = 6;
	}*/

	point s = A[it];
	for (double i = R; i != 1; i *= 2)
		s = (s + p) * 0.5;
	p = s;
}

void solve2()
{
	display();

	srand(time(0));
	vector<point> A;
	point p;
	rand_points(A, nu);
	p = { (rand() % W * 2) - W,(rand() % H * 2) - H };
	draw_point(A, 0.5, 0);

	for (int i = 0; i < 1000000; i++)
	{
		rand_M(A, p);
		draw_point(p, 0, 5, 0, 0.5);
	}
}

void task2(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Лабораторная работа 7. Задание 2. Вариант 93");
	init();
	OXY();
	glutDisplayFunc(solve2);
	glutMainLoop();
}