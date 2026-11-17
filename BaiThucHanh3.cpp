#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
class Vehicle {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiGianDo;
    double phiDoXe;

public:
    Vehicle()
        : maXe(0), loaiXe(""), gioVao(0),
          thoiGianDo(0), phiDoXe(0.0) {}

    Vehicle(int ma, const string& loaiXe, int gioVao, int thoiGianDo)
        : maXe(ma), loaiXe(loaiXe), gioVao(gioVao),
          thoiGianDo(thoiGianDo), phiDoXe(0.0) {
        phiDoXe = calculateFee();
    }

    int getVehicleID() const { return maXe; }
    string getVehicleType() const { return loaiXe; }
    int getEntryTime() const { return gioVao; }
    int getParkingDuration() const { return thoiGianDo; }
    double getParkingFee() const { return phiDoXe; }

    void setVehicleID(int ma) { maXe = ma; }
    void setVehicleType(const string& loaiXeMoi) {
        loaiXe = loaiXeMoi;
        phiDoXe = calculateFee();
    }
    void setEntryTime(int thoiGian) {
        gioVao = thoiGian;
        phiDoXe = calculateFee();
    }
    void setParkingDuration(int thoiGianDoMoi) {
        thoiGianDo = thoiGianDoMoi;
        phiDoXe = calculateFee();
    }
    double calculateFee() const {
        double donGia = 0.0;
        double tongPhi = 0.0;

        if (loaiXe == "car") {
            donGia = 6.0;
        } else if (loaiXe == "motorcycle") {
            donGia = 4.0;
        } else if (loaiXe == "bicycle") {
            donGia = 2.0;
        }

        for (int chiSo = 0; chiSo < thoiGianDo; ++chiSo) {
            int gio = (gioVao + chiSo) % 24;
            bool gioCaoDiem = (gio >= 6 && gio <= 10) ||
                            (gio >= 15 && gio <= 18);

            if (chiSo <= 2) {
                tongPhi += gioCaoDiem ? donGia * 1.3
                                     : donGia * 0.95;
            } else {
                tongPhi += donGia * 0.9;
            }
        }
        return tongPhi;
    }

    void display() const {
        cout << "Ma xe: " << maXe << '\n'
             << "Loai xe: " << loaiXe << '\n'
             << "Gio vao: " << gioVao << "h\n"
             << "Thoi gian do xe: " << thoiGianDo << "h\n"
             << "Phi do xe: " << fixed << setprecision(2)
             << phiDoXe << "$\n";
    }
};
class ParkingLot {
private:
    int maBai;
    char kichThuoc;
    int sucChua;
    int soXeHienTai;
    Vehicle** danhSachXe;

    void initializeArray() {
        for (int chiSo = 0; chiSo < sucChua; ++chiSo) {
            danhSachXe[chiSo] = nullptr;
        }
    }

    void releaseMemory() {
        if (danhSachXe != nullptr) {
            for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
                delete danhSachXe[chiSo];
                danhSachXe[chiSo] = nullptr;
            }
            delete[] danhSachXe;
            danhSachXe = nullptr;
        }
        soXeHienTai = 0;
        sucChua = 0;
    }

