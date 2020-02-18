
/***************************************************************************
                         entornoG.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
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

/* Constructor del objeto EntornoG que crea un entorno gráfico con los 
   parámetros especificados e inicializa las variables del entornoG */
EntornoG::EntornoG (char *titulo, char *icono, int ancho, int alto, 
		    int servidorIP)
{
    int tamano;

    // Inicialización de la ventana
    this->ventana = NULL;

    // Reserva de memoria del título de la ventana
    tamano = strlen (titulo);
    this->titulo = new char [tamano+1];
    if (this->titulo == NULL)
    {
	fprintf (stderr, "entornoG.cc::EntornoG ");
	fprintf (stderr, "(char*, char*, int, int): ");
	fprintf (stderr, "Memoria insuficiente para titulo\n");
	exit (-1);
    }

    // Asignación del título de la ventana
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

    // Asignación del nombre del icono de la ventana
    strcpy (this->icono, icono);

    // Asignación de la dimensión de la ventana
    this->ancho = ancho;
    this->alto = alto;

    // Inicialización de la conexión del cliente
    this->conexion = NULL;

    // Inicialización de la dirección IP del servidor
    this->servidorIP = servidorIP;

    // Inicialización de las dimensiones del mundo
    this->mundoInf = this->mundoSup = 0;
    this->castilInf = this->castilSup = 0;
    this->casaInf = this->casaSup = 0;

    // Inicialización de la lista de edificios
    this->listaEdificios = NULL;
    this->tamanoEdificios = 0;

    // Inicialización de la lista de objetos
    this->listaObjetos = NULL;
    this->tamanoObjetos = 0;

    // Inicialización de la lista de personajes
    this->listaP = NULL;
    this->tamanoP = 0;

    // Inicialización de la lista de elementos
    this->listaElementos = NULL;
    this->tamanoElementos = 0;

    // Inicialización de la lista de casillas
    this->listaCasillas = NULL;
    this->tamanoCasillas = 0;

    // Inicialización de la lista de texturas
    this->listaTexturas = NULL;
    this->tamanoTexturas = 0;

    // Inicialización de la posición (x,y) del personaje activo
    this->posx = 0;
    this->posy = 0;
    this->inix = 0;
    this->iniy = 0;

    // Inicialización del edificio donde se encuentra el personaje activo
    this->edif = -1;

    // Inicialización del estado del cursor
    this->cursorStatus = 0;

    // Inicialización de la posición (x,y) del cursor
    this->cursorx = 0;
    this->cursory = 0;

    // Inicialización del estado del cuadro de características
    this->caractStatus = 0;

    // Inicialización del estado del menú de acciones
    this->menuAccStatus = 0;

    // Inicialización de la posición de la acción del menú
    this->posAccion = 0;

    // Inicialización del límite superior del menú de acciones
    this->topePosAccion = 0;

    // Inicialización de la acción actual solicitada
    this->accionActual = -1;

    // Inicialización del socket
    this->sock = -1;

    // Inicialización del turno
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

// Método que inicia el entorno gráfico inicializando tanto OpenGL como SDL
void EntornoG::iniciaEntorno (void)
{
    this->SDL_init ();
    this->GL_init ();
}

/***************************************************************************/

// Método que implementa el bucle de eventos de SDL 
void EntornoG::visualizaEntorno (void)
{
    SDL_Event evento;
    int port, esp, tecla, accion, indiceP, entrada, env, hayEvento, turno = -1;

    // Carga de las texturas del mundo
    this->cargaTexturas ();

    // Visualizacion del menu de comienzo
    esp = this->visualizaMenuStart ();

    // Creación de la conexión del cliente
    this->conexion = new ConexionCliente (AF_INET, SOCK_STREAM, 0);

    // Conversión del puerto
    port = htons (50007);

    // Conexión del cliente
    this->conexion->conectaAServidor (AF_INET, this->servidorIP, port);

    // Envío de la especie del personaje activo al servidor
    enviaEnteroAServidor (this->conexion, esp);

    // Carga del tamaño del mundo
    this->cargaTamanoMundo ();
    
    // Bucle de visualización
    while (1)
    {
	// Recepción del flag de envío
	env = recibeEnteroDeServidor (this->conexion);
	
	// Recepción del turno
	this->turno = recibeEnteroDeServidor (this->conexion);		

	// Si el flag de envío está activo
	if (env > 0)
	{
	    // Carga del mundo
	    indiceP = this->cargaMundo (env);

	    // Si el personaje activo no existe
	    if (indiceP == -1)
	    {
		// Envío del flag de desconexión
		enviaEnteroAServidor (this->conexion, -1);

		// Retardo
		sleep (1);

		// Cierre
		this->visualizaOver ();
	    }

	    // Visualización
	    this->GL_display (indiceP);
	    SDL_GL_SwapBuffers ();		    	    
	}

	if (this->turno != turno)
	{
	    // Actualización del turno
	    turno = this->turno;

	    // Visualización
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
		    // Inicialización de la ventana
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		
		    // Visualización
		    this->GL_display (indiceP);
		    SDL_GL_SwapBuffers ();		
		    
		    break;
		}
	     
		// Evento redimensionar aplicación
		case SDL_VIDEORESIZE:
		{
		    // Inicialización de la ventana redimensionada
		    this->ancho = evento.resize.w;
		    this->alto = evento.resize.h;
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		    
		    // Visualización
		    this->GL_display (indiceP);
		    SDL_GL_SwapBuffers ();
		    
		    break;		
		}
		
		// Evento pulsar tecla 
		case SDL_KEYDOWN:
		{
		    // Obtención de la tecla pulsada
		    tecla = evento.key.keysym.sym;
		    
		    // Obtención de la acción asociada a la tecla
		    accion = this->SDL_key (tecla, &entrada);
		    		    
		    // Si le toca el turno o es una acción sin turno
		    if ((this->sock == this->turno) || (accion == -1) || 
			(accion == 26))
		    {
			// Envío de la accion
			enviaEnteroAServidor (this->conexion, accion);

			// Envío al servidor de las coordenadas modificadas
			this->enviaCoordenadas (accion, entrada);

			// Si la acción es de desconexión
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
		
		// Evento cerrar aplicación
		case SDL_QUIT:
		{		  
		    // Envío del flag de desconexión
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

// Método que visualiza una pantalla de inicio con selección de opciones
int EntornoG::visualizaMenuStart (void)
{
    SDL_Event evento;
    int tecla, esp, posOpcion;

    // Inicializacion de parametros
    esp = -1;
    posOpcion = 3;

    // Bucle de visualización
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
		    // Inicialización de la ventana
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		
		    // Visualización
		    this->GL_displayMenuStart (posOpcion);
		    SDL_GL_SwapBuffers ();		
		    
		    break;
		}
	     
		// Evento redimensionar aplicación
		case SDL_VIDEORESIZE:
		{
		    // Inicialización de la ventana redimensionada
		    this->ancho = evento.resize.w;
		    this->alto = evento.resize.h;
		    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						      32, MASK);
		    this->GL_reshape (this->ancho, this->alto);
		    
		    // Visualización
		    this->GL_displayMenuStart (posOpcion);
		    SDL_GL_SwapBuffers ();
		    
		    break;		
		}
		
		// Evento pulsar tecla 
		case SDL_KEYDOWN:
		{
		    // Obtención de la tecla pulsada
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

		    // Visualización
		    this->GL_displayMenuStart (posOpcion);
		    SDL_GL_SwapBuffers ();

		    break;
		}
		
		// Evento cerrar aplicación
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

// Método que visualiza una pantalla de fin
void EntornoG::visualizaOver (void)
{
    SDL_Event evento;
    int tecla;

    // Inicialización de la ventana
    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 32, MASK);
    this->GL_reshape (this->ancho, this->alto);
    
    // Visualización
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
		// Inicialización de la ventana
		this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						  32, MASK);
		this->GL_reshape (this->ancho, this->alto);
		
		// Visualización
		this->GL_displayOver ();
		SDL_GL_SwapBuffers ();		
		
		break;
	    }
	     
	    // Evento redimensionar aplicación
	    case SDL_VIDEORESIZE:
	    {
		// Inicialización de la ventana redimensionada
		this->ancho = evento.resize.w;
		this->alto = evento.resize.h;
		this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 
						  32, MASK);
		this->GL_reshape (this->ancho, this->alto);
		    
		// Visualización
		this->GL_displayOver ();
		SDL_GL_SwapBuffers ();
		    
		break;		
	    }
		
	    // Evento pulsar tecla 
	    case SDL_KEYDOWN:
	    {
		// Obtención de la tecla pulsada
		tecla = evento.key.keysym.sym;
		
		// Cierre
		if (tecla == SDLK_ESCAPE)
		{
		    SDL_Quit ();
		    exit (0);					
		}
		
		break;
	    }
		
	    // Evento cerrar aplicación
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

// Método que implementa la función de inicialización de OpenGL
void EntornoG::GL_init (void)
{
    // Técnica de coloreado 
    glShadeModel (GL_FLAT);

    // Activación del Z-buffer (profundidad)
    glDepthFunc (GL_LEQUAL);
    glEnable (GL_DEPTH_TEST);
    
    // Definición de todos los poligonos del mismo modo (rellenos)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // para ambos lados

    // La textura tanto en la dirección S como en T se repite
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // La aplicación del texel al centro del pixel se hace utilizando medias
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Se permite aplicar efectos a la textura
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/***************************************************************************/

// Método que implementa la función de redimensionado de OpenGL
void EntornoG::GL_reshape (int ancho, int alto)
{
    // Definición del viewport
    glViewport (0, 0, (GLint) ancho, (GLint) alto);

    // Carga de la matriz para la proyección
    glMatrixMode (GL_PROJECTION);

    // Carga de la matriz identidad
    glLoadIdentity ();

    // Definición de la proyección
    gluPerspective (45, (float) ancho / (float) alto, 0.1, 100);

    // Carga de la matriz de modelo 
    glMatrixMode (GL_MODELVIEW);   
}

/***************************************************************************/

// Método que implementa la función de dibujado de OpenGL
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

    // Posición de la cámara
    glTranslatef (0.0, 0.0, -7.0);

    glPushMatrix ();
    {
	// Inclinación 45 grados
	glRotatef (-45, 1, 0, 0);
    
	// Desplazamiento del mundo en cada movimiento
	glTranslatef (0.0, -this->iniy, 0.0); 
	glTranslatef (-this->inix, 0.0, 0.0);        
    
	// Dibujo de las casillas del mundo
	if (this->edif == -1)         
	{    	
	    // Obtención del tipo de muro
	    tipoMuro = -1;
	    
	    for (int i = 0; i < this->tamanoCasillas; i++)
	    {
		// Obtención de la casilla
		unaCasilla = this->listaCasillas->obtieneElemento (i);
		
		// Obtención de la posición (x,y) de la casilla
		x = unaCasilla->obtieneAtributo ("posx");
		y = unaCasilla->obtieneAtributo ("posy");
		
		// Obtención del tipo de la casilla	
		tipo = unaCasilla->obtieneAtributo ("tipo");
		
		// Dibujo de la casilla en función de su tipo
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
	    // Obtención del tipo de muro
	    tipoMuro = 17;
	    
	    // Obtención de la textura
	    unaTextura = this->listaTexturas->obtieneElemento (5);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    
	    // Obtención de los límites
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
	    // Obtención del tipo de muro
	    tipoMuro = 16;
	    
	    // Obtención de la textura
	    unaTextura = this->listaTexturas->obtieneElemento (4);
	    imagen = unaTextura->obtienePixels ();
	    ancho = unaTextura->obtieneAncho ();
	    alto = unaTextura->obtieneAlto ();
	    
	    // Obtención de los límites
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
		// Obtención del edificio
		unEdificio = this->listaEdificios->obtieneElemento (i);
		
		// Obtención de la posición (x,y) del edificio
		x = unEdificio->obtieneAtributo ("posx");
		y = unEdificio->obtieneAtributo ("posy");
		
		// Obtención de la longitud (x,y) del edificio
		lx = unEdificio->obtieneAtributo ("longx");
		ly = unEdificio->obtieneAtributo ("longy");
		
		// Obtención del tipo de edificio
		tipo = unEdificio->obtieneAtributo ("tipo");
		
		// Dibujo del edificio en función de su tipo
		if (tipo == 0)	// Castillo
		{
		    /* Asignación de los índices para la fachada, pared y 
		       tejado */
		    fachada = 8;
		    pared = 9;
		    tejado = 6;
		}
		
		else if (tipo == 1) // Posada	
		{
		    /* Asignación de los índices para la fachada, pared y 
		       tejado */
		    fachada = 10;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 2) // Biblioteca
		{
		    /* Asignación de los índices para la fachada, pared y 
		       tejado */
		    fachada = 11;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 3) // Armas
		{
		    /* Asignación de los índices para la fachada, pared y 
		       tejado */
		    fachada = 12;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 4) // Escudos
		{
		    /* Asignación de los índices para la fachada, pared y 
		       tejado */
		    fachada = 13;
		    pared = 15;
		    tejado = 7;
		}
		
		else if (tipo == 5) // Armaduras
		{
		    /* Asignación de los índices para la fachada, pared y 
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
	    // Obtención del elemento ordenado
	    unElemento = this->listaElementos->obtieneElemento (i);
	    
	    // Obtención del tipo de elemento
	    tipo = unElemento->obtieneAtributo ("tipo");
	    
	    // Obtención del índice del elemento
	    posicion = unElemento->obtieneAtributo ("posicion");
	    
	    // Personajes
	    if (tipo == 0)	    
	    {
		// Obtención del personaje
		unPersonaje = this->listaP->obtieneElemento (posicion);
		
		// Obtención de la posición (x,y) del personaje
		x = unPersonaje->obtieneAtributo ("posx");
		y = unPersonaje->obtieneAtributo ("posy");
		
		// Obtención de la especie del personaje
		especie = unPersonaje->obtieneAtributo ("esp");
		
		// Obtención de la textura asociada a la especie del personaje
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
		// Obtención del objeto
		unObjeto = this->listaObjetos->obtieneElemento (posicion);
		
		// Obtención de la visibilidad del objeto
		visible = unObjeto->obtieneAtributo ("visi");
		
		// Si es visible
		if (visible == 1)
		{
		    // Obtención de la posición (x,y) del objeto
		    x = unObjeto->obtieneAtributo ("posx");
		    y = unObjeto->obtieneAtributo ("posy");
		    
		    // Obtención de la longitud (x,y) del objeto
		    lx = unObjeto->obtieneAtributo ("longx");
		    ly = unObjeto->obtieneAtributo ("longy");
		    
		    // Obtención del tipo del objeto
		    tipo = unObjeto->obtieneAtributo ("tipo");
		    
		    // Obtención de la textura asociada al tipo del objeto
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

    // Dibujo de las características del personaje
    if (this->caractStatus == 1)    
	this->GL_caracteristicas (indiceP);
    
    // Dibujo del menú de acciones
    if (this->menuAccStatus == 1)
	this->GL_menuAcciones ();
}

/***************************************************************************/

// Método que implementa la función de dibujado de una pantalla de inicio
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

    // Posición de la cámara
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

// Método que implementa la función de dibujado de una pantalla de fin
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

    // Posición de la cámara
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

// Método que dibuja una flecha indicadora en la posición señalada
void EntornoG::GL_cursor (float x, float y)
{
    glPushMatrix ();
    {	    
	// Desactivación del Z-buffer (profundidad)
	glDisable (GL_DEPTH_TEST);

	// Posición del cursor
	glTranslatef (x, y, 0.0);

	// Rotación del cursor
	glRotatef (90.0, 1.0, 0.0, 0.0);

	// Si el cursor está a 0
	if (this->cursorStatus == 0)
	    glColor3f (1.0, 0.0, 0.0); // Color Rojo 

	// Si el cursor está a 1
	else
	    glColor3f (0.0, 1.0, 0.0); // Color Verde

	// Dibujo del cursor por vértices
	glBegin (GL_POLYGON);
	{	    
	    glVertex3f (0.65, 1.5, 0.0);  // Vértice 1
	    glVertex3f (0.25, 1.5, 0.0);  // Vértice 2
	    glVertex3f (0.45, 1.3, 0.0);  // Vértice 3
	}
	glEnd ();
	glColor3f (1.0, 1.0, 1.0);

	// Activación del Z-buffer (profundidad)
	glEnable (GL_DEPTH_TEST);
    }
    glPopMatrix ();    
}

/***************************************************************************/

/* Método que dibuja un poligono semitransparente en OpenGL con un texto 
   asociado a las características del personaje activo */
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

    // Obtención del personaje
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
    
    // Obtención de las habilidades
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
    
    // Obtención del equipo
    escudo = unPersonaje->obtieneEqu (0);
    arma = unPersonaje->obtieneEqu (1);
    armadura = unPersonaje->obtieneEqu (2);
    monedas = unPersonaje->obtieneEqu (3);
    llave = unPersonaje->obtieneEqu (4);
    pocion = unPersonaje->obtieneEqu (5);       	

    glPushMatrix ();
    {
	// Desactivación del Z-buffer (profundidad)
	glDisable (GL_DEPTH_TEST);

	// Carga de la textura del polígono semitransparente
	unaTextura = new Textura ("./texturas/menus/fondo.png", RGBA);    
	imagen = unaTextura->obtienePixels ();
	ancho = unaTextura->obtieneAncho ();
	alto = unaTextura->obtieneAlto ();
	
	// Dibujo del polígono semitransparente
	GL_poligonoT (1.5, 3.0, 4.0, -6.0, imagen, ancho, alto, 0.0);
	
	// Inicialización de la fuente
	glfInit ();
	
	// Carga de la fuente
	glfLoadFont ("./fonts/arial1.glf");
	
	// Activación de contorno
	glfEnable (GLF_CONTOURING);
	
	// Distancia entre los caracteres
	glfSetSymbolSpace(0.3);
	
	// Tamaño del texto
	glScalef (0.1, 0.1, 0.1);
	
	// Inicialización de las coordenadas del texto
	x = 20.0;
	y = 25.0;
	z = 4.0;
	
	// Impresión de los pg
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y, z, "P.Golpe:");
	
	cad1 = itoa (pg);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxpg);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y, z, cad1);
	
	// Impresión de la energía
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-2, z, "Energia:");
	
	cad1 = itoa (ene);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxene);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y-2, z, cad1);
	
	// Impresión del hambre
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-4, z, "Hambre:");
	
	cad1 = itoa (ham);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxham);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y-4, z, cad1);
	
	// Impresión de la sed
	glfSetContourColor(0.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-6, z, "Sed:");
	
	cad1 = itoa (sed);
	cad1 = strcat (cad1, "/");
	cad2 = itoa (maxsed);
	cad1 = strcat (cad1, cad2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+9, y-6, z, cad1);
	
	// Impresión de la fuerza
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-9, z, "Fue:");
	
	cad1 = itoa (fue);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-9, z, cad1);
	
	// Impresión de la constitución
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-11, z, "Con:");
	
	cad1 = itoa (con);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-11, z, cad1);
	
	// Impresión del tamaño
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-13, z, "Tam:");
	
	cad1 = itoa (tam);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-13, z, cad1);
	
	// Impresión de la inteligencia
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-15, z, "Inte:");
	
	cad1 = itoa (inte);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-15, z, cad1);
	
	// Impresión de la destreza
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-17, z, "Des:");
	
	cad1 = itoa (des);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-17, z, cad1);
	
	// Impresión del sigilo
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-19, z, "Sigilo:");
	
	cad1 = itoa (mh1);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-19, z, cad1);
	
	// Impresión de la percepción
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-21, z, "Percepc:");
	
	cad1 = itoa (mh2);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-21, z, cad1);
	
	// Impresión del número de estudios
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-23, z, "N.Estu:");
	
	cad1 = itoa (estu);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-23, z, cad1);
	
	// Impresión del número de entrenamientos
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-25, z, "N.Entr:");
	
	cad1 = itoa (entr);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-25, z, cad1);
	
	// Impresión de la misión
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-27, z, "Mision:");
	
	cad1 = itoa (obj);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-27, z, cad1);
	
	// Impresión del momento de reacción
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-29, z, "M.Reacc:");
	
	cad1 = itoa (mmr);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-29, z, cad1);
	
	// Impresión del número de turnos
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-31, z, "N.Turnos:");
	
	cad1 = itoa (nturnos);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-31, z, cad1);
	
	// Impresión de la armadura
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
	
	// Impresión del arma
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
	
	// Impresión del escudo
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
	
	// Impresión de la llave
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
	
	// Impresión de las monedas
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-45, z, "Monedas:");
	
	cad1 = itoa (monedas);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-45, z, cad1);
	
	// Impresión de la poción
	glfSetContourColor(1.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y-47, z, "Pocion:");
	
	if (pocion != -1)
	{
	    cad1 = itoa (pocion);
	    glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	    this->GL_imprimeTexto (x+12, y-47, z, cad1);
	}
	
	// Impresión del turno
	glfSetContourColor(1.0, 0.0, 0.0, 0.0);
	this->GL_imprimeTexto (x, y-50, z, "Turno:");
	
	cad1 = itoa (this->turno);
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);
	this->GL_imprimeTexto (x+12, y-50, z, cad1);
	
	// Descarga de la fuente
	glfUnloadFont ();
	    
	// Cierre de la libería de fuentes
	glfClose ();

	// Activación del Z-buffer (profundidad)
	glEnable (GL_DEPTH_TEST);

	// Liberación de las cadenas de caracteres
	delete [] cad1;
	delete [] cad2;
    }
    glPopMatrix ();
}

