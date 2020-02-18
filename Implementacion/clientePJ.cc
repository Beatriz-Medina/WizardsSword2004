
/***************************************************************************
                          clientePJ.cc  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
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

    // Inicialización de la semilla aleatoria
    semilla = time (NULL);
    srand (semilla);

    // Obtención de la dirección IP del servidor
    printf ("Conexión con el servidor: ");
    fgets (cadena, 20, stdin);
    tamano = strlen (cadena);
    cadena[tamano-1] = '\0';
    servidorIP = inet_addr (cadena);

    // Creación del entorno gráfico
    unEntorno = new EntornoG ("Wizard's Sword", "logo.png", 640, 480, 
			      servidorIP);

    // Inicio del entorno gráfico
    unEntorno->iniciaEntorno ();

    // Visualización del entorno gráfico
    unEntorno->visualizaEntorno ();
    
   return 0;
}

/****************************************************************************/







