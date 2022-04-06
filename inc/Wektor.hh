#ifndef WEKTOR_HH
#define WEKTOR_HH

#include "rozmiar.h"
#include <iostream>


class Wektor {
private:

    double rozmiar[ROZMIAR];     

public:

    Wektor();
    Wektor(double [ROZMIAR]);
    Wektor operator + (const Wektor &v);
    Wektor operator - (const Wektor &v);
    Wektor operator * (const double &tmp);
    double operator * (const Wektor &Wek);
    Wektor operator / (const double &tmp);
    const double &operator [] (int index) const;
    double &operator [] (int index);
    double dl_wek();

};

std::ostream &operator << (std::ostream &out, Wektor const &tmp);
std::istream &operator >> (std::istream &in, Wektor &tmp);


#endif
