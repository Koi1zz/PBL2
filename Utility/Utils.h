#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "MyVector.h"
using namespace std;

const int ROWS = 5;
const int COLS = 6;

// Struct luu tru thong tin ngay le
struct NgayLeInfo {
    string ngay;    // dd/mm (vd: "01/01")
    string ten;     // Ten ngay le (vd: "Tet Duong Lich")

    NgayLeInfo() {}
    NgayLeInfo(const string& n, const string& t) : ngay(n), ten(t) {}
};

// Danh sach ngay le
extern MyVector<NgayLeInfo> danhSachNgayLe;

// Khoi tao danh sach ngay le
void khoiTaoNgayLe();

// Xu ly chuoi
string trim(const string& s);
string toLower(const string& s);

// Xu ly ngay
bool isCuoiTuan(const string& ngay);
bool isNgayLe(const string& ngay);

// Xu ly ghe
pair<int, int> seatToIndex(const string& seat);
string nhapPassword();

// Kiem tra ngay co hop le hay k
bool isValidDate(const string& date);
bool isValidTime(const string& gio);

// ve duong ngang
string nhapChuoiKhongRong(const string& prompt);

void drawTableLine(const MyVector<int>& columnWidths);

// Ve header bang
void drawTableHeader(const MyVector<string>& headers, const MyVector<int>& columnWidths);

// Ve 1 hang du lieu
void drawTableRow(const MyVector<string>& rowData, const MyVector<int>& columnWidths);

void drawTable(const string& title,
               const MyVector<string>& headers,
               const MyVector<MyVector<string>>& data,
               const MyVector<int>& columnWidths);
#endif