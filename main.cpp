#include <iostream>
using namespace std;

struct FoodMenu{
    string kategori;
    string nama;
    int harga;
    FoodMenu *next, *prev;
};

FoodMenu *firstMenu;

bool isMenuEmpty(){
    if(firstMenu == NULL){
        return true;
    } else {
        return false;
    }
}

void createMenu(string kategori, string nama, int harga){
    FoodMenu *newMenu, *current;
    newMenu = new FoodMenu;
    newMenu->nama = nama;
    newMenu->kategori = kategori;
    newMenu->harga = harga;
    newMenu->next = NULL;

    if(!isMenuEmpty()){
        current = firstMenu;
        while(current->next != NULL){
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

    // TESTING DOUBLE LINKED LIST
        while(current->next != NULL){
            if(current->prev == NULL || current->kategori != current->prev->kategori){
                cout << "[" << current->kategori << "]\n";
            }
            cout << current->nama << "\t\tRp " << current->harga << "\n";
            current = current->next;
        }
        cout << current->nama << "\t\tRp " << current->harga << "\n";

        current = current->prev;
        while(current != NULL){
            cout << current->nama << "\t\tRp " << current->harga << "\n";
            current = current->prev;
        }
    }
}

void fileInit(){

}


int main(){
    // ini testing dulu
    // struct FoodMenu paketan[3] = {
    //     {"Ayam", 1000},
    //     {"Bebek", 2000},
    //     {"Sapi", 3000}
    // };
    // cout << paketan[0].nama << endl;

    createMenu("Lauk", "Ayam Bakar", 15000);
    createMenu("Lauk", "Ayam Goreng", 10000);
    createMenu("Lauk", "Ayam Geprek", 17000);

    printMenu();

    
}