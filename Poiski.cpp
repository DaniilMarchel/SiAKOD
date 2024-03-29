// Poiski.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <ctime>

using namespace std;

unsigned long CmpCount; // Счетчик сравнений

// Функция обнуления счетчика
void ClearCoutn() {
	CmpCount = 0;
}

// Функция, возвращающая количество сделанных сравнений
unsigned long GetCmpCount() {
	return CmpCount;
}


// BaseType - тип элемента массива подверженного сортировке
// по полю Key
struct BaseType {
	int key;    // Ключевое поле

	// Переопределение оператора сравнения на меньше
	bool operator < (const BaseType&Var) const {
		CmpCount++;
		return(key < Var.key);
	}
	// Переопределение оператора сравнения на меньше или равно
	bool operator <= (const BaseType&Var) const {
		CmpCount++;
		return(key <= Var.key);
	}
	// Переопределение оператора сравнения на больше
	bool operator > (const BaseType&Var) const {
		CmpCount++;
		return(key > Var.key);
	}
	// Переопределение оператора сравнения на больше или равно
	bool operator >= (const BaseType&Var) const {
		CmpCount++;
		return(key >= Var.key);
	}
	// Переопределение оператора сравнения равенство
	bool operator == (const BaseType&Var) const {
		CmpCount++;
		return(key == Var.key);
	}
	// Переопределение оператора сравнения на неравенство
	bool operator != (const BaseType&Var) const {
		CmpCount++;
		return(key != Var.key);
	}
};

int SizeArray = 50;
int const N = 50;

int mas[N];

// Функция формирования массива случайным образом
void RandArray(BaseType* a, long n) {
	srand(time(0));
	for (long i = 0; i < n; i++) {
		a[i].key = rand() % 1000;
		mas[i] = a[i].key;
	}
}

// Функция формирования массива упорядоченного по возрастанию
void SortArray(BaseType* a, long n) {
	for (long i = 0; i < n; i++) {
		a[i].key = i;
	}
}


int poisk1(BaseType *a, long first , long size, BaseType el) {

	int i = first;
	while (i < size && a[i] != el) {
		i++;
		CmpCount++;
	}
	if (i != size) { return i; }
	else { return -1; }
}


int poisk1b(BaseType *a, long first, long size, BaseType el) {
	BaseType temp;
	
		temp = a[size-1];
		a[size-1] = el;
		int i = first;
			while (el != a[i]) {
				i++;
			}
			a[size-1] = temp;
			CmpCount++;
			if (i == size-1) { return -1;}
			else { return i; }
	
}


int poisk2a(BaseType* a, long first, long size, BaseType el) {
	BaseType temp;
	int x = el.key;
	temp = a[size - 1];
	a[size - 1] = el;
	int i = first;
	while (el != a[i]) {
		if (a[i].key > x) { return -1; }
		i++;
	}
	a[size - 1] = temp;
	CmpCount++;
	if (i == size) { return -1; }
	else { return i; }


}


int poisk2b(BaseType* a, long first, long size, BaseType el) {
	int i = first;
	int j;
	while (i < size) {
		j = i + ((size - i) / 2);
			if (a[j] >= el) { size = j; }
			else { i = j + 1; }
	}
		
	if (a[i] == el) {return i;}
	else { return -1; }
}


int poisk2c(BaseType* a, long first, long size, BaseType el) {
	int p;
	bool F = 1;
	int h = sqrt(size-first);
	int i = first+h;
	while (F && i < size) {
		if (el <= a[i - 1]) {
			F = 0;
			p = poisk1(a,i-h,i, el);
		}
		i=i+h;
	}

	if (F) {
		if (el <= a[size-1]) {
			p = poisk1(a,i-h,size, el);

		}
		else { p = -1; }
	}
	return p;
}


