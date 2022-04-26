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

UkladRownanLiniowych UkladRownanLiniowych::podstaw(Macierz tmp, Wektor tymczas){
    (*this).mac=tmp;
    (*this).wek_wyn=tymczas;
    return (*this);

}

std::istream &operator>>(std::istream &Strm, UkladRownanLiniowych &UklRown){
    Strm >> UklRown.mac >> UklRown.wek_wyn;
    return Strm;
}

std::ostream &operator<<(std::ostream &Strm,const UkladRownanLiniowych &UklRown){

    for (int i=0;i<ROZMIAR;++i){
        Strm << "| ";
        for (int j=0;j<ROZMIAR;++j){
            Strm << std::left << std::setw(5) << UklRown.mac(i, j);
        }
        Strm << "| |x_" << i+1 << "| ";
        if(i==1)
            Strm << " = ";
	    else
            Strm << "   ";
	Strm << " [ " <<UklRown.wek_wyn[i] << " ] ";
        std::cout << std::endl;
    }
    return Strm;
}

    Wektor UkladRownanLiniowych::wyz_blad(Wektor &odp){
        Wektor blad;
        blad=(*this).mac*odp;
        blad=blad-(*this).wek_wyn;
        return blad;   
    }

    bool UkladRownanLiniowych::czy_zero(int wiersz, int kolumna)const{
    int w;
    for(w = wiersz;w<ROZMIAR;++w){
        if((*this).mac(w,kolumna)!=0){
            return true;
        }
    }
            return false;
}

Macierz UkladRownanLiniowych::zamien_wiersz(int wiersz, int kolumna){
    Macierz tmp=(*this).mac;
    double komorka=1;
    int licznik_zamian =1;
    int wiersz_zamien;

    wiersz_zamien = wiersz + 1;
    while((licznik_zamian<ROZMIAR-wiersz)&&(komorka!=0)){
        komorka=tmp(wiersz,kolumna);
        std::cout << "Zamiana miejscami wierszy:" << std::endl;
        std::cout << tmp.wartosc[wiersz] << std::endl;
        std::cout << tmp.wartosc[wiersz_zamien] << std::endl <<std::endl;
        std::swap(tmp.wartosc[wiersz],tmp.wartosc[wiersz_zamien]);
        tmp.wartosc[wiersz_zamien]=tmp.wartosc[wiersz_zamien]*(-1);
        licznik_zamian++;
        wiersz_zamien++;
    }
    return tmp;
}

double UkladRownanLiniowych::Gauss(){
    UkladRownanLiniowych uklad = (*this);
    double dzielniki;
    double wyznacznik=1;
    Macierz pomocnicza=(*this).mac;
    Wektor zerowanie=(*this).wek_wyn;
    int wiersz=0, kolumna=0, liczba_zerowan =1;
    int w, k;

    std::cout << "Aktualny wygląd macierzy" << std::endl;
    std::cout << pomocnicza << std::endl << std::endl;

    while(liczba_zerowan<ROZMIAR){
        if(pomocnicza(wiersz,kolumna)!=0){
        w=wiersz;
        k=kolumna;
        dzielniki = pomocnicza(wiersz,kolumna);
        std::cout << "Liczba, przez którą dzielimy wiersz" << std::endl;
        std::cout << dzielniki << std::endl << std::endl;
        zerowanie=pomocnicza.wartosc[wiersz]/dzielniki;
        std::cout << "Wiersz, którym zerujemy miejsca" << std::endl;
        std::cout << zerowanie << std::endl << std::endl;
        for(int i=1; i<ROZMIAR-wiersz;i++){
            pomocnicza.wartosc[w+1] = pomocnicza.wartosc[w+1]- (zerowanie*pomocnicza(w+1,k));
            w++;
        }
        std::cout << "Aktualny wygląd macierzy" << std::endl;
        std::cout << pomocnicza << std::endl << std::endl;
        wiersz++;
        kolumna++;
        liczba_zerowan++;
        }else{
            if(pomocnicza.czy_zero(wiersz,kolumna)){
                pomocnicza = pomocnicza.zamien_wiersz(wiersz,kolumna);
            }else{
            std::cout << "Układ równań nie ma rozwiązań. Wyznacznik macierzy równy '0'." << std::endl;
            return 0;
            }
        }
    }

    for(int k=0;k<ROZMIAR;k++){
    wyznacznik=wyznacznik*pomocnicza(k,k);
    }  
    std::cout << "Wyznacznik tej macierzy wynosi: " << wyznacznik << std::endl<<std::endl;
    return wyznacznik;
}

Wektor UkladRownanLiniowych::oblicz()const{
    UkladRownanLiniowych uklad=(*this);
    Macierz macierz_pom = (*this).mac;
    Wektor wektor_pom = (*this).wek_wyn;
    Wektor wyznaczniki ,wyniki;
    double wyznacznik_mac;

    wyznacznik_mac=uklad.Gauss();
    for(int i=0;i<ROZMIAR;++i){
        for(int j=0;j<ROZMIAR;j++){
        std::swap(macierz_pom(j,i), wektor_pom[j]);
        }
        uklad=uklad.podstaw(macierz_pom,wektor_pom);

        switch (i)
        {
        case 0:
            std::cout<<"Wyliczanie wyznacznika 'x':"<<std::endl<<std::endl;
            break;
        
        case 1:
            std::cout<<"Wyliczanie wyznacznika 'y':"<<std::endl<<std::endl;
            break;

        case 2:
            std::cout<<"Wyliczanie wyznacznika 'z':"<<std::endl<<std::endl;
            break;

        default:
            break;
        }

        wyznaczniki[i]=uklad.Gauss();
        for(int j=0;j<ROZMIAR;j++){
        std::swap(wektor_pom[j],macierz_pom(j,i));
        }
        uklad=uklad.podstaw(macierz_pom,wektor_pom);
    }
    for(int i=0;i<ROZMIAR;++i){
        wyniki[i]=wyznaczniki[i]/wyznacznik_mac;
    }

    return wyniki;
}
