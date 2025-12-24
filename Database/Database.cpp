#include "Database.h"
#include "Utility/Utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
Database& Database::getInstance() {
    static Database instance;
    return instance;
}
void Database::loadAll() {
    docTaiKhoan();
    docPhim();
    docLichChieu();
    docVe();
}
void Database::docTaiKhoan() {
    ifstream f("data/users.txt");
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        line = trim(line);
        if (line.empty()) continue;

        MyVector<string> parts;
        string part;
        istringstream ss(line);

        while (getline(ss, part, '|')) {
            parts.push_back(trim(part));
        }

        if (parts.size() >= 6) {
            try {
                UserInfo user;
                user.username = parts[0];
                user.password = parts[1];
                user.ten = parts[2];
                user.sdt = parts[3];
                user.email = parts[4];
                user.isAdmin = (parts[5] == "1");

                dsTaiKhoan.push_back(user);
            } catch (...) {}
        }
    }
    f.close();
}
void Database::docPhim() {
    ifstream f("data/movies.txt");
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        line = trim(line);
        if (line.empty()) continue;

        MyVector<string> parts;
        string part;
        istringstream ss(line);

        while (getline(ss, part, '|')) {
            parts.push_back(trim(part));
        }

        if (parts.size() < 4) continue;

        try {
            Phim p;
            for (auto &item : parts) {
                string lowerItem = toLower(item);
                if (lowerItem.find("id:") == 0) {
                    p.setId(stoi(trim(item.substr(3))));
                }
                else if (lowerItem.find("name:") == 0) {
                    p.setTen(trim(item.substr(5)));
                }
                else if (lowerItem.find("genres:") == 0) {
                    p.setTheLoai(trim(item.substr(7)));
                }
                else if (lowerItem.find("length:") == 0) {
                    p.setThoiLuong(stoi(trim(item.substr(7))));
                }
            }

            if (p.getId() != 0 && !p.getTen().empty()) {
                dsPhim.push_back(p);
            }
        } catch (...) {}
    }
    f.close();
}
void Database::docLichChieu() {
    ifstream f("data/schedules.txt");
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        line = trim(line);
        if (line.empty()) continue;

        MyVector<string> parts;
        string part;
        istringstream ss(line);

        while (getline(ss, part, '|')) {
            parts.push_back(trim(part));
        }

        if (parts.size() < 4) continue;

        try {
            LichChieu lc;
            for (auto &item : parts) {
                string lowerItem = toLower(item);
                if (lowerItem.find("idp:") == 0) {
                    lc.setId(stoi(trim(item.substr(4))));
                }
                else if (lowerItem.find("idm:") == 0) {
                    lc.setIdPhim(stoi(trim(item.substr(4))));
                }
                else if (lowerItem.find("rooms:") == 0) {
                    lc.setPhong(trim(item.substr(6)));
                }
                else if (lowerItem.find("date:") == 0) {
                    string dateTimeStr = trim(item.substr(5));
                    size_t commaPos = dateTimeStr.find(',');
                    if (commaPos != string::npos) {
                        lc.setGio(trim(dateTimeStr.substr(0, commaPos)));
                        lc.setNgay(trim(dateTimeStr.substr(commaPos + 1)));
                    } else {
                        lc.setGio("19:00");
                        lc.setNgay(dateTimeStr);
                    }
                }
            }

            if (lc.getId() != 0 && lc.getIdPhim() != 0) {
                dsLich.push_back(lc);
            }
        } catch (...) {}
    }
    f.close();
}
void Database::docVe() {
    ifstream f("data/tickets.txt");
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        line = trim(line);
        if (line.empty()) continue;

        MyVector<string> parts;
        string part;
        istringstream ss(line);

        while (getline(ss, part, '|')) {
            parts.push_back(trim(part));
        }

        if (parts.size() >= 8) {
            try {
                Ve v;
                v.setUser(parts[0]);
                v.setIdPhim(stoi(parts[1]));
                v.setPhong(parts[2]);
                v.setGhe(parts[3]);
                v.setGiaVe(stoi(parts[4]));
                v.setLichId(stoi(parts[5]));
                v.setNgay(parts[6]);
                v.setGio(parts[7]);
                dsVe.push_back(v);
            } catch (...) {}
        }
    }
    f.close();
}
void Database::savePhim() {
    ofstream f("data/movies.txt");
    if (!f.is_open()) return;

    for (auto &p : dsPhim) {
        f << "Id: " << p.getId() << " | Name: " << p.getTen()
          << " | Genres: " << p.getTheLoai() << " | Length: " << p.getThoiLuong() << "\n";
    }
    f.close();
}
void Database::saveLich() {
    ofstream f("data/schedules.txt");
    if (!f.is_open()) return;

    for (auto &lc : dsLich) {
        f << "Idp: " << lc.getId() << " | Idm: " << lc.getIdPhim()
          << " | Rooms: " << lc.getPhong() << " | Date: " << lc.getGio() << "," << lc.getNgay() << "\n";
    }
    f.close();
}
void Database::saveVe() {
    ofstream f("data/tickets.txt");
    if (!f.is_open()) return;

    for (auto &v : dsVe) {
        f << v.getUser() << "|" << v.getIdPhim() << "|" << v.getPhong() << "|" << v.getGhe() << "|"
          << v.getGiaVe() << "|" << v.getLichId() << "|" << v.getNgay() << "|" << v.getGio() << "\n";
    }
    f.close();
}
MyVector<Phim>& Database::getDsPhim() { return dsPhim; }
MyVector<LichChieu>& Database::getDsLich() { return dsLich; }
MyVector<Ve>& Database::getDsVe() { return dsVe; }
bool Database::kiemTraDangNhap(const string& username, const string& password) {
    UserInfo* user = timUser(username);

    if (user == nullptr) {
        return false;
    }

    return user->password == password;
}

