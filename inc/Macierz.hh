#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "rozmiar.h"
#include "Wektor.hh"
#include <iostream>
#include <cstdlib>

class Macierz {
private:
  Wektor wartosc[ROZMIAR];               

public:
  Macierz(Wektor [ROZMIAR]);           
  Macierz();                               
  
  Wektor operator * (Wektor tmp);           
  Macierz operator + (Macierz tmp);
  Macierz operator - (Wektor tmp);
  double  &operator () (unsigned int row, unsigned int column);
  const double &operator () (unsigned int row, unsigned int column) const;
  Macierz transponowanie();
  double wyznacznik()const;
  double wyznacznik_x(Wektor &v)const;
  double wyznacznik_y(Wektor &v)const;
  double wyznacznik_z(Wektor &v)const;
  Wektor oblicz(Wektor &v, double wyznacznik_u);
  Wektor wyz_blad(Wektor& x, Wektor& wyn);
};

std::istream &operator>>(std::istream &in, Macierz &mat);
std::ostream &operator<<(std::ostream &out, Macierz const &mat);



#endif
