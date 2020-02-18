
/***************************************************************************
                         EntornoG.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#ifndef _ENTORNOG_HH
#define _ENTORNOG_HH

#include <SDL.h>

#include "conexionCliente.hh"
#include "lista.cc"
#include "edificio.hh"
#include "objeto.hh"
#include "personaje.hh"
#include "casilla.hh"
#include "elemento.hh"
#include "textura.hh"

#define uchar unsigned char
#define MASK SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_RESIZABLE|SDL_OPENGL

/****************************************************************************/

class EntornoG
{
    /* Clase que implementa un entorno gr�fico orientado a conexi�n utilizando 
       la librer�a OpenGL para dibujar los escenarios de la aplicaci�n y la 
       libreria SDL para manejar los eventos de la ventana de la aplicaci�n */

 private:
    SDL_Surface *ventana;             // Ventana SDL    
    char *titulo;                     // T�tulo de la ventana SDL
    char *icono;                      // Nombre del icono de la ventana SDL
    int ancho;                        // Ancho de la ventana SDL
    int alto;                         // Alto de la ventana SDL
    ConexionCliente *conexion;        // Conexi�n del cliente
    int servidorIP;                   // Direcci�n del servidor
    int mundoInf;                     // Dimensi�n inferior del mundo
    int mundoSup;                     // Dimensi�n superior del mundo
    int castilInf;                    // Dimensi�n inferior de los castillos
    int castilSup;                    // Dimensi�n superior de los castillos
    int casaInf;                      // Dimensi�n inferior de las casas
    int casaSup;                      // Dimensi�n superior de las casas
    Lista<Edificio*> *listaEdificios; // Lista de edificios
    Lista<Objeto*> *listaObjetos;     // Lista de objetos
    Lista<Personaje*> *listaP;        // Lista de personajes
    Lista<Elemento*> *listaElementos; // Lista de elementos
    Lista<Casilla*> *listaCasillas;   // Lista de casillas
    Lista<Textura*> *listaTexturas;   // Lista de texturas
    int tamanoEdificios;              // Tama�o de la lista de edificios
    int tamanoObjetos;                // Tama�o de la lista de objetos
    int tamanoP;                      // Tama�o de la lista de personajes
    int tamanoElementos;              // Tama�o de la lista de elementos
    int tamanoCasillas;               // Tama�o de la lista de casillas
    int tamanoTexturas;               // Tama�o de la lista de texturas
    int posx;                         // Posici�n x del personaje activo 
    int posy;                         // Posici�n y del personaje activo 
    int inix;                         // Posici�n x inicial
    int iniy;                         // Posici�n y inicial
    int edif;                         // Edificio donde est� el personaje   
    int cursorStatus;                 // Estado del cursor 
    int cursorx;                      // Posici�n x del cursor
    int cursory;                      // Posici�n y del cursor
    int caractStatus;                 // Estado del cuadro de caracter�sticas
    int menuAccStatus;                // Estado del men� de acciones
    int posAccion;                    // Posici�n de la acci�n del men�
    int topePosAccion;                // L�mite superior del men� de acciones
    int accionActual;                 // Flag que indica la acci�n solicitada
    int sock;                         // Socket del personaje activo
    int turno;                        // Turno asociado al socket activo

 public:
    EntornoG (char *titulo, char *icono, int ancho, int alto, int servidorIP);
    /* Constructor del objeto EntornoG que crea un entorno gr�fico con los 
       par�metros especificados e inicializa las variables del entornoG */

    ~EntornoG ();
    // Destructor del objeto EntornoG

    void iniciaEntorno (void);
    // M�todo que inicia el entorno gr�fico inicializando tanto OpenGL como SDL

    void visualizaEntorno (void);
    // M�todo que implementa el bucle de eventos de SDL

    int visualizaMenuStart (void);
    // M�todo que visualiza una pantalla de inicio con selecci�n de opciones
    
    void visualizaOver (void);
    // M�todo que visualiza una pantalla de fin

    void GL_init (void);
    // M�todo que implementa la funci�n de inicializaci�n de OpenGL

    void GL_reshape (int ancho, int alto);
    // M�todo que implementa la funci�n de redimensionado de OpenGL

    void GL_display (int indice);
    // M�todo que implementa la funci�n de dibujado de OpenGL

    void GL_displayMenuStart (int posOpcion);
    // M�todo que implementa la funci�n de dibujado de una pantalla de inicio

    void GL_displayOver (void);
    // M�todo que implementa la funci�n de dibujado de una pantalla de fin

    void GL_cursor (float x, float y);
    // M�todo que dibuja una flecha indicadora en la posici�n se�alada

    void GL_caracteristicas (int indiceP);
    /* M�todo que dibuja un poligono semitransparente en OpenGL con un texto 
       asociado a las caracter�sticas del personaje activo */

    void GL_menuAcciones (void);
    /* M�todo que dibuja un pol�gono semitransparente en OpenGL con un men�
       de acciones */

    void GL_imprimeTexto (float x, float y, float z, char *texto);
    /* M�todo que imprime la cadena de texto dada en las coordenadas
       especificadas */

    void GL_poligono (float x, float y, float lx, float ly, uchar *imagen, 
		      int ancho, int alto, float rot, int eje);
    // M�todo que dibuja un pol�gono plano en OpenGL con una textura

    void GL_poligonoT (float x, float y, float lx, float ly, uchar *imagen, 
		       int ancho, int alto, float rot);
    /* M�todo que dibuja un pol�gono plano en OpenGL utilizando una textura con
       transparencia */

    void GL_cubo (float x, float y, float lx, float ly, float lz, 
		  uchar *imagen1, uchar *imagen2, uchar *imagen3, 
		  int ancho1, int alto1, int ancho2, int alto2, 
		  int ancho3, int alto3);
    // M�todo que dibuja un cubo 3D en OpenGL utilizando tres tipos de texturas

    void SDL_init (void);
    // M�todo que implementa la funci�n de inicializaci�n de SDL

    int SDL_key (int evento, int *entrada);
    /* M�todo que implementa la funci�n asociada al evento de pulsar una tecla
       Devuelve la acci�n asociada a la tecla */

    void cargaTamanoMundo (void);
    /* M�todo que carga las dimensiones del mundo a trav�s de los datos 
       enviados desde elservidor */

    int cargaMundo (int env);
    /* M�todo que carga las estructuras del mundo con los datos recibidos a 
       trav�s del servidor y devuelve el �ndice donde se encuentra el personaje
       activo */

    void cargaTexturas (void);
    // M�todo que carga las texturas del mundo en la lista de texturas

    void enviaCoordenadas (int accion, int entrada);
    // M�todo que env�a las coordenadas modificadas del personaje activo
};

#endif 

/****************************************************************************/
