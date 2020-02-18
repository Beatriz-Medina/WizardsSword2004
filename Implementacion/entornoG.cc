
/***************************************************************************
                         entornoG.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <GL/glut.h>
#include <SDL_image.h>
#include <SDL.h>

#include "entornoG.hh"
#include "conexionCliente.hh"
#include "lista.cc"
#include "edificio.hh"
#include "objeto.hh"
#include "personaje.hh"
#include "casilla.hh"
#include "elemento.hh"
#include "textura.hh"
#include "funciones.hh"
#include "glf.hh"
 
#define RGB  3
#define RGBA 4

/***************************************************************************/

/* Constructor del objeto EntornoG que crea un entorno gr�fico con los 
   par�metros especificados e inicializa las variables del entornoG */
EntornoG::EntornoG (char *titulo, char *icono, int ancho, int alto, 
		    int servidorIP)
{
    int tamano;

    // Inicializaci�n de la ventana
    this->ventana = NULL;

    // Reserva de memoria del t�tulo de la ventana
    tamano = strlen (titulo);
    this->titulo = new char [tamano+1];
    if (this->titulo == NULL)
    {
	fprintf (stderr, "entornoG.cc::EntornoG ");
	fprintf (stderr, "(char*, char*, int, int): ");
	fprintf (stderr, "Memoria insuficiente para titulo\n");
	exit (-1);
    }

    // Asignaci�n del t�tulo de la ventana
    strcpy (this->titulo, titulo);

    // Reserva de memoria del nombre del icono de la ventana
    tamano = strlen (icono);
    this->icono = new char [tamano+1];
    if (this->icono == NULL)
    {
	fprintf (stderr, "entornoG.cc::EntornoG ");
	fprintf (stderr, "(char*, char*, int, int): ");
	fprintf (stderr, "Memoria insuficiente para icono\n");
	exit (-1);
    }

    // Asignaci�n del nombre del icono de la ventana
    strcpy (this->icono, icono);

    // Asignaci�n de la dimensi�n de la ventana
    this->ancho = ancho;
    this->alto = alto;

    // Inicializaci�n de la conexi�n del cliente
    this->conexion = NULL;

    // Inicializaci�n de la direcci�n IP del servidor
    this->servidorIP = servidorIP;

    // Inicializaci�n de las dimensiones del mundo
    this->mundoInf = this->mundoSup = 0;
    this->castilInf = this->castilSup = 0;
    this->casaInf = this->casaSup = 0;

    // Inicializaci�n de la lista de edificios
    this->listaEdificios = NULL;
    this->tamanoEdificios = 0;

    // Inicializaci�n de la lista de objetos
    this->listaObjetos = NULL;
    this->tamanoObjetos = 0;

    // Inicializaci�n de la lista de personajes
    this->listaP = NULL;
    this->tamanoP = 0;

    // Inicializaci�n de la lista de elementos
    this->listaElementos = NULL;
    this->tamanoElementos = 0;

    // Inicializaci�n de la lista de casillas
    this->listaCasillas = NULL;
    this->tamanoCasillas = 0;

    // Inicializaci�n de la lista de texturas
    this->listaTexturas = NULL;
    this->tamanoTexturas = 0;

    // Inicializaci�n de la posici�n (x,y) del personaje activo
    this->posx = 0;
    this->posy = 0;
    this->inix = 0;
    this->iniy = 0;

    // Inicializaci�n del edificio donde se encuentra el personaje activo
    this->edif = -1;

    // Inicializaci�n del estado del cursor
    this->cursorStatus = 0;

    // Inicializaci�n de la posici�n (x,y) del cursor
    this->cursorx = 0;
    this->cursory = 0;

    // Inicializaci�n del estado del cuadro de caracter�sticas
    this->caractStatus = 0;

    // Inicializaci�n del estado del men� de acciones
    this->menuAccStatus = 0;

    // Inicializaci�n de la posici�n de la acci�n del men�
    this->posAccion = 0;

    // Inicializaci�n del l�mite superior del men� de acciones
    this->topePosAccion = 0;

    // Inicializaci�n de la acci�n actual solicitada
    this->accionActual = -1;

    // Inicializaci�n del socket
    this->sock = -1;

    // Inicializaci�n del turno
    this->turno = -1;
}

/***************************************************************************/

// Destructor del objeto EntornoG
EntornoG::~EntornoG ()
{
    if (this->titulo != NULL)
    {
	delete [] this->titulo;
	this->titulo = NULL;
    }

    if (this->icono != NULL)
    {
	delete [] this->icono;
	this->icono = NULL;
    }
}

/***************************************************************************/

// M�todo que inicia el entorno gr�fico inicializando tanto OpenGL como SDL
void EntornoG::iniciaEntorno (void)
{
    this->SDL_init ();
    this->GL_init ();
}

/***************************************************************************/

// M�todo que implementa el bucle de eventos de SDL 
void EntornoG::visualizaEntorno (void)
{
    SDL_Event evento;
    int port, esp, tecla, accion, indiceP, entrada, env, hayEvento, turno = -1;

    // Carga de las texturas del mundo
    this->cargaTexturas ();

    // Visualizacion del menu de comienzo
    esp = this->visualizaMenuStart ();

    // Creaci�n de la conexi�n del cliente
    this->conexion = new ConexionCliente (AF_INET, SOCK_STREAM, 0);

    // Conversi�n del puerto
    port = htons (50007);

    // Conexi�n del cliente
    this->conexion->conectaAServidor (AF_INET, this->servidorIP, port);

    // Env�o de la especie del personaje activo al servidor
    enviaEnteroAServidor (this->conexion, esp);

    // Carga del tama�o del mundo
    this->cargaTamanoMundo ();
    
    // Bucle de visualizaci�n
    while (1)
    {
	// Recepci�n del flag de env�o
	env = recibeEnteroDeServidor (this->conexion);
	
	// Recepci�n del turno
	this->turno = recibeEnteroDeServidor (this->conexion);		

	// Si el flag de env�o est� activo
	if (env > 0)
	{
	    // Carga del mundo
	    indiceP = this->cargaMundo (env);

	    // Si el personaje activo no existe
	    if (indiceP == -1)
	    {
		// Env�o del flag de desconexi�n
		enviaEnteroAServidor (this->conexion, -1);

		// Retardo
		sleep (1);

		// Cierre
		this->visualizaOver ();
	    }

	    // Visualizaci�n
	    this->GL_display (indiceP);
	    SDL_GL_SwapBuffers ();		    	    
	}

	if (this->turno != turno)
	{
	    // Actualizaci�n del turno
	    turno = this->turno;

	    // Visualizaci�n
	    this->GL_display (indiceP);
	    SDL_GL_SwapBuffers ();
	}

	// Bucle de eventos
	while ((hayEvento = SDL_PollEvent (&evento)))
	{	
	    // Eventos
	    switch (evento.type)
	    {
		// Evento expose
		case SDL_VIDEOEXPOSE:
		{
		    // Inicializaci�n de la ventana
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		
		    // Visualizaci�n
		    this->GL_display (indiceP);
		    SDL_GL_SwapBuffers ();		
		    
		    break;
		}
	     
		// Evento redimensionar aplicaci�n
		case SDL_VIDEORESIZE:
		{
		    // Inicializaci�n de la ventana redimensionada
		    this->ancho = evento.resize.w;
		    this->alto = evento.resize.h;
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		    
		    // Visualizaci�n
		    this->GL_display (indiceP);
		    SDL_GL_SwapBuffers ();
		    
		    break;		
		}
		
		// Evento pulsar tecla 
		case SDL_KEYDOWN:
		{
		    // Obtenci�n de la tecla pulsada
		    tecla = evento.key.keysym.sym;
		    
		    // Obtenci�n de la acci�n asociada a la tecla
		    accion = this->SDL_key (tecla, &entrada);
		    		    
		    // Si le toca el turno o es una acci�n sin turno
		    if ((this->sock == this->turno) || (accion == -1) || 
			(accion == 26))
		    {
			// Env�o de la accion
			enviaEnteroAServidor (this->conexion, accion);

			// Env�o al servidor de las coordenadas modificadas
			this->enviaCoordenadas (accion, entrada);

			// Si la acci�n es de desconexi�n
			if (accion == -1)
			{
			    // Retardo
			    sleep (1);

			    // Cierre
			    this->visualizaOver ();
			}
		    }

		    // Si no le toca el turno
		    else
			enviaEnteroAServidor (this->conexion, 0);

		    break;
		}
		
		// Evento cerrar aplicaci�n
		case SDL_QUIT:
		{		  
		    // Env�o del flag de desconexi�n
		    enviaEnteroAServidor (this->conexion, -1);
		    
		    // Retardo
		    sleep (1);

		    // Cierre
		    this->visualizaOver ();
		    
		    break;
		}	    	    
		
		default:
		    break;
	    }
	}
	
	if (hayEvento == 0)	
	    enviaEnteroAServidor (this->conexion, 0);	    	
    }
}

/***************************************************************************/

