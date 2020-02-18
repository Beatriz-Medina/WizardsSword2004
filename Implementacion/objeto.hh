
/***************************************************************************
                           objeto.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _OBJETO_HH
#define _OBJETO_HH

#define VACIO -1

class Objeto
{
    /* Clase que implementa los atributos de un objeto del juego
       
       id:       Identificador del objeto

       tipo:     Tipo de objeto
                 0 -> arbol
		 1 -> setas
		 2 -> miel
		 3 -> cofre		 
		 4 -> bruja
		 5 -> candelabro
		 6 -> huesos
		 7 -> portal mágico
		 8 -> estatua
		 9 -> esclava1
		 10 -> esclava1 libre
		 11 -> esclava2
		 12 -> esclava2 libre
		 13 -> esclavo1
		 14 -> esclavo1 libre
		 15 -> esclavo2
		 16 -> esclavo2 libre
		 17 -> pinchos
		 18 -> bibliotecaria
		 19 -> mesa
		 20 -> biblioteca
		 21 -> posadera
		 22 -> cama
		 23 -> vela
		 24 -> escoba
		 25 -> armero
		 26 -> estatua con armadura
		 27 -> espada1
		 28 -> espada2
		 29 -> hacha
		 30 -> bola y cadena
		 31 -> escudo1
		 32 -> escudo2
		 33 -> escudo3
		 34 -> maniqui
		 35 -> cuero
		 36 -> cota de anillos
		 37 -> armadura
		 38 -> coraza

       visi:     Flag que indica si el objeto es visible o no
                 0 -> No visible
		 1 -> Visible
 
       posx:     Posición x del objeto
       posy:     Posición y del objeto

       longx:    Longitud x del objeto
       longy:    Longitud y del objeto

       casilx:   Número de casillas que ocupa en el eje x
       casily:   Número de casillas que ocupa en el eje y

       edif:     Identificador del edificio donde se encuentra el objeto 
                 o VACIO si no se encuentra en ninguno

       equ:      Tipo de objeto que contiene el objeto o VACIO si no contiene
                 nada
		 0     -> llave
		 1-10  -> poción (i) (i: 1->10)
		 11    -> monedas (50 unidades)

       nAtr:     Número de atributos del objeto Objeto

    */

 private:
    int id;
    int tipo;                      
    int visi;
    int posx;
    int posy;
    int longx;
    int longy;
    int casilx;
    int casily;
    int edif;
    int equ;
    int nAtr;

 public:
    Objeto ();
    // Constructor del objeto Objeto que inicializa todos sus atributos a VACIO
 
    ~Objeto ();
    // Destructor del objeto Objeto

    int obtieneNAtributos (void);
    // Método consultor que devuelve el número de atributos del objeto Objeto
    
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
