
/***************************************************************************
                          funciones.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funciones.hh"
#include "lista.cc"
#include "edificio.hh"
#include "objeto.hh"
#include "personaje.hh"
#include "casilla.hh"
#include "elemento.hh"
#include "envio.hh"

#define INF -100000
#define SUP  100000

/***************************************************************************/

// Funci�n que devuelve el socket activo
int obtieneClienteActivo (Lista<Personaje*> *listaClientes, int turno)
{
    Personaje *unPersonaje;
    int tamanoClientes, posActiva, sockActivo;
 
    // Obtenci�n del tama�o de la lista de clientes conectados
    tamanoClientes = listaClientes->obtieneTamano ();

    // Si la lista no est� vac�a
    if (tamanoClientes > 0)
    {	
	// Obtenci�n de la posici�n del cliente activo en la lista 
	posActiva = turno % tamanoClientes;

	// Obtenci�n del cliente
	unPersonaje = listaClientes->obtieneElemento (posActiva);
	    	    
	// Obtenci�n del socket activo
	sockActivo = unPersonaje->obtieneAtributo ("sock");
	
	return sockActivo;
    }

    return -1;
}

/***************************************************************************/

// Funci�n que inserta en la lista un nuevo elemento con el socket especificado
void insertaEnvio (Lista<Envio*> *listaEnvios, int sock)
{
    Envio *unEnvio;

    // Creaci�n de un elemento envio nuevo
    unEnvio = new Envio ();
   
    // Asignaci�n del socket del envio
    unEnvio->reAsignaSock (sock);
    
    // Inserci�n en la lista de envios
    listaEnvios->insertaElemento (unEnvio);    
}

/***************************************************************************/

// Funci�n que elimina de la lista el elemento cuyo socket se especifica
void eliminaEnvio (Lista<Envio*> *listaEnvios, int sock)
{
    Envio *unEnvio;
    int tamano, sock1, encontrado = 0;

    // Obtenci�n del tama�o de la lista de env�os
    tamano = listaEnvios->obtieneTamano ();

    // B�squeda por la lista de env�os
    for (int i = 0; (i < tamano) && (encontrado == 0); i++)
    {
	// Obtenci�n del elemento
	unEnvio = listaEnvios->obtieneElemento (i);

	// Obtenci�n del socket
	sock1 = unEnvio->obtieneSock ();

	// Comprobaci�n de sockets
	if (sock == sock1)
	{
	    // Eliminaci�n del elemento
	    listaEnvios->eliminaElemento (i);
	    
	    // Actualizaci�n del flag de parada
	    encontrado = 1;
	}	
    }
}

/***************************************************************************/

/* Funci�n que devuelve el flag de env�o del elemento cuyo socket se especifica
   En caso de que el socket no exista devuelve -1 */
int obtieneEnvio (Lista<Envio*> *listaEnvios, int sock)
{
    Envio *unEnvio;
    int tamano, sock1, encontrado = 0, env = -1;

    // Obtenci�n del tama�o de la lista de env�os
    tamano = listaEnvios->obtieneTamano ();

    // B�squeda por la lista de env�os
    for (int i = 0; (i < tamano) && (encontrado == 0); i++)
    {
	// Obtenci�n del elemento
	unEnvio = listaEnvios->obtieneElemento (i);

	// Obtenci�n del socket
	sock1 = unEnvio->obtieneSock ();

	// Comprobaci�n de sockets
	if (sock == sock1)
	{
	    // Obtenci�n del flag de env�o
	    env = unEnvio->obtieneEnv ();

	    // Actualizaci�n del flag de parada
	    encontrado = 1;
	}
    }

    return env;
}

/***************************************************************************/

// Funci�n que modifica el flag de env�o del socket especificado
void reAsignaEnvio (Lista<Envio*> *listaEnvios, int sock, int nuevoEnv)
{
    Envio *unEnvio;
    int tamano, sock1, encontrado = 0;

    // Obtenci�n del tama�o de la lista de env�os
    tamano = listaEnvios->obtieneTamano ();

    // B�squeda por la lista de env�os
    for (int i = 0; (i < tamano) && (encontrado == 0); i++)
    {
	// Obtenci�n del elemento
	unEnvio = listaEnvios->obtieneElemento (i);

	// Obtenci�n del socket
	sock1 = unEnvio->obtieneSock ();

	// Comprobaci�n de sockets
	if (sock == sock1)
	{
	    // Modificaci�n del flag de env�o
	    unEnvio->reAsignaEnv (nuevoEnv);

	    // Actualizaci�n del env�o en la lista
	    listaEnvios->reAsignaElemento (i, unEnvio);

	    // Actualizaci�n del flag de parada
	    encontrado = 1;
	}
    }
}

/***************************************************************************/

/* Funci�n que pone el flag de env�o de todos los elementos de la lista con
   el valor especificado */
void activaEnvios (Lista<Envio*> *listaEnvios, int nuevoEnv)
{
    Envio *unEnvio;
    int tamano;

    // Obtenci�n del tama�o de la lista de env�os
    tamano = listaEnvios->obtieneTamano ();

    // Recorrido por la lista de env�os
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del elemento
	unEnvio = listaEnvios->obtieneElemento (i);
	
	// Modificaci�n del flag de env�o
	unEnvio->reAsignaEnv (nuevoEnv);

	// Actualizaci�n del env�o en la lista
	listaEnvios->reAsignaElemento (i, unEnvio);
    }	
}

/***************************************************************************/

// Funci�n que env�a un entero al cliente cuyo socket se especifica
void enviaEnteroACliente (ConexionServidor *conexion, int sock, int entero)
{
    char *cadena;
    char tamano;
    size_t nbytes;
    int tamanoCadena;

    // Conversi�n del entero a cadena
    cadena = itoa (entero);

    // Obtenci�n del tama�o de la cadena
    tamanoCadena = strlen (cadena);

    // Conversi�n del tama�o de la cadena a caracter
    tamano = int2char (tamanoCadena);

    // Env�o del tama�o de la cadena al cliente
    nbytes = 1 * sizeof (char);
    conexion->enviaDatos (&tamano, nbytes, sock);

    // Env�o de la cadena al cliente caracter por caracter
    for (int i = 0; i < tamanoCadena; i++)
	conexion->enviaDatos (&cadena[i], nbytes, sock);

    // Liberaci�n de la cadena
    delete [] cadena;
}

/***************************************************************************/

// Funci�n que recibe un entero del cliente cuyo socket se especifica
int recibeEnteroDeCliente (ConexionServidor *conexion, int sock)
{
    char *cadena;
    char tamano, caracter;
    size_t nbytes;
    int tamanoCadena, entero;

    // Recepci�n del tama�o de la cadena del cliente
    nbytes = 1 * sizeof (char);
    conexion->recibeDatos (&tamano, nbytes, sock);
    
    // Conversi�n del tama�o de la cadena a entero
    tamanoCadena = char2int (tamano);

    // Reserva de memoria para la cadena
    cadena = new char [tamanoCadena + 1];

    // Recepci�n de la cadena del cliente caracter a caracter
    for (int i = 0; i < tamanoCadena; i++)
    {
	conexion->recibeDatos (&caracter, nbytes, sock);
	cadena[i] = caracter;
    }

    // Inserci�n del '\0'
    cadena[tamanoCadena] = '\0';

    // Conversi�n a entero de la cadena
    entero = atoi (cadena);

    // Liberaci�n de la cadena
    delete [] cadena;

    return entero;
}

/***************************************************************************/

// Funci�n que env�a un entero al servidor
void enviaEnteroAServidor (ConexionCliente *conexion, int entero)
{
    char *cadena;
    char tamano;
    size_t nbytes;
    int tamanoCadena;

    // Conversi�n del entero a cadena
    cadena = itoa (entero);

    // Obtenci�n del tama�o de la cadena
    tamanoCadena = strlen (cadena);

    // Conversi�n del tama�o de la cadena a caracter
    tamano = int2char (tamanoCadena);

    // Env�o del tama�o de la cadena al servidor
    nbytes = 1 * sizeof (char);
    conexion->enviaDatos (&tamano, nbytes);

    // Env�o de la cadena al servidor caracter por caracter
    for (int i = 0; i < tamanoCadena; i++)
	conexion->enviaDatos (&cadena[i], nbytes);

    // Liberaci�n de la cadena
    delete [] cadena;
}

/***************************************************************************/

// Funci�n que recibe un entero del servidor
int recibeEnteroDeServidor (ConexionCliente *conexion)
{
    char *cadena;
    char tamano, caracter;
    size_t nbytes;
    int tamanoCadena, entero;
    
    // Recepci�n del tama�o de la cadena del servidor
    nbytes = 1 * sizeof (char);
    conexion->recibeDatos (&tamano, nbytes);
    
    // Conversi�n del tama�o de la cadena a entero
    tamanoCadena = char2int (tamano);

    // Reserva de memoria para la cadena
    cadena = new char [tamanoCadena + 1];

    // Recepci�n de la cadena del servidor caracter a caracter
    for (int i = 0; i < tamanoCadena; i++)
    {
	conexion->recibeDatos (&caracter, nbytes);
	cadena[i] = caracter;
    }

    // Inserci�n del '\0'
    cadena[tamanoCadena] = '\0';

    // Conversi�n a entero de la cadena
    entero = atoi (cadena);

    // Liberaci�n de la cadena
    delete [] cadena;

    return entero;
}

/***************************************************************************/

// Funci�n que devuelve en las coordenadas indicadas el tama�o del mundo
void obtieneTamMundo (int *mundoInf, int *mundoSup, int *castilInf, 
		      int *castilSup, int *casaInf, int *casaSup)
{
    FILE *ficheroCasillas;

    // Apertura del fichero de casillas
    ficheroCasillas = fopen ("./mundo/casillas.dat", "r");
    if (ficheroCasillas == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaCasillas ");
	fprintf (stderr, "(int *, int *, int *, int *, int *, int *): ");
	fprintf (stderr, "No se puede abrir el fichero de casillas\n");
	exit (-1);
    }

    // Lectura de los par�metros del mundo
    fscanf (ficheroCasillas, "%d %d %d %d %d %d\n", mundoInf, mundoSup, 
	    castilInf, castilSup, casaInf, casaSup);

    // Cierre del fichero
    fclose (ficheroCasillas);
}

/***************************************************************************/

/* Funci�n que devuelve una lista con todos los edificios del mundo que est�n 
   dentro del rango especificado */
Lista<Edificio*> *cargaEdificios (int xinf, int xsup, int yinf, int ysup)
{
    Lista<Edificio*> *listaEdificios;
    Edificio *unEdificio;
    FILE *ficheroEdificios;
    int id, tipo, llav, posx, posy, longx, longy, casilx, casily; 
    int dentro;

    // Creaci�n de la lista de edificios
    listaEdificios = new Lista<Edificio*> ();
    if (listaEdificios == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaEdificios ");
	fprintf (stderr, "(int, int, int, int): ");
	fprintf (stderr, "Memoria insuficiente para listaEdificios\n");
	exit (-1);
    }

    // Apertura del fichero de edificios
    ficheroEdificios = fopen ("./mundo/edificios.dat", "r");
    if (ficheroEdificios == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaEdificios ");
	fprintf (stderr, "(int, int, int, int): ");
	fprintf (stderr, "No se puede abrir el fichero edificios.dat\n");
	exit (-1);
    }

    // Lectura del fichero de edificios
    while (!feof (ficheroEdificios))
    {
	// Lectura de cada edificio
	fscanf (ficheroEdificios, "%d %d %d %d %d %d %d %d %d\n", &id, &tipo, 
		&llav, &posx, &posy, &longx, &longy, &casilx, &casily);
	
	// Comprobaci�n de las coordenadas
	dentro = 0;
	
	for (int i = posx; (i < posx + casilx) && (dentro != 1); i++)
	    for (int j = posy; (j < posy + casily) && (dentro != 1); j++)
		if ((i >= xinf) && (i < xsup))
		    if ((j >= yinf) && (j < ysup))
			dentro = 1;

	// Si el edificio est� dentro del rango 
	if (dentro == 1)
	{
	    // Creaci�n del edificio
	    unEdificio = new Edificio ();

	    // Asignaci�n de los atributos del edificio
	    unEdificio->reAsignaAtributo ("id", id);
	    unEdificio->reAsignaAtributo ("tipo", tipo);
	    unEdificio->reAsignaAtributo ("llav", llav);
	    unEdificio->reAsignaAtributo ("posx", posx);
	    unEdificio->reAsignaAtributo ("posy", posy);
	    unEdificio->reAsignaAtributo ("longx", longx);
	    unEdificio->reAsignaAtributo ("longy", longy);
	    unEdificio->reAsignaAtributo ("casilx", casilx);
	    unEdificio->reAsignaAtributo ("casily", casily);
	    
	    // Inserci�n del edificio en la lista
	    listaEdificios->insertaElemento (unEdificio);
	}	
    }

    // Cierre del fichero
    fclose (ficheroEdificios);

    return listaEdificios;
}

