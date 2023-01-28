#include <iostream>
#include "AVLTree.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;
struct info
{
    string name;
    string second_name;
    string adress;
    int phone_number[10];
};


Node client_info(bool WantMyNumber)
{
    string bufor;
    int opcja;
    Node data_holder;
    cout << "Firma - 0 / Osoba prywatna - 1" << endl;
    cout << "Opcja: ";
    cin >> opcja;
    if(opcja == 0)
    {
        cout << "Podaj nazwe: ";
        getline(cin, bufor);
        getline(cin, bufor);
        strcpy(data_holder.name, bufor.c_str());
        strcpy(data_holder.second_name, " ");
    }
    else
    {
        cout << "Podaj imie: ";
        getline(cin, bufor);
        getline(cin, bufor);
        strcpy(data_holder.name, bufor.c_str());
        cout << "Podaj nazwisko: ";
        getline(cin, bufor);
        strcpy(data_holder.second_name, bufor.c_str());
    }

    cout << "Podaj adres: ";
    getline(cin, bufor);
    strcpy(data_holder.adress, bufor.c_str());
    if(WantMyNumber)
    {
        cout << "Podaj numery telefonow"<<endl<<"(wpisz 0, aby zakonczyc podawanie numerow"<<endl;
        for(int i=0; i<10; i++)
        {
            cout << i+1 << " numer telefonu: ";
            cin >> data_holder.phone_number[i];
            if(data_holder.phone_number[i] == 0) return data_holder;
        }
        return data_holder;
    }
    return data_holder;
}

int main()
{
    string bufor;
    fstream file("abonamenci.bin", ios::binary | ios::in | ios::out);
    if(!file.is_open())
    {
        cout << "Blad";
        exit(1337);
    }
    Node TMP;
    file.read((char*)&TMP, sizeof(Node));
    TMP.SayMyName();
    Node* root = new Node(TMP);
    AVL AVLTree;
    while(!file.eof())
    {
        file.read((char*)&TMP, sizeof(Node));
        TMP.SayMyName();
        AVLTree.insert(TMP, root);
        if(file.fail())break;
    }

    int UP = 1, control = 0;
    while(UP)
    {
        system("CLS");
        cout << "Witaj uzytkowniku!" << endl << "Wybierz jedna z opcji:" << endl;
        cout << "1 - Dodaj abonamenta" << endl;
        cout << "2 - Usun abonamenta" << endl;
        cout << "3 - Wyszukaj abonamenta" << endl;
        cout << "0 - Zakoncz" << endl;
        cout << "Opcja: ";
        cin >> control;
        switch(control)
        {
        case 0:
            UP = 0;
            break;
        case 1:
            TMP = client_info(true);
            AVLTree.insert(TMP, root);
            system("CLS");
            break;
        case 2:
            TMP = client_info(false);
            AVLTree.deleteItem(TMP, root);
            //file.write((char*)&TMP, sizeof(Node));
            cin.get();
            cin.get();
            system("CLS");
            break;
        case 3:
            TMP = client_info(false);
            if(!AVLTree.FindItem(TMP, root))
                cout << "Brak abonamenta";
            cin.get();
            cin.get();
            system("CLS");
            break;
        }
    }

    file.close();


}
