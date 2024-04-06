#include <iostream>
#include "Head.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");
	int n = 5;
	//cin >> n;
	switch (n)
	{
	case 0:
		break;
	case 1:
		task1(argc, argv);
		break;
	case 2:
		task2(argc, argv);
		break;
	case 3:
		task3(argc, argv);
		break;
	case 4:
		task4(argc, argv);
		break;
	case 5:
		task5(argc, argv);
		break;
	default:
		break;
	}
}
