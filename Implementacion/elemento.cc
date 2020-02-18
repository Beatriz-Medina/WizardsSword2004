
/***************************************************************************
                          elemento.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
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
    // Inicializaci�n de los atributos a VACIO
    this->tipo = VACIO;
    this->posicion = VACIO;

    // Inicializaci�n del n�mero de atributos
    this->nAtr = 2;
}

/***************************************************************************/

// Destructor del objeto Elemento
Elemento::~Elemento ()
{}

/***************************************************************************/

// M�todo consultor que devuelve el n�mero de atributos del objeto Elemento
int Elemento::obtieneNAtributos (void)
{
    return this->nAtr;
}

/***************************************************************************/

/* M�todo consultor que devuelve el valor del atributo cuyo nombre se 
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

/* M�todo consultor que devuelve el valor del atributo cuyo �ndice se 
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

/* M�todo que actualiza con un nuevo valor al atributo cuyo nombre se
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

/* M�todo que actualiza con un nuevo valor al atributo cuyo �ndice se
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
