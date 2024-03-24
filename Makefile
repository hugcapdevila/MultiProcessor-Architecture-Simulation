OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11


program.exe: program.o Cluster.o Procesador.o Proceso.o Area.o
	g++ -o program.exe program.o Cluster.o Procesador.o Proceso.o Area.o

program.o: program.cc Cluster.hh Procesador.hh Proceso.hh Area.hh
	g++ -c program.cc $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh Procesador.hh BinTree.hh
	g++ -c Cluster.cc $(OPCIONS)

Procesador.o: Procesador.cc Procesador.hh Proceso.hh 
	g++ -c Procesador.cc $(OPCIONS)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

Area.o: Area.cc Area.hh Proceso.hh Cluster.hh
	g++ -c Area.cc $(OPCIONS)

tar: Proceso.hh Proceso.cc Procesador.hh Procesador.cc Cluster.hh Cluster.cc Area.hh Area.cc program.cc BinTree.hh Makefile
	tar -cvf practica.tar Proceso.hh Proceso.cc Procesador.hh Procesador.cc Cluster.hh Cluster.cc Area.hh Area.cc program.cc BinTree.hh Makefile html.zip

clean:
	rm -f *.o
	rm -f *.exe
