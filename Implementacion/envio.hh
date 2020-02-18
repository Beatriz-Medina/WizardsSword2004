
/***************************************************************************
                          envio.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#ifndef _ENVIO_HH
#define _ENVIO_HH

#define VACIO -1

class Envio
{
    /* Clase utilizada para indicar si un socket cliente va a enviar datos al 
       servidor */

 private:
    int sock;        // Socket del cliente
    int env;         // Flag que indica si se env�an datos o no 
                     // 0 -> No se env�an datos
                     // 1 -> Se env�an s�lo los elementos
                     // 2 -> Se env�a todo
                     
 public:
    Envio ();
    // Constructor del objeto Envio que inicializa sus par�metros a VACIO

    ~Envio ();
    // Destructor del objeto Envio

    int obtieneSock (void);
    // M�todo consultor que devuelve el socket del objeto    

    int obtieneEnv (void);
    // M�todo consultor que devuelve el flag de envio del objeto

    void reAsignaSock (int nuevoValor);
    // M�todo que actualiza el atributo socket con el valor especificado

    void reAsignaEnv (int nuevoValor);
    // M�todo que actualiza el atributo env con el valor especificado
};

#endif 

/****************************************************************************/
