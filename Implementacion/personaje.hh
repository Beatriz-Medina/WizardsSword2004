
/***************************************************************************
                         personaje.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
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
       con:      Constituci�n del personaje (limitada por fue + tam)
       tam:      Tama�o del personaje
       inte:     Inteligencia del personaje
       des:      Destreza del personaje (limitada por des * 2)

       pg:       Puntos de golpe del personaje (media alta de con y tam) 
       ene:      Energ�a del personaje (fue + con)
       ham:      Hambre del personaje (con + tam)
       sed:      Sed del personaje (con + tam)

       maxpg:    L�mite de pg
       maxene:   L�mite de ene
       maxham:   L�mite de ham
       maxsed:   L�mite de sed
       
       mh1:      Modificador de habilidad del personaje (sigilo)
       mh2:      Modificador de habilidad del personaje (percepci�n)

       mmr:      Momento de reacci�n del personaje

       posx:     Posici�n x del personaje
       posy:     Posici�n y del personaje

       edif:     Identificador del edificio donde se encuentra el personaje 
                 o VACIO si no se encuentra en ninguno

       estu:     Contador que acumula el n�mero de estudios realizados
       entr:     Contador que acumula el n�mero de entrenamientos realizados
       obj:      Indicador de la misi�n asignada asociada al entrenamiento

       nturnos:  Contador del n�mero de turnos que puede utilizar el personaje

       nAtr:     N�mero de atributos del objeto Personaje

       equ:      Equipo o inventario del personaje 
                 Vector de elementos[0, 1,..., 5]
		 Posici�n 0 -> escudo
		 Posici�n 1 -> arma 
		 Posici�n 2 -> armadura 
		 Posici�n 3 -> n�mero de monedas de oro
		 Posici�n 4 -> llave
		 Posici�n 5 -> poci�n

       tamEqu:   Tama�o del equipo

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
    /* M�todo consultor que devuelve el n�mero de atributos del objeto 
       personaje */

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

    int obtieneTamEqu (void);
    // M�todo consultor que devuelve el tama�o del equipo

    int obtieneEqu (int posicion);
    /* M�todo consultor que devuelve el valor del elemento del equipo cuya
       posici�n se especifica */
    
    void reAsignaEqu (int posicion, int nuevoValor);
    /* M�todo que actualiza con un nuevo valor al elemento del equipo cuya 
       posici�n se especifica */
};

#endif 

/****************************************************************************/
