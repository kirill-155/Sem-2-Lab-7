#pragma once
#include "Head.h"

string path = "input_task1.txt";

void write_info(vector<point>& A, vector<point>& B)
{
	ifstream in(path);
	if (in.is_open())
	{
		int n, m;
		in >> n >> m;
		A.resize(n);
		B.resize(m);
		for (int i = 0; i < n; i++)
			in >> A[i];
		for (int i = 0; i < m; i++)
			in >> B[i];
	}
	in.close();
}

double Square(const vector<point>& A)
{
	double sum = 0;
	for (int i = 0; i < A.size() - 1; i++)
		sum += 0.5 * (A[i].y + A[i + 1].y) * (A[i + 1].x - A[i].x);
	return sum;
}

bool is_inside(const vector<point>& square, const vector<point>& B)
{
	for (int i = 0; i < 2; i++)
	{
		double a1 = square[i + 1].y - square[i].y, b1 = square[i].x - square[i + 1].x, c1 = (-a1) * square[i].x + (-b1) * square[i].y;
		double a2 = square[(i + 3) % 4].y - square[i + 2].y, b2 = square[i + 2].x - square[(i + 3) % 4].x, c2 = (-a2) * square[i + 2].x + (-b2) * square[i + 2].y;

		if (a1 < 0)
		{
			a1 = -a1;
			b1 = -b1;
			c1 = -c1;
		}
		else if (a1 == 0 && b1 < 0)
		{
			b1 = -b1;
			c1 = -c1;
		}
		if (a2 < 0)
		{
			a2 = -a2;
			b2 = -b2;
			c2 = -c2;
		}
		else if (a2 == 0 && b2 < 0)
		{
			b2 = -b2;
			c2 = -c2;
		}

		for (int j = 0; j < B.size(); j++)
		{
			if ((a1 * B[j].x + b1 * B[j].y + c1) * (a2 * B[j].x + b2 * B[j].y + c2) > 0)
			{
				return false;
			}
		}
	}
	return true;
}

void solve1()
{
	display();

	vector<point> A, B, C;
	write_info(A, B);

	pair<vector<point>, double> res;
	res.second = 1000000;

	for (int it1 = 0; it1 < A.size(); it1++)
		for (int it2 = it1 + 1; it2 < A.size(); it2++)
			for (int it3 = it2 + 1; it3 < A.size(); it3++)
				for (int it4 = it3 + 1; it4 < A.size(); it4++)
				{
					double dis1 = (A[it1] - A[it2]).dist2(), dis2 = (A[it2] - A[it3]).dist2(), dis3 = (A[it3] - A[it4]).dist2(),
						dis4 = (A[it4] - A[it1]).dist2(), dis5 = (A[it1] - A[it3]).dist2(), dis6 = (A[it2] - A[it4]).dist2();
					set<double> k;
					k.insert(dis1);
					k.insert(dis2);
					k.insert(dis3);
					k.insert(dis4);
					k.insert(dis5);
					k.insert(dis6);
					if (k.size() == 2)
					{
						vector<point> square;
						if (dis1 == dis2 && dis2 != dis5)
						{
							square.push_back(A[it1]);
							square.push_back(A[it2]);
							square.push_back(A[it3]);
							square.push_back(A[it4]);
						}
						else if (dis1 == dis5 && dis2 != dis5)
						{
							square.push_back(A[it1]);
							square.push_back(A[it2]);
							square.push_back(A[it4]);
							square.push_back(A[it3]);
						}
						else if (dis2 == dis5 && dis1 != dis2)
						{
							square.push_back(A[it1]);
							square.push_back(A[it3]);
							square.push_back(A[it2]);
							square.push_back(A[it4]);
						}
						else
							break;

						double s = Square(square);
						if (s < res.second && is_inside(square, B))
						{
							res.second = s;
							res.first = square;
						}
					}
				}

	C = res.first;
	if (C.size() == 0)
	{
		system("chcp 1251 > nul");
		cout << "Решения нет\n";
	}
	draw_point(A);
	draw_point(B, 0.5, 0);
	draw_line(C);
}

void task1(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);// Размер окна
	glutInitWindowPosition(400, 100);// позиция открытия
	glutCreateWindow("Лабораторная работа 7. Задание 1. Вариант 16");// Заголовок окна
	init();
	OXY();
	glutDisplayFunc(solve1);

	//glutMouseFunc(mouse);
	//glutKeyboardFunc(keyboard);

	//glutTimerFunc(100, timer, 0);
	glutMainLoop();
}