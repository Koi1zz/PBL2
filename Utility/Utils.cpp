#include "Utils.h"
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif
#include <iostream>
using namespace std;

// Khai bao bien toan cuc
MyVector<NgayLeInfo> danhSachNgayLe;

// Ham khoi tao danh sach ngay le
void khoiTaoNgayLe() {

    static bool daKhoiTao = false;
    if (daKhoiTao) return;

    danhSachNgayLe.push_back(NgayLeInfo("01/01", "Tet Duong Lich"));
    danhSachNgayLe.push_back(NgayLeInfo("30/04", "Ngay Giai Phong Mien Nam"));
    danhSachNgayLe.push_back(NgayLeInfo("01/05", "Ngay Quoc Te Lao Dong"));
    danhSachNgayLe.push_back(NgayLeInfo("02/09", "Ngay Quoc Khanh"));

    daKhoiTao = true;
}

// Xoa khoang trang
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Chuyen chu thuong
string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Kiem tra cuoi tuan
bool isCuoiTuan(const string& ngay) {
    tm timeStruct = {};
    string s = ngay + " 00:00:00";
    istringstream ss(s);
    ss >> get_time(&timeStruct, "%d/%m/%Y %H:%M:%S");
    if (ss.fail()) return false;

    time_t t = mktime(&timeStruct);
    if (t == -1) return false;

    tm* timeInfo = localtime(&t);
    int w = timeInfo->tm_wday;
    return (w == 0 || w == 6);  // 0=Chu nhat, 6=Thu bay
}

// Kiem tra ngay le
bool isNgayLe(const string& ngay) {
    // Khoi tao danh sach neu chua co
    khoiTaoNgayLe();

    if (ngay.size() < 5) return false;

    string dm = ngay.substr(0, 5);  // Lay dd/mm

    // Duyet qua MyVector de tim
    for (int i = 0; i < danhSachNgayLe.size(); i++) {
        if (danhSachNgayLe[i].ngay == dm) {
            return true;
        }
    }

    return false;
}

// Chuyen ten ghe thanh chi so
pair<int, int> seatToIndex(const string& seat) {
    string seatTrim = trim(seat);
    if (seatTrim.size() < 2) return {-1, -1};

    char rowChar = toupper(seatTrim[0]);
    if (rowChar < 'A' || rowChar > 'Z') return {-1, -1};

    string colStr = seatTrim.substr(1);
    for (char c : colStr) {
        if (!isdigit(c)) return {-1, -1};
    }

    try {
        int col = stoi(colStr) - 1;
        int row = rowChar - 'A';

        if (row < 0 || row >= ROWS) return {-1, -1};
        if (col < 0 || col >= COLS) return {-1, -1};

        return {row, col};
    } catch (...) {
        return {-1, -1};
    }
}
string nhapPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) {
            cout << endl;
            break;
        }
        else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += ch;
            cout << '*';
        }
    }

    return password;
}