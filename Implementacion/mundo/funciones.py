
# **************************************************************************
#			  funciones.py	-  description
#   	                       ------------------
# Wizard's Sword
# desarrollado por     : (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


from elemento import *

# *************************************************************************

# Funcion que comprueba si un elemento se encuentra en una lista dada
# de otros elementos
# En caso afirmativo se devuelve el indice del elemento coincidente en la lista
# En otro caso se devuelve -1
def dentro (unElemento, lista, incremento):

    # Obtencion de la posicion (x,y) del elemento
    posx = unElemento.obtienePosx ()
    posy = unElemento.obtienePosy ()

    # Obtencion del tamano en casillas (x,y) del elemento
    casilx = unElemento.obtieneCasilx ()
    casily = unElemento.obtieneCasily ()

    # Obtencion del edificio al que pertenece el elemento
    edif = unElemento.obtieneEdif ()
    
    # Busqueda del elemento en la lista
    for i in range (len (lista)):
        posx1 = lista[i].obtienePosx ()
        posy1 = lista[i].obtienePosy ()

        casilx1 = lista[i].obtieneCasilx ()
        casily1 = lista[i].obtieneCasily ()

        if (incremento == 1):
            posx1 = posx1 - 1
            posy1 = posy1 - 1
            casilx1 = casilx1 + 2
            casily1 = casily1 + 2
            
        edif1 = lista[i].obtieneEdif ()

        if (edif == edif1):
            for x in range (posx, posx + casilx):
                for y in range (posy, posy + casily):
                    if ((x >= posx1) and (x < posx1 + casilx1)):
                        if ((y >= posy1) and (y < posy1 + casily1)):
                            return i
    return -1

# *************************************************************************

# Funcion que comprueba si un elemento se encuentra en los limites indicados
# En caso afirmativo se devuelve 1
# En otro caso se devuelve 0
def dentroLimites (unElemento, casillaInf, casillaSup):

    # Obtencion de la posicion (x,y) del elemento
    posx = unElemento.obtienePosx ()
    posy = unElemento.obtienePosy ()

    # Obtencion del tamano en casillas (x,y) del elemento
    casilx = unElemento.obtieneCasilx ()
    casily = unElemento.obtieneCasily ()
    
    # Busqueda del elemento en la lista
    for x in range (posx, posx + casilx):
        for y in range (posy, posy + casily):
            if ((x <= casillaInf) or (x >= casillaSup) or (y <= casillaInf) or
                (y >= casillaSup)):
                return 0
    return 1

# *************************************************************************
