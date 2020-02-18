
/***************************************************************************
                         personaje.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "personaje.hh"

/***************************************************************************/

/* Constructor del objeto Personaje que inicializa todos sus atributos
   a VACIO */
Personaje::Personaje ()
{
    // Inicialización de los atributos a VACIO
    this->sock = VACIO;
    this->esp = VACIO;
    this->fue = VACIO;
    this->con = VACIO;
    this->tam = VACIO;
    this->inte = VACIO;
    this->des = VACIO;
    this->pg = VACIO;
    this->ene = VACIO;
    this->ham = VACIO;
    this->sed = VACIO;
    this->maxpg = VACIO;
    this->maxene = VACIO;
    this->maxham = VACIO;
    this->maxsed = VACIO;
    this->mh1 = VACIO;
    this->mh2 = VACIO;
    this->mmr = VACIO;
    this->posx = VACIO;
    this->posy = VACIO;
    this->edif = VACIO;
    this->estu = VACIO;
    this->entr = VACIO;
    this->obj = VACIO;
    this->nturnos = VACIO;

    // Inicialización del número de atributos
    this->nAtr = 25;

    // Reserva de memoria para el equipo
    this->tamEqu = 6;
    this->equ = new int [this->tamEqu];
    if (this->equ == NULL)
    {
	fprintf (stderr, "personaje.cc::personaje (): ");
	fprintf (stderr, "Memoria insuficiente para equ\n");
	exit (-1);
    }
    
    // Inicialización del equipo a VACIO
    for (int i = 0; i < this->tamEqu; i++)
	this->equ[i] = VACIO;    
}

/***************************************************************************/

// Destructor del objeto Personaje
Personaje::~Personaje ()
{
    // Liberación de recursos para el equipo
    if (this->equ != NULL)
    {
	delete [] this->equ;
	this->equ = NULL;
	this->tamEqu = 0;
    }

    // Inicialización a VACIO de los atributos
    this->sock = VACIO;
    this->esp = VACIO;
    this->fue = VACIO;
    this->con = VACIO;
    this->tam = VACIO;
    this->inte = VACIO;
    this->des = VACIO;
    this->pg = VACIO;
    this->ene = VACIO;
    this->ham = VACIO;
    this->sed = VACIO;	
    this->maxpg = VACIO;
    this->maxene = VACIO;
    this->maxham = VACIO;
    this->maxsed = VACIO;
    this->mh1 = VACIO;
    this->mh2 = VACIO;
    this->mmr = VACIO;
    this->posx = VACIO;
    this->posy = VACIO;
    this->edif = VACIO;
    this->estu = VACIO;
    this->entr = VACIO;
    this->obj = VACIO;
    this->nturnos = VACIO;

    // Inicialización del número de atributos
    this->nAtr = 25;
}

/***************************************************************************/

