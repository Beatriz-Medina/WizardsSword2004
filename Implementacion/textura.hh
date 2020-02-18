
/***************************************************************************
                          textura.hh  -  description
                             -------------------
  Wizard's Sword
  desarrollado por     : (C) 2004 by Mª Beatriz Medina Yañez
 ***************************************************************************/


#ifndef _TEXTURA_HH
#define _TEXTURA_HH

#define uchar unsigned char
#define VACIO -1

class Textura
{
    // Clase que almacena una textura del juego
   
 private:
    uchar *pixels;  // Pixels de la textura
    int ancho;      // Ancho de la textura
    int alto;       // Alto de la textura

 public:
    Textura (char *nombre, int profundidad);
    /* Constructor del objeto Textura que carga en memoria la textura con
       respecto al nombre y profundidad especificados */

    ~Textura ();
    // Destructor del objeto Textura

    uchar *obtienePixels (void);
    // Método consultor que devuelve la matriz de pixels de la textura 
    
    int obtieneAncho (void);
    // Método consultor que devuelve el ancho de la textura

    int obtieneAlto (void);
    // Método consultor que devuelve el alto de la textura
};

#endif 

/****************************************************************************/
