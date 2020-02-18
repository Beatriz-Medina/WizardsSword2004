
# **************************************************************************
#			  objeto.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa los atributos de un objeto del juego

# id:       Identificador del objeto

# tipo:     Tipo de objeto
#           0 -> arbol
#           1 -> setas
#           2 -> miel
#           3 -> cofre		 
#           4 -> bruja
#           5 -> candelabro
#           6 -> huesos
#           7 -> portal magico
#           8 -> estatua
#           9 -> esclava1
#           10 -> esclava1 libre
#           11 -> esclava2
#           12 -> esclava2 libre
#           13 -> esclavo1
#           14 -> esclavo1 libre
#           15 -> esclavo2
#           16 -> esclavo2 libre
#           17 -> pinchos
#           18 -> bibliotecaria
#           19 -> mesa
#           20 -> biblioteca
#           21 -> posadera
#           22 -> cama
#           23 -> vela
#           24 -> escoba
#           25 -> armero
#           26 -> estatua con armadura
#           27 -> espada1
#           28 -> espada2
#           29 -> hacha
#           30 -> bola y cadena
#           31 -> escudo1
#           32 -> escudo2
#           33 -> escudo3
#           34 -> maniqui
#           35 -> armadura de cuero
#           36 -> cota de anillos
#           37 -> armadura
#           38 -> coraza

# visi:     Flag que indica si el objeto es visible o no
#           0 -> No visible
#           1 -> Visible
 
# posx:     Posicion x del objeto
# posy:     Posicion y del objeto

# longx:    Longitud x del objeto
# longy:    Longitud y del objeto

# casilx:   Numero de casillas que ocupa en el eje x
# casily:   Numero de casillas que ocupa en el eje y

# edif:     Identificador del edificio donde se encuentra el objeto
#           o VACIO si no se encuentra en ninguno

# equ:      Tipo de objeto que contiene el objeto o VACIO si no contiene nada
#           0     -> llave
#           1-10  -> pocion (i) (i: 1->10)
#           11    -> monedas (50 unidades)

# nAtr:     Numero de atributos del objeto Objeto

class Objeto:
    __id = None
    __tipo = None
    __visi = None
    __posx = None
    __posy = None
    __longx = None
    __longy = None
    __casilx = None
    __casily = None
    __edif = None	
    __equ = None
    __nAtr = None

    # Inicializador
    def __init__ (self):
        self.__nAtr = 11

    # Metodo consultor que devuelve el numero de atributos del objeto Objeto
    def obtieneNAtributos (self):
        return self.__nAtr
    
    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'id')):
            return self.__id

        elif ((atributo == 2) or (atributo == 'tipo')):
            return self.__tipo

        elif ((atributo == 3) or (atributo == 'visi')):
            return self.__visi

        elif ((atributo == 4) or (atributo == 'posx')):
            return self.__posx

        elif ((atributo == 5) or (atributo == 'posy')):
            return self.__posy

        elif ((atributo == 6) or (atributo == 'longx')):
            return self.__longx

        elif ((atributo == 7) or (atributo == 'longy')):
            return self.__longy

        elif ((atributo == 8) or (atributo == 'casilx')):
            return self.__casilx

        elif ((atributo == 9) or (atributo == 'casily')):
            return self.__casily

        elif ((atributo == 10) or (atributo == 'edif')):
            return self.__edif

        elif ((atributo == 11) or (atributo == 'equ')):
            return self.__equ

    # Metodo que actualiza con un nuevo valor al atributo especificado    
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'id')):
            self.__id = nuevoValor

        elif ((atributo == 2) or (atributo == 'tipo')):
            self.__tipo = nuevoValor

        elif ((atributo == 3) or (atributo == 'visi')):
            self.__visi = nuevoValor

        elif ((atributo == 4) or (atributo == 'posx')):
            self.__posx = nuevoValor

        elif ((atributo == 5) or (atributo == 'posy')):
            self.__posy = nuevoValor

        elif ((atributo == 6) or (atributo == 'longx')):
            self.__longx = nuevoValor

        elif ((atributo == 7) or (atributo == 'longy')):
            self.__longy = nuevoValor

        elif ((atributo == 8) or (atributo == 'casilx')):
            self.__casilx = nuevoValor

        elif ((atributo == 9) or (atributo == 'casily')):
            self.__casily = nuevoValor

        elif ((atributo == 10) or (atributo == 'edif')):
            self.__edif = nuevoValor

        elif ((atributo == 11) or (atributo == 'equ')):
            self.__equ = nuevoValor

# *************************************************************************
