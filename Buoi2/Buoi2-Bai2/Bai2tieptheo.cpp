#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int phan_nguyen;
    int tu_so;
    int mau_so;
} HonSo;

typedef struct {
    int tu_so;
    int mau_so;
} PhanSo;

void taoMangHonSo(HonSo b[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        b[i].phan_nguyen = rand() % 10; 
        b[i].tu_so = rand() % 10;       
        do {
            b[i].mau_so = rand() % 10;  
        } while (b[i].mau_so == 0);
    }
}

void xuatDanhSachHonSo(HonSo b[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d/%d\n", b[i].phan_nguyen, b[i].tu_so, b[i].mau_so);
    }
}

int soSanhHonSo(HonSo a, HonSo b) {
    int tu_so_a = a.phan_nguyen * a.mau_so + a.tu_so;
    int tu_so_b = b.phan_nguyen * b.mau_so + b.tu_so;
    int mau_so_chung = a.mau_so * b.mau_so;
    
    if (tu_so_a * b.mau_so < tu_so_b * a.mau_so)
        return -1;
    else if (tu_so_a * b.mau_so > tu_so_b * a.mau_so)
        return 1;
    else
        return 0;
}

PhanSo chuyenHonSoThanhPhanSo(HonSo a) {
    PhanSo ketqua;
    ketqua.tu_so = a.phan_nguyen * a.mau_so + a.tu_so;
    ketqua.mau_so = a.mau_so;
    return ketqua;
}

HonSo chuyenPhanSoThanhHonSo(PhanSo a) {
    HonSo ketqua;
    ketqua.phan_nguyen = a.tu_so / a.mau_so;
    ketqua.tu_so = a.tu_so % a.mau_so;
    ketqua.mau_so = a.mau_so;
    return ketqua;
}

HonSo tinhTongHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.mau_so + ps_b.tu_so * ps_a.mau_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.mau_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

HonSo tinhHieuHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.mau_so - ps_b.tu_so * ps_a.mau_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.mau_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

HonSo tinhTichHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.tu_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.mau_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

HonSo tinhThuongHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.mau_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.tu_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

void sapXepNoiBot(HonSo b[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (soSanhHonSo(b[j], b[j+1]) > 0) {
                HonSo temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }
}

void sapXepChen(HonSo b[], int n) {
    for (int i = 1; i < n; i++) {
        HonSo key = b[i];
        int j = i - 1;
        while (j >= 0 && soSanhHonSo(b[j], key) > 0) {
            b[j + 1] = b[j];
            j = j - 1;
        }
        b[j + 1] = key;
    }
}

void sapXepChon(HonSo b[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (soSanhHonSo(b[j], b[min_idx]) < 0) {
                min_idx = j;
            }
        }
        HonSo temp = b[min_idx];
        b[min_idx] = b[i];
        b[i] = temp;
    }
}

// 1. Linear search
int timKiemTuyenTinh(HonSo b[], int n, HonSo x) {
    for (int i = 0; i < n; i++) {
        if (soSanhHonSo(b[i], x) == 0) {
            return i;
        }
    }
    return -1;
}

// 2. Sap xep phan nguyen chan len dau
void sapXepChanLe(HonSo b[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        while (left < n && b[left].phan_nguyen % 2 == 0) left++;
        while (right >= 0 && b[right].phan_nguyen % 2 != 0) right--;
        if (left < right) {
            HonSo temp = b[left];
            b[left] = b[right];
            b[right] = temp;
        }
    }
}

