#include <conio.h>
#include <stdio.h>
#include <string.h>

//=================================================================
//=================================================================
#define MAXSIZE 100
#define fNameIn_DSSV "input_DSSV.txt" 
#define fNameOut_DSSV "output_DSSV.txt" 

typedef struct SinhVien {
    char mssv[11];
    char ho[8], hoLot[20], ten[8];
    double diemTB;
    char xepLoai[10];
} SV;
typedef SV ItemType;

//=================================================================
//=================================================================
void xepLoaiSV(ItemType &x) {
    if (x.diemTB >= 8) strcpy(x.xepLoai, "Gioi");
    else if (x.diemTB >= 6.5) strcpy(x.xepLoai, "Kha");
    else if (x.diemTB >= 5.0) strcpy(x.xepLoai, "Trung binh");
    else strcpy(x.xepLoai, "Yeu");
}

void xuatTTSV(ItemType x) {
    printf("%-15s%-10s%-20s%-10s%5.2lf%-10s\n", x.mssv, x.ho, x.hoLot, x.ten, x.diemTB, x.xepLoai);
}

void docTTSV(FILE *fi, ItemType &x) {
    fscanf(fi, "%[^#]%*c%[^#]%*c%[^#]%*c%[^#]%*c%lf\n", x.mssv, x.ho, x.hoLot, x.ten, &x.diemTB);
    xepLoaiSV(x);
}

void ghiTTSV(FILE *fo, ItemType x) {
    fprintf(fo, "%-15s%-10s%-20s%-10s%5.2lf%-10s\n", x.mssv, x.ho, x.hoLot, x.ten, x.diemTB, x.xepLoai);
}

void docDSSV(char fNameIn[], ItemType ds[], int &n) {
    FILE *fi = fopen(fNameIn, "rt");
    if (fi == NULL) {
        printf("Loi: mo file de doc du lieu.");
        getch();
        return;
    }
    fscanf(fi, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        SV x;
        docTTSV(fi, x);
        ds[i] = x;
    }
    fclose(fi);
}

void ghiDSSV(char fNameOut[], ItemType ds[], int n) {
    FILE *fo = fopen(fNameOut, "wt");
    if (fo == NULL) {
        printf("Loi: mo file de ghi du lieu.");
        getch();
        return;
    }
    fprintf(fo, "%-5s%-15s%-40s%-10s%-10s\n", "STT", "MSSV", "HO VA TEN SINH VIEN", "DIEM TB", "XEP LOAI");
    for (int i = 0; i < n; i++) {
        fprintf(fo, "%-5d", i + 1);
        ghiTTSV(fo, ds[i]);
    }
    fclose(fo);
}

void xuatDSSV(ItemType ds[], int &n) {
    printf("%-5s%-15s%-40s%-10s%-10s\n", "STT", "MSSV", "HO VA TEN SINH VIEN", "DIEM TB", "XEP LOAI");
    for (int i = 0; i < n; i++) {
        printf("%-5d", i + 1);
        xuatTTSV(ds[i]);
    }
}

void sapXepTangDan(ItemType ds[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (ds[i].diemTB > ds[j].diemTB) {
                ItemType temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void sapXepGiamDan(ItemType ds[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (ds[i].diemTB < ds[j].diemTB) {
                ItemType temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void timSV_DTB_CaoNhat(ItemType ds[], int n) {
    double max = ds[0].diemTB;
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (ds[i].diemTB > max) {
            max = ds[i].diemTB;
            idx = i;
        }
    }
    printf("Sinh vien co diem trung binh cao nhat la:\n");
    xuatTTSV(ds[idx]);
}

void timSV_DTB_ThapNhat(ItemType ds[], int n) {
    double min = ds[0].diemTB;
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (ds[i].diemTB < min) {
            min = ds[i].diemTB;
            idx = i;
        }
    }
    printf("Sinh vien co diem trung binh thap nhat la:\n");
    xuatTTSV(ds[idx]);
}

void inSV_XepLoai_Gioi_Kha(ItemType ds[], int n) {
    printf("Danh sach sinh vien xep loai Gioi va Kha:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].xepLoai, "Gioi") == 0 || strcmp(ds[i].xepLoai, "Kha") == 0) {
            xuatTTSV(ds[i]);
        }
    }
}

int demSV_HoNguyen(ItemType ds[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].ho, "Nguyen") == 0) {
            count++;
        }
    }
    return count;
}

//=================================================================
//* Ph?n giao di?n và Hàm main
//=================================================================
void showMenu() {
    printf("\n***********************************************");
    printf("\n* MENU *");
    printf("\n***********************************************");
    printf("\n* 1. Doc danh sach sinh vien tu file *");
    printf("\n* 2. Xuat danh sach ra man hinh *");
    printf("\n* 3. Ghi danh sach sinh vien xuong file *");
    printf("\n* 4. Sap xep danh sach sinh vien tang dan theo diem trung binh *");
    printf("\n* 5. Sap xep danh sach sinh vien giam dan theo diem trung binh *");
    printf("\n* 6. Tim sinh vien co diem trung binh cao nhat *");
    printf("\n* 7. Tim sinh vien co diem trung binh thap nhat *");
    printf("\n* 8. In danh sach sinh vien xep loai Gioi va Kha *");
    printf("\n* 9. Dem so luong sinh vien ho Nguyen *");
    printf("\n* 0. Thoat chuong trinh *");
    printf("\n***********************************************");
}

void process() {
    SV DS[MAXSIZE];
    int N = 0;
    int chonChucNang;
    do {
        showMenu();
        printf("\nBan hay chon mot chuc nang bat ky: ");
        scanf("%d", &chonChucNang);
        switch (chonChucNang) {
            case 1:
                docDSSV(fNameIn_DSSV, DS, N);
                printf("DANH SACH SINH VIEN DOC TU FILE.\n");
                xuatDSSV(DS, N);
                break;
            case 2:
                printf("DANH SACH SINH VIEN LA:\n");
                xuatDSSV(DS, N);
                break;
            case 3:
                printf("GHI DANH SACH SINH VIEN XUONG FILE\n");
                ghiDSSV(fNameOut_DSSV, DS, N);
                break;
            case 4:
                printf("SAP XEP DANH SACH SINH VIEN TANG DAN THEO DIEM TB\n");
                sapXepTangDan(DS, N);
                xuatDSSV(DS, N);
                break;
            case 5:
                printf("SAP XEP DANH SACH SINH VIEN GIAM DAN THEO DIEM TB\n");
                sapXepGiamDan(DS, N);
                xuatDSSV(DS, N);
                break;
            case 6:
                timSV_DTB_CaoNhat(DS, N);
                break;
            case 7:
                timSV_DTB_ThapNhat(DS, N);
                break;
            case 8:
                inSV_XepLoai_Gioi_Kha(DS, N);
                break;
            case 9:
                printf("So luong sinh vien ho Nguyen la: %d\n", demSV_HoNguyen(DS, N));
                break;
        }
    } while (chonChucNang != 0);
}

int main() {
    process();
}