/***************************************************************************/

/* Método que dibuja un polígono semitransparente en OpenGL con un menú
   de acciones */
void EntornoG::GL_menuAcciones (void)
{
    Textura *unaTextura;
    uchar *imagen;
    float x, y, z;
    int ancho, alto;

    glPushMatrix ();
    {
	// Desactivación del Z-buffer (profundidad)
	glDisable (GL_DEPTH_TEST);
	
	// Carga de la textura del polígono semitransparente
	unaTextura = new Textura ("./texturas/menus/fondo.png", RGBA);    
	imagen = unaTextura->obtienePixels ();
	ancho = unaTextura->obtieneAncho ();
	alto = unaTextura->obtieneAlto ();
	
	// Dibujo del polígono semitransparente
	GL_poligonoT (-2.0, 0.0, 3.5, -4.0, imagen, ancho, alto, 0.0);
	
	// Inicialización de la fuente
	glfInit ();
	
	// Carga de la fuente
	glfLoadFont ("./fonts/arial1.glf");
	
	// Activación de contorno
	glfEnable (GLF_CONTOURING);
	
	// Distancia entre los caracteres
	glfSetSymbolSpace(0.3);

        // Tamaño del texto
	glScalef (0.1, 0.1, 0.1);

        // Inicialización de las coordenadas del texto
	x = -13.0;
	y = -5.0;
	z = 4.0;

	// Impresión del texto inicial
	glfSetContourColor(0.0, 1.0, 1.0, 0.0);
	this->GL_imprimeTexto (x, y, z, "Accion a realizar?");
	glfSetContourColor(1.0, 1.0, 0.0, 0.0);

	// Impresión de las acciones del personaje
	if (this->accionActual == 4)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Atacar personaje");
	    this->GL_imprimeTexto (x, y-8, z, "Robar personaje");
	    this->GL_imprimeTexto (x, y-12, z, "Salir");
	}

	// Impresión de las acciones de comer setas
	else if (this->accionActual == 6)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comer setas");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de comer miel
	else if (this->accionActual == 7)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comer miel");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de abrir cofre
	else if (this->accionActual == 8)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Abrir cofre");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de aceptar misión
	else if (this->accionActual == 9)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Aceptar mision 50$ * entr");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de liberar prisionero
	else if (this->accionActual == 10)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Liberar prisionero");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de estudiar
	else if (this->accionActual == 11)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Estudiar 50$");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de descansar
	else if (this->accionActual == 12)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Descansar 50$");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}
	
	// Impresión de las acciones de comprar armas
	else if (this->accionActual == 13)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comprar esp. corta 100$");
	    this->GL_imprimeTexto (x, y-8, z, "Comprar esp. ancha 150$");
	    this->GL_imprimeTexto (x, y-12, z, "Comprar hacha 200$");
	    this->GL_imprimeTexto (x, y-16, z, "Comprar cadena 250$");
	    this->GL_imprimeTexto (x, y-20, z, "Salir");
	}

	// Impresión de las acciones de comprar escudos
	else if (this->accionActual == 17)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comprar escu. verde 100$");
	    this->GL_imprimeTexto (x, y-8, z, "Comprar escu. rojo 150$");
	    this->GL_imprimeTexto (x, y-12, z, "Comprar escu. azul 200$");
	    this->GL_imprimeTexto (x, y-16, z, "Salir");
	}

	// Impresión de las acciones de comprar armaduras
	else if (this->accionActual == 20)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Comprar cuero 100$");
	    this->GL_imprimeTexto (x, y-8, z, "Comprar cota 150$");
	    this->GL_imprimeTexto (x, y-12, z, "Comprar armadura 200$");
	    this->GL_imprimeTexto (x, y-16, z, "Comprar coraza 250$");
	    this->GL_imprimeTexto (x, y-20, z, "Salir");
	}

	// Impresión de las acciones de beber agua
	else if (this->accionActual == 24)
	{
	    this->GL_imprimeTexto (x, y-4, z, "Beber agua");
	    this->GL_imprimeTexto (x, y-8, z, "Salir");
	}

	// Impresión de las acciones de finalizar misión
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

	// Cierre de la libería de fuentes
	glfClose ();

	// Activación del Z-buffer (profundidad)
	glEnable (GL_DEPTH_TEST);
    }
    glPopMatrix ();
}

