
/***************************************************************************
                          clientePJ.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by M� Beatriz Medina Ya�ez
 ***************************************************************************/


#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#include "entornoG.hh"

int main ()
{
    EntornoG *unEntorno;
    char cadena[20];
    long semilla;
    int tamano, servidorIP;

    // Inicializaci�n de la semilla aleatoria
    semilla = time (NULL);
    srand (semilla);

    // Obtenci�n de la direcci�n IP del servidor
    printf ("Conexi�n con el servidor: ");
    fgets (cadena, 20, stdin);
    tamano = strlen (cadena);
    cadena[tamano-1] = '\0';
    servidorIP = inet_addr (cadena);

    // Creaci�n del entorno gr�fico
    unEntorno = new EntornoG ("Wizard's Sword", "logo.png", 640, 480, 
			      servidorIP);

    // Inicio del entorno gr�fico
    unEntorno->iniciaEntorno ();

    // Visualizaci�n del entorno gr�fico
    unEntorno->visualizaEntorno ();
    
   return 0;
}

/****************************************************************************/