public:
    ParkingLot()
        : maBai(0), kichThuoc('S'), sucChua(1),
          soXeHienTai(0), danhSachXe(nullptr) {
        danhSachXe = new Vehicle*[sucChua];
        initializeArray();
    }

    ParkingLot(int ma, char kichThuocMoi)
        : maBai(ma), kichThuoc(kichThuocMoi),
          sucChua(kichThuocMoi == 'S' ? 1 : (kichThuocMoi == 'M' ? 2 : 3)),
          soXeHienTai(0), danhSachXe(nullptr) {
        danhSachXe = new Vehicle*[sucChua];
        initializeArray();
    }
    ParkingLot(const ParkingLot& doiTuongKhac)
        : maBai(doiTuongKhac.maBai), kichThuoc(doiTuongKhac.kichThuoc),
          sucChua(doiTuongKhac.sucChua),
          soXeHienTai(doiTuongKhac.soXeHienTai),
          danhSachXe(nullptr) {
        danhSachXe = new Vehicle*[sucChua];
        initializeArray();

        try {
            for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
                danhSachXe[chiSo] = new Vehicle(*doiTuongKhac.danhSachXe[chiSo]);
            }
        } catch (...) {
            for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
                delete danhSachXe[chiSo];
                danhSachXe[chiSo] = nullptr;
            }
            delete[] danhSachXe;
            danhSachXe = nullptr;
            throw;
        }
    }
    ParkingLot& operator=(const ParkingLot& doiTuongKhac) {
        if (this == &doiTuongKhac) {
            return *this;
        }

        Vehicle** danhSachXeMoi = new Vehicle*[doiTuongKhac.sucChua];
        for (int chiSo = 0; chiSo < doiTuongKhac.sucChua; ++chiSo) {
            danhSachXeMoi[chiSo] = nullptr;
        }

        try {
            for (int chiSo = 0; chiSo < doiTuongKhac.soXeHienTai; ++chiSo) {
                danhSachXeMoi[chiSo] = new Vehicle(*doiTuongKhac.danhSachXe[chiSo]);
            }
        } catch (...) {
            for (int chiSo = 0; chiSo < doiTuongKhac.soXeHienTai; ++chiSo) {
                delete danhSachXeMoi[chiSo];
            }
            delete[] danhSachXeMoi;
            throw;
        }

        releaseMemory();

        maBai = doiTuongKhac.maBai;
        kichThuoc = doiTuongKhac.kichThuoc;
        sucChua = doiTuongKhac.sucChua;
        soXeHienTai = doiTuongKhac.soXeHienTai;
        danhSachXe = danhSachXeMoi;

        return *this;
    }
    ~ParkingLot() {
        releaseMemory();
    }

    int getParkID() const { return maBai; }
    char getSize() const { return kichThuoc; }
    int getCurrentVehicleCount() const { return soXeHienTai; }
    int getCapacity() const { return sucChua; }

    bool containsVehicle(int maXe) const {
        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            if (danhSachXe[chiSo] != nullptr &&
                danhSachXe[chiSo]->getVehicleID() == maXe) {
                return true;
            }
        }
        return false;
    }
    void resize(int sucChuaMoi) {
        if (sucChuaMoi <= sucChua) {
            return;
        }

        Vehicle** danhSachXeMoi = new Vehicle*[sucChuaMoi];
        for (int chiSo = 0; chiSo < sucChuaMoi; ++chiSo) {
            danhSachXeMoi[chiSo] = nullptr;
        }

        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            danhSachXeMoi[chiSo] = danhSachXe[chiSo];
        }

        delete[] danhSachXe;
        danhSachXe = danhSachXeMoi;
        sucChua = sucChuaMoi;
    }

    bool addVehicle(const Vehicle& phuongTien) {
        if (containsVehicle(phuongTien.getVehicleID())) {
            return false;
        }

        if (soXeHienTai == sucChua) {
            resize(sucChua * 2);
        }

        danhSachXe[soXeHienTai] = new Vehicle(phuongTien);
        ++soXeHienTai;
        return true;
    }

    bool removeVehicle(int maXe) {
        int viTri = -1;

        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            if (danhSachXe[chiSo] != nullptr &&
                danhSachXe[chiSo]->getVehicleID() == maXe) {
                viTri = chiSo;
                break;
            }
        }

        if (viTri == -1) {
            return false;
        }

        delete danhSachXe[viTri];
        danhSachXe[viTri] = nullptr;

        for (int chiSo = viTri; chiSo < soXeHienTai - 1; ++chiSo) {
            danhSachXe[chiSo] = danhSachXe[chiSo + 1];
        }

        --soXeHienTai;
        danhSachXe[soXeHienTai] = nullptr;
        return true;
    }

    void display() const {
        cout << "\nBai " << maBai << " [" << kichThuoc << "] "
             << soXeHienTai << "/" << sucChua << " xe\n";

        if (soXeHienTai == 0) {
            cout << "  Bai chua co xe.\n";
            return;
        }

        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            if (danhSachXe[chiSo] != nullptr) {
                cout << "\n--- Xe thu " << chiSo + 1 << " ---\n";
                danhSachXe[chiSo]->display();
            }
        }
    }

    void displayVehiclesByType(const string& loaiXe) const {
        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            if (danhSachXe[chiSo] != nullptr &&
                danhSachXe[chiSo]->getVehicleType() == loaiXe) {
                danhSachXe[chiSo]->display();
                cout << "----------------------\n";
            }
        }
    }

    int countVehiclesByType(const string& loaiXe) const {
        int soLuong = 0;
        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            if (danhSachXe[chiSo] != nullptr &&
                danhSachXe[chiSo]->getVehicleType() == loaiXe) {
                ++soLuong;
            }
        }
        return soLuong;
    }

    double tongPhi() const {
        double tong = 0.0;
        for (int chiSo = 0; chiSo < soXeHienTai; ++chiSo) {
            if (danhSachXe[chiSo] != nullptr) {
                tong += danhSachXe[chiSo]->getParkingFee();
            }
        }
        return tong;
    }
};
class SystemInterface {
private:
    int sucChuaBai;
    int soBaiHienTai;
    ParkingLot** danhSachBai;

