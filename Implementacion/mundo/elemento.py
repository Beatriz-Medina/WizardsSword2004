
# **************************************************************************
#			  elemento.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


# Clase que implementa los atributos de un elemento que indican tanto su
# posicion como su tamano en casillas y su pertenencia a un edificio
class Elemento:
    __posx = None     # Atributo posx
    __posy = None     # Atributo posy
    __casilx = None   # Atributo casilx
    __casily = None   # Atributo casily
    __edif = None     # Atributo edif

    # Inicializador
    def __init__ (self, posx, posy, casilx, casily, edif):
        self.__posx = posx
        self.__posy = posy
        self.__casilx = casilx
        self.__casily = casily
        self.__edif = edif
        
    # Metodo consultor que devuelve el atributo posx
    def obtienePosx (self):
        return self.__posx

    # Metodo consultor que devuelve el atributo posy
    def obtienePosy (self):
        return self.__posy

    # Metodo consultor que devuelve el atributo casilx
    def obtieneCasilx (self):
        return self.__casilx
    
    # Metodo consultor que devuelve el atributo casily
    def obtieneCasily (self):
        return self.__casily

    # Metodo consultor que devuelve el atributo edif
    def obtieneEdif (self):
        return self.__edif

# *************************************************************************