/***************************************************************************/

/* Funci�n que devuelve una lista con todos los objetos del mundo que est�n 
   dentro del rango y edificio especificados */
Lista<Objeto*> *cargaObjetos (int xinf, int xsup, int yinf, int ysup, int edif)
{
    Lista<Objeto*> *listaObjetos;
    Objeto *unObjeto;
    FILE *ficheroObjetos;
    int id, tipo, visi, posx, posy, longx, longy, casilx, casily;
    int edifObjeto, equ, dentro;

    // Creaci�n de la lista de objetos
    listaObjetos = new Lista<Objeto*> ();
    if (listaObjetos == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaObjetos ");
	fprintf (stderr, "(int, int, int, int, int): ");
	fprintf (stderr, "Memoria insuficiente para listaObjetos\n");
	exit (-1);
    }

    // Apertura del fichero de objetos
    ficheroObjetos = fopen ("./objetos.dat", "r");
    if (ficheroObjetos == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaObjetos ");
	fprintf (stderr, "(int, int, int, int, int): ");
	fprintf (stderr, "No se puede abrir el fichero objetos.dat\n");
	exit (-1);
    }

    // Lectura del fichero de objetos
    while (!feof (ficheroObjetos))
    {
	// Lectura de cada objeto
	fscanf (ficheroObjetos, "%d %d %d %d %d %d %d %d %d %d %d\n", 
		&id, &tipo, &visi, &posx, &posy, &longx, &longy, &casilx, 
		&casily, &edifObjeto, &equ);
	
	// Comprobaci�n de las coordenadas	    
	dentro = 0;

	if (edif == edifObjeto)
	    for (int i = posx; (i < posx + casilx) && (dentro != 1); i++)
		for (int j = posy; (j < posy + casily) && (dentro != 1); j++)
		    if ((i >= xinf) && (i < xsup))
			if ((j >= yinf) && (j < ysup))	      
			    dentro = 1;

	// Si el objeto est� dentro del rango
	if (dentro == 1)
	{
	    // Creaci�n del objeto
	    unObjeto = new Objeto ();

	    // Asignaci�n de los atributos del objeto
	    unObjeto->reAsignaAtributo ("id", id);
	    unObjeto->reAsignaAtributo ("tipo", tipo);
	    unObjeto->reAsignaAtributo ("visi", visi);
	    unObjeto->reAsignaAtributo ("posx", posx);
	    unObjeto->reAsignaAtributo ("posy", posy);
	    unObjeto->reAsignaAtributo ("longx", longx);
	    unObjeto->reAsignaAtributo ("longy", longy);
	    unObjeto->reAsignaAtributo ("casilx", casilx);
	    unObjeto->reAsignaAtributo ("casily", casily);
	    unObjeto->reAsignaAtributo ("edif", edifObjeto);
	    unObjeto->reAsignaAtributo ("equ", equ);
	    
	    // Inserci�n del objeto en la lista
	    listaObjetos->insertaElemento (unObjeto);
	}	
    }
    
    // Cierre del fichero
    fclose (ficheroObjetos);

    return listaObjetos;
}

/***************************************************************************/

/* Funci�n que devuelve una lista  a partir de la dada con todos los personajes
   del mundo que est�n dentro del rango y edificio especificados */
Lista<Personaje*> *cargaPersonajes (int xinf, int xsup, int yinf, int ysup, 
				    Lista<Personaje*> *listaClientes, int edif)
{
    Lista<Personaje*> *listaP;
    Personaje *unPersonaje;
    int tamano, posx, posy, edif1, dentro;

    // Creaci�n de la nueva lista de personajes
    listaP = new Lista<Personaje*> ();
    if (listaP == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaPersonajes ");
	fprintf (stderr, "(int, int, int, int, Lista<Personaje*>*, int): ");
	fprintf (stderr, "Memoria insuficiente para listaP\n");
	exit (-1);
    }

    // Obtenci�n del tama�o de la lista de clientes
    tamano = listaClientes->obtieneTamano ();

    // B�squeda por la lista de clientes
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del cliente
	unPersonaje = listaClientes->obtieneElemento (i);

	// Obtenci�n de las coordenadas del cliente
	posx = unPersonaje->obtieneAtributo ("posx");
	posy = unPersonaje->obtieneAtributo ("posy");

	// Obtenci�n del edificio del cliente
	edif1 = unPersonaje->obtieneAtributo ("edif");

	// Comprobaci�n de coordenadas
	dentro = 0;

	if (edif1 == edif)
	    if ((posx >= xinf) && (posx < xsup))
		if ((posy >= yinf) && (posy < ysup))
		    dentro = 1;
	
	// Si el cliente est� dentro del rango
	if (dentro == 1)	

	    // Inserci�n del cliente en la lista de personajes
	    listaP->insertaElemento (unPersonaje);
    }	
    
    return listaP;
}

/***************************************************************************/

/* Funci�n que devuelve una lista con todas las casillas del mundo que est�n 
   dentro del rango especificado */
Lista<Casilla*> *cargaCasillas (int xinf, int xsup, int yinf, int ysup)
{
    Lista<Casilla*> *listaCasillas;
    Casilla *unaCasilla;
    FILE *ficheroCasillas;
    int posx, posy, tipo, nada;

    // Creaci�n de la lista de casillas
    listaCasillas = new Lista<Casilla*> ();
    if (listaCasillas == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaCasillas ");
	fprintf (stderr, "(int, int, int, int): ");
	fprintf (stderr, "Memoria insuficiente para listaCasillas\n");
	exit (-1);
    }

    // Apertura del fichero de casillas
    ficheroCasillas = fopen ("./mundo/casillas.dat", "r");
    if (ficheroCasillas == NULL)
    {
	fprintf (stderr, "funciones.cc: cargaCasillas ");
	fprintf (stderr, "(int, int, int, int): ");
	fprintf (stderr, "No se puede abrir el fichero de casillas\n");
	exit (-1);
    }

    // Lectura anticipada del tama�o del mundo
    fscanf (ficheroCasillas, "%d %d %d %d %d %d\n", &nada, &nada, &nada, &nada,
	    &nada, &nada);

    // Lectura del fichero de casillas
    while (!feof (ficheroCasillas))
    {
	// Lectura de cada casilla
	fscanf (ficheroCasillas, "%d %d %d\n", &tipo, &posx, &posy);
	
	// Comprobaci�n de las coordenadas
	if ((posx >= xinf) && (posx < xsup))
	    if ((posy >= yinf) && (posy < ysup))		       
	    {
		// Creaci�n de la casilla
		unaCasilla = new Casilla ();

		// Asignaci�n de los atributos de la casilla
		unaCasilla->reAsignaAtributo ("tipo", tipo);
		unaCasilla->reAsignaAtributo ("posx", posx);
		unaCasilla->reAsignaAtributo ("posy", posy);

		// Inserci�n de la casilla en la lista
		listaCasillas->insertaElemento (unaCasilla);
	    }	
    }
    
    // Cierre del fichero
    fclose (ficheroCasillas);
    
    return listaCasillas;
}

/***************************************************************************/

/* Funci�n que devuelve una lista con los elementos de las dos listas 
   especificadas ordenados de mayor a menor profundidad */
Lista<Elemento*> *ordenaListas (Lista<Personaje*> *listaP, 
				Lista<Objeto*> *listaObjetos)
{
    Lista<Personaje*> *listaPAux;
    Lista<Objeto*> *listaObjetosAux;
    Lista<Elemento*> *listaElementos;
    Personaje *unPersonaje;
    Personaje *nuevoPersonaje;
    Objeto *unObjeto;
    Objeto *nuevoObjeto;
    Elemento *unElemento;
    int tamanoP, tamanoObjetos;
    int posy, posyMax, tipo, tipoElemento, indice;

    // Creaci�n de la lista auxiliar de personajes
    listaPAux = new Lista<Personaje*> ();
    if (listaPAux == NULL)
    {
	fprintf (stderr, "funciones.cc: ordenaListas ");
	fprintf (stderr, "(Lista<Personaje*> *, Lista<Objeto*> *): ");
	fprintf (stderr, "Memoria insuficiente para listaPAux\n");
	exit (-1);
    }

    // Obtenci�n del tama�o de la lista de personajes
    tamanoP = listaP->obtieneTamano ();

    // Copia de la lista de personajes a la lista auxiliar
    for (int i = 0; i < tamanoP; i++)
    {
	// Obtenci�n del personaje de la lista de personajes
	unPersonaje = listaP->obtieneElemento (i);

	// Obtenci�n de la coordenada y del personaje 
	posy = unPersonaje->obtieneAtributo ("posy");

	// Creaci�n de un nuevo personaje
	nuevoPersonaje = new Personaje ();

	// Asignaci�n de la coordenada y del nuevo personaje
	nuevoPersonaje->reAsignaAtributo ("posy", posy);

	// Inserci�n del nuevo personaje en la lista
	listaPAux->insertaElemento (nuevoPersonaje);
    }

    // Creaci�n de la lista auxiliar de objetos
    listaObjetosAux = new Lista<Objeto*> ();
    if (listaObjetosAux == NULL)
    {
	fprintf (stderr, "funciones.cc: ordenaListas ");
	fprintf (stderr, "(Lista<Personaje*> *, Lista<Objeto*> *): ");
	fprintf (stderr, "Memoria insuficiente para listaObjetosAux\n");
	exit (-1);
    }

    // Obtenci�n del tama�o de la lista de objetos
    tamanoObjetos = listaObjetos->obtieneTamano ();

    // Copia de la lista de objetos a la lista auxiliar
    for (int i = 0; i < tamanoObjetos; i++)
    {
	// Obtenci�n del objeto de la lista de objetos
	unObjeto = listaObjetos->obtieneElemento (i);

	// Obtenci�n de la coordenada y del objeto
	posy = unObjeto->obtieneAtributo ("posy");

	// Obtenci�n del tipo del objeto
	tipo = unObjeto->obtieneAtributo ("tipo");

	// Creaci�n de un nuevo objeto
	nuevoObjeto = new Objeto ();

	// Asignaci�n de los atributos del nuevo objeto
	nuevoObjeto->reAsignaAtributo ("posy", posy);
	nuevoObjeto->reAsignaAtributo ("tipo", tipo);

	// Inserci�n del nuevo objeto en la lista
	listaObjetosAux->insertaElemento (nuevoObjeto);
    }

    // Creaci�n de la lista de elementos
    listaElementos = new Lista<Elemento*> ();
    if (listaElementos == NULL)
    {
	fprintf (stderr, "funciones.cc: ordenaListas ");
	fprintf (stderr, "(Lista<Personaje*> *, Lista<Objeto*> *): ");
	fprintf (stderr, "Memoria insuficiente para listaElementos\n");
	exit (-1);
    }

    // Bucle de ordenaci�n en funci�n de la coordenada y
    do
    {
	// Valor inicial m�ximo para la coordenada y
	posyMax = INF;

	// B�squeda del m�ximo elemento en profundidad en listaPAux	
	for (int i = 0; i < tamanoP; i++)
	{
	    // Obtenci�n del personaje
	    unPersonaje = listaPAux->obtieneElemento (i);

	    // Obtenci�n de la coordenada y del personaje
	    posy = unPersonaje->obtieneAtributo ("posy");
	    
	    // Si la coordenada y es mayor que el m�ximo
	    if (posy > posyMax)
	    {
		// La coordenada y se convierte en el m�ximo
		posyMax = posy;
		
		// Se almacena el tipo de elemento como personaje
		tipoElemento = 0;

		// Se almacena el �ndice del elemento
		indice = i;
	    }
	}

	// B�squeda del m�ximo elemento en profundidad en listaObjetosAux
	for (int i = 0; i < tamanoObjetos; i++)
	{
	    // Obtenci�n del objeto
	    unObjeto = listaObjetosAux->obtieneElemento (i);

	    // Obtenci�n de la coordenada y del objeto
	    posy = unObjeto->obtieneAtributo ("posy");

	    // Si la coordenada y es mayor que el m�ximo
	    if (posy > posyMax)
	    {
		// La coordenada y se convierte en el m�ximo
		posyMax = posy;

		// Se almacena el tipo de elemento como objeto
		tipoElemento = 1;

		// Se almacena el �ndice del elemento
		indice = i;
	    }
	    
	    // Si la coordenada y es igual a un m�ximo ya encontrado
	    if ((posy == posyMax) && (posyMax != INF))
	    {
		// Obtenci�n del tipo de objeto
		tipo = unObjeto->obtieneAtributo ("tipo");

		// Si el tipo de objeto es "arbol" o "cama"
		if ((tipo == 0) ||(tipo == 22))
		{
		    // La coordenada y se convierte en el m�ximo
		    posyMax = posy;
		    
		    // Se almacena el tipo de elemento como objeto
		    tipoElemento = 1;

		    // Se almacena el �ndice del elemento
		    indice = i;
		}
	    }	    	    
	}

	// Si se ha encontrado un m�ximo
	if (posyMax != INF)
	{
	    // Creaci�n de un nuevo elemento
	    unElemento = new Elemento ();

	    // Asignaci�n de los atributos del nuevo elemento
	    unElemento->reAsignaAtributo ("tipo", tipoElemento);
	    unElemento->reAsignaAtributo ("posicion", indice);

	    // Inserci�n del elemento en la lista
	    listaElementos->insertaElemento (unElemento);

	    // Si el elemento creado es un personaje
	    if (tipoElemento == 0)
	    {
		// Obtenci�n del personaje
		unPersonaje = listaPAux->obtieneElemento (indice);

		// Marcado del personaje como visitado
		unPersonaje->reAsignaAtributo ("posy", INF);

		// Actualizaci�n del personaje en su lista
		listaPAux->reAsignaElemento (indice, unPersonaje);
	    }

	    // Si el elemento creado es un objeto
	    else
	    {
		// Obtenci�n del objeto
		unObjeto = listaObjetosAux->obtieneElemento (indice);

		// Marcado del objeto como visitado
		unObjeto->reAsignaAtributo ("posy", INF);

		// Actualizaci�n del objeto en su lista
		listaObjetosAux->reAsignaElemento (indice, unObjeto);
	    }
	}

    } while (posyMax != INF); 

    return listaElementos;
}

