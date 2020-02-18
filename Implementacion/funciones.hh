
/***************************************************************************
                          funciones.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
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
// Función que devuelve el socket activo
 
void insertaEnvio (Lista<Envio*> *listaEnvios, int sock);
// Función que inserta en la lista un nuevo elemento con el socket especificado

void eliminaEnvio (Lista<Envio*> *listaEnvios, int sock);
// Función que elimina de la lista el elemento cuyo socket se especifica

int obtieneEnvio (Lista<Envio*> *listaEnvios, int sock);
/* Función que devuelve el flag de envío del elemento cuyo socket se especifica
   En caso de que el socket no exista devuelve -1 */

void reAsignaEnvio (Lista<Envio*> *listaEnvios, int sock, int nuevoEnv);
// Función que modifica el flag de envío del socket especificado

void activaEnvios (Lista<Envio*> *listaEnvios, int nuevoEnv);
/* Función que pone el flag de envío de todos los elementos de la lista con
   el valor especificado */

void enviaEnteroACliente (ConexionServidor *conexion, int sock, int entero);
// Función que envía un entero al cliente cuyo socket se especifica

int recibeEnteroDeCliente (ConexionServidor *conexion, int sock);
// Función que recibe un entero del cliente cuyo socket se especifica

void enviaEnteroAServidor (ConexionCliente *conexion, int entero);
// Función que envía un entero al servidor

int recibeEnteroDeServidor (ConexionCliente *conexion);
// Función que recibe un entero del servidor

void obtieneTamMundo (int *mundoInf, int *mundoSup, int *castilInf, 
		      int *castilSup, int *casaInf, int *casaSup);
// Función que devuelve en las coordenadas indicadas el tamaño del mundo

Lista<Edificio*> *cargaEdificios (int xinf, int xsup, int yinf, int ysup);
/* Función que devuelve una lista con todos los edificios del mundo que estén 
   dentro del rango especificado */

Lista<Objeto*> *cargaObjetos (int xinf, int xsup, int yinf, int ysup, 
			      int edif);
/* Función que devuelve una lista con todos los objetos del mundo que estén 
   dentro del rango y edificio especificados */

Lista<Personaje*> *cargaPersonajes (int xinf, int xsup, int yinf, int ysup, 
				    Lista<Personaje*> *listaClientes, 
				    int edif);
/* Función que devuelve una lista  a partir de la dada con todos los personajes
   del mundo que estén dentro del rango y edificio especificados */

Lista<Casilla*> *cargaCasillas (int xinf, int xsup, int yinf, int ysup);
/* Función que devuelve una lista con todas las casillas del mundo que estén 
   dentro del rango especificado */

Lista<Elemento*> *ordenaListas (Lista<Personaje*> *listaP, 
				Lista<Objeto*> *listaObjetos);
/* Función que devuelve una lista con los elementos de las dos listas 
   especificadas ordenados de mayor a menor profundidad */

Lista<Personaje*> *ordenaClientes (Lista<Personaje*> *listaClientes);
// Función que ordena la lista de clientes por momento de reacción

void actualizaObjetos (Lista<Objeto*> *listaObjetos);
// Función que actualiza el fichero de objetos con la lista especificada

void actualizaPersonajes (Lista<Personaje*> *listaP, 
			  Lista<Personaje*> *listaClientes);
// Función que actualiza la lista de clientes con la lista de personajes dada

void insertaNuevosObjetos (Lista<Objeto*> *listaObjetos, 
			   Lista<Personaje*> *listaP, int xinf, int xsup, 
			   int yinf, int ysup);
/* Función que inserta los objetos de la lista especificada en el fichero de
   objetos */

void iniciaObjetos (Lista<Objeto*> *listaObjetos, int edif);
/* Función que asigna los objetos trampas a no visibles y los objetos 
   prisioneros a esclavos pertenecientes al edificio especificado */

Lista<Objeto*> *creaCofres (Lista<Personaje*> *listaP, int indiceP);
/* Función que crea una lista de objetos cofres que incluyan el equipo
   del personaje de la lista especificada */

int obtieneIndice (Lista<Personaje*> *listaP, int sock);
/* Función que devuelve el índice en la lista del personaje cuyo socket 
   coincide con el especificado 
   En caso de que no coincida se devuelve -1 */

int obtieneTipoEdificio (int edif, Lista<Edificio*> *listaEdificios);
/* Función que devuelve el tipo del identificador de edificio especificado
   Devuelve -1 en caso de que no lo encuentre */

int coincideEdificio (int posx, int posy, Lista<Edificio*> *listaEdificios);
/* Función que devuelve el índice de un edificio de la lista dada si la 
   posición especificada coincide con él 
   En otro caso devuelve -1 */

int coincideObjeto (int posx, int posy, Lista<Objeto*> *listaObjetos);
/* Función que devuelve el índice de un objeto de la lista dada si la 
   posición especificada coincide con él 
   En otro caso devuelve -1 */

int coincidePersonaje (int posx, int posy, Lista<Personaje*> *listaP);
/* Función que devuelve el índice de un personaje de la lista dada si la 
   posición especificada coincide con él 
   En otro caso devuelve -1 */

int objetoTrampa (int posx, int posy, int *visible, 
		  Lista<Objeto*> *listaObjetos);
/* Función que comprueba si el objeto de la lista con la posición especificada
   es de tipo trampa o no
   Se devuelve el identificador del objeto en caso de que sea una trampa
   En otro caso se devuelve -1
   En visible se devuelve si el objeto está oculto o no */

