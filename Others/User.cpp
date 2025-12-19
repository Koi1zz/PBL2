#include "User.h"
#include "Utility/Utils.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

User::User(const string& uname, Database& database) : username(uname), db(database) {}
User::~User() {}
string User::getUsername() const { return username; }

void drawLine(int idWidth, int tenWidth, int theLoaiWidth, int thoiLuongWidth) {
    cout << "+";
    cout << string(idWidth + 2, '-') << "+";
    cout << string(tenWidth + 2, '-') << "+";
    cout << string(theLoaiWidth + 2, '-') << "+";
    cout << string(thoiLuongWidth + 2, '-') << "+";
    cout << "\n";
}

void User::hienThiPhim() {
    cout << "\n";

    const int idWidth = 5;
    const int tenWidth = 35;
    const int theLoaiWidth = 20;
    const int thoiLuongWidth = 12;


    cout << string(80, '=') << "\n";
    cout << setw(40) << " " << "DANH SACH PHIM HIEN CO\n";
    cout << string(80, '=') << "\n\n";

    if (db.getDsPhim().empty()) {
        cout << "Khong co phim nao.\n\n";
        return;
    }

    drawLine(idWidth, tenWidth, theLoaiWidth, thoiLuongWidth);

    cout << "| " << setw(idWidth) << left << "Ma"
         << " | " << setw(tenWidth) << left << "Ten Phim"
         << " | " << setw(theLoaiWidth) << left << "The Loai"
         << " | " << setw(thoiLuongWidth) << left << "Thoi Luong"
         << " |\n";

    drawLine(idWidth, tenWidth, theLoaiWidth, thoiLuongWidth);

    for (int i = 0; i < db.getDsPhim().size(); i++) {
        Phim& p = db.getDsPhim()[i];


        string ten = p.getTen();
        if (ten.length() > tenWidth) {
            ten = ten.substr(0, tenWidth - 3) + "...";
        }

        string theLoai = p.getTheLoai();
        if (theLoai.length() > theLoaiWidth) {
            theLoai = theLoai.substr(0, theLoaiWidth - 3) + "...";
        }

        cout << "| " << setw(idWidth) << left << p.getId()
             << " | " << setw(tenWidth) << left << ten
             << " | " << setw(theLoaiWidth) << left << theLoai
             << " | " << setw(thoiLuongWidth) << left << (to_string(p.getThoiLuong()) + " phut")
             << " |\n";
    }


    drawLine(idWidth, tenWidth, theLoaiWidth, thoiLuongWidth);

    cout << "\nTong so phim: " << db.getDsPhim().size() << "\n";
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

void User::timPhim() {
    cout << "\n===== TIM KIEM PHIM =====\n";
    cout << "1. Tim theo ten phim\n";
    cout << "2. Tim theo the loai\n";
    cout << "Chon: ";
    
    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap sai! Vui long chon 1 hoac 2: ";
    }
    cin.ignore();
    
    string key;
    if (choice == 1) {
        cout << "Nhap ten phim: ";
    } else {
        cout << "Nhap the loai: ";
    }
    getline(cin, key);
    key = trim(key);
    
    if (key.empty()) {
        cout << "Khong duoc de trong!\n";
        return;
    }

    string keyLower = toLower(key);
    MyVector<Phim> ketQua;

    for (int i = 0; i < db.getDsPhim().size(); i++) {
        Phim& p = db.getDsPhim()[i];
        
        if (choice == 1) {
            // Tim theo ten
            if (toLower(p.getTen()).find(keyLower) != string::npos) {
                ketQua.push_back(p);
            }
        } else {
            // Tim theo the loai
            if (toLower(p.getTheLoai()).find(keyLower) != string::npos) {
                ketQua.push_back(p);
            }
        }
    }

    if (ketQua.empty()) {
        cout << "\nKhong tim thay phim phu hop!\n";
        return;
    }

    cout << "\n===== KET QUA TIM KIEM =====\n";
    const int idWidth = 5;
    const int tenWidth = 35;
    const int theLoaiWidth = 20;
    const int thoiLuongWidth = 12;

    drawLine(idWidth, tenWidth, theLoaiWidth, thoiLuongWidth);

    cout << "| " << setw(idWidth) << left << "Ma"
         << " | " << setw(tenWidth) << left << "Ten Phim"
         << " | " << setw(theLoaiWidth) << left << "The Loai"
         << " | " << setw(thoiLuongWidth) << left << "Thoi Luong"
         << " |\n";

    drawLine(idWidth, tenWidth, theLoaiWidth, thoiLuongWidth);

    for (int i = 0; i < ketQua.size(); i++) {
        Phim& p = ketQua[i];

        string ten = p.getTen();
        if (ten.length() > tenWidth) {
            ten = ten.substr(0, tenWidth - 3) + "...";
        }

        string theLoai = p.getTheLoai();
        if (theLoai.length() > theLoaiWidth) {
            theLoai = theLoai.substr(0, theLoaiWidth - 3) + "...";
        }

        cout << "| " << setw(idWidth) << left << p.getId()
             << " | " << setw(tenWidth) << left << ten
             << " | " << setw(theLoaiWidth) << left << theLoai
             << " | " << setw(thoiLuongWidth) << left << (to_string(p.getThoiLuong()) + " phut")
             << " |\n";
    }

    drawLine(idWidth, tenWidth, theLoaiWidth, thoiLuongWidth);
    cout << "\nTim thay " << ketQua.size() << " phim.\n";
}

