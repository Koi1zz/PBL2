#include "Ve.h"
#include <iostream>
using namespace std;
Ve::Ve() : user(""), idPhim(0), phong(""), ghe(""), giave(0), lichId(0), ngay(""), gio("") {}
Ve::Ve(const string& user, int idPhim, const string& phong, const string& ghe,
       int giave, int lichId, const string& ngay, const string& gio)
    : user(user), idPhim(idPhim), phong(phong), ghe(ghe),
      giave(giave), lichId(lichId), ngay(ngay), gio(gio) {}



string Ve::getUser() const { return user; }
int Ve::getIdPhim() const { return idPhim; }
string Ve::getPhong() const { return phong; }
string Ve::getGhe() const { return ghe; }
int Ve::getGiaVe() const { return giave; }
int Ve::getLichId() const { return lichId; }
string Ve::getNgay() const { return ngay; }
string Ve::getGio() const { return gio; }



void Ve::setUser(const string& user) { this->user = user; }
void Ve::setIdPhim(int idPhim) { this->idPhim = idPhim; }
void Ve::setPhong(const string& phong) { this->phong = phong; }
void Ve::setGhe(const string& ghe) { this->ghe = ghe; }
void Ve::setGiaVe(int giave) { this->giave = giave; }
void Ve::setLichId(int lichId) { this->lichId = lichId; }
void Ve::setNgay(const string& ngay) { this->ngay = ngay; }
void Ve::setGio(const string& gio) { this->gio = gio; }
void Ve::hienThi() const {
    cout << "User: " << user << " | Phim ID: " << idPhim
         << " | Phong: " << phong << " | Ghe: " << ghe
         << " | Gia: " << giave << " | " << ngay << " " << gio << "\n";
}

