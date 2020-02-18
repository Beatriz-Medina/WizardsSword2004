
# **************************************************************************
#			  personaje.py  -  description
#   	                      ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


#  Clase que implementa los atributos de un personaje del juego

# sock:     Socket del cliente

# esp:      Especie a la que pertenece el personaje
#           0 -> humano
#           1 -> hobbit
#           2 -> elfo
#           3 -> gigante
#           4 -> mono

# fue:      Fuerza del personaje (limitada por con + tam)
# con:      Constitucion del personaje (limitada por fue + tam)
# tam:      Tamano del personaje
# inte:     Inteligencia del personaje
# des:      Destreza del personaje (limitada por des * 2)

# pg:       Puntos de golpe del personaje (media alta de con y tam) 
# ene:      Energia del personaje (fue + con)
# ham:      Hambre del personaje (con + tam)
# sed:      Sed del personaje (con + tam)

# maxpg:    Limite de pg
# maxene:   Limite de ene
# maxham:   Limite de ham
# maxsed:   Limite de sed
       
# mh1:      Modificador de habilidad del personaje (sigilo)
# mh2:      Modificador de habilidad del personaje (percepcion)

# mmr:      Momento de reaccion del personaje

# posx:     Posicion x del personaje
# posy:     Posicion y del personaje

# edif:     Identificador del edificio donde se encuentra el personaje 
#           o VACIO si no se encuentra en ninguno

# estu:     Contador que acumula el numero de estudios realizados
# entr:     Contador que acumula el numero de entrenamientos realizados
# obj:      Indicador de la mision asignada asociada al entrenamiento

# nturnos:  Contador del numero de turnos que puede utilizar el personaje

# nAtr:     Numero de atributos del objeto Personaje

# equ0:     Escudo
# equ1:     Arma 
# equ2:     Armadura 
# equ3:     Numero de monedas de oro
# equ4:     Llave
# equ5:     Pocion

# tamEqu:   Tamano del equipo