/***************************************************************************/

/* Método que imprime la cadena de texto dada en las coordenadas
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

// Método que dibuja un polígono plano en OpenGL con una textura
void EntornoG::GL_poligono (float x, float y, float lx, float ly, 
			    uchar *imagen, int ancho, int alto, float rot, 
			    int eje)
{
    glPushMatrix ();
    {
	// Posición del polígono
	glTranslatef (x, y, 0.0);

	// Rotación del polígono
	if (eje == 1)
	    glRotatef (rot, 1.0, 0.0, 0.0);

	else if (eje == 2)
	    glRotatef (rot, 0.0, 1.0, 0.0);


	// Activación de la textura
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen);

	// Dibujo del polígono por vértices
	glBegin (GL_POLYGON);
	{
	    glTexCoord2f (0.0, 1.0);     // Vértice 1 de la textura
	    glVertex3f (0.0, 0.0, 0.0);  // Vértice 1 del polígono 
	    
	    glTexCoord2f (1.0, 1.0);     // Vértice 2 de la textura
	    glVertex3f (lx, 0.0, 0.0);   // Vértice 2 del polígono
	    
	    glTexCoord2f (1.0, 0.0);     // Vértice 3 de la textura
	    glVertex3f (lx, ly, 0.0);    // Vértice 3 del polígono

	    glTexCoord2f (0.0, 0.0);     // Vértice 4 de la textura
	    glVertex3f (0.0, ly, 0.0);   // Vértice 4 del polígono	       
	}
	glEnd ();

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);
    }
    glPopMatrix ();
}

/***************************************************************************/

