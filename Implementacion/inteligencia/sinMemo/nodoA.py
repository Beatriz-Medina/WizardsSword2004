
# **************************************************************************
#			   nodoA.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa un nodo A*

# id:       Identificador del nodo
# idpa:     Identificador del nodo padre

# posx:     Posicion x del estado
# posy:     Posicion y del estado

# oper:     Operacion realizada
#           1 -> arriba
#           2 -> abajo
#           3 -> izquierda
#           4 -> derecha

# g:        Funcion de costo asociado al nodo
# h:        Funcion de estimacion heuristica asociado al nodo
# f:        Funcion de criterio heuristico: g + h

class NodoA:
    __id = None    
    __idpa = None                        
    __posx = None
    __posy = None
    __oper = None
    __g = None
    __h = None
    __f = None
                
    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if (atributo == 'id'):
            return self.__id

        elif (atributo == 'idpa'):
            return self.__idpa

        elif (atributo == 'posx'):
            return self.__posx

        elif (atributo == 'posy'):
            return self.__posy

        elif (atributo == 'oper'):
            return self.__oper

        elif (atributo == 'g'):
            return self.__g

        elif (atributo == 'h'):
            return self.__h

        elif (atributo == 'f'):
            return self.__f

    # Metodo que actualiza con un nuevo valor al atributo especificado    
    def reAsignaAtributo (self, atributo, nuevoValor):

        if (atributo == 'id'):
            self.__id = nuevoValor

        elif (atributo == 'idpa'):
            self.__idpa = nuevoValor

        elif (atributo == 'posx'):
            self.__posx = nuevoValor

        elif (atributo == 'posy'):
            self.__posy = nuevoValor

        elif (atributo == 'oper'):
            self.__oper = nuevoValor

        elif (atributo == 'g'):
            self.__g = nuevoValor

        elif (atributo == 'h'):
            self.__h = nuevoValor

        elif (atributo == 'f'):
            self.__f = nuevoValor

# *************************************************************************
