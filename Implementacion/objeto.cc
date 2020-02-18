
/***************************************************************************
                          objeto.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objeto.hh"

/***************************************************************************/

// Constructor del objeto Objeto que inicializa todos sus atributos a VACIO
Objeto::Objeto ()
{
    // Inicialización de los atributos a VACIO
    this->id = VACIO;
    this->tipo = VACIO;
    this->visi = VACIO;
    this->posx = VACIO;
    this->posy = VACIO;
    this->longx = VACIO;
    this->longy = VACIO;
    this->casilx = VACIO;
    this->casily = VACIO;
    this->edif = VACIO;	
    this->equ = VACIO;

    // Inicialización del número de atributos
    this->nAtr = 11;
}

/***************************************************************************/

// Destructor del objeto Objeto
Objeto::~Objeto ()
{}

/***************************************************************************/

// Método consultor que devuelve el número de atributos del objeto Objeto
int Objeto::obtieneNAtributos (void)
{
    return this->nAtr;
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo nombre se 
   especifica */ 
int Objeto::obtieneAtributo (char *atributo)
{
    if (!strcmp (atributo, "id"))
	return this->id;

    else if (!strcmp (atributo, "tipo"))
	return this->tipo;

    else if (!strcmp (atributo, "visi"))
	return this->visi;

    else if (!strcmp (atributo, "posx"))
	return this->posx;

    else if (!strcmp (atributo, "posy"))
	return this->posy;

    else if (!strcmp (atributo, "longx"))
	return this->longx;

    else if (!strcmp (atributo, "longy"))
	return this->longy;

    else if (!strcmp (atributo, "casilx"))
	return this->casilx;

    else if (!strcmp (atributo, "casily"))
	return this->casily;

    else if (!strcmp(atributo, "edif"))
	return this->edif;

    else if (!strcmp (atributo, "equ"))
	return this->equ;

    else
    {
	fprintf (stderr, "objeto.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo índice se 
   especifica */ 
int Objeto::obtieneAtributo (int atributo)
{
    if (atributo == 1)
	return this->id;

    else if (atributo == 2)
	return this->tipo;

    else if (atributo == 3)
	return this->visi;

    else if (atributo == 4)
	return this->posx;

    else if (atributo == 5)
	return this->posy;

    else if (atributo == 6)
	return this->longx;

    else if (atributo == 7)
	return this->longy;

    else if (atributo == 8)
	return this->casilx;

    else if (atributo == 9)
	return this->casily;

    else if (atributo == 10)
	return this->edif;

    else if (atributo == 11)
	return this->equ;

    else
    {
	fprintf (stderr, "objeto.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo nombre se
   especifica */
void Objeto::reAsignaAtributo (char *atributo, int nuevoValor)
{
    if (!strcmp (atributo, "id"))
	this->id = nuevoValor;

    else if (!strcmp (atributo, "tipo"))
	this->tipo = nuevoValor;

    else if (!strcmp (atributo, "visi"))
	this->visi = nuevoValor;

    else if (!strcmp (atributo, "posx"))
	this->posx = nuevoValor;

    else if (!strcmp (atributo, "posy"))
	this->posy = nuevoValor;

    else if (!strcmp (atributo, "longx"))
	this->longx = nuevoValor;

    else if (!strcmp (atributo, "longy"))
	this->longy = nuevoValor;

    else if (!strcmp (atributo, "casilx"))
	this->casilx = nuevoValor;

    else if (!strcmp (atributo, "casily"))
	this->casily = nuevoValor;

    else if (!strcmp(atributo, "edif"))
	this->edif = nuevoValor;

    else if (!strcmp (atributo, "equ"))
	this->equ = nuevoValor;
    
    else
    {
	fprintf (stderr, "objeto.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo índice se
   especifica */
void Objeto::reAsignaAtributo (int atributo, int nuevoValor)
{
    if (atributo == 1)
	this->id = nuevoValor;

    else if (atributo == 2)
	this->tipo = nuevoValor;

    else if (atributo == 3)
	this->visi = nuevoValor;

    else if (atributo == 4)
	this->posx = nuevoValor;

    else if (atributo == 5)
	this->posy = nuevoValor;

    else if (atributo == 6)
	this->longx = nuevoValor;

    else if (atributo == 7)
	this->longy = nuevoValor;

    else if (atributo == 8)
	this->casilx = nuevoValor;

    else if (atributo == 9)
	this->casily = nuevoValor;

    else if (atributo == 10)
	this->edif = nuevoValor;

    else if (atributo == 11)
	this->equ = nuevoValor;
    
    else
    {
	fprintf (stderr, "objeto.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/
