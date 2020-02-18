
/***************************************************************************
                          envio.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
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
    int env;         // Flag que indica si se envían datos o no 
                     // 0 -> No se envían datos
                     // 1 -> Se envían sólo los elementos
                     // 2 -> Se envía todo
                     
 public:
    Envio ();
    // Constructor del objeto Envio que inicializa sus parámetros a VACIO

    ~Envio ();
    // Destructor del objeto Envio

    int obtieneSock (void);
    // Método consultor que devuelve el socket del objeto    

    int obtieneEnv (void);
    // Método consultor que devuelve el flag de envio del objeto

    void reAsignaSock (int nuevoValor);
    // Método que actualiza el atributo socket con el valor especificado

    void reAsignaEnv (int nuevoValor);
    // Método que actualiza el atributo env con el valor especificado
};

#endif 

/****************************************************************************/
