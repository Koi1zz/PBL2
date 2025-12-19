#include "LichChieu.h"
#include <iostream>
using namespace std;
LichChieu::LichChieu() : id(0), idPhim(0), phong(""), ngay(""), gio("") {}

LichChieu::LichChieu(int id, int idPhim, const string& phong, const string& ngay, const string& gio)
    : id(id), idPhim(idPhim), phong(phong), ngay(ngay), gio(gio) {}
int LichChieu::getId() const { return id; }
int LichChieu::getIdPhim() const { return idPhim; }
string LichChieu::getPhong() const { return phong; }
string LichChieu::getNgay() const { return ngay; }
string LichChieu::getGio() const { return gio; }
void LichChieu::setId(int id) { this->id = id; }
void LichChieu::setIdPhim(int idPhim) { this->idPhim = idPhim; }
void LichChieu::setPhong(const string& phong) { this->phong = phong; }
void LichChieu::setNgay(const string& ngay) { this->ngay = ngay; }
void LichChieu::setGio(const string& gio) { this->gio = gio; }
void LichChieu::hienThi() const {
    cout << id << " | Phim ID: " << idPhim << " | " << phong
         << " | " << ngay << " " << gio << "\n";
}