/***************************************************************************/

// Funci�n que ordena la lista de clientes por momento de reacci�n
Lista<Personaje*> *ordenaClientes (Lista<Personaje*> *listaClientes)
{
    Lista<Personaje*> *listaAux;
    Lista<Personaje*> *listaOrdenada;
    Personaje *unPersonaje;
    Personaje *nuevoPersonaje;
    int tamano, mmr, des, minMmr, maxDes, indice, contador = 0;

    // Creaci�n de la lista auxiliar de clientes
    listaAux = new Lista<Personaje*> ();
    if (listaAux == NULL)
    {
	fprintf (stderr, "funciones.cc: ordenaClientes ");
	fprintf (stderr, "(Lista<Personaje*> *): ");
	fprintf (stderr, "Memoria insuficiente para listaAux\n");
	exit (-1);
    }

    // Creaci�n de la lista ordenada de clientes
    listaOrdenada = new Lista<Personaje*> ();
    if (listaOrdenada == NULL)
    {
	fprintf (stderr, "funciones.cc: ordenaClientes ");
	fprintf (stderr, "(Lista<Personaje*> *): ");
	fprintf (stderr, "Memoria insuficiente para listaOrdenada\n");
	exit (-1);
    }

    // Obtenci�n del tama�o de la lista de clientes
    tamano = listaClientes->obtieneTamano ();       

    // Copia de la lista de clientes
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del personaje de la lista de personajes
	unPersonaje = listaClientes->obtieneElemento (i);

	// Obtenci�n del atributo mmr del personaje 
	mmr = unPersonaje->obtieneAtributo ("mmr");

	// Obtenci�n del atributo des del personaje
	des = unPersonaje->obtieneAtributo ("des");

	// Creaci�n de un nuevo personaje
	nuevoPersonaje = new Personaje ();

	// Asignaci�n de los atributos al nuevo personaje
	nuevoPersonaje->reAsignaAtributo ("mmr", mmr);
	nuevoPersonaje->reAsignaAtributo ("des", des);

	// Inserci�n del nuevo personaje en la lista
	listaAux->insertaElemento (nuevoPersonaje);
    }

    // Inicializaci�n del m�nimo
    minMmr = SUP;
    maxDes = INF;

    // Bucle principal
    while (contador < tamano)
    {
	// B�squeda por la lista de clientes
	for (int i = 0; i < tamano; i++)
	{
	    // Obtenci�n de un cliente
	    unPersonaje = listaAux->obtieneElemento (i);

	    // Obtenci�n del momento de reacci�n del cliente
	    mmr = unPersonaje->obtieneAtributo ("mmr");
	    
	    // Comprobaci�n de que el personaje no est� eliminado
	    if (mmr != -1)
	    {
		// Obtenci�n de la des del cliente
		des = unPersonaje->obtieneAtributo ("des");

		// Si el cliente tiene menor momento de reacci�n que el m�nimo
		if (mmr < minMmr)
		{
		    // Actualizaci�n como nuevo m�nimo
		    minMmr = mmr;
		    maxDes = des;
		    indice = i;
		}

		// Si el cliente tiene el mismo momento de reacci�n
		else if (mmr == minMmr)
		{
		    // Si tiene mayor des
		    if (des > maxDes)
		    {
			// Actualizaci�n como nuevo m�nimo
			minMmr = mmr;
			maxDes = des;
			indice = i;
		    }
		}
	    }
	}

	// Inserci�n del m�nimo en la lista ordenada
	unPersonaje = listaClientes->obtieneElemento (indice);
	listaOrdenada->insertaElemento (unPersonaje);

	// Eliminaci�n del cliente en la lista de clientes
	unPersonaje = listaAux->obtieneElemento (indice);
	unPersonaje->reAsignaAtributo ("mmr", -1);
	listaAux->reAsignaElemento (indice, unPersonaje);

	// Inicializaci�n del m�nimo
	minMmr = SUP;

	// Incremento del contador
	contador++;
    }

    return listaOrdenada;
}

/***************************************************************************/

// Funci�n que actualiza el fichero de objetos con la lista especificada
void actualizaObjetos (Lista<Objeto*> *listaObjetos)
{
    Objeto *unObjeto;
    FILE *ficheroObjetos;
    FILE *ficheroAuxiliar;
    int id, id1, tipo, visi, posx, posy, longx, longy, casilx, casily, edif;
    int equ, tamano, nAtributos, fin;

    // Obtenci�n del tama�o de la lista de objetos
    tamano = listaObjetos->obtieneTamano ();

    // Si la lista no est� vac�a
    if (tamano != 0)
    {	
	// Apertura del fichero de objetos
	ficheroObjetos = fopen ("./objetos.dat", "r");
	if (ficheroObjetos == NULL)
	{
	    fprintf (stderr, "funciones.cc: actualizaObjetos ");
	    fprintf (stderr, "(Lista<Objeto*> *): ");
	    fprintf (stderr, "No se puede abrir el fichero objetos.dat\n");
	    exit (-1);
	}

	// Creaci�n del fichero auxiliar
	ficheroAuxiliar = fopen ("./auxiliar.dat", "w");
	if (ficheroAuxiliar == NULL)
	{
	    fprintf (stderr, "funciones.cc: actualizaObjetos ");
	    fprintf (stderr, "(Lista<Objeto*> *): ");
	    fprintf (stderr, "No se puede crear el fichero auxiliar.dat\n");
	    exit (-1);
	}

	// Lectura del fichero de objetos
	while (!feof (ficheroObjetos))
	{
	    // Lectura de cada objeto
	    fscanf (ficheroObjetos, "%d %d %d %d %d %d %d %d %d %d %d\n",
		    &id, &tipo, &visi, &posx, &posy, &longx, &longy, &casilx, 
		    &casily, &edif, &equ);
	    
	    // B�squeda del objeto en la lista
	    fin = 0;
	    for (int i = 0; (i < tamano) && (fin != 1); i++)
	    {
		// Obtenci�n del objeto
		unObjeto = listaObjetos->obtieneElemento (i);

		// Obtenci�n del identificador del objeto
		id1 = unObjeto->obtieneAtributo ("id");

		// Comprobaci�n de identificadores
		if (id1 == id)
		{
		    // Obtenci�n del tipo del objeto
		    tipo = unObjeto->obtieneAtributo ("tipo");

		    // Si el objeto no se ha eliminado
		    if (tipo != -1)
		    {
			// Obtenci�n del n�mero de atributos
			nAtributos = unObjeto->obtieneNAtributos ();
		    	    
			// Escritura del objeto en el fichero auxiliar
			for (int j = 1; j <= nAtributos; j++)
			{
			    if (j == nAtributos)
				fprintf (ficheroAuxiliar, "%d\n", 
				     unObjeto->obtieneAtributo (j));
			    else
				fprintf (ficheroAuxiliar, "%d ", 
				     unObjeto->obtieneAtributo (j));
			}
		    }

		    // Borrado del objeto en la lista
		    listaObjetos->eliminaElemento (i);
		    tamano = listaObjetos->obtieneTamano ();

		    // Asignaci�n del flag de parada
		    fin = 1;
		}
	    }
	    
	    // Si el objeto no est� en la lista ni est� eliminado se deja 
	    if (fin == 0)	    
		fprintf (ficheroAuxiliar, "%d %d %d %d %d %d %d %d %d %d %d\n",
			 id, tipo, visi, posx, posy, longx, longy, casilx, 
			 casily, edif, equ);	    
	}

	// Cierre de ficheros
	fclose (ficheroObjetos);
	fclose (ficheroAuxiliar);

	// Renombramiento del fichero auxiliar en el nuevo fichero de objetos
	remove ("./objetos.dat");
	rename ("./auxiliar.dat", "./objetos.dat");    
    }
}	

/***************************************************************************/

// Funci�n que actualiza la lista de clientes con la lista de personajes dada
void actualizaPersonajes (Lista<Personaje*> *listaP, 
			  Lista<Personaje*> *listaClientes)
{
    Personaje *unCliente;
    Personaje *unPersonaje;
    int tamanoP, tamanoClientes, sock, sock1, fin;

    // Obtenci�n del tama�o de la lista de clientes
    tamanoClientes = listaClientes->obtieneTamano ();

    // B�squeda por la lista de clientes
    for (int i = 0; i < tamanoClientes; i++)
    {
	// Obtenci�n del cliente
	unCliente = listaClientes->obtieneElemento (i);

	// Obtenci�n del socket del cliente
	sock = unCliente->obtieneAtributo ("sock");

	// B�squeda en la lista de personajes
	fin = 0;
	tamanoP = listaP->obtieneTamano ();
	for (int j = 0; (j < tamanoP) && (fin != 1); j++)
	{
	    // Obtenci�n del personaje
	    unPersonaje = listaP->obtieneElemento (j);

	    // Obtenci�n del socket del personaje
	    sock1 = unPersonaje->obtieneAtributo ("sock");

	    // Comprobaci�n de sockets
	    if (sock1 == sock)
	    {
		// Actualizaci�n del cliente
		listaClientes->reAsignaElemento (i, unPersonaje);

		// Borrado del personaje en la lista
		listaP->eliminaElemento (j);

		// Asignaci�n del flag de parada
		fin = 1;
	    }
	}
    }
}
 
/***************************************************************************/

/* Funci�n que inserta los objetos de la lista especificada en el fichero de
   objetos */
