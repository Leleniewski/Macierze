#include <iostream>
#include "Wektor.hh"
#include "Macierz.hh"
#include "UkladRownanLiniowych.hh"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>



int main() {
  Macierz wspolczynniki, trans;
  Wektor wyr_wol;
  Wektor wek_wyrz_wol, wek_wynik, wek_bledu;
  Macierz mat_wczyt, transponowana;
  double wyznacznik_u=1; 
  std::cin >> mat_wczyt;
  std::cin >> wek_wyrz_wol;
  trans = mat_wczyt.transponowanie();
  trans.Gauss(); 
  std::cout << "Macierz trans: " << std::endl << trans << std::endl;
  std::cout << "Wektor: " << std::endl << wek_wyrz_wol << std::endl << std::endl;
  if(wyznacznik_u!=0){
    wek_wynik=trans.oblicz(wek_wyrz_wol, wyznacznik_u);
  }else{
    std::cout << "Nie da się obliczyć rozwiązań." << std::endl;
  }
  wek_bledu=transponowana.wyz_blad(wek_wynik, wek_wyrz_wol);
  std::cout << "Wektor błędu:" << std::endl << wek_bledu << std::endl << std::endl;
  std::cout << "Długość wektora błędu:" << std::endl << wek_bledu.dl_wek() << std::endl << std::endl;
}
