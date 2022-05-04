#ifndef UKLADROWNANLINIOWYCH_HH
#define UKLADROWNANLINIOWYCH_HH

#include <iostream>
#include "Wektor.hh"
#include "Macierz.hh"
#include "rozmiar.h"  



class UkladRownanLiniowych {
  private:

  Macierz mac;
  Wektor wek_wyn;
  
  public:

  void setUkl_macierz(int i, int j, double liczby){
    mac.setMac(i, j, liczby);
  }

  void setUkl_wektor(int i, double wypelnienie){
    wek_wyn.setWek(i,wypelnienie);
  }

  double getUkl_macierz(int i, int j){
    return mac.getMac(i, j);
  }

  double getUkl_wektor(int miejsce_wek){
    return wek_wyn.getWek(miejsce_wek);
  }

  

  UkladRownanLiniowych(Macierz mat, Wektor vec);
  UkladRownanLiniowych();
  bool zeruj_kol(int wiersz, int kolumna);
  UkladRownanLiniowych zamiana_wierszy(int wiersz, int kolumna)const;
  Wektor wyz_blad(Wektor &odp);
  UkladRownanLiniowych Gauss(int wiersz, int kolumna);
  UkladRownanLiniowych dzielenie_wierszy(int wiersz, int kolumna);
  UkladRownanLiniowych dzialania(int wiersz, int kolumna);
  void czy_zero(int wiersz, int kolumna);
  Wektor Oblicz();
  void wyswietl();
  void Wyswietl_zamiana_wierszy(int wiersz, int zmiana);
  void Wyswietl_zerowanie(int zmiana, double liczba, int wiersz);
  void Wyswietl_dzielenie(int wiersz, double liczba);
};

std::istream& operator >> (std::istream &Strm, UkladRownanLiniowych &UklRown);
std::ostream& operator << ( std::ostream& Strm, UkladRownanLiniowych &UklRown);


#endif