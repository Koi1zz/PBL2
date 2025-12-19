#include "Phim.h"
#include <iostream>
using namespace std;

Phim::Phim() : id(0), ten(""), theloai(""), thoiluong(0) {}
Phim::Phim(int id, const string& ten, const string& theloai, int thoiluong)
    : id(id), ten(ten), theloai(theloai), thoiluong(thoiluong) {}

int Phim::getId() const { return id; }
string Phim::getTen() const { return ten; }
string Phim::getTheLoai() const { return theloai; }
int Phim::getThoiLuong() const { return thoiluong; }

void Phim::setId(int id) { this->id = id; }
void Phim::setTen(const string& ten) { this->ten = ten; }
void Phim::setTheLoai(const string& theloai) { this->theloai = theloai; }
void Phim::setThoiLuong(int thoiluong) { this->thoiluong = thoiluong; }

void Phim::hienThi() const {
    cout << id << " | " << ten << " | " << theloai << " | " << thoiluong << " Min\n";
}

