#include "UkladRownanLiniowych.hh"
#include <iostream>
#include <cmath>
#include <iomanip>
#include "Macierz.hh"
#include "Wektor.hh"


UkladRownanLiniowych::UkladRownanLiniowych(Macierz mac, Wektor wek){
    this->mac=mac;
    this->wek_wyn=wek;
}

UkladRownanLiniowych::UkladRownanLiniowych(){
    for(int i=0;i<ROZMIAR;++i){
        for(int j=0;j<ROZMIAR;++j){
            mac(i,j)=0;
        }
    }
    for(int i=0;i<ROZMIAR;++i){
        wek_wyn[i]=0;
    }
}

std::istream& operator >> (std::istream &Strm, UkladRownanLiniowych &UklRown){
    double liczby;
    for(int i=0; i<ROZMIAR; ++i){
        for (int j=0; j<ROZMIAR ; ++j) {
        Strm >> liczby;
        UklRown.setUkl_macierz(i, j, liczby);
        }
    }

    for(int i=0; i<ROZMIAR; ++i){
        Strm>>liczby;
        UklRown.setUkl_wektor(i,liczby);
    }

    return Strm;
}

std::ostream &operator<<(std::ostream &Strm, UkladRownanLiniowych &UklRown){
    for (int i=0;i<ROZMIAR;++i){
        Strm << "| ";
        for(int j=0;j<ROZMIAR; ++j){
            Strm << UklRown.getUkl_macierz(i,j)<<"\t";
        }
        Strm << "| |x_" << i+1 << "| ";
        if(i==1)
            Strm << " = ";
	    else
            Strm << "   ";
	Strm << " [ " << UklRown.getUkl_wektor(i) << " ] ";
        std::cout << std::endl;
    }
    return Strm;
}

bool UkladRownanLiniowych::zeruj_kol(int wiersz, int kolumna){
    int j=wiersz+1, i=0;
    
    if(wiersz<ROZMIAR && kolumna<ROZMIAR-1){
        for(i=wiersz+1; i<ROZMIAR; i++){
            if((*this).mac(i,kolumna)==0)
                ++j;
        }
    }
    if(j==i){
        std::cout << "Równanie nie ma jednego rozwiązania" <<std::endl<<std::endl;
        exit(0);
        return false;

    }
    else{
        return true;
    }
}

UkladRownanLiniowych UkladRownanLiniowych::zamiana_wierszy(int wiersz, int kolumna)const{
    UkladRownanLiniowych tmp = (*this);
    int i=wiersz+1;
    
    if(tmp.mac(wiersz,kolumna)==0){
        while (i < ROZMIAR && tmp.mac(i,kolumna) == 0) {
            ++i;
        }
        if (tmp.mac(i,kolumna) != 0) {
            for (int j = kolumna; j < ROZMIAR; ++j) {
                std::swap(tmp.mac(wiersz, j), tmp.mac(i, j));
                std::swap(tmp.wek_wyn[wiersz], tmp.wek_wyn[i]);
            }
            tmp.Wyswietl_zamiana_wierszy(wiersz,i);
        }
    }
    return tmp;
}

void UkladRownanLiniowych::czy_zero(int wiersz, int kolumna){
    if((*this).zeruj_kol(wiersz, kolumna)==true){
        (*this)=(*this).zamiana_wierszy(wiersz,kolumna);
    }
}

UkladRownanLiniowych UkladRownanLiniowych::Gauss(int wiersz, int kolumna){
    double pomocnicza;

    for (int j = wiersz+1; j < ROZMIAR; ++j){
        pomocnicza = (*this).mac(j, kolumna);
        for (int i = kolumna; i < ROZMIAR; ++i) {
            (*this).mac(j, i) = (*this).mac(j, i) - (pomocnicza * (*this).mac(wiersz, i));
        }
        (*this).wek_wyn[j] = (*this).wek_wyn[j] - (pomocnicza *(*this).wek_wyn[wiersz]);
        if (pomocnicza != 0){
            (*this).Wyswietl_zerowanie(j, pomocnicza, wiersz);
        }
    }
    if(wiersz>0){
        for (int j = wiersz; j >0; --j) {
            pomocnicza = (*this).mac(j-1, kolumna);
            for (int i = kolumna; i < ROZMIAR; ++i) {
                (*this).mac(j-1, i) = (*this).mac(j-1, i) - (pomocnicza * (*this).mac(wiersz, i));
            }
            (*this).wek_wyn[j-1] = (*this).wek_wyn[j-1] - (pomocnicza *(*this).wek_wyn[wiersz]);
            if (pomocnicza != 0){
                (*this).Wyswietl_zerowanie(j-1, pomocnicza, wiersz);
            }
        }
    }   
        return (*this);
    }

