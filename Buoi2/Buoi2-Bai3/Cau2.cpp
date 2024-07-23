#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char ten[50];
    int tuoi;
    float diemTB;
} SinhVien;


typedef struct {
    char tenLop[50];
    int siSo;
    SinhVien *danhSachSinhVien;
} LopHoc;


void taoFileDSLop(LopHoc *danhSachLop, int soLop) {
    FILE *file = fopen("dslop.txt", "w");
    if (file == NULL) {
        printf("Không the tao file.\n");
        return;
    }
    
    for (int i = 0; i < soLop; i++) {
        fprintf(file, "%s %d\n", danhSachLop[i].tenLop, danhSachLop[i].siSo);
        for (int j = 0; j < danhSachLop[i].siSo; j++) {
            fprintf(file, "%s %d %.2f\n", danhSachLop[i].danhSachSinhVien[j].ten, danhSachLop[i].danhSachSinhVien[j].tuoi, danhSachLop[i].danhSachSinhVien[j].diemTB);
        }
    }
    
    fclose(file);
}


void docFileDSLop(LopHoc **danhSachLop, int *soLop) {
    FILE *file = fopen("dslop.txt", "r");
    if (file == NULL) {
        printf("Không the mo file.\n");
        return;
    }
    
    fscanf(file, "%d", soLop);
    *danhSachLop = (LopHoc*)malloc((*soLop) * sizeof(LopHoc));
    
    for (int i = 0; i < *soLop; i++) {
        fscanf(file, "%s %d", (*danhSachLop)[i].tenLop, &(*danhSachLop)[i].siSo);
        (*danhSachLop)[i].danhSachSinhVien = (SinhVien*)malloc((*danhSachLop)[i].siSo * sizeof(SinhVien));
        
        for (int j = 0; j < (*danhSachLop)[i].siSo; j++) {
            fscanf(file, "%s %d %f", (*danhSachLop)[i].danhSachSinhVien[j].ten, &(*danhSachLop)[i].danhSachSinhVien[j].tuoi, &(*danhSachLop)[i].danhSachSinhVien[j].diemTB);
        }
    }
    
    fclose(file);
}


void xuatDanhSachLop(LopHoc *danhSachLop, int soLop) {
    for (int i = 0; i < soLop; i++) {
        printf("Lop: %s\n", danhSachLop[i].tenLop);
        printf("Si so: %d\n", danhSachLop[i].siSo);
        for (int j = 0; j < danhSachLop[i].siSo; j++) {
            printf("Sinh vien: %s, Tuoi: %d, Ðiem TB: %.2f\n", danhSachLop[i].danhSachSinhVien[j].ten, danhSachLop[i].danhSachSinhVien[j].tuoi, danhSachLop[i].danhSachSinhVien[j].diemTB);
        }
        printf("\n");
    }
}


void inLopCoSinhVienGioi(LopHoc *danhSachLop, int soLop) {
    for (int i = 0; i < soLop; i++) {
        int demSinhVienGioi = 0;
        for (int j = 0; j < danhSachLop[i].siSo; j++) {
            if (danhSachLop[i].danhSachSinhVien[j].diemTB >= 8.0) {
                demSinhVienGioi++;
            }
        }
        if (demSinhVienGioi > 5) {
            printf("Lop %s có %d sinh vien gioi.\n", danhSachLop[i].tenLop, demSinhVienGioi);
        }
    }
}


void timLopNhieuSinhVienNhat(LopHoc *danhSachLop, int soLop) {
    int maxSiSo = 0;
    int chiSoLop = 0;
    for (int i = 0; i < soLop; i++) {
        if (danhSachLop[i].siSo > maxSiSo) {
            maxSiSo = danhSachLop[i].siSo;
            chiSoLop = i;
        }
    }
    printf("Lop co nhieu sinh vien nhat la %s voi %d sinh vien.\n", danhSachLop[chiSoLop].tenLop, danhSachLop[chiSoLop].siSo);
}


void timSinhVienDiemTBCaoNhat(LopHoc *danhSachLop, int soLop) {
    float maxDiemTB = 0;
    SinhVien sinhVienDiemTBCaoNhat;
    for (int i = 0; i < soLop; i++) {
        for (int j = 0; j < danhSachLop[i].siSo; j++) {
            if (danhSachLop[i].danhSachSinhVien[j].diemTB > maxDiemTB) {
                maxDiemTB = danhSachLop[i].danhSachSinhVien[j].diemTB;
                sinhVienDiemTBCaoNhat = danhSachLop[i].danhSachSinhVien[j];
            }
        }
    }
    printf("Sinh vien có diem trung binh cao nhat la %s voi diem TB la %.2f.\n", sinhVienDiemTBCaoNhat.ten, sinhVienDiemTBCaoNhat.diemTB);
}

int main() {
    int soLop;
    LopHoc *danhSachLop;

    
    printf("Nhap so luong lop: ");
    scanf("%d", &soLop);
    
    danhSachLop = (LopHoc*)malloc(soLop * sizeof(LopHoc));
    
    for (int i = 0; i < soLop; i++) {
        printf("Nhap ten lop %d: ", i + 1);
        scanf("%s", danhSachLop[i].tenLop);
        printf("Nhap si so lop %d: ", i + 1);
        scanf("%d", &danhSachLop[i].siSo);
        
        danhSachLop[i].danhSachSinhVien = (SinhVien*)malloc(danhSachLop[i].siSo * sizeof(SinhVien));
        
        for (int j = 0; j < danhSachLop[i].siSo; j++) {
            printf("Nhap ten sinh vien %d: ", j + 1);
            scanf("%s", danhSachLop[i].danhSachSinhVien[j].ten);
            fflush(stdin);
            printf("Nhap tuoi sinh vien %d: ", j + 1);
            scanf("%d", &danhSachLop[i].danhSachSinhVien[j].tuoi);
            fflush(stdin);
            printf("Nhap diem TB sinh vien %d: ", j + 1);
            scanf("%f", &danhSachLop[i].danhSachSinhVien[j].diemTB);
        }
    }
    
    
    taoFileDSLop(danhSachLop, soLop);
    
    
    LopHoc *docDanhSachLop;
    int docSoLop;
    docFileDSLop(&docDanhSachLop, &docSoLop);
    
    
    xuatDanhSachLop(docDanhSachLop, docSoLop);
    
    
    inLopCoSinhVienGioi(docDanhSachLop, docSoLop);
    
    
    timLopNhieuSinhVienNhat(docDanhSachLop, docSoLop);
    
    
    timSinhVienDiemTBCaoNhat(docDanhSachLop, docSoLop);
    
   
    for (int i = 0; i < soLop; i++) {
        free(danhSachLop[i].danhSachSinhVien);
    }
    free(danhSachLop);
    for (int i = 0; i < docSoLop; i++) {
        free(docDanhSachLop[i].danhSachSinhVien);
    }
    free(docDanhSachLop);
    
    return 0;
}

