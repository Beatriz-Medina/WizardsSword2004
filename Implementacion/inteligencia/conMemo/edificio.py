
# **************************************************************************
#			  edificio.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa los atributos de un edificio del juego

# id:       Identificador del edificio

# tipo:     Tipo de edificio
#           0 -> Castillo
#           1 -> Posada
#           2 -> Biblioteca
#           3 -> Tienda de armas
#           4 -> Tienda de escudos
#           5 -> Tienda de armaduras

# llav:     Flag que indica si el edificio esta cerrado o no con llave
#           0 -> No cerrado
#           1 -> Cerrado

# posx:     Posicion x del edificio
# posy:     Posicion y del edificio

# longx:    Longitud x del edificio
# longy:    Longitud y del edificio

# casilx:   Numero de casillas que ocupa en el eje x
# casily:   Numero de casillas que ocupa en el eje y
       
# nAtr:     Numero de atributos del objeto Edificio

class Edificio:
    __id = None      
    __tipo = None   
    __llav = None   
    __posx = None   
    __posy = None
    __longx = None
    __longy = None
    __casilx = None
    __casily = None
    __nAtr = None

    # Inicializador
    def __init__ (self):
        self.__nAtr = 9

    # Metodo consultor que devuelve el numero de atributos del objeto Edificio
    def obtieneNAtributos (self):
        return self.__nAtr
    
    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'id')):
            return self.__id

        elif ((atributo == 2) or (atributo == 'tipo')):
            return self.__tipo

        elif ((atributo == 3) or (atributo == 'llav')):
            return self.__llav

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

    # Metodo que actualiza con un nuevo valor al atributo especificado    
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'id')):
            self.__id = nuevoValor

        elif ((atributo == 2) or (atributo == 'tipo')):
            self.__tipo = nuevoValor
            
        elif ((atributo == 3) or (atributo == 'llav')):
            self.__llav = nuevoValor

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

# *************************************************************************
