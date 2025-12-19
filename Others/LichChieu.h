#ifndef LICHCHIEU_H
#define LICHCHIEU_H
#include <string>
using namespace std;
class LichChieu {
private:
    int id;
    int idPhim;
    string phong;
    string ngay;
    string gio;
public:
    LichChieu();
    LichChieu(int id, int idPhim, const string& phong, const string& ngay, const string& gio);
    int getId() const;
    int getIdPhim() const;
    string getPhong() const;
    string getNgay() const;
    string getGio() const;
    void setId(int id);
    void setIdPhim(int idPhim);
    void setPhong(const string& phong);
    void setNgay(const string& ngay);
    void setGio(const string& gio);
    void hienThi() const;
};

#endif
