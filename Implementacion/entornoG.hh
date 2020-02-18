
/***************************************************************************
                         EntornoG.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
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
    /* Clase que implementa un entorno gráfico orientado a conexión utilizando 
       la librería OpenGL para dibujar los escenarios de la aplicación y la 
       libreria SDL para manejar los eventos de la ventana de la aplicación */

 private:
    SDL_Surface *ventana;             // Ventana SDL    
    char *titulo;                     // Título de la ventana SDL
    char *icono;                      // Nombre del icono de la ventana SDL
    int ancho;                        // Ancho de la ventana SDL
    int alto;                         // Alto de la ventana SDL
    ConexionCliente *conexion;        // Conexión del cliente
    int servidorIP;                   // Dirección del servidor
    int mundoInf;                     // Dimensión inferior del mundo
    int mundoSup;                     // Dimensión superior del mundo
    int castilInf;                    // Dimensión inferior de los castillos
    int castilSup;                    // Dimensión superior de los castillos
    int casaInf;                      // Dimensión inferior de las casas
    int casaSup;                      // Dimensión superior de las casas
    Lista<Edificio*> *listaEdificios; // Lista de edificios
    Lista<Objeto*> *listaObjetos;     // Lista de objetos
    Lista<Personaje*> *listaP;        // Lista de personajes
    Lista<Elemento*> *listaElementos; // Lista de elementos
    Lista<Casilla*> *listaCasillas;   // Lista de casillas
    Lista<Textura*> *listaTexturas;   // Lista de texturas
    int tamanoEdificios;              // Tamaño de la lista de edificios
    int tamanoObjetos;                // Tamaño de la lista de objetos
    int tamanoP;                      // Tamaño de la lista de personajes
    int tamanoElementos;              // Tamaño de la lista de elementos
    int tamanoCasillas;               // Tamaño de la lista de casillas
    int tamanoTexturas;               // Tamaño de la lista de texturas
    int posx;                         // Posición x del personaje activo 
    int posy;                         // Posición y del personaje activo 
    int inix;                         // Posición x inicial
    int iniy;                         // Posición y inicial
    int edif;                         // Edificio donde está el personaje   
    int cursorStatus;                 // Estado del cursor 
    int cursorx;                      // Posición x del cursor
    int cursory;                      // Posición y del cursor
    int caractStatus;                 // Estado del cuadro de características
    int menuAccStatus;                // Estado del menú de acciones
    int posAccion;                    // Posición de la acción del menú
    int topePosAccion;                // Límite superior del menú de acciones
    int accionActual;                 // Flag que indica la acción solicitada
    int sock;                         // Socket del personaje activo
    int turno;                        // Turno asociado al socket activo

 public:
    EntornoG (char *titulo, char *icono, int ancho, int alto, int servidorIP);
    /* Constructor del objeto EntornoG que crea un entorno gráfico con los 
       parámetros especificados e inicializa las variables del entornoG */

    ~EntornoG ();
    // Destructor del objeto EntornoG

    void iniciaEntorno (void);
    // Método que inicia el entorno gráfico inicializando tanto OpenGL como SDL

    void visualizaEntorno (void);
    // Método que implementa el bucle de eventos de SDL

    int visualizaMenuStart (void);
    // Método que visualiza una pantalla de inicio con selección de opciones
    
    void visualizaOver (void);
    // Método que visualiza una pantalla de fin

    void GL_init (void);
    // Método que implementa la función de inicialización de OpenGL

    void GL_reshape (int ancho, int alto);
    // Método que implementa la función de redimensionado de OpenGL

    void GL_display (int indice);
    // Método que implementa la función de dibujado de OpenGL

    void GL_displayMenuStart (int posOpcion);
    // Método que implementa la función de dibujado de una pantalla de inicio

    void GL_displayOver (void);
    // Método que implementa la función de dibujado de una pantalla de fin

    void GL_cursor (float x, float y);
    // Método que dibuja una flecha indicadora en la posición señalada

    void GL_caracteristicas (int indiceP);
    /* Método que dibuja un poligono semitransparente en OpenGL con un texto 
       asociado a las características del personaje activo */

    void GL_menuAcciones (void);
    /* Método que dibuja un polígono semitransparente en OpenGL con un menú
       de acciones */

    void GL_imprimeTexto (float x, float y, float z, char *texto);
    /* Método que imprime la cadena de texto dada en las coordenadas
       especificadas */

    void GL_poligono (float x, float y, float lx, float ly, uchar *imagen, 
		      int ancho, int alto, float rot, int eje);
    // Método que dibuja un polígono plano en OpenGL con una textura

    void GL_poligonoT (float x, float y, float lx, float ly, uchar *imagen, 
		       int ancho, int alto, float rot);
    /* Método que dibuja un polígono plano en OpenGL utilizando una textura con
       transparencia */

    void GL_cubo (float x, float y, float lx, float ly, float lz, 
		  uchar *imagen1, uchar *imagen2, uchar *imagen3, 
		  int ancho1, int alto1, int ancho2, int alto2, 
		  int ancho3, int alto3);
    // Método que dibuja un cubo 3D en OpenGL utilizando tres tipos de texturas

    void SDL_init (void);
    // Método que implementa la función de inicialización de SDL

    int SDL_key (int evento, int *entrada);
    /* Método que implementa la función asociada al evento de pulsar una tecla
       Devuelve la acción asociada a la tecla */

    void cargaTamanoMundo (void);
    /* Método que carga las dimensiones del mundo a través de los datos 
       enviados desde elservidor */

    int cargaMundo (int env);
    /* Método que carga las estructuras del mundo con los datos recibidos a 
       través del servidor y devuelve el índice donde se encuentra el personaje
       activo */

    void cargaTexturas (void);
    // Método que carga las texturas del mundo en la lista de texturas

    void enviaCoordenadas (int accion, int entrada);
    // Método que envía las coordenadas modificadas del personaje activo
};

#endif 

/****************************************************************************/
