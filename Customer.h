#include <iostream>
#include <string>
using namespace std;

void addOrder(){
    string idMenu;
    int jumlah;
    FoodMenu *current;

    cout << "\nId Menu: ";
    // getline(cin, idMenu);
    cin >> idMenu;
    cout << "Id menu yg Anda Pesan: " << idMenu << endl;

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
        // kalo Cart kosong, buat Cart baru
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

void customerDashboard(){
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
        return;

        default:
            break;
        }

    }
}