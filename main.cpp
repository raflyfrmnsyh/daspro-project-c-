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

void addMenu(){
    string idMenu;
    FoodMenu *current;

    cout << "\nId Menu: ";
    getline(cin, idMenu);
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

        if(current != NULL){
            cout << current->harga;
        } else{
            cout << "Menu ga adaaa";
            return;
        }

        Cart *currentCart, *prevCart, *newCart;
        newCart = new Cart;
        newCart->nama = &current->nama;
        newCart->harga = &current->harga;
        newCart->next = NULL;

        if(firstCart != NULL){
            
            currentCart = firstCart;
            while(currentCart != NULL){
                if(currentCart->next == NULL){
                    prevCart = currentCart;
                }
                if(*currentCart->nama == current->nama){
                    cout << "ada ayam bakar\n";
                    currentCart->qty += 1;
                    delete newCart;
                    return;
                }
                currentCart = currentCart->next;
            }
            prevCart->next = newCart;
            newCart->qty = 1;

        } else {
            newCart->qty = 1;
            firstCart = newCart;
        }
    }
}

void printCart(){
    if(firstCart != NULL){
        Cart *current = firstCart;
        while(current != NULL){
            cout << "\n" << *current->nama << "\t\t" << *current->harga << " x " << current->qty << " = " << *current->harga * current->qty << "\n";
            current = current->next;
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
    
    printMenu();

    addMenu();
    addMenu();

    printCart();

    
}