bool Database::isUserAdmin(const string& username) {
    UserInfo* user = timUser(username);
    if (user == nullptr) {
        return false;
    }
    return user->isAdmin;
}
Phim* Database::findPhimById(int id) {
    for (int i = 0; i < dsPhim.size(); i++) {
        if (dsPhim[i].getId() == id) {
            return &dsPhim[i];
        }
    }
    return nullptr;
}
LichChieu* Database::findLichById(int id) {
    for (int i = 0; i < dsLich.size(); i++) {
        if (dsLich[i].getId() == id) {
            return &dsLich[i];
        }
    }
    return nullptr;
}
bool Database::isSeatAvailable(int lichId, const string& ghe) {
    for (int i = 0; i < dsVe.size(); i++) {
        if (dsVe[i].getLichId() == lichId && dsVe[i].getGhe() == ghe) {
            return false;
        }
    }
    return true;
}
MyVector<string> Database::goiYGhe(int lichId, int soLuong) {
    int seats[ROWS][COLS];
    memset(seats, 0, sizeof(seats));

    for (auto &v : dsVe) {
        if (v.getLichId() == lichId) {
            auto pr = seatToIndex(v.getGhe());
            if (pr.first >= 0 && pr.first < ROWS && pr.second >= 0 && pr.second < COLS) {
                seats[pr.first][pr.second] = 1;
            }
        }
    }
    MyVector<string> out;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c + soLuong - 1 < COLS; c++) {
            bool ok = true;
            for (int k = 0; k < soLuong; k++) {
                if (seats[r][c+k]) { ok = false; break; }
            }
            if (ok) {
                for (int k = 0; k < soLuong; k++) {
                    string s;
                    s.push_back(char('A'+r));
                    s += to_string(c+k+1);
                    out.push_back(s);
                }
                return out;
            }
        }
    }
    return out;
}
void Database::addVe(const Ve& ve) {
    dsVe.push_back(ve);
    saveVe();
}
void Database::addPhim(const Phim& phim) {
    dsPhim.push_back(phim);
    savePhim();
}
void Database::addLichChieu(const LichChieu& lich) {
    dsLich.push_back(lich);
    saveLich();
}
void Database::removePhim(int id) {
    dsPhim.removeIf([id](const Phim& p) {
        return p.getId() == id;
    });

    // Xóa lịch chiếu liên quan
    dsLich.removeIf([id](const LichChieu& lc) {
        return lc.getIdPhim() == id;
    });

    savePhim();
    saveLich();
}
MyVector<Ve> Database::getVeByUser(const string& username) {
    MyVector<Ve> result;
    for (int i = 0; i < dsVe.size(); i++) {
        if (dsVe[i].getUser() == username) {
            result.push_back(dsVe[i]);
        }
    }
    return result;
}
bool Database::taiKhoanTonTai(const string& username) {
     return timUser(username) != nullptr;
}

bool Database::sdtTonTai(const string& sdt) {
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        if (dsTaiKhoan[i].sdt == sdt) {
            return true;
        }
    }
    return false;
}

bool Database::emailTonTai(const string& email) {
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        if (dsTaiKhoan[i].email == email) {
            return true;
        }
    }
    return false;
}
bool Database::dangKyTaiKhoan(const UserInfo& userInfo) {
    if (taiKhoanTonTai(userInfo.username) ||
        sdtTonTai(userInfo.sdt) ||
        emailTonTai(userInfo.email)) {
        return false;
    }

    dsTaiKhoan.push_back(userInfo);
    luuTaiKhoan();
    return true;
}
void Database::luuTaiKhoan() {
    ofstream f("data/users.txt");
    if (!f.is_open()) return;

    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        UserInfo& user = dsTaiKhoan[i];
        f << user.username << "|" << user.password << "|" << user.ten
          << "|" << user.sdt << "|" << user.email << "|"
          << (user.isAdmin ? "1" : "0") << "\n";
    }
    f.close();
}

MyVector<UserInfo> Database::getDanhSachUser() {
    MyVector<UserInfo> result;
    for (int i = 0; i < dsTaiKhoan.size(); i++) {
        if (!dsTaiKhoan[i].isAdmin) {
            result.push_back(dsTaiKhoan[i]);
        }
    }
    return result;

}