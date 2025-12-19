#ifndef DATABASE_H
#define DATABASE_H
#include "Others/Phim.h"
#include "Others/Ve.h"
#include "Others/LichChieu.h"
#include "Utility/MyVector.h"
#include <string>
using namespace std;

struct UserInfo {
    string username;
    string password;
    string ten;
    string sdt;
    string email;
    bool isAdmin;

    UserInfo() : isAdmin(false) {}
    UserInfo(const string& uname, const string& pwd, const string& name,
             const string& phone, const string& mail, bool admin = false)
        : username(uname), password(pwd), ten(name), sdt(phone), email(mail), isAdmin(admin) {}
};

class Database
{
private:
    MyVector<UserInfo> dsTaiKhoan;  // ← Mảng động các UserInfo
    MyVector<Phim> dsPhim;
    MyVector<LichChieu> dsLich;
    MyVector<Ve> dsVe;

    Database(){};
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    UserInfo* timUser(const string& username) {
        for (int i = 0; i < dsTaiKhoan.size(); i++) {
            if (dsTaiKhoan[i].username == username) {
                return &dsTaiKhoan[i];  // Trả về con trỏ nếu tìm thấy
            }
        }
        return nullptr;  // Không tìm thấy
    }
public:
    static Database& getInstance();
    void loadAll();
    void docTaiKhoan();
    void docPhim();
    void docLichChieu();
    void docVe();
    void savePhim();
    void saveLich();
    void saveVe();
    void luuTaiKhoan();

    MyVector<Phim>& getDsPhim();
    MyVector<LichChieu>& getDsLich();
    MyVector<Ve>& getDsVe();
    MyVector<UserInfo> getDanhSachUser();

    bool kiemTraDangNhap(const string& username, const string& password);
    bool isUserAdmin(const string& username);
    Phim* findPhimById(int id);
    LichChieu* findLichById(int id);
    bool isSeatAvailable(int lichId, const string& ghe);
    MyVector<string> goiYGhe(int lichId, int soLuong);

    void addVe(const Ve& ve);
    void addPhim(const Phim& phim);
    void addLichChieu(const LichChieu& lich);
    void removePhim(int id);

    MyVector<Ve> getVeByUser(const string& username);

    // Các phương thức quản lý user
    bool taiKhoanTonTai(const string& username);
    bool sdtTonTai(const string& sdt);
    bool emailTonTai(const string& email);
    bool dangKyTaiKhoan(const UserInfo& userInfo);
//    vector<UserInfo> getDanhSachUser();
};
#endif // DATABASE_H
