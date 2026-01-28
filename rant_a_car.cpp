#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Struktura - nasze pudełko na dane
struct Samochod {
    string marka, model, miejsca, nadwozie, rejestracja, skrzynia, kolor, silnik, data_wyp, data_zwr;
};

// Baza danych w pamięci
vector<Samochod> baza;

// 1. Wczytywanie - bez sprawdzania czy plik istnieje
void wczytaj() {
    string nazwa, linia;
    cout << "Podaj nazwe pliku: ";
    cin >> nazwa;

    ifstream plik(nazwa);
    baza.clear();

    while (getline(plik, linia)) {
        stringstream ss(linia);
        Samochod s;
        // Pobieramy dane po przecinku
        getline(ss, s.marka, ',');
        getline(ss, s.model, ',');
        getline(ss, s.miejsca, ',');
        getline(ss, s.nadwozie, ',');
        getline(ss, s.rejestracja, ',');
        getline(ss, s.skrzynia, ',');
        getline(ss, s.kolor, ',');
        getline(ss, s.silnik, ',');
        getline(ss, s.data_wyp, ',');
        getline(ss, s.data_zwr, ',');
        
        baza.push_back(s);
    }
    cout << "Wczytano!" << endl;
}

// 2. Wyświetlanie listy
void lista() {
    cout << "\n--- LISTA ---" << endl;
    for (int i = 0; i < baza.size(); i++) {
        cout << i + 1 << ". " << baza[i].marka << " " << baza[i].model << endl;
    }
}

// 3. Szczegóły - zakładamy, że numer jest dobry
void szczegoly() {
    lista();
    int nr;
    cout << "Podaj numer auta: ";
    cin >> nr;
    
    // Od razu pobieramy auto, bez sprawdzania czy nr jest dobry
    // nr-1, bo w informatyce liczymy od zera
    Samochod s = baza[nr - 1]; 

    cout << "Marka: " << s.marka << "\nModel: " << s.model;
    cout << "\nRejestracja: " << s.rejestracja << "\nSkrzynia: " << s.skrzynia;
    cout << "\nWypozyczony: " << s.data_wyp << "\nZwrot: " << s.data_zwr << endl;
}

// 4. Dodawanie - prosto w dół
void dodaj() {
    Samochod s;
    cout << "Marka: "; cin >> s.marka;
    cout << "Model: "; cin >> s.model;
    cout << "Miejsca: "; cin >> s.miejsca;
    cout << "Nadwozie: "; cin >> s.nadwozie;
    cout << "Rejestracja: "; cin >> s.rejestracja;
    cout << "Skrzynia: "; cin >> s.skrzynia;
    cout << "Kolor: "; cin >> s.kolor;
    cout << "Silnik: "; cin >> s.silnik;
    s.data_wyp = "";
    s.data_zwr = "";
    baza.push_back(s);
}

// 5. Filtrowanie
void filtruj() {
    string typ;
    cout << "Jaka skrzynia: "; cin >> typ;
    for (int i = 0; i < baza.size(); i++) {
        if (baza[i].skrzynia == typ) {
            cout << baza[i].marka << " " << baza[i].model << endl;
        }
    }
}

// 6. Zapis
void zapisz() {
    string nazwa;
    cout << "Plik do zapisu: "; cin >> nazwa;
    ofstream plik(nazwa);
    for (int i = 0; i < baza.size(); i++) {
        plik << baza[i].marka << "," << baza[i].model << "," << baza[i].miejsca << ","
             << baza[i].nadwozie << "," << baza[i].rejestracja << "," << baza[i].skrzynia << ","
             << baza[i].kolor << "," << baza[i].silnik << "," << baza[i].data_wyp << ","
             << baza[i].data_zwr << endl;
    }
}

// 7. Wypożycz/Zwróć - jedna funkcja, bez ifów sprawdzających numer
void status(bool czyWyp) {
    lista();
    int nr;
    string data;
    cout << "Numer auta: "; cin >> nr;
    cout << "Data: "; cin >> data;
    
    if (czyWyp) baza[nr - 1].data_wyp = data;
    else        baza[nr - 1].data_zwr = data;
}

// 8. Dostępność
void termin() {
    string data;
    cout << "Data: "; cin >> data;
    for (int i = 0; i < baza.size(); i++) {
        if (baza[i].data_zwr <= data) {
            cout << baza[i].marka << " - Wolny" << endl;
        }
    }
}

int main() {
    int w;
    do {
        cout << "\n1.Wczytaj 2.Lista 3.Info 4.Dodaj 5.Filtr 6.Zapis 7.Wypozycz 8.Zwrot 9.Termin 0.Koniec\nWybor: ";
        cin >> w;
        if (w==1) wczytaj();
        if (w==2) lista();
        if (w==3) szczegoly();
        if (w==4) dodaj();
        if (w==5) filtruj();
        if (w==6) zapisz();
        if (w==7) status(true);
        if (w==8) status(false);
        if (w==9) termin();
    } while (w != 0);
    return 0;
}