class Personaje:
    __sock = None    
    __esp = None                        
    __fue = None
    __con = None
    __tam = None
    __inte = None
    __des = None
    __pg = None
    __ene = None
    __ham = None
    __sed = None
    __maxpg = None
    __maxene = None
    __maxham = None
    __maxsed = None
    __mh1 = None
    __mh2 = None 
    __mmr = None
    __posx = None
    __posy = None
    __edif = None
    __estu = None
    __entr = None
    __obj = None
    __nturnos = None
    __nAtr = None
    __equ0 = None
    __equ1 = None
    __equ2 = None
    __equ3 = None
    __equ4 = None
    __equ5 = None
    __tamEqu = None

    # Inicializador
    def __init__ (self):
        self.__nAtr = 25
        self.__tamEqu = 6
            
    # Metodo consultor que devuelve el numero de atributos del objeto Personaje
    def obtieneNAtributos (self):
        return self.__nAtr
    
    # Metodo consultor que devuelve el valor del atributo especificado
    def obtieneAtributo (self, atributo):

        if ((atributo == 1) or (atributo == 'sock')):
            return self.__sock

        elif ((atributo == 2) or (atributo == 'esp')):
            return self.__esp

        elif ((atributo == 3) or (atributo == 'fue')):
            return self.__fue

        elif ((atributo == 4) or (atributo == 'con')):
            return self.__con

        elif ((atributo == 5) or (atributo == 'tam')):
            return self.__tam

        elif ((atributo == 6) or (atributo == 'inte')):
            return self.__inte

        elif ((atributo == 7) or (atributo == 'des')):
            return self.__des

        elif ((atributo == 8) or (atributo == 'pg')):
            return self.__pg

        elif ((atributo == 9) or (atributo == 'ene')):
            return self.__ene

        elif ((atributo == 10) or (atributo == 'ham')):
            return self.__ham

        elif ((atributo == 11) or (atributo == 'sed')):
            return self.__sed

        elif ((atributo == 12) or (atributo == 'maxpg')):
            return self.__maxpg

        elif ((atributo == 13) or (atributo == 'maxene')):
            return self.__maxene

        elif ((atributo == 14) or (atributo == 'maxham')):
            return self.__maxham

        elif ((atributo == 15) or (atributo == 'maxsed')):
            return self.__maxsed

        elif ((atributo == 16) or (atributo == 'mh1')):
            return self.__mh1

        elif ((atributo == 17) or (atributo == 'mh2')):
            return self.__mh2

        elif ((atributo == 18) or (atributo == 'mmr')):
            return self.__mmr

        elif ((atributo == 19) or (atributo == 'posx')):
            return self.__posx

        elif ((atributo == 20) or (atributo == 'posy')):
            return self.__posy

        elif ((atributo == 21) or (atributo == 'edif')):
            return self.__edif

        elif ((atributo == 22) or (atributo == 'estu')):
            return self.__estu

        elif ((atributo == 23) or (atributo == 'entr')):
            return self.__entr

        elif ((atributo == 24) or (atributo == 'obj')):
            return self.__obj

        elif ((atributo == 25) or (atributo == 'nturnos')):
            return self.__nturnos

    # Metodo que actualiza con un nuevo valor al atributo especificado    
    def reAsignaAtributo (self, atributo, nuevoValor):

        if ((atributo == 1) or (atributo == 'sock')):
            self.__sock = nuevoValor

        elif ((atributo == 2) or (atributo == 'esp')):
            self.__esp = nuevoValor

        elif ((atributo == 3) or (atributo == 'fue')):
            self.__fue = nuevoValor

        elif ((atributo == 4) or (atributo == 'con')):
            self.__con = nuevoValor

        elif ((atributo == 5) or (atributo == 'tam')):
            self.__tam = nuevoValor

        elif ((atributo == 6) or (atributo == 'inte')):
            self.__inte = nuevoValor

        elif ((atributo == 7) or (atributo == 'des')):
            self.__des = nuevoValor

        elif ((atributo == 8) or (atributo == 'pg')):
            self.__pg = nuevoValor

        elif ((atributo == 9) or (atributo == 'ene')):
            self.__ene = nuevoValor

        elif ((atributo == 10) or (atributo == 'ham')):
            self.__ham = nuevoValor

        elif ((atributo == 11) or (atributo == 'sed')):
            self.__sed = nuevoValor

        elif ((atributo == 12) or (atributo == 'maxpg')):
            self.__maxpg = nuevoValor

        elif ((atributo == 13) or (atributo == 'maxene')):
            self.__maxene = nuevoValor

        elif ((atributo == 14) or (atributo == 'maxham')):
            self.__maxham = nuevoValor

        elif ((atributo == 15) or (atributo == 'maxsed')):
            self.__maxsed = nuevoValor

        elif ((atributo == 16) or (atributo == 'mh1')):
            self.__mh1 = nuevoValor

        elif ((atributo == 17) or (atributo == 'mh2')):
            self.__mh2 = nuevoValor

        elif ((atributo == 18) or (atributo == 'mmr')):
            self.__mmr = nuevoValor

        elif ((atributo == 19) or (atributo == 'posx')):
            self.__posx = nuevoValor

        elif ((atributo == 20) or (atributo == 'posy')):
            self.__posy = nuevoValor

        elif ((atributo == 21) or (atributo == 'edif')):
            self.__edif = nuevoValor

        elif ((atributo == 22) or (atributo == 'estu')):
            self.__estu = nuevoValor

        elif ((atributo == 23) or (atributo == 'entr')):
            self.__entr = nuevoValor

        elif ((atributo == 24) or (atributo == 'obj')):
            self.__obj = nuevoValor

        elif ((atributo == 25) or (atributo == 'nturnos')):
            self.__nturnos = nuevoValor

    # Metodo consultor que devuelve el tamano del equipo
    def obtieneTamEqu (self):
        return self.__tamEqu

    # Metodo consultor que devuelve el valor del elemento del equipo cuya
    # posicion se especifica
    def obtieneEqu (self, posicion):

        if (posicion == 0):
            return self.__equ0

        elif (posicion == 1):
            return self.__equ1

        elif (posicion == 2):
            return self.__equ2

        elif (posicion == 3):
            return self.__equ3

        elif (posicion == 4):
            return self.__equ4

        elif (posicion == 5):
            return self.__equ5

    # Metodo que actualiza con un nuevo valor al elemento del equipo cuya 
    # posicion se especifica
    def reAsignaEqu (self, posicion, nuevoValor):

        if (posicion == 0):
            self.__equ0 = nuevoValor

        elif (posicion == 1):
            self.__equ1 = nuevoValor

        elif (posicion == 2):
            self.__equ2 = nuevoValor

        elif (posicion == 3):
            self.__equ3 = nuevoValor

        elif (posicion == 4):
            self.__equ4 = nuevoValor

        elif (posicion == 5):
            self.__equ5 = nuevoValor

# *************************************************************************