// M�todo que visualiza una pantalla de inicio con selecci�n de opciones
int EntornoG::visualizaMenuStart (void)
{
    SDL_Event evento;
    int tecla, esp, posOpcion;

    // Inicializacion de parametros
    esp = -1;
    posOpcion = 3;

    // Bucle de visualizaci�n
    while (esp == -1)
    {    
	// Bucle de eventos
	while (SDL_PollEvent (&evento))
	{
	    // Eventos
	    switch (evento.type)
	    {
		// Evento expose
		case SDL_VIDEOEXPOSE:
		{
		    // Inicializaci�n de la ventana
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		
		    // Visualizaci�n
		    this->GL_displayMenuStart (posOpcion);
		    SDL_GL_SwapBuffers ();		
		    
		    break;
		}
	     
		// Evento redimensionar aplicaci�n
		case SDL_VIDEORESIZE:
		{
		    // Inicializaci�n de la ventana redimensionada
		    this->ancho = evento.resize.w;
		    this->alto = evento.resize.h;
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		    
		    // Visualizaci�n
		    this->GL_displayMenuStart (posOpcion);
		    SDL_GL_SwapBuffers ();
		    
		    break;		
		}
		
		// Evento pulsar tecla 
		case SDL_KEYDOWN:
		{
		    // Obtenci�n de la tecla pulsada
		    tecla = evento.key.keysym.sym;
			    
		    // Cierre
		    if (tecla == SDLK_ESCAPE)
		    {
			SDL_Quit ();
			exit (0);					
		    }

		    // Cursor arriba
		    else if ((tecla == SDLK_UP) and (posOpcion < 3))
			posOpcion += 3;
		    
		    // Cursor abajo
		    else if ((tecla == SDLK_DOWN) and (posOpcion > -9))
			posOpcion -= 3;
		    
		    // Tecla return
		    else if (tecla == SDLK_RETURN)
		    {			
			if (posOpcion == 3)
			    esp = 0;
			
			else if (posOpcion == 0)
			    esp = 1;

			else if (posOpcion == -3)
			    esp = 2;

			else if (posOpcion == -6)
			    esp = 3;

			else if (posOpcion == -9)
			    esp = 4;				
		    }

		    // Visualizaci�n
		    this->GL_displayMenuStart (posOpcion);
		    SDL_GL_SwapBuffers ();

		    break;
		}
		
		// Evento cerrar aplicaci�n
		case SDL_QUIT:
		{		  
		    // Cierre
		    SDL_Quit ();
		    exit (0);
		    
		    break;
		}	    	    
		
		default:
		    break;
	    }
	}
    }

    return esp;
}

/***************************************************************************/

// M�todo que visualiza una pantalla de fin
void EntornoG::visualizaOver (void)
{
    SDL_Event evento;
    int tecla;

    // Inicializaci�n de la ventana
    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 32, MASK);
    this->GL_reshape (this->ancho, this->alto);
    
    // Visualizaci�n
    this->GL_displayOver ();
    SDL_GL_SwapBuffers ();		

    // Bucle de eventos
    while (SDL_WaitEvent (&evento))
    {
	// Eventos
	switch (evento.type)
	{
	    // Evento expose
	    case SDL_VIDEOEXPOSE:
	    {
		// Inicializaci�n de la ventana
		this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						  32, MASK);
		this->GL_reshape (this->ancho, this->alto);
		
		// Visualizaci�n
		this->GL_displayOver ();
		SDL_GL_SwapBuffers ();		
		
		break;
	    }
	     
	    // Evento redimensionar aplicaci�n
	    case SDL_VIDEORESIZE:
	    {
		// Inicializaci�n de la ventana redimensionada
		this->ancho = evento.resize.w;
		this->alto = evento.resize.h;
		this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						  32, MASK);
		this->GL_reshape (this->ancho, this->alto);
		    
		// Visualizaci�n
		this->GL_displayOver ();
		SDL_GL_SwapBuffers ();
		    
		break;		
	    }
		
	    // Evento pulsar tecla 
	    case SDL_KEYDOWN:
	    {
		// Obtenci�n de la tecla pulsada
		tecla = evento.key.keysym.sym;
		
		// Cierre
		if (tecla == SDLK_ESCAPE)
		{
		    SDL_Quit ();
		    exit (0);					
		}
		
		break;
	    }
		
	    // Evento cerrar aplicaci�n
	    case SDL_QUIT:
	    {		  
		// Cierre
		SDL_Quit ();
		exit (0);
		    
		break;
	    }	    	    
		
	    default:
		break;
	}
    }
}

/***************************************************************************/