void insertaNuevosObjetos (Lista<Objeto*> *listaObjetos, 
			   Lista<Personaje*> *listaP, int xinf, int xsup,
			   int yinf, int ysup)
{
    FILE *ficheroObjetos;
    Objeto *unObjeto;
    int tamano, posx, posy, casilx, casily, nAtributos, atributo, id, nada;
    
    // Apertura del fichero de objetos
    ficheroObjetos = fopen ("./objetos.dat", "r+");
    if (ficheroObjetos == NULL)
    {
	fprintf (stderr, "funciones.cc: insertaNuevosObjetos ");
	fprintf (stderr, "(Lista<Objeto*> *, Lista<Personaje*> *, ");
	fprintf (stderr, "int, int, int, int): ");
	fprintf (stderr, "No se puede abrir el fichero objetos.dat\n");
	exit (-1);
    }

    // Recorrido del fichero hasta el final
    while (!feof (ficheroObjetos))
    
	// Lectura de cada l�nea
        fscanf (ficheroObjetos, "%d %d %d %d %d %d %d %d %d %d %d\n",
		&id, &nada, &nada, &nada, &nada, &nada, &nada, &nada, &nada,
		&nada, &nada);
    

    // Obtenci�n del tama�o de la lista de objetos
    tamano = listaObjetos->obtieneTamano ();

    // Recorrido por la lista de objetos
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del objeto
	unObjeto = listaObjetos->obtieneElemento (i);
	
	// Obtenci�n del n�mero de casillas que ocupa el objeto
	casilx = unObjeto->obtieneAtributo ("casilx");
	casily = unObjeto->obtieneAtributo ("casily");

	// Generaci�n de una posici�n para el objeto
	obtienePosicion (xinf, xsup, yinf, ysup, &posx, &posy, listaP);

	// Incremento del identificador
	id++;

	// Reasignaci�n de los atributos del objeto
	unObjeto->reAsignaAtributo ("id", id);
	unObjeto->reAsignaAtributo ("posx", posx);
	unObjeto->reAsignaAtributo ("posy", posy);

	// Inserci�n en el fichero
	nAtributos = unObjeto->obtieneNAtributos ();
	for (int j = 1; j <= nAtributos; j++)
	{
	    atributo = unObjeto->obtieneAtributo (j);

	    if (j == nAtributos)
		fprintf (ficheroObjetos, "%d\n", atributo);
	    else
		fprintf (ficheroObjetos, "%d ", atributo);
	}
    }

    // Cierre del fichero
    fclose (ficheroObjetos);
}

/***************************************************************************/

/* Funci�n que asigna los objetos trampas a no visibles y los objetos 
   prisioneros a esclavos pertenecientes al edificio especificado */
void iniciaObjetos (Lista<Objeto*> *listaObjetos, int edif)
{
    Objeto *unObjeto;
    int tamano, edif1, tipo, visi;

    // Obtenci�n del tama�o de la lista de objetos
    tamano = listaObjetos->obtieneTamano ();

    // B�squeda por la lista de objetos
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del objeto
	unObjeto = listaObjetos->obtieneElemento (i);

	// Obtenci�n del edificio al que pertenece el objeto
	edif1 = unObjeto->obtieneAtributo ("edif");

	// Comprobaci�n de edificios
	if (edif1 == edif)
	{
	    // Obtenci�n del tipo del objeto
	    tipo = unObjeto->obtieneAtributo ("tipo");

	    // esclava1 libre -> esclava1
	    if (tipo == 10)
		unObjeto->reAsignaAtributo ("tipo", 9);
	    
	    // esclava2 libre -> esclava2
	    else if (tipo == 12)
		unObjeto->reAsignaAtributo ("tipo", 11);

	    // esclavo1 libre -> esclavo1
	    else if (tipo == 14)
		unObjeto->reAsignaAtributo ("tipo", 13);

	    // esclavo2 libre -> esclavo2
	    else if (tipo == 16)
		unObjeto->reAsignaAtributo ("tipo", 15);

	    // pinchos visibles -> pinchos ocultos
	    else if (tipo == 17)
	    {	    
		visi = unObjeto->obtieneAtributo ("visi");
				
		if (visi == 1)		
		    unObjeto->reAsignaAtributo ("visi", 0);		
	    }

	    // Actualizaci�n del objeto en la lista
	    listaObjetos->reAsignaElemento (i, unObjeto);	
	}
    }
}

/***************************************************************************/

/* Funci�n que crea una lista de objetos cofres que incluyan el equipo
   del personaje de la lista especificada */
Lista<Objeto*> *creaCofres (Lista<Personaje*> *listaP, int indiceP)
{
    Lista<Objeto*> *listaObjetos;
    Personaje *unPersonaje;
    Objeto *unObjeto;
    int posx, posy, edif, tamEqu, atributo, ncofres;

    // Creaci�n de la lista de objetos
    listaObjetos = new Lista<Objeto*> ();
    if (listaObjetos == NULL)
    {
	fprintf (stderr, "funciones.cc: creaCofres ");
	fprintf (stderr, "(Lista<Personaje*> *, int): ");
	fprintf (stderr, "Memoria insuficiente para listaObjetos\n");
	exit (-1);
    }

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n de las coordenadas y edificio donde se encuentra el personaje
    posx = unPersonaje->obtieneAtributo ("posx");
    posy = unPersonaje->obtieneAtributo ("posy");
    edif = unPersonaje->obtieneAtributo ("edif");

    // Generaci�n de los cofres a partir del equipo del personaje
    tamEqu = unPersonaje->obtieneTamEqu ();
    for (int i = 3; i < tamEqu; i++)
    {
	// Obtenci�n del elemento del equipo
	atributo = unPersonaje->obtieneEqu (i);

	// Si el elemento no es VACIO
	if (atributo > 0)
	{	    
	    // Si el elemento son monedas de oro
	    if (i == 3)
	    {
		// Se crean cofres por cada 50 monedas
		ncofres = atributo / 50;
		for (int j = 0; j < ncofres; j++)
		{
		    // Creaci�n del objeto
		    unObjeto = new Objeto ();

		    // Asignaci�n de atributos
		    unObjeto->reAsignaAtributo ("tipo", 3);
		    unObjeto->reAsignaAtributo ("equ", 11);

		    unObjeto->reAsignaAtributo ("longx", 1);
		    unObjeto->reAsignaAtributo ("longy", 1);
		    unObjeto->reAsignaAtributo ("casilx", 1);
		    unObjeto->reAsignaAtributo ("casily", 1);
		    unObjeto->reAsignaAtributo ("visi", 1);

		    // Inserci�n en la lista
		    listaObjetos->insertaElemento (unObjeto);
		}
	    }
	    
	    // Si el elemento es una llave
	    else if (i == 4)
	    {
		// Creaci�n del objeto
		unObjeto = new Objeto ();

		// Asignaci�n de atributos
		unObjeto->reAsignaAtributo ("tipo", 3);
		unObjeto->reAsignaAtributo ("equ", 0);

		unObjeto->reAsignaAtributo ("longx", 1);
		unObjeto->reAsignaAtributo ("longy", 1);
		unObjeto->reAsignaAtributo ("casilx", 1);
		unObjeto->reAsignaAtributo ("casily", 1);
		unObjeto->reAsignaAtributo ("visi", 1);

		// Inserci�n en la lista
		listaObjetos->insertaElemento (unObjeto);
	    }

	    // Si el elemento es una poci�n
	    else 
	    {
		// Creaci�n del objeto
		unObjeto = new Objeto ();
		
		// Asignaci�n de atributos
		unObjeto->reAsignaAtributo ("tipo", 3);
		unObjeto->reAsignaAtributo ("equ", atributo);

		unObjeto->reAsignaAtributo ("longx", 1);
		unObjeto->reAsignaAtributo ("longy", 1);
		unObjeto->reAsignaAtributo ("casilx", 1);
		unObjeto->reAsignaAtributo ("casily", 1);
		unObjeto->reAsignaAtributo ("visi", 1);

		// Inserci�n en la lista
		listaObjetos->insertaElemento (unObjeto);
	    }
	}
    }

    return listaObjetos;
}

/***************************************************************************/

/* Funci�n que devuelve el �ndice en la lista del personaje cuyo socket 
   coincide con el especificado 
   En caso de que no coincida se devuelve -1 */
int obtieneIndice (Lista<Personaje*> *listaP, int sock)
{
    Personaje *unPersonaje;
    int tamano;

    // Obtenci�n del tama�o de la lista de personajes
    tamano = listaP->obtieneTamano ();

    // B�squeda por la lista de personajes
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del personaje
	unPersonaje = listaP->obtieneElemento (i);

	// Comprobaci�n de sockets
	if (unPersonaje->obtieneAtributo ("sock") == sock)
	    return i;
    }

    return -1;
}

/***************************************************************************/

/* Funci�n que devuelve el tipo del identificador de edificio especificado
   Devuelve -1 en caso de que no lo encuentre */
int obtieneTipoEdificio (int edif, Lista<Edificio*> *listaEdificios)
{
    Edificio *unEdificio;
    int tamano, id, tipoEdificio;

    // Obtenci�n del tamano de la lista de edificios
    tamano = listaEdificios->obtieneTamano ();

    // B�squeda del edificio por la lista
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del edificio
	unEdificio = listaEdificios->obtieneElemento (i);

        // Obtencion del identificador del edificio
        id = unEdificio->obtieneAtributo ("id");

        // Si coinciden los identificadores
        if (id == edif)
	{
            // Obtencion del tipo del edificio
            tipoEdificio = unEdificio->obtieneAtributo ("tipo");

            return tipoEdificio;
	}
    }

    return -1;   
}

/***************************************************************************/

/* Funci�n que devuelve el �ndice de un edificio de la lista dada si la 
   posici�n especificada coincide con �l 
   En otro caso devuelve -1 */
int coincideEdificio (int posx, int posy, Lista<Edificio*> *listaEdificios)
{
    Edificio *unEdificio;
    int tamano, posx1, posy1, casilx1, casily1;

    // Obtenci�n del tama�o de la lista de edificios
    tamano = listaEdificios->obtieneTamano ();

    // B�squeda por la lista de edificios
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del edificio
	unEdificio = listaEdificios->obtieneElemento (i);
	
	// Obtenci�n de las coordenadas (x,y) del edificio
	posx1 = unEdificio->obtieneAtributo ("posx");
	posy1 = unEdificio->obtieneAtributo ("posy");

	// Obtenci�n del n�mero de casillas que ocupa el edificio
	casilx1 = unEdificio->obtieneAtributo ("casilx");
	casily1 = unEdificio->obtieneAtributo ("casily");

	// Comprobaci�n de coordenadas
	if ((posx >= posx1) && (posx < posx1 + casilx1))
	    if ((posy >= posy1) && (posy < posy1 + casily1))
		return i;		    
    }

    return -1;
}

/***************************************************************************/

/* Funci�n que devuelve el �ndice de un objeto de la lista dada si la 
   posici�n especificada coincide con �l 
   En otro caso devuelve -1 */
int coincideObjeto (int posx, int posy, Lista<Objeto*> *listaObjetos)
{
    Objeto *unObjeto;
    int tamano, posx1, posy1, casilx1, casily1;

    // Obtenci�n del tama�o de la lista de objetos
    tamano = listaObjetos->obtieneTamano ();

    // B�squeda por la lista de objetos
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del objeto
	unObjeto = listaObjetos->obtieneElemento (i);
	
	// Obtenci�n de las coordenadas (x,y) del objeto
	posx1 = unObjeto->obtieneAtributo ("posx");
	posy1 = unObjeto->obtieneAtributo ("posy");

	// Obtenci�n del n�mero de casillas que ocupa el objeto
	casilx1 = unObjeto->obtieneAtributo ("casilx");
	casily1 = unObjeto->obtieneAtributo ("casily");

	// Comprobaci�n de coordenadas
	if ((posx >= posx1) && (posx < posx1 + casilx1))
	    if ((posy >= posy1) && (posy < posy1 + casily1))
		return i;		    
    }

    return -1;
}

/***************************************************************************/

/* Funci�n que devuelve el �ndice de un personaje de la lista dada si la 
   posici�n especificada coincide con �l 
   En otro caso devuelve -1 */
