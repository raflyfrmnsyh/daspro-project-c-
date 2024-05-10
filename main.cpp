#include <iostream>
#include <string>
using namespace std;

// <user db>
const int MAX_USER = 20;
const int NUM_COLUMNS = 3; // username, password, role

int numUsers = 0;
int currUser;
bool IS_CONTINUE = true;
bool USER_FOUND = false;

string users[MAX_USER][NUM_COLUMNS];
int usersWallet[MAX_USER]; // array nyimpen saldo semua user
string (*pUsers)[NUM_COLUMNS] = users;

// string userProfile[numColumns];
string* pUserProfile[NUM_COLUMNS];

// </user db>

#include "UserGate.h"

struct FoodMenu{
    string kategori;
    string id;
    string nama;
    int harga;
    int sisaStok;
    FoodMenu *next;
    FoodMenu *prev;
};

struct Cart{
    string *nama;
    string *id;
    int *harga;
    int qty;
    Cart *next;
    Cart *prev;
};

int TOTAL_PAYMENT = 0;

struct Transaction{
    string namaCust;
    int total;
    Transaction *next;
};

Cart *firstCart;
FoodMenu *firstMenu;
Transaction *firstTransaction;

bool isMenuEmpty(){
    if(firstMenu == NULL){
        return true;
    } else {
        return false;
    }
}

void printMenu(){
    FoodMenu *current;
    if(!isMenuEmpty()){
        current = firstMenu;

        while(current != NULL){
            if(current->prev == NULL || current->kategori != current->prev->kategori){
                cout << "\n[id]\t[" << current->kategori << "]" << "  \t\t[Harga]\t\t\t[Stok]\n";
            }
            cout << current->id << "\t" << current->nama << "\t\tRp " << current->harga << "  \t\t" << current->sisaStok << "\n";
            current = current->next;
        }
    }
}

void printSaldo(){
    cout << "[Saldo Anda: Rp." << usersWallet[currUser] << " ]\n";
}

#include "Customer.h"
#include "Admin.h"

void initApp(){
    createMenu("Lauk", "a1", "Ayam Bakar", 15000, 10);
    createMenu("Lauk", "a2", "Ayam Goreng", 13000, 20);
    createMenu("Lauk", "a3", "Ayam Geprek", 17000, 20);

    createMenu("Nasi", "n1", "Nasi Putih", 5000, 20);
    createMenu("Nasi", "n2", "Nasi Kuning", 7000, 20);
    createMenu("Nasi", "n3", "Nasi Kebuli", 10000, 20);

    createMenu("Minuman", "m1", "Es Teh Manis", 7000, 29);
    createMenu("Minuman", "m2", "Air Mineral", 4000, 20);
    createMenu("Minuman", "m3", "Es Jeruk", 8000, 20);

    createMenu("Lauk", "a4", "Ikan Bakar", 23000, 10);
    createMenu("Nasi", "n4", "Nasi Goreng", 13000, 5);

    createAccount("admin", "admin", "admin", 0);
    createAccount("caca", "caca", "customer", 100000);
}

int main(){
    initApp();
    while(IS_CONTINUE){
        loginGate();

        if(USER_FOUND){
            if(*(pUserProfile[2]) == "customer"){
                customerDashboard();
            } else if (*(pUserProfile[2]) == "admin"){
                adminDashboard();
            }
        }
    }
    cout << "Enter untuk lanjutkan";
    cin.get();
    
}