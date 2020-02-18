
/***************************************************************************
                          edificio.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#ifndef _EDIFICIO_HH
#define _EDIFICIO_HH

#define VACIO -1

class Edificio
{
    /* Clase que implementa los atributos de un edificio del juego
   
       id:       Identificador del edificio

       tipo:     Tipo de edificio
                 0 -> Castillo
		 1 -> Posada
		 2 -> Biblioteca
		 3 -> Tienda de armas
		 4 -> Tienda de escudos
		 5 -> Tienda de armaduras

       llav:     Flag que indica si el edificio est� cerrado o no con llave
                 0 -> No cerrado
		 1 -> Cerrado

       posx:     Posici�n x del edificio
       posy:     Posici�n y del edificio

       longx:    Longitud x del edificio
       longy:    Longitud y del edificio

       casilx:   N�mero de casillas que ocupa en el eje x
       casily:   N�mero de casillas que ocupa en el eje y
       
       nAtr:     N�mero de atributos del objeto Edificio

    */

 private:
    int id;
    int tipo;                      
    int llav;
    int posx;
    int posy;
    int longx;
    int longy;
    int casilx;
    int casily;
    int nAtr;

 public:
    Edificio ();
    /* Constructor del objeto Edificio que inicializa todos sus atributos a 
       VACIO */

    ~Edificio ();
    // Destructor del objeto Edificio

    int obtieneNAtributos (void);
    // M�todo consultor que devuelve el n�mero de atributos del objeto Edificio

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
