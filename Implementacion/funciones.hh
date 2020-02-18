
/***************************************************************************
                          funciones.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#ifndef _FUNCIONES_HH
#define _FUNCIONES_HH

#include "lista.cc"
#include "edificio.hh"
#include "objeto.hh"
#include "personaje.hh"
#include "casilla.hh"
#include "elemento.hh"
#include "envio.hh"
#include "conexionServidor.hh"
#include "conexionCliente.hh"

int obtieneClienteActivo (Lista<Personaje*> *listaClientes, int turno);
// Funci�n que devuelve el socket activo
 
void insertaEnvio (Lista<Envio*> *listaEnvios, int sock);
// Funci�n que inserta en la lista un nuevo elemento con el socket especificado

void eliminaEnvio (Lista<Envio*> *listaEnvios, int sock);
// Funci�n que elimina de la lista el elemento cuyo socket se especifica

int obtieneEnvio (Lista<Envio*> *listaEnvios, int sock);
/* Funci�n que devuelve el flag de env�o del elemento cuyo socket se especifica
   En caso de que el socket no exista devuelve -1 */

void reAsignaEnvio (Lista<Envio*> *listaEnvios, int sock, int nuevoEnv);
// Funci�n que modifica el flag de env�o del socket especificado

void activaEnvios (Lista<Envio*> *listaEnvios, int nuevoEnv);
/* Funci�n que pone el flag de env�o de todos los elementos de la lista con
   el valor especificado */

void enviaEnteroACliente (ConexionServidor *conexion, int sock, int entero);
// Funci�n que env�a un entero al cliente cuyo socket se especifica

int recibeEnteroDeCliente (ConexionServidor *conexion, int sock);
// Funci�n que recibe un entero del cliente cuyo socket se especifica

void enviaEnteroAServidor (ConexionCliente *conexion, int entero);
// Funci�n que env�a un entero al servidor

int recibeEnteroDeServidor (ConexionCliente *conexion);
// Funci�n que recibe un entero del servidor

void obtieneTamMundo (int *mundoInf, int *mundoSup, int *castilInf, 
		      int *castilSup, int *casaInf, int *casaSup);
// Funci�n que devuelve en las coordenadas indicadas el tama�o del mundo

Lista<Edificio*> *cargaEdificios (int xinf, int xsup, int yinf, int ysup);
/* Funci�n que devuelve una lista con todos los edificios del mundo que est�n 
   dentro del rango especificado */

Lista<Objeto*> *cargaObjetos (int xinf, int xsup, int yinf, int ysup, 
			      int edif);
/* Funci�n que devuelve una lista con todos los objetos del mundo que est�n 
   dentro del rango y edificio especificados */

Lista<Personaje*> *cargaPersonajes (int xinf, int xsup, int yinf, int ysup, 
				    Lista<Personaje*> *listaClientes, 
				    int edif);
/* Funci�n que devuelve una lista  a partir de la dada con todos los personajes
   del mundo que est�n dentro del rango y edificio especificados */

Lista<Casilla*> *cargaCasillas (int xinf, int xsup, int yinf, int ysup);
/* Funci�n que devuelve una lista con todas las casillas del mundo que est�n 
   dentro del rango especificado */

Lista<Elemento*> *ordenaListas (Lista<Personaje*> *listaP, 
				Lista<Objeto*> *listaObjetos);
/* Funci�n que devuelve una lista con los elementos de las dos listas 
   especificadas ordenados de mayor a menor profundidad */

Lista<Personaje*> *ordenaClientes (Lista<Personaje*> *listaClientes);
// Funci�n que ordena la lista de clientes por momento de reacci�n

void actualizaObjetos (Lista<Objeto*> *listaObjetos);
// Funci�n que actualiza el fichero de objetos con la lista especificada

void actualizaPersonajes (Lista<Personaje*> *listaP, 
			  Lista<Personaje*> *listaClientes);
// Funci�n que actualiza la lista de clientes con la lista de personajes dada