int coincidePersonaje (int posx, int posy, Lista<Personaje*> *listaP)
{
    Personaje *unPersonaje;
    int tamano, posx1, posy1;

    // Obtenci�n del tama�o de la lista de personajes
    tamano = listaP->obtieneTamano ();

    // B�squeda por la lista de personajes
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del personaje
	unPersonaje = listaP->obtieneElemento (i);

	// Obtenci�n de las coordenadas (x,y) del personaje 
	posx1 = unPersonaje->obtieneAtributo ("posx");
	posy1 = unPersonaje->obtieneAtributo ("posy");

	// Comprobaci�n de coordenadas
	if ((posx1 == posx) && (posy1 == posy))
	    return i;	
    }

    return -1;  
}

/***************************************************************************/

/* Funci�n que comprueba si un objeto de la lista con la posici�n especificada
   es de tipo trampa o no
   Se devuelve el identificador del objeto en caso de que sea una trampa
   En otro caso se devuelve -1
   En visible se devuelve si el objeto est� oculto o no */
int objetoTrampa (int posx, int posy, int *visible, 
		  Lista<Objeto*> *listaObjetos)
{
    Objeto *unObjeto;
    int tamano, posx1, posy1, tipo;
    
    // Obtenci�n del tama�o de la lista de objetos
    tamano = listaObjetos->obtieneTamano ();

    // B�squeda por la lista de objetos
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n del objeto
	unObjeto = listaObjetos->obtieneElemento (i);

	// Obtenci�n de las coordenadas (x,y) del objeto
	posx1 = unObjeto->obtieneAtributo ("posx");
	posy1 = unObjeto->obtieneAtributo ("posy");

	// Comprobaci�n de coordenadas
	if ((posx == posx1) && (posy == posy1))
	{
	    // Obtenci�n del tipo del objeto
	    tipo = unObjeto->obtieneAtributo ("tipo");

	    // Si es de tipo pinchos
	    if (tipo == 17)
	    {
		*visible = unObjeto->obtieneAtributo ("visi");
		return i;
	    }

	    // En otro caso
	    else
		return -1;
	}
    }    

    return -1;
}

/***************************************************************************/

// Funci�n que activa el objeto de la lista especificada a visible
void objetoVisible (Lista<Objeto*> *listaObjetos, int indiceO)
{
    Objeto *unObjeto;

    // Obtencion del objeto
    unObjeto = listaObjetos->obtieneElemento (indiceO);

    // Actualizaci�n del objeto
    unObjeto->reAsignaAtributo ("visi", 1);
    listaObjetos->reAsignaElemento (indiceO, unObjeto);
}

/***************************************************************************/

/* Funci�n que cambia el tipo del objeto especificado incrementando el
   n�mero de monedas del personaje tambi�n indicado */
void liberaPrisionero (Lista<Personaje*> *listaP, int indiceP,
		       Lista<Objeto*> *listaObjetos, int indiceO)
{
    Objeto *unObjeto;
    Personaje *unPersonaje;
    int tipo, monedas;

    // Obtenci�n del objeto
    unObjeto = listaObjetos->obtieneElemento (indiceO);

    // Obtenci�n del tipo de objeto
    tipo = unObjeto->obtieneAtributo ("tipo");

    // Modificaci�n del tipo de objeto
    unObjeto->reAsignaAtributo ("tipo", tipo + 1);

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del n�mero de monedas del personaje
    monedas = unPersonaje->obtieneEqu (3);

    // Modificaci�n del n�mero de monedas del personaje
    unPersonaje->reAsignaEqu (3, monedas + 50);

    // Actualizaci�n de las listas
    listaP->reAsignaElemento (indiceP, unPersonaje);
    listaObjetos->reAsignaElemento (indiceO, unObjeto);
}

/***************************************************************************/

/* Funci�n que devuelve el tipo de casilla de la indicada en la lista
   En caso de que la casilla no exista devuelve -1 */
int tipoCasilla (int posx, int posy, Lista<Casilla*> *listaCasillas)
{
    Casilla *unaCasilla;
    int tamano, posx1, posy1, tipo;

    // Obtenci�n del tama�o de la lista de casillas
    tamano = listaCasillas->obtieneTamano ();

    // B�squeda por la lista de casillas
    for (int i = 0; i < tamano; i++)
    {
	// Obtenci�n de la casilla
	unaCasilla = listaCasillas->obtieneElemento (i);
	
	// Obtenci�n de las coordenadas (x,y) de la casilla
	posx1 = unaCasilla->obtieneAtributo ("posx");
	posy1 = unaCasilla->obtieneAtributo ("posy");

	// Comprobaci�n de coordenadas
	if ((posx1 == posx) && (posy1 == posy))
	{
	    // Obtenci�n del tipo de la casilla
	    tipo = unaCasilla->obtieneAtributo ("tipo");

	    return tipo;
	}
    }

    return -1;
}

/***************************************************************************/

/* Funci�n que devuelve una posici�n para un personaje que no sea coincidente 
   con ning�n otro elemento */
void obtienePosicion (int xinf, int xsup, int yinf, int ysup, 
		      int *posx, int *posy, Lista<Personaje*> *listaP)
{
    Lista<Edificio*> *listaEdificios;
    Lista<Objeto*> *listaObjetos;
    int fin = 0;

    // Carga de las listas de edificios y objetos
    listaEdificios = cargaEdificios (xinf, xsup, yinf, ysup);
    listaObjetos = cargaObjetos (xinf, xsup, yinf, ysup, -1);

    // Bucle para la obtenci�n de una posici�n correcta
    while (fin != 1)
    {
	// Obtenci�n de una posici�n (x,y) aleatoria
	*posx = generaAleatorio (xinf, xsup-1); 
	*posy = generaAleatorio (xinf, xsup-1);
	
	// Comprobaci�n de que la casilla est� vac�a
	if ((coincideEdificio (*posx, *posy, listaEdificios) == -1) &&
	    (coincideObjeto (*posx, *posy, listaObjetos) == -1) &&
	    (coincidePersonaje (*posx, *posy, listaP) == -1))

		fin = 1;
    }
}

/***************************************************************************/

// Funci�n que realiza ntiradas de un dado cuyo n�mero de caras se indica
int tiraDado (int nveces, int ncaras)
{
    int suma = 0;
 
    // Bucle de acumulaci�n de tiradas
    for (int i = 0; i < nveces; i++)    	
	suma += generaAleatorio (1, ncaras);
    
    return suma;
} 

/***************************************************************************/

// Funci�n que ajusta el valor del md dado con una tirada de dados
int ajustaMD (int valor)
{
    int nveces;

    if (valor < 12)
        valor = -tiraDado (1, 4);

    else if (valor < 24)
        valor = 0;
        
    else if (valor < 32)
        valor = tiraDado (1, 4);
        
    else if (valor < 40)
        valor = tiraDado (1, 6);
        
    else
    {
        nveces = 1 + ((valor - 40) / 16);        
	valor = tiraDado (nveces, 6);
    }

    return valor;
}

/***************************************************************************/

/* Funci�n que ajusta el valor de habilidad en funci�n de la influencia y
   la caracteristica dada */
int ajustaMH (char influencia, int caracteristica)
{
    int valor, signo;

    // Si es una influencia Primaria
    if (influencia == 'P')
	return caracteristica - 10;
        
    // Si es una influencia Secundaria
    else if (influencia == 'S')
    {
        valor = caracteristica - 10;

        if (valor < 0)
            signo = -1;
        else
            signo = 1;

        valor = abs (valor);
        
        if ((valor % 2) == 0)
            return (valor / 2) * signo;

        else
            return ((valor / 2) + 1) * signo;
    }

    // Si es una influencia Negativa
    else
        return 10 - caracteristica;
}

/***************************************************************************/

/* Funci�n que ajusta el momento de reacci�n en funci�n del tama�o y destreza
   especificados */
int ajustaMMR (int tam, int des)
{
    int mtam, mdes;

    // Obtenci�n de los modificadores de tama�o
    if (tam < 10)   
	mtam = 3;
    
    else if (tam < 16)    
	mtam = 2;
	    
    else if (tam < 20)    
	mtam = 1;

    else    
	mtam = 0;

    // Obtenci�n de los modificadores de destreza
    if (des < 10)   
	mdes = 4;
    
    else if (des < 16)    
	mdes = 3;
	    
    else if (des < 20)    
	mdes = 2;

    else    
	mdes = 1;


    return mtam + mdes;
}

/***************************************************************************/

/* Funci�n que ajusta el n�mero de turnos en funci�n del momento de reacci�n
   especificado */
int ajustaNturnos (int mmr)
{
    if (mmr >= 10)
	return 1;

    else if (mmr >= 7)
	return 2;

    else if (mmr >= 4)
	return 3;

    else 
	return 4;
}

/***************************************************************************/

/* Funci�n que realiza una tirada de la habilidad especificada
   Devuelve 1 si ha tenido �xito
   En caso contrario devuelve 0 */
int tiradaMH (Lista<Personaje*> *listaP, int indiceP, int habilidad)
{
    Personaje *unPersonaje;
    int mh, tirada, ene, ham, sed;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n de ene, ham, sed del personaje
    ene = unPersonaje->obtieneAtributo ("ene");
    ham = unPersonaje->obtieneAtributo ("ham");
    sed = unPersonaje->obtieneAtributo ("sed");

    // Si el personaje no tiene carencias
    if ((ene > 0) && (ham > 0) && (sed > 0))
    {
	// Obtenci�n del mh correspondiente
	if (habilidad == 1)
	    mh = unPersonaje->obtieneAtributo ("mh1");

	else if (habilidad == 2)
	    mh = unPersonaje->obtieneAtributo ("mh2");

	else
	    mh = habilidad;

	// Tirada de habilidad
	tirada = tiraDado (100, 1);

	// Comprobaci�n del �xito de la tirada
	if (tirada <= mh)
	    return 1;

	else
	    return 0;
    }

    return 0;
}

/***************************************************************************/

/* Funci�n que devuelve 1 si el personaje1 especificado sale victorioso
   enfrentado su habilidad con el personaje2 tambi�n especificado */
int enfrentaMH (Lista<Personaje*> *listaP, int indiceP1, int indiceP2)
{
    Personaje *personaje1;
    Personaje *personaje2;
    int exito, mh1, mh2;

    // Obtenci�n del personaje1
    personaje1 = listaP->obtieneElemento (indiceP1);

    // Obtenci�n del modificador de sigilo del personaje1
    mh1 = personaje1->obtieneAtributo ("mh1");

    // Obtenci�n del personaje2
    personaje2 = listaP->obtieneElemento (indiceP2);

    // Tirada de percepci�n del personaje2
    exito = tiradaMH (listaP, indiceP2, 2);

    // Si �xito del personaje2
    if (exito == 1)
    {
	// Obtenci�n del modificador de percepci�n del personaje2
	mh2 = personaje2->obtieneAtributo ("mh2");

	// Tirada de sigilo del personaje1
	exito = tiradaMH (listaP, indiceP1, mh2 - mh1);

	// Si �xito del personaje1
	if (exito == 1)
	    return 1;

	else
	    return 0;
    }

    // Si pifia del personaje2 o si no ha habido tirada
    else
    {
	// Tirada de sigilo del personaje1
	exito = tiradaMH (listaP, indiceP1, mh1);

	// Si �xito del personaje1
	if (exito == 1)
	    return 1;

	else
	    return 0;
    }
}

/***************************************************************************/

/* Funci�n que realiza un ataque de un personaje a otro decrementando
   los pg del segundo */
