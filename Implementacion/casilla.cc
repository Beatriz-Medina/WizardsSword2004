
/***************************************************************************
                          casilla.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "casilla.hh"

/***************************************************************************/

/* Constructor del objeto Casilla que inicializa todos sus atributos a 
   VACIO */
Casilla::Casilla ()
{
    // Inicialización de los atributos a VACIO
    this->tipo = VACIO;
    this->posx = VACIO;
    this->posy = VACIO;

    // Inicialización del número de atributos
    this->nAtr = 3;
}

/***************************************************************************/

// Destructor del objeto Casilla
Casilla::~Casilla ()
{}

/***************************************************************************/

// Método consultor que devuelve el número de atributos del objeto Casilla
int Casilla::obtieneNAtributos (void)
{
    return this->nAtr;
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo nombre se 
   especifica */ 
int Casilla::obtieneAtributo (char *atributo)
{
    if (!strcmp (atributo, "tipo"))
	return this->tipo;

    else if (!strcmp (atributo, "posx"))
	return this->posx;

    else if (!strcmp (atributo, "posy"))
	return this->posy;

    else
    {
	fprintf (stderr, "casilla.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo índice se 
   especifica */ 
int Casilla::obtieneAtributo (int atributo)
{
    if (atributo == 1)
	return this->tipo;

    else if (atributo == 2)
	return this->posx;

    else if (atributo == 3)
	return this->posy;

    else
    {
	fprintf (stderr, "casilla.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo nombre se
   especifica */
void Casilla::reAsignaAtributo (char *atributo, int nuevoValor)
{
    if (!strcmp (atributo, "tipo"))
	this->tipo = nuevoValor;
    
    else if (!strcmp (atributo, "posx"))
	this->posx = nuevoValor;

    else if (!strcmp (atributo, "posy"))
	this->posy = nuevoValor;

    else
    {
	fprintf (stderr, "casilla.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo índice se
   especifica */
void Casilla::reAsignaAtributo (int atributo, int nuevoValor)
{
    if (atributo == 1)
	this->tipo = nuevoValor;
    
    else if (atributo == 2)
	this->posx = nuevoValor;

    else if (atributo == 3)
	this->posy = nuevoValor;

    else
    {
	fprintf (stderr, "casilla.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/

