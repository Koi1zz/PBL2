#include "Admin.h"
#include "Utility/Utils.h"
#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;
Admin::Admin(const string& uname, Database& database) : User(uname, database) {}

// Them phim moi
void Admin::themPhim() {
    int id, thoiluong;
    string ten, theloai;
    cout << "Id movies: ";
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Numbers: ";
    }
    cin.ignore();
    Phim* phimTrung = db.findPhimById(id);
    if (phimTrung != nullptr) {
        cout << "Trung ID voi phim \"" << phimTrung->getTen()
             << "\" da co!\n";
        cout << "Vui long chon ID khac.\n";
        return;
    }
    ten = nhapChuoiKhongRong("Names: ");
    theloai = nhapChuoiKhongRong("Genres: ");
    cout << "Lengths (Minutes): ";
    while (!(cin >> thoiluong|| thoiluong <= 0)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Choice: ";
    }
    cin.ignore();

    Phim p(id, ten, theloai, thoiluong);
    db.addPhim(p);
    cout << "Adding Successfully!\n";
}

// Xoa phim
void Admin::xoaPhim() {
    cout << "Id you want to remove: ";
    int id;
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Numbers: ";
    }
    cin.ignore();
    Phim* phim = db.findPhimById(id);
    if (phim == nullptr) {
        cout << "Khong co phim nay de xoa!\n";
        cout << "Vui long kiem tra lai ID.\n";
        return;
    }
    cout << "\nThong tin phim se xoa:\n";
    cout << "Ten: " << phim->getTen() << "\n";
    cout << "The loai: " << phim->getTheLoai() << "\n";

    cout << "\nBan co chac chan muon xoa? (y/n): ";
    string confirm;
    cin >> confirm;
    cin.ignore();
    if (toLower(trim(confirm)) != "y" && toLower(trim(confirm)) != "yes") {
        cout << "Da huy thao tac xoa.\n";
        return;
    }
    db.removePhim(id);
    cout << "Delete Successfully!\n";
}

// them Lich Chieu
void Admin::themLichChieu() {
    cout << "\n===== DANH SACH PHIM =====\n";
    for (int i = 0; i < db.getDsPhim().size(); i++) {
        Phim& p = db.getDsPhim()[i];
        cout << "ID: " << p.getId() << " - " << p.getTen() << "\n";
    }
    cout << "\n";

    int id, idPhim;
    string phong, ngay, gio;

    cout << "Id Schedules: ";
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Numbers: ";
    }

    LichChieu* lichKiemTra = db.findLichById(id);
    if (lichKiemTra != nullptr) {
        cout << "ID lich chieu " << id << " da ton tai!\n";
        cout << "Vui long chon ID khac.\n";
        return;
    }

    cout << "Id Movies: ";
    while (!(cin >> idPhim)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Numbers: ";
    }
    cin.ignore();

    // KIỂM TRA PHIM CÓ TỒN TẠI KHÔNG
    Phim* phimKiemTra = db.findPhimById(idPhim);
    if (phimKiemTra == nullptr) {
        cout << "Khong co phim co ID " << idPhim << " trong danh sach phim hien co!\n";
        cout << "Vui long kiem tra lai danh sach phim truoc khi tao lich chieu.\n";
        return;
    }

    cout << "Rooms: ";
    getline(cin, phong);
    cout << "Date (dd/mm/yyyy): ";
    getline(cin, ngay);

    if (!isValidDate(ngay)) {
        cout << "Ngay khong hop le! Khong the tao lich chieu trong qua khu.\n";
        return;
    }

    cout << "Times (hh:mm): ";
    getline(cin, gio);
    if (!isValidTime(gio)) {
    cout << "Gio khong hop le! Vui long nhap dung dinh dang hh:mm (vd: 09:00)\n";
    return;
}
    for (auto &lich : db.getDsLich()) {
        if (lich.getPhong() == phong && lich.getNgay() == ngay && lich.getGio() == gio) {
            cout << "Existed!\n";
            return;
        }
    }
    LichChieu lc(id, idPhim, phong, ngay, gio);
    db.addLichChieu(lc);
    cout << "Adding Successfully!\n";
}

// hien thi lich
void Admin::hienThiLichChieu() {
    // Chuẩn bị headers
    MyVector<string> headers;
    headers.push_back("ID");
    headers.push_back("Ten Phim");
    headers.push_back("Phong");
    headers.push_back("Ngay");
    headers.push_back("Gio");

    // Chuẩn bị độ rộng cột
    MyVector<int> columnWidths;
    columnWidths.push_back(5);   // ID
    columnWidths.push_back(35);  // Tên phim
    columnWidths.push_back(8);   // Phòng
    columnWidths.push_back(12);  // Ngày
    columnWidths.push_back(8);   // Giờ

    // Chuẩn bị dữ liệu
    MyVector<MyVector<string>> data;
    for (int i = 0; i < db.getDsLich().size(); i++) {
        LichChieu& lc = db.getDsLich()[i];
        Phim* p = db.findPhimById(lc.getIdPhim());
        string tenPhim = p ? p->getTen() : "Unknown";

        MyVector<string> row;
        row.push_back(to_string(lc.getId()));
        row.push_back(tenPhim);
        row.push_back(lc.getPhong());
        row.push_back(lc.getNgay());
        row.push_back(lc.getGio());

        data.push_back(row);
    }

    drawTable("DANH SACH LICH CHIEU", headers, data, columnWidths);
}

