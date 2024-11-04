#ifndef TONKHO_H
#define TONKHO_H

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

class SanPhamTonKho {
public:
    string ngay;
    std::array<int, 5> soLuong;
    std::array<int, 5> gia;

    SanPhamTonKho(string _ngay, const std::array<int, 5>& _soLuong, const std::array<int, 5>& _gia);

    void hienThi() const;
    string toCSVFormat() const;
};

class QuanLyTonKho {
private:
    vector<SanPhamTonKho> danhSachTonKho;

    void docTuFile(const string& tenFile);
    void luuVaoFile(const string& tenFile);
    void capNhatTonKho();

public:
    QuanLyTonKho(const string& tenFile);

    void themSanPham();
    void hienThiDanhSachTonKho() const;
    void suaSanPham(const string& ngay);
    void xoaSanPham(const string& ngay);
    void timKiemSanPham(const string& ngay) const;
};

#endif // TONKHO_H