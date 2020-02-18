
/***************************************************************************
                          envio.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#include "envio.hh"

/***************************************************************************/

// Constructor del objeto Envio que inicializa sus parámetros a VACIO
Envio::Envio ()
{
    this->sock = VACIO;
    this->env = VACIO;
}

/***************************************************************************/

// Destructor del objeto Envio
Envio::~Envio ()
{}

/***************************************************************************/

// Método consultor que devuelve el socket del objeto    
int Envio::obtieneSock (void)
{
    return this->sock;
}

/***************************************************************************/

// Método consultor que devuelve el flag de envio del objeto
int Envio::obtieneEnv (void)
{
    return this->env;
}

/***************************************************************************/

// Método que actualiza el atributo socket con el valor especificado
void Envio::reAsignaSock (int nuevoValor)
{
    this->sock = nuevoValor;
}

/***************************************************************************/

// Método que actualiza el atributo env con el valor especificado
void Envio::reAsignaEnv (int nuevoValor)
{
    this->env = nuevoValor;
}

/***************************************************************************/