// M�todo que implementa la funci�n de inicializaci�n de OpenGL
void EntornoG::GL_init (void)
{
    // T�cnica de coloreado 
    glShadeModel (GL_FLAT);

    // Activaci�n del Z-buffer (profundidad)
    glDepthFunc (GL_LEQUAL);
    glEnable (GL_DEPTH_TEST);
    
    // Definici�n de todos los poligonos del mismo modo (rellenos)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // para ambos lados

    // La textura tanto en la direcci�n S como en T se repite
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // La aplicaci�n del texel al centro del pixel se hace utilizando medias
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Se permite aplicar efectos a la textura
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/***************************************************************************/

// M�todo que implementa la funci�n de redimensionado de OpenGL
void EntornoG::GL_reshape (int ancho, int alto)
{
    // Definici�n del viewport
    glViewport (0, 0, (GLint) ancho, (GLint) alto);

    // Carga de la matriz para la proyecci�n
    glMatrixMode (GL_PROJECTION);

    // Carga de la matriz identidad
    glLoadIdentity ();

    // Definici�n de la proyecci�n
    gluPerspective (45, (float) ancho / (float) alto, 0.1, 100);

    // Carga de la matriz de modelo 
    glMatrixMode (GL_MODELVIEW);   
}

/***************************************************************************/

// M�todo que implementa la funci�n de dibujado de OpenGL
void EntornoG::GL_display (int indiceP)
{
    Edificio *unEdificio;
    Objeto *unObjeto;
    Personaje *unPersonaje;
    Elemento *unElemento;
    Casilla *unaCasilla;
    Textura *unaTextura;
    uchar *imagen;
    uchar *imagen2;
    uchar *imagen3;
    float color;
    int inf, sup, x, y, lx, ly, tipo, tipoMuro, visible, especie; 
    int posicion, fachada, pared, tejado;
    int ancho, ancho2, ancho3, alto, alto2, alto3;

    // Borrado de los buffers de color y del Z-buffer 
    if (this->edif != -1)
	color = 0.0;
    else
	color = 0.6;

    glClearColor(0.0, color, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carga de la matriz identidad
    glLoadIdentity ();

    // Posici�n de la c�mara
    glTranslatef (0.0, 0.0, -7.0);

    glPushMatrix ();
    {
	// Inclinaci�n 45 grados
	glRotatef (-45, 1, 0, 0);
    
	// Desplazamiento del mundo en cada movimiento
	glTranslatef (0.0, -this->iniy, 0.0); 
	glTranslatef (-this->inix, 0.0, 0.0);        
    
	// Dibujo de las casillas del mundo
	if (this->edif == -1)         
	{    	
	    // Obtenci�n del tipo de muro
	    tipoMuro = -1;
	    
	    for (int i = 0; i < this->tamanoCasillas; i++)
	    {
		// Obtenci�n de la casilla
		unaCasilla = this->listaCasillas->obtieneElemento (i);
		
		// Obtenci�n de la posici�n (x,y) de la casilla
		x = unaCasilla->obtieneAtributo ("posx");
		y = unaCasilla->obtieneAtributo ("posy");
		
		// Obtenci�n del tipo de la casilla	
		tipo = unaCasilla->obtieneAtributo ("tipo");
		
		// Dibujo de la casilla en funci�n de su tipo
		unaTextura = this->listaTexturas->obtieneElemento (tipo);
		imagen = unaTextura->obtienePixels ();
		ancho = unaTextura->obtieneAncho ();
		alto = unaTextura->obtieneAlto ();
		
		this->GL_poligono (x, y, 1, 1, imagen, ancho, alto, 0, 1);
	    }
	}
	
	// Dibujo de las casillas de los castillos
	else if ((this->edif % 6) == 0) 
	{
	    // Obtenci�n del tipo de muro
	    tipoMuro = 17;
	    
	    // Obtenci�n de la textura
	    unaTextura = this->listaTexturas->obtieneElemento (5);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    
	    // Obtenci�n de los l�mites
	    inf = castilInf;
	    sup = castilSup;
	    
	    // Bucle de casillas
	    for (int i = inf; i < sup; i++)
		for (int j = inf; j < sup; j++)	    
		    this->GL_poligono (i, j, 1, 1, imagen, ancho, alto, 0, 1);
	}
	
	// Dibujo de las casillas de las casas
	else                            
	{
	    // Obtenci�n del tipo de muro
	    tipoMuro = 16;
	    
	    // Obtenci�n de la textura
	    unaTextura = this->listaTexturas->obtieneElemento (4);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    
	    // Obtenci�n de los l�mites
	    inf = casaInf;
	    sup = casaSup;
	    
	    // Bucle de casillas
	    for (int i = inf; i < sup; i++)
		for (int j = inf; j < sup; j++)	    
		    this->GL_poligono (i, j, 1, 1, imagen, ancho, alto, 0, 1);
	}
	
	
	// Dibujo de los muros  
	if (tipoMuro != -1)
	    for (int i = inf; i <= sup; i += sup*2)
		for (int j = inf; j < sup; j++)
		{
		    // Muros horizontales exceptuando la entrada
		    if ((j != 0) || ((j == 0) && (i != inf)))
		    {
			unaTextura = this->listaTexturas->
			    obtieneElemento (tipoMuro);
			
			imagen = unaTextura->obtienePixels ();
			ancho = unaTextura->obtieneAncho ();
			alto = unaTextura->obtieneAlto ();
			
			this->GL_poligono (j, i, 1, 1, imagen, ancho, alto, 
					   90, 1);
		    }
		    
		    // Muros verticales
		    this->GL_poligono(i, j, 1, 1, imagen, ancho, alto, -90, 2);
		}
    
	// Dibujo de los edificios
	if (this->edif == -1)
	{
	    for (int i = 0; i < this->tamanoEdificios; i++)
	    {
		// Obtenci�n del edificio
		unEdificio = this->listaEdificios->obtieneElemento (i);
		
		// Obtenci�n de la posici�n (x,y) del edificio
		x = unEdificio->obtieneAtributo ("posx");
		y = unEdificio->obtieneAtributo ("posy");
		
		// Obtenci�n de la longitud (x,y) del edificio
		lx = unEdificio->obtieneAtributo ("longx");
		ly = unEdificio->obtieneAtributo ("longy");
		
		// Obtenci�n del tipo de edificio
		tipo = unEdificio->obtieneAtributo ("tipo");
		
		// Dibujo del edificio en funci�n de su tipo
		if (tipo == 0)	// Castillo
		{
		    /* Asignaci�n de los �ndices para la fachada, pared y 
		       tejado */
		    fachada = 8;
		    pared = 9;
		    tejado = 6;
		}
		
		else if (tipo == 1) // Posada	
		{
		    /* Asignaci�n de los �ndices para la fachada, pared y 
		       tejado */
		    fachada = 10;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 2) // Biblioteca
		{
		    /* Asignaci�n de los �ndices para la fachada, pared y 
		       tejado */
		    fachada = 11;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 3) // Armas
		{
		    /* Asignaci�n de los �ndices para la fachada, pared y 
		       tejado */
		    fachada = 12;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 4) // Escudos
		{
		    /* Asignaci�n de los �ndices para la fachada, pared y 
		       tejado */
		    fachada = 13;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 5) // Armaduras
		{
		    /* Asignaci�n de los �ndices para la fachada, pared y 
		       tejado */
		    fachada = 14;
		    pared = 15;
		    tejado = 7;
		}
		
		// Carga de la textura de la fachada
		unaTextura = this->listaTexturas->obtieneElemento (fachada);
		imagen = unaTextura->obtienePixels ();
		ancho = unaTextura->obtieneAncho ();
		alto = unaTextura->obtieneAlto ();
		
		// Carga de la textura de la pared
		unaTextura = this->listaTexturas->obtieneElemento (pared);
		imagen2 = unaTextura->obtienePixels ();
		ancho2 = unaTextura->obtieneAncho ();
		alto2 = unaTextura->obtieneAlto ();
		
		// Carga de la textura del tejado
		unaTextura = this->listaTexturas->obtieneElemento (tejado);
		imagen3 = unaTextura->obtienePixels ();
		ancho3 = unaTextura->obtieneAncho ();
		alto3 = unaTextura->obtieneAlto ();
		
		// Dibujo del edificio
		this->GL_cubo (x, y, lx, ly, -ly, imagen, imagen2, imagen3, 
			       ancho, alto, ancho2, alto2, ancho3, alto3);
	    }
	}
	
	// Dibujo de los objetos y personajes por orden de profundidad
	for (int i = 0; i < this->tamanoElementos; i++)
	{
	    // Obtenci�n del elemento ordenado
	    unElemento = this->listaElementos->obtieneElemento (i);
	    
	    // Obtenci�n del tipo de elemento
	    tipo = unElemento->obtieneAtributo ("tipo");
	    
	    // Obtenci�n del �ndice del elemento
	    posicion = unElemento->obtieneAtributo ("posicion");
	    
	    // Personajes
	    if (tipo == 0)	    
	    {
		// Obtenci�n del personaje
		unPersonaje = this->listaP->obtieneElemento (posicion);
		
		// Obtenci�n de la posici�n (x,y) del personaje
		x = unPersonaje->obtieneAtributo ("posx");
		y = unPersonaje->obtieneAtributo ("posy");
		
		// Obtenci�n de la especie del personaje
		especie = unPersonaje->obtieneAtributo ("esp");
		
		// Obtenci�n de la textura asociada a la especie del personaje
		posicion = 18 + especie;	    
		unaTextura = this->listaTexturas->obtieneElemento (posicion);
		imagen = unaTextura->obtienePixels ();
		ancho = unaTextura->obtieneAncho ();
		alto = unaTextura->obtieneAlto ();
		
		// Dibujo del personaje
		this->GL_poligonoT (x, y, 1, 1, imagen, ancho, alto, 45.0);
	    }
	    
	    // Objetos
	    else if (tipo == 1)
	    {
		// Obtenci�n del objeto
		unObjeto = this->listaObjetos->obtieneElemento (posicion);
		
		// Obtenci�n de la visibilidad del objeto
		visible = unObjeto->obtieneAtributo ("visi");
		
		// Si es visible
		if (visible == 1)
		{
		    // Obtenci�n de la posici�n (x,y) del objeto
		    x = unObjeto->obtieneAtributo ("posx");
		    y = unObjeto->obtieneAtributo ("posy");
		    
		    // Obtenci�n de la longitud (x,y) del objeto
		    lx = unObjeto->obtieneAtributo ("longx");
		    ly = unObjeto->obtieneAtributo ("longy");
		    
		    // Obtenci�n del tipo del objeto
		    tipo = unObjeto->obtieneAtributo ("tipo");
		    
		    // Obtenci�n de la textura asociada al tipo del objeto
		    posicion = 23 + tipo;
		    unaTextura = this->listaTexturas->obtieneElemento
			(posicion);
		    imagen = unaTextura->obtienePixels ();
		    ancho = unaTextura->obtieneAncho ();
		    alto = unaTextura->obtieneAlto ();
		    
		    if (tipo == 20)
		    {
			posicion = this->tamanoTexturas-2;
			unaTextura = this->listaTexturas->
			    obtieneElemento (posicion);
			
			imagen2 = unaTextura->obtienePixels ();
			ancho2 = unaTextura->obtieneAncho ();
			alto2 = unaTextura->obtieneAlto ();
			
			this->GL_cubo (x, y, lx, ly, -0.5, imagen, imagen2, 
				       imagen2, ancho, alto, ancho2, alto2, 
				       ancho2, alto2);
		    }
		    
		    else if (tipo == 22)
		    {
			posicion = this->tamanoTexturas-1;
			unaTextura = this->listaTexturas->
			    obtieneElemento (posicion);
			
			imagen2 = unaTextura->obtienePixels ();
			ancho2 = unaTextura->obtieneAncho ();
			alto2 = unaTextura->obtieneAlto ();
			
			this->GL_cubo (x, y, lx, ly - 0.5, -1, imagen2, 
				       imagen2, imagen, ancho2, alto2, ancho2, 
				       alto2, ancho, alto);
		    }
		    
		    else
			this->GL_poligonoT (x, y, lx, ly, imagen, ancho, alto,
					    45.0);
		}
	    }
	}
		
	// Dibujo del cursor del personaje activo	
	this->GL_cursor (this->cursorx, this->cursory);
    }
    glPopMatrix ();

    // Dibujo de las caracter�sticas del personaje
    if (this->caractStatus == 1)    
	this->GL_caracteristicas (indiceP);
    
    // Dibujo del men� de acciones
    if (this->menuAccStatus == 1)
	this->GL_menuAcciones ();
}

/***************************************************************************/

// M�todo que implementa la funci�n de dibujado de una pantalla de inicio
void EntornoG::GL_displayMenuStart (int posOpcion)
{
    Textura *unaTextura;
    uchar *imagen;
    float posicion;
    int ancho, alto;

    // Borrado de los buffers de color y del Z-buffer 
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carga de la matriz identidad
    glLoadIdentity ();

    // Posici�n de la c�mara
    glTranslatef (0.0, 0.0, -2.4);

    // Obtencion de la textura
    unaTextura = new Textura ("./texturas/menus/start.png", RGB);
    imagen = unaTextura->obtienePixels ();
    ancho = unaTextura->obtieneAncho ();
    alto = unaTextura->obtieneAlto ();

    // Dibujo del poligono con la textura
    this->GL_poligono (-2, -1.5, 4, 2.8, imagen, ancho, alto, 0, 1);

    // Obtencion de la textura del indicador
    unaTextura = this->listaTexturas->obtieneElemento (51);
    imagen = unaTextura->obtienePixels ();
    ancho = unaTextura->obtieneAncho ();
    alto = unaTextura->obtieneAlto ();

    // Obtencion de la posicion del indicador
    if (posOpcion == 3)
	posicion = 0.3;
    
    else if (posOpcion == 0)
	posicion = 0.0;
    
    else if (posOpcion == -3)
	posicion = -0.3;
    
    else if (posOpcion == -6)
	posicion = -0.6;
    
    else if (posOpcion == -9)
	posicion = -0.9;				

    // Dibujo del indicador
    this->GL_poligonoT (0.2, posicion, 0.3, 0.3, imagen, ancho, alto, 0.0);
}

/***************************************************************************/

// M�todo que implementa la funci�n de dibujado de una pantalla de fin
void EntornoG::GL_displayOver (void)
{
    Textura *unaTextura;
    uchar *imagen;
    int ancho, alto;

    // Borrado de los buffers de color y del Z-buffer 
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Carga de la matriz identidad
    glLoadIdentity ();

    // Posici�n de la c�mara
    glTranslatef (0.0, 0.0, -2.4);

    // Obtencion de la textura
    unaTextura = new Textura ("./texturas/menus/over.png", RGB);
    imagen = unaTextura->obtienePixels ();
    ancho = unaTextura->obtieneAncho ();
    alto = unaTextura->obtieneAlto ();

    // Dibujo del poligono con la textura
    this->GL_poligono (-2, -1.5, 4, 2.8, imagen, ancho, alto, 0, 1);
}

/***************************************************************************/

// M�todo que dibuja una flecha indicadora en la posici�n se�alada
void EntornoG::GL_cursor (float x, float y)
{
    glPushMatrix ();
    {	    
	// Desactivaci�n del Z-buffer (profundidad)
	glDisable (GL_DEPTH_TEST);

	// Posici�n del cursor
	glTranslatef (x, y, 0.0);

	// Rotaci�n del cursor
	glRotatef (90.0, 1.0, 0.0, 0.0);

	// Si el cursor est� a 0
	if (this->cursorStatus == 0)
	    glColor3f (1.0, 0.0, 0.0); // Color Rojo 

	// Si el cursor est� a 1
	else
	    glColor3f (0.0, 1.0, 0.0); // Color Verde

	// Dibujo del cursor por v�rtices
	glBegin (GL_POLYGON);
	{	    
	    glVertex3f (0.65, 1.5, 0.0);  // V�rtice 1
	    glVertex3f (0.25, 1.5, 0.0);  // V�rtice 2
	    glVertex3f (0.45, 1.3, 0.0);  // V�rtice 3
	}
	glEnd ();
	glColor3f (1.0, 1.0, 1.0);

	// Activaci�n del Z-buffer (profundidad)
	glEnable (GL_DEPTH_TEST);
    }
    glPopMatrix ();    
}

/***************************************************************************/

/* M�todo que dibuja un poligono semitransparente en OpenGL con un texto 
   asociado a las caracter�sticas del personaje activo */
void EntornoG::GL_caracteristicas (int indiceP)
{    
    Personaje *unPersonaje;
    Textura *unaTextura;
    uchar *imagen;
    char *cad1;
    char *cad2;
    float x, y, z;
    int ancho, alto;
    int pg, ene, ham, sed, maxpg, maxene, maxham, maxsed; 
    int fue, con, tam, inte, des, mh1, mh2, mmr, estu, entr, obj, nturnos;
    int tipo, escudo, arma, armadura, monedas, llave, pocion;

    // Obtenci�n del personaje
    unPersonaje = this->listaP->obtieneElemento (indiceP);
    
    // Obtencion de los atributos de salud
    pg = unPersonaje->obtieneAtributo ("pg");
    ene = unPersonaje->obtieneAtributo ("ene");
    ham = unPersonaje->obtieneAtributo ("ham");
    sed = unPersonaje->obtieneAtributo ("sed");
    maxpg = unPersonaje->obtieneAtributo ("maxpg");
    maxene = unPersonaje->obtieneAtributo ("maxene");
    maxham = unPersonaje->obtieneAtributo ("maxham");
    maxsed = unPersonaje->obtieneAtributo ("maxsed");
    
    // Obtenci�n de las habilidades
    fue = unPersonaje->obtieneAtributo ("fue");
    con = unPersonaje->obtieneAtributo ("con");
    tam = unPersonaje->obtieneAtributo ("tam");
    inte = unPersonaje->obtieneAtributo ("inte");
    des = unPersonaje->obtieneAtributo ("des");
    mh1 = unPersonaje->obtieneAtributo ("mh1");
    mh2 = unPersonaje->obtieneAtributo ("mh2");
    mmr = unPersonaje->obtieneAtributo ("mmr");
    estu = unPersonaje->obtieneAtributo ("estu");
    entr = unPersonaje->obtieneAtributo ("entr");
    obj = unPersonaje->obtieneAtributo ("obj");
    nturnos = unPersonaje->obtieneAtributo ("nturnos");
    
    // Obtenci�n del equipo
    escudo = unPersonaje->obtieneEqu (0);
    arma = unPersonaje->obtieneEqu (1);
    armadura = unPersonaje->obtieneEqu (2);
    monedas = unPersonaje->obtieneEqu (3);
    llave = unPersonaje->obtieneEqu (4);
    pocion = unPersonaje->obtieneEqu (5);       	

    glPushMatrix ();
    {
	// Desactivaci�n del Z-buffer (profundidad)
	glDisable (GL_DEPTH_TEST);

	// Carga de la textura del pol�gono semitransparente
	unaTextura = new Textura ("./texturas/menus/fondo.png", RGBA);    
	imagen = unaTextura->obtienePixels ();
	ancho = unaTextura->obtieneAncho ();
	alto = unaTextura->obtieneAlto ();
	
	// Dibujo del pol�gono semitransparente
	GL_poligonoT (1.5, 3.0, 4.0, -6.0, imagen, ancho, alto, 0.0);
	
	// Inicializaci�n de la fuente
	glfInit ();
	
	// Carga de la fuente
	glfLoadFont ("./fonts/arial1.glf");
	
	// Activaci�n de contorno
	glfEnable (GLF_CONTOURING);
	
	// Distancia entre los caracteres
	glfSetSymbolSpace(0.3);
	
	// Tama�o del texto
	glScalef (0.1, 0.1, 0.1);
	
	// Inicializaci�n de las coordenadas del texto
	x = 20.0;
	y = 25.0;
	z = 4.0;
	
	// Impresi�n de los pg
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y, z, "P.Golpe:");
	
	cad1 = itoa (pg);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxpg);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y, z, cad1);
	
	// Impresi�n de la energ�a
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-2, z, "Energia:");
	
	cad1 = itoa (ene);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxene);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y-2, z, cad1);
	
	// Impresi�n del hambre
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-4, z, "Hambre:");
	
	cad1 = itoa (ham);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxham);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y-4, z, cad1);
	
	// Impresi�n de la sed
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-6, z, "Sed:");
	
	cad1 = itoa (sed);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxsed);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y-6, z, cad1);
	
	// Impresi�n de la fuerza
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-9, z, "Fue:");
	
	cad1 = itoa (fue);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-9, z, cad1);
	
	// Impresi�n de la constituci�n
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-11, z, "Con:");
	
	cad1 = itoa (con);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-11, z, cad1);
	
	// Impresi�n del tama�o
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-13, z, "Tam:");
	
	cad1 = itoa (tam);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-13, z, cad1);
	
	// Impresi�n de la inteligencia
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-15, z, "Inte:");
	
	cad1 = itoa (inte);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-15, z, cad1);
	
	// Impresi�n de la destreza
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-17, z, "Des:");
	
	cad1 = itoa (des);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-17, z, cad1);
	
	// Impresi�n del sigilo
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-19, z, "Sigilo:");
	
	cad1 = itoa (mh1);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-19, z, cad1);
	
	// Impresi�n de la percepci�n
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-21, z, "Percepc:");
	
	cad1 = itoa (mh2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-21, z, cad1);
	
	// Impresi�n del n�mero de estudios
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-23, z, "N.Estu:");
	
	cad1 = itoa (estu);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-23, z, cad1);
	
	// Impresi�n del n�mero de entrenamientos
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-25, z, "N.Entr:");
	
	cad1 = itoa (entr);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-25, z, cad1);
	
	// Impresi�n de la misi�n
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-27, z, "Mision:");
	
	cad1 = itoa (obj);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-27, z, cad1);
	
	// Impresi�n del momento de reacci�n
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-29, z, "M.Reacc:");
	
	cad1 = itoa (mmr);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-29, z, cad1);
	
	// Impresi�n del n�mero de turnos
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-31, z, "N.Turnos:");
	
	cad1 = itoa (nturnos);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-31, z, cad1);
	
	// Impresi�n de la armadura
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-34, z, "Armadura:");
	
	if (armadura != -1)
	{
	    tipo = 57 + armadura;
	    unaTextura = this->listaTexturas->obtieneElemento (tipo);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    this->GL_poligonoT (x+11, y-36, 5, 5, imagen, ancho, alto, 0.0);
	}
	
	// Impresi�n del arma
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-37, z, "Arma:");
	
	if (arma != -1)
	{
	    tipo = 49 + arma;
	    unaTextura = this->listaTexturas->obtieneElemento (tipo);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    this->GL_poligonoT (x+11, y-39, 5, 5, imagen, ancho, alto, 0.0);
	}
	
	// Impresi�n del escudo
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-39, z, "Escudo:");
	
	if (escudo != -1)
	{
	    tipo = 53 + escudo;
	    unaTextura = this->listaTexturas->obtieneElemento (tipo);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    this->GL_poligonoT (x+11, y-42, 5, 5, imagen, ancho, alto, 0.0);
	}
	
	// Impresi�n de la llave
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-42, z, "Llave:");
	
	if (llave != -1)
	{
	    unaTextura = new Textura ("./texturas/menus/llave.png", RGBA);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    this->GL_poligonoT (x+11, y-45, 5, 5, imagen, ancho, alto, 0.0);
	}
	
	// Impresi�n de las monedas
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-45, z, "Monedas:");
	
	cad1 = itoa (monedas);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-45, z, cad1);
	
	// Impresi�n de la poci�n
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-47, z, "Pocion:");
	
	if (pocion != -1)
	{
	    cad1 = itoa (pocion);
	    glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	    this->GL_imprimeTexto (x+12, y-47, z, cad1);
	}
	
	// Impresi�n del turno
	glfSetContourColor(1.0, 0.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-50, z, "Turno:");
	
	cad1 = itoa (this->turno);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-50, z, cad1);
	
	// Descarga de la fuente
	glfUnloadFont ();
	    
	// Cierre de la liber�a de fuentes
	glfClose ();

	// Activaci�n del Z-buffer (profundidad)
	glEnable (GL_DEPTH_TEST);

	// Liberaci�n de las cadenas de caracteres
	delete [] cad1;
	delete [] cad2;
    }
    glPopMatrix ();
}

