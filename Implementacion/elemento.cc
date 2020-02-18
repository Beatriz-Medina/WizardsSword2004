
/***************************************************************************
                          elemento.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elemento.hh"

/***************************************************************************/

/* Constructor del objeto Elemento que inicializa todos sus atributos a 
   VACIO */
Elemento::Elemento ()
{
    // Inicialización de los atributos a VACIO
    this->tipo = VACIO;
    this->posicion = VACIO;

    // Inicialización del número de atributos
    this->nAtr = 2;
}

/***************************************************************************/

// Destructor del objeto Elemento
Elemento::~Elemento ()
{}

/***************************************************************************/

// Método consultor que devuelve el número de atributos del objeto Elemento
int Elemento::obtieneNAtributos (void)
{
    return this->nAtr;
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo nombre se 
   especifica */ 
int Elemento::obtieneAtributo (char *atributo)
{
    if (!strcmp (atributo, "tipo"))
	return this->tipo;

    else if (!strcmp (atributo, "posicion"))
	return this->posicion;

    else
    {
	fprintf (stderr, "elemento.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo índice se 
   especifica */ 
int Elemento::obtieneAtributo (int atributo)
{
    if (atributo == 1)
	return this->tipo;

    else if (atributo == 2)
	return this->posicion;

    else
    {
	fprintf (stderr, "elemento.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo nombre se
   especifica */
void Elemento::reAsignaAtributo (char *atributo, int nuevoValor)
{
    if (!strcmp (atributo, "tipo"))
	this->tipo = nuevoValor;

    else if (!strcmp (atributo, "posicion"))
	this->posicion = nuevoValor;

    else
    {
	fprintf (stderr, "elemento.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo índice se
   especifica */
void Elemento::reAsignaAtributo (int atributo, int nuevoValor)
{
    if (atributo == 1)
	this->tipo = nuevoValor;

    else if (atributo == 2)
	this->posicion = nuevoValor;

    else
    {
	fprintf (stderr, "elemento.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/
