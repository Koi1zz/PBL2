#ifndef VE_H
#define VE_H
#include <string>
using namespace std;
class Ve {
private:
    string user;
    int idPhim;
    string phong;
    string ghe;
    int giave;
    int lichId;
    string ngay;
    string gio;
public:
    Ve();
    Ve(const string& user, int idPhim, const string& phong, const string& ghe,
       int giave, int lichId, const string& ngay, const string& gio);
    string getUser() const;
    int getIdPhim() const;
    string getPhong() const;
    string getGhe() const;
    int getGiaVe() const;
    int getLichId() const;
    string getNgay() const;
    string getGio() const;
    void setUser(const string& user);
    void setIdPhim(int idPhim);
    void setPhong(const string& phong);
    void setGhe(const string& ghe);
    void setGiaVe(int giave);
    void setLichId(int lichId);
    void setNgay(const string& ngay);
    void setGio(const string& gio);
    void hienThi() const;
};

#endif


