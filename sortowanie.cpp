#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define zakres 20

void print(int* arr, int n) {  //wyœwietla dane
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}
void init(int* arr, int n) {  //generuje losowe dane
	for (int i = 0; i < n; i++)
		arr[i] = rand() % zakres;
}
//---//
void selectionSort(int* arr, int n) { // Sortowanie przez wybieranie
	int min;
	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) min = j;
		}
		swap(arr[i], arr[min]);
	}
}
void bubbleSort(int* arr, int n) { // Sortowanie przez zamianê

	for (int i = 1; i <= n - 1; i++) {
		for (int j = n - 1; j >= i; j--) {
			if (arr[j] < arr[j - 1])
				swap(arr[j], arr[j - 1]);
		}
	}
}
void insertionSort(int* arr, int n) { // Sortowanie przez wstawianie
	int aux;
	int j;

	for (int i = 1; i < n; i++) {
		aux = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > aux) arr[j + 1] = arr[j];
			else break;
		}
		arr[j + 1] = aux;
	}
}
void quickSort(int* S, int left, int right) {
	int pivot = S[(left + right) / 2];
	int i = left - 1;
	int j = right + 1;

	if (right <= left) return;
	while (true) {
		while (pivot > S[++i]);
		while (pivot < S[--j]);
		if (i <= j) swap(S[i], S[j]);
		else break;
	}
	if (j > left) quickSort(S, left, j);
	if (i < right) quickSort(S, i, right);
}
//---//
void merge(int* items, int left, int mid, int right) {
	int* aux = new int[(right - left)];
	int i = left, j = mid + 1, k = 0;

	while (i <= mid && j <= right) {
		if (items[j] < items[i]) {
			aux[k] = items[j];
			j++;
		}
		else {
			aux[k] = items[i];
			i++;
		}
		k++;
	}
	if (i <= mid) {
		while (i <= mid) {
			aux[k] = items[i];
			i++;
			k++;
		}
	}
	else {
		while (j <= right) {
			aux[k] = items[j];
			j++;
			k++;
		}
	}

	for (i = 0; i <= right - left; i++)
		items[left + i] = aux[i];
}
void mergeSort(int* items, int left, int right) { // Sortowanie przez scalanie
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(items, left, mid);
		mergeSort(items, mid + 1, right);
		merge(items, left, mid, right);
	}
}
//---//
void heapify(int* arr, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (arr[left] > arr[largest] && left < n)
		largest = left;

	if (arr[right] > arr[largest] && right < n)
		largest = right;

	if (largest != i) { //czyli wystepuje zamiana
		std::swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
void heapSort(int* arr, int n) { // Sortowanie przez kopcowanie

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i); //budujemy kopiec typu max

	for (int i = n - 1; i >= 0; i--) {
		std::swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
//---//
int highestValue(int* arr, int n) { // funckja do countingSort
	int highest = arr[0];

	for (int i = 1; i < n; i++) {
		if (arr[i] > highest) // dla min w drug¹ strone (<)
			highest = arr[i];
	}
	return highest;
}
void countingSort(int* items, int n) { // Sortowanie przez zliczanie
	int highest = highestValue(items, n);
	int* countings = new int[highest + 1]{ 0 }; //ile danej wartoœci
	int* aux = new int[n] {}; //tablica wyjœciowa

	for (int i = 0; i < n; i++)
		countings[items[i]] += 1;

	for (int j = 1; j <= highest; j++)
		countings[j] += countings[j - 1];

	for (int i = n - 1; i >= 0; i--) {
		aux[countings[items[i]] - 1] = items[i];
		countings[items[i]] -= 1;
	}
	for (int i = 0; i < n; i++)
		items[i] = aux[i];
}
//---//
void bucketSort(int* arr, int n) {
	std::queue<int> b[zakres];
	//std::queue<int> b[10]; //dla radixSorta
	int index = 0, index2 = 0;

	for (int i = 0; i < n; i++) {
		//index = n * arr[i]; // oblicza indeks kube³ka
		index = arr[i];
		b[index].push(arr[i]);
	}
	//for (int i = 0; i < n; i++)
		//std::sort(b[i].front(), b[i].back());
	index = 0;
	for (int i = 0; i < zakres; i++) {
		while (!b[index].empty()) {
			arr[index2] = b[index].front();
			b[index].pop();
			index2++;
		}
		index++;
	}
}
//---//
void radixBucketSort(int* arr, int n, int div) {
	int* output = new int[n];
	int count[10]{};

	for (int i = 0; i < n; i++)
		count[(arr[i] / div) % 10]++;

	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / div) % 10] - 1] = arr[i];
		count[(arr[i] / div) % 10]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = output[i];
}
void radixSort(int* arr, int n) {
	int max = highestValue(arr, n);

	for (int exp = 1; max / exp > 0; exp *= 10)
		radixBucketSort(arr, n, exp);
}
int main() {
	int n = 14;
	int* items = new int[n];

	init(items, n);
	print(items, n);
	//insertionSort(items, n);
	//selectionSort(items, n);
	//bubbleSort(items, n);
	//quickSort(items, 0, n-1);
	//mergeSort(items, 0, n -1);
	//heapSort(items, n);
	//countingSort(items, n);
	//bucketSort(items, n);
	//radixSort(items, n);
	print(items, n);

}
