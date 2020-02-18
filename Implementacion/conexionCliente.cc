
/***************************************************************************
                       conexionCliente.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include "conexionCliente.hh"

/***************************************************************************/

/* Constructor del objeto ConexionCliente que crea una interfaz socket con 
   los par�metros especificados */
ConexionCliente::ConexionCliente (int familia, int servicio, int protocolo)
{
    // Creaci�n del socket para la conexi�n del cliente con el servidor
    this->sock = socket (familia, servicio, protocolo);
    if (this->sock == -1)
    {
	fprintf (stderr, "conexionCliente.cc::ConexionCliente ");
	fprintf (stderr, " (int, int, int): ");
	fprintf (stderr, "No se puede crear el socket\n");
	exit (-1);
    }   
}

/***************************************************************************/

/* Destructor del objeto ConexionCliente que cierra el socket creado en el 
   constructor */
ConexionCliente::~ConexionCliente ()
{
    // Cierre del socket de conexi�n con el servidor
    close (this->sock);
}

/***************************************************************************/

/* M�todo que conecta un cliente al servidor a trav�s del socket creado
   en el constructor y con los par�metros especificados */
void ConexionCliente::conectaAServidor (int familia, int direccion, int puerto)
{
    struct sockaddr_in sockDescrip;
    int error;

    // Asignaci�n de los par�metros del socket 
    sockDescrip.sin_family = familia;
    sockDescrip.sin_addr.s_addr = direccion;
    sockDescrip.sin_port = puerto; 
    
    // Conexi�n del cliente al servidor a trav�s del socket 
    error = connect (this->sock, (struct sockaddr *) &sockDescrip, 
		     sizeof (sockDescrip));
    if (error == -1)
    {
	fprintf (stderr, "conexionCliente.cc::conectaAServidor ");
	fprintf (stderr, "(int, int, int): ");
	fprintf (stderr, "No se puede conectar el cliente al servidor\n");
	exit (-1);
    }
}

/***************************************************************************/

/* M�todo que env�a la informaci�n especificada al servidor a trav�s del 
   socket creado en el constructor */
void ConexionCliente::enviaDatos (void *datos, size_t nbytes)
{
    int error;

    // Env�o de la informaci�n 
    error = send (this->sock, datos, nbytes, 0);    
    if (error == -1)
    {
	fprintf (stderr, "conexionCliente.cc::enviaDatos ");
	fprintf (stderr, "(void *, size_t): ");
	fprintf (stderr, "No se pueden enviar datos al servidor\n");
	exit (-1);
    }
}

/***************************************************************************/

/* M�todo que recibe la informaci�n del servidor en el par�metro 
   especificado a trav�s del socket creado en el constructor */
void ConexionCliente::recibeDatos(void *datos, size_t nbytes)
{
    int error;    

    // Recepci�n de datos
    error = recv (this->sock, datos, nbytes, 0);
    if (error == -1)
    {
	fprintf (stderr, "conexionCliente.cc::recibeDatos ");
	fprintf (stderr, "(void *, size_t): ");
	fprintf (stderr, "No se pueden recibir datos del servidor\n");
	exit (-1);
    }    
}

/***************************************************************************/
