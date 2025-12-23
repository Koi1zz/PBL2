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
string nhapPassword();  // Nháº­p password áº©n
#endif