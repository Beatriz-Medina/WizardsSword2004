
/***************************************************************************
                          casilla.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
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
       
       posx:     Posici�n x de la casilla
       posy:     Posici�n y de la casilla

       nAtr:     N�mero de atributos del objeto Casilla

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
    // M�todo consultor que devuelve el n�mero de atributos del objeto Casilla

    int obtieneAtributo (char *atributo);
    /* M�todo consultor que devuelve el valor del atributo cuyo nombre se 
       especifica */ 

    int obtieneAtributo (int atributo);
    /* M�todo consultor que devuelve el valor del atributo cuyo �ndice se 
       especifica */ 
    
    void reAsignaAtributo (char *atributo, int nuevoValor);
    /* M�todo que actualiza con un nuevo valor al atributo cuyo nombre se
       especifica */    

    void reAsignaAtributo (int atributo, int nuevoValor);
    /* M�todo que actualiza con un nuevo valor al atributo cuyo �ndice se
       especifica */    
};

#endif 

/****************************************************************************/
