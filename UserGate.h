#include <iostream>
#include <string>
using namespace std;

extern const int maxUsers;
extern const int numColumns;

extern int numUsers;
extern string (*pUsers)[numColumns];

void printArrayUsers(){
    for(int i = 0; i < maxUsers; i++){
        // [i][0]
        if ( *(*(pUsers + i)) == ""){
            continue;
        }
        for(int j = 0; j < 3; j++){
            cout << *(*(pUsers + i) + j) << " ";
        }
        cout << endl;
    }
}

void createAccount(string name, string password, string role){
    *(*(pUsers + numUsers) + 0) = name;
    *(*(pUsers + numUsers) + 1) = password;
    *(*(pUsers + numUsers) + 2) = role;
    numUsers++;
}

bool isUsernameTaken(const string& username) {
    for (int i = 0; i < numUsers; ++i) {
        if (*(*(pUsers + i)) == username) {
            return true;
        }
    }
    return false;
}

void registerUser() {
if (numUsers < maxUsers) {
        string username, password, role;
        while (true)
        {
            cout << "Masukkan username: ";
            cin >> username;

            if (isUsernameTaken(username)) {
            cout << "Username sudah terpakai. Silakan gunakan username lain." << endl;
            return;
            }
            cout << "Masukkan password: ";
            cin >> password;
            cout << "Masukkan role\n\t1: customer\n\t2: admin ";
            cin >> role;
            if (role == "1") {
                role = "customer";
                break;
            } else if (role == "2") {
                role = "admin";
                break;
            } else {
                cout << "Role tidak valid. Silakan pilih role yang sesuai." << endl;
                return;
            }
        }
        createAccount(username, password, role);
        cout << "Pengguna berhasil terdaftar." << endl;
        
    } else {
        cout << "Database pengguna penuh. Tidak bisa mendaftarkan pengguna baru." << endl;
    }
}

void loginUser() {
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    bool userFound = false;
    for (int i = 0; i < numUsers; ++i) {
        if (*(*(pUsers + i) + 0) == username && *(*(pUsers + i) + 1) == password) {
            cout << "Login berhasil. Selamat datang, " << username << "!" << endl;
            cout << "Role: " << *(*(pUsers + i) + 2) << endl;
            userFound = true;
            break;
        }
    }
    if (!userFound) {
        cout << "Login gagal. Silakan coba lagi." << endl;
    }
}

void loginGate(){
    createAccount("admin1", "admin123", "admin");
    createAccount("cust1", "cust123", "cust");

    int choice;
    do {
        cout << "\nMENU AWAL" << endl;
        cout << "1. Daftar" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        
        cout << "\t(length array): " << endl;
        cout << "\t(isi array):\n";
        printArrayUsers();
        cout << endl;

        cout << "Pilihan Anda: ";
        cin >> choice;
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Terima kasih. Sampai jumpa!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 3);
}