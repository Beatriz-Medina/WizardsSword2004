
/***************************************************************************
                        conexionServidor.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#ifndef _CONEXION_SERVIDOR_HH
#define _CONEXION_SERVIDOR_HH

class ConexionServidor
{
    /* Clase que implementa una interfaz de conexi�n para un servidor al que
       se puedan conectar un n�mero indeterminado de clientes en base a una 
       arquitectura cliente/servidor */

 private:
    int sock;  // Socket para la conexi�n con el cliente
    
 public:
    ConexionServidor (int familia, int servicio, int protocolo);
    /* Constructor del objeto ConexionServidor que crea una interfaz socket 
       con los par�metros especificados */

    ~ConexionServidor ();
    /* Destructor del objeto ConexionServidor que cierra el socket creado en el
       constructor */

    void asignaConexion (int familia, int direccion, int puerto);
    /* M�todo que asigna al socket creado en el constructor los par�metros
       especificados */

    void abreConexion (int tamanoMax);
    /* M�todo que abre en modo de escucha el socket creado en el constructor 
       indicandole el tama�o m�ximo de peticiones pendientes que puede haber */

    int aceptaCliente (void);
    /* M�todo encargado de aceptar las conexiones de los clientes que se
       conectan al servidor. Devuelve un nuevo socket asociado al cliente 
       conectado */

    void desconectaCliente (int cliente);
    // M�todo encargado de cerrar el socket del cliente especificado

    void enviaDatos (void *datos, size_t nbytes, int cliente);
    /* M�todo que env�a la informaci�n indicada a trav�s del socket del 
       cliente especificado */

    void recibeDatos (void *datos, size_t nbytes, int cliente);
    /* M�todo que recibe la informaci�n en el par�metro indicado a trav�s 
       del socket del cliente especificado */
};

#endif 

/****************************************************************************/
