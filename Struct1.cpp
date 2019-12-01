// Struct1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include<iostream>
#include<Windows.h>
#include<conio.h>

using namespace std;

struct Zapis{
	char n,o;
	short p;
};

void BinOut(unsigned char* Buf, int len) {
	int i, j;
	unsigned char byte;
	for (i = len - 1; i >= 0; i--)
		for (j = 1, byte = Buf[i]; j <= 8; byte <<= 1, j++)
			_putch(byte & 0x80 ? '1' : '0');
	cout << endl;
}

void BinIn(unsigned char* Buf, int len) {
	int i, j;
	char ch;
	for (i = len - 1; i >= 0; i--)
		for (j = 1, Buf[i] = 0; j <= 8; Buf[i] = (Buf[i] << 1) + (ch - '0'), j++) {
			while ((ch = _getch()) != '0'&&ch != '1');
			_putch(ch);
		}
	cout << endl;
}

int main(int argc, char argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned char x;
	cout << "Введитечислотипа unsigned char: ";
	cin >> x;
	cout << "Двоичное представление введенного числа: " << endl;
	BinOut((unsigned char*)&x, sizeof(x));
	cout << "Введите двоичное представление числа типа unsigned char: " << endl;
	BinIn((unsigned char*)&x, sizeof(x));
	cout << "Это число: " << x << endl;
	_getch();


	double y;
	cout << "Введите число типа double: ";
	cin >> y;
	cout << "Двоичное представление введенного числа: " << endl;
	BinOut((unsigned char*)&y, sizeof(y));
	cout << "Введите двоичное представление числа типа double:" << endl;
	BinIn((unsigned char*)&y, sizeof(y));
	cout << "Это число: " << y << endl;
	_getch();


	Zapis z;
	cout << "Введите первое значение структуры типа char: ";
	cin >> z.n;
	cout << "Введите второе значение структуры типа char: ";
	cin >> z.o;
	cout << "Введите третье значение структуры типа short: ";
	cin >> z.p;
	cout << "Двоичное представление введенной структуры: " << endl;
	BinOut((unsigned char*)&z, sizeof(z));
	cout << "Введите двоичное представление структуры(short,char,char): " << endl;
	BinIn((unsigned char*)&z, sizeof(z));
	cout << "Эта структура: " << z.n << ends << z.o << ends << z.p << endl;
	_getch();


	cout << endl;
	system("pause");
	return 0;
}
