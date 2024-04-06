#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>
#include <fstream>
#include <Windows.h>
#include <queue>
#include "glut.h"

using namespace std;

int W = 50;
int H = 40;

double Scale = 20;

double width = Scale * W;
double height = Scale * H;

//int indent = Scale / 2;

struct point
{
	double x, y;

	point() = default;
	point(double x, double y) : x(x), y(y) {}
	point(int x, int y) : x(x), y(y) {}

	point& operator=(const point& B) {
		x = B.x;
		y = B.y;
		return *this;
	}

	point operator+(point B) const {
		point res;
		res.x = x + B.x;
		res.y = y + B.y;
		return res;
	}

	point operator-(point B) const {
		point res;
		res.x = x - B.x;
		res.y = y - B.y;
		return res;
	}

	point operator*(double k) const {
		point res;
		res.x = x * k;
		res.y = y * k;
		return res;
	}

	point operator/(double k) const {
		point res;
		res.x = x / k;
		res.y = y / k;
		return res;
	}

	void rand_point(int w = width, int h = height, int precision = 1) {
		x = ((rand() * rand() % (w * 2 * precision)) - w * precision) * 1.0 / precision;
		y = ((rand() * rand() % (h * 2 * precision)) - h * precision) * 1.0 / precision;
	}

	void rand_point2(double w1, double w2, double h1 = -height, double h2 = height, int precision = 10000) {
		if (w2 == w1)
			x = w1;
		else
			x = ((rand() * rand() % (int)round((w2 - w1) * precision)) + w1 * precision) / precision;
		if (h2 == h1)
			y = h1;
		else
			y = ((rand() * rand() % (int)round((h2 - h1) * precision)) + h1 * precision) / precision;
	}

	void line(const point& B, double& a, double& b, double& c) const {
		a = B.y - y, b = x - B.x, c = (-a) * x + (-b) * y;
	}

	double line(const point& B, const point& C) const {
		double a = B.y - y, b = x - B.x, c = (-a) * x + (-b) * y;
		return a * C.x + b * C.y + c;
	}

	double dist2() const {
		return x * x + y * y;
	}

	double dot(const point& B) const {
		return x * B.x + y * B.y;
	}

	double cross(const point& B) const {
		return x * B.y - y * B.x;
	}

	bool operator==(const point& B) const {
		return x == B.x && y == B.y;
	}

	bool operator!=(const point& B) const {
		return !(*this == B);
	}

	bool operator==(const int& B) const {
		return x == B && y == B;
	}

	bool operator!=(const int& B) const {
		return !(*this == B);
	}

	friend std::istream& operator>>(std::istream& in, point& p) {
		in >> p.x >> p.y;
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, const point& p) {
		out << p.x << " " << p.y;
		return out;
	}
};

void rand_RGB(double& R, double& G, double& B)
{
	R = ((rand() % 20) - 6) / 10.0;
	G = ((rand() % 20) - 4) / 10.0;
	B = ((rand() % 20) - 3) / 10.0;
}

void OXY()
{
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);

	glVertex2i(0, -height);
	glVertex2i(0, height);
	glVertex2i(-width, 0);
	glVertex2i(width, 0);

	glEnd();
	glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//OXY();
	//glutSwapBuffers();
	glFlush();
}

void mouse(int button, int state, int x, int y) {
	// Действие при нажатии левой кнопки мыши
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "On left mouse button click action\n";
	}
	// Действие при нажатии правой кнопки мыши
	else if (button == GLUT_RIGHT_BUTTON && state ==
		GLUT_DOWN) {
		std::cout << "On right mouse button click action\n";
	}
}
void keyboard_cop(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		// Действие при нажатии клавиши ESC
		exit(0);
		break;
	case 'a':
		// Действие при нажатии клавиши ’a’ на английской раскладке
		std::cout << "Action on pressing the 'a' key\n";
		break;
	case 'b':
		// Действие при нажатии клавиши ’b’ на английской раскладке
		std::cout << "Action on pressing the 'b' key\n";
		break;
	}
}

void timer(int = 0)
{
	display();
	glutTimerFunc(100, timer, 0);
}

void draw_point(const vector<point>& A, double R = 0, double G = 0.5, double B = 0, double size = 5.0)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(R, G, B);
	for (int i = 0; i < A.size(); i++)
	{
		glVertex2i(A[i].x * Scale, A[i].y * Scale);
	}
	glEnd();
	glFlush();
}

void draw_point(const point& A, double R = 0, double G = 0.5, double B = 0, double size = 5.0)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(R, G, B);
	glVertex2i(A.x * Scale, A.y * Scale);
	glEnd();
	glFlush();
}

void draw_line(vector<point>& C, double R = 0, double G = 0.5, double B = 0)
{
	glBegin(GL_LINES);
	glColor3f(R, G, B);
	for (int i = 0; i < C.size(); i++)
	{
		glVertex2i(C[i].x * Scale, C[i].y * Scale);
		glVertex2i(C[(i + 1) % C.size()].x * Scale, C[(i + 1) % C.size()].y * Scale);
	}
	glEnd();
	glFlush();
}

void resize(vector<point> A)
{
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i].x * Scale + Scale > width)
			width = A[i].x * Scale + Scale;

		if (A[i].y * Scale + Scale > height)
			height = A[i].y * Scale + Scale;
	}
}
