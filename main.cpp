#include <iostream>
#include <string>
using namespace std;

struct FoodMenu{
    string kategori;
    string id;
    string nama;
    int harga;
    FoodMenu *next;
    FoodMenu *prev;
};

struct Cart{
    string *nama;
    string *id;
    int *harga;
    int qty;
    Cart *next;
};
Cart *firstCart;
FoodMenu *firstMenu;

bool isMenuEmpty(){
    if(firstMenu == NULL){
        return true;
    } else {
        return false;
    }
}

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

void printMenu(){
    FoodMenu *current;
    if(!isMenuEmpty()){
        current = firstMenu;

        // while(current != NULL){
        //     cout << current->nama << "\t\tRp " << current->harga << "\n";
        //     current = current->next;
        // }

        while(current != NULL){
            if(current->prev == NULL || current->kategori != current->prev->kategori){
                cout << "\n[id]\t[" << current->kategori << "]\n";
            }
            cout << current->id << "\t" << current->nama << "\t\tRp " << current->harga << "\n";
            current = current->next;
        }

    // TESTING DOUBLE LINKED LIST
        // cout << current->nama << "\t\tRp " << current->harga << "\n";

        // current = current->prev;
        // while(current != NULL){
        //     cout << current->nama << "\t\tRp " << current->harga << "\n";
        //     current = current->prev;
        // }
    }
}

FoodMenu * cariMenu(string namaMenu){
    FoodMenu *current;
    if(!isMenuEmpty()){
        current = firstMenu;
        while(current != NULL){
            if(current->nama == namaMenu){
                return current;
            }
            current = current->next;
        }
        return NULL;
    } else {
        return NULL;
    }
}

void addOrder(){
    string idMenu;
    int jumlah;
    FoodMenu *current;

    cout << "\nId Menu: ";
    // getline(cin, idMenu);
    cin >> idMenu;
    cout << "Id menu yg Anda Pesan: " << idMenu << endl;
    // cout << cariMenu(idMenu)->harga;
    if(!isMenuEmpty()){
        current = firstMenu;
        while(current != NULL){
            if(current->id == idMenu){
                break;
            }
            current = current->next;
        }

        // kalo id menu tidak tersedia
        if(current == NULL){
            cout << "Menu ga adaaa";
            return;
        }

        cout << current->nama << " Rp " << current->harga << endl;
        cout << "\tJumlah\t: ";
        cin >> jumlah;

        Cart *currentCart, *prevCart, *newCart;
        newCart = new Cart;
        newCart->nama = &current->nama;
        newCart->id = &current->id;
        newCart->harga = &current->harga;
        newCart->next = NULL;

        // kalo cart tidak kosong...
        if(firstCart != NULL){
            currentCart = firstCart;
            // lakukan iterasi
            while(currentCart != NULL){
                if(currentCart->next == NULL){
                    prevCart = currentCart;
                }
                // kalo menu yg dipesan udh dipesan sebelumnya, tambahin jumlahnya
                if(*currentCart->nama == current->nama){
                    currentCart->qty += jumlah;
                    delete newCart;
                    return;
                }
                currentCart = currentCart->next;
                newCart->qty = jumlah;
                prevCart->next = newCart;
            }
        } else{
            newCart->qty = jumlah;
            firstCart = newCart;
        }

        return;
    }
}

void printCart(){
    if(firstCart != NULL){
        Cart *current = firstCart;
        cout << "========================" <<endl;
        while(current != NULL){
            cout << "\n" << *current->nama << "\t\t" << *current->harga << " x " << current->qty << " = " << *current->harga * current->qty << "\n";
            current = current->next;
        }
        cout << "========================" <<endl;
    }
}

void initApp(){
    createMenu("Lauk", "a1", "Ayam Bakar", 15000);
    createMenu("Lauk", "a2", "Ayam Goreng", 13000);
    createMenu("Lauk", "a3", "Ayam Geprek", 17000);

    createMenu("Nasi", "n1", "Nasi Putih", 5000);
    createMenu("Nasi", "n2", "Nasi Kuning", 7000);
    createMenu("Nasi", "n3", "Nasi Kebuli", 10000);

    createMenu("Minuman", "m1", "Es Teh Manis", 7000);
    createMenu("Minuman", "m2", "Air Mineral", 4000);
    createMenu("Minuman", "m3", "Es Jeruk", 8000);

    createMenu("Lauk", "a4", "Ikan Bakar", 23000);
    createMenu("Nasi", "n4", "Nasi Goreng", 13000);
}


int main(){
    // ini testing dulu
    // struct FoodMenu paketan[3] = {
    //     {"Ayam", 1000},
    //     {"Bebek", 2000},
    //     {"Sapi", 3000}
    // };
    // cout << paketan[0].nama << endl;

    initApp();
    int opsi;
    
    // 1. tambah pesanan (addOrder())
    // 2. lihat pesanan (printCart())
    // 3. hapus pesanan
    // 4. cetak invoice

    while(true){
        cout << "===== Selamat datang di Restoran 69! =====\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Pesanan\n";
        cout << "3. Hapus Pesanan\n";
        cout << "4. Checkout dan Cetak Invoice\n";
        cout << "5. Keluar\n";
        cout << "\nOpsi\t: ";
        cin >> opsi;

        switch (opsi)
        {
        case 1:
            printMenu();
            addOrder();
            break;

        case 2:
            printCart();
            break;

        case 3:
            cout << "\n=== Hapus pesanan ===\n";
            break;
        
        case 4:
            cout << "\n=== Checkout ===\n";
            break;

        case 5:
        return 0;

        default:
            break;
        }

    }
    printMenu();

    addOrder();
    addOrder();

    printCart();

    cout << "Enter untuk lanjutkan";
    cin.get();
    
}