void insertaNuevosObjetos (Lista<Objeto*> *listaObjetos, 
			   Lista<Personaje*> *listaP, int xinf, int xsup, 
			   int yinf, int ysup);
/* Funci�n que inserta los objetos de la lista especificada en el fichero de
   objetos */

void iniciaObjetos (Lista<Objeto*> *listaObjetos, int edif);
/* Funci�n que asigna los objetos trampas a no visibles y los objetos 
   prisioneros a esclavos pertenecientes al edificio especificado */

Lista<Objeto*> *creaCofres (Lista<Personaje*> *listaP, int indiceP);
/* Funci�n que crea una lista de objetos cofres que incluyan el equipo
   del personaje de la lista especificada */

int obtieneIndice (Lista<Personaje*> *listaP, int sock);
/* Funci�n que devuelve el �ndice en la lista del personaje cuyo socket 
   coincide con el especificado 
   En caso de que no coincida se devuelve -1 */

int obtieneTipoEdificio (int edif, Lista<Edificio*> *listaEdificios);
/* Funci�n que devuelve el tipo del identificador de edificio especificado
   Devuelve -1 en caso de que no lo encuentre */

int coincideEdificio (int posx, int posy, Lista<Edificio*> *listaEdificios);
/* Funci�n que devuelve el �ndice de un edificio de la lista dada si la 
   posici�n especificada coincide con �l 
   En otro caso devuelve -1 */

int coincideObjeto (int posx, int posy, Lista<Objeto*> *listaObjetos);
/* Funci�n que devuelve el �ndice de un objeto de la lista dada si la 
   posici�n especificada coincide con �l 
   En otro caso devuelve -1 */

int coincidePersonaje (int posx, int posy, Lista<Personaje*> *listaP);
/* Funci�n que devuelve el �ndice de un personaje de la lista dada si la 
   posici�n especificada coincide con �l 
   En otro caso devuelve -1 */

int objetoTrampa (int posx, int posy, int *visible, 
		  Lista<Objeto*> *listaObjetos);
/* Funci�n que comprueba si el objeto de la lista con la posici�n especificada
   es de tipo trampa o no
   Se devuelve el identificador del objeto en caso de que sea una trampa
   En otro caso se devuelve -1
   En visible se devuelve si el objeto est� oculto o no */

void objetoVisible (Lista<Objeto*> *listaObjetos, int indiceO);
// Funci�n que activa el objeto de la lista especificada a visible

void liberaPrisionero (Lista<Personaje*> *listaP, int indiceP,
		       Lista<Objeto*> *listaObjetos, int indiceO);
/* Funci�n que cambia el tipo del objeto especificado incrementando el
   n�mero de monedas del personaje tambi�n indicado */

int tipoCasilla (int posx, int posy, Lista<Casilla*> *listaCasillas);
/* Funci�n que devuelve el tipo de casilla de la indicada en la lista
   En caso de que la casilla no exista devuelve -1 */

void obtienePosicion (int xinf, int xsup, int yinf, int ysup, 
		      int *posx, int *posy, Lista<Personaje*> *listaP);
/* Funci�n que devuelve una posici�n para un personaje que no sea coincidente 
   con la posici�n de ning�n otro elemento */

int tiraDado (int nveces, int ncaras);
// Funci�n que realiza ntiradas de un dado cuyo n�mero de caras se indica

int ajustaMD (int valor);
// Funci�n que ajusta el valor del md dado con una tirada de dados

int ajustaMH (char influencia, int caracteristica);
/* Funci�n que ajusta el valor de habilidad en funci�n de la influencia y
   la caracteristica dada */

int ajustaMMR (int tam, int des);
/* Funci�n que ajusta el momento de reacci�n en funci�n del tama�o y destreza
   especificados */

int ajustaNturnos (int mmr);
/* Funci�n que ajusta el n�mero de turnos en funci�n del momento de reacci�n
   especificado */

int tiradaMH (Lista<Personaje*> *listaP, int indiceP, int habilidad);
/* Funci�n que realiza una tirada de la habilidad especificada
   Devuelve 1 si ha tenido �xito
   En caso contrario devuelve 0 */