void atacaPersonaje (Lista<Personaje*> *listaP, int indiceP1, int indiceP2)
{
    Personaje *personaje1;
    Personaje *personaje2;
    int esp, arma, escudo, armadura, fue, tam, pd, md, pa, pg, golpe;

    // Obtenci�n del personaje2
    personaje2 = listaP->obtieneElemento (indiceP2);

    // Obtenci�n de la especie del personaje2 
    esp = personaje2->obtieneAtributo ("esp");

    // Obtenci�n del escudo del personaje2
    escudo = personaje2->obtieneEqu (0);

    /* Si el personaje2 no tiene escudo se obtienen los puntos de armadura 
       naturales */
    if (escudo == -1)
    {
	// Humano, Hobbit, Elfo, Mono
	if ((esp < 3) || (esp == 4))
	    pa = 3;
	
	// Gigante
	else if (esp == 3)
	    pa = 6;
		
    }

    /* Si el personaje2 tiene escudo se obtienen los puntos de armadura 
       asociados */
    else
    {
	switch (escudo)
	{
	    // Escudo1
	    case 1:
	    {
		pa = tiraDado (2, 1);
		break;
	    }
	    
	    // Escudo2
	    case 2:
	    {
		pa = tiraDado (4, 1);
		break;
	    }
	    
	    // Escudo3
	    case 3:
	    {
		pa = tiraDado (6, 1);
		break;
	    }
	}
    }
    
    // Obtenci�n de la armadura del personaje2
    armadura = personaje2->obtieneEqu (2);

    // Si el personaje2 tiene armadura
    if (armadura != -1)
    {
	// Comprobaci�n del tipo de armadura
	switch (armadura)
	{
	    // Armadura de cuero
	    case 1:
	    {
		pa += 2;
		break;
	    }
	    
	    // Cota de anillos
	    case 2:
	    {
		pa += 5;
		break;
	    }
	    
	    // Armadura
	    case 3:
	    {
		pa += 7;
		break;
	    }
	    
	    // Coraza
	    case 4:
	    {
		pa += 9;
		break;
	    }
	}
    }

    // Obtenci�n del personaje1
    personaje1 = listaP->obtieneElemento (indiceP1);

    // Obtenci�n de la fuerza del personaje1
    fue = personaje1->obtieneAtributo ("fue");
    
    // Obtenci�n del tama�o del personaje1
    tam = personaje1->obtieneAtributo ("tam");
    
    // Obtenci�n del modificador de da�o del personaje1
    if ((fue > 0) && (tam > 0))
	md = ajustaMD (fue + tam);
    else
	md = 0;
    
    // Obtenci�n del arma del personaje1
    arma = personaje1->obtieneEqu (1);
    
    /* Si el personaje1 no tiene arma se obtienen los puntos de da�o 
       naturales */
    if (arma == -1)
    {
	// Obtenci�n de la especie del personaje1 
	esp = personaje1->obtieneAtributo ("esp");
	
	// Gigante
	if (esp == 3)	    
	    pd = tiraDado (6, 2);
	
	// Otra especie
	else
	    pd = tiraDado (6, 1);
    }
    
    // Si el personaje1 tiene arma se obtienen los puntos de da�o asociados
    else
    {
	// Comprobaci�n del tipo de arma
	switch (arma)
	{
	    // Espada1
	    case 1:
	    {
		pd = tiraDado (6, 1) + 1;
		break;
	    }
	    
	    // Espada2
	    case 2:
	    {
		pd = tiraDado (8, 1) + 1;
		break;
	    }
	    
	    // Hacha
	    case 3:
	    {
		pd = tiraDado (8, 1) + 2;
		break;
	    }
	    
	    // Bola y cadena
	    case 4:
	    {
		pd = tiraDado (1, 10) + 1;
		break;
	    }
	}
    }
	
    // Calculo del da�o recibido
    golpe = pa - (md + pd);
    
    // Si ha habido da�o
    if (golpe < 0)
    {
	// Obtenci�n de los puntos de golpe del personaje2
	pg = personaje2->obtieneAtributo ("pg");
	
	// Decremento de los puntos de golpe del personaje2
	pg += golpe;
	personaje2->reAsignaAtributo ("pg", pg);			
	
	// Actualizaci�n del personaje2 en la lista
	listaP->reAsignaElemento (indiceP2, personaje2);
    }
}

/***************************************************************************/

/* Funci�n que incrementa las caracter�sticas del personaje indicado de la
   lista dada */
void incrementaCaracteristicas (Lista<Personaje*> *listaP, int indiceP)
{
    Personaje *unPersonaje;
    int fue, con, tam, des, inte, pg, ene, ham, sed;
    int mh1, mh2, mmr, nturnos;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n de la fue del personaje
    fue = unPersonaje->obtieneAtributo ("fue");

    // Obtenci�n de la con del personaje
    con = unPersonaje->obtieneAtributo ("con");

    // Obtenci�n del tam del personaje
    tam = unPersonaje->obtieneAtributo ("tam");

    // Obtenci�n de la des del personaje
    des = unPersonaje->obtieneAtributo ("des");
    
    // Obtenci�n de la inte del personaje
    inte = unPersonaje->obtieneAtributo ("inte");

    // Incremento de la fue del personaje
    if ((fue + 1) <= (con + tam))
    {
	fue++;
	unPersonaje->reAsignaAtributo ("fue", fue);
    }

    // Incremento de la con del personaje
    if ((con + 1) <= (fue + tam))
    {
	con++;
	unPersonaje->reAsignaAtributo ("con", con);
    }

    // Incremento de la des del personaje
    if (des + 1 <= 2 * des)
    {
	des++;
	unPersonaje->reAsignaAtributo ("des", des);

    }

    // Actualizaci�n de los pg del personaje
    pg = (int) (round ((con + tam) / 2.0));
    unPersonaje->reAsignaAtributo ("pg", pg);
    unPersonaje->reAsignaAtributo ("maxpg", pg);

    // Actualizaci�n de la ene del personaje
    ene = fue + con;
    unPersonaje->reAsignaAtributo ("ene", ene);
    unPersonaje->reAsignaAtributo ("maxene", ene);

    // Actualizaci�n de la ham y sed del personaje
    ham = con + tam;
    sed = con + tam;
    unPersonaje->reAsignaAtributo ("ham", ham);
    unPersonaje->reAsignaAtributo ("sed", sed);
    unPersonaje->reAsignaAtributo ("maxham", ham);
    unPersonaje->reAsignaAtributo ("maxsed", sed);

    // Actualizaci�n de los mh del personaje
    mh1 = 10 + ajustaMH ('P', des) + ajustaMH ('N', tam);
    mh2 = 25 + ajustaMH ('P', inte) + ajustaMH ('S', con);
    unPersonaje->reAsignaAtributo ("mh1", mh1);
    unPersonaje->reAsignaAtributo ("mh2", mh2);

    // Actualizaci�n del momento de reacci�n del personaje
    mmr = ajustaMMR (tam, des);
    unPersonaje->reAsignaAtributo ("mmr", mmr);

    // Actualizaci�n del n�mero de turnos del personaje
    nturnos = ajustaNturnos (mmr);
    unPersonaje->reAsignaAtributo ("nturnos", nturnos);

    // Actualizaci�n del personaje en la lista
    listaP->reAsignaElemento (indiceP, unPersonaje);
}

/***************************************************************************/

/* Funci�n que incrementa los atributos ene, ham, sed y pg del personaje
   indicado de la lista dada */
void incrementaSalud (Lista<Personaje*> *listaP, int indiceP, int coste)
{
    Personaje *unPersonaje;
    int maxene, maxham, maxsed, maxpg, monedas;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n de las monedas que tiene el personaje
    monedas = unPersonaje->obtieneEqu (3);

    // Si tiene suficiente monedas o no necesita pagar
    if ((monedas >= 50) || (coste == 0))
    {	
	// Obtenci�n de los m�ximos de salud
	maxene = unPersonaje->obtieneAtributo ("maxene");
	maxham = unPersonaje->obtieneAtributo ("maxham");
	maxsed = unPersonaje->obtieneAtributo ("maxsed");
	maxpg = unPersonaje->obtieneAtributo ("maxpg");

	// Incremento de la salud del personaje al m�ximo
	unPersonaje->reAsignaAtributo ("ene", maxene);
	unPersonaje->reAsignaAtributo ("ham", maxham);
	unPersonaje->reAsignaAtributo ("sed", maxsed);
	unPersonaje->reAsignaAtributo ("pg", maxpg);

	// Decremento de las monedas del personaje
	if (coste != 0)
	{
	    monedas -= 50;
	    unPersonaje->reAsignaEqu (3, monedas);
	}

	// Actualizaci�n del personaje
	listaP->reAsignaElemento (indiceP, unPersonaje);
    }
}

/***************************************************************************/

/* Funci�n que decrementa los atributos ene, ham, sed del personaje indicado
   de la lista dada */
void decrementaSalud (Lista<Personaje*> *listaP, int indiceP, int decremento)
{
    Personaje *unPersonaje;
    int ene, ham, sed, pg;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n de ene, ham, sed del personaje
    ene = unPersonaje->obtieneAtributo ("ene");
    ham = unPersonaje->obtieneAtributo ("ham");
    sed = unPersonaje->obtieneAtributo ("sed");

    // Decremento de ene, ham, sed del personaje
    ene -= decremento;    
    ham -= decremento;
    sed -= decremento;

    // Comprobaci�n de los m�nimos
    if (ene < 0)
	ene = 0;

    if (ham < 0)
	ham = 0;
    
    if (sed < 0)
	sed = 0;
    
    // Asignaci�n de ene, ham y sed del personaje
    unPersonaje->reAsignaAtributo ("ene", ene);
    unPersonaje->reAsignaAtributo ("ham", ham);
    unPersonaje->reAsignaAtributo ("sed", sed);

    // Comprobaci�n de la ene del personaje
    if (ene == 0)
    {
	pg = unPersonaje->obtieneAtributo ("pg");
	if (pg > 0)
	    pg--;

	unPersonaje->reAsignaAtributo ("pg", pg);	    
    }
		
    // Comprobaci�n del ham del personaje
    if (ham == 0)
    {
	pg = unPersonaje->obtieneAtributo ("pg");
	if (pg > 0)
	    pg--;

	unPersonaje->reAsignaAtributo ("pg", pg);
    }

    // Comprobaci�n de la sed del personaje
    if (sed == 0)
    {
	pg = unPersonaje->obtieneAtributo ("pg");
	if (pg > 0)
	    pg--;

	unPersonaje->reAsignaAtributo ("pg", pg);

    }

    // Actualizaci�n del personaje
    listaP->reAsignaElemento (indiceP, unPersonaje);
}

/***************************************************************************/

// Funci�n que decrementa el pg del personaje indicado de la lista dada
void decrementaPG (Lista<Personaje*> *listaP, int indiceP, int decremento)
{
    Personaje *unPersonaje;
    int pg;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Decremento del pg
    pg = unPersonaje->obtieneAtributo ("pg");
    pg -= decremento;

    if (pg < 0)
	pg = 0;

    unPersonaje->reAsignaAtributo ("pg", pg);

    // Actualizaci�n del personaje
    listaP->reAsignaElemento (indiceP, unPersonaje);
}

/***************************************************************************/

// Funci�n que incrementa el ene del personaje indicado de la lista dada
void incrementaEne (Lista<Personaje*> *listaP, int indiceP)
{
    Personaje *unPersonaje;
    int maxene;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del maxene del personaje
    maxene = unPersonaje->obtieneAtributo ("maxene");

    // Incremento del ene del personaje
    unPersonaje->reAsignaAtributo ("ene", maxene);

    // Actualizaci�n del personaje
    listaP->reAsignaElemento (indiceP, unPersonaje);
}   

/***************************************************************************/

// Funci�n que incrementa el ham del personaje indicado de la lista dada
void incrementaHam (Lista<Personaje*> *listaP, int indiceP, int incremento)
{
    Personaje *unPersonaje;
    int ham, maxham;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del ham del personaje
    ham = unPersonaje->obtieneAtributo ("ham");

    // Obtenci�n del maxham del personaje
    maxham = unPersonaje->obtieneAtributo ("maxham");

    // Incremento del ham del personaje
    if (incremento == 1)
	ham += 8;
    else
	ham = maxham;

    if (ham > maxham)
	ham = maxham;

    unPersonaje->reAsignaAtributo ("ham", ham);

    // Actualizaci�n del personaje
    listaP->reAsignaElemento (indiceP, unPersonaje);
}   

/***************************************************************************/

/* Funci�n que incrementa el atributo sed del personaje indicado de la lista
   dada */
void incrementaSed (Lista<Personaje*> *listaP, int indiceP)
{
    Personaje *unPersonaje;
    int maxsed;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del maxsed del personaje
    maxsed = unPersonaje->obtieneAtributo ("maxsed");

    // Incremento del atributo sed del personaje al m�ximo
    unPersonaje->reAsignaAtributo ("sed", maxsed);

    // Actualizaci�n del personaje
    listaP->reAsignaElemento (indiceP, unPersonaje);
}