/* Método que dibuja un polígono plano en OpenGL utilizando una textura con
   transparencia */
void EntornoG::GL_poligonoT (float x, float y, float lx, float ly, 
			     uchar *imagen, int ancho, int alto, float rot)
{
    glPushMatrix ();
    {
	// Posición del polígono
	glTranslatef (x, y, 0.0);

	// Rotación del polígono
	glRotatef (rot, 1.0, 0.0, 0.0);

	// Activación de la textura
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, 
		      GL_UNSIGNED_BYTE, imagen);

	// Activación del canal Alpha para la transparencia
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	// Color blanco con canal Alpha
	glColor4f (1.0, 1.0, 1.0, 1.0);

	// Dibujo del polígono por vértices
	glBegin (GL_POLYGON);
	{
	    glTexCoord2f (0.0, 1.0);     // Vértice 1 de la textura
	    glVertex3f (0.0, 0.0, 0.0);  // Vértice 1 del polígono
	    
	    glTexCoord2f (1.0, 1.0);     // Vértice 2 de la textura
	    glVertex3f (lx, 0.0, 0.0);   // Vértice 2 del polígono
	    
	    glTexCoord2f (1.0, 0.0);     // Vértice 3 de la textura
	    glVertex3f (lx, ly, 0.0);    // Vértice 3 del polígono	       

	    glTexCoord2f (0.0, 0.0);     // Vértice 4 de la textura
	    glVertex3f (0.0, ly, 0.0);   // Vértice 4 del polígono       
	}
	glEnd ();
	
	// Desactivación de la transparencia
	glDisable (GL_BLEND);

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);
    }
    glPopMatrix ();
}

