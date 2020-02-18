
# **************************************************************************
#			  elemento.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


# Clase utilizada para indicar el tipo y la posicion en la lista de un
# elemento del juego como son los objetos y los personajes 

class Elemento:
    __tipo = None      # Tipo de elemento: 0 (Personaje), 1 (Objeto)
    __posicion = None  # Posicion del elemento en su lista correspondiente
    __nAtr = None      # Numero de atributos del objeto Elemento
    
    # Inicializador
    def __init__ (self):
        self.__nAtr = 2

    # Metodo consultor que devuelve el numero de atributos del objeto Elemento
    def obtieneNAtributos (self):
        return self.__nAtr
    
    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'tipo')):
            return self.__tipo

        elif ((atributo == 2) or (atributo == 'posicion')):
            return self.__posicion

    # Metodo que actualiza con un nuevo valor al atributo especificado    
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'tipo')):
            self.__tipo = nuevoValor

        elif ((atributo == 2) or (atributo == 'posicion')):
            self.__posicion = nuevoValor
            
# *************************************************************************