/***************************************************************************/

// Funci�n que incrementa los mh del personaje especificado de la lista dada
void incrementaMH (Lista<Personaje*> *listaP, int indiceP)
{
    Personaje *unPersonaje;
    int mh1, mh2, estu, monedas;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del n�mero de monedas del personaje
    monedas = unPersonaje->obtieneEqu (3);

    // Si el personaje tiene suficientes monedas
    if (monedas >= 50)
    {
	// Decremento del n�mero de monedas
	unPersonaje->reAsignaEqu (3, monedas - 50);

	// Obtenci�n de los mh del personaje
	mh1 = unPersonaje->obtieneAtributo ("mh1");
	mh2 = unPersonaje->obtieneAtributo ("mh2");

	// Obtenci�n del n�mero de veces que ha estudiado el personaje
	estu = unPersonaje->obtieneAtributo ("estu");

	// Modificaci�n del estu del personaje
	estu++;
	unPersonaje->reAsignaAtributo ("estu", estu);

	// Decremento de la salud del personaje
	decrementaSalud (listaP, indiceP, 2 * estu);

	// Incremento en 1 percentil de los mh del personaje
	if (mh1 < 100)
	    mh1++;
	
	if (mh2 < 100)
	    mh2++;

	// Asignaci�n de los mh incrementados al personaje
	unPersonaje->reAsignaAtributo ("mh1", mh1);
	unPersonaje->reAsignaAtributo ("mh2", mh2);

	// Actualizaci�n del personaje
	listaP->reAsignaElemento (indiceP, unPersonaje);
    }
}

/***************************************************************************/

/* Funci�n que incrementa el equipo del personaje especificado con el objeto
   dado */
void incrementaEqu (Lista<Personaje*> *listaP, int indiceP, 
		    Lista<Objeto*> *listaObjetos, int indiceO)
{
    Personaje *unPersonaje;
    Objeto *unObjeto;
    int equObjeto, equPersonaje;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del objeto
    unObjeto = listaObjetos->obtieneElemento (indiceO);

    // Obtenci�n del equipo del objeto
    equObjeto = unObjeto->obtieneAtributo ("equ");

    // Si el elemento es una llave
    if (equObjeto == 0)
    {
	// Obtenci�n de la llave del personaje
	equPersonaje = unPersonaje->obtieneEqu (4);

	// Si el personaje no tiene llave
	if (equPersonaje == -1)
	{
	    // Asignaci�n de la llave al personaje
	    unPersonaje->reAsignaEqu (4, 1);

	    // Eliminaci�n del objeto
	    unObjeto->reAsignaAtributo ("tipo", -1);
	}
    }

    // Si el elemento son monedas (50 unidades)
    else if (equObjeto == 11)
    {
	// Obtenci�n del n�mero de monedas del personaje
	equPersonaje = unPersonaje->obtieneEqu (3);

	// Incremento del n�mero de monedas del personaje
	unPersonaje->reAsignaEqu (3, equPersonaje + 50);

	// Eliminaci�n del objeto
	unObjeto->reAsignaAtributo ("tipo", -1);
    }

    // Si el elemento es una poci�n (1->10)
    else if ((equObjeto >= 1) && (equObjeto <= 10))
    {	
	// Obtenci�n de la poci�n del personaje
	equPersonaje = unPersonaje->obtieneEqu (5);

	// Asignaci�n de la nueva poci�n	
	unPersonaje->reAsignaEqu (5, equObjeto);

	// Si el personaje ya ten�a una poci�n anterior
	if (equPersonaje != -1)
	
	    // Intercambio de pociones
	    unObjeto->reAsignaAtributo ("equ", equPersonaje);	
	
	// Si el personaje no ten�a poci�n
	else
	
	    // Eliminaci�n del objeto
	    unObjeto->reAsignaAtributo ("tipo", -1);	
    }

    // Actualizaci�n de las listas
    listaP->reAsignaElemento (indiceP, unPersonaje);
    listaObjetos->reAsignaElemento (indiceO, unObjeto);
}

/***************************************************************************/

/* Funci�n que incrementa del equipo del personaje1 con el equipo del 
   personaje2 */
void incrementaEqu (Lista<Personaje*> *listaP, int indiceP1, int indiceP2)
{
    Personaje *personaje1;
    Personaje *personaje2;
    int equ1, equ2;

    // Obtenci�n del personaje1
    personaje1 = listaP->obtieneElemento (indiceP1);

    // Obtenci�n del personaje2
    personaje2 = listaP->obtieneElemento (indiceP2);

    // Obtenci�n del n�mero de monedas del personaje1
    equ1 = personaje1->obtieneEqu (3);

    // Obtenci�n del n�mero de monedas del personaje2
    equ2 = personaje2->obtieneEqu (3);

    // Incremento del n�mero de monedas del personaje1
    personaje1->reAsignaEqu (3, equ1 + equ2);

    // Decremento del n�mero de monedas del personaje2
    personaje2->reAsignaEqu (3, 0);
    
    // Obtenci�n de la llave del personaje1
    equ1 = personaje1->obtieneEqu (4);
	
    // Obtenci�n de la llave del personaje2
    equ2 = personaje2->obtieneEqu (4);

    // Si el personaje1 no tiene llave y el personaje2 s�
    if ((equ1 == -1) && (equ2 != -1))
    {
	// Asignaci�n de la llave al personaje1
	personaje1->reAsignaEqu (4, 1);

	// Eliminaci�n de la llave del personaje2
	personaje2->reAsignaEqu (4, -1);
    }
    
    // Obtenci�n de la poci�n del personaje1
    equ1 = personaje1->obtieneEqu (5);

    // Obtenci�n de la poci�n del personaje2
    equ2 = personaje2->obtieneEqu (5);

    // Si el personaje2 tiene poci�n
    if (equ2 != -1)
    {
	// Intercambio de pociones	
	personaje1->reAsignaEqu (5, equ2);
	personaje2->reAsignaEqu (5, equ1);	    
    }

    // Actualizaci�n de las listas
    listaP->reAsignaElemento (indiceP1, personaje1);
    listaP->reAsignaElemento (indiceP2, personaje2);
}

/***************************************************************************/

// Funci�n que incrementa el objetivo del personaje indicado de la lista dada
void incrementaObj (Lista<Personaje*> *listaP, int indiceP)
{
    Personaje *unPersonaje;
    int obj, entr, monedas, decremento;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del n�mero de veces que se ha entrenado el personaje
    entr = unPersonaje->obtieneAtributo ("entr");

    // Modificaci�n de entr
    entr++;
    decremento = entr * 50; 

    // Obtenci�n del n�mero de monedas del personaje
    monedas = unPersonaje->obtieneEqu (3);

    // Obtenci�n del objetivo del personaje
    obj = unPersonaje->obtieneAtributo ("obj");

    // Si tiene suficiente n�mero de monedas y ning�n objetivo a cumplir
    if ((monedas >= decremento) && (obj == 0))
    {
	// Actualizaci�n de entr
	unPersonaje->reAsignaAtributo ("entr", entr);

	// Actualizaci�n del n�mero de monedas
	unPersonaje->reAsignaEqu (3, monedas - decremento);

	// Actualizaci�n del objetivo del personaje
	obj = entr % 10;

	if (obj == 0)
	    obj = 10;

	unPersonaje->reAsignaAtributo ("obj", obj);

	// Actualizaci�n del personaje en la lista
	listaP->reAsignaElemento (indiceP, unPersonaje);
    }
}

/***************************************************************************/

// Funci�n que en funci�n del turno y la car decrementa la salud del personaje
void decrementaPersonaje (Lista<Personaje*> *listaClientes, int turnoP, 
			  int sock)
{
    Personaje *unPersonaje;
    int indice, escudo, arma, armadura, decremento = 0;

    // Cada diez turnos
    if ((turnoP % 10) == 0)
    {
	// Obtenci�n del �ndice del cliente
	indice = obtieneIndice (listaClientes, sock);
		
	// Obtenci�n del personaje
	unPersonaje = listaClientes->obtieneElemento (indice);

	// Obtenci�n del escudo del personaje
	escudo = unPersonaje->obtieneEqu (0);

	// Obtenci�n de la car del escudo
	if (escudo == 1)
	    decremento++;

	else if (escudo == 2)
	    decremento += 2;

	else if (escudo == 3)
	    decremento += 4;

	// Obtenci�n del arma del personaje
	arma = unPersonaje->obtieneEqu (1);

	// Obtenci�n de la car del arma
	if (arma == 1)
	    decremento++;

	else if (arma == 2)
	    decremento += 2;

	else if (arma == 3)
	    decremento += 3;

	else if (arma == 4)
	    decremento += 4;

	// Obtenci�n del armadura del personaje
	armadura = unPersonaje->obtieneEqu (2);

	// Obtenci�n de la car de la armadura
	if (armadura == 1)
	    decremento++;

	else if (armadura == 2)
	    decremento += 2;
	
	else if (armadura == 3)
	    decremento += 3;

	else if (armadura == 4)
	    decremento += 4;

	// Decremento de la salud del personaje
	decrementaSalud (listaClientes, indice, 1 + decremento);
    }
}

/***************************************************************************/

// Funci�n que devuelve el precio del objeto especificado
int obtienePrecio (int tipoObjeto)
{
    // Espada1, Escudo1, Cuero
    if ((tipoObjeto == 27) || (tipoObjeto == 31) || (tipoObjeto == 35))
	return 100;

    // Espada2, Escudo2, Cota de anillos
    else if ((tipoObjeto == 28) || (tipoObjeto == 32) || (tipoObjeto == 36))
	return 150;

    // Hacha, Escudo3, Armadura
    else if ((tipoObjeto == 29) || (tipoObjeto == 33) || (tipoObjeto == 37))
	return 200;

    // Bola y cadena, Coraza
    else
	return 250;
}

/***************************************************************************/

/* Funci�n que modifica el equipo del personaje especificado comprando el tipo
   de objeto dado */
void compraObjeto (Lista<Personaje*> *listaP, int indiceP, int tipoObjeto)
{
    Personaje *unPersonaje;
    int tipo, equ, indiceEqu, monedas, precio, mmr, nturnos, incremento = 0;

    // Obtenci�n del personaje
    unPersonaje = listaP->obtieneElemento (indiceP);

    // Obtenci�n del precio del objeto
    precio = obtienePrecio (tipoObjeto);

    // Comprobaci�n del tipo de objeto
    switch (tipoObjeto)
    {
	// Espada1
	case 27:
	{
	    indiceEqu = 1;
	    tipo = 1;
	    incremento = 2;
	    break;
	}

	// Espada2
	case 28:
	{
	    indiceEqu = 1;
	    tipo = 2;
	    incremento = 2;
	    break;
	}

	// Hacha
	case 29:
	{
	    indiceEqu = 1;
	    tipo = 3;
	    incremento = 2;
	    break;
	}

	// Bola y cadena
	case 30:
	{
	    indiceEqu = 1;
	    tipo = 4;
	    incremento = 2;
	    break;
	}

	// Escudo1
	case 31:
	{
	    indiceEqu = 0;
	    tipo = 1;
	    incremento = 3;
	    break;
	}

	// Escudo2
	case 32:
	{
	    indiceEqu = 0;
	    tipo = 2;
	    incremento = 3;
	    break;
	}

	// Escudo3
	case 33:
	{
	    indiceEqu = 0;
	    tipo = 3;
	    incremento = 3;
	    break;
	}

	// Cuero
	case 35:
	{
	    indiceEqu = 2;
	    tipo = 1;
	    break;
	}

	// Cota de anillos
	case 36:
	{
	    indiceEqu = 2;
	    tipo = 2;
	    break;
	}

	// Armadura
	case 37:
	{
	    indiceEqu = 2;
	    tipo = 3;
	    break;
	}

	// Coraza
	case 38:
	{
	    indiceEqu = 2;
	    tipo = 4;
	    break;
	}
    }

    // Obtenci�n del objeto que tenga el personaje
    equ = unPersonaje->obtieneEqu (indiceEqu);

    // Obtenci�n del n�mero de monedas del personaje
    monedas = unPersonaje->obtieneEqu (3);

    // Si no tiene el objeto 
    if (equ == -1)
    {
	// Si tiene suficiente monedas
	if (monedas >= precio)
	{
	    // Compra del objeto	    
	    unPersonaje->reAsignaEqu (3, monedas - precio);
	    unPersonaje->reAsignaEqu (indiceEqu, tipo);

	    // Actualizaci�n del momento de reacci�n del personaje
	    mmr = unPersonaje->obtieneAtributo ("mmr") + incremento;
	    unPersonaje->reAsignaAtributo ("mmr", mmr);

	    // Actualizaci�n del n�mero de turnos del personaje
	    nturnos = ajustaNturnos (mmr);
	    unPersonaje->reAsignaAtributo ("nturnos", nturnos);

	    // Actualizaci�n del personaje
	    listaP->reAsignaElemento (indiceP, unPersonaje);
	}
    }

    // Si tiene el objeto pero de distinto tipo
    else if (equ != tipo)
    {
	// Obtenci�n del tipo de objeto del equ del personaje
	if (indiceEqu == 0)
	    equ += 30;

	else if (indiceEqu == 1)
	    equ += 26;

	else
	    equ += 34;

	// Venta del objeto anterior
	monedas += obtienePrecio (equ);

	// Si tiene suficiente monedas
	if (monedas >= precio)
	{
	    // Compra del nuevo objeto
	    unPersonaje->reAsignaEqu (3, monedas - precio);
	    unPersonaje->reAsignaEqu (indiceEqu, tipo);

	    // Actualizaci�n del personaje
	    listaP->reAsignaElemento (indiceP, unPersonaje);
	}
    }
}

