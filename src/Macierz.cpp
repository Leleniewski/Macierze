#include "Wektor.hh"
#include "Macierz.hh"


Macierz::Macierz() {
    for (int i = 0; i < ROZMIAR; ++i) {
        for(int j=0; j<ROZMIAR; ++j){
            wartosc[i][j]=0;
        }
    }
}

Macierz::Macierz(Wektor tmp[ROZMIAR]){
    for (int i = 0; i < ROZMIAR; ++i){
        for(int j=0; j<ROZMIAR;++j){
            wartosc[i][j] = tmp[i][j];
        }
    }
}


double &Macierz::operator()(unsigned int rzad, unsigned int kolumna){
    return wartosc[rzad][kolumna];
}


const double &Macierz::operator()(unsigned int rzad, unsigned int kolumna)const{
    return wartosc[rzad][kolumna];
}


Macierz Macierz::operator + (Macierz tmp) {
    Macierz wynik;
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            wynik(i, j) = (*this).wartosc[i][j] + tmp(i, j);
        }
    }
    return wynik;
}

Wektor Macierz::operator * (Wektor tmp) {
    Wektor result;
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            result[i] += wartosc[i][j] * tmp[j];
        }
    }
    return result;
}


std::istream &operator>>(std::istream &in, Macierz &mac) {
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            in >> mac(i, j);
        }
    }
    return in;
}


std::ostream &operator<<(std::ostream &out, const Macierz &mac) {
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            out << "| " << mac(i, j) << " |\t"; 
        }
        std::cout << std::endl;
    }
    return out;
}


Macierz Macierz::transponowanie(){
Macierz transponowana;
    for(int i=0;i<ROZMIAR;++i){
        for(int j=0;j<ROZMIAR;++j){
            transponowana(i,j)=(*this)(j,i);
        }
    }
return transponowana;
}

