#include <iostream>
#include <string>
#include "ValidInput.h"
#include "UserGate.h"
using namespace std;

void addOrder(){
    string idMenu;
    int jumlah;
    FoodMenu *current;

    cout << "\nId Menu: ";
    idMenu = inputOneWord();
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
        jumlah = inputValidInt();

        while(jumlah < 0){
            cout << "Jumlah tidak valid!\tJumlah\t: ";
            jumlah = inputValidInt();
        }

        if (current->sisaStok < jumlah) {
                    cout << "Stok tidak cukup untuk pesanan ini!\n";
                    return;
                }

        current->sisaStok -= jumlah;
        Cart *currentCart, *prevCart, *newCart;
        newCart = new Cart;
        newCart->nama = &current->nama;
        newCart->id = &current->id;
        newCart->harga = &current->harga;
        newCart->next = NULL;
        TOTAL_PAYMENT += (current->harga * jumlah);

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
            }
                newCart->qty = jumlah;
                prevCart->next = newCart;
                newCart->prev = prevCart;
            
        // kalo Cart kosong, buat Cart baru
        } else{
            newCart->qty = jumlah;
            firstCart = newCart;
        }
    }
}

void printCart(){
    int total = 0;
    if(firstCart != NULL){
        Cart *current = firstCart;
        cout << "------------------------------------------------------" <<endl;
        while(current != NULL){
            cout << *current->id << "\t" << *current->nama << "\t\t" << "Rp." << *current->harga << " x " << current->qty << " = Rp." << *current->harga * current->qty << "\n";
            current = current->next;
        }
        cout << "------------------------------------------------------" <<endl;
        cout << "\t\t\tTotal\t: Rp." << TOTAL_PAYMENT << endl;
    } else {
        cout << "------------------------------------------------------" <<endl;
        cout << "             (Belum ada menu dipesan)                 \n";
        cout << "------------------------------------------------------" <<endl;
    }
}

void removeOrder(){
    Cart *current;
    string id;
    int jumlah;

    cout << "ID pesanan yang ingin dikurangi: ";
    id = inputOneWord();
    current = firstCart;
    bool isFound = false;

    while(current != NULL){
        if(id == *current->id){
            isFound = true;
            break;
        }
        current = current->next;
    }

    // jika id menu ada di cart...
    if(isFound){
        cout << "Kurangi sebanyak: ";
        jumlah = inputValidInt();
        while(current->qty < jumlah){
            cout << "Jumlah pesanan yang dikurangi tidak boleh lebih dari yang jumlah yang dipesan!\nKurangi sebanyak: ";
            jumlah = inputValidInt();
        }

        // tambahkan jumlah pesanan yang dihapus ke stok kembali
        FoodMenu *menu = firstMenu;
        while (menu != nullptr) {
            if (menu->id == *current->id) {
                menu->sisaStok += jumlah;
                break;
            }
            menu = menu->next;
        }

        current->qty -= jumlah;
        TOTAL_PAYMENT -= (jumlah * *current->harga);

        if(current->qty == 0){
            if(current == firstCart){
                firstCart = current->next;

                if(firstCart != NULL){
                    firstCart->prev = NULL;
                }

                delete current;
            }

            else if(current->prev != NULL && current->next != NULL){
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }

            else if(current->next == NULL){
                current->prev->next = NULL;
                delete current;
            }
        }
    } else {
        cout << "ID menu tidak ditemukan!\n";
    }

    printCart();    
}

void deleteFirstCart(){
    Cart *current;
    if(firstCart == NULL){
        return;
    }
    current = firstCart;
    firstCart = firstCart->next;
    if(firstCart != NULL){
        firstCart->prev = NULL;
    }
    current->next = NULL;
    delete current;
}

void deleteAllCart(){
    while(firstCart != NULL){
        deleteFirstCart();
    }
}

void topUp(){
    int amount;
    cout << "Masukkan nominal (kelipatan 50000): ";
    amount = inputValidInt();

    while(amount < 0 || amount % 50000 != 0){
        cout << "Jumlah tidak valid!\n";
        cout << "Masukkan nominal: ";
        amount = inputValidInt();
    }

    // cout << "Masukkan password: ";
    usersWallet[currUser] += amount;
    cout << "Top up berhasil, menambahkan Rp." << amount << " ke dalam saldo\n";

}

void addTransaction(){
    Transaction *newTransaction, *currTransaction;
    newTransaction = new Transaction;
    newTransaction->namaCust = *pUserProfile[0];
    newTransaction->total = TOTAL_PAYMENT;
    TOTAL_PAYMENT = 0;

    // kalo transaksi belum pernah ada..
    if(firstTransaction == NULL){
        newTransaction->next = NULL;
        firstTransaction = newTransaction;

    // kalo udah pernah ada...
    } else {
        newTransaction->next = firstTransaction;
        firstTransaction = newTransaction;
    }
}

int hitungTotal(){
    if(firstCart != NULL){
        Cart *curr;
        int total = 0;
        curr = firstCart;
        while(curr != NULL){
            total += ((*curr->harga) * curr->qty);
            curr = curr->next;
        }
        return total;
    } else {
        return 0;
    }
}

void checkout(){
    string confirm;
    printCart();
    cout << "\nYakin ingin checkout dan mencetak invoice? (y/n): ";
    int totalPembayaran = hitungTotal();
    confirm = inputOneWord();

    if(confirm != "y"){
        cout << "Tidak jadi checkout\n";
        return;
    } else {
        // cetakInvoice()
        // addTransaction()
        // deleteAllCart()
        // TOTAL_PAYMENT = 0
        if(usersWallet[currUser] < totalPembayaran){
            cout << "Saldo anda tidak mencukupi!\nIngin melanjutkan ke top up? (y/n): ";
            confirm = inputOneWord();
            if(confirm == "y"){
                topUp();
                cout << "silahkan checkout kembali!\n";
                return;
            } else {
                return;
            }

        } else {
            cout << "\n=================== Restoran 69 ======================\n";
            cout << "Nama Pelanggan\t: " << **(pUserProfile + 0) << endl;
            printCart();
            cout << "======================================================\n";

            addTransaction();
            deleteAllCart();
            printCart();
            usersWallet[currUser] -= totalPembayaran;
        }
    }
}

void customerDashboard(){
    int opsi;

    while(true){
        cout << "\n\n===== Selamat datang di Restoran 77! =====\n";
        printSaldo();
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Pesanan\n";
        cout << "3. Kurangi Pesanan\n";
        cout << "4. Checkout dan Cetak Invoice\n";
        cout << "5. Top Up Saldo\n";
        cout << "6. Logout\n";
        cout << "7. Keluar Aplikasi\n";
        cout << "\nOpsi\t: ";
        opsi = inputValidInt();

        switch (opsi)
        {
        case 1:
            cout << "\n=== Tambah pesanan ===\n";
            printMenu();
            addOrder();
            break;

        case 2:
            cout << "\n=== Lihat pesanan ===\n";
            printCart();
            wait();
            break;

        case 3:
            cout << "\n=== Kurangi pesanan ===\n";
            printCart();
            removeOrder();
            break;
        
        case 4:
            cout << "\n=== Checkout ===\n";
            checkout();
            break;

        case 5:
            cout << "\n=== Top Up Saldo ===\n";
            topUp();
            break;
        case 6:
            USER_FOUND = false;
            deleteAllCart();
            return;

        case 7:
            IS_CONTINUE = false;
            return;

        default:
            break;
        }

    }
}