/***************************************************************************/

/* M�todo que dibuja un pol�gono semitransparente en OpenGL con un men�
   de acciones */
void EntornoG::GL_menuAcciones (void)
{
    Textura *unaTextura;
    uchar *imagen;
    float x, y, z;
    int ancho, alto;

    glPushMatrix ();
    {
	// Desactivaci�n del Z-buffer (profundidad)
	glDisable (GL_DEPTH_TEST);
	
	// Carga de la textura del pol�gono semitransparente
	unaTextura = new Textura ("./texturas/menus/fondo.png", RGBA);    
	imagen = unaTextura->obtienePixels ();
	ancho = unaTextura->obtieneAncho ();
	alto = unaTextura->obtieneAlto ();
	
	// Dibujo del pol�gono semitransparente
	GL_poligonoT (-2.0, 0.0, 3.5, -4.0, imagen, ancho, alto, 0.0);
	
	// Inicializaci�n de la fuente
	glfInit ();
	
	// Carga de la fuente
	glfLoadFont ("./fonts/arial1.glf");
	
	// Activaci�n de contorno
	glfEnable (GLF_CONTOURING);
	
	// Distancia entre los caracteres
	glfSetSymbolSpace(0.3);

        // Tama�o del texto
	glScalef (0.1, 0.1, 0.1);

        // Inicializaci�n de las coordenadas del texto
	x = -13.0;
	y = -5.0;
	z = 4.0;

	// Impresi�n del texto inicial
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y, z, "Accion a realizar?");
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);

	// Impresi�n de las acciones del personaje
	if (this->accionActual == 4)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Atacar personaje");
	    this->GL_imprimeTexto (x, y-8, z, "Robar personaje");
	    this->GL_imprimeTexto (x, y-12, z, "Salir");
	}

	// Impresi�n de las acciones de comer setas
	else if (this->accionActual == 6)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comer setas");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de comer miel
	else if (this->accionActual == 7)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comer miel");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de abrir cofre
	else if (this->accionActual == 8)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Abrir cofre");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de aceptar misi�n
	else if (this->accionActual == 9)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Aceptar mision 50$ * entr");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de liberar prisionero
	else if (this->accionActual == 10)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Liberar prisionero");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de estudiar
	else if (this->accionActual == 11)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Estudiar 50$");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de descansar
	else if (this->accionActual == 12)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Descansar 50$");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}
	
	// Impresi�n de las acciones de comprar armas
	else if (this->accionActual == 13)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comprar esp. corta 100$");
	    this->GL_imprimeTexto (x, y-8, z, "Comprar esp. ancha 150$");
	    this->GL_imprimeTexto (x, y-12, z, "Comprar hacha 200$");
	    this->GL_imprimeTexto (x, y-16, z, "Comprar cadena 250$");
	    this->GL_imprimeTexto (x, y-20, z, "Salir");
	}

	// Impresi�n de las acciones de comprar escudos
	else if (this->accionActual == 17)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comprar escu. verde 100$");
	    this->GL_imprimeTexto (x, y-8, z, "Comprar escu. rojo 150$");
	    this->GL_imprimeTexto (x, y-12, z, "Comprar escu. azul 200$");
	    this->GL_imprimeTexto (x, y-16, z, "Salir");
	}

	// Impresi�n de las acciones de comprar armaduras
	else if (this->accionActual == 20)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comprar cuero 100$");
	    this->GL_imprimeTexto (x, y-8, z, "Comprar cota 150$");
	    this->GL_imprimeTexto (x, y-12, z, "Comprar armadura 200$");
	    this->GL_imprimeTexto (x, y-16, z, "Comprar coraza 250$");
	    this->GL_imprimeTexto (x, y-20, z, "Salir");
	}

	// Impresi�n de las acciones de beber agua
	else if (this->accionActual == 24)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Beber agua");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresi�n de las acciones de finalizar misi�n
	else if (this->accionActual == 25)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Finalizar mision");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Dibujo del icono
	unaTextura = this->listaTexturas->obtieneElemento (51);
	imagen = unaTextura->obtienePixels ();
	ancho = unaTextura->obtieneAncho ();
	alto = unaTextura->obtieneAlto ();
	this->GL_poligonoT (x-7, this->posAccion, 5, 5, imagen, ancho, 
			    alto, 0.0);

	// Descarga de la fuente
	glfUnloadFont ();

	// Cierre de la liber�a de fuentes
	glfClose ();

	// Activaci�n del Z-buffer (profundidad)
	glEnable (GL_DEPTH_TEST);
    }
    glPopMatrix ();
}