    void initializeArray() {
        for (int chiSo = 0; chiSo < sucChuaBai; ++chiSo) {
            danhSachBai[chiSo] = nullptr;
        }
    }

    void releaseMemory() {
        if (danhSachBai != nullptr) {
            for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
                delete danhSachBai[chiSo];
                danhSachBai[chiSo] = nullptr;
            }
            delete[] danhSachBai;
            danhSachBai = nullptr;
        }
        soBaiHienTai = 0;
        sucChuaBai = 0;
    }

    int findLotIndex(int ma) const {
        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            if (danhSachBai[chiSo] != nullptr &&
                danhSachBai[chiSo]->getParkID() == ma) {
                return chiSo;
            }
        }
        return -1;
    }

    bool vehicleIDExists(int ma) const {
        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            if (danhSachBai[chiSo] != nullptr &&
                danhSachBai[chiSo]->containsVehicle(ma)) {
                return true;
            }
        }
        return false;
    }

public:
    SystemInterface()
        : sucChuaBai(5), soBaiHienTai(0), danhSachBai(nullptr) {
        danhSachBai = new ParkingLot*[sucChuaBai];
        initializeArray();
    }
    SystemInterface(const SystemInterface& doiTuongKhac)
        : sucChuaBai(doiTuongKhac.sucChuaBai),
          soBaiHienTai(doiTuongKhac.soBaiHienTai),
          danhSachBai(nullptr) {
        danhSachBai = new ParkingLot*[sucChuaBai];
        initializeArray();

        try {
            for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
                danhSachBai[chiSo] = new ParkingLot(*doiTuongKhac.danhSachBai[chiSo]);
            }
        } catch (...) {
            for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
                delete danhSachBai[chiSo];
                danhSachBai[chiSo] = nullptr;
            }
            delete[] danhSachBai;
            danhSachBai = nullptr;
            throw;
        }
    }
    SystemInterface& operator=(const SystemInterface& doiTuongKhac) {
        if (this == &doiTuongKhac) {
            return *this;
        }

        ParkingLot** danhSachBaiMoi = new ParkingLot*[doiTuongKhac.sucChuaBai];
        for (int chiSo = 0; chiSo < doiTuongKhac.sucChuaBai; ++chiSo) {
            danhSachBaiMoi[chiSo] = nullptr;
        }

        try {
            for (int chiSo = 0; chiSo < doiTuongKhac.soBaiHienTai; ++chiSo) {
                danhSachBaiMoi[chiSo] = new ParkingLot(*doiTuongKhac.danhSachBai[chiSo]);
            }
        } catch (...) {
            for (int chiSo = 0; chiSo < doiTuongKhac.soBaiHienTai; ++chiSo) {
                delete danhSachBaiMoi[chiSo];
            }
            delete[] danhSachBaiMoi;
            throw;
        }

        releaseMemory();

        sucChuaBai = doiTuongKhac.sucChuaBai;
        soBaiHienTai = doiTuongKhac.soBaiHienTai;
        danhSachBai = danhSachBaiMoi;

        return *this;
    }
    ~SystemInterface() {
        releaseMemory();
    }

    void resizeSystem(int sucChuaMoi) {
        if (sucChuaMoi <= sucChuaBai) {
            return;
        }

        ParkingLot** danhSachBaiMoi = new ParkingLot*[sucChuaMoi];
        for (int chiSo = 0; chiSo < sucChuaMoi; ++chiSo) {
            danhSachBaiMoi[chiSo] = nullptr;
        }

        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            danhSachBaiMoi[chiSo] = danhSachBai[chiSo];
        }

        delete[] danhSachBai;
        danhSachBai = danhSachBaiMoi;
        sucChuaBai = sucChuaMoi;
    }

    bool addParkingLot(int ma, char kichThuoc) {
        if (findLotIndex(ma) != -1) {
            return false;
        }

        if (soBaiHienTai == sucChuaBai) {
            resizeSystem(sucChuaBai * 2);
        }

        danhSachBai[soBaiHienTai] = new ParkingLot(ma, kichThuoc);
        ++soBaiHienTai;
        return true;
    }

    bool removeParkingLot(int ma) {
        int viTri = findLotIndex(ma);
        if (viTri == -1) {
            return false;
        }

        delete danhSachBai[viTri];
        danhSachBai[viTri] = nullptr;

        for (int chiSo = viTri; chiSo < soBaiHienTai - 1; ++chiSo) {
            danhSachBai[chiSo] = danhSachBai[chiSo + 1];
        }

        --soBaiHienTai;
        danhSachBai[soBaiHienTai] = nullptr;
        return true;
    }

    bool addVehicleToLot(int maBai, const Vehicle& phuongTien) {
        int viTri = findLotIndex(maBai);
        if (viTri == -1 || vehicleIDExists(phuongTien.getVehicleID())) {
            return false;
        }
        return danhSachBai[viTri]->addVehicle(phuongTien);
    }

    bool removeVehicleFromSystem(int maXe) {
        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            if (danhSachBai[chiSo]->removeVehicle(maXe)) {
                return true;
            }
        }
        return false;
    }

    void displayAllLots() const {
        if (soBaiHienTai == 0) {
            cout << "Chua co bai do nao!\n";
            return;
        }

        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            if (danhSachBai[chiSo] != nullptr) {
                danhSachBai[chiSo]->display();
            }
        }
    }

    void displayLot(int ma) const {
        int viTri = findLotIndex(ma);
        if (viTri == -1) {
            cout << "Khong tim thay bai!\n";
            return;
        }
        danhSachBai[viTri]->display();
    }

    void listVehiclesByType(const string& loaiXe) const {
        bool timThay = false;

        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            int soLuong = danhSachBai[chiSo]->countVehiclesByType(loaiXe);
            if (soLuong > 0) {
                cout << "\nBai " << danhSachBai[chiSo]->getParkID() << ":\n";
                danhSachBai[chiSo]->displayVehiclesByType(loaiXe);
                timThay = true;
            }
        }

        if (!timThay) {
            cout << "Khong co xe thuoc loai nay!\n";
        }
    }

    void showAverageFee() const {
        int soLuongXe = 0;
        double tong = 0.0;

        for (int chiSo = 0; chiSo < soBaiHienTai; ++chiSo) {
            soLuongXe += danhSachBai[chiSo]->getCurrentVehicleCount();
            tong += danhSachBai[chiSo]->tongPhi();
        }

        if (soLuongXe == 0) {
            cout << "Chua co xe nao!\n";
            return;
        }

        cout << fixed << setprecision(2);
        cout << "Tong so xe: " << soLuongXe << '\n';
        cout << "Tong phi: " << tong << "$\n";
        cout << "Phi trung binh: "
             << tong / soLuongXe << "$\n";
    }

    void runMenu() {
        int luaChon;

        while (true) {
            cout << "\n========== QUAN LY BAI DO XE ==========\n";
            cout << "1. Tao bai do xe moi\n";
            cout << "2. Them xe vao bai do\n";
            cout << "3. Xoa mot bai do xe\n";
            cout << "4. Lay xe ra khoi bai do\n";
            cout << "5. Hien thi danh sach tat ca bai do\n";
            cout << "6. Hien thi danh sach xe theo bai\n";
            cout << "7. Liet ke xe theo loai phuong tien\n";
            cout << "8. Tom tat phi do xe trung binh\n";
            cout << "9. Thoat chuong trinh\n";
            cout << "Lua chon cua ban: ";

            if (!(cin >> luaChon)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Vui long nhap mot so tu 1 den 9!\n";
                continue;
            }

            if (luaChon == 1) {
                int ma;
                char kichThuocBai;

                cout << "Nhap ma bai: ";
                cin >> ma;
                cout << "Nhap kich thuoc bai (S/M/L): ";
                cin >> kichThuocBai;
                kichThuocBai = static_cast<char>(
                    toupper(static_cast<unsigned char>(kichThuocBai)));

                if (kichThuocBai != 'S' && kichThuocBai != 'M' && kichThuocBai != 'L') {
                    cout << "Kich thuoc khong hop le!\n";
                    continue;
                }

                if (addParkingLot(ma, kichThuocBai)) {
                    cout << "Tao bai do thanh cong!\n";
                } else {
                    cout << "Ma bai da ton tai!\n";
                }
            }
            else if (luaChon == 2) {
                int maBai, maXe, gioVao, thoiGianDo;
                string loaiXe;

                cout << "Nhap ma bai: ";
                cin >> maBai;
                cout << "Nhap ma xe: ";
                cin >> maXe;
                cout << "Nhap loai xe (car/motorcycle/bicycle): ";
                cin >> loaiXe;

                for (size_t chiSo = 0; chiSo < loaiXe.length(); ++chiSo) {
                    loaiXe[chiSo] = static_cast<char>(
                        tolower(static_cast<unsigned char>(loaiXe[chiSo])));
                }

                if (loaiXe != "car" && loaiXe != "motorcycle" &&
                    loaiXe != "bicycle") {
                    cout << "Loai xe khong hop le!\n";
                    continue;
                }

                cout << "Nhap gio vao (0-23): ";
                cin >> gioVao;
                cout << "Nhap thoi gian do (gio): ";
                cin >> thoiGianDo;

                if (gioVao < 0 || gioVao > 23 || thoiGianDo <= 0) {
                    cout << "Thoi gian khong hop le!\n";
                    continue;
                }

                Vehicle phuongTien(maXe, loaiXe, gioVao, thoiGianDo);

                if (addVehicleToLot(maBai, phuongTien)) {
                    cout << "Them xe thanh cong!\n";
                } else {
                    cout << "Khong the them xe: bai khong ton tai "
                         << "hoac ma xe da duoc su dung!\n";
                }
            }
            else if (luaChon == 3) {
                int ma;
                cout << "Nhap ma bai can xoa: ";
                cin >> ma;

                if (removeParkingLot(ma)) {
                    cout << "Da xoa bai do va giai phong cac xe trong bai!\n";
                } else {
                    cout << "Khong tim thay bai do!\n";
                }
            }
            else if (luaChon == 4) {
                int ma;
                cout << "Nhap ma xe can lay ra: ";
                cin >> ma;

                if (removeVehicleFromSystem(ma)) {
                    cout << "Lay xe thanh cong!\n";
                } else {
                    cout << "Khong tim thay xe!\n";
                }
            }
            else if (luaChon == 5) {
                displayAllLots();
            }
            else if (luaChon == 6) {
                int ma;
                cout << "Nhap ma bai can xem: ";
                cin >> ma;
                displayLot(ma);
            }
            else if (luaChon == 7) {
                string loaiXe;
                cout << "Nhap loai xe (car/motorcycle/bicycle): ";
                cin >> loaiXe;

                for (size_t chiSo = 0; chiSo < loaiXe.length(); ++chiSo) {
                    loaiXe[chiSo] = static_cast<char>(
                        tolower(static_cast<unsigned char>(loaiXe[chiSo])));
                }

                if (loaiXe != "car" && loaiXe != "motorcycle" &&
                    loaiXe != "bicycle") {
                    cout << "Loai xe khong hop le!\n";
                    continue;
                }

                listVehiclesByType(loaiXe);
            }
            else if (luaChon == 8) {
                showAverageFee();
            }
            else if (luaChon == 9) {
                cout << "Ket thuc chuong trinh!\n";
                break;
            }
            else {
                cout << "Lua chon khong hop le! Vui long chon tu 1 den 9.\n";
            }
        }
    }
};

int main() {
    SystemInterface heThong;
    heThong.runMenu();
    return 0;
}