int User::tinhGiaVe(const string& ngay) {
    if (isCuoiTuan(ngay) || isNgayLe(ngay)) {
        return 80000;
    }
    return 50000;
}

void User::showSeats(int lichId) {
    LichChieu* lc = db.findLichById(lichId);
    if (!lc) {
        cout << "Lich chieu khong ton tai.\n";
        return;
    }

    bool seats[ROWS][COLS] = {false};

    for (int i = 0; i < db.getDsVe().size(); i++) {
        Ve& v = db.getDsVe()[i];
        if (v.getLichId() == lichId) {
            auto pos = seatToIndex(v.getGhe());
            if (pos.first >= 0 && pos.first < ROWS && pos.second >= 0 && pos.second < COLS) {
                seats[pos.first][pos.second] = true;
            }
        }
    }

    cout << "\n===== SO DO GHE PHONG " << lc->getPhong() << " =====\n";

    Phim* p = db.findPhimById(lc->getIdPhim());
    if (p) {
        cout << "Phim: " << p->getTen() << "\n";
    }
    cout << "Ngay gio: " << lc->getNgay() << " " << lc->getGio() << "\n\n";

    cout << "      ";
    for (int c = 0; c < COLS; c++) {
        cout << setw(4) << c + 1;
    }
    cout << "\n    +" << string(COLS * 4, '-') << "+\n";

    for (int r = 0; r < ROWS; r++) {
        cout << "  " << (char)('A' + r) << " |";
        for (int c = 0; c < COLS; c++) {
            cout << setw(4) << (seats[r][c] ? "[X]" : "[ ]");
        }
        cout << " |\n";
    }
    cout << "    +" << string(COLS * 4, '-') << "+\n";
    cout << "\nChu thich: [ ] = Trong | [X] = Da dat\n";
}

