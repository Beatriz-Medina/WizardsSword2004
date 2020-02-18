
/***************************************************************************
                          envio.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include "envio.hh"

/***************************************************************************/

// Constructor del objeto Envio que inicializa sus par�metros a VACIO
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

// M�todo consultor que devuelve el socket del objeto    
int Envio::obtieneSock (void)
{
    return this->sock;
}

/***************************************************************************/

// M�todo consultor que devuelve el flag de envio del objeto
int Envio::obtieneEnv (void)
{
    return this->env;
}

/***************************************************************************/

// M�todo que actualiza el atributo socket con el valor especificado
void Envio::reAsignaSock (int nuevoValor)
{
    this->sock = nuevoValor;
}

/***************************************************************************/

// M�todo que actualiza el atributo env con el valor especificado
void Envio::reAsignaEnv (int nuevoValor)
{
    this->env = nuevoValor;
}

/***************************************************************************/
