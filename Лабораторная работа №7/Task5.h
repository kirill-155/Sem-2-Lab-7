#pragma once
#include "Head.h"

struct chess_piece {
	int posichion;
	vector<int> Possible_move;

	chess_piece() = default;
	chess_piece(int n) : posichion(n) { }

	chess_piece operator=(const chess_piece& B)
	{
		posichion = B.posichion;
		Possible_move = B.Possible_move;
		return *this;
	}

	chess_piece& operator+=(const chess_piece& B)
	{
		set<int> s;
		for (int i = 0; i < Possible_move.size(); i++)
		{
			s.insert(Possible_move[i]);
		}
		for (int i = 0; i < B.Possible_move.size(); i++)
		{
			s.insert(B.Possible_move[i]);
		}
		vector<int> Possible_move_cop;
		for (int i : s)
		{
			Possible_move_cop.push_back(i);
		}
		Possible_move = Possible_move_cop;
		return *this;
	}
};

void draw_cell(const point& A, int id, double R = 0, double G = 0.5, double B = 0, double size = 5.0)
{
	glColor3f(R, G, B);
	if (id == -1)
	{
		glRasterPos2i(A.x * Scale - 3.5, A.y * Scale - 5);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'K');
	}
	else if (id == -2)
	{
		
	}
	else if (id < 10)
	{
		glRasterPos2i(A.x * Scale - 3.5, A.y * Scale - 5);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + id);
	}
	else if(id < 100)
	{
		glRasterPos2i(A.x * Scale - 7, A.y * Scale - 5);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + id / 10);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + id % 10);
	}
	else if (id < 1000)
	{
		glRasterPos2i(A.x * Scale - 10.5, A.y * Scale - 5);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + id / 100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + id / 10 % 10);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + id % 10);

	}

	glBegin(GL_LINE_LOOP);
	glVertex2i((A.x + 0.5) * Scale, (A.y + 0.5) * Scale);
	glVertex2i((A.x - 0.5) * Scale, (A.y + 0.5) * Scale);
	glVertex2i((A.x - 0.5) * Scale, (A.y - 0.5) * Scale);
	glVertex2i((A.x + 0.5) * Scale, (A.y - 0.5) * Scale);
	glEnd();
	glFlush();
}

void draw_field(const vector<point>& A, int idt, double R = 0, double G = 0.5, double B = 0)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < A.size(); i++)
	{
		draw_cell(A[i], i == idt ? -1 : i, R, G, B);
	}
}

void field(vector<point>& A, int n)
{
	double size = 10;

	Scale = H * size / n;
	double W1k = int(width / Scale * 100) / 100;
	int id = 0;

	for (int i = 1; i < n; i++)
	{
		double cenH = i;
		double ot = (W1k - i) / 2;
		for (int j = 0; j < i; j++)
		{
			A[id].y = cenH;
			A[id].x = ot + j + 0.5;
			id++;
		}
	}
	double cenH = n;
	double ot = (W1k - n) / 2;
	for (int j = 0; j < n; j++)
	{
		A[id].y = cenH;
		A[id].x = ot + j + 0.5;
		id++;
	}
	for (int i = n - 1; i > 0; i--)
	{
		double cenH = n * 2 - i;
		double ot = (W1k - i) / 2;
		for (int j = 0; j < i; j++)
		{
			A[id].y = cenH;
			A[id].x = ot + j + 0.5;
			id++;
		}
	}
}

void Possible_move_king(chess_piece& k, const vector<point>& A)
{
	vector<point> B(6);
	B[0] = { A[k.posichion].x - 1, A[k.posichion].y };
	B[1] = { A[k.posichion].x + 1, A[k.posichion].y };
	B[2] = { A[k.posichion].x + 0.5, A[k.posichion].y + 1 };
	B[3] = { A[k.posichion].x - 0.5, A[k.posichion].y + 1 };
	B[4] = { A[k.posichion].x + 0.5, A[k.posichion].y - 1 };
	B[5] = { A[k.posichion].x - 0.5, A[k.posichion].y - 1 };

	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < B.size(); j++)
			if (A[i] == B[j])
				k.Possible_move.push_back(i);
}