/***************************************************************************/

/* M�todo que imprime la cadena de texto dada en las coordenadas
   especificadas */
void EntornoG::GL_imprimeTexto (float x, float y, float z, char *texto)
{
    glPushMatrix ();
    {
	glTranslatef (x, y, z);
	glfDraw3DSolidString (texto);
    }
    glPopMatrix ();
}

/***************************************************************************/

// M�todo que dibuja un pol�gono plano en OpenGL con una textura
void EntornoG::GL_poligono (float x, float y, float lx, float ly, 
			    uchar *imagen, int ancho, int alto, float rot, 
			    int eje)
{
    glPushMatrix ();
    {
	// Posici�n del pol�gono
	glTranslatef (x, y, 0.0);

	// Rotaci�n del pol�gono
	if (eje == 1)
	    glRotatef (rot, 1.0, 0.0, 0.0);

	else if (eje == 2)
	    glRotatef (rot, 0.0, 1.0, 0.0);


	// Activaci�n de la textura
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen);

	// Dibujo del pol�gono por v�rtices
	glBegin (GL_POLYGON);
	{
	    glTexCoord2f (0.0, 1.0);     // V�rtice 1 de la textura
	    glVertex3f (0.0, 0.0, 0.0);  // V�rtice 1 del pol�gono 
	    
	    glTexCoord2f (1.0, 1.0);     // V�rtice 2 de la textura
	    glVertex3f (lx, 0.0, 0.0);   // V�rtice 2 del pol�gono
	    
	    glTexCoord2f (1.0, 0.0);     // V�rtice 3 de la textura
	    glVertex3f (lx, ly, 0.0);    // V�rtice 3 del pol�gono

	    glTexCoord2f (0.0, 0.0);     // V�rtice 4 de la textura
	    glVertex3f (0.0, ly, 0.0);   // V�rtice 4 del pol�gono	       
	}
	glEnd ();

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);
    }
    glPopMatrix ();
}

/***************************************************************************/

/* M�todo que dibuja un pol�gono plano en OpenGL utilizando una textura con
   transparencia */
