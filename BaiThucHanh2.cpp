#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao, tg_do;
    double phi_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double lay_phi() const;

    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien()
    : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0), phi_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {
    phi_do = tinh_phi();
}

int phuong_tien::lay_ma_xe() const {
    return ma_xe;
}

string phuong_tien::lay_loai_xe() const {
    return loai_xe;
}

double phuong_tien::lay_phi() const {
    return phi_do;
}

double phuong_tien::tinh_phi() const {
    double gia;

    if (loai_xe == "Car") gia = 6;
    else if (loai_xe == "Motorcycle") gia = 4;
    else gia = 2;

    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9)
                 || (gio_vao >= 15 && gio_vao <= 18);

    double tong = 0;

    for (int i = 0; i < tg_do; i++) {
        if (i < 2) {
            if (cao_diem) tong += gia * 1.30;
            else tong += gia * 0.95;
        }
        else tong += gia * 0.90;
    }

    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "ID: " << ma_xe<< " | " << loai_xe<< " | " << gio_vao << "h"<< " | " << tg_do << "h"<< " | Phi: $" << fixed << setprecision(2)<< phi_do << endl;
}

class bai_xe {
private:
    static const int MAX_VEHICLES = 3;

    int ma_bai;
    char kich_thuoc;
    phuong_tien pt[MAX_VEHICLES];
    int so_xe;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool day() const;
    int tim_xe(int ma_xe) const;

    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);

    void hien_thi() const;
    void liet_ke(string loai) const;

    int dem_xe(string loai) const;
    double tong_phi(string loai) const;
};

bai_xe::bai_xe(): ma_bai(0), kich_thuoc('S'), so_xe(0) {}

bai_xe::bai_xe(int ma, char kt): ma_bai(ma), kich_thuoc(kt), so_xe(0) {}

int bai_xe::lay_ma() const {return ma_bai;}

bool bai_xe::day() const {
    int cap = 1;

    if (kich_thuoc == 'M') cap = 2;
    else if (kich_thuoc == 'L') cap = 3;

    return so_xe >= cap;
}

int bai_xe::tim_xe(int ma_xe) const {
    for (int i = 0; i < so_xe; i++) {
        if (pt[i].lay_ma_xe() == ma_xe)
            return i;
    }

    return -1;
}

bool bai_xe::them(const phuong_tien& v) {
    if (day()) return false;

    pt[so_xe] = v;
    so_xe++;

    return true;
}

bool bai_xe::xoa(int ma_xe) {
    int vt = tim_xe(ma_xe);

    if (vt == -1) return false;

    for (int i = vt; i < so_xe - 1; i++)
        pt[i] = pt[i + 1];

    so_xe--;

    return true;
}

void bai_xe::hien_thi() const {
    int suc_chua = 1;

    if (kich_thuoc == 'M') suc_chua = 2;
    else if (kich_thuoc == 'L') suc_chua = 3;

    cout << "\nBai " << ma_bai << " [" << kich_thuoc << "] "<< so_xe << "/" << suc_chua << " xe\n";

    for (int i = 0; i < so_xe; i++)
        pt[i].hien_thi();
}

void bai_xe::liet_ke(string loai) const {
    for (int i = 0; i < so_xe; i++) {
        if (pt[i].lay_loai_xe() == loai)
            pt[i].hien_thi();
    }
}

int bai_xe::dem_xe(string loai) const {
    int dem = 0;

    for (int i = 0; i < so_xe; i++) {
        if (pt[i].lay_loai_xe() == loai)
            dem++;
    }

    return dem;
}

double bai_xe::tong_phi(string loai) const {
    double tong = 0;

    for (int i = 0; i < so_xe; i++) {
        if (pt[i].lay_loai_xe() == loai)
            tong += pt[i].lay_phi();
    }

    return tong;
}

class SystemInterface {
private:
    static const int MAX_LOTS = 10;

    bai_xe bai[MAX_LOTS];
    int so_bai;