void move_king(const vector<point>& A)
{
	int n;
	cout << "Где король?\n";
	cin >> n;
	chess_piece k;
	k.posichion = n;
	Possible_move_king(k, A);//первый ход короля
	vector<chess_piece> vk(k.Possible_move.size());
	for (int i = 0; i < vk.size(); i++)
	{
		chess_piece k2;
		k2.posichion = k.Possible_move[i];
		Possible_move_king(k2, A);
		vk[i] = k2;
	}
	draw_field(A, n);//перерисовка поля
	draw_cell(A[k.posichion], -1, 1, 0, 0);// прорисовка позиции короля

	for (int i = 0; i < vk.size(); i++)
		for (int j = 0; j < vk[i].Possible_move.size(); j++)//наложение выделения возможных ходов короля во 2 ход
			draw_cell(A[vk[i].Possible_move[j]], vk[i].Possible_move[j] == n ? -1 : vk[i].Possible_move[j], 1, 0, 0);

	int n2;
	cout << "Куда?\n";
	cin >> n2;
	if (n == n2)
	{
		draw_cell(A[n2], -1, 0, 0, 1);
	}
	else
	{
		point pos = A[n];
		vector<int> put = { n };
		while (pos - A[n2] != 0)
		{
			if (pos.y == A[n2].y)
			{
				if (pos.x < A[n2].x)
					pos.x++;
				else if (pos.x > A[n2].x)
					pos.x--;
			}
			else if (pos.y < A[n2].y)
			{
				pos.y++;
				if (pos.x == A[n2].x)
					pos.x += 0.5;
				else if (pos.x < A[n2].x)
					pos.x += 0.5;
				else if (pos.x > A[n2].x)
					pos.x -= 0.5;
			} if (pos.y > A[n2].y)
			{
				pos.y--;
				if (pos.x == A[n2].x)
					pos.x += 0.5;
				else if (pos.x < A[n2].x)
					pos.x += 0.5;
				else if (pos.x > A[n2].x)
					pos.x -= 0.5;
			}
			for (int i = 0; i < A.size(); i++)
				if (pos == A[i])
				{
					put.push_back(i);
					break;
				}
		}

		for (int i = 0; i < put.size(); i++)
		{
			draw_cell(A[put[i]], put[i] == n ? -1 : put[i], 0, 0, 1);
			cout << put[i] << " ";
		}
		cout << "\n";
	}
}

void Possible_move_horse(chess_piece& k, const vector<point>& A)
{
	vector<point> B(12);
	B[0] = { A[k.posichion].x + 0.5, A[k.posichion].y + 3 };
	B[1] = { A[k.posichion].x - 0.5, A[k.posichion].y + 3 };
	B[2] = { A[k.posichion].x + 2, A[k.posichion].y + 2 };
	B[3] = { A[k.posichion].x - 2, A[k.posichion].y + 2 };
	B[4] = { A[k.posichion].x + 2.5, A[k.posichion].y + 1 };
	B[5] = { A[k.posichion].x - 2.5, A[k.posichion].y + 1 };

	B[6] = { A[k.posichion].x + 0.5, A[k.posichion].y - 3 };
	B[7] = { A[k.posichion].x - 0.5, A[k.posichion].y - 3 };
	B[8] = { A[k.posichion].x + 2, A[k.posichion].y - 2 };
	B[9] = { A[k.posichion].x - 2, A[k.posichion].y - 2 };
	B[10] = { A[k.posichion].x + 2.5, A[k.posichion].y - 1 };
	B[11] = { A[k.posichion].x - 2.5, A[k.posichion].y - 1 };

	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < B.size(); j++)
			if (A[i] == B[j])
				k.Possible_move.push_back(i);
}

void move_horse(const vector<point>& A)
{
	int n;
	cout << "Где конь?\n";
	cin >> n;
	chess_piece k;
	k.posichion = n;
	Possible_move_horse(k, A);//первый ход коня
	vector<chess_piece> vk(k.Possible_move.size());
	for (int i = 0; i < vk.size(); i++)
	{
		vk[i].posichion = k.Possible_move[i];
		Possible_move_horse(vk[i], A);
	}

	draw_field(A, n);//перерисовка поля
	draw_cell(A[n], -1, 1, 0, 0);// прорисовка позиции коня

	for (int i = 0; i < vk.size(); i++)
		for (int j = 0; j < vk[i].Possible_move.size(); j++)//наложение выделения возможных ходов коня во 2 ход
			draw_cell(A[vk[i].Possible_move[j]], vk[i].Possible_move[j] == n ? -1 : vk[i].Possible_move[j], 1, 0, 0);

	// 2 часть задания
	int n2;
	cout << "Куда?\n";
	cin >> n2;
	if (n == n2)
	{
		draw_cell(A[n2], -1, 0, 0, 1);
	}
	else
	{
		vector<int> put;
		chess_piece pos = n;
		queue < pair<vector<int>, chess_piece>> poss;
		poss.push({ put,pos });
		vector<int> Mark(A.size(), 0);
		Mark[n] = 1;
		bool f = 1;

		while (f || poss.size() == 0)
		{
			pair<vector<int>, chess_piece> p = poss.front();
			poss.pop();
			put = p.first;
			pos = p.second;
			put.push_back(pos.posichion);

			Possible_move_horse(pos, A);

			for (int i = 0; i < pos.Possible_move.size(); i++)
			{
				if (Mark[pos.Possible_move[i]] == 0)
				{
					if (pos.Possible_move[i] == n2)
					{
						for (int j = 0; j < put.size(); j++)
						{
							draw_cell(A[put[j]], put[j] == n ? -1 : put[j], 0, 0, 1);
							cout << put[j] << " ";
						}
						draw_cell(A[n2], n2, 0, 0, 1);
						cout << n2 << " ";
						f = 0;
						break;
					}

					Mark[pos.Possible_move[i]] = 1;
					poss.push({ put, pos.Possible_move[i] });
				}
			}
		}
	}

}

void solve5()
{
	display();

	int n;
	cin >> n;
	vector<point> A(n * (n - 1) + n);
	field(A, n);
	draw_field(A, -1);
	move_king(A);
	bool f;
	cout << "Продолжить?\n";
	cin >> f;
	draw_field(A, -1);
	if (f)
		move_horse(A);
}

void task5(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Лабораторная работа 7. Задание 5. Вариант 1");
	init();
	glutDisplayFunc(solve5);
	glutMainLoop();
}