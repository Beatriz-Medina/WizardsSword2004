
# **************************************************************************
#			  casilla.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa los atributos de una casilla del juego

# tipo:     Tipo de casilla
#           0 -> Hierba
#           1 -> Tierra
#           2 -> Piedra
#           3 -> Poza de agua
#           4 -> Interior casas
#           5 -> Interior castillos	 

# posx:     Posicion x de la casilla
# posy:     Posicion y de la casilla

# nAtr:     Numero de atributos del objeto Casilla

class Casilla:
    __tipo = None
    __posx = None
    __posy = None
    __nAtr = None
    
    # Inicializador
    def __init__ (self):
        self.__nAtr = 3

    # Metodo consultor que devuelve el numero de atributos del objeto Casilla
    def obtieneNAtributos (self):
        return self.__nAtr
    
    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'tipo')):
            return self.__tipo

        elif ((atributo == 2) or (atributo == 'posx')):
            return self.__posx

        elif ((atributo == 3) or (atributo == 'posy')):
            return self.__posy

    # Metodo que actualiza con un nuevo valor al atributo especificado    
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'tipo')):
            self.__tipo = nuevoValor

        elif ((atributo == 2) or (atributo == 'posx')):
            self.__posx = nuevoValor
            
        elif ((atributo == 3) or (atributo == 'posy')):
            self.__posy = nuevoValor

# *************************************************************************
