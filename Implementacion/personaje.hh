
/***************************************************************************
                         personaje.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _PERSONAJE_HH
#define _PERSONAJE_HH

#define VACIO -1

class Personaje
{
    /* Clase que implementa los atributos de un personaje del juego       

       sock:     Socket del cliente

       esp:      Especie a la que pertenece el personaje
                 0 -> humano
		 1 -> hobbit
		 2 -> elfo
		 3 -> gigante
		 4 -> mono

       fue:      Fuerza del personaje (limitada por con + tam)
       con:      Constitución del personaje (limitada por fue + tam)
       tam:      Tamaño del personaje
       inte:     Inteligencia del personaje
       des:      Destreza del personaje (limitada por des * 2)

       pg:       Puntos de golpe del personaje (media alta de con y tam) 
       ene:      Energía del personaje (fue + con)
       ham:      Hambre del personaje (con + tam)
       sed:      Sed del personaje (con + tam)

       maxpg:    Límite de pg
       maxene:   Límite de ene
       maxham:   Límite de ham
       maxsed:   Límite de sed
       
       mh1:      Modificador de habilidad del personaje (sigilo)
       mh2:      Modificador de habilidad del personaje (percepción)

       mmr:      Momento de reacción del personaje

       posx:     Posición x del personaje
       posy:     Posición y del personaje

       edif:     Identificador del edificio donde se encuentra el personaje 
                 o VACIO si no se encuentra en ninguno

       estu:     Contador que acumula el número de estudios realizados
       entr:     Contador que acumula el número de entrenamientos realizados
       obj:      Indicador de la misión asignada asociada al entrenamiento

       nturnos:  Contador del número de turnos que puede utilizar el personaje

       nAtr:     Número de atributos del objeto Personaje

       equ:      Equipo o inventario del personaje 
                 Vector de elementos[0, 1,..., 5]
		 Posición 0 -> escudo
		 Posición 1 -> arma 
		 Posición 2 -> armadura 
		 Posición 3 -> número de monedas de oro
		 Posición 4 -> llave
		 Posición 5 -> poción

       tamEqu:   Tamaño del equipo

    */

 private:
    int sock;    
    int esp;                        
    int fue;
    int con;
    int tam;
    int inte;
    int des;
    int pg;
    int ene;
    int ham;
    int sed;
    int maxpg;
    int maxene;
    int maxham;
    int maxsed;
    int mh1;
    int mh2;
    int mmr;
    int posx;
    int posy;
    int edif;
    int estu;
    int entr;
    int obj;
    int nturnos;
    int nAtr;
    int *equ;
    int tamEqu;

 public:
    Personaje ();
    /* Constructor del objeto Personaje que inicializa todos sus atributos
       a VACIO */

    ~Personaje ();
    // Destructor del objeto Personaje

    int obtieneNAtributos (void);
    /* Método consultor que devuelve el número de atributos del objeto 
       personaje */

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

    int obtieneTamEqu (void);
    // Método consultor que devuelve el tamaño del equipo

    int obtieneEqu (int posicion);
    /* Método consultor que devuelve el valor del elemento del equipo cuya
       posición se especifica */
    
    void reAsignaEqu (int posicion, int nuevoValor);
    /* Método que actualiza con un nuevo valor al elemento del equipo cuya 
       posición se especifica */
};

#endif 

/****************************************************************************/