void User::datVe() {
    cout << "\n===== DAT VE XEM PHIM =====\n\n";

    if (db.getDsLich().empty()) {
        cout << "Chua co lich chieu nao.\n";
        return;
    }

    const int idWidth = 5;
    const int phimWidth = 30;
    const int phongWidth = 10;
    const int ngayWidth = 12;
    const int gioWidth = 8;

    cout << "+";
    cout << string(idWidth + 2, '-') << "+";
    cout << string(phimWidth + 2, '-') << "+";
    cout << string(phongWidth + 2, '-') << "+";
    cout << string(ngayWidth + 2, '-') << "+";
    cout << string(gioWidth + 2, '-') << "+\n";

    cout << "| " << setw(idWidth) << left << "Ma"
         << " | " << setw(phimWidth) << left << "Ten Phim"
         << " | " << setw(phongWidth) << left << "Phong"
         << " | " << setw(ngayWidth) << left << "Ngay"
         << " | " << setw(gioWidth) << left << "Gio"
         << " |\n";

    cout << "+";
    cout << string(idWidth + 2, '-') << "+";
    cout << string(phimWidth + 2, '-') << "+";
    cout << string(phongWidth + 2, '-') << "+";
    cout << string(ngayWidth + 2, '-') << "+";
    cout << string(gioWidth + 2, '-') << "+\n";

    for (int i = 0; i < db.getDsLich().size(); i++) {
        LichChieu& lc = db.getDsLich()[i];
        Phim* p = db.findPhimById(lc.getIdPhim());
        string tenPhim = p ? p->getTen() : "Unknown";

        if (tenPhim.length() > phimWidth) {
            tenPhim = tenPhim.substr(0, phimWidth - 3) + "...";
        }

        cout << "| " << setw(idWidth) << left << lc.getId()
             << " | " << setw(phimWidth) << left << tenPhim
             << " | " << setw(phongWidth) << left << lc.getPhong()
             << " | " << setw(ngayWidth) << left << lc.getNgay()
             << " | " << setw(gioWidth) << left << lc.getGio()
             << " |\n";
    }

    cout << "+";
    cout << string(idWidth + 2, '-') << "+";
    cout << string(phimWidth + 2, '-') << "+";
    cout << string(phongWidth + 2, '-') << "+";
    cout << string(ngayWidth + 2, '-') << "+";
    cout << string(gioWidth + 2, '-') << "+\n\n";

    cout << "Ma lich chieu: ";
    int lichId;
    while (!(cin >> lichId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap sai! Nhap lai: ";
    }
    cin.ignore();

    LichChieu* lc = db.findLichById(lichId);
    if (!lc) {
        cout << "Lich chieu khong ton tai.\n";
        return;
    }

    int giave = tinhGiaVe(lc->getNgay());
    showSeats(lichId);

    cout << "\nGia ve: " << giave << " VND\n";
    cout << "So luong ve: ";
    int soLuong;
    while (!(cin >> soLuong) || soLuong <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap sai! Nhap lai: ";
    }
    cin.ignore();
    MyVector<string> gheGoiY = db.goiYGhe(lichId, soLuong);

    if (!gheGoiY.empty()) {
        cout << "\n===== GOI Y GHE LIEN NHAU =====\n";
        cout << "He thong goi y cac ghe ngoi lien nhau:\n";
        cout << "  ";
        for (int i = 0; i < gheGoiY.size(); i++) {
            cout << gheGoiY[i];
            if (i < gheGoiY.size() - 1) cout << ", ";
        }
        cout << "\n\n";

        // Hỏi user có muốn dùng gợi ý không
        cout << "Ban co muon dat cac ghe nay? (y/n): ";
        string choice;
        getline(cin, choice);
        choice = trim(toLower(choice));

        if (choice == "y" || choice == "yes") {
            // Kiểm tra lại các ghế có còn trống không
            bool allAvailable = true;
            for (int i = 0; i < gheGoiY.size(); i++) {
                if (!db.isSeatAvailable(lichId, gheGoiY[i])) {
                    cout << "Ghe " << gheGoiY[i] << " vua bi dat!\n";
                    allAvailable = false;
                    break;
                }
            }

            if (allAvailable) {
                // Đặt tất cả ghế gợi ý
                for (int i = 0; i < gheGoiY.size(); i++) {
                    Ve v(username, lc->getIdPhim(), lc->getPhong(), gheGoiY[i],
                         giave, lichId, lc->getNgay(), lc->getGio());
                    db.addVe(v);
                }

                cout << "\n=== DAT VE THANH CONG ===\n";
                cout << "Cac ghe: ";
                for (int i = 0; i < gheGoiY.size(); i++) {
                    cout << gheGoiY[i];
                    if (i < gheGoiY.size() - 1) cout << ", ";
                }
                cout << "\nTong tien: " << giave * soLuong << " VND\n";
                return;
            }
        }
    } else {
        cout << "\n Khong con " << soLuong << " ghe lien nhau trong!\n";
        cout << "Ban vui long chon tung ghe rieng le.\n\n";
    }

     cout << "\n===== CHON GHE THU CONG =====\n";
    MyVector<string> gheChon;
    for (int i = 0; i < soLuong; i++) {
        string ghe;
        while (true) {
            cout << "Ghe thu " << (i + 1) << " (vd: A1): ";
            getline(cin, ghe);
            ghe = trim(ghe);

            auto pos = seatToIndex(ghe);
            if (pos.first == -1) {
                cout << "Sai dinh dang!\n";
                continue;
            }

            if (!db.isSeatAvailable(lichId, ghe)) {
                cout << "Ghe da duoc dat! Chon ghe khac.\n";
                continue;
            }

            break;
        }
        gheChon.push_back(ghe);
    }

    for (int i = 0; i < gheChon.size(); i++) {
        Ve v(username, lc->getIdPhim(), lc->getPhong(), gheChon[i],
             giave, lichId, lc->getNgay(), lc->getGio());
        db.addVe(v);
    }

    cout << "\n=== DAT VE THANH CONG ===\n";
    cout << "Tong tien: " << giave * soLuong << " VND\n";
}

void User::xemVe() {
    MyVector<Ve> userVe = db.getVeByUser(username);

    cout << "\n===== VE CUA BAN =====\n\n";
    if (userVe.empty()) {
        cout << "Ban chua dat ve nao.\n";
        return;
    }

    const int sttWidth = 4;
    const int phimWidth = 25;
    const int phongWidth = 8;
    const int gheWidth = 6;
    const int giaWidth = 10;
    const int ngayWidth = 12;
    const int gioWidth = 8;

    cout << "+";
    cout << string(sttWidth + 2, '-') << "+";
    cout << string(phimWidth + 2, '-') << "+";
    cout << string(phongWidth + 2, '-') << "+";
    cout << string(gheWidth + 2, '-') << "+";
    cout << string(giaWidth + 2, '-') << "+";
    cout << string(ngayWidth + 2, '-') << "+";
    cout << string(gioWidth + 2, '-') << "+\n";

    cout << "| " << setw(sttWidth) << left << "STT"
         << " | " << setw(phimWidth) << left << "Phim"
         << " | " << setw(phongWidth) << left << "Phong"
         << " | " << setw(gheWidth) << left << "Ghe"
         << " | " << setw(giaWidth) << left << "Gia"
         << " | " << setw(ngayWidth) << left << "Ngay"
         << " | " << setw(gioWidth) << left << "Gio"
         << " |\n";

    cout << "+";
    cout << string(sttWidth + 2, '-') << "+";
    cout << string(phimWidth + 2, '-') << "+";
    cout << string(phongWidth + 2, '-') << "+";
    cout << string(gheWidth + 2, '-') << "+";
    cout << string(giaWidth + 2, '-') << "+";
    cout << string(ngayWidth + 2, '-') << "+";
    cout << string(gioWidth + 2, '-') << "+\n";

    int totalCost = 0;
    for (int i = 0; i < userVe.size(); i++) {
        Ve& v = userVe[i];
        Phim* p = db.findPhimById(v.getIdPhim());
        string tenPhim = p ? p->getTen() : "Unknown";

        if (tenPhim.length() > phimWidth) {
            tenPhim = tenPhim.substr(0, phimWidth - 3) + "...";
        }

        cout << "| " << setw(sttWidth) << left << (i+1)
             << " | " << setw(phimWidth) << left << tenPhim
             << " | " << setw(phongWidth) << left << v.getPhong()
             << " | " << setw(gheWidth) << left << v.getGhe()
             << " | " << setw(giaWidth) << left << v.getGiaVe()
             << " | " << setw(ngayWidth) << left << v.getNgay()
             << " | " << setw(gioWidth) << left << v.getGio()
             << " |\n";

        totalCost += v.getGiaVe();
    }

    cout << "+";
    cout << string(sttWidth + 2, '-') << "+";
    cout << string(phimWidth + 2, '-') << "+";
    cout << string(phongWidth + 2, '-') << "+";
    cout << string(gheWidth + 2, '-') << "+";
    cout << string(giaWidth + 2, '-') << "+";
    cout << string(ngayWidth + 2, '-') << "+";
    cout << string(gioWidth + 2, '-') << "+\n";

    cout << "\nTong so ve: " << userVe.size() << "\n";
    cout << "Tong chi phi: " << totalCost << " VND\n";
}
