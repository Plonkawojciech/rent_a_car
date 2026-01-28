#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Struktura - pudełko na WSZYSTKIE dane z polecenia
struct Samochod {
    string marka, model, miejsca, nadwozie, rejestracja, skrzynia, kolor, silnik, data_wyp, data_zwr;
};

// Baza danych (lista)
vector<Samochod> baza;

// 1. Wczytywanie z pliku o nazwie podanej przez użytkownika
void wczytaj() {
    string nazwa, linia;
    cout << "Podaj nazwe pliku .csv: ";
    cin >> nazwa;

    ifstream plik(nazwa);
    baza.clear();

    while (getline(plik, linia)) {
        stringstream ss(linia);
        Samochod s;
        // Czytamy wszystko po przecinku
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

// 2. Wyświetlanie listy (tylko Model i Marka - zgodnie z poleceniem)
void lista() {
    cout << "\n--- LISTA SAMOCHODOW ---" << endl;
    for (int i = 0; i < baza.size(); i++) {
        cout << i + 1 << ". " << baza[i].marka << " " << baza[i].model << endl;
    }
}

// 3. Wyświetlanie całego opisu wybranego samochodu
// (Tutaj dodałem brakujące pola: miejsca, nadwozie, kolor, silnik)
void szczegoly() {
    lista();
    int nr;
    cout << "Podaj numer auta: ";
    cin >> nr;
    
    // Zakładamy, że user podał dobry numer
    Samochod s = baza[nr - 1]; 

    cout << "\n--- SZCZEGOLY ---" << endl;
    cout << "Marka: " << s.marka << endl;
    cout << "Model: " << s.model << endl;
    cout << "Liczba miejsc: " << s.miejsca << endl;
    cout << "Typ nadwozia: " << s.nadwozie << endl;
    cout << "Nr rejestracyjny: " << s.rejestracja << endl;
    cout << "Skrzynia biegow: " << s.skrzynia << endl;
    cout << "Kolor: " << s.kolor << endl;
    cout << "Pojemnosc silnika: " << s.silnik << " cm3" << endl;
    cout << "Data ost. wypozyczenia: " << s.data_wyp << endl;
    cout << "Data ost. zwrotu: " << s.data_zwr << endl;
}

// 4. Dodawanie nowego samochodu
void dodaj() {
    Samochod s;
    cout << "\n--- DODAWANIE ---" << endl;
    cout << "Marka: "; cin >> s.marka;
    cout << "Model: "; cin >> s.model;
    cout << "Liczba miejsc: "; cin >> s.miejsca;
    cout << "Nadwozie: "; cin >> s.nadwozie;
    cout << "Nr rejestracyjny: "; cin >> s.rejestracja;
    cout << "Skrzynia (Manualna/Automatyczna): "; cin >> s.skrzynia;
    cout << "Kolor: "; cin >> s.kolor;
    cout << "Silnik (cm3): "; cin >> s.silnik;
    
    // Nowe auto nie ma historii, wiec puste albo stare daty
    s.data_wyp = "";
    s.data_zwr = "2000-01-01"; 
    
    baza.push_back(s);
    cout << "Dodano!" << endl;
}

// 5. Filtrowanie wg rodzaju skrzyni biegów
void filtruj() {
    string typ;
    cout << "Jaka skrzynia (Manualna/Automatyczna): "; 
    cin >> typ;
    
    cout << "\n--- WYNIKI FILTROWANIA ---" << endl;
    for (int i = 0; i < baza.size(); i++) {
        // Sprawdzamy czy tekst w bazie jest taki sam jak wpisany
        if (baza[i].skrzynia == typ) {
            cout << baza[i].marka << " " << baza[i].model << " (" << baza[i].rejestracja << ")" << endl;
        }
    }
}

// 6. Zapis listy do pliku .csv
void zapisz() {
    string nazwa;
    cout << "Podaj nazwe pliku do zapisu: "; 
    cin >> nazwa;
    
    ofstream plik(nazwa);
    for (int i = 0; i < baza.size(); i++) {
        plik << baza[i].marka << "," << baza[i].model << "," << baza[i].miejsca << ","
             << baza[i].nadwozie << "," << baza[i].rejestracja << "," << baza[i].skrzynia << ","
             << baza[i].kolor << "," << baza[i].silnik << "," << baza[i].data_wyp << ","
             << baza[i].data_zwr << endl;
    }
    cout << "Zapisano!" << endl;
}

// 7. i 8. Wypożyczenie i Zwrot (aktualizacja dat)
void status(bool czyWyp) {
    lista();
    int nr;
    string data;
    cout << "Wybierz numer auta: "; cin >> nr;
    cout << "Podaj date (RRRR-MM-DD): "; cin >> data;
    
    if (czyWyp) {
        baza[nr - 1].data_wyp = data;
        cout << "Zaktualizowano date wypozyczenia." << endl;
    } else {
        baza[nr - 1].data_zwr = data;
        cout << "Zaktualizowano date zwrotu." << endl;
    }
}

// 9. Dostępność we wskazanym terminie (na podstawie daty zwrotu)
void termin() {
    string data;
    cout << "Sprawdz dostepnosc na dzien (RRRR-MM-DD): "; 
    cin >> data;
    
    cout << "\n--- DOSTEPNE AUTA ---" << endl;
    for (int i = 0; i < baza.size(); i++) {
        // Jezeli data zwrotu jest mniejsza (wczesniejsza) niz data klienta -> auto jest wolne
        if (baza[i].data_zwr <= data) {
            cout << baza[i].marka << " " << baza[i].model << " (Zwrot: " << baza[i].data_zwr << ")" << endl;
        }
    }
}

int main() {
    int w;
    do {
        cout << "\n=== WYPOZYCZALNIA ===" << endl;
        cout << "1. Wczytaj z pliku" << endl;
        cout << "2. Lista aut (Marka, Model)" << endl;
        cout << "3. Szczegoly (Pelny opis)" << endl;
        cout << "4. Dodaj samochod" << endl;
        cout << "5. Filtruj (Skrzynia)" << endl;
        cout << "6. Zapisz do pliku" << endl;
        cout << "7. Wypozycz (Aktualizacja daty)" << endl;
        cout << "8. Zwroc (Aktualizacja daty)" << endl;
        cout << "9. Sprawdz dostepnosc" << endl;
        cout << "0. Koniec" << endl;
        cout << "Wybor: ";
        cin >> w;

        if (w==1) wczytaj();
        if (w==2) lista();
        if (w==3) szczegoly();
        if (w==4) dodaj();
        if (w==5) filtruj();
        if (w==6) zapisz();
        if (w==7) status(true);  // true = wypozyczenie
        if (w==8) status(false); // false = zwrot
        if (w==9) termin();
    } while (w != 0);
    return 0;
}