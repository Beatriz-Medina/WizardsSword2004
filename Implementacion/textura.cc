
/***************************************************************************
                          textura.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "textura.hh"

/***************************************************************************/

/* Constructor del objeto Textura que carga en memoria la textura con
   respecto al nombre y profundidad especificados */
Textura::Textura (char *nombre, int profundidad)
{
    SDL_Surface *imagenSDL;

    // Carga de la imagen en SDL
    imagenSDL = IMG_Load (nombre);

    // Obtención del ancho y alto de la imagen
    this->ancho = imagenSDL->w;
    this->alto = imagenSDL->h;

    // Reserva de memoria para los pixels de la imagen
    this->pixels = new uchar [this->ancho * this->alto * profundidad];
    if (this->pixels == NULL)
    {
	fprintf (stderr, "textura.cc:: textura (char*, int):  ");
	fprintf (stderr, "Memoria insuficiente para pixels\n");
	exit (-1);	
    }

    // Asignación de los pixels de la imagen 
    this->pixels = (uchar *)imagenSDL->pixels;
}

/***************************************************************************/

// Destructor del objeto Textura
Textura::~Textura ()
{
    if (this->pixels != NULL)    
	delete [] this->pixels;
}

/***************************************************************************/

// Método consultor que devuelve la matriz de bits de la textura 
uchar *Textura::obtienePixels (void)
{
    return this->pixels;
}

/***************************************************************************/

// Método consultor que devuelve el ancho de la textura
int Textura::obtieneAncho (void)
{
    return this->ancho;
}

/***************************************************************************/

// Método consultor que devuelve el alto de la textura
int Textura::obtieneAlto (void)
{
    return this->alto;
}

/***************************************************************************/