int enfrentaMH (Lista<Personaje*> *listaP, int indiceP1, int indiceP2);
/* Funci�n que devuelve 1 si el personaje1 especificado sale victorioso
   enfrentado su habilidad con el personaje2 tambi�n especificado 
   En otro caso devuelve 0 */

void atacaPersonaje (Lista<Personaje*> *listaP, int indiceP1, int indiceP2);
/* Funci�n que realiza un ataque de un personaje a otro decrementando
   los pg del segundo */

void incrementaCaracteristicas (Lista<Personaje*> *listaP, int indiceP);
/* Funci�n que incrementa las caracter�sticas del personaje indicado de la
   lista dada */

void incrementaSalud (Lista<Personaje*> *listaP, int indiceP, int coste);
/* Funci�n que incrementa los atributos ene, ham, sed y pg del personaje
   indicado de la lista dada */

void decrementaSalud (Lista<Personaje*> *listaP, int indiceP, int decremento);
/* Funci�n que decrementa los atributos ene, ham, sed del personaje indicado
   de la lista dada */

void decrementaPG (Lista<Personaje*> *listaP, int indiceP, int decremento);
// Funci�n que decrementa el pg del personaje indicado de la lista dada

void incrementaEne (Lista<Personaje*> *listaP, int indiceP);
// Funci�n que incrementa el ene del personaje indicado de la lista dada

void incrementaHam (Lista<Personaje*> *listaP, int indiceP, int incremento);
// Funci�n que incrementa el ham del personaje indicado de la lista dada
  
void incrementaSed (Lista<Personaje*> *listaP, int indiceP);
/* Funci�n que incrementa el atributo sed del personaje indicado de la lista
   dada */

void incrementaMH (Lista<Personaje*> *listaP, int indiceP);
// Funci�n que incrementa los mh del personaje especificado de la lista dada

void incrementaEqu (Lista<Personaje*> *listaP, int indiceP, 
		    Lista<Objeto*> *listaObjetos, int indiceO);
/* Funci�n que incrementa el equipo del personaje especificado con el objeto
   dado */

void incrementaEqu (Lista<Personaje*> *listaP, int indiceP1, int indiceP2);
/* Funci�n que incrementa del equipo del personaje1 con el equipo del 
   personaje2 */

void incrementaObj (Lista<Personaje*> *listaP, int indiceP);
// Funci�n que incrementa el objetivo del personaje indicado de la lista dada

void decrementaPersonaje (Lista<Personaje*> *listaClientes, int turnoP, 
			  int sock);
// Funci�n que en funci�n del turno y la car decrementa la salud del personaje

int obtienePrecio (int tipoObjeto);
// Funci�n que devuelve el precio del objeto especificado

void compraObjeto (Lista<Personaje*> *listaP, int indiceP, int tipoObjeto);
/* Funci�n que modifica el equipo del personaje especificado comprando el tipo
   de objeto dado */

int obtieneAccion (int cursorx, int cursory, Lista<Edificio*> *listaEdificios, 
		   Lista<Objeto*> *listaObjetos, 
		   Lista<Personaje*> *listaP, int indiceP,
		   Lista<Casilla*> *listaCasillas, int cursorStatus);
/* Funci�n que devuelve un entero con la acci�n a realizar asociada a la 
   posici�n del cursor especificada */

char *obtieneFichero (char *path, int fichero, char *extension);
/* Funci�n que compone el nombre de un fichero a trav�s de los argumentos
   especificados */

void copiaFichero (char *origen, char *destino);
// Funci�n que realiza una copia de un fichero en otro

int generaAleatorio (int inf, int sup);
// Funci�n que devuelve un n�mero aleatorio en el rango especificado

char *int2string (int entero);
// Funci�n que convierte un entero en una cadena con dos d�gitos

char *itoa (int entero);
// Funci�n que convierte un entero en una cadena

char int2char (int entero);
// Funci�n que convierte un entero en un caracter

int char2int (char caracter);
// Funci�n que convierte un caracter en un entero

#endif 

/****************************************************************************/