UkladRownanLiniowych UkladRownanLiniowych::dzielenie_wierszy(int wiersz, int kolumna){
    double dzielnik;
    dzielnik = (*this).mac(wiersz, kolumna);

    for (int i = 0; i < ROZMIAR; ++i) {
        (*this).mac(wiersz, i) = (*this).mac(wiersz, i) / dzielnik;
    }
    (*this).wek_wyn[wiersz] = (*this).wek_wyn[wiersz]/dzielnik;
    if (dzielnik != 1){
        (*this).Wyswietl_dzielenie(wiersz, dzielnik);
    }
 
    return (*this);
}

UkladRownanLiniowych UkladRownanLiniowych::dzialania(int wiersz, int kolumna){
    (*this).dzielenie_wierszy(wiersz, kolumna);
    (*this).Gauss(wiersz, kolumna);
    return (*this);
}


Wektor UkladRownanLiniowych::Oblicz(){
    Wektor wynik;
    int wiersze =0, kolumny =0;

    (*this).czy_zero(wiersze, kolumny);
    for(int w=0; w<ROZMIAR;++w){
        (*this).dzialania(wiersze,kolumny);
        if(wiersze<ROZMIAR){
        wiersze++;
        kolumny++;
        (*this).czy_zero(wiersze,kolumny);
        }
    }
    
    for(int i=0; i<ROZMIAR;++i){
        wynik[i]=(*this).wek_wyn[i];
    }
    return wynik;
}

Wektor UkladRownanLiniowych::wyz_blad(Wektor &odp){
    Wektor blad;
    blad=(*this).mac*odp;
    blad=blad-(*this).wek_wyn;
    return blad;   
}

void UkladRownanLiniowych::wyswietl(){
    Wektor wynik, blad;
    double dlugosc_bledu;

    (*this).mac=(*this).mac.transponowanie();
    UkladRownanLiniowych pom=(*this);

    std::cout << std::endl << "Układ równań liniowych:"<<std::endl;
    std::cout << (*this) << std::endl<<std::endl;
    wynik=(*this).Oblicz();
    std::cout << "Rozwiąznaia układu równań [x, y, z]: "<<std::endl;
    std::cout << wynik << std::endl<<std::endl;
    blad=pom.wyz_blad(wynik);
    dlugosc_bledu=blad.dl_wek();
    std::cout << "Wektor błędu wynosi: "<<std::endl;
    std::cout << blad << std::endl<<std::endl;
    std::cout << "Długość wektora błędu wynosi: "<<std::endl;
    std::cout << dlugosc_bledu << std::endl<<std::endl;
}


    
void UkladRownanLiniowych::Wyswietl_zamiana_wierszy(int wiersz, int zmiana){
    std::cout << "Zamieniono wiersze " << wiersz+1 << " z wierszem " << zmiana+1 << std::endl << std::endl;
    std::cout << (*this) << std::endl << std::endl;
}

void UkladRownanLiniowych::Wyswietl_zerowanie(int zmiana, double liczba, int wiersz){
    std::cout << "Od wiersza " << zmiana+1 << " odjęto wiersz " << wiersz+1 << " pomnożony przez " << liczba << std::endl << std::endl;
    std::cout << (*this) << std::endl << std::endl;
}
void UkladRownanLiniowych::Wyswietl_dzielenie(int wiersz, double liczba){
    std::cout << "Podzielono wiersz: " << wiersz+1 << " przez liczbę: " << liczba << std::endl << std::endl;
    std::cout << (*this) << std::endl << std::endl;
}