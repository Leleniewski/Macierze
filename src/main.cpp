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
  Wektor wek_wyrz_wol, wek_wynik, wek_bledu;
  Macierz mat_wczyt, transponowana;

  std::cin >> mat_wczyt;
  std::cin >> wek_wyrz_wol;

  UkladRownanLiniowych rownanie(mat_wczyt, wek_wyrz_wol);

  transponowana = mat_wczyt.transponowanie();


  UkladRownanLiniowych transp(transponowana, wek_wyrz_wol);
  std::cout << "Układ równań:" << std::endl << transp << std::endl << std::endl;
  wek_wynik = transp.oblicz();

  std::cout << "Wektor wyników" << std::endl << wek_wynik << std::endl << std::endl;

  wek_bledu=transp.wyz_blad(wek_wynik);
  
  std::cout << "Wektor błędu:" << std::endl << wek_bledu << std::endl << std::endl;
  std::cout << "Długość wektora błędu:" << std::endl << wek_bledu.dl_wek() << std::endl << std::endl;
}
