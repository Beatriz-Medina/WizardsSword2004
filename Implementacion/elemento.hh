
/***************************************************************************
                          elemento.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _ELEMENTO_HH
#define _ELEMENTO_HH

#define VACIO -1

class Elemento
{
    /* Clase utilizada para indicar el tipo y la posición en la lista de un 
       elemento del juego como son los objetos y los personajes */
   
 private:
    int tipo;      // Tipo de elemento: 0 (Personaje), 1 (Objeto)
    int posicion;  // Posicion del elemento en su lista correspondiente
    int nAtr;      // Número de atributos del objeto elemento

 public:
    Elemento ();
    /* Constructor del objeto Elemento que inicializa todos sus atributos a 
       VACIO */

    ~Elemento ();
    // Destructor del objeto Elemento

    int obtieneNAtributos (void);
    // Método consultor que devuelve el número de atributos del objeto Elemento

    int obtieneAtributo (char *atributo);
    /* Método consultor que devuelve el valor del atributo cuyo nombre se 
       especifica */ 

    int obtieneAtributo (int atributo);
    /* Método consultor que devuelve el valor del atributo cuyo índice se 
       especifica */ 
    
    void reAsignaAtributo (char *atributo, int nuevoValor);
    /* Método que actualiza con un nuevo valor al atributo cuyo nombre se
       especifica */    

    void reAsignaAtributo (int atributo, int nuevoValor);
    /* Método que actualiza con un nuevo valor al atributo cuyo índice se
       especifica */    
};

#endif 

/****************************************************************************/
