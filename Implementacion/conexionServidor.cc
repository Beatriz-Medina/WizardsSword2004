
/***************************************************************************
                      conexionServidor.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include "conexionServidor.hh"

/***************************************************************************/

/* Constructor del objeto ConexionServidor que crea una interfaz socket 
   con los par�metros especificados */
ConexionServidor::ConexionServidor (int familia, int servicio, int protocolo)
{
    // Creaci�n del socket para la conexi�n del servidor con los clientes
    this->sock = socket (familia, servicio, protocolo);
    if (this->sock == -1)
    {
	fprintf (stderr, "conexionServidor.cc::ConexionServidor ");
	fprintf (stderr, "(int, int, int): ");
	fprintf (stderr, "No se puede crear el socket\n");
	exit (-1);
    }
}

/***************************************************************************/

/* Destructor del objeto ConexionServidor que cierra el socket creado en el
   constructor */
ConexionServidor::~ConexionServidor ()
{
    // Cierre del socket de conexi�n con los clientes
    close (this->sock);
}

/***************************************************************************/

/* M�todo que asigna al socket creado en el constructor los par�metros
   especificados */
void ConexionServidor::asignaConexion (int familia, int direccion, int puerto)
{
    struct sockaddr_in sockDescrip;
    int error;

    // Asignaci�n de los par�metros del socket 
    sockDescrip.sin_family = familia;
    sockDescrip.sin_addr.s_addr = direccion;
    sockDescrip.sin_port = puerto; 

    // Asignaci�n del socket
    error = bind (this->sock, (struct sockaddr *) &sockDescrip, 
		  sizeof (sockDescrip));
    if (error == -1)
    {
	fprintf (stderr, "conexionServidor.cc::asignaConexion "); 
	fprintf (stderr, "(int, int, int): ");
	fprintf (stderr, "No se puede asignar el socket\n");
	exit (-1);
    }
}

/***************************************************************************/

/* M�todo que abre en modo de escucha el socket creado en el constructor 
   indicandole el tama�o m�ximo de peticiones pendientes que puede haber */
void ConexionServidor::abreConexion (int tamanoMax)
{
    int error;

    // Apertura pasiva del socket en modo escucha
    error = listen (this->sock, tamanoMax);
    if (error == -1)
    {
	fprintf (stderr, "conexionServidor.cc::abreConexion (int): "); 
	fprintf (stderr, "No se puede abrir el socket en modo escucha\n");
	exit (-1);
    }
}

/***************************************************************************/

/* M�todo encargado de aceptar las conexiones de los clientes que se
   conectan al servidor. Devuelve un nuevo socket asociado al cliente 
   conectado */
int ConexionServidor::aceptaCliente (void)
{
    struct sockaddr_in sockCliente; 
    int aceptado, tamanoSockCliente;
    
    // Aceptaci�n de la conexi�n con el cliente
    tamanoSockCliente = sizeof (sockCliente);
    aceptado = accept (this->sock, (struct sockaddr *) &sockCliente, 
		      (socklen_t *) &tamanoSockCliente);

    return aceptado;
}

/***************************************************************************/

// M�todo encargado de cerrar el socket del cliente especificado
void ConexionServidor::desconectaCliente (int cliente)
{
    // Cierre del socket de conexi�n con el cliente
    close (cliente);
}

/***************************************************************************/

/* M�todo que env�a la informaci�n indicada a trav�s del socket del cliente 
   especificado */
void ConexionServidor::enviaDatos (void *datos, size_t nbytes, int cliente)
{
    int error;

    // Env�o de datos
    error = send (cliente, datos, nbytes, 0);
    if (error == -1)
    {
	fprintf (stderr, "conexionServidor.cc::enviaDatos ");
	fprintf (stderr, "(void*, size_t, int): ");
	fprintf (stderr, "No se pueden enviar datos al cliente\n");
	exit (-1);
    }
}

/***************************************************************************/

/* M�todo que recibe la informaci�n en el par�metro indicado a trav�s del 
   socket del cliente especificado */
void ConexionServidor::recibeDatos (void *datos, size_t nbytes, int cliente)
{
    int error;    

    // Recepci�n de datos
    error = recv (cliente, datos, nbytes, 0);
    if (error == -1)
    {
	fprintf (stderr, "conexionServidor.cc::recibeDatos ");
	fprintf (stderr, "(void*, size_t, int): ");
	fprintf (stderr, "No se pueden recibir datos del cliente\n");
	exit (-1);
    }    
}

/***************************************************************************/
