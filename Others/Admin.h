#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
class Admin : public User {
public:
    Admin(const string& uname, Database& database);
    void themPhim();
    void xoaPhim();
    void themLichChieu();
    void hienThiLichChieu();
    void xemTatCaVe();
    void datVe() override;
    void xemVe() override;
    void xemDanhSachUser();
    void thongKe();
};

#endif
