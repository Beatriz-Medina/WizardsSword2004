
# **************************************************************************
#			   item.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa un item asociado a un objeto contenedor

class Item:
    __id = None    # Identificador del objeto
    __elem = None  # Tipo de elemento que contiene                      
    __nAtr = None  # Numero de atributos del objeto Item

    # Inicializador
    def __init__ (self):
        self.__nAtr = 2

    # Metodo consultor que devuelve el numero de atributos del objeto Item
    def obtieneNAtributos (self):
        return self.__nAtr

    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'id')):
            return self.__id

        elif ((atributo == 2) or (atributo == 'elem')):
            return self.__elem
    
    # Metodo que actualiza con un nuevo valor al atributo especificado   
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'id')):
            self.__id = nuevoValor

        elif ((atributo == 2) or (atributo == 'elem')):
            self.__elem = nuevoValor

# *************************************************************************
