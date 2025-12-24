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

// nhap password an
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

// kiem tra ngay co hop le hay k
bool isValidDate(const string& ngay) {
    // Lay ngay hien tai
    time_t now = time(0);
    tm* timeNow = localtime(&now);

    // Parse ngay nhap vao (dd/mm/yyyy)
    tm timeInput = {};
    istringstream ss(ngay);
    ss >> get_time(&timeInput, "%d/%m/%Y");

    if (ss.fail()) {
        return false; // Dinh dang khong hop le
    }

    // Chuyen thanh time_t de so sanh
    time_t inputTime = mktime(&timeInput);

    // So sanh: chi lay phan ngay, bo qua gio phut giay
    timeNow->tm_hour = 0;
    timeNow->tm_min = 0;
    timeNow->tm_sec = 0;
    time_t todayTime = mktime(timeNow);

    // Ngay nhap vao phai >= ngay hom nay
    return (inputTime >= todayTime);
}
bool isValidTime(const string& gio) {
    if (gio.length() != 5) return false;
    if (gio[2] != ':') return false;

    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (!isdigit(gio[i])) return false;
    }

    int hour = stoi(gio.substr(0, 2));
    int minute = stoi(gio.substr(3, 2));

    return (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59);
}
string nhapChuoiKhongRong(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        value = trim(value);

        if (!value.empty()) {
            return value;
        }
        cout << "Khong duoc de trong! Vui long nhap lai.\n";
    }
}
void drawTableLine(const MyVector<int>& columnWidths) {
    cout << "+";
    for (int i = 0; i < columnWidths.size(); i++) {
        cout << string(columnWidths[i] + 2, '-') << "+";
    }
    cout << "\n";
}

// Vẽ header của bảng
void drawTableHeader(const MyVector<string>& headers, const MyVector<int>& columnWidths) {
    cout << "|";
    for (int i = 0; i < headers.size(); i++) {
        cout << " " << setw(columnWidths[i]) << left << headers[i] << " |";
    }
    cout << "\n";
}

// Vẽ 1 hàng dữ liệu
void drawTableRow(const MyVector<string>& rowData, const MyVector<int>& columnWidths) {
    cout << "|";
    for (int i = 0; i < rowData.size(); i++) {
        string data = rowData[i];

        // Cắt chuỗi nếu quá dài
        if (data.length() > columnWidths[i]) {
            data = data.substr(0, columnWidths[i] - 3) + "...";
        }

        cout << " " << setw(columnWidths[i]) << left << data << " |";
    }
    cout << "\n";
}
void drawTable(const string& title,
               const MyVector<string>& headers,
               const MyVector<MyVector<string>>& data,
               const MyVector<int>& columnWidths) {

    // Tính tổng độ rộng bảng
    int totalWidth = 1; // Viền đầu
    for (int i = 0; i < columnWidths.size(); i++) {
        totalWidth += columnWidths[i] + 3; // width + 2 khoảng trắng + 1 viền
    }

    // In tiêu đề
    cout << "\n";
    cout << string(totalWidth, '=') << "\n";

    // Căn giữa tiêu đề
    int paddingLeft = (totalWidth - title.length()) / 2;
    cout << string(paddingLeft, ' ') << title << "\n";
    cout << string(totalWidth, '=') << "\n\n";

    // Kiểm tra dữ liệu rỗng
    if (data.empty()) {
        cout << "Khong co du lieu.\n\n";
        return;
    }

    // Vẽ bảng
    drawTableLine(columnWidths);
    drawTableHeader(headers, columnWidths);
    drawTableLine(columnWidths);

    // Vẽ từng hàng dữ liệu
    for (int i = 0; i < data.size(); i++) {
        drawTableRow(data[i], columnWidths);
    }

    drawTableLine(columnWidths);

    // Hiển thị tổng số dòng
    cout << "\nTong so: " << data.size() << "\n";
}