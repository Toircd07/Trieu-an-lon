#include "tonkho.h"
#include "banra.h"
#include <iostream>

using namespace std;

void TKmenu() {
    QuanLyTonKho quanLy("data/tonkho.csv");
    int luaChon;

    do {
        cout << "\n--- Quan Ly Ton Kho ---\n";
        cout << "1. Them san pham\n";
        cout << "2. Hien thi danh sach san pham\n";
        cout << "3. Sua thong tin san pham\n";
        cout << "4. Xoa san pham\n";
        cout << "5. Tim kiem san pham\n";
        cout << "0. Thoat\n";
        cout << "Chon mot tuy chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                quanLy.themSanPham();
                break;
            case 2:
                quanLy.hienThiDanhSachTonKho();
                break;
            case 3: {
                string ngay;
                cout << "Nhap ngay can sua: ";
                cin >> ngay;
                quanLy.suaSanPham(ngay);
                break;
            }
            case 4: {
                string ngay;
                cout << "Nhap ngay can xoa: ";
                cin >> ngay;
                quanLy.xoaSanPham(ngay);
                break;
            }
            case 5: {
                string ngay;
                cout << "Nhap ngay san pham can tim: ";
                cin >> ngay;
                quanLy.timKiemSanPham(ngay);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai!\n";
        }
    } while (luaChon != 0);
}
void BRmenu() {
    QuanLyDonHang quanLy("data/donhangbanra.csv");
    int luaChon;

    do {
        cout << "\n--- Quan Ly Don Hang ---\n";
        cout << "1. Them don hang\n";
        cout << "2. Hien thi danh sach don hang\n";
        cout << "3. Sua thong tin don hang\n";
        cout << "4. Xoa don hang\n";
        cout << "5. Tim kiem don hang\n";
        cout << "0. Thoat\n";
        cout << "Chon mot tuy chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                quanLy.themDonHang();
                break;
            case 2:
                quanLy.hienThiDanhSachDonHang();
                break;
            case 3: {
                string ngay;
                cout << "Nhap ngay can sua: ";
                cin >> ngay;
                quanLy.suaDonHang(ngay);
                break;
            }
            case 4: {
                string ngay;
                cout << "Nhap ngay can xoa: ";
                cin >> ngay;
                quanLy.xoaDonHang(ngay);
                break;
            }
            case 5: {
                string ngay;
                cout << "Nhap ngay don hang can tim: ";
                cin >> ngay;
                quanLy.timKiemDonHang(ngay);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai!\n";
        }
    } while (luaChon != 0);
}

int main() {
    int luaChon;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Quan ly don hang\n";
        cout << "2. Quan ly ton kho\n";
        cout << "0. Thoat\n";
        cout << "Chon mot tuy chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                BRmenu();
                break;
            case 2:
                TKmenu();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai!\n";
        }
    } while (luaChon != 0);

    return 0;
}