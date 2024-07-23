#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char hoTen[50];
    char soDienThoai[20];
    int soVeNguoiLon;
    int soVeTreEm;
    char tenPhim[50];
    char phongChieu[10];
    char xuatChieu[20];
    int tienPhaiTra;
} KhachHang;

KhachHang dskh[MAX];
int n = 0;

void docDanhSachKhachHang() {
    FILE *file = fopen("dskh.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file!\n");
        return;
    }
    while (fscanf(file, "%[^\n]%*c", dskh[n].hoTen) != EOF) {
        fscanf(file, "%[^\n]%*c", dskh[n].soDienThoai);
        fscanf(file, "%d", &dskh[n].soVeNguoiLon);
        fscanf(file, "%d", &dskh[n].soVeTreEm);
        fscanf(file, "%*c%[^\n]%*c", dskh[n].tenPhim);
        fscanf(file, "%[^\n]%*c", dskh[n].phongChieu);
        fscanf(file, "%[^\n]%*c", dskh[n].xuatChieu);
        dskh[n].tienPhaiTra = dskh[n].soVeNguoiLon * 40000 + dskh[n].soVeTreEm * 20000;
        n++;
    }
    fclose(file);
}

void xuatDanhSachKhachHang() {
    printf("Danh sach khach hang:\n");
    for (int i = 0; i < n; i++) {
        printf("Khach hang %d:\n", i + 1);
        printf("Ho ten: %s\n", dskh[i].hoTen);
        printf("So dien thoai: %s\n", dskh[i].soDienThoai);
        printf("So ve nguoi lon: %d\n", dskh[i].soVeNguoiLon);
        printf("So ve tre em: %d\n", dskh[i].soVeTreEm);
        printf("Ten phim: %s\n", dskh[i].tenPhim);
        printf("Phong chieu: %s\n", dskh[i].phongChieu);
        printf("Xuat chieu: %s\n", dskh[i].xuatChieu);
        printf("Tien phai tra: %d VND\n", dskh[i].tienPhaiTra);
    }
}

void tinhTongDoanhThu() {
    int tongDoanhThu = 0;
    for (int i = 0; i < n; i++) {
        tongDoanhThu += dskh[i].tienPhaiTra;
    }
    printf("Tong doanh thu cua rap phim: %d VND\n", tongDoanhThu);
}

void tinhTongDoanhThuTungPhim() {
    for (int i = 0; i < n; i++) {
        int tongDoanhThu = 0;
        for (int j = 0; j < n; j++) {
            if (strcmp(dskh[i].tenPhim, dskh[j].tenPhim) == 0) {
                tongDoanhThu += dskh[j].tienPhaiTra;
            }
        }
        printf("Tong doanh thu cua phim \"%s\": %d VND\n", dskh[i].tenPhim, tongDoanhThu);
    }
}

void xuatThongTinKhachHangTheoPhongVaXuat() {
    char phongChieu[10], xuatChieu[20];
    fflush(stdin);
    printf("Nhap phong chieu: ");
    scanf("%s", phongChieu);
    fflush(stdin);
    printf("Nhap xuat chieu: ");
    scanf("%s", xuatChieu);
    
    printf("Thong tin khach hang cua phong chieu %s va xuat chieu %s:\n", phongChieu, xuatChieu);
    for (int i = 0; i < n; i++) {
        if (strcmp(dskh[i].phongChieu, phongChieu) == 0 && strcmp(dskh[i].xuatChieu, xuatChieu) == 0) {
            printf("Ho ten: %s\n", dskh[i].hoTen);
            printf("So dien thoai: %s\n", dskh[i].soDienThoai);
            printf("So ve nguoi lon: %d\n", dskh[i].soVeNguoiLon);
            printf("So ve tre em: %d\n", dskh[i].soVeTreEm);
            printf("Ten phim: %s\n", dskh[i].tenPhim);
            printf("Tien phai tra: %d VND\n", dskh[i].tienPhaiTra);
        }
    }
}

void hoanVi(KhachHang *a, KhachHang *b) {
    KhachHang temp = *a;
    *a = *b;
    *b = temp;
}

void sapXepTienPhaiTraChon() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dskh[i].tienPhaiTra > dskh[j].tienPhaiTra) {
                hoanVi(&dskh[i], &dskh[j]);
            }
        }
    }
}

void sapXepTienPhaiTraNoiBot() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dskh[j].tienPhaiTra > dskh[j + 1].tienPhaiTra) {
                hoanVi(&dskh[j], &dskh[j + 1]);
            }
        }
    }
}

void sapXepTienPhaiTraChen() {
    for (int i = 1; i < n; i++) {
        KhachHang key = dskh[i];
        int j = i - 1;
        while (j >= 0 && dskh[j].tienPhaiTra > key.tienPhaiTra) {
            dskh[j + 1] = dskh[j];
            j--;
        }
        dskh[j + 1] = key;
    }
}

void sapXepHoTen() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(dskh[i].hoTen, dskh[j].hoTen) > 0) {
                hoanVi(&dskh[i], &dskh[j]);
            }
        }
    }
}

int binarySearch(char *hoTen) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(dskh[mid].hoTen, hoTen);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    int choice;
    char hoTen[50];
    
    docDanhSachKhachHang();
    xuatDanhSachKhachHang();
    
    printf("\nChon phuong thuc sap xep so tien phai tra:\n");
    printf("1. Sap xep bang thuat toán chon\n");
    printf("2. Sap xep bang thuat toan noi bot\n");
    printf("3. Sap xep bang thuat toan chen\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            sapXepTienPhaiTraChon();
            break;
        case 2:
            sapXepTienPhaiTraNoiBot();
            break;
        case 3:
            sapXepTienPhaiTraChen();
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return 1;
    }
    
    printf("\nDanh sach khach hang sau khi sap xep theo so tien phai tra tang dan:\n");
    xuatDanhSachKhachHang();
    
    sapXepHoTen();
    printf("\nDanh sach khach hang sau khi sap xep theo ho ten tang dan:\n");
    xuatDanhSachKhachHang();
    
    printf("\nNhap ten khach hang can tim: ");
    scanf("%s", hoTen);
    int index = binarySearch(hoTen);
    if (index != -1) {
        printf("Khach hang \"%s\" duoc tim thay:\n", hoTen);
        printf("Ho ten: %s\n", dskh[index].hoTen);
        printf("So dien thoai: %s\n", dskh[index].soDienThoai);
        printf("So ve nguoi lon: %d\n", dskh[index].soVeNguoiLon);
        printf("So ve tre em: %d\n", dskh[index].soVeTreEm);
        printf("Ten phim: %s\n", dskh[index].tenPhim);
        printf("Phong chieu: %s\n", dskh[index].phongChieu);
        printf("Xuat chieu: %s\n", dskh[index].xuatChieu);
        printf("Tien phai tra: %d VND\n", dskh[index].tienPhaiTra);
    } else {
        printf("Khach hang \"%s\" khong duoc tim thay!\n", hoTen);
    }
    
    tinhTongDoanhThu();
    tinhTongDoanhThuTungPhim();
    xuatThongTinKhachHangTheoPhongVaXuat();
    
    return 0;
}

