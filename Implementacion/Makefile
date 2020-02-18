# Makefile

CC = g++
FLGS = -c 

OBJ1 = servidor.o
OBJ2 = clientePJ.o

OBJ = lista.o conexionServidor.o conexionCliente.o edificio.o objeto.o \
	personaje.o casilla.o elemento.o envio.o textura.o funciones.o \
	entornoG.o glf.o

EXE1 = servidor
EXE2 = clientePJ

INCL = -I/usr/X11R6/include -I/usr/include/SDL 
DLIB = -L/usr/X11R6/lib 
LIB =  -lGL -lGLU -lSDL -lSDL_image


$(EXE1) $(EXE2): $(OBJ) $(OBJ1) $(OBJ2)
	$(CC) -o $(EXE1) $(OBJ) $(OBJ1) $(INCL) $(DLIB) $(LIB) 
	$(CC) -o $(EXE2) $(OBJ) $(OBJ2) $(INCL) $(DLIB) $(LIB) 

servidor.o: servidor.cc
	$(CC) $(FLGS) servidor.cc $(INCL)

clientePJ.o: clientePJ.cc
	$(CC) $(FLGS) clientePJ.cc $(INCL)

lista.o: lista.cc
	$(CC) $(FLGS) lista.cc $(INCL)

conexionServidor.o: conexionServidor.cc
	$(CC) $(FLGS) conexionServidor.cc $(INCL)

conexionCliente.o: conexionCliente.cc
	$(CC) $(FLGS) conexionCliente.cc $(INCL)

edificio.o: edificio.cc
	$(CC) $(FLGS) edificio.cc $(INCL)

objeto.o: objeto.cc
	$(CC) $(FLGS) objeto.cc $(INCL)

personaje.o: personaje.cc
	$(CC) $(FLGS) personaje.cc $(INCL)

casilla.o: casilla.cc
	$(CC) $(FLGS) casilla.cc $(INCL)

elemento.o: elemento.cc
	$(CC) $(FLGS) elemento.cc $(INCL)

envio.o: envio.cc
	$(CC) $(FLGS) envio.cc $(INCL)

textura.o: textura.cc
	$(CC) $(FLGS) textura.cc $(INCL)

funciones.o: funciones.cc
	$(CC) $(FLGS) funciones.cc $(INCL)

entornoG.o: entornoG.cc
	$(CC) $(FLGS) entornoG.cc $(INCL)

glf.o: glf.cc
	$(CC) $(FLGS) glf.cc $(INCL)	
clean:	
	@rm -f *.o
	@rm -f *~