/***************************************************************************/

// Método que dibuja un cubo 3D en OpenGL utilizando tres tipos de texturas
void EntornoG::GL_cubo (float x, float y, float lx, float ly, float lz, 
			uchar *imagen1, uchar *imagen2, uchar *imagen3, 
			int ancho1, int alto1, int ancho2, int alto2, 
			int ancho3, int alto3)
{
    glPushMatrix ();
    {
	// Posición del cubo
	glTranslatef (x, y, 0.0);

	// Rotación del cubo
	glRotatef (90.0, 1.0, 0.0, 0.0);

	// Activación de la textura para la cara delantera
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho1, alto1, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen1);

	// Dibujo de la cara delantera por vértices
	glBegin (GL_QUADS); 
	{
	    glTexCoord2f (0.0, 1.0);     // Vértice 1 de la textura
	    glVertex3f (0.0, 0.0, 0.0);  // Vértice 1 del polígono

	    glTexCoord2f (1.0, 1.0);     // Vértice 2 de la textura
	    glVertex3f (lx, 0.0, 0.0);   // Vértice 2 del polígono

	    glTexCoord2f (1.0, 0.0);     // Vértice 3 de la textura
	    glVertex3f (lx, ly, 0.0);    // Vértice 3 del polígono

	    glTexCoord2f (0.0, 0.0);     // Vértice 4 de la textura
	    glVertex3f (0.0, ly, 0.0);   // Vértice 4 del polígono
	}
	glEnd ();

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);

	// Activación de la textura para la cara trasera
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho2, alto2, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen2);

	// Dibujo de la cara trasera por vértices
	glBegin (GL_QUADS);  
	{
	    glTexCoord2f (0.0, 1.0);    // Vértice 1 de la textura
	    glVertex3f (lx, 0.0, lz);   // Vértice 1 del polígono

	    glTexCoord2f (1.0, 1.0);    // Vértice 2 de la textura
	    glVertex3f (0.0, 0.0, lz);  // Vértice 2 del polígono
	    
	    glTexCoord2f (1.0, 0.0);    // Vértice 3 de la textura
	    glVertex3f (0.0, ly, lz);   // Vértice 3 del polígono

	    glTexCoord2f (0.0, 0.0);    // Vértice 4 de la textura
	    glVertex3f (lx, ly, lz);    // Vértice 4 del polígono
	}
	glEnd ();

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);

	// Activación de la textura para la cara lateral izquierda
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho2, alto2, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen2);

	// Dibujo de la cara lateral izquierda por vértices
	glBegin (GL_QUADS);  
	{	
	    glTexCoord2f (0.0, 1.0);       // Vértice 1 de la textura
	    glVertex3f (0.0, 0.0, lz);     // Vértice 1 del polígono 

	    glTexCoord2f (1.0, 1.0);       // Vértice 2 de la textura
	    glVertex3f (0.0, 0.0,  0.0);   // Vértice 2 del polígono

	    glTexCoord2f (1.0, 0.0);       // Vértice 3 de la textura
	    glVertex3f (0.0, ly, 0.0);     // Vértice 3 del polígono 

	    glTexCoord2f (0.0, 0.0);       // Vértice 4 de la textura
	    glVertex3f (0.0, ly, lz);      // Vértice 4 del polígono 
	}
	glEnd();

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);

	// Activación de la textura para la cara lateral derecha
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho2, alto2, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen2);
	
	// Dibujo de la cara lateral derecha por vértices
	glBegin (GL_QUADS);  
	{	
	    glTexCoord2f (0.0, 1.0);       // Vértice 1 de la textura
	    glVertex3f (lx, 0.0,  0.0);    // Vértice 1 del polígono

	    glTexCoord2f (1.0, 1.0);       // Vértice 2 de la textura
	    glVertex3f (lx, 0.0, lz);      // Vértice 2 del polígono

	    glTexCoord2f (1.0, 0.0);       // Vértice 3 de la textura
	    glVertex3f (lx, ly, lz);       // Vértice 3 del polígono

	    glTexCoord2f (0.0, 0.0);       // Vértice 4 de la textura
	    glVertex3f (lx, ly, 0.0);      // Vértice 4 del polígono
	}
	glEnd ();

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);

	// Activación de la textura para la cara de arriba
	glEnable (GL_TEXTURE_2D);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, ancho3, alto3, 0, GL_RGB, 
		      GL_UNSIGNED_BYTE, imagen3);

	// Dibujo de la cara de arriba por vértices
	glBegin (GL_QUADS);  
	{ 
	    glTexCoord2f (0.0, 1.0);       // Vértice 1 de la textura
	    glVertex3f (0.0, ly, 0.0);     // Vértice 1 del polígono

	    glTexCoord2f (1.0, 1.0);       // Vértice 2 de la textura
	    glVertex3f (lx, ly, 0.0);      // Vértice 2 del polígono

	    glTexCoord2f (1.0, 0.0);       // Vértice 3 de la textura
	    glVertex3f (lx, ly, lz);       // Vértice 3 del polígono

	    glTexCoord2f (0.0, 0.0);       // Vértice 4 de la textura
	    glVertex3f (0.0, ly, lz);      // Vértice 4 del polígono
	}
	glEnd ();	

	// Desactivación de la textura
	glDisable (GL_TEXTURE_2D);
    }
    glPopMatrix ();
}

