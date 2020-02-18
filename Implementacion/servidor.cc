
/***************************************************************************
                          servidor.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <SDL_thread.h>

#include "conexionServidor.hh"
#include "lista.cc"
#include "edificio.hh"
#include "objeto.hh"
#include "personaje.hh"
#include "casilla.hh"
#include "elemento.hh"
#include "envio.hh"
#include "funciones.hh"

/***************************************************************************/

// Variables globales
Lista<Personaje*> *listaClientes;
Lista<Envio*> *listaEnvios;
ConexionServidor *conexion;
int mundoInf, mundoSup, castilInf, castilSup, casaInf, casaSup;
int sockActivo, turno;

/***************************************************************************/

// Definici�n de funciones para las hebras
int enviaCliente (void *);

/***************************************************************************/

int main ()
{
    Personaje *unPersonaje;
    long semilla;
    int port, sock, posx, posy, esp;
    int fue, con, tam, inte, des, pg, ene, ham, sed, mh1, mh2, mmr, nturnos;
    int equ3, tamanoClientes;

    // Inicializaci�n de la semilla aleatoria
    semilla = time (NULL);
    srand (semilla);

    // Copia de los ficheros del mundo modificables
    copiaFichero ("./mundo/objetos.dat", "./objetos.dat");

    // Obtenci�n del tama�o del mundo
    obtieneTamMundo (&mundoInf, &mundoSup, &castilInf, &castilSup, &casaInf, 
		     &casaSup);

    // Reserva de memoria para la lista de clientes conectados 
    listaClientes = new Lista<Personaje*> ();
    if (listaClientes == NULL)
    {
	fprintf (stderr, "servidor.cc: ");
	fprintf (stderr, "Memoria insuficiente para listaClientes\n");
	exit (-1);
    }

    // Reserva de memoria para la lista de envios de los clientes 
    listaEnvios = new Lista<Envio*> ();
    if (listaEnvios == NULL)
    {
	fprintf (stderr, "servidor.cc: ");
	fprintf (stderr, "Memoria insuficiente para listaEnvios\n");
	exit (-1);
    }

    // Creaci�n de la conexi�n del servidor
    conexion = new ConexionServidor (AF_INET, SOCK_STREAM, 0);

    // Conversi�n del puerto
    port = htons (50007);

    // Asignaci�n de la conexi�n del servidor
    conexion->asignaConexion (AF_INET, INADDR_ANY, port);

    // Apertura pasiva de la conexi�n del servidor en modo escucha
    conexion->abreConexion (1);

    // Bucle de transmisi�n con los clientes
    while (1)
    {   	
	// Obtenci�n del tama�o de la lista de clientes	
	tamanoClientes = listaClientes->obtieneTamano ();

	// Si no hay clientes conectados 
	if (tamanoClientes == 0)
	{
	    // Inicializaci�n de par�metros
	    sockActivo = -1;
	    turno = 0;
	}

	// Aceptaci�n del nuevo cliente
	sock = conexion->aceptaCliente ();

	// Si se acepta el cliente
	if (sock != -1)
	{
	    // Creaci�n de un nuevo personaje
	    unPersonaje = new Personaje ();
	    
	    // Asignaci�n del socket del cliente
	    unPersonaje->reAsignaAtributo ("sock", sock);

	    // Generaci�n de una posici�n (x,y) aleatoria no coincidente
	    obtienePosicion (mundoInf + 6, mundoSup - 6, mundoInf + 6, 
			     mundoSup - 6, &posx, &posy, listaClientes);

	    // Asignaci�n de la posici�n del personaje
	    unPersonaje->reAsignaAtributo ("posx", posx);
	    unPersonaje->reAsignaAtributo ("posy", posy);

	    // Recepci�n de la especie del personaje
	    esp = recibeEnteroDeCliente (conexion, sock);
	    
	    // Asignaci�n de la especie del personaje		
	    unPersonaje->reAsignaAtributo ("esp", esp);

	    // Inicializaci�n de los atributos de rol seg�n la especie
	    if (esp == 0) // Humano
	    {
		fue = tiraDado (3, 6);
		con = tiraDado (3, 6);
		tam = tiraDado (2, 6) + 6;
		inte = tiraDado (2, 6) + 6;
		des = tiraDado (3, 6);
		equ3 = 50;
	    }

	    else if (esp == 1) // Hobbit
	    {
		fue = tiraDado (2, 6);
		con = tiraDado (2, 6) + 12;
		tam = tiraDado (2, 3);
		inte = tiraDado (2, 6) + 6;
		des = tiraDado (2, 6) + 10;
		equ3 = 50;
	    }
	    
	    else if (esp == 2) // Elfo
	    {
		fue = tiraDado (2, 6) + 2;
		con = tiraDado (3, 6);
		tam = tiraDado (2, 6) + 8;
		inte = tiraDado (3, 6) + 6;
		des = tiraDado (3, 6) + 3;
		equ3 = 50;
	    }
	    
	    else if (esp == 3) // Gigante
	    {
		fue = tiraDado (3, 6) + 6;
		con = tiraDado (2, 6) + 6;
		tam = tiraDado (3, 6) + 6;
		inte = tiraDado (3, 6);
		des = tiraDado (3, 6);
		equ3 = 50;
	    }
	    
	    else // Mono
	    {
		fue = tiraDado (2, 6);
		con = tiraDado (2, 6);
		tam = tiraDado (2, 3);
		inte = 0;
		des = tiraDado (3, 6) + 10;
		equ3 = 0;
	    }
	    
	    // Inicializaci�n de los atributos gen�ricos
	    pg = int (round ((con + tam ) / 2.0));
	    ene = fue + con;
	    ham = con + tam;
	    sed = con + tam;
	    mh1 = 10 + ajustaMH ('P', des) + ajustaMH ('N', tam);
	    mh2 = 25 + ajustaMH ('P', inte) + ajustaMH ('S', con);	  
	    mmr = ajustaMMR (tam, des);
	    nturnos = ajustaNturnos (mmr);

	    // Asignaci�n de los atributos de rol al personaje
	    unPersonaje->reAsignaAtributo ("fue", fue);
	    unPersonaje->reAsignaAtributo ("con", con);
	    unPersonaje->reAsignaAtributo ("tam", tam);
	    unPersonaje->reAsignaAtributo ("inte", inte);
	    unPersonaje->reAsignaAtributo ("des", des);
	    unPersonaje->reAsignaAtributo ("pg", pg);
	    unPersonaje->reAsignaAtributo ("ene", ene);
	    unPersonaje->reAsignaAtributo ("ham", ham);
	    unPersonaje->reAsignaAtributo ("sed", sed);
	    unPersonaje->reAsignaAtributo ("maxpg", pg);
	    unPersonaje->reAsignaAtributo ("maxene", ene);
	    unPersonaje->reAsignaAtributo ("maxham", ham);
	    unPersonaje->reAsignaAtributo ("maxsed", sed);		
	    unPersonaje->reAsignaAtributo ("mh1", mh1);
	    unPersonaje->reAsignaAtributo ("mh2", mh2);
	    unPersonaje->reAsignaAtributo ("mmr", mmr);
	    unPersonaje->reAsignaAtributo ("estu", 0);
	    unPersonaje->reAsignaAtributo ("entr", 0);
	    unPersonaje->reAsignaAtributo ("obj", 0);
	    unPersonaje->reAsignaAtributo ("nturnos", nturnos);
	    unPersonaje->reAsignaEqu (3, equ3);

	    /***************************************************************** 
	                             DEMO
            /*****************************************************************/

	    // Coordenadas (-5, 14) Misiones
	    // Coordenadas (15, -48) Biblioteca
	    // Coordenadas (25, -8) Tienda de Espadas
/**
	    unPersonaje->reAsignaAtributo ("posx", -5);
	    unPersonaje->reAsignaAtributo ("posy", 14);

	    if (esp != 4)
	    {
		unPersonaje->reAsignaEqu (5, 1);
		unPersonaje->reAsignaEqu (4, 1);
		unPersonaje->reAsignaEqu (3, 0);
	    }
/**/
	    /*****************************************************************/

	    // Inserci�n del nuevo cliente en la lista de clientes conectados
	    listaClientes->insertaElemento (unPersonaje);	    

	    // Actualizaci�n del turno
	    listaClientes = ordenaClientes (listaClientes);
	    turno = 0;
	    sockActivo = obtieneClienteActivo (listaClientes, turno);

	    // Inserci�n del nuevo elemento en la lista de envios
	    insertaEnvio (listaEnvios, sock);

	    // Actualizaci�n a 1 de todos los env�os
	    activaEnvios (listaEnvios, 1);
	    
	    // Actualizaci�n del flag de env�o del nuevo cliente a 2
	    reAsignaEnvio (listaEnvios, sock, 2);

	    // Hebra que interacciona con el cliente 
	    SDL_CreateThread (enviaCliente, (void *) &sock);
	}
    }

    return 0;
}