void objetoVisible (Lista<Objeto*> *listaObjetos, int indiceO);
// Función que activa el objeto de la lista especificada a visible

void liberaPrisionero (Lista<Personaje*> *listaP, int indiceP,
		       Lista<Objeto*> *listaObjetos, int indiceO);
/* Función que cambia el tipo del objeto especificado incrementando el
   número de monedas del personaje también indicado */

int tipoCasilla (int posx, int posy, Lista<Casilla*> *listaCasillas);
/* Función que devuelve el tipo de casilla de la indicada en la lista
   En caso de que la casilla no exista devuelve -1 */

void obtienePosicion (int xinf, int xsup, int yinf, int ysup, 
		      int *posx, int *posy, Lista<Personaje*> *listaP);
/* Función que devuelve una posición para un personaje que no sea coincidente 
   con la posición de ningún otro elemento */

int tiraDado (int nveces, int ncaras);
// Función que realiza ntiradas de un dado cuyo número de caras se indica

int ajustaMD (int valor);
// Función que ajusta el valor del md dado con una tirada de dados

int ajustaMH (char influencia, int caracteristica);
/* Función que ajusta el valor de habilidad en función de la influencia y
   la caracteristica dada */

int ajustaMMR (int tam, int des);
/* Función que ajusta el momento de reacción en función del tamaño y destreza
   especificados */

int ajustaNturnos (int mmr);
/* Función que ajusta el número de turnos en función del momento de reacción
   especificado */

int tiradaMH (Lista<Personaje*> *listaP, int indiceP, int habilidad);
/* Función que realiza una tirada de la habilidad especificada
   Devuelve 1 si ha tenido éxito
   En caso contrario devuelve 0 */

int enfrentaMH (Lista<Personaje*> *listaP, int indiceP1, int indiceP2);
/* Función que devuelve 1 si el personaje1 especificado sale victorioso
   enfrentado su habilidad con el personaje2 también especificado 
   En otro caso devuelve 0 */

void atacaPersonaje (Lista<Personaje*> *listaP, int indiceP1, int indiceP2);
/* Función que realiza un ataque de un personaje a otro decrementando
   los pg del segundo */

void incrementaCaracteristicas (Lista<Personaje*> *listaP, int indiceP);
/* Función que incrementa las características del personaje indicado de la
   lista dada */

void incrementaSalud (Lista<Personaje*> *listaP, int indiceP, int coste);
/* Función que incrementa los atributos ene, ham, sed y pg del personaje
   indicado de la lista dada */

void decrementaSalud (Lista<Personaje*> *listaP, int indiceP, int decremento);
/* Función que decrementa los atributos ene, ham, sed del personaje indicado
   de la lista dada */

void decrementaPG (Lista<Personaje*> *listaP, int indiceP, int decremento);
// Función que decrementa el pg del personaje indicado de la lista dada

void incrementaEne (Lista<Personaje*> *listaP, int indiceP);
// Función que incrementa el ene del personaje indicado de la lista dada

void incrementaHam (Lista<Personaje*> *listaP, int indiceP, int incremento);
// Función que incrementa el ham del personaje indicado de la lista dada
  
void incrementaSed (Lista<Personaje*> *listaP, int indiceP);
/* Función que incrementa el atributo sed del personaje indicado de la lista
   dada */

void incrementaMH (Lista<Personaje*> *listaP, int indiceP);
// Función que incrementa los mh del personaje especificado de la lista dada

void incrementaEqu (Lista<Personaje*> *listaP, int indiceP, 
		    Lista<Objeto*> *listaObjetos, int indiceO);
/* Función que incrementa el equipo del personaje especificado con el objeto
   dado */

void incrementaEqu (Lista<Personaje*> *listaP, int indiceP1, int indiceP2);
/* Función que incrementa del equipo del personaje1 con el equipo del 
   personaje2 */

void incrementaObj (Lista<Personaje*> *listaP, int indiceP);
// Función que incrementa el objetivo del personaje indicado de la lista dada

void decrementaPersonaje (Lista<Personaje*> *listaClientes, int turnoP, 
			  int sock);
// Función que en función del turno y la car decrementa la salud del personaje

int obtienePrecio (int tipoObjeto);
// Función que devuelve el precio del objeto especificado

void compraObjeto (Lista<Personaje*> *listaP, int indiceP, int tipoObjeto);
/* Función que modifica el equipo del personaje especificado comprando el tipo
   de objeto dado */

int obtieneAccion (int cursorx, int cursory, Lista<Edificio*> *listaEdificios, 
		   Lista<Objeto*> *listaObjetos, 
		   Lista<Personaje*> *listaP, int indiceP,
		   Lista<Casilla*> *listaCasillas, int cursorStatus);
/* Función que devuelve un entero con la acción a realizar asociada a la 
   posición del cursor especificada */

char *obtieneFichero (char *path, int fichero, char *extension);
/* Función que compone el nombre de un fichero a través de los argumentos
   especificados */

void copiaFichero (char *origen, char *destino);
// Función que realiza una copia de un fichero en otro

int generaAleatorio (int inf, int sup);
// Función que devuelve un número aleatorio en el rango especificado

char *int2string (int entero);
// Función que convierte un entero en una cadena con dos dígitos

char *itoa (int entero);
// Función que convierte un entero en una cadena

char int2char (int entero);
// Función que convierte un entero en un caracter

int char2int (char caracter);
// Función que convierte un caracter en un entero

#endif 

/****************************************************************************/
