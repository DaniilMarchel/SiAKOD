

#include "pch.h"
#include <iostream>
#include <ctime>

using namespace std;

unsigned long CmpCount; // Счетчик сравнений
unsigned long MovCount; // Счетчик пересылок (присваиваний)

// Функция обнуления счетчиков
void ClearCoutn() {
	CmpCount = 0;
	MovCount = 0;
}
// Функция, возвращающая количество сделанных сравнений
unsigned long GetCmpCount() {
	return CmpCount;
}
// Функция возвращающая количество сделанных пересылок
unsigned long GetMovCount() {
	return MovCount;
}
// Функция возвращающая суммарное количество
// сделанных сравнений и пересылок
unsigned long GetAllCount() {
	return CmpCount + MovCount;
}
//------------------------------------------------------------

// BaseType - тип элемента массива подверженного сортировке
// по полю Key
struct BaseType {
	int key;    // Ключевое поле
				// Преопределение оператора присваивания
	BaseType&operator=(const BaseType&Var) {
		key = Var.key;
		MovCount++;
		return *this;
	}
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

// Функция формирования массива случайным образом
void RandArray(BaseType* a, long n) {
	srand(time(0));
	for (long i = 0; i < n; i++) {
		a[i].key = rand() % 200;
	}
}

// Функция формирования массива упорядоченного по возрастанию
void SortArray(BaseType* a, long n) {
	for (long i = 0; i < n; i++) {
		a[i].key = i;
	}
}

// Функция формирования массива упорядоченного по убыванию
void UnSortArray(BaseType* a, long n) {
	for (long i = 0; i < n; i++) {
		a[i].key = n - i;
	}
}


//Сортировка вставками
template<class T>
void insertsort(T* a, long size) {
	for (int i = 1; i < size; i++) {
		BaseType x = a[i];
		int j = i - 1;
		while (x < a[j] && j >= 0) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
}



//Сортировка выбором
template<class T>
void selectionsort(T* a, long size) {
	int k;
	for (int i = 0; i < size; i++) {
		T min = a[i];
		for (int j = i + 1; j < size; j++) {
			if (min > a[j]) {
				min = a[j];
				k = j;
			}
		}
		if (a[i] != min) {
			a[k] = a[i];
		}
		a[i] = min;
	}
}



//СортировкаПузырьком
template<class T>
void bubblesort(T* a, long size) {
	T temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j > i; j--) {
			if (a[j - 1] > a[j]) {
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
	}
}



//Сортировка Шелла
template<class T>
void shellsort(T* a, long size) {
	T temp;
	int step, j;
	step = size / 2;
	while (step > 0) {
		for (int i = 0; i < size - step; i++) {
			j = i;
			while (j >= 0 && a[j] > a[j + step]) {
				temp = a[j];
				a[j] = a[j + step];
				a[j + step] = temp;
				j--;
			}
		}
		step = step / 2;
	}
}



//Быстрая сортировка
template<class T>
void quicksort(T* a, long size) {
	// На входе - массив a[], a[N] - его последний элемент.

	long i = 0, j = size;      // поставить указатели на исходные места
	T temp, p;

	p = a[size / 2];      // центральный элемент
						// процедура разделения
	do {
		while (a[i] < p) i++;
		while (a[j] > p) j--;

		if (i <= j) {
			temp = a[i]; a[i] = a[j]; a[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	// рекурсивные вызовы, если есть, что сортировать
	if (j > 0) quicksort(a, j);
	if (size > i) quicksort(a + i, size - i);
}



//Пирамидальная сортировка
template<class T>
void downHeap(T a[], long k, long g)
{
	//  процедура просеивания следующего элемента 
	//  До процедуры: a[k+1]...a[n]  - пирамида 
	//  После:  a[k]...a[n]  - пирамида 
	T new_elem;
	long child;
	new_elem = a[k];

	while (k <= g / 2) // пока у a[k] есть дети 
	{
		child = 2 * k;

		if (child < g&&a[child] < a[child + 1]) //  выбираем большего сына 
			child++;
		if (new_elem >= a[child])
			break;
		// иначе 
		a[k] = a[child];  // переносим сына наверх 
		k = child;
	}
	a[k] = new_elem;
}
template<class T>
void heapSort(T a[], long size)
{
	long i;
	T temp;
	// строим пирамиду 
	for (i = size / 2 - 1; i >= 0; --i)
		downHeap(a, i, size - 1);

	for (i = size - 1; i > 0; --i)
	{
		// меняем первый с последним 
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		// восстанавливаем пирамидальность
		downHeap(a, 0, i - 1);
	}
}


int main(int argc, char argv[])
{
	setlocale(LC_ALL, "Russian");

	// Количество элементов в массиве
	int SizeArray[9] = { 5,10,15,20,25,30,35,40,45 };
	// Массив указателей на случайные массивы
	BaseType* ProbArray[9];
	// Цикл по разной размерности 
	// для формирования массивов случайным образом
	for (int i = 0; i < 9; i++) {
		ProbArray[i] = new BaseType[SizeArray[i]];
		RandArray(ProbArray[i], SizeArray[i]);
	}
	BaseType* a; // Указатель на сортируемый массив

	cout << "СОРТИРОВКА ВСТАВКАМИ:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < 9; i++) {
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Кол-во элементов в массиве: " << SizeArray[i];
		cout << endl << "Средний случай:" << endl;
		ClearCoutn();
		insertsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		insertsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование худшего случая
		// (массив упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i] - 1);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		insertsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		delete a;
	}

	system("pause");
	cout << endl << "СОРТИРОВКА ВЫБОРОМ:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < 9; i++) {
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Кол-во элементов в массиве: " << SizeArray[i];
		cout << endl << "Средний случай:" << endl;
		ClearCoutn();
		selectionsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		selectionsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование худшего случая
		// (массив упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i] - 1);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		selectionsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		delete a;
	}

	system("pause");
	cout << endl << "СОРТИРОВКА ПУЗЫРЬКОМ" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < 9; i++) {
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Кол-во элементов в массиве: " << SizeArray[i];
		cout << endl << "Средний случай:" << endl;
		ClearCoutn();
		bubblesort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		bubblesort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование худшего случая
		// (массив упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i] - 1);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		bubblesort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		delete a;
	}

	system("pause");
	cout << endl << "СОРТИРОВКА ШЕЛЛА:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < 9; i++) {
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Кол-во элементов в массиве: " << SizeArray[i];
		cout << endl << "Средний случай:" << endl;
		ClearCoutn();
		shellsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		shellsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование худшего случая
		// (массив упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i] - 1);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		shellsort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		delete a;
	}

	system("pause");
	cout << endl << "СОРТИРОВКА ХОАРА:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < 9; i++) {
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Кол-во элементов в массиве: " << SizeArray[i];
		cout << endl << "Средний случай:" << endl;
		ClearCoutn();
		quicksort(a, SizeArray[i] - 1);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		quicksort(a, SizeArray[i] - 1);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование худшего случая
		// (массив упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i] - 1);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		quicksort(a, SizeArray[i] - 1);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		delete a;
	}

	system("pause");
	cout << endl << "СОРТИРОВКА ПИРАМИДАЛЬНАЯ:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < 9; i++) {
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) {
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Кол-во элементов в массиве: " << SizeArray[i];
		cout << endl << "Средний случай:" << endl;
		ClearCoutn();
		heapSort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		heapSort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		// Исследование худшего случая
		// (массив упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i] - 1);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		heapSort(a, SizeArray[i]);
		cout << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		cout << "Кол-во операций обменов: " << GetMovCount() << endl;
		cout << "Кол-во операций: " << GetAllCount() << endl;

		delete a;
	}

	cout << endl;
	system("pause");
	return 0;
}
