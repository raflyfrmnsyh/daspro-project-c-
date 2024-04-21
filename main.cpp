#include <iostream>
#include <string>
using namespace std;

// <user db>
const int maxUsers = 20;
const int numColumns = 3;

int numUsers = 0;
bool isContinue = true;

string users[maxUsers][numColumns];
string (*pUsers)[numColumns] = users;

// string userProfile[numColumns];
string* pUserProfile[numColumns];

// </user db>

#include "UserGate.h"

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
                cout << "\n[id]\t[" << current->kategori << "]\n";
            }
            cout << current->id << "\t" << current->nama << "\t\tRp " << current->harga << "\n";
            current = current->next;
        }
    }
}

// FoodMenu * cariMenu(string namaMenu){
//     FoodMenu *current;
//     if(!isMenuEmpty()){
//         current = firstMenu;
//         while(current != NULL){
//             if(current->nama == namaMenu){
//                 return current;
//             }
//             current = current->next;
//         }
//         return NULL;
//     } else {
//         return NULL;
//     }
// }

#include "Customer.h"
#include "Admin.h"
#include "rafly.h"

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

    createAccount("admin1", "admin123", "admin");
    createAccount("c", "c", "customer");
}

int main(){
    initApp();
    while(isContinue){
        loginGate();

        if(*(pUserProfile[2]) == "customer"){
            customerDashboard();
        } else if (*(pUserProfile[2]) == "admin"){
            adminDashboard();
        }
    }
    cout << "Enter untuk lanjutkan";
    cin.get();
    
}