// 3. Binary search
int timKiemNhiPhan(HonSo b[], int n, HonSo x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int comparison = soSanhHonSo(b[mid], x);
        if (comparison == 0)
            return mid;
        else if (comparison < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 4. Chia mang b thanh 2 mang s1 va s2
void chiaMang(HonSo b[], int n, int s1[], PhanSo s2[]) {
    for (int i = 0; i < n; i++) {
        s1[i] = b[i].phan_nguyen;
        s2[i].tu_so = b[i].tu_so;
        s2[i].mau_so = b[i].mau_so;
    }
}

// 5. Xoa phan tu thu k
void xoaPhanTu(HonSo b[], int *n, int k) {
    if (k < 0 || k >= *n) return;
    for (int i = k; i < *n - 1; i++) {
        b[i] = b[i + 1];
    }
    (*n)--;
}

// 6. Them hon so x vao vi tri k
void themPhanTu(HonSo b[], int *n, HonSo x, int k) {
    if (k < 0 || k > *n) return;
    for (int i = *n; i > k; i--) {
        b[i] = b[i - 1];
    }
    b[k] = x;
    (*n)++;
}

// 7. Tao mang c tu mang b
void taoMangC(HonSo b[], int n, PhanSo c[]) {
    for (int i = 0; i < n; i++) {
        c[i] = chuyenHonSoThanhPhanSo(b[i]);
    }
}

// 8. Tinh tong mang b
HonSo tinhTongMang(HonSo b[], int n) {
    HonSo tong = {0, 0, 1};
    for (int i = 0; i < n; i++) {
        tong = tinhTongHonSo(tong, b[i]);
    }
    return tong;
}

// 9. Tim phan tu lon nhat/nho nhat
HonSo timPhanTuLonNhat(HonSo b[], int n) {
    HonSo max = b[0];
    for (int i = 1; i < n; i++) {
        if (soSanhHonSo(b[i], max) > 0) {
            max = b[i];
        }
    }
    return max;
}

HonSo timPhanTuNhoNhat(HonSo b[], int n) {
    HonSo min = b[0];
    for (int i = 1; i < n; i++) {
        if (soSanhHonSo(b[i], min) < 0) {
            min = b[i];
        }
    }
    return min;
}

// 10. Xuat vi tri phan nguyen chan
void xuatViTriPhanNguyenChan(HonSo b[], int n) {
    printf("Vi tri phan nguyen chan:\n");
    for (int i = 0; i < n; i++) {
        if (b[i].phan_nguyen % 2 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// 11. Xuat vi tri phan tu lon nhat/nho nhat
void xuatViTriPhanTuLonNhat(HonSo b[], int n) {
    HonSo max = timPhanTuLonNhat(b, n);
    printf("Vi tri phan tu lon nhat:\n");
    for (int i = 0; i < n; i++) {
        if (soSanhHonSo(b[i], max) == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void xuatViTriPhanTuNhoNhat(HonSo b[], int n) {
    HonSo min = timPhanTuNhoNhat(b, n);
    printf("Vi tri phan tu nho nhat:\n");
    for (int i = 0; i < n; i++) {
        if (soSanhHonSo(b[i], min) == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int n = 10; 
    HonSo b[100];
    HonSo x = {5, 3, 7};
    
    taoMangHonSo(b, n);
    printf("Danh sach hon so ban dau:\n");
    xuatDanhSachHonSo(b, n);
    
    // 1. Linear search
    int index = timKiemTuyenTinh(b, n, x);
    if (index != -1)
        printf("\nHon so x tim thay tai vi tri: %d\n", index);
    else
        printf("\nHon so x khong co trong mang\n");

    // 2. Sap xep chan le
    sapXepChanLe(b, n);
    printf("\nDanh sach sau khi sap xep phan nguyen chan len dau:\n");
    xuatDanhSachHonSo(b, n);
    
    // 3. Binary search
    sapXepNoiBot(b, n);  // Ensure array is sorted
    index = timKiemNhiPhan(b, n, x);
    if (index != -1)
        printf("\nHon so x tim thay tai vi tri (binary search): %d\n", index);
    else
        printf("\nHon so x khong co trong mang (binary search)\n");

    // 4. Chia mang thanh s1 va s2
    int s1[100];
    PhanSo s2[100];
    chiaMang(b, n, s1, s2);
    printf("\nMang s1 (phan nguyen):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", s1[i]);
    }
    printf("\nMang s2 (phan so):\n");
    for (int i = 0; i < n; i++) {
        printf("%d/%d ", s2[i].tu_so, s2[i].mau_so);
    }
    printf("\n");

    // 5. Xoa phan tu thu k
    int k = 2;
    xoaPhanTu(b, &n, k);
    printf("\nMang sau khi xoa phan tu thu %d:\n", k);
    xuatDanhSachHonSo(b, n);

    // 6. Them phan tu x vao vi tri k
    themPhanTu(b, &n, x, k);
    printf("\nMang sau khi them hon so x vao vi tri %d:\n", k);
    xuatDanhSachHonSo(b, n);

    // 7. Tao mang c tu mang b
    PhanSo c[100];
    taoMangC(b, n, c);
    printf("\nMang c (phan so tu hon so mang b):\n");
    for (int i = 0; i < n; i++) {
        printf("%d/%d ", c[i].tu_so, c[i].mau_so);
    }
    printf("\n");

    // 8. Tinh tong mang b
    HonSo tong = tinhTongMang(b, n);
    printf("\nTong cac hon so trong mang b: %d %d/%d\n", tong.phan_nguyen, tong.tu_so, tong.mau_so);

    // 9. Tim phan tu lon nhat/nho nhat
    HonSo max = timPhanTuLonNhat(b, n);
    HonSo min = timPhanTuNhoNhat(b, n);
    printf("\nPhan tu lon nhat: %d %d/%d\n", max.phan_nguyen, max.tu_so, max.mau_so);
    printf("Phan tu nho nhat: %d %d/%d\n", min.phan_nguyen, min.tu_so, min.mau_so);

    // 10. Xuat vi tri phan nguyen chan
    xuatViTriPhanNguyenChan(b, n);

    // 11. Xuat vi tri phan tu lon nhat/nho nhat
    xuatViTriPhanTuLonNhat(b, n);
    xuatViTriPhanTuNhoNhat(b, n);
    
    return 0;
}

