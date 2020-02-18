
/***************************************************************************
                        conexionServidor.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _CONEXION_SERVIDOR_HH
#define _CONEXION_SERVIDOR_HH

class ConexionServidor
{
    /* Clase que implementa una interfaz de conexión para un servidor al que
       se puedan conectar un número indeterminado de clientes en base a una 
       arquitectura cliente/servidor */

 private:
    int sock;  // Socket para la conexión con el cliente
    
 public:
    ConexionServidor (int familia, int servicio, int protocolo);
    /* Constructor del objeto ConexionServidor que crea una interfaz socket 
       con los parámetros especificados */

    ~ConexionServidor ();
    /* Destructor del objeto ConexionServidor que cierra el socket creado en el
       constructor */

    void asignaConexion (int familia, int direccion, int puerto);
    /* Método que asigna al socket creado en el constructor los parámetros
       especificados */

    void abreConexion (int tamanoMax);
    /* Método que abre en modo de escucha el socket creado en el constructor 
       indicandole el tamaño máximo de peticiones pendientes que puede haber */

    int aceptaCliente (void);
    /* Método encargado de aceptar las conexiones de los clientes que se
       conectan al servidor. Devuelve un nuevo socket asociado al cliente 
       conectado */

    void desconectaCliente (int cliente);
    // Método encargado de cerrar el socket del cliente especificado

    void enviaDatos (void *datos, size_t nbytes, int cliente);
    /* Método que envía la información indicada a través del socket del 
       cliente especificado */

    void recibeDatos (void *datos, size_t nbytes, int cliente);
    /* Método que recibe la información en el parámetro indicado a través 
       del socket del cliente especificado */
};

#endif 

/****************************************************************************/
