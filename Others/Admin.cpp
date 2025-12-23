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
    cout << "Names: ";
    getline(cin, ten);
    cout << "Genres: ";
    getline(cin, theloai);
    cout << "Lengths (Minutes): ";
    while (!(cin >> thoiluong)) {
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

    db.removePhim(id);
    cout << "Delete Successfully!\n";
}

// them Lich Chieu
void Admin::themLichChieu() {
    int id, idPhim;
    string phong, ngay, gio;

    cout << "Id Schedules: ";
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Numbers: ";
    }
    cout << "Id Movies: ";
    while (!(cin >> idPhim)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Wrong Numbers: ";
    }
    cin.ignore();
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
    cout << "\n===== Schedules =====\n";
    for (auto &lc : db.getDsLich()) {
        Phim* p = db.findPhimById(lc.getIdPhim());
        string tenPhim = p ? p->getTen() : "Unknown";

        cout << lc.getId() << " | " << tenPhim << " | " << lc.getPhong()
             << " | " << lc.getNgay() << " " << lc.getGio() << "\n";
    }
}

// xem tat ca cac ve
void Admin::xemTatCaVe() {
    cout << "\n===== List of Tickets =====\n";
    for (auto &v : db.getDsVe()) {
        Phim* p = db.findPhimById(v.getIdPhim());
        string tenPhim = p ? p->getTen() : "Unknown";
        cout << "User: " << v.getUser() << " | Phim: " << tenPhim
             << " | Rooms: " << v.getPhong() << " | Seats: " << v.getGhe()
             << " | Price: " << v.getGiaVe() << " | Date: " << v.getNgay()
             << " " << v.getGio() << "\n";
    }
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

    cout << "\n===== DANH SACH TAI KHOAN USER =====\n";
    if (dsUser.empty()) {
        cout << "Khong co tai khoan user nao!\n";
        return;
    }
    
    cout << setw(15) << left << "Username"
         << setw(20) << "Ten"
         << setw(15) << "SDT"
         << setw(25) << "Email"
         << "\n";
    cout << string(75, '-') << "\n";

    for (auto &user : dsUser) {
        cout << setw(15) << left << user.username
             << setw(20) << user.ten
             << setw(15) << user.sdt
             << setw(25) << user.email
             << "\n";
    }
}

// thong ke he thong
void Admin::thongKe() {
    cout << "\n";
    cout << string(80, '=') << "\n";
    cout << setw(45) << " " << "THONG KE HE THONG\n";
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

    // 3. Top 10 phim bán chạy nhất
    cout << "===== TOP 10 PHIM BAN CHAY NHAT =====\n";
    
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
    
    // Hiển thị top 10
    const int sttWidth = 5;
    const int tenWidth = 35;
    const int soVeWidth = 10;
    const int doanhThuWidth = 15;
    
    cout << "+";
    cout << string(sttWidth + 2, '-') << "+";
    cout << string(tenWidth + 2, '-') << "+";
    cout << string(soVeWidth + 2, '-') << "+";
    cout << string(doanhThuWidth + 2, '-') << "+\n";
    
    cout << "| " << setw(sttWidth) << left << "STT"
         << " | " << setw(tenWidth) << left << "Ten Phim"
         << " | " << setw(soVeWidth) << left << "So Ve"
         << " | " << setw(doanhThuWidth) << left << "Doanh Thu"
         << " |\n";
    
    cout << "+";
    cout << string(sttWidth + 2, '-') << "+";
    cout << string(tenWidth + 2, '-') << "+";
    cout << string(soVeWidth + 2, '-') << "+";
    cout << string(doanhThuWidth + 2, '-') << "+\n";
    
    int limit = stats.size() < 10 ? stats.size() : 10;
    for (int i = 0; i < limit; i++) {
        string ten = stats[i].tenPhim;
        if (ten.length() > tenWidth) {
            ten = ten.substr(0, tenWidth - 3) + "...";
        }
        
        cout << "| " << setw(sttWidth) << left << (i + 1)
             << " | " << setw(tenWidth) << left << ten
             << " | " << setw(soVeWidth) << left << stats[i].soVe
             << " | " << setw(doanhThuWidth) << left << stats[i].doanhThu
             << " |\n";
    }
    
    cout << "+";
    cout << string(sttWidth + 2, '-') << "+";
    cout << string(tenWidth + 2, '-') << "+";
    cout << string(soVeWidth + 2, '-') << "+";
    cout << string(doanhThuWidth + 2, '-') << "+\n";
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