void EntornoG::GL_poligonoT (float x, float y, float lx, float ly, 
			     uchar *imagen, int ancho, int alto, float rot)
{
    glPushMatrix ();
    {
	// Posici�n del pol�gono
	glTranslatef (x, y, 0.0);

	// Rotaci�n del pol�gono
	glRotatef (rot, 1.0, 0.0, 0.0);

	// Activaci�n de la textura
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, 
		      GL_UNSIGNED_BYTE, imagen);

	// Activaci�n del canal Alpha para la transparencia
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	// Color blanco con canal Alpha
	glColor4f (1.0, 1.0, 1.0, 1.0);

	// Dibujo del pol�gono por v�rtices
	glBegin (GL_POLYGON);
	{
	    glTexCoord2f (0.0, 1.0);     // V�rtice 1 de la textura
	    glVertex3f (0.0, 0.0, 0.0);  // V�rtice 1 del pol�gono
	    
	    glTexCoord2f (1.0, 1.0);     // V�rtice 2 de la textura
	    glVertex3f (lx, 0.0, 0.0);   // V�rtice 2 del pol�gono
	    
	    glTexCoord2f (1.0, 0.0);     // V�rtice 3 de la textura
	    glVertex3f (lx, ly, 0.0);    // V�rtice 3 del pol�gono	       

	    glTexCoord2f (0.0, 0.0);     // V�rtice 4 de la textura
	    glVertex3f (0.0, ly, 0.0);   // V�rtice 4 del pol�gono       
	}
	glEnd ();
	
	// Desactivaci�n de la transparencia
	glDisable (GL_BLEND);

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);
    }
    glPopMatrix ();
}

/***************************************************************************/

// M�todo que dibuja un cubo 3D en OpenGL utilizando tres tipos de texturas
void EntornoG::GL_cubo (float x, float y, float lx, float ly, float lz, 
			uchar *imagen1, uchar *imagen2, uchar *imagen3, 
			int ancho1, int alto1, int ancho2, int alto2, 
			int ancho3, int alto3)
{
    glPushMatrix ();
    {
	// Posici�n del cubo
	glTranslatef (x, y, 0.0);

	// Rotaci�n del cubo
	glRotatef (90.0, 1.0, 0.0, 0.0);

	// Activaci�n de la textura para la cara delantera
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho1, alto1, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen1);

	// Dibujo de la cara delantera por v�rtices
	glBegin (GL_QUADS); 
	{
	    glTexCoord2f (0.0, 1.0);     // V�rtice 1 de la textura
	    glVertex3f (0.0, 0.0, 0.0);  // V�rtice 1 del pol�gono

	    glTexCoord2f (1.0, 1.0);     // V�rtice 2 de la textura
	    glVertex3f (lx, 0.0, 0.0);   // V�rtice 2 del pol�gono

	    glTexCoord2f (1.0, 0.0);     // V�rtice 3 de la textura
	    glVertex3f (lx, ly, 0.0);    // V�rtice 3 del pol�gono

	    glTexCoord2f (0.0, 0.0);     // V�rtice 4 de la textura
	    glVertex3f (0.0, ly, 0.0);   // V�rtice 4 del pol�gono
	}
	glEnd ();

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);

	// Activaci�n de la textura para la cara trasera
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho2, alto2, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen2);

	// Dibujo de la cara trasera por v�rtices
	glBegin (GL_QUADS);  
	{
	    glTexCoord2f (0.0, 1.0);    // V�rtice 1 de la textura
	    glVertex3f (lx, 0.0, lz);   // V�rtice 1 del pol�gono

	    glTexCoord2f (1.0, 1.0);    // V�rtice 2 de la textura
	    glVertex3f (0.0, 0.0, lz);  // V�rtice 2 del pol�gono
	    
	    glTexCoord2f (1.0, 0.0);    // V�rtice 3 de la textura
	    glVertex3f (0.0, ly, lz);   // V�rtice 3 del pol�gono

	    glTexCoord2f (0.0, 0.0);    // V�rtice 4 de la textura
	    glVertex3f (lx, ly, lz);    // V�rtice 4 del pol�gono
	}
	glEnd ();

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);

	// Activaci�n de la textura para la cara lateral izquierda
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho2, alto2, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen2);

	// Dibujo de la cara lateral izquierda por v�rtices
	glBegin (GL_QUADS);  
	{	
	    glTexCoord2f (0.0, 1.0);       // V�rtice 1 de la textura
	    glVertex3f (0.0, 0.0, lz);     // V�rtice 1 del pol�gono 

	    glTexCoord2f (1.0, 1.0);       // V�rtice 2 de la textura
	    glVertex3f (0.0, 0.0,  0.0);   // V�rtice 2 del pol�gono

	    glTexCoord2f (1.0, 0.0);       // V�rtice 3 de la textura
	    glVertex3f (0.0, ly, 0.0);     // V�rtice 3 del pol�gono 

	    glTexCoord2f (0.0, 0.0);       // V�rtice 4 de la textura
	    glVertex3f (0.0, ly, lz);      // V�rtice 4 del pol�gono 
	}
	glEnd();

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);

	// Activaci�n de la textura para la cara lateral derecha
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho2, alto2, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen2);
	
	// Dibujo de la cara lateral derecha por v�rtices
	glBegin (GL_QUADS);  
	{	
	    glTexCoord2f (0.0, 1.0);       // V�rtice 1 de la textura
	    glVertex3f (lx, 0.0,  0.0);    // V�rtice 1 del pol�gono

	    glTexCoord2f (1.0, 1.0);       // V�rtice 2 de la textura
	    glVertex3f (lx, 0.0, lz);      // V�rtice 2 del pol�gono

	    glTexCoord2f (1.0, 0.0);       // V�rtice 3 de la textura
	    glVertex3f (lx, ly, lz);       // V�rtice 3 del pol�gono

	    glTexCoord2f (0.0, 0.0);       // V�rtice 4 de la textura
	    glVertex3f (lx, ly, 0.0);      // V�rtice 4 del pol�gono
	}
	glEnd ();

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);

	// Activaci�n de la textura para la cara de arriba
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho3, alto3, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen3);

	// Dibujo de la cara de arriba por v�rtices
	glBegin (GL_QUADS);  
	{ 
	    glTexCoord2f (0.0, 1.0);       // V�rtice 1 de la textura
	    glVertex3f (0.0, ly, 0.0);     // V�rtice 1 del pol�gono

	    glTexCoord2f (1.0, 1.0);       // V�rtice 2 de la textura
	    glVertex3f (lx, ly, 0.0);      // V�rtice 2 del pol�gono

	    glTexCoord2f (1.0, 0.0);       // V�rtice 3 de la textura
	    glVertex3f (lx, ly, lz);       // V�rtice 3 del pol�gono

	    glTexCoord2f (0.0, 0.0);       // V�rtice 4 de la textura
	    glVertex3f (0.0, ly, lz);      // V�rtice 4 del pol�gono
	}
	glEnd ();	

	// Desactivaci�n de la textura
	glDisable (GL_TEXTURE_2D);
    }
    glPopMatrix ();
}

/***************************************************************************/

// M�todo que implementa la funci�n de inicializaci�n de SDL
void EntornoG::SDL_init (void)
{
    // Inicializaci�n de SDL
    if (SDL_Init (SDL_INIT_VIDEO) == -1)
    {
	fprintf (stderr, "entornoG.cc: SDL_init (void): ");
	fprintf (stderr, "No se puede iniciar SDL\n");
	exit (-1);
    }

    // Inicializaci�n de la ventana
    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 32, MASK);  
    SDL_WM_SetCaption (this->titulo, NULL);
    SDL_WM_SetIcon(IMG_Load (this->icono), NULL);

    // Definici�n del retardo de las teclas
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

/***************************************************************************/

/* M�todo que implementa la funci�n asociada al evento de pulsar una tecla
   Devuelve la acci�n realizada */