// Método consultor que devuelve el número de atributos del objeto Personaje
int Personaje::obtieneNAtributos (void)
{
    return this->nAtr;
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo nombre se 
   especifica */ 
int Personaje::obtieneAtributo (char *atributo)
{
    if (!strcmp (atributo, "sock"))
	return this->sock;

    else if (!strcmp (atributo, "esp"))
	return this->esp;

    else if (!strcmp (atributo, "fue"))
	return this->fue;

    else if (!strcmp (atributo, "con"))
	return this->con;

    else if (!strcmp (atributo, "tam"))
	return this->tam;

    else if (!strcmp (atributo, "inte"))
	return this->inte;

    else if (!strcmp(atributo, "des"))
	return this->des;
    
    else if (!strcmp (atributo, "pg"))
	return this->pg;

    else if (!strcmp (atributo, "ene"))
	return this->ene;

    else if (!strcmp (atributo, "ham"))
	return this->ham;

    else if (!strcmp (atributo, "sed"))
	return this->sed;

    else if (!strcmp (atributo, "maxpg"))
	return this->maxpg;

    else if (!strcmp (atributo, "maxene"))
	return this->maxene;

    else if (!strcmp (atributo, "maxham"))
	return this->maxham;

    else if (!strcmp (atributo, "maxsed"))
	return this->maxsed;

    else if (!strcmp (atributo, "mh1"))
	return this->mh1;

    else if (!strcmp (atributo, "mh2"))
	return this->mh2;

    else if (!strcmp (atributo, "mmr"))
	return this->mmr;

    else if (!strcmp (atributo, "posx"))
	return this->posx;

    else if (!strcmp (atributo, "posy"))
	return this->posy;

    else if (!strcmp (atributo, "edif"))
	return this->edif;

    else if (!strcmp (atributo, "estu"))
	return this->estu;

    else if (!strcmp (atributo, "entr"))
	return this->entr;

    else if (!strcmp (atributo, "obj"))
	return this->obj;

    else if (!strcmp (atributo, "nturnos"))
	return this->nturnos;

    else
    {
	fprintf (stderr, "personaje.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método consultor que devuelve el valor del atributo cuyo índice se 
   especifica */ 
int Personaje::obtieneAtributo (int atributo)
{
    if (atributo == 1)
	return this->sock;

    else if (atributo == 2)
	return this->esp;

    else if (atributo == 3)
	return this->fue;

    else if (atributo == 4)
	return this->con;

    else if (atributo == 5)
	return this->tam;

    else if (atributo == 6)
	return this->inte;

    else if (atributo == 7)
	return this->des;

    else if (atributo == 8)
	return this->pg;

    else if (atributo == 9)
	return this->ene;

    else if (atributo == 10)
	return this->ham;

    else if (atributo == 11)
	return this->sed;

    else if (atributo == 12)
	return this->maxpg;

    else if (atributo == 13)
	return this->maxene;

    else if (atributo == 14)
	return this->maxham;

    else if (atributo == 15)
	return this->maxsed;

    else if (atributo == 16)
	return this->mh1;

    else if (atributo == 17)
	return this->mh2;

    else if (atributo == 18)
	return this->mmr;

    else if (atributo == 19)
	return this->posx;

    else if (atributo == 20)
	return this->posy;

    else if (atributo == 21)
	return this->edif;

    else if (atributo == 22)
	return this->estu;

    else if (atributo == 23)
	return this->entr;

    else if (atributo == 24)
	return this->obj;

    else if (atributo == 25)
	return this->nturnos;

    else
    {
	fprintf (stderr, "personaje.cc::obtieneAtributo (char *): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo nombre se
   especifica */
void Personaje::reAsignaAtributo (char *atributo, int nuevoValor)
{
    if (!strcmp (atributo, "sock"))
	this->sock = nuevoValor;

    else if (!strcmp (atributo, "esp"))
	this->esp = nuevoValor;

    else if (!strcmp (atributo, "fue"))
	this->fue = nuevoValor;

    else if (!strcmp (atributo, "con"))
	this->con = nuevoValor;

    else if (!strcmp (atributo, "tam"))
	this->tam = nuevoValor;

    else if (!strcmp (atributo, "inte"))
	this->inte = nuevoValor;

    else if (!strcmp(atributo, "des"))
	this->des = nuevoValor;

    else if (!strcmp (atributo, "pg"))
	this->pg = nuevoValor;

    else if (!strcmp (atributo, "ene"))
	this->ene = nuevoValor;

    else if (!strcmp (atributo, "ham"))
	this->ham = nuevoValor;

    else if (!strcmp (atributo, "sed"))
	this->sed = nuevoValor;

    else if (!strcmp (atributo, "maxpg"))
	this->maxpg = nuevoValor;

    else if (!strcmp (atributo, "maxene"))
	this->maxene = nuevoValor;

    else if (!strcmp (atributo, "maxham"))
	this->maxham = nuevoValor;

    else if (!strcmp (atributo, "maxsed"))
	this->maxsed = nuevoValor;

    else if (!strcmp (atributo, "mh1"))
	this->mh1 = nuevoValor;

    else if (!strcmp (atributo, "mh2"))
	this->mh2 = nuevoValor;

    else if (!strcmp (atributo, "mmr"))
	this->mmr = nuevoValor;

    else if (!strcmp (atributo, "posx"))
	this->posx = nuevoValor;

    else if (!strcmp (atributo, "posy"))
	this->posy = nuevoValor;

    else if (!strcmp (atributo, "edif"))
	this->edif = nuevoValor;

    else if (!strcmp (atributo, "estu"))
	this->estu = nuevoValor;

    else if (!strcmp (atributo, "entr"))
	this->entr = nuevoValor;

    else if (!strcmp (atributo, "obj"))
	this->obj = nuevoValor;

    else if (!strcmp (atributo, "nturnos"))
	this->nturnos = nuevoValor;
    
    else
    {
	fprintf (stderr, "personaje.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/

/* Método que actualiza con un nuevo valor al atributo cuyo índice se
   especifica */
void Personaje::reAsignaAtributo (int atributo, int nuevoValor)
{
    if (atributo == 1)
	this->sock = nuevoValor;

    else if (atributo == 2)
	this->esp = nuevoValor;

    else if (atributo == 3)
	this->fue = nuevoValor;

    else if (atributo == 4)
	this->con = nuevoValor;

    else if (atributo == 5)
	this->tam = nuevoValor;

    else if (atributo == 6)
	this->inte = nuevoValor;

    else if (atributo == 7)
	this->des = nuevoValor;

    else if (atributo == 8)
	this->pg = nuevoValor;

    else if (atributo == 9)
	this->ene = nuevoValor;

    else if (atributo == 10)
	this->ham = nuevoValor;

    else if (atributo == 11)
	this->sed = nuevoValor;

    else if (atributo == 12)
	this->maxpg = nuevoValor;

    else if (atributo == 13)
	this->maxene = nuevoValor;

    else if (atributo == 14)
	this->maxham = nuevoValor;

    else if (atributo == 15)
	this->maxsed = nuevoValor;

    else if (atributo == 16)
	this->mh1 = nuevoValor;

    else if (atributo == 17)
	this->mh2 = nuevoValor;

    else if (atributo == 18)
	this->mmr = nuevoValor;

    else if (atributo == 19)
	this->posx = nuevoValor;

    else if (atributo == 20)
	this->posy = nuevoValor;

    else if (atributo == 21)
	this->edif = nuevoValor;

    else if (atributo == 22)
	this->estu = nuevoValor;

    else if (atributo == 23)
	this->entr = nuevoValor;

    else if (atributo == 24)
	this->obj = nuevoValor;

    else if (atributo == 25)
	this->nturnos = nuevoValor;
    
    else
    {
	fprintf (stderr, "personaje.cc::reAsignaAtributo (char *, int): ");
	fprintf (stderr, "El atributo %s no existe\n", atributo);
	exit (-1);
    }    
}

/***************************************************************************/

// Método consultor que devuelve el tamaño del equipo
int Personaje::obtieneTamEqu (void)
{
    return this->tamEqu;
}

/***************************************************************************/

/* Método consultor que devuelve el valor del elemento del equipo cuya
   posición se especifica */
int Personaje::obtieneEqu (int posicion)
{
    if ((posicion < 0) || (posicion >= this->tamEqu))
    {
	fprintf (stderr, "personaje.cc::obtieneEqu (int): ");
	fprintf (stderr, "La posición debe estar en el rango [0-%d]\n",
		 this->tamEqu-1);
	exit (-1);
    }

    return this->equ[posicion];
}

/***************************************************************************/
  
/* Método que actualiza con un nuevo valor al elemento del equipo cuya 
   posición se especifica */
void Personaje::reAsignaEqu (int posicion, int nuevoValor)
{
    if ((posicion < 0) || (posicion >= this->tamEqu))
    {
	fprintf (stderr, "personaje.cc::reAsignaEqu (int, int): ");
	fprintf (stderr, "La posición debe estar en el rango [0-%d]\n",
		 this->tamEqu-1);
	exit (-1);
    }

    this->equ[posicion] = nuevoValor;
}

/***************************************************************************/
