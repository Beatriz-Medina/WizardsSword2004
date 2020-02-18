
/***************************************************************************
                       conexionCliente.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include "conexionCliente.hh"

/***************************************************************************/

/* Constructor del objeto ConexionCliente que crea una interfaz socket con 
   los parámetros especificados */
ConexionCliente::ConexionCliente (int familia, int servicio, int protocolo)
{
    // Creación del socket para la conexión del cliente con el servidor
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
    // Cierre del socket de conexión con el servidor
    close (this->sock);
}

/***************************************************************************/

/* Método que conecta un cliente al servidor a través del socket creado
   en el constructor y con los parámetros especificados */
void ConexionCliente::conectaAServidor (int familia, int direccion, int puerto)
{
    struct sockaddr_in sockDescrip;
    int error;

    // Asignación de los parámetros del socket 
    sockDescrip.sin_family = familia;
    sockDescrip.sin_addr.s_addr = direccion;
    sockDescrip.sin_port = puerto; 
    
    // Conexión del cliente al servidor a través del socket 
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

/* Método que envía la información especificada al servidor a través del 
   socket creado en el constructor */
void ConexionCliente::enviaDatos (void *datos, size_t nbytes)
{
    int error;

    // Envío de la información 
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

/* Método que recibe la información del servidor en el parámetro 
   especificado a través del socket creado en el constructor */
void ConexionCliente::recibeDatos(void *datos, size_t nbytes)
{
    int error;    

    // Recepción de datos
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
