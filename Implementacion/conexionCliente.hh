
/***************************************************************************
                       conexionCliente.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _CONEXION_CLIENTE_HH
#define _CONEXION_CLIENTE_HH
 
class ConexionCliente
{
    /* Clase que implementa una interfaz de conexión para un cliente que se
       pueda conectar a un servidor en base a una arquitectura 
       cliente/servidor */

 private:
    int sock;  // Socket para la conexión del cliente al servidor
    
 public:
    ConexionCliente (int familia, int servicio, int protocolo);
    /* Constructor del objeto ConexionCliente que crea una interfaz socket con 
       los parámetros especificados */

    ~ConexionCliente ();
    /* Destructor del objeto ConexionCliente que cierra el socket creado en el 
       constructor */

    void conectaAServidor (int familia, int direccion, int puerto);
    /* Método que conecta un cliente al servidor a través del socket creado
       en el constructor y con los parámetros especificados */

    void enviaDatos (void *datos, size_t nbytes);
    /* Método que envía la información especificada al servidor a través del 
       socket creado en el constructor */

    void recibeDatos (void *datos, size_t nbytes);
    /* Método que recibe la información del servidor en el parámetro 
       especificado a través del socket creado en el constructor */
};

#endif 

/****************************************************************************/
