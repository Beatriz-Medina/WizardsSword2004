
# **************************************************************************
#			   operador.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa un operador para el algoritmo STRIPS

class Operador:
    __nombre = None  # Nombre del operador
    __prec = None    # Precondiciones del operador                      
    __post = None    # Postcondiciones del operador

    # Inicializador
    def __init__ (self):
        self.__prec = []
        self.__post = []
        
    # Metodo consultor que devuelve el nombre del operador
    def obtieneNombre (self):
        return self.__nombre

    # Metodo consultor que devuelve el tamano de las precondiciones
    def obtieneNPrec (self):
        return len (self.__prec)

    # Metodo consultor que devuelve el tamano de las postcondiciones
    def obtieneNPost (self):
        return len (self.__post)

    # Metodo consultor que devuelve la precondicion especificada  
    def obtienePrecond (self, posicion):
        return self.__prec[posicion]

    # Metodo consultor que devuelve la lista de precondiciones
    def obtienePrec (self):
        return self.__prec

    # Metodo consultor que devuelve la postcondicion especificada
    def obtienePostcond (self, posicion):
        return self.__post[posicion]

    # Metodo consultor que devuelve la lista de postcondiciones
    def obtienePost (self):
        return self.__post
    
    # Metodo que actualiza con un nuevo valor al atributo nombre
    def reAsignaNombre (self, nuevoValor):
        self.__nombre = nuevoValor

    # Metodo que inserta una nueva precondicion para el operador
    def insertaPrecond (self, nuevoValor):
        self.__prec.append (nuevoValor)

    # Metodo que inserta una nueva postcondicion para el operador
    def insertaPostcond (self, nuevoValor):
        self.__post.append (nuevoValor)

# *************************************************************************
