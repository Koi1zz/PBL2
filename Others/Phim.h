#ifndef PHIM_H
#define PHIM_H
#include <string>
using namespace std;

class Phim {
private:
    int id;
    string ten;
    string theloai;
    int thoiluong;

public:
    Phim();
    Phim(int id, const string& ten, const string& theloai, int thoiluong);
    int getId() const;
    string getTen() const;
    string getTheLoai() const;
    int getThoiLuong() const;
    void setId(int id);
    void setTen(const string& ten);
    void setTheLoai(const string& theloai);
    void setThoiLuong(int thoiluong);
    void hienThi() const;
};

#endif

