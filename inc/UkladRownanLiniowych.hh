#ifndef UKLADROWNANLINIOWYCH_HH
#define UKLADROWNANLINIOWYCH_HH

#include <iostream>
#include "Wektor.hh"
#include "Macierz.hh"
#include "rozmiar.h"  



class UkladRownanLiniowych {
  public:

  Macierz mac;
  Wektor wek_wyn;
  
  

  UkladRownanLiniowych(Macierz mat, Wektor vec);
  UkladRownanLiniowych();
  UkladRownanLiniowych podstaw(Macierz tmp, Wektor tymczas);
  Wektor wyz_blad(Wektor &odp);
  bool czy_zero(int wiersz, int kolumna)const;
  Macierz zamien_wiersz(int wiersz, int kolumna);
  double Gauss();
  Wektor oblicz()const;
};

std::istream& operator >> (std::istream &Strm, UkladRownanLiniowych &UklRown);
std::ostream& operator << ( std::ostream& Strm, const UkladRownanLiniowych& UklRown);


#endif
