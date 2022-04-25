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
