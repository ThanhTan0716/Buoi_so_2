#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX 50

void NhapMang(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i);
        scanf("%d", &a[i]);
    }
}

void XuatMang(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}


void LietKeNguyenTo(int a[], int size, int n) {
    bool found = false;
    printf("Cac so nguyen to nho hon %d: ", n);
    for (int i = 0; i < size; i++) {
        if (isPrime(a[i]) && a[i] < n) {
            printf("%d ", a[i]);
            found = true;
        }
    }
    if (!found) {
        printf("Khong co so nguyen to nao nho hon %d\n", n);
    } else {
        printf("\n");
    }
}


bool ChuSoDauLe(int num) {
    while (num >= 10) {
        num /= 10;
    }
    return num % 2 != 0;
}

int TongChuSoDauLe(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (ChuSoDauLe(a[i])) {
            sum += a[i];
        }
    }
    return sum;
}


void LietKeSoLanXuatHien(int a[], int n) {
    int count[MAX] = {0};
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (count[a[i]] != 0) {
            printf("Phan tu %d xuat hien %d lan\n", a[i], count[a[i]]);
            count[a[i]] = 0; 
        }
    }
}


void SapXepChanLe(int a[], int n) {
    int chan[MAX], le[MAX];
    int chanCount = 0, leCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            chan[chanCount++] = a[i];
        } else {
            le[leCount++] = a[i];
        }
    }


    for (int i = 0; i < chanCount - 1; i++) {
        for (int j = i + 1; j < chanCount; j++) {
            if (chan[i] > chan[j]) {
                int temp = chan[i];
                chan[i] = chan[j];
                chan[j] = temp;
            }
        }
    }


    for (int i = 0; i < leCount - 1; i++) {
        for (int j = i + 1; j < leCount; j++) {
            if (le[i] < le[j]) {
                int temp = le[i];
                le[i] = le[j];
                le[j] = temp;
            }
        }
    }


    int index = 0;
    for (int i = 0; i < chanCount; i++) {
        a[index++] = chan[i];
    }
    for (int i = 0; i < leCount; i++) {
        a[index++] = le[i];
    }
}


void TimDayConGiamDaiNhat(int a[], int n) {
    int maxLength = 1, length = 1, endIndex = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            length++;
            if (length > maxLength) {
                maxLength = length;
                endIndex = i;
            }
        } else {
            length = 1;
        }
    }

    printf("Day con giam dai nhat: ");
    for (int i = endIndex - maxLength + 1; i <= endIndex; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int TimSoNhoThuHai(int a[], int n) {
    int min1 = INT_MAX, min2 = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (a[i] < min1) {
            min2 = min1;
            min1 = a[i];
        } else if (a[i] < min2 && a[i] != min1) {
            min2 = a[i];
        }
    }
    return min2;
}


bool ChuaChuSo(int num, int x) {
    char strNum[12], strX[3];
    sprintf(strNum, "%d", num);
    sprintf(strX, "%d", x);
    return (strstr(strNum, strX) != NULL);
}

void TimPhanTuChuaChuSoX(int a[], int n, int x) {
    printf("Cac phan tu chua cac chu so cua %d: ", x);
    for (int i = 0; i < n; i++) {
        if (ChuaChuSo(a[i], x)) {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
}


void SapXepChanTangLeNguyen(int a[], int n) {
    int chan[MAX], chanCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            chan[chanCount++] = a[i];
        }
    }


    for (int i = 0; i < chanCount - 1; i++) {
        for (int j = i + 1; j < chanCount; j++) {
            if (chan[i] > chan[j]) {
                int temp = chan[i];
                chan[i] = chan[j];
                chan[j] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            a[i] = chan[index++];
        }
    }
}


void SapXepLeChan(int a[], int n) {
    int le[MAX], chan[MAX];
    int leCount = 0, chanCount = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            chan[chanCount++] = a[i];
        } else {
            le[leCount++] = a[i];
        }
    }

    int index = 0;
    for (int i = 0; i < leCount; i++) {
        a[index++] = le[i];
    }
    for (int i = 0; i < chanCount; i++) {
        a[index++] = chan[i];
    }
}

int main() {
    int a[MAX], n, x;

    printf("Nhap so phan tu cua mang: ");
    scanf("%d", &n);

    NhapMang(a, n);

    printf("Mang da nhap: ");
    XuatMang(a, n);


    printf("Nhap n de liet ke cac so nguyen to nho hon: ");
    scanf("%d", &x);
    LietKeNguyenTo(a, n, x);


    printf("Tong cac phan tu co chu so dau la chu so le: %d\n", TongChuSoDauLe(a, n));


    LietKeSoLanXuatHien(a, n);


    SapXepChanLe(a, n);
    printf("Mang sau khi sap xep chan tang le giam: ");
    XuatMang(a, n);


    TimDayConGiamDaiNhat(a, n);


    printf("So nho thu 2 trong mang: %d\n", TimSoNhoThuHai(a, n));


    printf("Nhap x (so co 2 chu so) de tim cac phan tu chua cac chu so cua x: ");
    scanf("%d", &x);
    TimPhanTuChuaChuSoX(a, n, x);


    SapXepChanTangLeNguyen(a, n);
    printf("Mang sau khi sap xep chan tang le nguyen: ");
    XuatMang(a, n);


    SapXepLeChan(a, n);
    printf("Mang sau khi sap xep le o dau chan o cuoi: ");
    XuatMang(a, n);

    return 0;
}

