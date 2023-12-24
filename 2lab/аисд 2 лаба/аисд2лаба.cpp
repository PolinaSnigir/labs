#include <iostream>
#include <cmath>

using namespace std;

template <class T>
class DynamicArray {
private:
    T* arr;
    int size;
    int capacity;

public:
    DynamicArray() {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }
    void add(T value) {
        if (size == capacity) {
            T* temp = new T[capacity * 2];
            for (int i = 0; i < size; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            capacity *= 2;
        }
        arr[size] = value;
        size++;
    }

    T get(int index) {

        if (index >= 0 && index < size) {
            return arr[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    void resize(int newSize) {
        T* tempArr = new T[newSize];
        int copySize = newSize < size ? newSize : size;
        for (int i = 0; i < copySize; i++) {
            tempArr[i] = arr[i];
        }
        delete[] arr;
        arr = tempArr;
        capacity = newSize;
        size = copySize;
    }


};

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    DynamicArray<int> leftArr;
    DynamicArray<int> rightArr;
    leftArr.resize(n1);
    rightArr.resize(n2);

    for (int i = 0; i < n1; i++) {
        leftArr.add(arr[left + i]);
    }

    for (int i = 0; i < n2; i++) {
        rightArr.add(arr[mid + 1 + i]);
    }

    int i = 0, j = 0, k = left;


    while (i < n1 && j < n2) {
        int gallopLeft = 0;
        while (j < n2 && leftArr.get(i) > rightArr.get(j)) {
            arr[k] = rightArr.get(j);
            j++;
            k++;
            gallopLeft++;
        }


        for (int gallopIndex = 0; gallopIndex < gallopLeft; gallopIndex++) {
            leftArr.add(arr[left + i + gallopIndex]);
        }
        i += gallopLeft;


        while (i < n1 && j < n2) {
            if (leftArr.get(i) <= rightArr.get(j)) {
                arr[k] = leftArr.get(i);
                i++;
            }
            else {
                arr[k] = rightArr.get(j);
                j++;
            }
            k++;
        }
    }

    while (i < n1) {
        arr[k] = leftArr.get(i);
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr.get(j);
        j++;
        k++;
    }
}

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int calculateMinrun(int size) {
    int minrun = 32;

    while (size >= minrun) {
        minrun |= size & 1;
        size >>= 1;
    }

    return minrun;
}

void timSort(int arr[], int size) {

    int minrun = calculateMinrun(size);
    for (int i = 0; i < size; i += minrun) {
        insertionSort(arr, i, min(i + minrun - 1, size - 1));
    }

    for (int sizeMerge = minrun; sizeMerge < size; sizeMerge *= 2) {
        for (int left = 0; left < size; left += 2 * sizeMerge) {
            int mid = left + sizeMerge - 1;
            int right = min((left + 2 * sizeMerge - 1), (size - 1));

            if (mid < right) {
                if (arr[mid] <= arr[mid + 1]) {
                    continue;
                }

                merge(arr, left, mid, right);
            }

        }
    }


}


int main() {
    setlocale(LC_ALL, "Russian");
    int arr[128];
    srand(time(0));
    for (int i = 0; i < 128; i++)
        arr[i] = 1 + rand() % 100;

    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    timSort(arr, size);

    cout << "Отсортированный массив:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}