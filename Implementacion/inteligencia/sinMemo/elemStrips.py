
# **************************************************************************
#			 elemStrips.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa a un elemento de la pila STRIPS

# tipo:  Tipo de elemento
#        0 -> Objetivo
#        1 -> Precondicion del operador objetivo
#        2 -> Precondicion normal
#        3 -> Operador normal

# valor: Valor del elemento

# nAtr:  Numero de atributos del objeto ElemStrips
class ElemStrips:
    __tipo = None 
    __valor = None                        
    __nAtr = None 

    # Inicializador
    def __init__ (self):
        self.__valor = []
        self.__nAtr = 2

    # Metodo consultor que devuelve el numero de atributos del objeto
    # ElemStrips
    def obtieneNAtributos (self):
        return self.__nAtr

    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'tipo')):
            return self.__tipo

        elif ((atributo == 2) or (atributo == 'valor')):
            return self.__valor
    
    # Metodo que actualiza con un nuevo valor al atributo especificado   
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'tipo')):
            self.__tipo = nuevoValor

        elif ((atributo == 2) or (atributo == 'valor')):
            self.__valor = nuevoValor

# *************************************************************************
