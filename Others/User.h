#ifndef USER_H
#define USER_H
#include "Database/Database.h"
#include <string>
using namespace std;
class User
{
protected:
    string username;
    Database& db;
public:
    User(const string& uname, Database& database);
    virtual ~User();
    string getUsername() const;
    void hienThiPhim();
    void timPhim();
    int tinhGiaVe(const string& ngay);
    void showSeats(int lichId);
    virtual void datVe();
    virtual void xemVe();
};
#endif // USER_H

