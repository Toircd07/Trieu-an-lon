#include "tonkho.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <map>
#include <array>

using namespace std;


SanPhamTonKho::SanPhamTonKho(string _ngay, const std::array<int, 5>& _soLuong, const std::array<int, 5>& _gia) {
    ngay = _ngay;
    soLuong = _soLuong;
    gia = _gia;
}

void SanPhamTonKho::hienThi() const {
    cout << setw(12) << ngay;
    for (const auto& sl : soLuong) {
        cout << setw(12) << sl;
    }
    for (const auto& g : gia) {
        cout << setw(12) << g;
    }
    cout << endl;
}

string SanPhamTonKho::toCSVFormat() const {
    stringstream ss;
    ss << ngay;
    for (const auto& sl : soLuong) {
        ss << "," << sl;
    }
    for (const auto& g : gia) {
        ss << "," << g;
    }
    return ss.str() + "\n";
}

QuanLyTonKho::QuanLyTonKho(const string& tenFile) {
    docTuFile(tenFile);
}

void QuanLyTonKho::docTuFile(const string& tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }

    string line, ngay;
    std::array<int, 5> soLuong, gia;

    getline(file, line); // Bỏ qua dòng tiêu đề

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, ngay, ',');
        for (int i = 0; i < 5; i++) {
            ss >> soLuong[i];
            ss.ignore();
        }
        for (int i = 0; i < 5; i++) {
            ss >> gia[i];
            if (i < 4) ss.ignore();
        }

        danhSachTonKho.emplace_back(ngay, soLuong, gia);
    }
    file.close();
}

void QuanLyTonKho::luuVaoFile(const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << endl;
        return;
    }
    file << "ngay,so_luong_A1,so_luong_A2,so_luong_A3,so_luong_A4,so_luong_A5,gia_A1,gia_A2,gia_A3,gia_A4,gia_A5\n";
    for (const auto& sanPham : danhSachTonKho) {
        file << sanPham.toCSVFormat();
    }
    file.close();
}
void QuanLyTonKho::capNhatTonKho() {
    map<string, std::array<int, 5>> tonKhoMap;

    ifstream qlnhFile("data/Qlnh_list.csv");
    string line;
    getline(qlnhFile, line);
    while (getline(qlnhFile, line)) {
        stringstream ss(line);
        int maSanPham, soLuong;
        string date;
        ss >> maSanPham;
        ss.ignore();
        ss >> line;
        ss >> soLuong;
        ss.ignore();
        ss >> line;
        ss.ignore();
        ss >> date;

        tonKhoMap[date][maSanPham - 1] += soLuong;
    }
    qlnhFile.close();

    ifstream dhbrFile("data/donhangbanra.csv");
    getline(dhbrFile, line);
    while (getline(dhbrFile, line)) {
        stringstream ss(line);
        int maSanPham, soLuong;
        string date;
        ss >> maSanPham;
        ss.ignore();
        ss >> line;
        ss >> soLuong;
        ss.ignore();
        ss >> line;
        ss.ignore();
        ss >> date;

        tonKhoMap[date][maSanPham - 1] -= soLuong;
    }
    dhbrFile.close();

    for (const auto& entry : tonKhoMap) {
        string ngay = entry.first;
        std::array<int, 5> soLuong = {0};
        for (int i = 0; i < 5; i++) {
            soLuong[i] = entry.second[i];
        }
        bool found = false;
        for (auto& sanPham : danhSachTonKho) {
            if (sanPham.ngay == ngay) {
                sanPham = SanPhamTonKho(ngay, soLuong, sanPham.gia);
                found = true;
                break;
            }
        }
        if (!found) {
            danhSachTonKho.emplace_back(ngay, soLuong, std::array<int, 5>{350000, 315000, 280000, 245000, 210000});
        }
    }

    luuVaoFile("data/tonkho.csv");
}
void QuanLyTonKho::themSanPham() {
    string ngay;
    std::array<int, 5> soLuong, gia;

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

    danhSachTonKho.emplace_back(ngay, soLuong, gia);
    luuVaoFile("data/tonkho.csv");
    cout << "San pham da duoc them thanh cong.\n";
}

void QuanLyTonKho::hienThiDanhSachTonKho() const {
    if (danhSachTonKho.empty()) {
        cout << "Khong co san pham nao trong danh sach ton kho.\n";
        return;
    }

    cout << setw(12) << "Ngay"
         << setw(12) << "S.L A1" << setw(12) << "S.L A2" << setw(12) << "S.L A3" << setw(12) << "S.L A4" << setw(12) << "S.L A5"
         << setw(12) << "Gia A1" << setw(12) << "Gia A2" << setw(12) << "Gia A3" << setw(12) << "Gia A4" << setw(12) << "Gia A5"
         << endl;
    for (const auto& sanPham : danhSachTonKho) {
        sanPham.hienThi();
    }
}

void QuanLyTonKho::suaSanPham(const string& ngay) {
    for (auto& sanPham : danhSachTonKho) {
        if (sanPham.ngay == ngay) {
            std::array<int, 5> soLuong, gia;
            for (int i = 0; i < 5; i++) {
                cout << "Nhap so luong moi cho A" << (i + 1) << ": ";
                cin >> soLuong[i];
            }
            for (int i = 0; i < 5; i++) {
                cout << "Nhap gia moi cho A" << (i + 1) << ": ";
                cin >> gia[i];
            }

            sanPham = SanPhamTonKho(ngay, soLuong, gia);
            luuVaoFile("data/tonkho.csv");
            cout << "Thong tin san pham da duoc cap nhat.\n";
            return;
        }
    }
    cout << "Khong tim thay san pham voi ngay " << ngay << endl;
}

void QuanLyTonKho::xoaSanPham(const string& ngay) {
    for (auto it = danhSachTonKho.begin(); it != danhSachTonKho.end(); ++it) {
        if (it->ngay == ngay) {
            danhSachTonKho.erase(it);
            luuVaoFile("data/tonkho.csv");
            cout << "San pham da duoc xoa.\n";
            return;
        }
    }
    cout << "Khong tim thay san pham voi ngay " << ngay << endl;
}

void QuanLyTonKho::timKiemSanPham(const string& ngay) const {
    bool timThay = false;
    cout << setw(12) << "Ngay"
         << setw(12) << "S.L A1" << setw(12) << "S.L A2" << setw(12) << "S.L A3" << setw(12) << "S.L A4" << setw(12) << "S.L A5"
         << setw(12) << "Gia A1" << setw(12) << "Gia A2" << setw(12) << "Gia A3" << setw(12) << "Gia A4" << setw(12) << "Gia A5"
         << endl;

    for (const auto& sanPham : danhSachTonKho) {
        if (sanPham.ngay == ngay) {
            sanPham.hienThi();
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay san pham.\n";
    }
}
