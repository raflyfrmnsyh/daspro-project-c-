#include <iostream>
#include <string>
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

    // input id menu sekaligus mencegah duplikasi
    cin.ignore();
    do{
        cout << "\n\tID menu baru: ";
        getline(cin, newId); cout << endl;

        if(menuIdExists(newId)){
            cout << "ID menu sudah ada, gunakan ID lain!\n";
        } else {
            break;
        }
    } while (true);

    // cin.ignore();
    cout << "\n\tNama menu baru: ";
    getline(cin, newName); cout << endl;

    // cin.ignore();
    cout << "\n\tKategori menu baru: ";
    getline(cin, newCategory); cout << endl;

    // cin.ignore();
    cout << "\n\tHarga menu baru: ";
    cin >> newPrice;

    cout << "ID\t\t: " << newId << endl;
    cout << "Nama Menu\t: "<< newName << endl;
    cout << "Kategori\t: " << newCategory << endl;
    cout << "Harga\t\t: " << newPrice << endl;

    cout << "Yakin ingin menambahkan data tsb? (y/n)";
    cin >> confirm;

    if(confirm == "y"){
        createMenu(newCategory, newId, newName, newPrice);
        cout << "Menu berhasil ditambahkan!\n";
    } else {
        cout << "Menu tidak jadi ditambahkan!\n";
    }

}

void adminDashboard(){
    int opsi;
    
    // 1. Buat menu (addMenu())
    // 2. Hapus menu (deleteMenu())
    // 3. Cetak Laporan Pendapatan
    // 4. Keluar

    while(true){
        cout << "===== Selamat datang di Restoran 69! =====\n";
        cout << "1. Buat Menu Baru\n";
        cout << "2. Hapus Menu\n";
        cout << "3. Cetak Laporan Pendapatan\n";
        cout << "4. Keluar\n";
        cout << "\nOpsi\t: ";
        cin >> opsi;

        switch (opsi)
        {
        case 1:
            printMenu();
            addMenu();
            break;

        case 2:
            cout << "\n=== Hapus Menu ===\n";
            break;

        case 3:
            cout << "\n=== Cetak Laporan Pendapatan ===\n";
            break;
        
        case 4:
            return;

        default:
            break;
        }

    }
}