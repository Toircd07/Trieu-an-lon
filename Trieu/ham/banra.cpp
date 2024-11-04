#include "banra.h"
#include <bits/stdc++.h>
using namespace std;

DonHang::DonHang(string _ngay, int _soLuong[], int _gia[]) {
    ngay = _ngay;
    for (int i = 0; i < 5; i++) {
        soLuong[i] = _soLuong[i];
        gia[i] = _gia[i];
    }
}

void DonHang::hienThi() const {
    cout << setw(12) << ngay;
    for (int i = 0; i < 5; i++) {
        cout << setw(12) << soLuong[i];
    }
    for (int i = 0; i < 5; i++) {
        cout << setw(12) << gia[i];
    }
    cout << endl;
}

string DonHang::toCSVFormat() const {
    stringstream ss;
    ss << ngay;
    for (int i = 0; i < 5; i++) {
        ss << ";" << soLuong[i];
    }
    for (int i = 0; i < 5; i++) {
        ss << ";" << gia[i];
    }
    return ss.str() + "\n";
}

QuanLyDonHang::QuanLyDonHang(const string& tenFile) {
    docTuFile(tenFile);
}

void QuanLyDonHang::docTuFile(const string& tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }

    string line, ngay;
    int soLuong[5], gia[5];

    getline(file, line); // Bỏ qua dòng tiêu đề

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, ngay, ';');
        for (int i = 0; i < 5; i++) {
            ss >> soLuong[i];
            ss.ignore();
        }
        for (int i = 0; i < 5; i++) {
            ss >> gia[i];
            if (i < 4) ss.ignore();
        }
        danhSachDonHang.emplace_back(ngay, soLuong, gia);
    }
    file.close();
}

void QuanLyDonHang::luuVaoFile(const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }
    file << "ngay;so_luong_A1;so_luong_A2;so_luong_A3;so_luong_A4;so_luong_A5;gia_A1;gia_A2;gia_A3;gia_A4;gia_A5\n";
    for (const auto& donHang : danhSachDonHang) {
        file << donHang.toCSVFormat();
    }
    file.close();
}

void QuanLyDonHang::capNhatDonHangTuFile(const string& tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }

    string line, ngay, loaiThit;
    int soLuong;

    getline(file, line); // Bỏ qua dòng tiêu đề

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, ngay, ';');
        getline(ss, loaiThit, ';');
        ss >> soLuong;

        for (auto& donHang : danhSachDonHang) {
            if (donHang.ngay == ngay) {
                if (loaiThit == "A1") {
                    donHang.soLuong[0] = soLuong;
                } else if (loaiThit == "A2") {
                    donHang.soLuong[1] = soLuong;
                } else if (loaiThit == "A3") {
                    donHang.soLuong[2] = soLuong;
                } else if (loaiThit == "A4") {
                    donHang.soLuong[3] = soLuong;
                } else if (loaiThit == "A5") {
                    donHang.soLuong[4] = soLuong;
                }
                break;
            }
        }
    }

    file.close();
}

void QuanLyDonHang::luuDanhSachDonHang(const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }
    file << "ngay;so_luong_A1;so_luong_A2;so_luong_A3;so_luong_A4;so_luong_A5;gia_A1;gia_A2;gia_A3;gia_A4;gia_A5\n";
    for (const auto& donHang : danhSachDonHang) {
        file << donHang.toCSVFormat();
    }
    file.close();
}

void QuanLyDonHang::themDonHang() {
    string ngay;
    int soLuong[5], gia[5];

    cout << "Nhap ngay (dd/mm/yyyy): ";
    cin >> ngay;
    for (int i = 0; i < 5; i++) {
        cout << "Nhap so luong cho A" << (i + 1) << ": ";
        cin >> soLuong[i];
    }
    for (int i = 0; i < 5; i++) {
        cout << "Nhap gia cho A" << (i + 1) << ": ";
        cin >> gia[i];
    }

    danhSachDonHang.emplace_back(ngay, soLuong, gia);
    luuVaoFile("data/donhangbanra.csv");
    cout << "Don hang da duoc them thanh cong.\n";
}

void QuanLyDonHang::hienThiDanhSachDonHang() const {
    cout << setw(12) << "Ngay"
         << setw(12) << "S.L A1" << setw(12) << "S.L A2" << setw(12) << "S.L A3" << setw(12) << "S.L A4" << setw(12) << "S.L A5"
         << setw(12) << "Gia A1" << setw(12) << "Gia A2" << setw(12) << "Gia A3" << setw(12) << "Gia A4" << setw(12) << "Gia A5"
         << endl;
    for (const auto& donHang : danhSachDonHang) {
        donHang.hienThi();
    }
}

void QuanLyDonHang::suaDonHang(const string& ngay) {
    for (auto& donHang : danhSachDonHang) {
        if (donHang.ngay == ngay) {
            int soLuong[5], gia[5];
            for (int i = 0; i < 5; i++) {
                cout << "Nhap so luong moi cho A" << (i + 1) << ": ";
                cin >> soLuong[i];
            }
            for (int i = 0; i < 5; i++) {
                cout << "Nhap gia moi cho A" << (i + 1) << ": ";
                cin >> gia[i];
            }

            donHang = DonHang(ngay, soLuong, gia);
            luuVaoFile("data/donhangbanra.csv");
            cout << "Thong tin don hang da duoc cap nhat.\n";
            return;
        }
    }
    cout << "Khong tim thay don hang voi ngay " << ngay << endl;
}

void QuanLyDonHang::xoaDonHang(const string& ngay) {
    for (auto it = danhSachDonHang.begin(); it != danhSachDonHang.end(); ++it) {
        if (it->ngay == ngay) {
            danhSachDonHang.erase(it);
            luuVaoFile("data/donhangbanra.csv");
            cout << "Don hang da duoc xoa.\n";
            return;
        }
    }
    cout << "Khong tim thay don hang voi ngay " << ngay << endl;
}

void QuanLyDonHang::timKiemDonHang(const string& ngay) const {
    bool timThay = false;
    cout << setw(12) << "Ngay"
         << setw(12) << "S.L A1" << setw(12) << "S.L A2" << setw(12) << "S.L A3" << setw(12) << "S.L A4" << setw(12) << "S.L A5"
         << setw(12) << "Gia A1" << setw(12) << "Gia A2" << setw(12) << "Gia A3" << setw(12) << "Gia A4" << setw(12) << "Gia A5"
         << endl;

    for (const auto& donHang : danhSachDonHang) {
        if (donHang.ngay == ngay) {
            donHang.hienThi();
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay don hang.\n";
    }
}

void QuanLyDonHang::capNhatDuLieu() {
    capNhatDonHangTuFile("data/Costumer (2).csv");
    luuDanhSachDonHang("data/donhangbanra.csv");
}