int main(int argc, char argv[])
{
	setlocale(LC_ALL, "Russian");
	BaseType iskelem;
	double SumCount = 0;

	int mas1[N];
	for (int i = 0; i < N; i++) {
		mas1[i] = i;
	}
	
	// Массив указателей на случайные массивы
	BaseType* ProbArray[N];
	// Цикл по разной размерности для формирования массивов случайным образом
	for (int i = 0; i < N; i++) {
		ProbArray[i] = new BaseType[SizeArray];
		RandArray(ProbArray[i], SizeArray);
	}
	BaseType* a; // Указатель на сортируемый массив


	cout << "ЛИНЕЙНЫЙ ПОИСК:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++) {
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		iskelem.key = mas[i];
		cout << iskelem.key;

		cout << endl << "Кол-во элементов в массиве: " << SizeArray<<endl;
		ClearCoutn();
		cout<<poisk1(a, 0, SizeArray, iskelem);

		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();

		delete a;
	}
	cout << "Средний cлучай(ЛИНЕЙНЫЙ ПОИСК) " << SumCount / N << endl;
	system("pause");
	cout << "--------------------------------------------------" << endl;
	SumCount = 0;



	cout << "ЛИНЕЙНЫЙ ПОИСК улучшенный:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++) {
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		iskelem.key = mas[i];
		cout << iskelem.key;

		cout << endl << "Кол-во элементов в массиве: " << SizeArray<<endl;
		ClearCoutn();
		cout << poisk1b(a, 0, SizeArray, iskelem);

		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();

		delete a;
	}
	cout << "Средний cлучай(ЛИНЕЙНЫЙ ПОИСК улучшенный) " << SumCount / N << endl;
	system("pause");
	cout << "--------------------------------------------------" << endl;
	SumCount = 0;
	

	for (int i = 0; i < N; i++) {
		ProbArray[i] = new BaseType[SizeArray];
		SortArray(ProbArray[i], SizeArray);
	}



	cout << "ЛИНЕЙНЫЙ ПОИСК на упорядоченном массиве:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++) {
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl<<"Искомый элемент: ";
		iskelem.key = mas1[i];
		cout << iskelem.key;

		cout << endl << "Кол-во элементов в массиве: " << SizeArray <<endl;
		ClearCoutn();
		cout << poisk2a(a, 0, SizeArray, iskelem);

		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();

		delete a;
	}
	cout << "Средний cлучай(ЛИНЕЙНЫЙ ПОИСК на упорядоченном массиве) " << SumCount/N << endl;
	system("pause");
	cout << "--------------------------------------------------" << endl;
	SumCount = 0;




		cout << "БИНАРНЫЙ ПОИСК:" << endl;
		// Цикл по разной размерности массива
		for (int i = 0; i < N; i++) {
			a = new BaseType[SizeArray];
			//(случайный массив)
			for (int j = 0; j < SizeArray; j++) {
				a[j] = ProbArray[i][j];
			}

			cout <<endl<< "Искомый элемент: ";
			iskelem.key = mas1[i];
			cout<< iskelem.key;

			cout << endl << "Кол-во элементов в массиве: " << SizeArray <<endl;
			ClearCoutn();
			cout << poisk2b(a, 0, SizeArray -1, iskelem);

			cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
			SumCount = SumCount + GetCmpCount();
			delete a;

		}
		cout << "Средний случай(БИНАРНЫЙ ПОИСК) " << SumCount/N << endl;
		system("pause");
		cout << "--------------------------------------------------" << endl;
		SumCount = 0;



		cout << "БЛОЧНЫЙ ПОИСК:" << endl;
		// Цикл по разной размерности массива
		for (int i = 0; i < N; i++) {
			a = new BaseType[SizeArray];
			//(случайный массив)
			for (int j = 0; j < SizeArray; j++) {
				a[j] = ProbArray[i][j];
			}

			cout <<endl<< "Искомый элемент: ";
			iskelem.key=mas1[i];
			cout << iskelem.key;

			cout << endl << "Кол-во элементов в массиве: " << SizeArray <<endl;
			ClearCoutn();
			cout << poisk2c(a, 0, SizeArray, iskelem);

			cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
			SumCount = SumCount + GetCmpCount();

			delete a;
		}
		cout << "Средний случай(БЛОЧНЫЙ ПОИСК) " << SumCount /N << endl;

	
	system("pause");
	return 0;
}