    bool trung_ma_bai(int ma) const;
    bool trung_ma_xe(int ma) const;
    int tao_ma_moi();

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() {
    so_bai = 0;
}

bool SystemInterface::trung_ma_bai(int ma) const {
    for (int i = 0; i < so_bai; i++) {
        if (bai[i].lay_ma() == ma)
            return true;
    }

    return false;
}

bool SystemInterface::trung_ma_xe(int ma) const {
    for (int i = 0; i < so_bai; i++) {
        if (bai[i].tim_xe(ma) != -1)
            return true;
    }

    return false;
}

int SystemInterface::tao_ma_moi() {
    static int ma = 1000;

    do {
        ma++;
    } while (trung_ma_bai(ma) || trung_ma_xe(ma));

    return ma;
}

//int nhap_so(string tb) {
//    int n;
//
//    while (true) {
//        cout << tb;
//        cin >> n;
//
//        if (cin.fail()) {
//            cout << "Nhap sai! Hay nhap lai.\n";
//            cin.clear();
//            cin.ignore(1000, '\n');
//        }
//        else {
//            cin.ignore(1000, '\n');
//            return n;
//        }
//    }
//}

void SystemInterface::runMenu() {
    int chon;

    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";

        cin>>chon;

        switch (chon) {

        case 1: {
            if (so_bai == MAX_LOTS) {
                cout << "Da day 10 bai!\n";
                break;
            }
			int ma;
			cout<<"Nhap ma can tao: ";
            cin>>ma;

            if (trung_ma_bai(ma)) {
                cout << "Ma bai bi trung! ";
                ma = tao_ma_moi();
                cout << "Ma moi: " << ma << endl;
            }

            char kt;

            do {
                cout << "Kich thuoc (S/M/L): ";
                cin >> kt;
                cin.ignore(1000, '\n');

                if (kt != 'S' && kt != 'M' && kt != 'L')
                    cout << "Kich thuoc khong hop le!\n";

            } while (kt != 'S' && kt != 'M' && kt != 'L');

            bai[so_bai] = bai_xe(ma, kt);
            so_bai++;

            cout << "Da tao bai " << ma << endl;
            break;
        }

        case 2: {
            if (so_bai == 0) {
                cout << "Chua co bai do!\n";
                break;
            }
			int ma; cin>>ma;

            if (trung_ma_xe(ma)) {
                cout << "Ma xe bi trung! ";
                ma = tao_ma_moi();
                cout << "Ma moi: " << ma << endl;
            }

            string loai;

            do {
                cout << "Loai xe (Car/Motorcycle/Bicycle): ";
                cin >> loai;

                if (loai != "Car" && loai != "Motorcycle"
                    && loai != "Bicycle")
                    cout << "Loai xe khong hop le!\n";

            } while (loai != "Car" && loai != "Motorcycle"
                     && loai != "Bicycle");

            int gio, tg;

            do {
                int gio;cin>>gio;
            } while (gio < 0 || gio > 23);

            do {
                int tg; cin>>tg;
            } while (tg < 1 || tg > 23);

            phuong_tien v(ma, loai, gio, tg);

            bool ok = false;

            for (int i = 0; i < so_bai; i++) {
                if (bai[i].them(v)) {
                    cout << "Da them xe vao bai "
                         << bai[i].lay_ma() << endl;

                    cout << "Phi: $" << fixed << setprecision(2)
                         << v.lay_phi() << endl;

                    ok = true;
                    break;
                }
            }

            if (!ok)
                cout << "Tat ca bai da day!\n";

            break;
        }

        case 3: {
        	int ma;cin>>ma;
            int vt = -1;

            for (int i = 0; i < so_bai; i++) {
                if (bai[i].lay_ma() == ma) {
                    vt = i;
                    break;
                }
            }

            if (vt == -1)
                cout << "Khong tim thay bai!\n";
            else {
                for (int i = vt; i < so_bai - 1; i++)
                    bai[i] = bai[i + 1];

                so_bai--;
                cout << "Da xoa bai " << ma << endl;
            }

            break;
        }

        case 4: {
        	int ma;
        	cout<<"Ma xe can lay ra: ";
        	cin>>ma;
            bool ok = false;

            for (int i = 0; i < so_bai; i++) {
                if (bai[i].xoa(ma)) {
                    cout << "Da lay xe ra!\n";
                    ok = true;
                    break;
                }
            }

            if (!ok)
                cout << "Khong tim thay xe!\n";

            break;
        }

        case 5: {
            if (so_bai == 0)
                cout << "Chua co bai do!\n";

            for (int i = 0; i < so_bai; i++)
                bai[i].hien_thi();

            break;
        }

        case 6: {
        	cout<<"Ma bai: ";
        	int ma;cin>>ma;
            bool ok = false;

            for (int i = 0; i < so_bai; i++) {
                if (bai[i].lay_ma() == ma) {
                    bai[i].hien_thi();
                    ok = true;
                    break;
                }
            }

            if (!ok)
                cout << "Khong tim thay bai!\n";

            break;
        }

        case 7: {
            string loai;

            cout << "Loai xe: ";
            cin >> loai;

            bool ok = false;

            for (int i = 0; i < so_bai; i++) {
                if (bai[i].dem_xe(loai) > 0) {
                    cout << "\nBai " << bai[i].lay_ma() << ":\n";
                    bai[i].liet_ke(loai);
                    ok = true;
                }
            }

            if (!ok)
                cout << "Khong co xe loai nay!\n";

            break;
        }

        case 8: {
            string ds[3] = {"Car", "Motorcycle", "Bicycle"};

            for (int j = 0; j < 3; j++) {
                int dem = 0;
                double tong = 0;

                cout << "\n" << ds[j] << ":\n";

                for (int i = 0; i < so_bai; i++) {
                    int d = bai[i].dem_xe(ds[j]);
                    double t = bai[i].tong_phi(ds[j]);

                    if (d > 0) {
                        cout << "Bai " << bai[i].lay_ma()
                             << ": " << d << " xe | TB: $"
                             << fixed << setprecision(2)
                             << t / d << endl;
                    }

                    dem += d;
                    tong += t;
                }

                if (dem == 0)
                    cout << "Khong co xe\n";
                else
                    cout << "Toan he thong: " << dem<< " xe | TB: $" << fixed<< setprecision(2) << tong / dem << endl;
            }

            break;
        }
        case 9:
            cout << "Ket thuc chuong trinh!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 9);
}

int main() {
    SystemInterface sys;
    sys.runMenu();
}