/***************************************************************************/

// Método que implementa la función de inicialización de SDL
void EntornoG::SDL_init (void)
{
    // Inicialización de SDL
    if (SDL_Init (SDL_INIT_VIDEO) == -1)
    {
	fprintf (stderr, "entornoG.cc: SDL_init (void): ");
	fprintf (stderr, "No se puede iniciar SDL\n");
	exit (-1);
    }

    // Inicialización de la ventana
    this->ventana = SDL_SetVideoMode (this->ancho, this->alto, 32, MASK);  
    SDL_WM_SetCaption (this->titulo, NULL);
    SDL_WM_SetIcon(IMG_Load (this->icono), NULL);

    // Definición del retardo de las teclas
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

/***************************************************************************/

/* Método que implementa la función asociada al evento de pulsar una tecla
   Devuelve la acción realizada */
int EntornoG::SDL_key (int evento, int *entrada)
{
    int indiceP, opcion, accion = 0;

    // Inicialización de parámetros
    *entrada = 0;
    this->posx = this->inix;
    this->posy = this->iniy;

    // Comprobación de los movimientos
    switch (evento)
    {
	// Movimiento arriba
	case SDLK_UP:
	{
	    // Si el menú de acciones está a 1
	    if (this->menuAccStatus == 1)
	    {
		if (this->posAccion < -11)
		{
		    this->posAccion += 4;

		    // Acción de visualización de menús
		    accion = 26;
		}
	    }

	    // Si el menú de acciones está a 0
	    else
	    {
		// Si el cursor está a 0
		if (this->cursorStatus == 0)
		{		
		    // Incremento de la posición y del personaje activo
		    this->posy++;

		    // Actualización del flag de entrada a 1
		    *entrada = 1;

		    // Acción de movimiento del personaje activo
		    accion = 1;
		}

		// Si el cursor está a 1
		else
		    // Comprobación de que el cursor sea adyacente al personaje
		    if (((this->cursory + 1) <= (this->posy + 1)) && 
			(this->cursorx == this->posx))
		    {
			// Incremento de la posición y del cursor
			this->cursory++;

			// Acción de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Movimiento abajo
	case SDLK_DOWN:
	{
	    // Si el menú de acciones está a 1
	    if (this->menuAccStatus == 1)
	    {
		if (this->posAccion > -27)
		{		
		    this->posAccion -= 4;

		    // Acción de visualización de menús
		    accion = 26;
		}
	    }

	    // Si el menú de acciones está a 0
	    else
	    {
		// Si el cursor está a 0
		if (this->cursorStatus == 0)
		{
		    // Decremento de la posición y del personaje activo
		    this->posy--;

		    // Acción de movimiento
		    accion = 1;
		}

		// Si el cursor está a 1
		else
		    // Comprobación de que el cursor sea adyacente al personaje
		    if (((this->cursory - 1) >= (this->posy - 1)) &&
			(this->cursorx == this->posx))
		    {
			// Decremento de la posición y del cursor
			this->cursory--;
			
			// Acción de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Movimiento izquierda
	case SDLK_LEFT:
	{
	    // Si el menú de acciones está a 0
	    if (this->menuAccStatus == 0)
	    {
		// Si el cursor está a 0
		if (this->cursorStatus == 0)
		{
		    // Decremento de la posición x del personaje activo
		    this->posx--;
		    
		    // Acción de movimiento
		    accion = 1;
		}

		// Si el cursor está a 1
		else
		    // Comprobación de que el cursor sea adyacente al personaje
		    if (((this->cursorx - 1) >= (this->posx - 1)) &&
			(this->cursory == this->posy))
		    {  
			// Decremento de la posición x del cursor
			this->cursorx--;
			
			// Acción de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Movimiento derecha
	case SDLK_RIGHT:
	{
	    // Si el menú de acciones está a 0
	    if (this->menuAccStatus == 0)
	    {
		// Si el cursor está a 0
		if (this->cursorStatus == 0)
		{
		    // Incremento de la posición x del personaje activo
		    this->posx++;

		    // Acción de movimiento
		    accion = 1;
		}

		// Si el cursor está a 1
		else
		    // Comprobación de que el cursor sea adyacenta al personaje
		    if (((this->cursorx + 1) <= (this->posx + 1)) &&
			(this->cursory == this->posy))
		    {
			// Incremento de la posición x del cursor
			this->cursorx++;
			
			// Acción de movimiento del cursor
			accion = 2;
		    }
	    }

	    break;
	}

	// Tecla Espacio
	case SDLK_SPACE:
	{
	    // Si el menú de acciones está a 0
	    if (this->menuAccStatus == 0)
	    {
		// Cambio del estado del cursor
		this->cursorStatus = 1 - this->cursorStatus;
		
		// Si ha cambiado a 0
		if (this->cursorStatus == 0)
		{
		    // Asignación de la posición del cursor al personaje activo
		    this->cursorx = this->posx;
		    this->cursory = this->posy;
		}

		// Acción de movimiento de cursor
		accion = 2;
	    }

	    break;
	}

	// Tecla Return
	case SDLK_RETURN:
	{
	    // Si el menú de acciones está a 1
	    if (this->menuAccStatus == 1)
	    {
		// Menú de acciones a 0
		this->menuAccStatus = 0;

		// Obtención de la opción del menú
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

		// Obtención de la acción
		if (opcion != -1)
		    accion = this->accionActual + opcion;

		else
		{
		    // Asignación de la posición del cursor al personaje activo
		    this->cursorx = this->posx;
		    this->cursory = this->posy;

		    // Acción de movimiento del cursor
		    accion = 2;
		}
	    }
	    
	    // Si el menú de acciones está a 0
	    else
	    {		
		// Obtención del índice del cliente
		indiceP = obtieneIndice (this->listaP, this->sock);

		// Obtención del menú
		this->accionActual = obtieneAccion (this->cursorx, 
						    this->cursory, 
						    this->listaEdificios,
						    this->listaObjetos,
						    this->listaP, indiceP,
						    this->listaCasillas,
						    this->cursorStatus);
		// Si hay menú
		if (this->accionActual != -1)
		{
		    // Cambio del estado del menú de acciones
		    this->menuAccStatus = 1;
		    
		    // Inicialización de la opción del menú
		    this->posAccion = -11;
		    
		    // Obtención del límite superior del menú
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

		    // Acción de visualización de menús
		    accion = 26;
		}

		// Si no hay menú
		else
		{
		    // Si el cursor está a 0
		    if (cursorStatus == 0)
			
			// Acción de paso de turno
			accion = 3;

		    else
		    {
			// Asignación de la posición del cursor
			this->cursorx = this->posx;
			this->cursory = this->posy;
		
			// Acción de movimiento de cursor
			accion = 2;
		    }
		}

		// Si el cursor está a 1
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
	    // Cambio del estado del cuadro de características
	    this->caractStatus = 1 - this->caractStatus;
	    
	    // Acción de visualización de menús
	    accion = 26;

	    break;
	}

	// Tecla Escape
	case SDLK_ESCAPE:
	{
	    // Acción de desconexión
	    accion = -1;

	    break;
	}
    }

    return accion;
}

/***************************************************************************/

/* Método que carga las dimensiones del mundo a través de los datos 
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

/* Método que carga las estructuras del mundo con los datos recibidos a 
   través del servidor y devuelve el índice donde se encuentra el personaje
   activo */
int EntornoG::cargaMundo (int env)
{    
    Edificio *unEdificio;
    Objeto *unObjeto;
    Personaje *unPersonaje;
    Elemento *unElemento;
    Casilla *unaCasilla;
    int indiceP, nAtributos, atributo, tamanoEqu;

    // Recepción del socket del cliente
    this->sock = recibeEnteroDeServidor (this->conexion);

    // Si el cliente no existe
    if (this->sock == -1)
	return -1;

    // Recepción de la posición del cursor
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

    // Recepción del tamaño de la lista de objetos
    this->tamanoObjetos = recibeEnteroDeServidor (this->conexion);
    
    // Recepción de cada uno de los objetos y su reconstrucción 
    for (int i = 0; i < this->tamanoObjetos; i++)
    {		
	// Creación del objeto
	unObjeto = new Objeto ();

	// Obtención del número de atributos de cada objeto
	nAtributos = unObjeto->obtieneNAtributos ();

	// Recepción de cada uno de los atributos  
	for (int j = 1; j <= nAtributos; j++)
	{
	    // Recepción del atributo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignación del atributo
	    unObjeto->reAsignaAtributo (j, atributo); 
	}
		
	// Inserción del objeto en la lista
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

    // Recepción del tamaño de la lista de personajes
    this->tamanoP = recibeEnteroDeServidor (this->conexion);

    // Recepción de cada uno de los personajes y su reconstrucción 
    for (int i = 0; i < this->tamanoP; i++)
    {
	// Creación del personaje
	unPersonaje = new Personaje ();
	
	// Obtención del número de atributos de cada personaje
	nAtributos = unPersonaje->obtieneNAtributos ();
	
	// Recepción de cada uno de los atributos
	for (int j = 1; j <= nAtributos; j++)
	{	    
	    // Recepción del atributo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignación del atributo
	    unPersonaje->reAsignaAtributo (j, atributo);
	}
	
	// Obtención del tamaño del equipo de cada personaje
	tamanoEqu = unPersonaje->obtieneTamEqu ();

	// Recepción de cada uno de los elementos del equipo
	for (int j = 0; j < tamanoEqu; j++)
	{
	    // Recepción del elemento del equipo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignación del elemento del equipo
	    unPersonaje->reAsignaEqu (j, atributo);
	}

	// Inserción del personaje en la lista
	this->listaP->insertaElemento (unPersonaje);

	// Obtención de los atributos del personaje activo
	if (unPersonaje->obtieneAtributo ("sock") == this->sock)
	{
	    // Posición (x,y) del personaje activo 
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

    // Recepción del tamaño de la lista de elementos
    this->tamanoElementos = recibeEnteroDeServidor (this->conexion);

    // Recepción de cada uno de los elementos y su reconstrucción 
    for (int i = 0; i < this->tamanoElementos; i++)
    {
	// Creación del elemento
	unElemento = new Elemento ();

	// Obtención del número de atributos de cada elemento
	nAtributos = unElemento->obtieneNAtributos ();

	// Recepción de cada uno de los atributos
	for (int j = 1; j <= nAtributos; j++)
	{
	    // Recepción del atributo
	    atributo = recibeEnteroDeServidor (this->conexion);

	    // Asignación del atributo
	    unElemento->reAsignaAtributo (j, atributo);
	}

	// Inserción del elemento en la lista
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

	// Recepción del tamaño de la lista de edificios 
	this->tamanoEdificios = recibeEnteroDeServidor (this->conexion);
	
	// Recepción de cada uno de los edificios y su reconstrucción 
	for (int i = 0; i < this->tamanoEdificios; i++)
	{
	    // Creación del edificio
	    unEdificio = new Edificio ();
	    
	    // Obtención del número de atributos de cada edificio
	    nAtributos = unEdificio->obtieneNAtributos ();
	    
	    // Recepción de cada uno de los atributos
	    for (int j = 1; j <= nAtributos; j++)
	    {
		// Recepción del atributo
		atributo = recibeEnteroDeServidor (this->conexion);
		
		// Asignación del atributo
		unEdificio->reAsignaAtributo (j, atributo);
	    }
	    
	    // Inserción del edificio en la lista
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
	
	// Recepción del tamaño de la lista de casillas
	this->tamanoCasillas = recibeEnteroDeServidor (this->conexion);
	
	// Recepción de cada una de las casillas y su reconstrucción
	for (int i = 0; i < this->tamanoCasillas; i++)
	{
	    // Creación de la casilla
	    unaCasilla = new Casilla ();
	    
	    // Obtención del número de atributos de cada casilla
	    nAtributos = unaCasilla->obtieneNAtributos ();
	    
	    // Recepción de cada uno de los atributos
	    for (int j = 1; j <= nAtributos; j++)
	    {
		// Recepción del atributo
		atributo = recibeEnteroDeServidor (this->conexion);
		
		// Asignación del atributo
		unaCasilla->reAsignaAtributo (j, atributo);
	    }
	    
	    // Inserción de la casilla en la lista
	    this->listaCasillas->insertaElemento (unaCasilla);
	}
    }

    return indiceP;
}

/***************************************************************************/

// Método que carga las texturas del mundo en la lista de texturas
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

    // Actualización del tamaño
    this->tamanoTexturas = this->listaTexturas->obtieneTamano ();

    // Liberación de recursos
    delete [] cadena;
}

/***************************************************************************/

// Método que envía las coordenadas modificadas del personaje activo
void EntornoG::enviaCoordenadas (int accion, int entrada)
{
    // Si la acción es de movimiento del personaje
    if (accion == 1)
    {
	// Envio de las coordenadas del personaje activo y del flag de entrada
	enviaEnteroAServidor (this->conexion, this->posx);
	enviaEnteroAServidor (this->conexion, this->posy);
	enviaEnteroAServidor (this->conexion, entrada);
    }

    /* Si la acción es de movimiento del cursor o está relacionada con algún
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

