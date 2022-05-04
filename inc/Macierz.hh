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

  void setMac(int i, int j, double liczby){
    wartosc[i][j]=liczby;
  }

  double getMac(int i, int j){
    return wartosc[i][j];
  }

  Macierz(Wektor [ROZMIAR]);           
  Macierz();                               
  
  Wektor operator * (Wektor tmp);           
  Macierz operator + (Macierz tmp);
  Macierz operator - (Wektor tmp);
  double  &operator () (unsigned int row, unsigned int column);
  const double &operator () (unsigned int row, unsigned int column) const;
  Macierz transponowanie();
};

std::istream &operator>>(std::istream &in, Macierz &mat);
std::ostream &operator<<(std::ostream &out, Macierz const &mat);



#endif
