#include <iostream>
#include <string>
#include "ValidInput.h"
using namespace std;

void createMenu(string kategori, string id, string nama, int harga){
    FoodMenu *newMenu, *current, *nextMenu;
    newMenu = new FoodMenu;
    newMenu->nama = nama;
    newMenu->id = id;
    newMenu->kategori = kategori;
    newMenu->harga = harga;
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
    int newPrice;

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

    cout << "ID\t\t: " << newId << endl;
    cout << "Nama Menu\t: "<< newName << endl;
    cout << "Kategori\t: " << newCategory << endl;
    cout << "Harga\t\t: " << newPrice << endl;

    cout << "Yakin ingin menambahkan data tsb? (y/n): ";
    confirm = inputOneWord();

    if(confirm == "y"){
        createMenu(newCategory, newId, newName, newPrice);
        cout << "Menu berhasil ditambahkan!\n";
    } else {
        cout << "Menu tidak jadi ditambahkan!\n";
    }

}

void adminDashboard(){
    int opsi;

    while(true){
        cout << "===== Selamat datang di Restoran 69! =====\n";
        cout << "1. Lihat Daftar Menu\n";
        cout << "2. Buat Menu Baru\n";
        cout << "3. Hapus Menu\n";
        cout << "4. Cetak Laporan Pendapatan\n";
        cout << "5. Keluar\n";
        cout << "\nOpsi\t: ";

        opsi = inputValidInt();

        switch (opsi){
        case 1:
            printMenu();
            wait();
            break;
        case 2:
            printMenu();
            addMenu();
            break;

        case 3:
            cout << "\n=== Hapus Menu ===\n";
            break;

        case 4:
            cout << "\n=== Cetak Laporan Pendapatan ===\n";
            break;
        
        case 5:
            return;

        default:
            cout << "Opsi tidak valid!\n";
            break;
        }

    }
}