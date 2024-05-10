#include <iomanip>
#include <iostream>
#include <string>
#include "ValidInput.h"
#include "UserGate.h"
using namespace std;

void createMenu(string kategori, string id, string nama, int harga, int sisaStok){
    FoodMenu *newMenu, *current, *nextMenu;
    newMenu = new FoodMenu;
    newMenu->nama = nama;
    newMenu->id = id;
    newMenu->kategori = kategori;
    newMenu->harga = harga;
    newMenu->sisaStok = sisaStok;
    newMenu->next = NULL;

    if(!isMenuEmpty()){
        current = firstMenu;
        while(current->next != NULL){
            if(current->kategori == newMenu->kategori && current->next->kategori != current->kategori){
                nextMenu = current->next;
                nextMenu->prev = newMenu;
                newMenu->next = nextMenu;
                break;
            }
            current = current->next;
        }
        current->next = newMenu;
        newMenu->prev = current;

    } else {
        firstMenu = newMenu;
        firstMenu->prev = NULL;
    }
}

bool menuIdExists(string newId){
    FoodMenu *current;
    current = firstMenu;
    while(current != NULL){
        if(current->id == newId){
            return true;
        }
        current = current->next;
    }
    return false;
}

void addMenu(){
    string newId, newName, newCategory, confirm;
    int newPrice, newStok;

    cout << "\n\tID menu baru: ";
    newId = inputOneWord();
    cout << endl;
    // mengecek duplikasi id menu
    while(menuIdExists(newId)){
        cout << "ID menu sudah ada, gunakan ID lain!\n";
        newId = inputOneWord();
    }

    cout << "\n\tNama menu baru: ";
    getline(cin, newName); cout << endl;

    cout << "\n\tKategori menu baru: ";
    getline(cin, newCategory); cout << endl;

    cout << "\n\tHarga menu baru: ";
    newPrice = inputValidInt();

    cout << "\n\tStok menu baru: ";
    newStok = inputValidInt();
    
    cout << "ID\t\t: " << newId << endl;
    cout << "Nama Menu\t: "<< newName << endl;
    cout << "Kategori\t: " << newCategory << endl;
    cout << "Harga\t\t: " << newPrice << endl;
    cout << "Stok\t\t: " << newStok << endl;

    cout << "Yakin ingin menambahkan data tsb? (y/n): ";
    confirm = inputOneWord();

    if(confirm == "y"){
        createMenu(newCategory, newId, newName, newPrice, newStok);
        cout << "Menu berhasil ditambahkan!\n";
    } else {
        cout << "Menu tidak jadi ditambahkan!\n";
    }

}

void addStok() {
    string idMenu;
    int tambahanStok;

    cout << "ID Menu yang stoknya akan ditambahkan: ";
    idMenu = inputOneWord();

    FoodMenu *current = firstMenu;
    while (current != nullptr) {
        if (current->id == idMenu) {
            break;
        }
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Menu tidak ditemukan!\n";
        return;
    }

    cout << "Jumlah stok yang ditambahkan: ";
    tambahanStok = inputValidInt();

    // Memastikan stok yang ditambahkan tidak negatif
    while (tambahanStok < 0) {
        cout << "Jumlah stok tidak valid!\n";
        cout << "Jumlah stok yang ditambahkan: ";
        tambahanStok = inputValidInt();
    }

    // Menambah stok
    current->sisaStok += tambahanStok;
    cout << "Stok untuk menu " << current->nama << " berhasil ditambahkan menjadi " << current->sisaStok << ".\n";
}


void deleteMenu () {
    if (isMenuEmpty()) {
        cout << "Menu kosong. Tidak ada yang dihapus." << endl;
        return;
    }

    FoodMenu *current = firstMenu, *prevMenu = nullptr;
    string id, confirm;
    current = firstMenu;
    
    cout << "ID Menu yang ingin dihapus: ";
    id = inputOneWord();
    
    while (current != nullptr) {
        if (current->id == id) {
            cout << "Yakin ingin menghapus data tsb? (y/n): ";
            confirm = inputOneWord();

            if(confirm != "y"){
                cout << "Menu tidak jadi dihapus!\n";
                return;
            } else {
                if (current == firstMenu) {
                    firstMenu = current->next;
                    if (firstMenu != nullptr)
                        firstMenu->prev = nullptr;
                        
                } else {
                    prevMenu->next = current->next;
                    if (current->next != nullptr)
                        current->next->prev = prevMenu;
                }
                delete current;
                cout << "Menu dengan ID " << id << " telah dihapus." << endl;
            } 
            
        }
        prevMenu = current;
        current = current->next;
    }
}

void printSaleReport() {
    Transaction *curr;
    int total = 0;

    if(firstTransaction != NULL){
        curr = firstTransaction;
        int count = 1;

        cout << setw(55) << "\n=======================================================\n";
        cout << setw(6) << "NO" << setw(15) << "Customer\t" << "Total Pembayaran" << endl;
        cout << setw(55) << "=======================================================\n";
        
        while(curr != NULL){
            // cout << setw(10) << count++ << setw(15) << curr->nama << setw(15) << curr->qty << setw(15) << "Rp." << *curr->harga * curr->qty << endl;
            cout << setw(6) << count++ << setw(15) << curr->namaCust << "\t" << "Rp." << curr->total <<endl;
            total += curr->total;
            curr = curr->next;
        }
        cout << setw(55) << "-------------------------------------------------------\n";
        cout << setw(25) << "Total = Rp." << total << endl;
        cout << setw(55) << "=======================================================\n";
        

    } else {
        
        cout << setw(55) << "\n=======================================================\n";
        cout << "\nBelum Ada Penjualan\n";
        cout << setw(55) << "=======================================================\n";
    }
    wait();
}

void adminDashboard(){
    int opsi;

    while(true){
        cout << "\n===== Selamat datang di Restoran 77! =====\n";
        cout << "1. Lihat Daftar Menu\n";
        cout << "2. Buat Menu Baru\n";
        cout << "3. Hapus Menu\n";
        cout << "4. Cetak Laporan Pendapatan\n";
        cout << "5. Tambah Stok\n";
        cout << "6. Logout\n";
        cout << "7. Keluar\n";
        cout << "\nOpsi\t: ";

        opsi = inputValidInt();

        switch (opsi){
        case 1:
            cout << "\n=== Daftar Menu ===\n";
            printMenu();
            wait();
            break;
        case 2:
            cout << "\n=== Buat Menu Baru ===\n";
            printMenu();
            addMenu();
            break;

        case 3:
            cout << "\n=== Hapus Menu ===\n";
            printMenu();
            deleteMenu();
            break;

        case 4:
            cout << "\n=== Cetak Laporan Pendapatan ===\n";
            printSaleReport();
            break;
        
        case 5:
            cout << "\n=== Tambah Stok ===\n";
            printMenu();
            addStok();
            break;

        case 6:
            USER_FOUND = false;
            return;
        
        case 7:
            IS_CONTINUE = false;
            return;

        default:
            cout << "Opsi tidak valid!\n";
            break;
        }

    }
}