void Admin::xemTatCaVe() {
    MyVector<string> headers;
    headers.push_back("User");
    headers.push_back("Phim");
    headers.push_back("Phong");
    headers.push_back("Ghe");
    headers.push_back("Gia");
    headers.push_back("Ngay");
    headers.push_back("Gio");
    MyVector<int> columnWidths;
    columnWidths.push_back(12);  // User
    columnWidths.push_back(30);  // Phim
    columnWidths.push_back(8);   // Phòng
    columnWidths.push_back(6);   // Ghế
    columnWidths.push_back(10);  // Giá
    columnWidths.push_back(12);  // Ngày
    columnWidths.push_back(8);   // Giờ

    // Chuẩn bị dữ liệu
    MyVector<MyVector<string>> data;
    for (int i = 0; i < db.getDsVe().size(); i++) {
        Ve& v = db.getDsVe()[i];
        Phim* p = db.findPhimById(v.getIdPhim());
        string tenPhim = p ? p->getTen() : "Unknown";

        MyVector<string> row;
        row.push_back(v.getUser());
        row.push_back(tenPhim);
        row.push_back(v.getPhong());
        row.push_back(v.getGhe());
        row.push_back(to_string(v.getGiaVe()));
        row.push_back(v.getNgay());
        row.push_back(v.getGio());

        data.push_back(row);
    }

    // Gọi hàm vẽ bảng
    drawTable("DANH SACH TAT CA VE DA DAT", headers, data, columnWidths);
}

// dat ve (chi admin xem duoc)
void Admin::datVe() {
    cout << "Admin Only.\n";
}

// xem ve (chi danh cho admin)
void Admin::xemVe() {
    cout << "Admin Only.\n";
}

// xem tat ca user
void Admin::xemDanhSachUser() {
    MyVector<UserInfo> dsUser = db.getDanhSachUser();

    MyVector<string> headers;
    headers.push_back("Username");
    headers.push_back("Ten");
    headers.push_back("SDT");
    headers.push_back("Email");

    MyVector<int> columnWidths;
    columnWidths.push_back(15);  // Username
    columnWidths.push_back(25);  // Tên
    columnWidths.push_back(15);  // SDT
    columnWidths.push_back(30);  // Email

    MyVector<MyVector<string>> data;
    for (int i = 0; i < dsUser.size(); i++) {
        MyVector<string> row;
        row.push_back(dsUser[i].username);
        row.push_back(dsUser[i].ten);
        row.push_back(dsUser[i].sdt);
        row.push_back(dsUser[i].email);

        data.push_back(row);
    }
    drawTable("DANH SACH TAI KHOAN USER", headers, data, columnWidths);
}

// thong ke he thong
void Admin::thongKe() {
    cout << "\n";
    cout << string(80, '=') << "\n";
    cout << setw(35) << " " << "THONG KE HE THONG\n";
    cout << string(80, '=') << "\n\n";

    // 1. Thống kê tổng quan
    int tongPhim = db.getDsPhim().size();
    int tongLichChieu = db.getDsLich().size();
    int tongVe = db.getDsVe().size();
    int tongUser = db.getDanhSachUser().size();

    cout << "===== TONG QUAN =====\n";
    cout << "Tong so phim:        " << tongPhim << "\n";
    cout << "Tong so lich chieu:  " << tongLichChieu << "\n";
    cout << "Tong so ve da ban:   " << tongVe << "\n";
    cout << "Tong so user:        " << tongUser << "\n\n";

    // 2. Doanh thu
    int tongDoanhThu = 0;
    for (int i = 0; i < db.getDsVe().size(); i++) {
        tongDoanhThu += db.getDsVe()[i].getGiaVe();
    }
    cout << "===== DOANH THU =====\n";
    cout << "Tong doanh thu:      " << tongDoanhThu << " VND\n";
    cout << "Doanh thu trung binh/ve: " << (tongVe > 0 ? tongDoanhThu / tongVe : 0) << " VND\n\n";

    // Đếm số vé cho mỗi phim
    struct PhimStats {
        int idPhim;
        string tenPhim;
        int soVe;
        int doanhThu;
    };

    MyVector<PhimStats> stats;

    for (int i = 0; i < db.getDsPhim().size(); i++) {
        Phim& p = db.getDsPhim()[i];
        PhimStats ps;
        ps.idPhim = p.getId();
        ps.tenPhim = p.getTen();
        ps.soVe = 0;
        ps.doanhThu = 0;

        // Đếm vé
        for (int j = 0; j < db.getDsVe().size(); j++) {
            if (db.getDsVe()[j].getIdPhim() == p.getId()) {
                ps.soVe++;
                ps.doanhThu += db.getDsVe()[j].getGiaVe();
            }
        }

        if (ps.soVe > 0) {
            stats.push_back(ps);
        }
    }

    // Sắp xếp giảm dần theo số vé (bubble sort)
    for (int i = 0; i < stats.size() - 1; i++) {
        for (int j = 0; j < stats.size() - i - 1; j++) {
            if (stats[j].soVe < stats[j + 1].soVe) {
                PhimStats temp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = temp;
            }
        }
    }
    MyVector<string> headers;
    headers.push_back("STT");
    headers.push_back("Ten Phim");
    headers.push_back("So Ve");
    headers.push_back("Doanh Thu");

    MyVector<int> columnWidths;
    columnWidths.push_back(5);
    columnWidths.push_back(35);
    columnWidths.push_back(10);
    columnWidths.push_back(15);

    MyVector<MyVector<string>> data;
    int limit = stats.size() < 10 ? stats.size() : 10;

    for (int i = 0; i < limit; i++) {
        MyVector<string> row;
        row.push_back(to_string(i + 1));
        row.push_back(stats[i].tenPhim);
        row.push_back(to_string(stats[i].soVe));
        row.push_back(to_string(stats[i].doanhThu) + " VND");

        data.push_back(row);
    }
    drawTable("TOP 10 PHIM BAN CHAY NHAT", headers, data, columnWidths);

    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

