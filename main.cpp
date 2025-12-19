#include "Database/Database.h"
#include "Others/User.h"
#include "Others/Admin.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
    Database& db = Database::getInstance();
    db.loadAll();

    while (true) {
        cout << "\n========================================\n";
        cout << "     HE THONG QUAN LY RAP CHIEU PHIM\n";
        cout << "========================================\n";
        cout << "1. DANG NHAP\n";
        cout << "2. DANG KY TAI KHOAN\n";
        cout << "3. THOAT\n";
        cout << "========================================\n";
        cout << "Chon chuc nang: ";

        int choice;
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap sai! Vui long nhap lai: ";
        }
        cin.ignore();

        switch (choice) {
            case 1: {
                string username, password;
                cout << "\n============= MENU LOGIN ==============="<< endl;
                cout << "Username : ";
                cin >> username;

                cout << "Password: ";
                cin >> password;

                if (!db.kiemTraDangNhap(username, password)) {
                    cout << "\nDang nhap that bai! Sai username hoac password.\n";
                    continue;
                }

                cout << "\n Dang nhap thanh cong! Chao mung " << username << "!\n";

                bool shouldLogout = false;

                if (db.isUserAdmin(username)) {
                    Admin admin(username, db);
                    int adminChoice;
                    while (!shouldLogout) {
                        cout << "\n========================================\n";
                        cout << "          MENU ADMIN\n";
                        cout << "========================================\n";
                        cout << "1. Xem Danh Sach Phim\n";
                        cout << "2. Them Phim Moi\n";
                        cout << "3. Xoa Phim\n";
                        cout << "4. Them Lich Chieu\n";
                        cout << "5. Xem Lich Chieu\n";
                        cout << "6. Xem Tat Ca Ve Da Dat\n";
                        cout << "7. Dang ky tai khoan Admin\n";
                        cout << "8. Xem Danh Sach User\n";
                        cout << "9. Thong Ke\n";
                        cout << "10. Logout (Dang xuat)\n";
                        cout << "0. Thoat chuong trinh\n";
                        cout << "========================================\n";
                        cout << "Chon chuc nang: ";

                        while (!(cin >> adminChoice)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nhap sai! Vui long nhap lai: ";
                        }
                        cin.ignore();

                        switch (adminChoice) {
                            case 1:
                                admin.hienThiPhim();
                                break;
                            case 2:
                                admin.themPhim();
                                break;
                            case 3:
                                admin.xoaPhim();
                                break;
                            case 4:
                                admin.themLichChieu();
                                break;
                            case 5:
                                admin.hienThiLichChieu();
                                break;
                            case 6:
                                admin.xemTatCaVe();
                                break;
                            case 7: {
                                UserInfo newAdmin;
                                cout << "\n============ DANG KY TAI KHOAN ADMIN ============" << endl;

                                cout << "Ten: ";
                                getline(cin, newAdmin.ten);

                                cout << "SDT: ";
                                getline(cin, newAdmin.sdt);

                                cout << "Email: ";
                                getline(cin, newAdmin.email);

                                cout << "Username: ";
                                getline(cin, newAdmin.username);

                                string password, confirmPassword;
                                cout << "Password: ";
                                getline(cin, password);

                                cout << "Xac nhan password: ";
                                getline(cin, confirmPassword);

                                if (password != confirmPassword) {
                                    cout << "Password xac nhan khong khop!\n";
                                    break;
                                }

                                newAdmin.password = password;
                                newAdmin.isAdmin = true;

                                if (db.dangKyTaiKhoan(newAdmin)) {
                                    cout << "Dang ky tai khoan ADMIN thanh cong!\n";
                                } else {
                                    cout << "Dang ky that bai! Username, SDT hoac Email da ton tai.\n";
                                }
                                break;
                            }
                            case 8:
                                admin.xemDanhSachUser();
                                break;
                            case 9:
                                admin.thongKe();
                                break;
                            case 10:
                                cout << "\n Dang xuat\n";
                                shouldLogout = true;
                                break;
                            case 0:
                                return 0;
                            default:
                                cout << "\n Lua chon khong hop le!\n";
                        }
                    }

                } else {
                    User user(username, db);
                    int userChoice;

                    while (!shouldLogout) {
                        cout << "\n========================================\n";
                        cout << "          MENU USER\n";
                        cout << "========================================\n";
                        cout << "1. Xem Danh Sach Phim\n";
                        cout << "2. Tim Kiem Phim\n";
                        cout << "3. Dat Ve Xem Phim\n";
                        cout << "4. Xem Ve Da Dat\n";
                        cout << "5. Logout (Dang xuat)\n";
                        cout << "0. Thoat chuong trinh\n";
                        cout << "========================================\n";
                        cout << "Chon chuc nang: ";

                        while (!(cin >> userChoice)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nhap sai! Vui long nhap lai: ";
                        }
                        cin.ignore();

                        switch (userChoice) {
                            case 1:
                                user.hienThiPhim();
                                break;
                            case 2:
                                user.timPhim();
                                break;
                            case 3:
                                user.datVe();
                                break;
                            case 4:
                                user.xemVe();
                                break;
                            case 5:
                                cout << "\n Dang xuat....\n";
                                shouldLogout = true;
                                break;
                            case 0:
                                return 0;
                            default:
                                cout << "\n Lua chon khong hop le!\n";
                        }
                    }
                }
                break;
            }
            case 2: {
                UserInfo newUser;
                cout << "\n============ DANG KY TAI KHOAN USER ============" << endl;
                cout << "Ten: ";
                getline(cin, newUser.ten);
                cout << "SDT: ";
                getline(cin, newUser.sdt);
                cout << "Email: ";
                getline(cin, newUser.email);
                cout << "Username: ";
                getline(cin, newUser.username);
                string password, confirmPassword;
                cout << "Password: ";
                getline(cin, password);
                cout << "Xac nhan password: ";
                getline(cin, confirmPassword);

                if (newUser.ten.empty() || newUser.sdt.empty() || newUser.email.empty() ||
                    newUser.username.empty() || password.empty()) {
                    cout << "Khong de trong thong tin!\n";
                    break;
                }

                if (newUser.username.length() < 3) {
                    cout << "Username phai co it nhat 3 ky tu!\n";
                    break;
                }

                if (password.length() < 3) {
                    cout << "Password phai co it nhat 3 ky tu!\n";
                    break;
                }

                if (password != confirmPassword) {
                    cout << "Password xac nhan khong khop!\n";
                    break;
                }

                newUser.password = password;
                newUser.isAdmin = false;

                if (db.dangKyTaiKhoan(newUser)) {
                    cout << "Dang ky tai khoan thanh cong!\n";
                    cout << "Ban co the dang nhap ngay bay gio.\n";
                } else {
                    cout << "Dang ky that bai! Username, SDT hoac Email da ton tai.\n";
                }
                break;
            }
            case 3:
                return 0;
            default:
                cout << "\nLua chon khong hop le!\n";
        }
    }
    return 0;
}


