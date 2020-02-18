
/***************************************************************************
                       conexionCliente.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#ifndef _CONEXION_CLIENTE_HH
#define _CONEXION_CLIENTE_HH
 
class ConexionCliente
{
    /* Clase que implementa una interfaz de conexi�n para un cliente que se
       pueda conectar a un servidor en base a una arquitectura 
       cliente/servidor */

 private:
    int sock;  // Socket para la conexi�n del cliente al servidor
    
 public:
    ConexionCliente (int familia, int servicio, int protocolo);
    /* Constructor del objeto ConexionCliente que crea una interfaz socket con 
       los par�metros especificados */

    ~ConexionCliente ();
    /* Destructor del objeto ConexionCliente que cierra el socket creado en el 
       constructor */

    void conectaAServidor (int familia, int direccion, int puerto);
    /* M�todo que conecta un cliente al servidor a trav�s del socket creado
       en el constructor y con los par�metros especificados */

    void enviaDatos (void *datos, size_t nbytes);
    /* M�todo que env�a la informaci�n especificada al servidor a trav�s del 
       socket creado en el constructor */

    void recibeDatos (void *datos, size_t nbytes);
    /* M�todo que recibe la informaci�n del servidor en el par�metro 
       especificado a trav�s del socket creado en el constructor */
};

#endif 

/****************************************************************************/
