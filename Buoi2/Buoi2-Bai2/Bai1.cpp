#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

// Bai 1_a
void TaoMangMotChieuLonHonBang15(int a[]) {
    for(int i = 15; i < MAX; i++) {
        a[i] = rand() % (MAX + 1);
    }
}

void XuatMang1a(int a[]) {
    printf("Mang duoc tao:\n");
    for(int i = 15; i < MAX; i++) {
        printf("Phan tu thu %d: %d\n", i, a[i]);
    }
}

// Bai 1_b
void TaoMangToanSoChan(int b[]) {
    int so;
    for(int i = 0; i < MAX; i++) {
        do {
            so = rand() % (MAX + 1);
        } while (so % 2 != 0 || so == 0);
        b[i] = so;
    }
}

void XuatMang1b(int b[]) {
    printf("Mang duoc tao:\n");
    for(int i = 0; i < MAX; i++) {
        printf("Phan tu thu %d: %d\n", i, b[i]);
    }
}

// Cau 1_c
int LinearSearch(int a[], int x) {
    for (int i = 0; i < MAX; ++i) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}

// Cau 1_d
void InterchangeSort(int a[], int giatang) {
    for (int i = 0; i < MAX - 1; ++i) {
        for (int j = i + 1; j < MAX; ++j) {
            if ((giatang && a[i] > a[j]) || (!giatang && a[i] < a[j])) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

// Cau 1_e
int BinarySearch(int a[], int x) {
    int left = 0, right = MAX - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x) {
            return mid;
        }
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Cau 1_f
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SelectionSort(int a[]) {
    for (int i = 0; i < MAX - 1; ++i) {
        int sonhonhat = i;
        for (int j = i + 1; j < MAX; ++j) {
            if (a[j] < a[sonhonhat]) {
                sonhonhat = j;
            }
        }
        swap(&a[i], &a[sonhonhat]);
    }
}

// Cau 1_g
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (a[j] < pivot) {
            ++i;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);
    return i + 1;
}

void QuickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        QuickSort(a, low, pi - 1);
        QuickSort(a, pi + 1, high);
    }
}

int main() {
    srand(time(0));
    int a[MAX] = {0};
    int b[MAX] = {0};
    
    printf("Cau 1a:\n");
    TaoMangMotChieuLonHonBang15(a);
    XuatMang1a(a);
    
    printf("Cau 1b\n");
    TaoMangToanSoChan(b);
    XuatMang1b(b);
    
    int x;
    printf("Nhap gia tri can tim: ");
    scanf("%d", &x);
    
    int index = LinearSearch(a, x);
    if (index != -1) {
        printf("Tim thay %d tai vi tri %d bang Linear Search\n", x, index);
    } else {
        printf("%d khong tim thay bang Linear Search\n", x);
    }
    
    InterchangeSort(a, 1);
    printf("Mang sau khi sap xep tang dan: ");
    for (int i = 0; i < MAX; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    InterchangeSort(a, 0);
    printf("Mang sau khi sap xep giam dan: ");
    for (int i = 0; i < MAX; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    index = BinarySearch(a, x);
    if (index != -1) {
        printf("Tim thay %d tai vi tri %d bang Binary Search\n", x, index);
    } else {
        printf("%d khong tim thay bang Binary Search\n", x);
    }
    
    SelectionSort(a);
    printf("Mang sau khi sap xep tang dan bang Selection Sort: ");
    for (int i = 0; i < MAX; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    QuickSort(a, 0, MAX - 1);
    printf("Mang sau khi sap xep tang dan bang Quick Sort: ");
    for (int i = 0; i < MAX; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

