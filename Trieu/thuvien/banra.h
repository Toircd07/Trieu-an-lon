#ifndef BANRA_H
#define BANRA_H

#include<vector>
#include<string>

using namespace std;

class DonHang {
public:
    string ngay;         // Ngày
    int soLuong[5];      // Số lượng cho 5 loại
    int gia[5];          // Giá cho 5 loại

    // Hàm khởi tạo đối tượng
    DonHang(string _ngay, int _soLuong[], int _gia[]);

    // Phương thức hiển thị thông tin đơn hàng
    void hienThi() const;

    // Hàm lưu thông tin vào file
    string toCSVFormat() const;
};

class QuanLyDonHang {
private:
    vector<DonHang> danhSachDonHang;

    // Hàm đọc dữ liệu từ file CSV
    void docTuFile(const string& tenFile);

    // Hàm ghi dữ liệu vào file CSV
    void luuVaoFile(const string& tenFile);

    // Phương thức cập nhật dữ liệu từ file Costumer (2).csv
    void capNhatDonHangTuFile(const string& tenFile);

    // Phương thức lưu danh sách đơn hàng vào file donhangbanra.csv
    void luuDanhSachDonHang(const string& tenFile);

public:
    // Hàm khởi tạo
    QuanLyDonHang(const string& tenFile);

    // Hàm thêm đơn hàng
    void themDonHang();

    // Hiển thị danh sách đơn hàng
    void hienThiDanhSachDonHang() const;

    // Sửa thông tin đơn hàng
    void suaDonHang(const string& ngay);

    // Hàm xóa đơn hàng
    void xoaDonHang(const string& ngay);

    // Tìm kiếm đơn hàng
    void timKiemDonHang(const string& ngay) const;

    // Phương thức cập nhật dữ liệu
    void capNhatDuLieu();
};

#endif // BANRA_H