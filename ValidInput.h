#pragma once

int inputValidInt(){
    int answer;
    cin >> answer;
    while(!cin){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Masukkan angka! Ulangi: ";
        cin >> answer;
    }
    cin.clear();
    cin.ignore(100, '\n');
    return answer;
}

string inputOneWord(){
    string answer;
    cin >> answer;
    cin.clear();
    cin.ignore(100, '\n');
    return answer;
}

void wait(){
    cout << "Enter untuk lanjutkan\n";
    cin.get();
    cin.clear();
    cin.ignore(100,'\n');
}
