
#include "pch.h"
#include <iostream>
#include <ctime>

using namespace std;

//Сортировка вставками
template<class T>
void insertsort(T* a, long size) {
	for (int i = 1; i < size; i++) {
		T x = a[i];
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
void heapsort(T a[], long size)
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

	int SizeArray;
	cout << "Кол-во элементов: ";
	cin >> SizeArray;

	int *mas = new int[SizeArray];
	for (int i = 0; i < SizeArray; i++) {
		mas[i] = rand() % 300 - 100;
	}

	cout << "До сортировки: ";
	for (int i = 0; i < SizeArray; i++) {
		cout<<mas[i]<<ends;
	}

	//insertsort(mas, SizeArray);
	//selectionsort(mas, SizeArray);
	//bubblesort(mas, SizeArray);
	//shellsort(mas, SizeArray);
	//quicksort(mas, SizeArray);
	//heapsort(mas, SizeArray);

	cout << endl << "После сортировки: ";
	for (int i = 0; i < SizeArray; i++) {
		cout << mas[i] << ends;
	}

	system("pause");
	return 0;
}
