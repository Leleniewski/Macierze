#include "Wektor.hh"
#include <cmath>

Wektor::Wektor() {
    for (int i = 0; i < ROZMIAR; ++i) {
        (*this)[i] = 0;
    }
}


Wektor::Wektor(double tmp[ROZMIAR]) {
    for (int i = 0; i < ROZMIAR; ++i) {
       (*this)[i] = tmp[i];
    }
}


Wektor Wektor::operator + (const Wektor &v) {
    Wektor wynik;
    for (int i = 0; i < ROZMIAR; ++i) {
      wynik[i] = (*this)[i] + v[i];
    }
    return wynik;
}


Wektor Wektor::operator - (const Wektor &v) {
    Wektor wynik;
    for (int i = 0; i < ROZMIAR; ++i) {
        wynik[i] = (*this)[i] - v[i];
    }
    return wynik;
}


Wektor Wektor::operator * (const double &tmp) {
    Wektor wynik;
    for (int i = 0; i < ROZMIAR; ++i) {
        wynik[i] = (*this)[i] * tmp;
    }
    return wynik;
}

double Wektor::operator * (const Wektor &Wek){
    double wynik;
    double tab[ROZMIAR];
    for(int i=0; i<ROZMIAR; ++i) {
        tab[i] = (*this)[i] * Wek[i];
        wynik += tab[i];
    }
    return wynik;
}

Wektor Wektor::operator / (const double &tmp) {
    Wektor wynik;

    for (int i = 0; i < ROZMIAR; ++i) {
        wynik[i] = (*this)[i] / tmp;
    }
    return wynik;
}


const double &Wektor::operator [] (int index) const {
    if (index < 0 || index >= ROZMIAR) {
        std::cerr << "Error: Wektor jest poza zasiegiem!" << std::endl;
    } 
    return rozmiar[index];
}

double &Wektor::operator[](int index) {
    return const_cast<double &>(const_cast<const Wektor *>(this)->operator[](index));
}


std::ostream &operator << (std::ostream &out, Wektor const &tmp) {
    for (int i = 0; i < ROZMIAR; ++i) {
        out << "[ " << tmp[i] << " ] ";
    }
    return out;
}


std::istream &operator >> (std::istream &in, Wektor &tmp) {
    for (int i = 0; i < ROZMIAR; ++i) {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}

double Wektor::dl_wek(){
double dl_wek_bledu;
Wektor blad = (*this);

dl_wek_bledu=sqrt(blad*blad);

return dl_wek_bledu;
}