#
#  To sa opcje dla kompilacji
#
CXXFLAGS= -c -g -Iinc -Wall -pedantic

__start__: uklad_rownan
	./uklad_rownan < macierz.txt

uklad_rownan: obj/main.o obj/UkladRownanLiniowych.o obj/Macierz.o obj/Wektor.o
	g++ -Wall -pedantic -o uklad_rownan obj/main.o obj/Wektor.o\
                                   obj/Macierz.o obj/UkladRownanLiniowych.o

obj/main.o: src/main.cpp inc/UkladRownanLiniowych.hh inc/Macierz.hh inc/Wektor.hh\
        inc/rozmiar.h
	g++ ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/UkladRownanLiniowych.o: src/UkladRownanLiniowych.cpp inc/UkladRownanLiniowych.hh
	g++ ${CXXFLAGS} -o obj/UkladRownanLiniowych.o src/UkladRownanLiniowych.cpp

obj/Macierz.o: src/Macierz.cpp inc/Macierz.hh 
	g++ ${CXXFLAGS} -o obj/Macierz.o src/Macierz.cpp

obj/Wektor.o: src/Wektor.cpp inc/Wektor.hh inc/rozmiar.h
	g++ ${CXXFLAGS} -o obj/Wektor.o src/Wektor.cpp

clean:
	rm -f obj/*.o uklad_rownan
