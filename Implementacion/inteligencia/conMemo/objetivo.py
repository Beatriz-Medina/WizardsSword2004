
# **************************************************************************
#			   objetivo.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa los atributos asociados a un elemento objetivo

class Objetivo:
    __id = None    # Identificador del objetivo
    __posx = None  # Coordenada x del objetivo                      
    __posy = None  # Coordenada y del objetivo
    __nAtr = None  # Numero de atributos
    
    # Inicializador
    def __init__ (self):
        self.__nAtr = 3

    # Metodo consultor que devuelve el numero de atributos del objeto Objetivo
    def obtieneNAtributos (self):
        return self.__nAtr

    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'id')):
            return self.__id

        elif ((atributo == 2) or (atributo == 'posx')):
            return self.__posx

        elif ((atributo == 3) or (atributo == 'posy')):
            return self.__posy

    # Metodo que actualiza con un nuevo valor al atributo especificado   
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'id')):
            self.__id = nuevoValor

        elif ((atributo == 2) or (atributo == 'posx')):
            self.__posx = nuevoValor

        elif ((atributo == 3) or (atributo == 'posy')):
            self.__posy = nuevoValor

# *************************************************************************