/***************************************************************************/

int enviaCliente (void *valor)
{
    Lista<Edificio*> *listaEdificios;
    Lista<Objeto*> *listaObjetos;
    Lista<Personaje*> *listaP;
    Lista<Casilla*> *listaCasillas;
    Lista<Elemento*> *listaElementos;
    Edificio *unEdificio;
    Objeto *unObjeto;
    Personaje *unPersonaje;
    Casilla *unaCasilla;
    Elemento *unElemento;
    SDL_mutex *mutex;
    long ini, fin, tiempo;
    int tamanoClientes, tamanoEdificios, tamanoObjetos, tamanoP;
    int tamanoCasillas, tamanoElementos, tamanoEqu, nAtributos, atributo;
    int sock, sock2, posx, posy, oldx, oldy, cursorx, cursory, x, y;
    int xinf, xsup, yinf, ysup, inf, sup, edif, pg, id, tipo, llave, entrada; 
    int env, terminaHebra, accion, indice, indiceE, indiceO, indiceP, turnoP;
    int esp, visible, exito, temporizador;
    int nturnos, contadorTurno;

    // Obtenci�n del cliente
    sock = *((int *) valor);

    // Obtenci�n del �ndice del cliente
    indice = obtieneIndice (listaClientes, sock);

    // Obtenci�n del cliente
    unPersonaje = listaClientes->obtieneElemento (indice);

    // Obtenci�n de las coordenadas (x,y) del cliente 
    posx = unPersonaje->obtieneAtributo ("posx");
    posy = unPersonaje->obtieneAtributo ("posy");
    
    // Inicializaci�n de la posici�n del cursor
    cursorx = posx;
    cursory = posy;

    // Inicializaci�n de las coordenadas antiguas
    oldx = posx;
    oldy = posy;

    // Env�o del tama�o del mundo
    enviaEnteroACliente (conexion, sock, mundoInf);
    enviaEnteroACliente (conexion, sock, mundoSup);
    enviaEnteroACliente (conexion, sock, castilInf);
    enviaEnteroACliente (conexion, sock, castilSup);
    enviaEnteroACliente (conexion, sock, casaInf);
    enviaEnteroACliente (conexion, sock, casaSup);

    // Inicializaci�n del turno del cliente
    turnoP = 0;

    // Inicializaci�n del contador de turnos del cliente
    contadorTurno = 0;

    // Inicializaci�n del flag de parada de la hebra
    terminaHebra = 0;

    // Bucle de la hebra
    while (terminaHebra == 0)
    {
	// Obtenci�n del �ndice del cliente
	indice = obtieneIndice (listaClientes, sock);

	// Si existe el cliente
	if (indice != -1)
	{	
	    // Obtenci�n del cliente
	    unPersonaje = listaClientes->obtieneElemento (indice);

	    // Obtenci�n de las coordenadas (x,y) del cliente 
	    posx = unPersonaje->obtieneAtributo ("posx");
	    posy = unPersonaje->obtieneAtributo ("posy");

	    // Obtenci�n del edificio donde se encuentra el cliente
	    edif = unPersonaje->obtieneAtributo ("edif");

	    // Obtenci�n de los pg del cliente
	    pg = unPersonaje->obtieneAtributo ("pg");
	    
	    // Si el cliente no tiene vida
	    if (pg <= 0)
	    {		
		// Env�o del flag de env�o (1)
		enviaEnteroACliente (conexion, sock, 1);

		// Env�o del turno del cliente
		enviaEnteroACliente (conexion, sock, sockActivo);

		// Env�o del socket de desconexi�n (-1)
		enviaEnteroACliente (conexion, sock, -1);

		// Actualizaci�n de la acci�n
		accion = -1;

		// Retardo
		sleep (1);
	    }
	    
	    else
	    {		
		// Obtenci�n del flag de env�o
		env = obtieneEnvio (listaEnvios, sock);
		
		// Env�o del flag de env�o
		enviaEnteroACliente (conexion, sock, env);

		// Env�o del turno del cliente
		enviaEnteroACliente (conexion, sock, sockActivo);
		
		// Si el cliente est� activo para enviar
		if (env > 0)
		{
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();

		    // Actualizaci�n del flag de env�o del cliente a 0
		    reAsignaEnvio (listaEnvios, sock, 0);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		

		    // Env�o del socket del cliente
		    enviaEnteroACliente (conexion, sock, sock);
		    
		    // Env�o de la posici�n del cursor
		    enviaEnteroACliente (conexion, sock, cursorx);
		    enviaEnteroACliente (conexion, sock, cursory);

		    // Si el cliente est� en el exterior
		    if (edif == -1)
		    {
			// Obtenci�n del radio de visi�n del cliente
			xinf = posx - 8;
			xsup = posx + 8;
			yinf = posy - 8;
			ysup = posy + 8;
		    }
	    
		    // Si el cliente no est� en el exterior
		    else	    	
		    {
			// Obtenci�n del radio de visi�n del cliente
			xinf = posx - 20;
			xsup = posx + 20;
			yinf = posy - 20;
			ysup = posy + 20;			
		    }
		    
		    /* Carga de los objetos del mundo que est�n dentro del 
		       radio */
		    listaObjetos = cargaObjetos (xinf, xsup, yinf, ysup, edif);
		    tamanoObjetos = listaObjetos->obtieneTamano ();
		
		    /* Carga de los personajes del mundo que est�n dentro del 
		       radio */
		    listaP = cargaPersonajes (xinf, xsup, yinf, ysup, 
					      listaClientes, edif);
		    tamanoP = listaP->obtieneTamano ();
	    
		    // Ordenaci�n de las listas de personajes y objetos
		    listaElementos = ordenaListas (listaP, listaObjetos);
		    tamanoElementos = listaElementos->obtieneTamano ();

		    // Env�o del tama�o de la lista de objetos
		    enviaEnteroACliente (conexion, sock, tamanoObjetos);
		    
		    // Env�o de cada uno de los objetos de la lista
		    for (int i = 0; i < tamanoObjetos; i++)
		    {
			// Obtenci�n del objeto
			unObjeto = listaObjetos->obtieneElemento (i);
		    
			// Obtenci�n del n�mero de atributos de cada objeto
			nAtributos = unObjeto->obtieneNAtributos ();
		    
			// Env�o de cada uno de los atributos del objeto
			for (int j = 1; j <= nAtributos; j++)
			{
			    // Obtenci�n del atributo
			    atributo = unObjeto->obtieneAtributo (j); 
		
			    // Env�o del atributo
			    enviaEnteroACliente (conexion, sock, atributo);
			}
		    }	    

		    // Env�o del tama�o de la lista de personajes
		    enviaEnteroACliente (conexion, sock, tamanoP);

		    // Env�o de cada uno de los personajes de la lista 
		    for (int i = 0; i < tamanoP; i++)
		    {
			// Obtenci�n del personaje
			unPersonaje = listaP->obtieneElemento (i);
			
			// Obtenci�n del n�mero de atributos de cada personaje
			nAtributos = unPersonaje->obtieneNAtributos ();
			
			// Env�o de cada uno de los atributos del personaje 
			for (int j = 1; j <= nAtributos; j++)
			{
			    // Obtenci�n del atributo
			    atributo = unPersonaje->obtieneAtributo (j);
			    
			    // Env�o del atributo
			    enviaEnteroACliente (conexion, sock, atributo);
			}
						
			// Obtenci�n del tama�o del equipo de cada personaje
			tamanoEqu = unPersonaje->obtieneTamEqu ();
			
			// Env�o de cada uno de los elementos del equipo  
			for (int j = 0; j < tamanoEqu; j++)
			{
			    // Obtenci�n del elemento del equipo
			    atributo = unPersonaje->obtieneEqu (j);
			    
			    // Env�o del elemento del equipo
			    enviaEnteroACliente (conexion, sock, atributo);
			}
		    }
	    	    
		    // Env�o del tama�o de la lista de elementos
		    enviaEnteroACliente (conexion, sock, tamanoElementos);
		    
		    // Env�o de cada uno de los elementos de la lista 
		    for (int i = 0; i < tamanoElementos; i++)
		    {
			// Obtenci�n del elemento
			unElemento = listaElementos->obtieneElemento (i);
			
			// Obtenci�n del n�mero de atributos de cada elemento
			nAtributos = unElemento->obtieneNAtributos ();
			
			// Env�o de cada uno de los atributos del elemento
			for (int j = 1; j <= nAtributos; j++)
			{
			    // Obtenci�n del atributo
			    atributo = unElemento->obtieneAtributo (j);
			    
			    // Env�o del atributo
			    enviaEnteroACliente (conexion, sock, atributo);
			}
		    }

		    // Si el envio engloba a todo el mundo
		    if (env == 2)
		    {
			/* Carga de los edificios del mundo que est�n 
			   dentro del radio */ 
			listaEdificios = cargaEdificios (xinf, xsup, yinf,
							 ysup);
			tamanoEdificios = listaEdificios->obtieneTamano ();
			
			/* Carga de las casillas del mundo que est�n 
			   dentro del radio */
			listaCasillas = cargaCasillas (xinf, xsup, yinf, 
						       ysup);
			tamanoCasillas = listaCasillas->obtieneTamano ();
						
			// Env�o del tama�o de la lista de edificios
			enviaEnteroACliente (conexion, sock, tamanoEdificios);

			// Env�o de cada uno de los edificios de la lista 
			for (int i = 0; i < tamanoEdificios; i++)
			{
			    // Obtenci�n del edificio
			    unEdificio = listaEdificios->obtieneElemento (i);
		    
			    /* Obtenci�n del n�mero de atributos de cada 
			       edificio */
			    nAtributos = unEdificio->obtieneNAtributos ();
		    
			    // Env�o de cada uno de los atributos del edificio 
			    for (int j = 1; j <= nAtributos; j++)
			    {
				// Obtenci�n del atributo
				atributo = unEdificio->obtieneAtributo (j); 
				
				// Env�o del atributo
				enviaEnteroACliente (conexion, sock, atributo);
			    }
			}
	    	    
			// Env�o del tama�o de la lista de casillas
			enviaEnteroACliente (conexion, sock, tamanoCasillas);
		    
			// Env�o de cada una de las casillas de la lista 
			for (int i = 0; i < tamanoCasillas; i++)
			{
			    // Obtenci�n de la casilla
			    unaCasilla = listaCasillas->obtieneElemento (i);
			
			    /* Obtenci�n del n�mero de atributos de cada 
			       casilla */
			    nAtributos = unaCasilla->obtieneNAtributos ();
			
			    // Env�o de cada uno de los atributos de la casilla
			    for (int j = 1; j <= nAtributos; j++)
			    {
				// Obtenci�n del atributo
				atributo = unaCasilla->obtieneAtributo (j);
				
				// Env�o del atributo
				enviaEnteroACliente (conexion, sock, atributo);
			    }
			}
		    }

		    // Inicializaci�n del temporizador
		    temporizador = 0;

		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Obtenci�n del cliente
		    unPersonaje = listaClientes->obtieneElemento (indice);

		    // Obtenci�n del n�mero de turnos del cliente
		    nturnos = unPersonaje->obtieneAtributo ("nturnos");
		}
	    }

	    // Recepci�n de la acci�n solicitada del cliente
	    accion = recibeEnteroDeCliente (conexion, sock);

	    // Si es el cliente activo
	    if (sock == sockActivo)
	    {
		// Si el temporizador est� a 0
		if (temporizador == 0)
		{
		    // Asignaci�n del temporizador a 1
		    temporizador = 1;

		    // Inicio del tiempo
		    ini = time (NULL);
		}

		// Medida de tiempo
		fin = time (NULL);

		// Obtenci�n del tiempo transcurrido
		tiempo = fin - ini;

		// Si el tiempo expira
		if (tiempo == 5)
		{
		    // Accion no determinada
		    accion = 0;

		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Inicio del temporizador
		    temporizador = 0;

		    // Si ya se han terminado los turnos del cliente
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;

			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo 
			    (listaClientes, turno);
		    }		
		}
	    }

	    // Si el cliente ha muerto se actualiza la acci�n a -1
	    if (pg <= 0)
		accion = -1;

	    // Si el cliente solicita desconectarse 
	    if (accion == -1)
	    {			    	
		// Creaci�n de un mutex
		mutex = SDL_CreateMutex ();

		// Desconexi�n del cliente
		conexion->desconectaCliente (sock);
		    
		// Obtenci�n del �ndice del cliente
		indice = obtieneIndice (listaClientes, sock);
		
		// Creaci�n de cofres con el equipo del cliente
		listaObjetos = creaCofres (listaClientes, indice);

		// Inserci�n de los nuevos cofres en el fichero de objetos
		insertaNuevosObjetos (listaObjetos, listaClientes, mundoInf, 
				      mundoSup, mundoInf, mundoSup);

		// Eliminaci�n del cliente en la lista
		listaClientes->eliminaElemento (indice);

		// Obtenci�n del tama�o de la lista de clientes
		tamanoClientes = listaClientes->obtieneTamano ();
		
		// Si el tama�o es mayor que 0
		if (tamanoClientes > 0)
		{
		    // Actualizaci�n del turno 
		    listaClientes = ordenaClientes (listaClientes);
		    turno = 0;
		    sockActivo = obtieneClienteActivo (listaClientes, turno);
		}

		// Eliminaci�n del cliente en la lista de env�os
		eliminaEnvio (listaEnvios, sock);
		    
		// Actualizaci�n a 1 de todos los env�os
		activaEnvios (listaEnvios, 1);
		    
		// Destrucci�n del mutex
		SDL_DestroyMutex (mutex);
		    
		// Actualizaci�n del flag de terminaci�n de la hebra
		terminaHebra = 1;
		    
		// Retardo
		sleep (1);
	    }
		
	    // Si el cliente solicita movimiento
	    else if (accion == 1)
	    {
		// Recepci�n de las coordenadas modificadas
		posx = recibeEnteroDeCliente (conexion, sock);
		posy = recibeEnteroDeCliente (conexion, sock);
		
		// Recepci�n del flag de entrada
		entrada = recibeEnteroDeCliente (conexion, sock);

		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Obtenci�n del cliente
		    unPersonaje = listaClientes->obtieneElemento (indice);

		    // Obtenci�n de la especie del cliente
		    esp = unPersonaje->obtieneAtributo ("esp");
		    
		    // Comprobaci�n de las nuevas coordenadas en edificios
		    indiceE = coincideEdificio(posx, posy, listaEdificios);
		    
		    // Comprobaci�n de las nuevas coordenadas en objetos
		    indiceO = coincideObjeto (posx, posy, listaObjetos);
		    
		    // Si coincide con alg�n objeto
		    if (indiceO != -1)
		    {
			// Obtenci�n del objeto
			unObjeto = listaObjetos->obtieneElemento(indiceO);
			
			// Obtenci�n del tipo del objeto
			tipo = unObjeto->obtieneAtributo ("tipo");
			
			// Comprobaci�n del tipo
			if ((tipo < 4) || (tipo == 17) || (tipo == 22) ||
			    ((tipo >= 27) && (tipo < 34)) || 
			    ((tipo >= 35) && (tipo < 39)))
			    
			    indiceO = -1;
			
			if (tipo == 7)
			{
			    // Obtenci�n de las coordenadas del objeto
			    x = unObjeto->obtieneAtributo ("posx");
			    y = unObjeto->obtieneAtributo ("posy");
			    
			    // Si la posici�n coincide con el centro
			    if ((posx == x + 1) && (posy == y))
				indiceO = -1;
			}
		    }
		    
		    // Comprobaci�n de las nuevas coordenadas en personajes
		    indiceP = coincidePersonaje (posx, posy, listaClientes);
		    
		    // Se excluye el cliente activo
		    if (indiceP == indice)
			indiceP = -1;
		    
		    // Comprobaci�n global
		    if ((indiceO == -1) && (indiceP == -1))		
		    {
			// Si la nueva posici�n es la entrada a un edificio
			if ((indiceE != -1) && (entrada == 1) && 
			    (edif == -1) && (esp != 4))
			{
			    // Obtenci�n del edificio
			    unEdificio = listaEdificios->
				obtieneElemento (indiceE);
			    
			    // Obtenci�n del identificador del edificio
			    id = unEdificio->obtieneAtributo ("id");
				
			    // Obtenci�n del tipo de edificio
			    tipo = unEdificio->obtieneAtributo ("tipo");
			    
			    // Si es un castillo
			    if (tipo == 0)
			    {
				// Obtenci�n de la llave del cliente
				llave = unPersonaje->obtieneEqu (4);
				
				// Si tiene la llave
				if (llave == 1)
				{
				    // Actualizaci�n del edificio 
				    unPersonaje->reAsignaAtributo ("edif", id);
				    
				    // Se guardan las coordenadas
				    oldx = posx;
				    oldy = posy - 1;
					
				    // Actualizaci�n de las coordenadas
				    unPersonaje->reAsignaAtributo ("posx", 0);
				    unPersonaje->
					reAsignaAtributo ("posy", castilInf);

				    // Actualizaci�n del cursor
				    cursorx = 0;
				    cursory = castilInf;

				    // Creaci�n de un mutex
				    mutex = SDL_CreateMutex ();
				    
				    // Inserci�n del cliente en la lista 
				    listaClientes->
					reAsignaElemento (indice, unPersonaje);

				    // Actualizaci�n a 1 de todos los env�os
				    activaEnvios (listaEnvios, 1);
				    
				    // Incremento del contador de turnos
				    contadorTurno++;

				    // Si ya se han terminado los turnos
				    if (contadorTurno == nturnos)
				    {
					// Inicializaci�n del contador turnos
					contadorTurno = 0;
					
					// Incremento del turno
					turno++;
					sockActivo = obtieneClienteActivo 
					    (listaClientes, turno);
				    }

				    // Incremento del turno del cliente
				    turnoP++;

				    // Decremento del cliente
				    decrementaPersonaje (listaClientes, turnoP,
							 sock);

				    // Destrucci�n del mutex
				    SDL_DestroyMutex (mutex);
				}
			    }
			    
			    // Si no es un castillo
			    else
			    {
				// Actualizaci�n del edificio 
				unPersonaje->reAsignaAtributo ("edif", id);
				
				// Se guardan las coordenadas
				oldx = posx;
				oldy = posy - 1;
				
				// Actualizaci�n de las coordenadas
				unPersonaje->reAsignaAtributo ("posx", 0);
				unPersonaje->reAsignaAtributo("posy", casaInf);
				
				// Actualizaci�n de la posici�n del cursor
				cursorx = 0;
				cursory = casaInf;
				
				// Creaci�n de un mutex
				mutex = SDL_CreateMutex ();
				
				// Inserci�n del cliente en la lista 
				listaClientes->
				    reAsignaElemento (indice, unPersonaje);
				
				// Actualizaci�n a 1 de todos los env�os
				activaEnvios (listaEnvios, 1);

				// Incremento del contador de turnos
				contadorTurno++;

				// Si ya se han terminado los turnos
				if (contadorTurno == nturnos)
				{
				    // Inicializaci�n del contador de turnos
				    contadorTurno = 0;

				    // Incremento del turno
				    turno++;
				    sockActivo = obtieneClienteActivo 
					(listaClientes, turno);
				}

				// Incremento del turno del cliente
				turnoP++;

				// Decremento del cliente
				decrementaPersonaje (listaClientes, turnoP, 
						     sock);
				
				// Destrucci�n del mutex
				SDL_DestroyMutex (mutex);
			    }
			}
			
			// Si la nueva posici�n es dentro de un edificio
			else if (edif != -1)
			{
			    if ((edif % 6) == 0)
			    {
				inf = castilInf;
				sup = castilSup;
			    }
			    
			    else
			    {
				inf = casaInf;
				sup = casaSup;
			    }
			    
			    // Si la nueva posici�n es salida de edificio
			    if ((posx == 0) && (posy == inf - 1))
			    {
				// Creaci�n de un mutex
				mutex = SDL_CreateMutex ();
				
				// Si el edificio es un castillo
				if ((edif % 6) == 0)		    
				{
				    // Inicializaci�n de trampas y prisioneros
				    iniciaObjetos (listaObjetos, edif);

				    // Actualizaci�n del fichero de objetos
				    actualizaObjetos (listaObjetos);
				}

				// Actualizaci�n de las coordenadas
				unPersonaje->reAsignaAtributo ("posx", oldx);
				unPersonaje->reAsignaAtributo ("posy", oldy);
				
				// Actualizaci�n del edificio
				unPersonaje->reAsignaAtributo ("edif", -1);
				
				// Actualizaci�n de la posici�n del cursor
				cursorx = oldx;
				cursory = oldy;
								
				// Inserci�n del cliente en la lista 
				listaClientes->
				    reAsignaElemento (indice, unPersonaje);
				
				// Actualizaci�n a 1 de todos los env�os
				activaEnvios (listaEnvios, 1);

				// Actualizaci�n del env�o del cliente a 2
				reAsignaEnvio (listaEnvios, sock, 2); 

				// Incremento del contador de turnos
				contadorTurno++;

				// Si ya se han terminado los turnos
				if (contadorTurno == nturnos)
				{
				    // Inicializaci�n del contador de turnos
				    contadorTurno = 0;

				    // Incremento del turno
				    turno++;
				    sockActivo = obtieneClienteActivo 
					(listaClientes, turno);
				}
				
				// Incremento del turno del cliente
				turnoP++;

				// Decremento del cliente
				decrementaPersonaje (listaClientes, turnoP, 
						     sock);

				// Destrucci�n del mutex
				SDL_DestroyMutex (mutex);
			    }
			    
			    // Si la nueva posici�n es dentro del recinto
			    else if ((posx >= inf) && (posx < sup))
				if ((posy >= inf) && (posy < sup))
				{
				    // Comprobaci�n de las trampas
				    indiceO = objetoTrampa (posx, posy, 
							    &visible, 
							    listaObjetos);
				    
				    // Creaci�n de un mutex
				    mutex = SDL_CreateMutex ();

				    // Inicializaci�n
				    exito = 0;

				    // Si hay una trampa
				    if (indiceO != -1)
				    {
					// Si es invisible
					if (visible == 0)
					{
					    // Tirada de percepci�n
					    exito = tiradaMH (listaClientes, 
							      indice, 2);

					    // Actualizaci�n a visible
					    objetoVisible (listaObjetos,
							   indiceO);
								    
					    // Actualizaci�n del fichero
					    actualizaObjetos(listaObjetos);
					    
					    // Si no hay exito
					    if (exito == 0)
					    
						// Decremento de pg del cliente
						decrementaPG (listaClientes, 
							      indice, 2);
					}

					// Si es visible
					else
					    // Decremento de pg del cliente
					    decrementaPG (listaClientes, 
							  indice, 2);
				    }

				    // Si no hay trampa o no hay exito
				    if ((indiceO == -1) or (exito == 0))
				    {
					// Actualizaci�n de las coordenadas 
					unPersonaje->
					    reAsignaAtributo ("posx", posx);

					unPersonaje->
					    reAsignaAtributo("posy", posy);
				    
					// Actualizaci�n del cursor
					cursorx = posx;
					cursory = posy;
				    				    
					// Inserci�n del cliente en la lista 
					listaClientes->reAsignaElemento
					    (indice, unPersonaje);
				    }

				    // Actualizaci�n a 1 de todos los env�os
				    activaEnvios (listaEnvios, 1);

				    // Incremento del contador de turnos
				    contadorTurno++;

				    // Si ya se han terminado los turnos
				    if (contadorTurno == nturnos)
				    {
					// Inicializaci�n del contador turnos
					contadorTurno = 0;

					// Incremento del turno
					turno++;
					sockActivo = obtieneClienteActivo 
					    (listaClientes, turno);
				    }

				    // Incremento del turno del cliente
				    turnoP++;
				    
				    // Decremento del cliente
				    decrementaPersonaje (listaClientes, turnoP,
							 sock);
				    
				    // Destrucci�n del mutex
				    SDL_DestroyMutex (mutex);
				}
			}
			
			// Si la nueva posici�n es en el mundo exterior
			else if ((indiceE == -1) && (edif == -1) && 
				 (posx >= mundoInf) && (posx < mundoSup) &&
				 (posy >= mundoInf) && (posy < mundoSup))
			{
			    // Actualizaci�n de las nuevas coordenadas  
			    unPersonaje->reAsignaAtributo ("posx", posx);
			    unPersonaje->reAsignaAtributo ("posy", posy);

			    // Actualizaci�n de la posici�n del cursor
			    cursorx = posx;
			    cursory = posy;
			    
			    // Creaci�n de un mutex
			    mutex = SDL_CreateMutex ();
			    
			    // Inserci�n del cliente en la lista 
			    listaClientes->
				reAsignaElemento (indice, unPersonaje);
			    
			    // Actualizaci�n a 1 de todos los env�os
			    activaEnvios (listaEnvios, 1);

			    // Actualizaci�n del env�o del cliente a 2
			    reAsignaEnvio (listaEnvios, sock, 2); 

			    // Incremento del contador de turnos
			    contadorTurno++;

			    // Si ya se han terminado los turnos
			    if (contadorTurno == nturnos)
			    {
				// Inicializaci�n del contador de turnos
				contadorTurno = 0;

				// Incremento del turno
				turno++;
				sockActivo = obtieneClienteActivo 
				    (listaClientes, turno);
			    }

			    // Incremento del turno del cliente
			    turnoP++;

			    // Decremento del cliente
			    decrementaPersonaje (listaClientes, turnoP, sock);
			    
			    // Destrucci�n del mutex
			    SDL_DestroyMutex (mutex);
			}		    
		    }
		}
	    }
	    
	    // Si el cliente solicita mover el cursor
	    else if (accion == 2)
	    {
		// Recepci�n de las coordenadas del cursor
		cursorx = recibeEnteroDeCliente (conexion, sock);
		cursory = recibeEnteroDeCliente (conexion, sock);

		// Creaci�n de un mutex
		mutex = SDL_CreateMutex ();
		
		// Actualizaci�n del flag de env�o del cliente a 1
		reAsignaEnvio (listaEnvios, sock, 1);
		
		// Destrucci�n del mutex
		SDL_DestroyMutex (mutex);
	    }
	    
	    // Si el cliente solicita pasar turno
	    else if (accion == 3)
	    {		
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();

		    // Incremento de la energ�a del cliente
		    incrementaEne (listaClientes, indice);

		    // Inicializaci�n del contador de turnos
		    contadorTurno = 0;
		    
		    // Incremento del turno
		    turno++;
		    sockActivo = obtieneClienteActivo(listaClientes,turno);
		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);
		    
		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);
		    
		    // Incremento del turno del cliente
		    turnoP++;
		}
	    }

	    // Si el cliente solicita atacar
	    else if (accion == 4)
	    {
		// Recepci�n de las coordenadas del cursor
		cursorx = recibeEnteroDeCliente (conexion, sock);
		cursory = recibeEnteroDeCliente (conexion, sock);

		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Obtenci�n del �ndice del personaje atacado
		    indiceP = coincidePersonaje(cursorx,cursory,listaClientes);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
		
		    // Ataque al personaje coincidente
		    atacaPersonaje (listaClientes, indice, indiceP);

		    // Obtenci�n del socket del personaje atacado
		    unPersonaje = listaClientes->obtieneElemento (indiceP);
		    sock2 = unPersonaje->obtieneAtributo ("sock");
			    
		    // Actualizaci�n del flag de env�o del personaje
		    reAsignaEnvio (listaEnvios, sock2, 1);

		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos del cliente
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
		    
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
		
		    // Incremento del turno del cliente
		    turnoP++;				
		    
		    // Decremento del cliente
		    decrementaPersonaje (listaClientes, turnoP, sock);

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);
		}
	    }

	    // Si el cliente solicita robar
	    else if (accion == 5)
	    {
		// Recepci�n de las coordenadas del cursor
		cursorx = recibeEnteroDeCliente (conexion, sock);
		cursory = recibeEnteroDeCliente (conexion, sock);

		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Obtenci�n del �ndice del personaje atacado
		    indiceP = coincidePersonaje(cursorx,cursory,listaClientes);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
		 
		    // Robo al personaje coincidente
		    exito = enfrentaMH (listaClientes, indice, indiceP);
		    
		    // Si tiene �xito
		    if (exito == 1)
		    {
			// Incremento del equipo del cliente
			incrementaEqu (listaClientes, indice, indiceP);

			// Obtenci�n del socket del personaje del robo
			unPersonaje = listaClientes->obtieneElemento (indiceP);
			sock2 = unPersonaje->obtieneAtributo ("sock");

			// Actualizaci�n del flag de env�o del personaje
			reAsignaEnvio (listaEnvios, sock2, 1);
		    }   

		    // Incremento del contador de turnos
		    contadorTurno++;
		    
		    // Si ya se han terminado los turnos del cliente
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
				
		    // Incremento del turno del cliente
		    turnoP++;				

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);
		}
	    }

	    // Si el cliente solicita comer setas
	    else if (accion == 6)
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Incremento del hambre del cliente
		    incrementaHam (listaClientes, indice, 1);
				
		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }

		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);
		}
	    }

	    // Si el cliente solicita comer miel
	    else if (accion == 7)
	    {
		// Recepci�n de las coordenadas del cursor
		cursorx = recibeEnteroDeCliente (conexion, sock);
		cursory = recibeEnteroDeCliente (conexion, sock);

		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Obtenci�n del �ndice del objeto
		    indiceO = coincideObjeto (cursorx, cursory, listaObjetos);

		    // Obtenci�n del objeto
		    unObjeto = listaObjetos->obtieneElemento (indiceO);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Incremento del hambre del cliente
		    incrementaHam (listaClientes, indice, 2);
				
		    // Actualizaci�n a 1 de todos los env�os
		    activaEnvios (listaEnvios, 1);
				
		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;

			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
				
		    // Eliminaci�n del objeto miel
		    unObjeto->reAsignaAtributo ("tipo", -1);
		    listaObjetos->reAsignaElemento (indiceO, unObjeto);
				
		    // Actualizaci�n del fichero de objetos
		    actualizaObjetos (listaObjetos);
		    				
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);
		}
	    }

	    // Si el cliente solicita abrir cofre
	    else if (accion == 8)
	    {
		// Recepci�n de las coordenadas del cursor
		cursorx = recibeEnteroDeCliente (conexion, sock);
		cursory = recibeEnteroDeCliente (conexion, sock);

		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Obtenci�n del personaje
		    unPersonaje = listaClientes->obtieneElemento (indice);
		    
		    // Obtenci�n de la especie del cliente
		    esp = unPersonaje->obtieneAtributo ("esp");

		    // Si la especie no es mono
		    if (esp != 4)
		    {
			// Obtenci�n del �ndice del objeto
			indiceO = coincideObjeto(cursorx,cursory,listaObjetos);

			// Creaci�n de un mutex
			mutex = SDL_CreateMutex ();
			 
			// Incremento del equipo del cliente
			incrementaEqu (listaClientes, indice, listaObjetos, 
				       indiceO);

			// Actualizaci�n del fichero de objetos
			actualizaObjetos (listaObjetos);
				
			// Actualizaci�n a 1 de todos los env�os
			activaEnvios (listaEnvios, 1);
				
			// Incremento del contador de turnos
			contadorTurno++;

			// Si ya se han terminado los turnos
			if (contadorTurno == nturnos)
			{
			    // Inicializaci�n del contador de turnos
			    contadorTurno = 0;
			    
			    // Incremento del turno
			    turno++;
			    sockActivo = obtieneClienteActivo 
				(listaClientes, turno);
			}

			// Incremento del turno del cliente
			turnoP++;				

			// Decremento del cliente
			decrementaPersonaje (listaClientes, turnoP, sock);

			// Actualizaci�n de la posici�n del cursor
			cursorx = posx;
			cursory = posy;
		    		    		    
			// Destrucci�n del mutex
			SDL_DestroyMutex (mutex);			
		    }
		}
	    }

	    // Si el cliente solicita aceptar misi�n
	    else if (accion == 9)
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Obtenci�n del personaje
		    unPersonaje = listaClientes->obtieneElemento (indice);

		    // Obtenci�n de la especie del cliente
		    esp = unPersonaje->obtieneAtributo ("esp");

		    // Si la especie no es mono
		    if (esp != 4)
		    {
			// Creaci�n de un mutex
			mutex = SDL_CreateMutex ();

			// Incremento del objetivo del cliente
			incrementaObj (listaClientes, indice);
		    
			// Incremento del contador de turnos
			contadorTurno++;
		    
			// Si ya se han terminado los turnos
			if (contadorTurno == nturnos)
			{
			    // Inicializaci�n del contador de turnos
			    contadorTurno = 0;
			    
			    // Incremento del turno
			    turno++;
			    sockActivo = obtieneClienteActivo 
				(listaClientes,turno);
			}
				
			// Incremento del turno del cliente
			turnoP++;

			// Actualizaci�n de la posici�n del cursor
			cursorx = posx;
			cursory = posy;
		    		    		    
			// Actualizaci�n del flag de env�o del cliente a 1
			reAsignaEnvio (listaEnvios, sock, 1);

			// Destrucci�n del mutex
			SDL_DestroyMutex (mutex);
		    }
		}
	    }

	    // Si el cliente solicita liberar prisionero
	    else if (accion == 10)
	    {
		// Recepci�n de las coordenadas del cursor
		cursorx = recibeEnteroDeCliente (conexion, sock);
		cursory = recibeEnteroDeCliente (conexion, sock);

		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Obtenci�n del �ndice del objeto
		    indiceO = coincideObjeto (cursorx, cursory, listaObjetos);
		    
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Liberaci�n del prisionero
		    liberaPrisionero (listaClientes, indice, listaObjetos, 
				      indiceO);

		    // Actualizaci�n del fichero de objetos
		    actualizaObjetos (listaObjetos);
		    
		    // Actualizaci�n a 1 de todos los env�os
		    activaEnvios (listaEnvios, 1);
		    
		    // Incremento del contador de turnos
		    contadorTurno++;
		    
		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
								
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);			
		}
	    }

	    // Si el cliente solicita estudiar
	    else if (accion == 11)
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Incremento de las habilidades del cliente
		    incrementaMH (listaClientes, indice);
				
		    // Incremento del contador de turnos
		    contadorTurno++;
				
		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }

		    // Incremento del turno del cliente
		    turnoP++;				
		    
		    // Decremento del cliente
		    decrementaPersonaje (listaClientes, turnoP, sock);

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		    
		}
	    }

	    // Si el cliente solicita descansar
	    else if (accion == 12)
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();

		    // Incremento de la salud del cliente
		    incrementaSalud (listaClientes, indice, 1);
				
		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
								
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		    
		}
	    }

	    // Si el cliente solicita comprar un arma
	    else if ((accion >= 13) && (accion < 17))
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Obtenci�n del tipo de arma
		    tipo = 27 + (accion - 13);
		    
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Compra del objeto 
		    compraObjeto (listaClientes, indice, tipo);
				
		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Actualizaci�n del turno
			listaClientes = ordenaClientes (listaClientes);
			turno = 0;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
				
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		    
		}
	    }			  

	    // Si el cliente solicita comprar un escudo
	    else if ((accion >= 17) && (accion < 20))
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Obtenci�n del tipo de escudo
		    tipo = 31 + (accion - 17);
		    
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Compra del objeto 
		    compraObjeto (listaClientes, indice, tipo);
				
		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Actualizaci�n del turno
			listaClientes = ordenaClientes (listaClientes);
			turno = 0;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
				
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		    
		}
	    }			  

	    // Si el cliente solicita comprar una armadura
	    else if ((accion >= 20) && (accion < 24))
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		    
		    // Obtenci�n del tipo de armadura
		    tipo = 35 + (accion - 20);
		    
		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
				
		    // Compra del objeto 
		    compraObjeto (listaClientes, indice, tipo);
				
		    // Incremento del contador de turnos
		    contadorTurno++;

		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
				
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		    
		}
	    }			  

	    // Si el cliente solicita beber agua
	    else if (accion == 24)
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();
		    
		    // Incremento de la sed del cliente
		    incrementaSed (listaClientes, indice);
		    
		    // Incremento del contador de turnos
		    contadorTurno++;
		    
		    // Si ya se han terminado los turnos
		    if (contadorTurno == nturnos)
		    {
			// Inicializaci�n del contador de turnos
			contadorTurno = 0;
			
			// Incremento del turno
			turno++;
			sockActivo = obtieneClienteActivo(listaClientes,turno);
		    }
						    
		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);
		    
		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);
		}
	    }

	    // Si el cliente solicita finalizar misi�n
	    else if (accion == 25)
	    {
		// Si es el cliente activo
		if (sock == sockActivo)
		{
		    // Obtenci�n del �ndice del cliente
		    indice = obtieneIndice (listaClientes, sock);
		  
		    // Obtenci�n del personaje
		    unPersonaje = listaClientes->obtieneElemento (indice);

		    // Inicializaci�n del objetivo a 0
		    unPersonaje->reAsignaAtributo ("obj", 0);

		    // Creaci�n de un mutex
		    mutex = SDL_CreateMutex ();

		    // Actualizaci�n del cliente
		    listaClientes->reAsignaElemento (indice, unPersonaje);

		    // Incremento de las caracteristicas 
		    incrementaCaracteristicas (listaClientes, indice);

		    // Inicializaci�n del contador de turnos
		    contadorTurno = 0;
		    
		    // Actualizaci�n del turno
		    listaClientes = ordenaClientes (listaClientes);
		    turno = 0;
		    sockActivo = obtieneClienteActivo (listaClientes, turno);

		    // Incremento del turno del cliente
		    turnoP++;

		    // Actualizaci�n de la posici�n del cursor
		    cursorx = posx;
		    cursory = posy;
		    		    		    
		    // Actualizaci�n del flag de env�o del cliente a 1
		    reAsignaEnvio (listaEnvios, sock, 1);

		    // Destrucci�n del mutex
		    SDL_DestroyMutex (mutex);		    
		}
	    }

	    // Si el cliente solicita actuar con los men�s
	    else if (accion == 26)
	    {
		// Creaci�n de un mutex
		mutex = SDL_CreateMutex ();
		
		// Actualizaci�n del flag de env�o del cliente a 1
		reAsignaEnvio (listaEnvios, sock, 1);
		
		// Destrucci�n del mutex
		SDL_DestroyMutex (mutex);
	    }
	}
    }
    
    return 0;
}

/***************************************************************************/
    
