
/***************************************************************************
                           lista.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _LISTA_HH
#define _LISTA_HH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ulong unsigned long

/***************************************************************************/

template <class tipo> 
class Lista 
{
    /* Clase plantilla que implementa una lista ordenada de elementos de 
       cualquier tipo */

 private:
    tipo *elemento;     // Array paramétrico de elementos
    ulong tamano;       // Tamaño del array de elementos

 public:
    Lista ();
    // Constructor del objeto Lista que inicializa una lista vacía

    ~Lista ();
    // Destructor del objeto Lista

    ulong obtieneTamano (void);
    // Método consultor que devuelve el tamaño actual de la lista

    tipo obtieneElemento (ulong posicion);
    // Método consultor que devuelve el elemento de la posición especificada

    void insertaElemento (tipo nuevoElemento);
    // Método que inserta un nuevo elemento al final de la lista

    void eliminaElemento (ulong posicion);
    // Método que elimina un elemento dado en la posición especificada

    void reAsignaElemento (ulong posicion, tipo nuevoElemento);
    /* Método que actualiza un elemento dado en la posición especificada
       con un nuevo elemento */ 
};

/***************************************************************************/

// Constructor del objeto Lista que inicializa una lista vacía 
template <class tipo> 
Lista<tipo>::Lista ()
{
    // Inicialización de los parámetros de la lista
    this->elemento = NULL;
    this->tamano = 0;
}

/***************************************************************************/

// Destructor del objeto Lista
template <class tipo>
Lista<tipo>::~Lista ()
{    
    if (this->elemento != NULL)
    {           
	delete [] this->elemento;
	this->elemento = NULL;
	this->tamano = 0;    
    }
}

/***************************************************************************/

// Método consultor que devuelve el tamaño actual de la lista
template <class tipo>
ulong Lista<tipo>::obtieneTamano (void)
{
    return this->tamano;
}

/***************************************************************************/

// Método consultor que devuelve el elemento de la posición especificada
template <class tipo>
tipo Lista<tipo>::obtieneElemento (ulong posicion)
{
    // Comprobación de lista vacía
    if (this->tamano == 0)
    {
	fprintf (stderr, "lista.cc::obtieneElemento (ulong): ");
	fprintf (stderr, "La lista está vacía\n");
	exit (-1);
    }

    // Comprobación de posición inválida
    if ((posicion < 0) || (posicion >= this->tamano))
    {
	fprintf (stderr, "lista.cc::obtieneElemento (ulong): ");
	fprintf (stderr, "La posición debe estar en el rango ");
	fprintf (stderr, "[0-%d]\n", this->tamano - 1);
	exit (-1);
    }

    return (this->elemento[posicion]);
}

/***************************************************************************/

// Método que inserta un nuevo elemento al final de la lista
template <class tipo>
void Lista<tipo>::insertaElemento (tipo nuevoElemento)
{
    tipo *aux;

    // Reserva de un array auxiliar con tamaño 1 más para el nuevo elemento
    aux = new tipo[this->tamano + 1];
    if (aux == NULL)
    {
	fprintf (stderr, "lista.cc::insertaElemento (tipo): ");
	fprintf (stderr, "Memoria insuficiente\n");
	exit (-1);
    }
    
    // Copia de los elementos anteriores en el array auxiliar
    if (this->tamano > 0)    
	memcpy (aux, this->elemento, this->tamano * sizeof (tipo));	
    
    // Inserción del nuevo elemento en el array auxiliar
    aux[this->tamano] = nuevoElemento;

    // Actualización del array de elementos
    delete [] this->elemento;
    this->elemento = aux;
    this->tamano ++;
}

/***************************************************************************/

// Método que elimina un elemento dado en la posición especificada
template <class tipo>
void Lista<tipo>::eliminaElemento (ulong posicion)
{
    tipo *aux;

    // Comprobación de lista vacía
    if (this->tamano == 0)
    {
	fprintf (stderr, "lista.cc::eliminaElemento (ulong): ");
	fprintf (stderr, "La lista está vacía\n");
	exit (-1);
    }

    // Comprobación de posición inválida
    if ((posicion < 0) || (posicion >= this->tamano))
    {
	fprintf (stderr, "lista.cc::eliminaElemento (ulong): ");
	fprintf (stderr, "La posición debe estar en el rango ");
	fprintf (stderr, "[0-%d]\n", this->tamano - 1);
       	exit (-1);
    }

    // Reserva de un array auxiliar con tamaño 1 menos para el elemento
    aux = new tipo[this->tamano - 1];
    if (aux == NULL)
    {
	fprintf (stderr, "lista.cc::eliminaElemento (ulong): ");
	fprintf (stderr, "Memoria insuficiente\n");
	exit (-1);
    }

    // Copia de los elementos anteriores y posteriores al elemento 
    if (posicion > 0)
    {
	memcpy (aux, this->elemento, posicion * sizeof (tipo));
	if (posicion < this->tamano - 1)	
	    memcpy (aux+posicion, this->elemento + posicion + 1, 
		   (this->tamano - posicion - 1) * sizeof (tipo));	
    }
    else
	memcpy(aux, this->elemento + 1, (this->tamano - 1) * sizeof (tipo));
	
    // Actualización del array de elementos
    delete [] this->elemento;
    this->elemento = aux;
    this->tamano --;
}		

/***************************************************************************/

/* Método que actualiza un elemento dado en la posición especificada
   con un nuevo elemento */
template <class tipo>
void Lista<tipo>::reAsignaElemento (ulong posicion, tipo nuevoElemento)
{
    // Comprobación de lista vacía
    if (this->tamano == 0)
    {
	fprintf (stderr, "lista.cc::reAsignaElemento (tipo, ulong): ");
	fprintf (stderr, "La lista está vacía\n");
	exit (-1);
    }
    
    // Comprobación de posición inválida
    if ((posicion < 0) || (posicion >= this->tamano))
    {
	fprintf (stderr, "lista.cc::reAsignaElemento (tipo, ulong): ");
	fprintf (stderr, "La posición debe estar en el ");
	fprintf (stderr, "rango [0-%d]\n", this->tamano - 1);
       	exit (-1);
    }

    this->elemento[posicion] = nuevoElemento;
}

#endif

/***************************************************************************/