int EntornoG::SDL_key (int evento, int *entrada)
{
    int indiceP, opcion, accion = 0;

    // Inicializaci�n de par�metros
    *entrada = 0;
    this->posx = this->inix;
    this->posy = this->iniy;

    // Comprobaci�n de los movimientos
    switch (evento)
    {
	// Movimiento arriba
	case SDLK_UP:
	{
	    // Si el men� de acciones est� a 1
	    if (this->menuAccStatus == 1)
	    {
		if (this->posAccion < -11)
		{
		    this->posAccion += 4;

		    // Acci�n de visualizaci�n de men�s
		    accion = 26;
		}
	    }

	    // Si el men� de acciones est� a 0
	    else
	    {
		// Si el cursor est� a 0
		if (this->cursorStatus == 0)
		{		
		    // Incremento de la posici�n y del personaje activo
		    this->posy++;

		    // Actualizaci�n del flag de entrada a 1
		    *entrada = 1;

		    // Acci�n de movimiento del personaje activo
		    accion = 1;
		}

		// Si el cursor est� a 1
		else
		    // Comprobaci�n de que el cursor sea adyacente al personaje
		    if (((this->cursory + 1) <= (this->posy + 1)) && 
			(this->cursorx == this->posx))
		    {
			// Incremento de la posici�n y del cursor
			this->cursory++;

			// Acci�n de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Movimiento abajo
	case SDLK_DOWN:
	{
	    // Si el men� de acciones est� a 1
	    if (this->menuAccStatus == 1)
	    {
		if (this->posAccion > -27)
		{		
		    this->posAccion -= 4;

		    // Acci�n de visualizaci�n de men�s
		    accion = 26;
		}
	    }

	    // Si el men� de acciones est� a 0
	    else
	    {
		// Si el cursor est� a 0
		if (this->cursorStatus == 0)
		{
		    // Decremento de la posici�n y del personaje activo
		    this->posy--;

		    // Acci�n de movimiento
		    accion = 1;
		}

		// Si el cursor est� a 1
		else
		    // Comprobaci�n de que el cursor sea adyacente al personaje
		    if (((this->cursory - 1) >= (this->posy - 1)) &&
			(this->cursorx == this->posx))
		    {
			// Decremento de la posici�n y del cursor
			this->cursory--;
			
			// Acci�n de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Movimiento izquierda
	case SDLK_LEFT:
	{
	    // Si el men� de acciones est� a 0
	    if (this->menuAccStatus == 0)
	    {
		// Si el cursor est� a 0
		if (this->cursorStatus == 0)
		{
		    // Decremento de la posici�n x del personaje activo
		    this->posx--;
		    
		    // Acci�n de movimiento
		    accion = 1;
		}

		// Si el cursor est� a 1
		else
		    // Comprobaci�n de que el cursor sea adyacente al personaje
		    if (((this->cursorx - 1) >= (this->posx - 1)) &&
			(this->cursory == this->posy))
		    {  
			// Decremento de la posici�n x del cursor
			this->cursorx--;
			
			// Acci�n de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Movimiento derecha
	case SDLK_RIGHT:
	{
	    // Si el men� de acciones est� a 0
	    if (this->menuAccStatus == 0)
	    {
		// Si el cursor est� a 0
		if (this->cursorStatus == 0)
		{
		    // Incremento de la posici�n x del personaje activo
		    this->posx++;

		    // Acci�n de movimiento
		    accion = 1;
		}

		// Si el cursor est� a 1
		else
		    // Comprobaci�n de que el cursor sea adyacenta al personaje
		    if (((this->cursorx + 1) <= (this->posx + 1)) &&
			(this->cursory == this->posy))
		    {
			// Incremento de la posici�n x del cursor
			this->cursorx++;
			
			// Acci�n de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Tecla Espacio
	case SDLK_SPACE:
	{
	    // Si el men� de acciones est� a 0
	    if (this->menuAccStatus == 0)
	    {
		// Cambio del estado del cursor
		this->cursorStatus = 1 - this->cursorStatus;
		
		// Si ha cambiado a 0
		if (this->cursorStatus == 0)
		{
		    // Asignaci�n de la posici�n del cursor al personaje activo
		    this->cursorx = this->posx;
		    this->cursory = this->posy;
		}

		// Acci�n de movimiento de cursor
		accion = 2;
	    }

	    break;
	}

	// Tecla Return
	case SDLK_RETURN:
	{
	    // Si el men� de acciones est� a 1
	    if (this->menuAccStatus == 1)
	    {
		// Men� de acciones a 0
		this->menuAccStatus = 0;

		// Obtenci�n de la opci�n del men�
		if (this->posAccion == -11)
		    opcion = 0;

		else if ((this->posAccion == -15) && 
			 (this->topePosAccion != -15))
		    opcion = 1;

		else if ((this->posAccion == -19) &&
			 (this->topePosAccion != -19))
		    opcion = 2;
		
		else if ((this->posAccion == -23) &&
			 (this->topePosAccion != -23))
		    opcion = 3;

		else
		    opcion = -1;

		// Obtenci�n de la acci�n
		if (opcion != -1)
		    accion = this->accionActual + opcion;

		else
		{
		    // Asignaci�n de la posici�n del cursor al personaje activo
		    this->cursorx = this->posx;
		    this->cursory = this->posy;

		    // Acci�n de movimiento del cursor
		    accion = 2;
		}
	    }
	    
	    // Si el men� de acciones est� a 0
	    else
	    {		
		// Obtenci�n del �ndice del cliente
		indiceP = obtieneIndice (this->listaP, this->sock);

		// Obtenci�n del men�
		this->accionActual = obtieneAccion (this->cursorx, 
						    this->cursory, 
						    this->listaEdificios,
						    this->listaObjetos,
						    this->listaP, indiceP,
						    this->listaCasillas,
						    this->cursorStatus);
		// Si hay men�
		if (this->accionActual != -1)
		{
		    // Cambio del estado del men� de acciones
		    this->menuAccStatus = 1;
		    
		    // Inicializaci�n de la opci�n del men�
		    this->posAccion = -11;
		    
		    // Obtenci�n del l�mite superior del men�
		    if (((this->accionActual > 4) && (this->accionActual < 13))
			|| ((this->accionActual >= 24) && 
			    (this->accionActual < 26)))
			
			    this->topePosAccion = -15;

		    else if (this->accionActual == 4)
			this->topePosAccion = -19;

		    else if ((this->accionActual == 13) || 
			     (this->accionActual == 20))
			this->topePosAccion = -27;
		    
		    else
			this->topePosAccion = -23;

		    // Acci�n de visualizaci�n de men�s
		    accion = 26;
		}

		// Si no hay men�
		else
		{
		    // Si el cursor est� a 0
		    if (cursorStatus == 0)
			
			// Acci�n de paso de turno
			accion = 3;

		    else
		    {
			// Asignaci�n de la posici�n del cursor
			this->cursorx = this->posx;
			this->cursory = this->posy;
		
			// Acci�n de movimiento de cursor
			accion = 2;
		    }
		}

		// Si el cursor est� a 1
		if (this->cursorStatus == 1)
		{
		    // Cambio del cursor a 0
		    this->cursorStatus = 0;
		}
	    }

	    break;
	}

	// Tecla Crtl-Derecho
	case SDLK_RCTRL:
	{
	    // Cambio del estado del cuadro de caracter�sticas
	    this->caractStatus = 1 - this->caractStatus;
	    
	    // Acci�n de visualizaci�n de men�s
	    accion = 26;

	    break;
	}

	// Tecla Escape
	case SDLK_ESCAPE:
	{
	    // Acci�n de desconexi�n
	    accion = -1;

	    break;
	}
    }

    return accion;
}

/***************************************************************************/

/* M�todo que carga las dimensiones del mundo a trav�s de los datos 
   enviados desde elservidor */
void EntornoG::cargaTamanoMundo (void)
{
    this->mundoInf = recibeEnteroDeServidor (this->conexion);
    this->mundoSup = recibeEnteroDeServidor (this->conexion);
    this->castilInf = recibeEnteroDeServidor (this->conexion);
    this->castilSup = recibeEnteroDeServidor (this->conexion);
    this->casaInf = recibeEnteroDeServidor (this->conexion);
    this->casaSup = recibeEnteroDeServidor (this->conexion);
}

/***************************************************************************/

/* M�todo que carga las estructuras del mundo con los datos recibidos a 
   trav�s del servidor y devuelve el �ndice donde se encuentra el personaje
   activo */
int EntornoG::cargaMundo (int env)
{    
    Edificio *unEdificio;
    Objeto *unObjeto;
    Personaje *unPersonaje;
    Elemento *unElemento;
    Casilla *unaCasilla;
    int indiceP, nAtributos, atributo, tamanoEqu;

    // Recepci�n del socket del cliente
    this->sock = recibeEnteroDeServidor (this->conexion);

    // Si el cliente no existe
    if (this->sock == -1)
	return -1;

    // Recepci�n de la posici�n del cursor
    this->cursorx = recibeEnteroDeServidor (this->conexion);
    this->cursory = recibeEnteroDeServidor (this->conexion);

    // Reserva de memoria para la lista de objetos
    this->listaObjetos = new Lista<Objeto*> ();
    if (this->listaObjetos == NULL)
    {
	fprintf (stderr, "entornoG.cc:: cargaMundo (void) :");
	fprintf (stderr, "Memoria insuficiente para listaObjetos\n");
	exit (-1);
    }

    // Recepci�n del tama�o de la lista de objetos
    this->tamanoObjetos = recibeEnteroDeServidor (this->conexion);
    
    // Recepci�n de cada uno de los objetos y su reconstrucci�n 
    for (int i = 0; i < this->tamanoObjetos; i++)
    {		
	// Creaci�n del objeto
	unObjeto = new Objeto ();

	// Obtenci�n del n�mero de atributos de cada objeto
	nAtributos = unObjeto->obtieneNAtributos ();

	// Recepci�n de cada uno de los atributos  
	for (int j = 1; j <= nAtributos; j++)
	{
	    // Recepci�n del atributo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignaci�n del atributo
	    unObjeto->reAsignaAtributo (j, atributo); 
	}
		
	// Inserci�n del objeto en la lista
	this->listaObjetos->insertaElemento (unObjeto);
    }	    	

    // Reserva de memoria para la lista de personajes
    this->listaP = new Lista<Personaje*> ();
    if (this->listaP == NULL)
    {
	fprintf (stderr, "entornoG.cc:: cargaMundo (void) :");
	fprintf (stderr, "Memoria insuficiente para listaP\n");
	exit (-1);
    }

    // Recepci�n del tama�o de la lista de personajes
    this->tamanoP = recibeEnteroDeServidor (this->conexion);

    // Recepci�n de cada uno de los personajes y su reconstrucci�n 
    for (int i = 0; i < this->tamanoP; i++)
    {
	// Creaci�n del personaje
	unPersonaje = new Personaje ();
	
	// Obtenci�n del n�mero de atributos de cada personaje
	nAtributos = unPersonaje->obtieneNAtributos ();
	
	// Recepci�n de cada uno de los atributos
	for (int j = 1; j <= nAtributos; j++)
	{	    
	    // Recepci�n del atributo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignaci�n del atributo
	    unPersonaje->reAsignaAtributo (j, atributo);
	}
	
	// Obtenci�n del tama�o del equipo de cada personaje
	tamanoEqu = unPersonaje->obtieneTamEqu ();

	// Recepci�n de cada uno de los elementos del equipo
	for (int j = 0; j < tamanoEqu; j++)
	{
	    // Recepci�n del elemento del equipo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignaci�n del elemento del equipo
	    unPersonaje->reAsignaEqu (j, atributo);
	}

	// Inserci�n del personaje en la lista
	this->listaP->insertaElemento (unPersonaje);

	// Obtenci�n de los atributos del personaje activo
	if (unPersonaje->obtieneAtributo ("sock") == this->sock)
	{
	    // Posici�n (x,y) del personaje activo 
	    this->inix = unPersonaje->obtieneAtributo ("posx");
	    this->iniy = unPersonaje->obtieneAtributo ("posy");

	    // Edificio donde se encuentra el personaje activo
	    this->edif = unPersonaje->obtieneAtributo ("edif");

	    // Indice del personaje activo en la lista de personajes
	    indiceP = i;
	}
    }

    // Reserva de memoria para la lista de elementos
    this->listaElementos = new Lista<Elemento*> ();
    if (this->listaElementos == NULL)
    {
	fprintf (stderr, "entornoG.cc:: cargaMundo (void) :");
	fprintf (stderr, "Memoria insuficiente para listaElementos\n");
	exit (-1);
    }

    // Recepci�n del tama�o de la lista de elementos
    this->tamanoElementos = recibeEnteroDeServidor (this->conexion);

    // Recepci�n de cada uno de los elementos y su reconstrucci�n 
    for (int i = 0; i < this->tamanoElementos; i++)
    {
	// Creaci�n del elemento
	unElemento = new Elemento ();

	// Obtenci�n del n�mero de atributos de cada elemento
	nAtributos = unElemento->obtieneNAtributos ();

	// Recepci�n de cada uno de los atributos
	for (int j = 1; j <= nAtributos; j++)
	{
	    // Recepci�n del atributo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignaci�n del atributo
	    unElemento->reAsignaAtributo (j, atributo);
	}

	// Inserci�n del elemento en la lista
	this->listaElementos->insertaElemento (unElemento);
    }

    // Si el envio engloba a todo el mundo
    if (env == 2)
    {
	// Reserva de memoria para la lista de edificios
	this->listaEdificios = new Lista<Edificio*> ();
	if (this->listaEdificios == NULL)
	{
	    fprintf (stderr, "entornoG.cc:: cargaMundo (void) :");
	    fprintf (stderr, "Memoria insuficiente para listaEdificios\n");
	    exit (-1);
	}

	// Recepci�n del tama�o de la lista de edificios 
	this->tamanoEdificios = recibeEnteroDeServidor (this->conexion);
	
	// Recepci�n de cada uno de los edificios y su reconstrucci�n 
	for (int i = 0; i < this->tamanoEdificios; i++)
	{
	    // Creaci�n del edificio
	    unEdificio = new Edificio ();
	    
	    // Obtenci�n del n�mero de atributos de cada edificio
	    nAtributos = unEdificio->obtieneNAtributos ();
	    
	    // Recepci�n de cada uno de los atributos
	    for (int j = 1; j <= nAtributos; j++)
	    {
		// Recepci�n del atributo
		atributo = recibeEnteroDeServidor (this->conexion);
		
		// Asignaci�n del atributo
		unEdificio->reAsignaAtributo (j, atributo);
	    }
	    
	    // Inserci�n del edificio en la lista
	    this->listaEdificios->insertaElemento (unEdificio);
	}
	
	// Reserva de memoria para la lista de casillas
	this->listaCasillas = new Lista<Casilla*> ();
	if (this->listaCasillas == NULL)
	{
	    fprintf (stderr, "entornoG.cc:: cargaMundo (void) :");
	    fprintf (stderr, "Memoria insuficiente para listaCasillas\n");
	    exit (-1);
	}
	
	// Recepci�n del tama�o de la lista de casillas
	this->tamanoCasillas = recibeEnteroDeServidor (this->conexion);
	
	// Recepci�n de cada una de las casillas y su reconstrucci�n
	for (int i = 0; i < this->tamanoCasillas; i++)
	{
	    // Creaci�n de la casilla
	    unaCasilla = new Casilla ();
	    
	    // Obtenci�n del n�mero de atributos de cada casilla
	    nAtributos = unaCasilla->obtieneNAtributos ();
	    
	    // Recepci�n de cada uno de los atributos
	    for (int j = 1; j <= nAtributos; j++)
	    {
		// Recepci�n del atributo
		atributo = recibeEnteroDeServidor (this->conexion);
		
		// Asignaci�n del atributo
		unaCasilla->reAsignaAtributo (j, atributo);
	    }
	    
	    // Inserci�n de la casilla en la lista
	    this->listaCasillas->insertaElemento (unaCasilla);
	}
    }

    return indiceP;
}

/***************************************************************************/

// M�todo que carga las texturas del mundo en la lista de texturas
void EntornoG::cargaTexturas (void)
{
    Textura *unaTextura;
    char *cadena;
    int profundidad;

    // Reserva de memoria para la lista de texturas
    this->listaTexturas = new Lista<Textura*> ();
    if (this->listaTexturas == NULL)
    {
	fprintf (stderr, "entornoG.cc:: cargaTexturas (void) :");
	fprintf (stderr, "Memoria insuficiente para listaTexturas\n");
	exit (-1);
    }

    // Carga de las texturas de las casillas
    for (int i = 0; i < 6; i++)
    {
	cadena = obtieneFichero ("./texturas/casillas/", i, ".png");
	unaTextura = new Textura (cadena, RGB);
	this->listaTexturas->insertaElemento (unaTextura);
    }    

    // Carga de las texturas de los edificios
    for (int i = 0; i < 12; i++)
    {
	cadena = obtieneFichero ("./texturas/edificios/", i, ".png");

	unaTextura = new Textura (cadena, RGB);
	this->listaTexturas->insertaElemento (unaTextura);
    }    

    // Carga de las texturas de los personajes
    for (int i = 0; i < 5; i++)
    {
	cadena = obtieneFichero ("./texturas/personajes/", i, ".png");
	unaTextura = new Textura (cadena, RGBA);
	this->listaTexturas->insertaElemento (unaTextura);
    }

    // Carga de las texturas de los objetos
    for (int i = 0; i < 41; i++)
    {
	cadena = obtieneFichero ("./texturas/objetos/", i, ".png");

	if ((i == 20) || (i == 22) || (i == 39) || (i == 40))
	    profundidad = RGB;
	else
	    profundidad = RGBA;

	unaTextura = new Textura (cadena, profundidad);
	this->listaTexturas->insertaElemento (unaTextura);
    }

    // Actualizaci�n del tama�o
    this->tamanoTexturas = this->listaTexturas->obtieneTamano ();

    // Liberaci�n de recursos
    delete [] cadena;
}

/***************************************************************************/

// M�todo que env�a las coordenadas modificadas del personaje activo
void EntornoG::enviaCoordenadas (int accion, int entrada)
{
    // Si la acci�n es de movimiento del personaje
    if (accion == 1)
    {
	// Envio de las coordenadas del personaje activo y del flag de entrada
	enviaEnteroAServidor (this->conexion, this->posx);
	enviaEnteroAServidor (this->conexion, this->posy);
	enviaEnteroAServidor (this->conexion, entrada);
    }

    /* Si la acci�n es de movimiento del cursor o est� relacionada con alg�n
       elemento */
    else if ((accion == 2) || (accion == 4) || (accion == 5) || (accion == 7) 
	     || (accion == 8) || (accion == 10))
    {
	// Envio de las coordenadas del cursor
	enviaEnteroAServidor (this->conexion, this->cursorx);
	enviaEnteroAServidor (this->conexion, this->cursory);
    }
}

/***************************************************************************/

