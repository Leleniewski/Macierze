#include "Wektor.hh"
#include "Macierz.hh"


Macierz::Macierz() {
    for (int i = 0; i < ROZMIAR; ++i) {
            wartosc->rozmiar[i] = 0;
    }
}

Macierz::Macierz(Wektor tmp[ROZMIAR]) {
    for (int i = 0; i < ROZMIAR; ++i) {
        wartosc[i] = tmp[i];
    }
}


double &Macierz::operator()(unsigned int rzad, unsigned int kolumna) {

    if (rzad >= ROZMIAR|| kolumna >= ROZMIAR) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); 
    }
    return wartosc[rzad][kolumna];
}


const double &Macierz::operator () (unsigned int rzad, unsigned int kolumna) const{

    if (rzad >= ROZMIAR||kolumna >= ROZMIAR) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); 
    }

    return wartosc[rzad][kolumna];
}


Macierz Macierz::operator + (Macierz tmp) {
    Macierz wynik;
    for (int i = 0; i < ROZMIAR; ++i) {
        for (int j = 0; j < ROZMIAR; ++j) {
            wynik(i, j) = this->wartosc[i][j] + tmp(i, j);
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



/*double Macierz::wyznacznik()const{
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
*/

Macierz Macierz::zamien_wiersz(int wiersz, int kolumna)const{
    Macierz tmp;
    double komórka=1;
    int licznik_zamian =1;
    int wiersz_zamien;

    wiersz_zamien = wiersz + 1;
    while((licznik_zamian<ROZMIAR-wiersz)&&(komórka!=0)){
        komórka=tmp(wiersz,kolumna);
        std::swap(tmp.wartosc[wiersz],tmp.wartosc[wiersz_zamien]);
        tmp.wartosc[wiersz_zamien]=tmp.wartosc[wiersz_zamien]*(-1);
        licznik_zamian++;
        wiersz_zamien++;
    }
    return tmp;
}

bool Macierz::czy_zero(int wiersz, int kolumna){
    for(wiersz;wiersz<ROZMIAR;++wiersz){
        if((*this)(wiersz,kolumna)!=0){
            return true;
        }else{
            return false;
        }
    }
}

Wektor Macierz::wyz_blad(Wektor& x, Wektor& wyn){
  Wektor blad;
  blad=(*this)*x;
  blad=blad-wyn;
  return blad;
}

double Macierz::Gauss(){
    double dzielniki[ROZMIAR-1];
    double wyznacznik=1;
    Macierz pomocnicza;
    Wektor zerowanie;
    int wiersz=0, kolumna=0, licznik_gauss = 0;
    int w, k;
    
    pomocnicza = (*this);

    for(int j=1; j<ROZMIAR; j++){
        if(pomocnicza(wiersz,kolumna)!=0){
        w=wiersz;
        k=kolumna;
        dzielniki[wiersz] = pomocnicza(wiersz,kolumna);
        zerowanie=pomocnicza.wartosc[wiersz]/dzielniki[wiersz];
        for(int i=1; i<ROZMIAR-wiersz;i++){
            pomocnicza.wartosc[w+1] = pomocnicza.wartosc[w+1]- (zerowanie*pomocnicza(w+1,k));
            w++;
        }
        wiersz++;
        kolumna++;
        std::cout << pomocnicza << std::endl;
    }

    for(int k=0;k<ROZMIAR;k++){
    wyznacznik=wyznacznik*pomocnicza(k,k);
    }   
    std::cout << wyznacznik << std::endl;

    return wyznacznik;
}