
/***************************************************************************
                          casilla.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _CASILLA_HH
#define _CASILLA_HH

#define VACIO -1

class Casilla
{
    /* Clase que implementa los atributos de una casilla del juego
   
       tipo:     Tipo de casilla
                 0 -> Hierba
		 1 -> Tierra
		 2 -> Piedra
		 3 -> Poza de agua
		 4 -> Interior casas
		 5 -> Interior castillos	 
       
       posx:     Posición x de la casilla
       posy:     Posición y de la casilla

       nAtr:     Número de atributos del objeto Casilla

    */

 private:
    int tipo;
    int posx;
    int posy;
    int nAtr;

 public:
    Casilla ();
    /* Constructor del objeto Casilla que inicializa todos sus atributos a 
       VACIO */

    ~Casilla ();
    // Destructor del objeto Casilla

    int obtieneNAtributos (void);
    // Método consultor que devuelve el número de atributos del objeto Casilla

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
