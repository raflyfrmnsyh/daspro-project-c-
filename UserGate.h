#include <iostream>
#include <string>
#include <conio.h>
#include "ValidInput.h"

#pragma once
using namespace std;

void printArrayUsers(){
    for(int i = 0; i < MAX_USER; i++){
        // [i][0]
        if ( *(*(pUsers + i)) == ""){
            continue;
        }
        for(int j = 0; j < 3; j++){
            cout << *(*(pUsers + i) + j) << " ";
        }
        cout << endl;
    }
}


void createAccount(string name, string password, string role, int saldo){
    *(*(pUsers + numUsers) + 0) = name;
    *(*(pUsers + numUsers) + 1) = password;
    *(*(pUsers + numUsers) + 2) = role;
    usersWallet[numUsers] = saldo;
    numUsers++;
}

bool isUsernameTaken(const string& username) {
    for (int i = 0; i < numUsers; ++i) {
        if (*(*(pUsers + i)) == username) {
            return true;
        }
    }
    return false;
}

void registerUser() {
if (numUsers < MAX_USER) {

        const int max_pass_length = 100;
        char pass[max_pass_length];
        char ch;
        int i = 0;

        string username, role;
        while (true)
        {
            cout << "Masukkan username: ";
            username = inputOneWord();

            while(isUsernameTaken(username)){
                cout << "Username sudah digunakan!\nUsername: ";
                username = inputOneWord();
            }
            
            cout << "Masukkan password : ";
            // password = inputOneWord();
            while(true){
                ch = getch();

                if (ch == '\r'){
                    pass[i] = '\0';
                    break;
                }

                else if (ch == '\b' && i > 0){
                    cout << "\b \b";
                    i--;
                } else if (i < max_pass_length - 1){
                    pass[i++] = ch;
                    cout << '*';
                }
            }

            cout << "\nMasukkan role\n\t1: customer\n\t2: admin ";
            role = inputOneWord();

            if (role == "1") {
                role = "customer";
                break;

            } else if (role == "2") {
                role = "admin";
                break;

            } else {
                cout << "Role tidak valid. Silakan pilih role yang sesuai." << endl;
                return;
            }
        }
        createAccount(username, pass, role, 0);
        cout << "Pengguna berhasil terdaftar." << endl;
        
    } else {
        cout << "Database pengguna penuh. Tidak bisa mendaftarkan pengguna baru." << endl;
    }
}

void loginUser() {
    const int max_pass_length = 100;
    char pass[max_pass_length];
    char ch;
    int i = 0;

    string username, password;
    cout << "Masukkan username: ";
    username = inputOneWord();


    cout << "Masukkan password: ";

        while(true){
            ch = getch();

            if (ch == '\r'){
                pass[i] = '\0';
                break;
            }

            else if (ch == '\b' && i > 0){
                cout << "\b \b";
                i--;
            } else if (i < max_pass_length - 1){
                pass[i++] = ch;
                cout << '*';
            }
        }
    // password = inputOneWord();

    for (int i = 0; i < numUsers; ++i) {
        if (*(*(pUsers + i) + 0) == username && *(*(pUsers + i) + 1) == pass) {
            cout << "Login berhasil. Selamat datang, " << username << "!" << endl;
            // cout << "Role: " << *(*(pUsers + i) + 2) << endl;

            // saving user profile (usnm, pw, role)
            pUserProfile[0] = (*(pUsers + i) + 0); // username
            pUserProfile[1] = (*(pUsers + i) + 1); // password
            pUserProfile[2] = (*(pUsers + i) + 2); // role

            // cout << endl << pUserProfile[0] << " : " << *pUserProfile[0] << endl;
            // cout << pUserProfile[1] << " : " << *pUserProfile[1] << endl;
            // cout << pUserProfile[2] << " : " << *pUserProfile[2] << endl;
            currUser = i;
            USER_FOUND = true;
            break;
        }
    }

    if (!USER_FOUND) {
        cout << "\n(Login gagal. Silakan coba lagi)\n";
    }
}

void loginGate(){
    int choice;
    while(true) {
        cout << "\nMENU AWAL" << endl;
        cout << "1. Daftar" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        
        cout << "(database array user):\n";
        printArrayUsers();
        cout << endl << endl;

        cout << "Pilihan Anda: ";
        choice = inputValidInt();

        switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                return;

            case 3:
                cout << "Terima kasih. Sampai jumpa!" << endl;
                IS_CONTINUE = false;
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}