/***************************************************************************/

/* Funci�n que devuelve un entero con la acci�n a realizar asociada a la 
   posici�n del cursor especificada */
int obtieneAccion (int cursorx, int cursory, Lista<Edificio*> *listaEdificios, 
		   Lista<Objeto*> *listaObjetos, 
		   Lista<Personaje*> *listaP, int indiceP, 
		   Lista<Casilla*> *listaCasillas, int cursorStatus)
{
    Personaje *unPersonaje;
    Objeto *unObjeto;
    int edif, obj, pocion, indiceP1, indiceO, tipoC, tipoE, tipoO = -1;

    // Si el estado del cursor est� a 1
    if (cursorStatus == 1)
    {
	// Coincidencia del cursor con personajes distinto al activo
	indiceP1 = coincidePersonaje (cursorx, cursory, listaP);
	if (indiceP1 == indiceP)
	    indiceP1 = -1;

	// Si coincide con alg�n personaje
	if (indiceP1 != -1)
	    return 4;

	// Si no coincide con alg�n personaje
	else
	{
	    // Coincidencia del cursor con objetos
	    indiceO = coincideObjeto (cursorx, cursory, listaObjetos);

	    // Si coincide con alg�n objeto
	    if (indiceO != -1)
	    {
		// Obtenci�n del objeto
		unObjeto = listaObjetos->obtieneElemento (indiceO);

		// Obtenci�n del tipo de objeto
		tipoO = unObjeto->obtieneAtributo ("tipo");

		// Si es de tipo setas
		if (tipoO == 1)
		    return 6;

		// Si es de tipo miel
		else if (tipoO == 2)
		    return 7;

		// Si es de tipo cofre
		else if (tipoO == 3)
		    return 8;
		
		// Si es de tipo bruja
		else if (tipoO == 4)
		    return 9;

		// Si es de tipo prisionero
		else if ((tipoO == 9) || (tipoO == 11) || 
			 (tipoO == 13) || (tipoO == 15))
		    return 10;

		// Si es de tipo bibliotecaria
		else if (tipoO == 18)
		    return 11;

		// Si es de tipo posadera
		else if (tipoO == 21)
		    return 12;

		// Si es de tipo vendedor
		else if (tipoO == 25)
		{
		    // Obtenci�n del personaje
		    unPersonaje = listaP->obtieneElemento (indiceP);
		    
		    // Obtenci�n del edificio del personaje
		    edif = unPersonaje->obtieneAtributo ("edif");

		    // Obtenci�n del tipo de edificio
		    tipoE = obtieneTipoEdificio (edif, listaEdificios);

		    // Si es de tipo armas
		    if (tipoE == 3)
			return 13;

		    // Si es de tipo escudos
		    else if (tipoE == 4)
			return 17;

		    // Si es de tipo armaduras
		    else
			return 20;
		}
	    }
	
	    // Si no coincide con ning�n objeto bloqueante
	    if ((indiceO == -1) || (tipoO == 0))
	    {
		// Coincidencia del cursor con casillas de agua		
		tipoC = tipoCasilla (cursorx, cursory, listaCasillas);
		if (tipoC == 3)
		    return 24;		
	    } 		       		       
	}	
    }

    // Si el estado del cursor est� a 0
    else
    {
	// Coincidencia del cursor con objetos
	indiceO = coincideObjeto (cursorx, cursory, listaObjetos);
	
	// Si coincide con alg�n objeto
	if (indiceO != -1)
	{
	    // Obtenci�n del objeto
	    unObjeto = listaObjetos->obtieneElemento (indiceO);

	    // Obtenci�n del tipo de objeto
	    tipoO = unObjeto->obtieneAtributo ("tipo");

	    // Si es de tipo portal
	    if (tipoO == 7)
	    {
		// Obtenci�n del personaje
		unPersonaje = listaP->obtieneElemento (indiceP);

		// Obtenci�n del objetivo del cliente
		obj = unPersonaje->obtieneAtributo ("obj");
			    
		// Obtenci�n de la poci�n del cliente
		pocion = unPersonaje->obtieneEqu (5);

		// Si coincide la poci�n con el objetivo
		if (pocion == obj)				
		    return 25;
	    }
	}
    }

    return -1;
}

/***************************************************************************/

/* Funci�n que compone el nombre de un fichero a trav�s de las cadenas 
   especificadas */
char *obtieneFichero (char *path, int fichero, char *extension)
{
    char *cadena;
    char *nombre;
    int tamano;

    // Obtenci�n de la cadena nombre
    nombre = int2string (fichero);
    
    // Reserva de memoria para la cadena resultante
    tamano = strlen (path) + strlen (nombre) + strlen (extension) + 1;
    cadena = new char [tamano];
    if (cadena == NULL)
    {
	fprintf (stderr, "funciones.cc: obtieneFichero ");
	fprintf (stderr, "(char *, int, char *): ");
	fprintf (stderr, "Memoria insuficiente para cadena\n");
	exit (-1);
    }
    
    // Composici�n del nombre del fichero
    strcpy (cadena, path);
    strcat (nombre, extension);
    strcat (cadena, nombre);

    // Liberaci�n de recursos
    delete [] nombre;

    return cadena;
}

/***************************************************************************/

// Funci�n que realiza una copia de un fichero en otro
void copiaFichero (char *origen, char *destino)
{
    FILE *fOrigen;
    FILE *fDestino;
    char cadena[100];

    // Apertura del fichero origen
    fOrigen = fopen (origen, "r");
    if (!fOrigen)
    {
	fprintf (stderr, "funciones.cc: copiaFichero (char *, char *): ");
	fprintf (stderr, "No se puede abrir el fichero %s\n", origen);
	exit (-1);
    }

    // Creaci�n del fichero destino
    fDestino = fopen (destino, "w");
    if (!fDestino)
    {
	fprintf (stderr, "funciones.cc: copiaFichero (char *, char *): ");
	fprintf (stderr, "No se puede crear el fichero %s\n", destino);
	exit (-1);
    }

    // Copia del fichero origen en el fichero destino
    while (!feof (fOrigen))
    {
	fgets (cadena, 100, fOrigen);

	if (!feof (fOrigen))
	    fputs (cadena, fDestino);
    }

    // Cierre de ficheros
    fclose (fOrigen);
    fclose (fDestino);        
}

/***************************************************************************/

// Funci�n que devuelve un n�mero aleatorio en el rango especificado
int generaAleatorio (int inf, int sup)
{
    float aleatorio;

    // Ajuste del l�mite inferior si es negativo
    if (inf < 0)
	inf--;

    // Generaci�n del n�mero aleatorio
    aleatorio = rand () / (RAND_MAX + 1.0);

    return ((int) (inf + (sup - (inf) + 1) * aleatorio));

}

/***************************************************************************/

// Funci�n que convierte un entero en una cadena con dos d�gitos
char *int2string (int entero)
{
    int cociente, resto;
    char *cadena;

    cociente = entero / 10;
    resto = entero % 10;

    cadena = new char [3];
    if (cadena == NULL)
    {
	fprintf (stderr, "funciones.cc: int2string (int):  ");
	fprintf (stderr, "Memoria insuficiente para cadena\n");
	exit (-1);
    }

    cadena[0] = int2char (cociente);
    cadena[1] = int2char (resto);
    cadena[2] = '\0';    

    return cadena;
}

/***************************************************************************/

// Funci�n que convierte un entero en una cadena
char *itoa (int entero)
{
    char *cadena;
    char *aux;
    int resto, tamano, tamanoNuevo, fin, signo, j;
    
    // Inicializaci�n de par�metros
    cadena = NULL;
    aux = NULL;
    tamano = 0;
    fin = 0;

    // Obtenci�n del signo del entero
    if (entero < 0)
	signo = 1;
    else
	signo = 0;

    // Obtenci�n del valor absoluto
    entero = abs (entero);

    // Bucle
    while (fin == 0)
    {
	// Obtenci�n del resto
	resto = entero % 10;

	// Creaci�n de la cadena auxiliar
	aux = new char [tamano + 1];

	// Copia de la cadena en la cadena auxiliar
	for (int i = 0; i < tamano; i++)
	    aux[i] = cadena[i];

	// Inserci�n del nuevo d�gito
	aux[tamano] = int2char (resto);
	    
	// Eliminaci�n de la cadena
	if (cadena != NULL)
	    delete [] cadena;

	// Actualizaci�n de la cadena
	cadena = aux;

	// Incremento del tama�o
	tamano++;

	// Obtenci�n del cociente
	entero /= 10;
	
	// Si el cocientes es 0
	if (entero == 0)
	    fin = 1;	
    }

    // Si el entero es positivo
    if (signo == 0)
    {
	tamanoNuevo = tamano + 1;
	aux = new char [tamanoNuevo];
	j = 0;
    }

    // Si el entero es negativo
    else
    {
	tamanoNuevo = tamano + 2;
	aux = new char [tamanoNuevo];
	aux[0] = '-';
	j = 1;
    }

    // Reverse de la cadena
    for (int i = tamano - 1; i >= 0; i--)
    {
	aux[j] = cadena[i];
	j++;
    }

    // Eliminaci�n de la cadena
    delete [] cadena;

    // Inserci�n del \0
    aux[tamanoNuevo - 1] = '\0';
	
    return aux;
}

/***************************************************************************/

// Funci�n que convierte un entero en un caracter
char int2char (int entero)
{
    switch (entero)
    {
	case 0:
	{
	    return '0';
	    break;
	}

	case 1:
	{
	    return '1';
	    break;
	}   

	case 2:
	{
	    return '2';
	    break;
	}   

	case 3:
	{
	    return '3';
	    break;
	}   

	case 4:
	{
	    return '4';
	    break;
	}   

	case 5:
	{
	    return '5';
	    break;
	}   
	
	case 6:
	{
	    return '6';
	    break;
	}   

	case 7:
	{
	    return '7';
	    break;
	}   

	case 8:
	{
	    return '8';
	    break;
	}   

	default:
	    return '9';
	    break;
    }
}

/***************************************************************************/

// Funci�n que convierte un caracter en un entero
int char2int (char caracter)
{
    switch (caracter)
    {
	case '0':
	{
	    return 0;
	    break;
	}

	case '1':
	{
	    return 1;
	    break;
	}   

	case '2':
	{
	    return 2;
	    break;
	}   

	case '3':
	{
	    return 3;
	    break;
	}   

	case '4':
	{
	    return 4;
	    break;
	}   

	case '5':
	{
	    return 5;
	    break;
	}   
	
	case '6':
	{
	    return 6;
	    break;
	}   

	case '7':
	{
	    return 7;
	    break;
	}   

	case '8':
	{
	    return 8;
	    break;
	}   

	default:
	    return 9;
	    break;
    }
}

/***************************************************************************/
