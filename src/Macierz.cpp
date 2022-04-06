#include "Wektor.hh"
#include "Macierz.hh"


Macierz::Macierz() {
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            wartosc[i][j] = 0;
        }
    }
}

Macierz::Macierz(Wektor tmp[ROZMIAR]) {
    for (int i = 0; i < ROZMIAR; ++i) {
        wartosc[i] = tmp[i];
    }
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

double &Macierz::operator()(unsigned int row, unsigned int column) {

    if (row >= ROZMIAR|| column >= ROZMIAR) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); 
    }
    return wartosc[row][column];
}


const double &Macierz::operator () (unsigned int row, unsigned int column) const{

    if (row >= ROZMIAR||column >= ROZMIAR) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); 
    }

    return wartosc[row][column];
}


Macierz Macierz::operator + (Macierz tmp) {
    Macierz result;
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            result(i, j) = this->wartosc[i][j] + tmp(i, j);
        }
    }
    return result;
}


std::istream &operator>>(std::istream &in, Macierz &mat) {
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            in >> mat(i, j);
        }
    }
    return in;
}


std::ostream &operator<<(std::ostream &out, const Macierz &mat) {
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            out << "| " << mat(i, j) << " |\t"; 
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



double Macierz::wyznacznik()const{
double wyznacznik;
double a, b, c;

a=(*this)(0,0)*(((*this)(1,1)*(*this)(2,2))-((*this)(1,2)*(*this)(2,1)));
b=(*this)(0,1)*(((*this)(1,0)*(*this)(2,2))-((*this)(1,2)*(*this)(2,0)));
c=(*this)(0,2)*(((*this)(1,0)*(*this)(2,1))-((*this)(1,1)*(*this)(2,0)));

wyznacznik = a-b+c;

return wyznacznik;
}


double Macierz::wyznacznik_x(Wektor &v) const{
Macierz x;
x=(*this);
double wyznacznik;
        for(int i=0;i<ROZMIAR;++i){
            x(i,0)=v[i];
        }
     wyznacznik=x.wyznacznik();

return wyznacznik;
}


double Macierz::wyznacznik_y(Wektor &v) const{
Macierz y;
y=(*this);
double wyznacznik;
        for(int i=0;i<ROZMIAR;++i){
            y(i,1)=v[i];
        }
     wyznacznik=y.wyznacznik();

return wyznacznik;
}


double Macierz::wyznacznik_z(Wektor &v)const{
Macierz z;
z=(*this);
double wyznacznik;
    for(int i=0;i<ROZMIAR;++i){
        z(i,2)=v[i];
    }
    wyznacznik=z.wyznacznik();

return wyznacznik;
}



Wektor Macierz::oblicz(Wektor &v, double wyznacznik_u){
double wyznacznik_x, wyznacznik_y, wyznacznik_z;
double tab[ROZMIAR];
Wektor wynik;

    wyznacznik_x=(*this).wyznacznik_x(v);
    tab[0] = wyznacznik_x/wyznacznik_u; 
    wyznacznik_y=(*this).wyznacznik_y(v);
    tab[1] = wyznacznik_y/wyznacznik_u;
    wyznacznik_z=(*this).wyznacznik_z(v);
    tab[2] = wyznacznik_z/wyznacznik_u;
    wynik=tab;
    std::cout << "Rozwiązanie układu równań (x1,x2,x3) " << std::endl;
    std::cout << wynik << std::endl << std::endl;
    return wynik;

}


Wektor Macierz::wyz_blad(Wektor& x, Wektor& wyn){
  Wektor blad;
  blad=(*this)*x;
  blad=blad-wyn;
  return blad;
}

