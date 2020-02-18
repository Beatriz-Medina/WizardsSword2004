
# **************************************************************************
#			  funciones.py   -  description
#   	                       ------------------
# Wizard's Sword
# desarrollado por	: (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


from socket import *
from random import *
from string import *
from time import *
from edificio import *
from objeto import *
from personaje import *
from casilla import *
from elemento import *
from nodoA import *
from operador import *
from elemStrips import *

# *************************************************************************

# Funcion que envia un entero al servidor 
def enviaEnteroAServidor (sockCliente, entero):

    # Conversion del entero a cadena
    cadena = str (entero)

    # Obtencion del tamano de la cadena
    tamanoCadena = len (cadena)

    # Conversion del tamano de la cadena a caracter
    tamano = str (tamanoCadena)

    # Envio del tamano de la cadena al servidor
    sockCliente.send (tamano)
    
    # Envio de la cadena al servidor caracter a caracter
    for i in range (tamanoCadena):
        sockCliente.send (cadena[i])

# *************************************************************************

# Funcion que recibe un entero del servidor
def recibeEnteroDeServidor (sockCliente):

    # Recepcion del tamano de la cadena del servidor
    tamano = sockCliente.recv (1)

    # Conversion a entero del tamano de la cadena
    tamanoCadena = int (tamano)

    # Inicializacion de la cadena
    cadena = ''
    
    # Recepcion de la cadena del servidor caracter a caracter
    for i in range (tamanoCadena):
        caracter = sockCliente.recv (1)
        cadena = cadena + caracter
        
    # Conversion a entero de la cadena
    entero = int (cadena)

    return entero

# *************************************************************************

# Funcion que carga las estructuras del mundo con los datos recibidos a traves
# del servidor y devuelve el indice donde se encuentra el personaje activo 
def cargaMundo (listaEdificios, listaObjetos, listaP, listaCasillas, env,
                sockCliente):
    
    # Recepcion del socket del cliente
    sock = recibeEnteroDeServidor (sockCliente)
    
    # Si el cliente no existe
    if (sock == -1):
	return -1
    
    # Recepcion de la posicion del cursor
    cursorx = recibeEnteroDeServidor (sockCliente)
    cursory = recibeEnteroDeServidor (sockCliente)

    # Recepcion del tamano de la lista de objetos
    tamanoObjetos = recibeEnteroDeServidor (sockCliente)
        
    # Recepcion de cada uno de los objetos y su reconstruccion 
    for i in range (tamanoObjetos):

	# Creacion del objeto
	unObjeto = Objeto ()

	# Obtencion del numero de atributos de cada objeto
	nAtributos = unObjeto.obtieneNAtributos ()

	# Recepcion de cada uno de los atributos
        for j in range (1, nAtributos + 1):

	    # Recepcion del atributo
	    atributo = recibeEnteroDeServidor (sockCliente)
            
	    # Asignacion del atributo
	    unObjeto.reAsignaAtributo (j, atributo) 
        
	# Insercion del objeto en la lista
	listaObjetos.append (unObjeto)
        
    # Recepcion del tamano de la lista de personajes
    tamanoP = recibeEnteroDeServidor (sockCliente)
    
    # Recepcion de cada uno de los personajes y su reconstruccion 
    for i in range (tamanoP):

	# Creacion del personaje
	unPersonaje = Personaje ()
	
	# Obtencion del numero de atributos de cada personaje
	nAtributos = unPersonaje.obtieneNAtributos ()
        
	# Recepcion de cada uno de los atributos
        for j in range (1, nAtributos + 1):

	    # Recepcion del atributo
	    atributo = recibeEnteroDeServidor (sockCliente)
            
	    # Asignacion del atributo
	    unPersonaje.reAsignaAtributo (j, atributo)
            
	# Obtencion del tamano del equipo de cada personaje
	tamanoEqu = unPersonaje.obtieneTamEqu ()

	# Recepcion de cada uno de los elementos del equipo
        for j in range (tamanoEqu):

	    # Recepcion del elemento del equipo
	    atributo = recibeEnteroDeServidor (sockCliente)
            
	    # Asignacion del elemento del equipo
	    unPersonaje.reAsignaEqu (j, atributo)
        
	# Insercion del personaje en la lista
	listaP.append (unPersonaje)
        
	# Obtencion del indice del personaje activo
        if (unPersonaje.obtieneAtributo ('sock') == sock):
	    indiceP = i
        
    # Recepcion del tamano de la lista de elementos
    tamanoElementos = recibeEnteroDeServidor (sockCliente)

    # Recepcion de cada uno de los elementos
    for i in range (tamanoElementos):

        # Creacion del elemento
        unElemento = Elemento ()
        
	# Obtencion del numero de atributos de cada elemento
	nAtributos = unElemento.obtieneNAtributos ()

	# Recepcion de cada uno de los atributos
        for j in range (1, nAtributos + 1):

	    # Recepcion del atributo
	    atributo = recibeEnteroDeServidor (sockCliente)
        
    # Si el envio engloba a todo el mundo
    if (env == 2):
    
        # Recepcion del tamano de la lista de edificios 
        tamanoEdificios = recibeEnteroDeServidor (sockCliente)

        # Recepcion de cada uno de los edificios y su reconstruccion 
        for i in range (tamanoEdificios):
    
            # Creacion del edificio
            unEdificio = Edificio ()

            # Obtencion del numero de atributos de cada edificio
            nAtributos = unEdificio.obtieneNAtributos ()

            # Recepcion de cada uno de los atributos
            for j in range (1, nAtributos + 1):

                # Recepcion del atributo
                atributo = recibeEnteroDeServidor (sockCliente)
                
                # Asignacion del atributo
                unEdificio.reAsignaAtributo (j, atributo)
            
            # Insercion del edificio en la lista
            listaEdificios.append (unEdificio)
                                
        # Recepcion del tamano de la lista de casillas
        tamanoCasillas = recibeEnteroDeServidor (sockCliente)

        # Recepcion de cada una de las casillas y su reconstruccion
        for i in range (tamanoCasillas):

            # Creacion de la casilla
            unaCasilla = Casilla ()

            # Obtencion del numero de atributos de cada casilla
            nAtributos = unaCasilla.obtieneNAtributos ()

            # Recepcion de cada uno de los atributos
            for j in range (1, nAtributos + 1):

                # Recepcion del atributo
                atributo = recibeEnteroDeServidor (sockCliente)
            
                # Asignacion del atributo
                unaCasilla.reAsignaAtributo (j, atributo)
            
            # Insercion de la casilla en la lista
            listaCasillas.append (unaCasilla)            
            
    return indiceP

# *************************************************************************

# Funcion que devuelve el indice de un edificio de la lista dada si la posicion
# especificada coincide con el 
# En otro caso devuelve -1
def coincideEdificio (posx, posy, listaEdificios):
    
    # Obtencion del tamano de la lista de edificios
    tamano = len (listaEdificios)
    
    # Busqueda por la lista de edificios
    for i in range (tamano):
	
	# Obtencion de las coordenadas (x,y) del edificio
	posx1 = listaEdificios[i].obtieneAtributo ('posx')
	posy1 = listaEdificios[i].obtieneAtributo ('posy')
        
	# Obtencion del numero de casillas que ocupa el edificio
	casilx1 = listaEdificios[i].obtieneAtributo ('casilx')
	casily1 = listaEdificios[i].obtieneAtributo ('casily')
        
	# Comprobacion de coordenadas
        if ((posx >= posx1) and (posx < posx1 + casilx1)):
            if ((posy >= posy1) and (posy < posy1 + casily1)):
		return i		    
    
    return -1

# *************************************************************************

# Funcion que devuelve el indice de un objeto de la lista dada si la posicion
# especificada coincide con el 
# En otro caso devuelve -1 
def coincideObjeto (posx, posy, listaObjetos):

    # Obtencion del tamano de la lista de objetos
    tamano = len (listaObjetos)

    # Busqueda por la lista de objetos
    for i in range (tamano):
        
	# Obtencion de las coordenadas (x,y) del objeto
	posx1 = listaObjetos[i].obtieneAtributo ('posx')
	posy1 = listaObjetos[i].obtieneAtributo ('posy')

	# Obtencion del numero de casillas que ocupa el objeto
	casilx1 = listaObjetos[i].obtieneAtributo ('casilx')
	casily1 = listaObjetos[i].obtieneAtributo ('casily')

	# Comprobacion de coordenadas
        if ((posx >= posx1) and (posx < posx1 + casilx1)):
            if ((posy >= posy1) and (posy < posy1 + casily1)):
                    return i		    
                
    return -1

# *************************************************************************

# Funcion que devuelve el indice de un personaje de la lista dada si la
# posicion especificada coincide con el 
# En otro caso devuelve -1 
def coincidePersonaje (posx, posy, listaP):

    # Obtencion del tamano de la lista de personajes
    tamano = len (listaP)

    # Busqueda por la lista de personajes
    for i in range (tamano):

	# Obtencion de las coordenadas (x,y) del personaje 
	posx1 = listaP[i].obtieneAtributo ('posx')
	posy1 = listaP[i].obtieneAtributo ('posy')

	# Comprobacion de coordenadas
        if ((posx1 == posx) and (posy1 == posy)):
	    return i
    
    return -1 


# *************************************************************************

# Funcion que devuelve 1 si la posicion especificada coincide con la salida del
# edificio de la lista indicado
# En otro caso devuelve 0
def coincideSalida (posx, posy, edif, listaEdificios, listaMundo):

    # Obtencion del tipo de edificio
    tipo = obtieneTipoEdificio (edif, listaEdificios)

    # Obtencion de limite inferior en funcion del tipo
    if (tipo == 0):
        inf = listaMundo[2]
    else:
        inf = listaMundo[4]
        
    # Comprobacion de coordenadas
    if ((posx == 0) and (posy == inf)):
        return 1

    return 0
                
# *************************************************************************

# Funcion que devuelve 1 si el edificio indicado coincide con el tipo
# especificado
# En otro caso devuelve 0
def coincideTipoEdificio (edif, tipo, listaEdificios):

    # Obtencion del tamano de la lista de edificios
    tamano = len (listaEdificios)
        
    # Busqueda del edificio por la lista
    for i in range (tamano):

        # Obtencion del identificador del edificio
        id = listaEdificios[i].obtieneAtributo ('id')

        # Si coinciden los identificadores
        if (id == edif):

            # Obtencion del tipo del edificio
            tipoEdificio = listaEdificios[i].obtieneAtributo ('tipo')
            
            # Si coinciden los tipos
            if (tipoEdificio == tipo):
                return 1

    return 0
    
# *************************************************************************

# Funcion que devuelve el tipo del identificador de edificio especificado
# Devuelve -1 en caso de que no lo encuentre
def obtieneTipoEdificio (edif, listaEdificios):

    # Obtencion del tamano de la lista de edificios
    tamano = len (listaEdificios)

    # Busqueda del edificio por la lista
    for i in range (tamano):

        # Obtencion del identificador del edificio
        id = listaEdificios[i].obtieneAtributo ('id')

        # Si coinciden los identificadores
        if (id == edif):

            # Obtencion del tipo del edificio
            tipoEdificio = listaEdificios[i].obtieneAtributo ('tipo')
            return tipoEdificio

    return -1

# *************************************************************************

# Funcion que comprueba si hay un edificio del tipo especificado adyacente a la
# posicion dada
# En ese caso devuelve 1
# En caso contrario devuelve 0
def hayEdificioCerca (posx, posy, tipo, listaEdificios):

    # Obtencion del indice del edificio
    indiceE = coincideEdificio (posx, posy, listaEdificios)

    # Si coincide con algun edificio
    if (indiceE != -1):

        # Obtencion del tipo de edificio
        tipoEdificio = listaEdificios[indiceE].obtieneAtributo ('tipo')

        # Si coinciden los tipos
        if (tipoEdificio == tipo):
            return 1

    return 0
                
# *************************************************************************

# Funcion que comprueba si hay un edificio libre del tipo especificado
# En ese caso devuelve 1
# En caso contrario devuelve 0
def hayEdificioLejos (tipo, listaEdificios, listaP, indiceP):

    # Obtencion del tamano de la lista de edificios
    tamano = len (listaEdificios)

    # Recorrido por la lista
    for i in range (tamano):

        # Obtencion de la posicion del edificio
        posx = listaEdificios[i].obtieneAtributo ('posx')
        posy = listaEdificios[i].obtieneAtributo ('posy') - 1

        # Obtencion del numero de casillas del edificio
        casilx = listaEdificios[i].obtieneAtributo ('casilx')

        # Obtencion del tipo de edificio
        tipoEdificio = listaEdificios[i].obtieneAtributo ('tipo')

        # Si los tipos coinciden
        if (tipoEdificio == tipo):
            
            # Recorrido por la fachada del edificio
            for j in range (posx, posx + casilx):
            
                # Obtencion de algun personaje coincidente
                indiceP1 = coincidePersonaje (j, posy, listaP)
                if (indiceP1 == indiceP):
                    indiceP1 = -1
                    
                # Si no coincide con ningun personaje
                if (indiceP1 == -1):
                    return 1

    return 0
        
# *************************************************************************

# Funcion que devuelve una lista con las coordenadas de entrada del edificio
# libre mas cercano del tipo especificado 
def obtieneEdificioLejos (posx, posy, tipo, listaEdificios, listaP):

    # Obtencion del tamano de la lista de edificios
    tamano = len (listaEdificios)

    # Inicializacion de parametros
    min = 100000
    coorEdificio = []

    # Recorrido por la lista
    for i in range (tamano):

        # Obtencion de la posicion del edificio
        posx1 = listaEdificios[i].obtieneAtributo ('posx')
        posy1 = listaEdificios[i].obtieneAtributo ('posy') - 1

        # Obtencion del numero de casillas del edificio
        casilx = listaEdificios[i].obtieneAtributo ('casilx')

        # Obtencion del tipo de edificio
        tipoEdificio = listaEdificios[i].obtieneAtributo ('tipo')

        # Si los tipos coinciden
        if (tipoEdificio == tipo):
            
            # Recorrido por la fachada del edificio
            for j in range (posx1, posx1 + casilx):
            
                # Obtencion de algun personaje coincidente
                indiceP1 = coincidePersonaje (j, posy1, listaP)
        
                # Si no coincide con ningun personaje
                if (indiceP1 == -1):
                    
                    # Comprobacion de las coordenadas
                    x = abs (posx - j)
                    y = abs (posy - posy1)
                    suma = x + y
                    
                    if (suma < min):
                        min = suma
                        coorEdificio.insert (0, j)
                        coorEdificio.insert (1, posy1)
                        
    return coorEdificio

# *************************************************************************

# Funcion que comprueba si hay un objeto libre del tipo especificado adyacente
# a la posicion dada
# En ese caso devuelve el indice del objeto
# En caso contrario devuelve -1
def obtieneObjetoCerca (posx, posy, tipo, listaObjetos, listaP, indiceP):

    # Obtencion del tamano de la lista de objetos
    tamano = len (listaObjetos)

    # Busqueda de objetos
    for i in range (tamano):

        # Obtencion del tipo del objeto
        tipoObjeto = listaObjetos[i].obtieneAtributo ('tipo')
            
        # Comprobacion del tipo
        if ((tipoObjeto == tipo) or ((tipo == 1) and (tipoObjeto == 2)) or
            ((tipo == 9) and ((tipoObjeto == 9) or (tipoObjeto == 11) or
                              (tipoObjeto == 13) or (tipoObjeto == 15)))):
                    
            # Obtencion de la posicion del objeto
            posx1 = listaObjetos[i].obtieneAtributo ('posx')
            posy1 = listaObjetos[i].obtieneAtributo ('posy')
                
            # Comprobacion de coincidencia con personajes
            if ((tipo < 4) or (tipo == 7) or (tipo == 17)):                    
                indiceP1 = coincidePersonaje (posx1, posy1, listaP)
                if (indiceP1 == indiceP):
                    indiceP1 = -1
                        
            else:
                indiceP1 = -1
                
            # Si no coincide con ningun personaje
            if (indiceP1 == -1):

                # Comprobacion de coordenadas
                if (((posx1 == posx) and (posy1 == posy)) or
                    ((posx1 == posx) and (posy1 == posy + 1)) or
                    ((posx1 == posx) and (posy1 == posy -1)) or
                    ((posx1 == posx + 1) and (posy1 == posy)) or
                    ((posx1 == posx - 1) and (posy1 == posy))):
                    return i

    return -1
    
# *************************************************************************

# Funcion que comprueba si hay un objeto libre del tipo especificado en la
# lista dada
# En ese caso devuelve 1
# En caso contrario devuelve 0
def hayObjetoLejos (tipo, listaObjetos, listaP, indiceP):

    # Obtencion del tamano de la lista de objetos
    tamano = len (listaObjetos)

    # Busqueda por la lista de objetos
    for i in range (tamano):

	# Obtencion del tipo del objeto
        tipoObjeto = listaObjetos[i].obtieneAtributo ('tipo')

        # Comprobacion del tipo
        if ((tipoObjeto == tipo) or ((tipo == 1) and (tipoObjeto == 2)) or
            ((tipo == 9) and ((tipoObjeto == 9) or (tipoObjeto == 11) or
                              (tipoObjeto == 13) or (tipoObjeto == 15)))):
            
            # Obtencion de la posicion del objeto
            posx1 = listaObjetos[i].obtieneAtributo ('posx')
            posy1 = listaObjetos[i].obtieneAtributo ('posy')

            # Si es de tipo portal
            if (tipo == 7):
                posx1 = posx1 + 1
                
            # Comprobacion de coincidencia con personajes 
            if ((tipo < 4) or (tipo == 7) or (tipo == 17)):
                indiceP1 = coincidePersonaje (posx1, posy1, listaP)

            else:
                indiceP1 = -1
                
            # Si no coincide con ningun personaje
            if (indiceP1 == -1):
                return 1

    return 0

# *************************************************************************

# Funcion que devuelve el indice del objeto libre mas cercano del tipo dado
def obtieneObjetoLejos (posx, posy, tipo, listaObjetos, listaP, indiceP):

    # Obtencion del tamano de la lista de objetos
    tamano = len (listaObjetos)

    # Inicializacion de parametros
    min = 100000
    indiceO = -1
    
    # Busqueda por la lista de objetos
    for i in range (tamano):

        # Obtencion del tipo del objeto
        tipoObjeto = listaObjetos[i].obtieneAtributo ('tipo')

        # Comprobacion del tipo
        if ((tipoObjeto == tipo) or ((tipo == 1) and tipoObjeto == 2) or
            ((tipo == 9) and ((tipoObjeto == 9) or (tipoObjeto == 11) or
                              (tipoObjeto == 13) or (tipoObjeto == 15)))):

            # Obtencion de la posicion del objeto
            posx1 = listaObjetos[i].obtieneAtributo ('posx')
            posy1 = listaObjetos[i].obtieneAtributo ('posy')
                
            # Si es de tipo portal
            if (tipo == 7):
                posx1 = posx1 + 1

            # Comprobacion de coincidencia con personajes
            if ((tipo < 4) or (tipo == 7) or (tipo == 17)):
                indiceP1 = coincidePersonaje (posx1, posy1, listaP)

            else:
                indiceP1 = -1
            
            # Si no coincide con ningun personaje
            if (indiceP1 == -1):

                # Comprobacion de las coordenadas
                x = abs (posx - posx1)
                y = abs (posy - posy1)
                suma = x + y
                
                if (suma < min):
                    min = suma
                    indiceO = i
                    
    return indiceO

# *************************************************************************

# Funcion que comprueba si hay un personaje adyacente a la posicion dada
# En ese caso devuelve el indice del personaje
# En caso contrario devuelve -1
def obtienePersonajeCerca (posx, posy, listaP):

    # Obtencion del tamano de la lista de personajes
    tamano = len (listaP)

    # Busqueda de personajes
    for i in range (tamano):
            
        # Obtencion de la posicion del personaje
        posx1 = listaP[i].obtieneAtributo ('posx')
        posy1 = listaP[i].obtieneAtributo ('posy')
        
        # Comprobacion de coordenadas
        if (((posx1 == posx) and (posy1 == posy + 1)) or
            ((posx1 == posx) and (posy1 == posy -1)) or
            ((posx1 == posx + 1) and (posy1 == posy)) or
            ((posx1 == posx - 1) and (posy1 == posy))):
            return i
        
    return -1

# *************************************************************************

# Funcion que comprueba si hay un personaje adyacente a la posicion dada con
# el elemento de equipo especificado
# En ese caso devuelve el indice del personaje
# En caso contrario devuelve -1
def obtienePersonajeEqu (posx, posy, indiceEqu, listaP):

    # Obtencion del tamano de la lista de personajes
    tamano = len (listaP)

    # Busqueda de personajes
    for i in range (tamano):
        
        # Obtencion de la posicion del personaje
        posx1 = listaP[i].obtieneAtributo ('posx')
        posy1 = listaP[i].obtieneAtributo ('posy')
                
        # Obtencion del elemento de equipo
        equ = listaP[i].obtieneEqu (indiceEqu)
        
        # Comprobacion de coordenadas y equipo
        if (equ > 0):
            if (((posx1 == posx) and (posy1 == posy + 1)) or
                ((posx1 == posx) and (posy1 == posy -1)) or
                ((posx1 == posx + 1) and (posy1 == posy)) or
                ((posx1 == posx - 1) and (posy1 == posy))):
                return i

    return -1

# *************************************************************************

# Funcion que devuelve el indice del personaje mas cercano
def obtienePersonajeLejos (posx, posy, listaP, indiceP):

    # Obtencion del tamano de la lista de personajes
    tamano = len (listaP)

    # Inicializacion de parametros
    min = 100000
    indiceP1 = -1
    
    # Busqueda por la lista de personajes
    for i in range (tamano):

        # Si no coincide con el indice
        if (i != indiceP):
            
            # Obtencion de las coordenadas del personaje
            posx1 = listaP[i].obtieneAtributo ('posx')
            posy1 = listaP[i].obtieneAtributo ('posy')

            # Comprobacion de las coordenadas
            x = abs (posx - posx1)
            y = abs (posy - posy1)
            suma = x + y
            
            if (suma < min):
                min = suma
                indiceP1 = i

    return indiceP1

# *************************************************************************

# Funcion que comprueba si hay una casilla libre del tipo especificado
# adyacente a la posicion dada
# En ese caso devuelve el indice de la casilla
# En caso contrario devuelve -1
def obtieneCasillaCerca (posx, posy, tipo, listaCasillas, listaP, indiceP):

    # Obtencion del tamano de la lista de casillas
    tamano = len (listaCasillas)

    # Busqueda de casillas
    for i in range (tamano):

        # Obtencion del tipo de la casilla
        tipoCasilla = listaCasillas[i].obtieneAtributo ('tipo')

        # Comprobacion del tipo de la casilla
        if (tipoCasilla == tipo):
            
            # Obtencion de la posicion de la casilla
            posx1 = listaCasillas[i].obtieneAtributo ('posx')
            posy1 = listaCasillas[i].obtieneAtributo ('posy')
        
            # Obtencion de algun personaje coincidente
            indiceP1 = coincidePersonaje (posx1, posy1, listaP)
            if (indiceP1 == indiceP):
                indiceP1 = -1

            # Comprobacion de coordenadas
            if (indiceP1 == -1):
                if (((posx1 == posx) and (posy1 == posy)) or
                    ((posx1 == posx) and (posy1 == posy + 1)) or
                    ((posx1 == posx) and (posy1 == posy -1)) or
                    ((posx1 == posx + 1) and (posy1 == posy)) or
                    ((posx1 == posx - 1) and (posy1 == posy))):
                    return i

    return -1

# *************************************************************************

# Funcion que comprueba si hay una casilla libre del tipo especificado en la
# lista dada
# En ese caso devuelve 1
# En caso contrario devuelve 0
def hayCasillaLejos (tipo, listaCasillas, listaP):

    # Obtencion del tamano de la lista de casillas
    tamano = len (listaCasillas)

    # Busqueda por la lista de casillas
    for i in range (tamano):

	# Obtencion del tipo de la casilla
        tipoCasilla = listaCasillas[i].obtieneAtributo ('tipo')

        # Comprobacion del tipo
        if (tipoCasilla == tipo):

            # Obtencion de la posicion de la casilla
            posx1 = listaCasillas[i].obtieneAtributo ('posx')
            posy1 = listaCasillas[i].obtieneAtributo ('posy')
        
            # Obtencion de algun personaje coincidente
            indiceP1 = coincidePersonaje (posx1, posy1, listaP)

            # Comprobacion de que la casilla no este ocupada
            if (indiceP1 == -1):            
                return 1

    return 0

# *************************************************************************

# Funcion que devuelve el indice de la casilla libre mas cercana del tipo dado
def obtieneCasillaLejos (posx, posy, tipo, listaCasillas, listaP):

    # Obtencion del tamano de la lista de casillas
    tamano = len (listaCasillas)

    # Inicializacion de parametros
    min = 100000
    indiceC = -1
    
    # Busqueda por la lista de casillas
    for i in range (tamano):

        # Obtencion del tipo de la casilla
        tipoCasilla = listaCasillas[i].obtieneAtributo ('tipo')
        
        # Comprobacion del tipo
        if (tipoCasilla == tipo):
            
            # Obtencion de la posicion de la casilla
            posx1 = listaCasillas[i].obtieneAtributo ('posx')
            posy1 = listaCasillas[i].obtieneAtributo ('posy')

            # Obtencion de algun personaje coincidente
            indiceP1 = coincidePersonaje (posx1, posy1, listaP)

            # Comprobacion de que la casilla no este ocupada
            if (indiceP1 == -1):            

                # Comprobacion de coordenadas
                x = abs (posx - posx1)
                y = abs (posy - posy1)
                suma = x + y
                
                if (suma < min):
                    min = suma
                    indiceC = i
                    
    return indiceC

# *************************************************************************

# Funcion que devuelve 1 si el objeto cuyo indice se especifica es bloqueante
# En caso contrario devuelve 0
def objetoBloqueante (posx, posy, listaObjetos, indiceO):
    
    # Obtencion del tipo del objeto
    tipo = listaObjetos[indiceO].obtieneAtributo ('tipo')

    # Si es de tipo bloqueante
    if ((tipo >= 4) and (tipo != 7) and (tipo != 17) and
        (tipo != 22) and ((tipo < 27) or (tipo == 34))): 
        return 1
        
    # Si es de tipo portal
    elif (tipo == 7):
        
        # Obtencion de las coordenadas del objeto
        x = listaObjetos[indiceO].obtieneAtributo ('posx')
        y = listaObjetos[indiceO].obtieneAtributo ('posy')
        
        # Si la posicion no coincide con el centro
        if ((posx != x + 1) and (posy == y)):
            return 1

    # Si es de tipo trampa
    elif (tipo == 17):
        
        # Obtencion de la visibilidad
        visi = listaObjetos[indiceO].obtieneAtributo ('visi')
        
        # Si es visible
        if (visi == 1):
            return 1

    return 0

# *************************************************************************

# Funcion que realiza un movimiento aleatorio comprobando que no sea
# coincidente con los elementos de las listas especificadas
# Devuelve el sentido del movimiento (1->arriba, 2->abajo. 3->izda, 4->dcha)
def mueveAleatorio (posx, posy, listaMundo, listaEdificios, tipoE,
                    listaObjetos, listaP, indiceP):

    # Obtencion de un movimiento aleatorio
    movimiento = randint (1, 4)

    # Movimiento arriba
    if (movimiento == 1):
        posx1 = posx
        posy1 = posy + 1
            
    # Movimiento abajo
    elif (movimiento == 2):
        posx1 = posx
        posy1 = posy - 1
            
    # Movimiento izquierda
    elif (movimiento == 3):
        posx1 = posx - 1
        posy1 = posy

    # Movimiento derecha
    elif (movimiento == 4):
        posx1 = posx + 1
        posy1 = posy 

    # Comprobacion de coordenadas con limites del mundo
    limite = 0
    
    # Si exterior
    if (tipoE == -1):
        if ((posx < listaMundo[0]) or (posx >= listaMundo[1])):
            limite = 1

        if ((posy < listaMundo[0]) or (posy >= listaMundo[1])):
            limite = 1

    # Si castillo
    elif (tipoE == 0):
        if ((posx < listaMundo[2]) or (posx >= listaMundo[3])):
            limite = 1

        if ((posy < listaMundo[2]) or (posy >= listaMundo[3])):
            limite = 1

    # Si casa
    else:
        if ((posx < listaMundo[4]) or (posx >= listaMundo[5])):
            limite = 1
    
        if ((posy < listaMundo[4]) or (posy >= listaMundo[5])):
            limite = 1

    # Comprobacion de coordenadas con edificios
    indiceE = coincideEdificio (posx1, posy1, listaEdificios)

    # Comprobacion de coordenadas con objetos
    indiceO = coincideObjeto (posx1, posy1, listaObjetos)

    # Si coincide con algun objeto
    if (indiceO != -1):

        # Comprobacion de objetos bloqueantes
        if (objetoBloqueante (posx1, posy1, listaObjetos, indiceO) == 0):
            indiceO = -1
            
    # Comprobacion de coordenadas con personajes
    indiceP1 = coincidePersonaje (posx1, posy1, listaP)
                
    # Mientras las coordenadas coincidan con algun elemento o limite
    while ((indiceE != -1) or (indiceO != -1) or (indiceP1 != -1) or
           (limite == 1)):
        
        # Obtencion de un movimiento aleatorio 
        movimiento = randint (1, 4)

        # Movimiento arriba
        if (movimiento == 1):
            posx1 = posx
            posy1 = posy + 1
                
        # Movimiento abajo
        elif (movimiento == 2):
            posx1 = posx
            posy1 = posy - 1
                
        # Movimiento izquierda
        elif (movimiento == 3):
            posx1 = posx - 1
            posy1 = posy
                        
        # Movimiento derecha
        elif (movimiento == 4):
            posx1 = posx + 1
            posy1 = posy 

        # Comprobacion de coordenadas con limites del mundo
        limite = 0
    
        # Si exterior
        if (tipoE == -1):
            if ((posx < listaMundo[0]) or (posx >= listaMundo[1])):
                limite = 1

            if ((posy < listaMundo[0]) or (posy >= listaMundo[1])):
                limite = 1

        # Si castillo
        elif (tipoE == 0):
            if ((posx < listaMundo[2]) or (posx >= listaMundo[3])):
                limite = 1

            if ((posy < listaMundo[2]) or (posy >= listaMundo[3])):
                limite = 1

        # Si casa
        else:
            if ((posx < listaMundo[4]) or (posx >= listaMundo[5])):
                limite = 1
    
            if ((posy < listaMundo[4]) or (posy >= listaMundo[5])):
                limite = 1

        # Comprobacion de coordenadas con edificios
        indiceE = coincideEdificio (posx1, posy1, listaEdificios)
                        
        # Comprobacion de coordenadas con objetos
        indiceO = coincideObjeto (posx1, posy1, listaObjetos)
            
        # Si coincide con algun objeto
        if (indiceO != -1):

            # Comprobacion de objetos bloqueantes
            if (objetoBloqueante (posx1, posy1, listaObjetos, indiceO) == 0):
                indiceO = -1

        # Comprobacion de coordenadas con personajes
        indiceP1 = coincidePersonaje (posx1, posy1, listaP)
            
    return movimiento

# *************************************************************************

# Funcion que devuelve el indice del nodoA con menor valor de f
def obtieneMenorNodo (abiertos):

    # Inicializacion de parametros
    minf = 100000
    indiceNodo = -1

    # Obtencion del tamano de abiertos
    tamano = len (abiertos)
    
    # Busqueda por la lista de abiertos
    for i in range (tamano):

        # Obtencion del valor f del nodo
        f = abiertos[i].obtieneAtributo ('f')

        # Comprobacion del minimo f
        if (f < minf):
            minf = f
            indiceNodo = i

    return indiceNodo

# *************************************************************************

# Funcion que devuelve el indice del nodoA cuyo identificador se especifica
# En caso de que no lo encuentre devuelve -1
def obtieneIndice (lista, id):

    # Obtencion del tamano de la lista
    tamano = len (lista)

    # Busqueda por la lista
    for i in range (tamano):

        # Obtencion del identificador del nodoA
        id1 = lista[i].obtieneAtributo ('id')

        # Comprobacion del identificador
        if (id1 == id):
            return i

    return -1

# *************************************************************************

# Funcion que devuelve el indice del objeto cuyo tipo y edificio se especifican
# En caso de que no exista dicho item devuelve -1
def obtieneIndiceObjeto (edif, tipoItem, listaObjetos):

    # Obtencion del tamano de la lista de objetos
    tamano = len (listaObjetos)

    # Busqueda por la lista
    for i in range (tamano):

        # Obtencion del edif del objeto
        edif1 = listaObjetos[i].obtieneAtributo ('edif')

        # Obtencion del tipo del objeto
        tipo1 = listaObjetos[i].obtieneAtributo ('tipo')

        # Si coinciden los atributos
        if ((edif1 == edif) and (tipo1 == tipoItem)):
            return i

    return -1
    
# *************************************************************************

# Funcion que obtiene la solucion a traves de la lista de cerrados
def obtieneSolucion (cerrados, nodoSolucion):

    # Obtencion del identificador del nodo padre
    idpa = nodoSolucion.obtieneAtributo ('idpa')

    while (idpa != 0):

        # Obtencion del nodo
        indiceNodo = obtieneIndice (cerrados, idpa)
        nodoSolucion = cerrados[indiceNodo]
        
        # Obtencion del identificador del nodo padre
        idpa = nodoSolucion.obtieneAtributo ('idpa')

    # Obtencion del movimiento
    oper = nodoSolucion.obtieneAtributo ('oper')

    return oper
        
# *************************************************************************

# Funcion que devuelve un nuevo nodoA a partir del especificado aplicando
# la operacion de movimiento dada
def obtieneNodoHijo (nodoActual, movimiento, contador, destx, desty):

    # Obtencion de las coordenadas del nodo actual
    posx = nodoActual.obtieneAtributo ('posx')
    posy = nodoActual.obtieneAtributo ('posy')

    # Obtencion del valor de g del nodo actual
    g = nodoActual.obtieneAtributo ('g')
    
    # Movimiento arriba
    if (movimiento == 1):
        posy = posy + 1

    # Movimiento abajo
    elif (movimiento == 2):
        posy = posy - 1

    # Movimiento izquierda
    elif (movimiento == 3):
        posx = posx - 1

    # Movimiento derecha
    else:
        posx = posx + 1

    # Creacion de un nuevo nodo
    nodoHijo = NodoA ()

    # Calculo de la heuristica
    x = abs (posx - destx)
    y = abs (posy - desty)
    h = x + y

    # Asignacion de atributos al nodo hijo
    nodoHijo.reAsignaAtributo ('id', contador)
    nodoHijo.reAsignaAtributo ('idpa', nodoActual.obtieneAtributo ('id'))
    nodoHijo.reAsignaAtributo ('posx', posx)
    nodoHijo.reAsignaAtributo ('posy', posy)
    nodoHijo.reAsignaAtributo ('oper', movimiento)
    nodoHijo.reAsignaAtributo ('g', g + 1)
    nodoHijo.reAsignaAtributo ('h', h)
    nodoHijo.reAsignaAtributo ('f', g + h + 1)
    
    return nodoHijo

# *************************************************************************

# Funcion que devuelve 1 si dos nodosA tienen el mismo estado
# En otro caso devuelve 0
def nodosIguales (nodo1, nodo2):

    # Obtencion del estado del nodo1
    posx1 = nodo1.obtieneAtributo ('posx')
    posy1 = nodo1.obtieneAtributo ('posy')

    # Obtencion del estado del nodo2
    posx2 = nodo2.obtieneAtributo ('posx')
    posy2 = nodo2.obtieneAtributo ('posy')

    # Comprobacion de estados
    if ((posx1 == posx2) and (posy1 == posy2)):
        return 1
    
    else:
        return 0
    
# *************************************************************************

# Funcion que devuelve 1 si el nodoA especificado no forma ciclos y presenta
# un estado posible
# En otro caso devuelve 0
def nodoAceptable (nodoHijo, cerrados, listaMundo, listaEdificios, tipoE,
                   listaObjetos, listaP):

    # Inicializacion del nodo para comprobar los ciclos
    nodoCiclo = nodoHijo
    
    # Obtencion del identificador del nodo padre
    idpa = nodoCiclo.obtieneAtributo ('idpa')

    # Comprobacion de los ciclos
    while (idpa != None):

        # Obtencion del nodo
        indiceNodo = obtieneIndice (cerrados, idpa)
        nodoCiclo = cerrados[indiceNodo]

        # Comprobacion de nodos
        if (nodosIguales (nodoHijo, nodoCiclo)):
            return 0
        
        # Obtencion del identificador del nodo padre
        idpa = nodoCiclo.obtieneAtributo ('idpa')

    # Obtencion de las coordenadas del nodo
    posx = nodoHijo.obtieneAtributo ('posx')
    posy = nodoHijo.obtieneAtributo ('posy')
    
    # Si limite exterior
    if (tipoE == -1):
        if ((posx < listaMundo[0]) or (posx >= listaMundo[1])):
            return 0

        if ((posy < listaMundo[0]) or (posy >= listaMundo[1])):
            return 0

    # Si limite castillo
    elif (tipoE == 0):
        if ((posx < listaMundo[2]) or (posx >= listaMundo[3])):
            return 0

        if ((posy < listaMundo[2]) or (posy >= listaMundo[3])):
            return 0

    # Si limite casa
    else:
        if ((posx < listaMundo[4]) or (posx >= listaMundo[5])):
            return 0
    
        if ((posy < listaMundo[4]) or (posy >= listaMundo[5])):
            return 0
        
    # Comprobacion de coordenadas con edificios
    if (coincideEdificio (posx, posy, listaEdificios) != -1):
        return 0
    
    # Obtencion del indice del objeto coincidente
    indiceO = coincideObjeto (posx, posy, listaObjetos)

    # Si hay un objeto coincidente
    if (indiceO != -1):

        # Comprobacion de objeto bloqueante
        bloqueante = objetoBloqueante (posx, posy, listaObjetos, indiceO)

        # Si es bloqueante
        if (bloqueante == 1):
            return 0
                    
    # Comprobacion de coordenadas con personajes
    if (coincidePersonaje (posx, posy, listaP) != -1):
        return 0

    return 1

# *************************************************************************

# Funcion que devuelve el indice del nodo especificado en caso de que se
# encuentra en la lista dada
# En caso contrario devuelve -1
def coincideLista (nodoHijo, lista):

    # Obtencion del tamano de la lista
    tamano = len (lista)

    # Recorrido por la lista
    for i in range (tamano):

        # Comprobacion de nodos
        if (nodosIguales (lista[i], nodoHijo)):
            return i

    return -1

# *************************************************************************

# Funcion que comprueba los valores de g entre el nodo hijo y el nodo
# cuyo indice se especifica
# En caso de que el valor de g del hijo sea mejor se actualiza el de la lista
def actualizaNodoHijo (nodoHijo, nodoActual, lista, indiceNodo, movimiento):
    
    # Obtencion del valor de g del nodo de la lista
    gViejo = lista[indiceNodo].obtieneAtributo ('g')

    # Obtencion del valor de g del nodo hijo
    gHijo = nodoHijo.obtieneAtributo ('g')

    # Si se ha obtenido un menor g con el hijo
    if (gHijo < gViejo):

        # Actualizacion del valor de g del nodo de la lista
        lista[indiceNodo].reAsignaAtributo ('g', gHijo)

        # Obtencion del valor de h del nodo de la lista
        h = lista[indiceNodo].obtieneAtributo ('h')

        # Actualizacion del valor de f del nodo de la lista
        lista[indiceNodo].reAsignaAtributo('f', gHijo + h)

        # Actualizacion del idpa del nodo de la lista
        lista[indiceNodo].reAsignaAtributo ('idpa',
                                            nodoActual.obtieneAtributo ('id'))

        # Actualizacion de la operacion de movimiento del nodo de la lista
        lista[indiceNodo].reAsignaAtributo ('oper', movimiento)

# *************************************************************************

# Funcion que devuelve un movimiento optimo siguiendo una busqueda A*
def obtieneMovimientoOptimo (posx, posy, destx, desty, listaMundo,
                             listaEdificios, tipoE, listaObjetos, listaP,
                             tipoSol):

    # Creacion del nodo inicial
    nodoIni = NodoA ()

    # Calculo de la heuristica
    x = abs (posx - destx)
    y = abs (posy - desty)
    h = x + y 

    # Asignacion de atributos del nodo inicial
    nodoIni.reAsignaAtributo ('id', 0)
    nodoIni.reAsignaAtributo ('posx', posx)
    nodoIni.reAsignaAtributo ('posy', posy)
    nodoIni.reAsignaAtributo ('g', 0)
    nodoIni.reAsignaAtributo ('h', h)
    nodoIni.reAsignaAtributo ('f', h)

    # Inicializacion de las listas
    abiertos = []
    cerrados = []

    # Inicializacion del contador de nodos
    contador = 1
    
    # Insercion del nodo inicial en abiertos
    abiertos.append (nodoIni)

    # Bucle A*
    while (abiertos != []):

        # Obtencion del nodoA con menor f
        indiceNodo = obtieneMenorNodo (abiertos)
        nodoActual = abiertos[indiceNodo]
        
        # Eliminacion del nodo actual en abiertos
        abiertos.pop (indiceNodo)
        
        # Insercion del nodo actual en cerrados
        cerrados.append (nodoActual)
        
        # Comprobacion del nodo objetivo
        h = nodoActual.obtieneAtributo ('h')
        if (h == tipoSol):            
            solucion = obtieneSolucion (cerrados, nodoActual)
            return solucion
        
        # Generacion de los hijos
        for i in range (1, 5):
            nodoHijo = obtieneNodoHijo (nodoActual, i, contador, destx, desty)
            
            # Comprobacion de que el nodo hijo sea aceptable
            if (nodoAceptable (nodoHijo, cerrados, listaMundo, listaEdificios,
                               tipoE, listaObjetos, listaP) == 1):
                
                # Comprobacion del nodo en abiertos
                indiceAbiertos = coincideLista (nodoHijo, abiertos)

                # Comprobacion del nodo en cerrados
                indiceCerrados = coincideLista (nodoHijo, cerrados)

                # Si esta en abiertos
                if (indiceAbiertos != -1):

                    # Actualizacion del nodo en abiertos
                    actualizaNodoHijo (nodoHijo, nodoActual, abiertos,
                                       indiceAbiertos, i)
                    
                # Si esta en cerrados
                elif (indiceCerrados != -1):

                    # Actualizacion del nodo en cerrados
                    actualizaNodoHijo (nodoHijo, nodoActual, cerrados,
                                       indiceCerrados, i)
                    
                # Si no esta ni en abiertos ni en cerrados
                else:
                    
                    # Insercion del nodo en abiertos
                    abiertos.append (nodoHijo)
                    
                    # Incremento del contador
                    contador = contador + 1
                    
    return -1

# *************************************************************************

# Funcion que devuelve el tipo del objeto mas caro que pueda comprar el
# personaje especificado en el tipo de edificio dado
def obtieneItemAComprar (listaP, indiceP, listaEdificios, tipoEdificio,
                         listaObjetos):

    # Obtencion del numero de monedas del personaje
    monedas = listaP[indiceP].obtieneEqu (3)

    # Caso 1: monedas >= 250
    if (monedas >= 250):
        if (tipoEdificio == 4):
            tipoItem = 3
            
        else:
            tipoItem = 4           
            
    # Caso 2: monedas == 200
    elif (monedas == 200):
            tipoItem = 3
                        
    # Caso 3: monedas == 150
    elif (monedas == 150):        
            tipoItem = 2

    # Caso 4: monedas == 100
    else:
        tipoItem = 1
            
    return tipoItem

# *************************************************************************

# Funcion que devuelve 1 si el elemento especificado es util para el personaje
# En caso contrario devuelve 0
def elementoUtil (elem, listaP, indiceP):
    
    # Si el elemento es una llave
    if (elem == 0):
        
        # Obtencion de la llave del personaje
        llav = listaP[indiceP].obtieneEqu (4)

        # Si el personaje ya tiene llave
        if (llav == 1):
            return 0

        # Si no tiene llave
        else:
            return 1

    # Si el elemento es una pocion
    elif ((elem >= 1) and (elem <= 10)):

        # Obtencion de la pocion del personaje
        pocion = listaP[indiceP].obtieneEqu (5)

        # Si el personaje ya tiene una pocion
        if (pocion != -1):

            # Obtencion de la pocion objetivo del personaje
            obj = listaP[indiceP].obtieneAtributo ('obj')

            # Si el elemento coincide con el objetivo
            if (elem == obj):
                return 1
            
            # Si no es el objetivo
            else:
                return 0
                    
        # Si no tiene pocion
        else:
            return 1

# *************************************************************************

# Funcion que comprueba si las precondiciones de la lista dada se ajustan
# de acuerdo a las listas del mundo especificadas
# En ese caso devuelve 1
# En caso contrario devuelve 0
def compruebaPrec (prec, listaMundo, listaEdificios, listaObjetos, listaP,
                   indiceP, listaCasillas):

    # Obtencion del tamano de la lista de precondiciones
    tamano = len (prec)

    # Inicializacion del contador de precondiciones
    contador = 0
    
    # Recorrido por todas las precondiciones
    while (contador < tamano):

        # Obtencion de la precondicion
        precond = prec[contador]

        # Precondicion: tieneHambre
        if (precond == 'tieneHambre'):

            # Obtencion del hambre del personaje
            ham = listaP[indiceP].obtieneAtributo ('ham')
            
            # Obtencion del maxham del personaje
            maxham = listaP[indiceP].obtieneAtributo ('maxham')
            
            # Comprobacion del hambre
            if (ham >= maxham/2):
                return 0
                
        # Precondicion: tieneSed
        elif (precond == 'tieneSed'):

            # Obtencion de la sed del personaje
            sed = listaP[indiceP].obtieneAtributo ('sed')

            # Obtencion de la maxsed del personaje
            maxsed = listaP[indiceP].obtieneAtributo ('maxsed')
            
            # Comprobacion de la sed
            if (sed >= maxsed/3):
                return 0

        # Precondicion: tieneCansancio
        elif (precond == 'tieneCansancio'):

            # Obtencion de la energia del personaje
            ene = listaP[indiceP].obtieneAtributo ('ene')

            # Obtencion de la maxene del personaje
            maxene = listaP[indiceP].obtieneAtributo ('maxene')
            
            # Comprobacion del cansancio
            if (ene >= maxene/2):
                return 0

        # Precondicion: tieneDinero
        elif (precond == 'tieneDinero'):

            # Obtencion del dinero del personaje
            monedas = listaP[indiceP].obtieneEqu (3)

            # Comprobacion del dinero
            if (monedas < 50):
                return 0

        # Precondicion: tieneDineroBruja
        elif (precond == 'tieneDineroBruja'):

            # Obtencion del dinero del personaje
            monedas = listaP[indiceP].obtieneEqu (3)

            # Obtencion del numero de entrenamientos del personaje
            entr = listaP[indiceP].obtieneAtributo ('entr')

            # Comprobacion del dinero
            if (monedas < (entr + 1) * 50):
                return 0

        # Precondicion: tieneDineroArmas
        elif (precond == 'tieneDineroArmas'):

            # Obtencion del dinero del personaje
            monedas = listaP[indiceP].obtieneEqu (3)

            # Si no tiene suficiente dinero
            if (monedas < 100):
                return 0
            
            # Obtencion del arma del personaje
            arma = listaP[indiceP].obtieneEqu (1)

            # Obtencion del tipo del item a comprar
            tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios, 3,
                                        listaObjetos)            
            # Comprobacion de item
            if (arma >= tipo):
                return 0
            
        # Precondicion: tieneDineroEscudos
        elif (precond == 'tieneDineroEscudos'):

            # Obtencion del dinero del personaje
            monedas = listaP[indiceP].obtieneEqu (3)

            # Si no tiene suficiente dinero
            if (monedas < 100):
                return 0
            
            # Obtencion del escudo del personaje
            escudo = listaP[indiceP].obtieneEqu (0)

            # Obtencion del tipo del item a comprar
            tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios, 4,
                                        listaObjetos)
            # Comprobacion de item
            if (escudo >= tipo):
                return 0

        # Precondicion: tieneDineroArmaduras
        elif (precond == 'tieneDineroArmaduras'):

            # Obtencion del dinero del personaje
            monedas = listaP[indiceP].obtieneEqu (3)

            # Si no tiene suficiente dinero
            if (monedas < 100):
                return 0
            
            # Obtencion de la armadura del personaje
            armadura = listaP[indiceP].obtieneEqu (2)
            
            # Obtencion del tipo del item a comprar
            tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios, 5,
                                        listaObjetos)
            # Comprobacion de item
            if (armadura >= tipo):
                return 0

        # Precondicion: tieneObjetivo
        elif (precond == 'tieneObjetivo'):

            # Obtencion del objetivo del personaje
            obj = listaP[indiceP].obtieneAtributo ('obj')

            # Comprobacion del objetivo
            if (obj == 0):
                return 0

        # Precondicion: !tieneObjetivo
        elif (precond == '!tieneObjetivo'):

            # Obtencion del objetivo del personaje
            obj = listaP[indiceP].obtieneAtributo ('obj')

            # Comprobacion del objetivo
            if (obj != 0):
                return 0

        # Precondicion: tienePocionObjetivo
        elif (precond == 'tienePocionObjetivo'):

            # Obtencion del objetivo del personaje
            obj = listaP[indiceP].obtieneAtributo ('obj')

            # Obtencion de la pocion del personaje
            pocion = listaP[indiceP].obtieneEqu (5)

            # Comprobacion de pocion objetivo
            if (obj != pocion):
                return 0

        # Precondicion: !tienePocionObjetivo
        elif (precond == '!tienePocionObjetivo'):
            
            # Obtencion del objetivo del personaje
            obj = listaP[indiceP].obtieneAtributo ('obj')

            # Obtencion de la pocion del personaje
            pocion = listaP[indiceP].obtieneEqu (5)

            # Comprobacion de pocion objetivo
            if (obj == pocion):
                return 0

        # Precondicion: tieneLlave
        elif (precond == 'tieneLlave'):

            # Obtencion de la llave del personaje
            llav = listaP[indiceP].obtieneEqu (4)

            # Comprobacion de la llave
            if (llav == -1):
                return 0

        # Precondicion: estaHerido
        elif (precond == 'estaHerido'):

            # Obtencion de los pg del personaje
            pg = listaP[indiceP].obtieneAtributo ('pg')

            # Obtencion de los maxpg del personaje
            maxpg = listaP[indiceP].obtieneAtributo ('maxpg')

            # Comprobacion de los pg
            if (pg == maxpg):
                return 0

        # Precondicion: estaExterior
        elif (precond == 'estaExterior'):

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion del edif
            if (edif != -1):
                return 0

        # Precondicion: salidaLibre
        elif (precond == 'salidaLibre'):

            # Obtencion del edificio donde se encuentra el personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Obtencion del tipo de edificio
            tipoEdificio = obtieneTipoEdificio (edif, listaEdificios)

            # Obtencion del limite inferior del edificio
            if (tipoEdificio == 0):
                inf = listaMundo[2]
            else:
                inf = listaMundo[4]

            # Comprobacion de salida libre
            indiceP1 = coincidePersonaje (0, inf, listaP)
            if (indiceP1 != -1):
                return 0

        # Precondicion: estaSalida
        elif (precond == 'estaSalida'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion de la salida
            sal = coincideSalida (posx, posy, edif, listaEdificios, listaMundo)
            if (sal == 0):
                return 0

        # Precondicion: estaPosada
        elif (precond == 'estaPosada'):

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion de la posada
            coincide = coincideTipoEdificio (edif, 1, listaEdificios)
            if (coincide == 0):
                return 0
            
        # Precondicion: estaBiblioteca
        elif (precond == 'estaBiblioteca'):

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion de la biblioteca
            coincide = coincideTipoEdificio (edif, 2, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: estaArmas
        elif (precond == 'estaArmas'):

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion de la tienda de armas
            coincide = coincideTipoEdificio (edif, 3, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: estaEscudos
        elif (precond == 'estaEscudos'):

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion de la tienda de escudos
            coincide = coincideTipoEdificio (edif, 4, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: estaArmaduras
        elif (precond == 'estaArmaduras'):

            # Obtencion del edif del personaje
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Comprobacion de la tienda de armaduras
            coincide = coincideTipoEdificio (edif, 5, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: estaPortal
        elif (precond == 'estaPortal'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Obtencion del indice del objeto coincidente
            indiceO = coincideObjeto (posx, posy, listaObjetos)

            # Si hay un objeto coincidente
            if (indiceO != -1):

                # Obtencion del tipo del objeto
                tipo = listaObjetos[indiceO].obtieneAtributo ('tipo')
        
                # Si es de tipo portal
                if (tipo == 7):
        
                    # Obtencion de las coordenadas del objeto
                    x = listaObjetos[indiceO].obtieneAtributo ('posx')
                    y = listaObjetos[indiceO].obtieneAtributo ('posy')
			    
                    # Si la posicion no coincide con el centro
                    if ((posx != x + 1) and (posy != y)):
                        return 0
                    
                # Si no es de tipo portal
                else:
                    return 0

            # Si no hay ningun objeto coincidente
            else:
                return 0

        # Precondicion: tieneCastilloCerca
        elif (precond == 'tieneCastilloCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy') + 1

            # Comprobacion del castillo
            coincide = hayEdificioCerca (posx, posy, 0, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: tienePosadaCerca
        elif (precond == 'tienePosadaCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy') + 1

            # Comprobacion de la posada
            coincide = hayEdificioCerca (posx, posy, 1, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: tieneBibliotecaCerca
        elif (precond == 'tieneBibliotecaCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy') + 1

            # Comprobacion de la biblioteca
            coincide = hayEdificioCerca (posx, posy, 2, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: tieneArmasCerca
        elif (precond == 'tieneArmasCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy') + 1

            # Comprobacion de la tienda de armas
            coincide = hayEdificioCerca (posx, posy, 3, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: tieneEscudosCerca
        elif (precond == 'tieneEscudosCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy') + 1

            # Comprobacion de la tienda de escudos
            coincide = hayEdificioCerca (posx, posy, 4, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: tieneArmadurasCerca
        elif (precond == 'tieneArmadurasCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy') + 1

            # Comprobacion de la tienda de armaduras
            coincide = hayEdificioCerca (posx, posy, 5, listaEdificios)
            if (coincide == 0):
                return 0

        # Precondicion: tieneCastilloLejos
        elif (precond == 'tieneCastilloLejos'):

            # Comprobacion del castillo
            coincide = hayEdificioLejos (0, listaEdificios, listaP, indiceP)
            if (coincide == 0):
                return 0

        # Precondicion: tienePosadaLejos
        elif (precond == 'tienePosadaLejos'):

            # Comprobacion de la posada
            coincide = hayEdificioLejos (1, listaEdificios, listaP, indiceP)
            if (coincide == 0):
                return 0

        # Precondicion: tieneBibliotecaLejos
        elif (precond == 'tieneBibliotecaLejos'):

            # Comprobacion de la biblioteca
            coincide = hayEdificioLejos (2, listaEdificios, listaP, indiceP)
            if (coincide == 0):
                return 0

        # Precondicion: tieneArmasLejos
        elif (precond == 'tieneArmasLejos'):

            # Comprobacion de la tienda de armas
            coincide = hayEdificioLejos (3, listaEdificios, listaP, indiceP)
            if (coincide == 0):
                return 0

        # Precondicion: tieneEscudosLejos
        elif (precond == 'tieneEscudosLejos'):

            # Comprobacion de la tienda de escudos
            coincide = hayEdificioLejos (4, listaEdificios, listaP, indiceP)
            if (coincide == 0):
                return 0

        # Precondicion: tieneArmadurasLejos
        elif (precond == 'tieneArmadurasLejos'):

            # Comprobacion de la tienda de armaduras
            coincide = hayEdificioLejos (5, listaEdificios, listaP, indiceP)
            if (coincide == 0):
                return 0

        # Precondicion: tienePosaderaCerca
        elif (precond == 'tienePosaderaCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de posadera cerca
            indiceO = obtieneObjetoCerca (posx, posy, 21, listaObjetos,
                                          listaP, indiceP)
            if (indiceO == -1):
                return 0

        # Precondicion: tienePosaderaLejos
        elif (precond == 'tienePosaderaLejos'):
            
            # Comprobacion de posadera lejos
            indiceO = hayObjetoLejos (21, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0            

        # Precondicion: tieneBrujaCerca
        elif (precond == 'tieneBrujaCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de bruja cerca
            indiceO = obtieneObjetoCerca (posx, posy, 4, listaObjetos,
                                          listaP, indiceP)
            if (indiceO == -1):
                return 0

        # Precondicion: tieneBrujaLejos
        elif (precond == 'tieneBrujaLejos'):

            # Comprobacion de bruja lejos
            indiceO = hayObjetoLejos (4, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0

        # Precondicion: tienePortalLejos
        elif (precond == 'tienePortalLejos'):

            # Comprobacion de portal lejos
            indiceO = hayObjetoLejos (7, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0

        # Precondicion: tienePrisioneroCerca
        elif (precond == 'tienePrisioneroCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de prisionero cerca
            indiceO = obtieneObjetoCerca (posx, posy, 9, listaObjetos,
                                          listaP, indiceP)
            if (indiceO == -1):
                return 0

        # Precondicion: tienePrisioneroLejos
        elif (precond == 'tienePrisioneroLejos'):

            # Comprobacion de prisionero lejos
            indiceO = hayObjetoLejos (9, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0

        # Precondicion: tieneVendedorArmasCerca, tieneVendedorEscudosCerca,
        # tieneVendedorArmadurasCerca
        elif ((precond == 'tieneVendedorArmasCerca') or
              (precond == 'tieneVendedorEscudosCerca') or
              (precond == 'tieneVendedorArmadurasCerca')):
            
            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')
            
            # Comprobacion de vendedor cerca
            indiceO = obtieneObjetoCerca (posx, posy, 25, listaObjetos,
                                          listaP, indiceP)
            if (indiceO == -1):
                return 0

        # Precondicion: tieneVendedorArmasLejos, tieneVendedorEscudosLejos,
        # tieneVendedorArmadurasLejos
        elif ((precond == 'tieneVendedorArmasLejos') or
              (precond == 'tieneVendedorEscudosLejos') or
              (precond == 'tieneVendedorArmadurasLejos')):
            
            # Comprobacion de vendedor lejos
            indiceO = hayObjetoLejos (25, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0

        # Precondicion: tieneBibliotecariaCerca
        elif (precond == 'tieneBibliotecariaCerca'):
            
            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de bibliotecaria cerca
            indiceO = obtieneObjetoCerca (posx, posy, 18, listaObjetos,
                                          listaP, indiceP)
            if (indiceO == -1):
                return 0

        # Precondicion: tieneBibliotecariaLejos
        elif (precond == 'tieneBibliotecariaLejos'):
            
            # Comprobacion de bibliotecaria lejos
            indiceO = hayObjetoLejos (18, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0

        # Precondicion: tieneCofreCerca
        elif (precond == 'tieneCofreCerca'):
            
            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de cofre cerca
            indiceO = obtieneObjetoCerca (posx, posy, 3, listaObjetos,
                                          listaP, indiceP)
            
            if (indiceO == -1):
                return 0

        # Precondicion: tieneCofreLejos
        elif (precond == 'tieneCofreLejos'):
            
            # Comprobacion de cofre lejos
            indiceO = hayObjetoLejos (3, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0

        # Precondicion: tieneComidaCerca
        elif (precond == 'tieneComidaCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de comida cerca
            indiceO = obtieneObjetoCerca (posx, posy, 1, listaObjetos,
                                          listaP, indiceP)
            if (indiceO == -1):
                return 0

        # Precondicion: tieneComidaLejos
        elif (precond == 'tieneComidaLejos'):

            # Comprobacion de comida lejos
            indiceO = hayObjetoLejos (1, listaObjetos, listaP, indiceP)
            if (indiceO == 0):
                return 0            
                    
        # Precondicion: tieneAguaCerca
        elif (precond == 'tieneAguaCerca'):

            # Obtencion de las coordenadas del personaje
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de agua cerca
            indiceC = obtieneCasillaCerca (posx, posy, 3, listaCasillas,
                                           listaP, indiceP)                
            if (indiceC == -1):
                return 0
                
        # Precondicion: tieneAguaLejos
        elif (precond == 'tieneAguaLejos'):

            # Comprobacion de agua lejos
            indiceC = hayCasillaLejos (3, listaCasillas, listaP)
            if (indiceC == 0):
                return 0
                        
        # Precondicion: tienePersonajeCerca
        elif (precond == 'tienePersonajeCerca'):

            # Obtencion de las coordenadas del personaje activo
            posx = listaP[indiceP].obtieneAtributo ('posx')
            posy = listaP[indiceP].obtieneAtributo ('posy')

            # Comprobacion de personaje cerca
            indiceP1 = obtienePersonajeCerca (posx, posy, listaP)            
            if (indiceP1 == -1):
                return 0

        # Precondicion: tienePersonajeLejos
        elif (precond == 'tienePersonajeLejos'):
                
            # Comprobacion de personaje lejos
            if (len (listaP) == 1):
                return 0
                            
        # Incremento del contador
        contador = contador + 1

    return 1
            
# *************************************************************************

# Funcion que comprueba si la regla especificada es verdadera
# En ese caso devuelve la postcondicion de la regla 
# En caso contrario devuelve una postcondicion nula 
def compruebaRegla (regla, listaMundo, listaEdificios, listaObjetos, listaP,
                    indiceP, listaCasillas):

    # Obtencion de la lista de tokens
    tokens = split (regla)

    # Obtencion del tamano de la lista de tokens
    tamano = len (tokens)
    
    # Obtencion de la postcondicion de la regla
    postRegla = tokens[tamano-1]

    # Obtencion de la lista de precondiciones de la regla
    prec = tokens [:tamano-1]

    # Comprobacion de las precondiciones
    verdadero = compruebaPrec (prec, listaMundo, listaEdificios, listaObjetos,
                               listaP, indiceP, listaCasillas)
    
    # Si se cumplen
    if (verdadero):
        return postRegla

    # Si no se cumplen
    else:
        return ''

# *************************************************************************

# Funcion que se encarga de enviar al servidor la informacion necesaria para
# realizar la accion especificada
def realizaAccion (accion, listaMundo, listaEdificios, listaObjetos,
                   listaP, indiceP, listaCasillas, sockCliente):
    
    # Obtencion de las coordenadas del personaje activo
    posx = listaP[indiceP].obtieneAtributo ('posx')
    posy = listaP[indiceP].obtieneAtributo ('posy')

    # Comprobacion de la accion
    # Accion: Comer
    if (accion == 'Comer'):
        
        # Obtencion del indice del objeto
        indiceO = obtieneObjetoCerca (posx, posy, 1, listaObjetos,
                                      listaP, indiceP)

        # Obtencion del tipo del objeto
        tipo = listaObjetos[indiceO].obtieneAtributo ('tipo')

        # Si es de tipo setas
        if (tipo == 1):

            # Envio de la accion al servidor
            enviaEnteroAServidor (sockCliente, 6)

        # Si es de tipo miel
        else:
            
            # Obtencion de las coordenadas del objeto
            coorx = listaObjetos[indiceO].obtieneAtributo ('posx')
            coory = listaObjetos[indiceO].obtieneAtributo ('posy')
        
            # Envio de la accion al servidor
            enviaEnteroAServidor (sockCliente, 7)
        
            # Envio de las coordenadas al servidor
            enviaEnteroAServidor (sockCliente, coorx)
            enviaEnteroAServidor (sockCliente, coory)
        
    # Accion: Beber
    elif (accion == 'Beber'):

        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 24)
                
    # Accion: Descansar
    elif (accion == 'Descansar'):

        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 3)

    # Accion: Finalizar Mision
    elif (accion == 'FinalizarMision'):

        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 25)

    # Accion: Curarse
    elif (accion == 'Curarse'):
                    
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 12)
                
    # Accion: Defenderse, Atacar
    elif ((accion == 'Defenderse') or (accion == 'Atacar')):

        # Obtencion del indice del personaje para atacar
        indiceP1 = obtienePersonajeCerca (posx, posy, listaP)
        
        # Obtencion de las coordenadas del personaje
        coorx = listaP[indiceP1].obtieneAtributo ('posx')
        coory = listaP[indiceP1].obtieneAtributo ('posy')
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 4)
        
        # Envio de las coordenadas al servidor
        enviaEnteroAServidor (sockCliente, coorx)
        enviaEnteroAServidor (sockCliente, coory)
        
    # Accion: AceptarMision
    elif (accion == 'AceptarMision'):
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 9)
                
    # Accion: Estudiar
    elif (accion == 'Estudiar'):
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 11)
                
    # Accion: ComprarArma
    elif (accion == 'ComprarArma'):
        
        # Obtencion del edificio donde se encuentra el personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Obtencion del tipo de edificio
        tipoEdificio = obtieneTipoEdificio (edif, listaEdificios)
        
        # Obtencion del tipo del objeto a comprar
        tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios,
                                    tipoEdificio, listaObjetos)

        tipo = tipo + 12
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, tipo)

    # Accion: ComprarEscudo
    elif (accion == 'ComprarEscudo'):
        
        # Obtencion del edificio donde se encuentra el personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Obtencion del tipo de edificio
        tipoEdificio = obtieneTipoEdificio (edif, listaEdificios)
        
        # Obtencion del tipo del objeto a comprar
        tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios,
                                    tipoEdificio, listaObjetos)

        tipo = tipo + 16
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, tipo)

    # Accion: ComprarArmadura
    elif (accion == 'ComprarArmadura'):
        
        # Obtencion del edificio donde se encuentra el personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Obtencion del tipo de edificio
        tipoEdificio = obtieneTipoEdificio (edif, listaEdificios)
        
        # Obtencion del tipo del objeto a comprar
        tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios,
                                    tipoEdificio, listaObjetos)

        tipo = tipo + 20
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, tipo)

    # Accion: AbrirCofre
    elif (accion == 'AbrirCofre'):
        
        # Obtencion del indice del objeto cofre
        indiceO = obtieneObjetoCerca (posx, posy, 3, listaObjetos,
                                      listaP, indiceP)
        
        # Obtencion de las coordenadas del objeto
        coorx = listaObjetos[indiceO].obtieneAtributo ('posx')
        coory = listaObjetos[indiceO].obtieneAtributo ('posy')
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 8)
        
        # Envio de las coordenadas al servidor
        enviaEnteroAServidor (sockCliente, coorx)
        enviaEnteroAServidor (sockCliente, coory)
                    
    # Accion: Robar
    elif (accion == 'Robar'):
            
        # Obtencion del indice del personaje para robar
        indiceP1 = obtienePersonajeEqu (posx, posy, 3, listaP)
        
        # Obtencion de las coordenadas del personaje
        coorx = listaP[indiceP1].obtieneAtributo ('posx')
        coory = listaP[indiceP1].obtieneAtributo ('posy')
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 5)
        
        # Envio de las coordenadas al servidor
        enviaEnteroAServidor (sockCliente, coorx)
        enviaEnteroAServidor (sockCliente, coory)
                
    # Accion: LiberarPrisionero
    elif (accion == 'LiberarPrisionero'):

        # Obtencion del indice del objeto prisionero
        indiceO = obtieneObjetoCerca (posx, posy, 9, listaObjetos,
                                      listaP, indiceP)
        
        # Obtencion de las coordenadas del objeto
        coorx = listaObjetos[indiceO].obtieneAtributo ('posx')
        coory = listaObjetos[indiceO].obtieneAtributo ('posy')
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 10)
        
        # Envio de las coordenadas al servidor
        enviaEnteroAServidor (sockCliente, coorx)
        enviaEnteroAServidor (sockCliente, coory)
        
    # Accion: EntrarCastillo, EntrarPosada, EntrarBiblioteca, EntrarArmas,
    # EntrarEscudos, EntrarArmaduras
    elif ((accion == 'EntrarCastillo') or (accion == 'EntrarPosada') or
          (accion == 'EntrarBiblioteca') or (accion == 'EntrarArmas') or
          (accion == 'EntrarEscudos') or (accion == 'EntrarArmaduras')):

        # Obtencion de las coordenadas a enviar
        coorx = posx
        coory = posy + 1
        entrada = 1
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 1)
        
        # Envio de las coordenadas al servidor
        enviaEnteroAServidor (sockCliente, coorx)
        enviaEnteroAServidor (sockCliente, coory)
        enviaEnteroAServidor (sockCliente, entrada)  
        
    # Accion: Salir
    elif (accion == 'Salir'):

        # Obtencion de las coordenadas a enviar
        coorx = posx
        coory = posy - 1
        entrada = 0
        
        # Envio de la accion al servidor
        enviaEnteroAServidor (sockCliente, 1)
        
        # Envio de las coordenadas al servidor
        enviaEnteroAServidor (sockCliente, coorx)
        enviaEnteroAServidor (sockCliente, coory)
        enviaEnteroAServidor (sockCliente, entrada)
        
    # Acciones de movimiento
    else:

        # Obtencion del edificio donde se encuentra el personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Obtencion del tipo de edificio
        tipoE = obtieneTipoEdificio (edif, listaEdificios)
        
        # Accion: MoverHaciaSalida
        if (accion == 'MoverHaciaSalida'):
            
            # Obtencion del limite inferior del edificio
            if (tipoE == 0):
                inf = listaMundo[2]
            else:
                inf = listaMundo[4]

            # Obtencion de las coordenadas
            destx = 0
            desty = inf 

            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)

        # Accion: MoverHaciaCastillo
        elif (accion == 'MoverHaciaCastillo'):

            # Obtencion del castillo mas cercano
            coorEdificio = obtieneEdificioLejos (posx, posy, 0,
                                                 listaEdificios, listaP)
            
            # Obtencion de las coordenadas
            destx = coorEdificio[0]
            desty = coorEdificio[1]
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaPosada
        elif (accion == 'MoverHaciaPosada'):

            # Obtencion de la posada mas cercana
            coorEdificio = obtieneEdificioLejos (posx, posy, 1,
                                                 listaEdificios, listaP)

            # Obtencion de las coordenadas
            destx = coorEdificio[0]
            desty = coorEdificio[1]
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaBiblioteca
        elif (accion == 'MoverHaciaBiblioteca'):
                            
            # Obtencion de la biblioteca mas cercana
            coorEdificio = obtieneEdificioLejos (posx, posy, 2,
                                                 listaEdificios, listaP)

            # Obtencion de las coordenadas
            destx = coorEdificio[0]
            desty = coorEdificio[1]
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaArmas
        elif (accion == 'MoverHaciaArmas'):
                            
            # Obtencion de la tienda de armas mas cercana
            coorEdificio = obtieneEdificioLejos (posx, posy, 3,
                                                 listaEdificios, listaP)

            # Obtencion de las coordenadas
            destx = coorEdificio[0]
            desty = coorEdificio[1]
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaEscudos
        elif (accion == 'MoverHaciaEscudos'):
                            
            # Obtencion de la tienda de escudos mas cercana
            coorEdificio = obtieneEdificioLejos (posx, posy, 4,
                                                 listaEdificios, listaP)

            # Obtencion de las coordenadas
            destx = coorEdificio[0]
            desty = coorEdificio[1]
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaArmaduras
        elif (accion == 'MoverHaciaArmaduras'):
                            
            # Obtencion de la tienda de armaduras mas cercana
            coorEdificio = obtieneEdificioLejos (posx, posy, 5,
                                                 listaEdificios, listaP)

            # Obtencion de las coordenadas
            destx = coorEdificio[0]
            desty = coorEdificio[1]
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaPosadera
        elif (accion == 'MoverHaciaPosadera'):

            # Obtencion del objeto posadera mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 21, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaVendedorArmas, MoverHaciaVendedorEscudos,
        # MoverHaciaVendedorArmaduras
        elif ((accion == 'MoverHaciaVendedorArmas') or
              (accion == 'MoverHaciaVendedorEscudos') or
              (accion == 'MoverHaciaVendedorArmaduras')):
                
            # Obtencion del objeto vendedor mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 25, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaBibliotecaria
        elif (accion == 'MoverHaciaBibliotecaria'):

            # Obtencion del objeto bibliotecaria mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 18, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaBruja
        elif (accion == 'MoverHaciaBruja'):

            # Obtencion del objeto bruja mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 4, listaObjetos,
                                          listaP, indiceP)

            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')

            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaPrisionero
        elif (accion == 'MoverHaciaPrisionero'):

            # Obtencion del objeto prisionero mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 9, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
        # Accion: MoverHaciaCofre
        elif (accion == 'MoverHaciaCofre'):

            # Obtencion del objeto cofre mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 3, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE, 
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaPortal
        elif (accion == 'MoverHaciaPortal'):

            # Obtencion del objeto portal mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 7, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx') + 1
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 0)
            
        # Accion: MoverHaciaPersonaje
        elif (accion == 'MoverHaciaPersonaje'):

            # Obtencion del personaje mas cercano
            indiceP1 = obtienePersonajeLejos (posx, posy, listaP, indiceP)
            
            # Obtencion de las coordenadas del personaje
            destx = listaP[indiceP1].obtieneAtributo ('posx')
            desty = listaP[indiceP1].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaComida
        elif (accion == 'MoverHaciaComida'):
                
            # Obtencion del objeto comida mas cercano
            indiceO = obtieneObjetoLejos (posx, posy, 1, listaObjetos,
                                          listaP, indiceP)
            
            # Obtencion de las coordenadas del objeto
            destx = listaObjetos[indiceO].obtieneAtributo ('posx')
            desty = listaObjetos[indiceO].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
            
        # Accion: MoverHaciaAgua
        elif (accion == 'MoverHaciaAgua'):
                
            # Obtencion de la casilla de agua mas cercana
            indiceC = obtieneCasillaLejos (posx, posy, 3, listaCasillas,
                                           listaP)
            
            # Obtencion de las coordenadas de la casilla
            destx = listaCasillas[indiceC].obtieneAtributo ('posx')
            desty = listaCasillas[indiceC].obtieneAtributo ('posy')
            
            # Obtencion del movimiento por el menor camino
            movimiento = obtieneMovimientoOptimo (posx, posy, destx, desty,
                                                  listaMundo,
                                                  listaEdificios, tipoE,
                                                  listaObjetos, listaP, 1)
        # Accion: MoverAleatorio
        else:
            
            # Obtencion de un movimiento aleatorio
            movimiento = mueveAleatorio (posx, posy, listaMundo,
                                         listaEdificios, tipoE,
                                         listaObjetos,
                                         listaP, indiceP)
            
        # Obtencion de las nuevas coordenadas en funcion del movimiento
        entrada = 0            
        if (movimiento == 1):
            coorx = posx
            coory = posy + 1
            entrada = 1
            
        elif (movimiento == 2):
            coorx = posx
            coory = posy - 1
            
        elif (movimiento == 3):
            coorx = posx - 1
            coory = posy
            
        else:
            coorx = posx + 1
            coory = posy
            
        # Si el movimiento es correcto
        if (movimiento != -1):
                
            # Envio de la accion al servidor
            enviaEnteroAServidor (sockCliente, 1)
                
            # Envio de las coordenadas al servidor
            enviaEnteroAServidor (sockCliente, coorx)
            enviaEnteroAServidor (sockCliente, coory)
            enviaEnteroAServidor (sockCliente, entrada)
            
        # Si no es correcto
        else:
            enviaEnteroAServidor (sockCliente, 0)

# *************************************************************************

# Funcion que toma una decision a partir de unas reglas para actuar en el mundo
def tomaDecisionReglas (listaMundo, listaEdificios, listaObjetos, listaP,
                        indiceP, listaCasillas, turno, sockCliente):
    
    # Obtencion del socket del cliente
    sock = listaP[indiceP].obtieneAtributo ('sock')
        
    # Si le toca el turno
    if (sock == turno):

        # Obtencion de la especie del cliente
        esp = listaP[indiceP].obtieneAtributo ('esp')
        
        # Apertura del fichero de reglas
        if (esp == 4):
            ficheroReglas = open ('./reglas1.txt', 'r')

        else:
            ficheroReglas = open ('./reglas2.txt', 'r')
                    
        # Lectura anticipada
        regla = ficheroReglas.readline ()

        # Inicializacion del contador de reglas
        contador = 1
        
        # Recorrido por el fichero de reglas
        while (regla != ''):
            
            # Obtencion de la postcondicion
            postcond = compruebaRegla (regla, listaMundo, listaEdificios,
                                       listaObjetos, listaP, indiceP,
                                       listaCasillas)
            
            # Si se cumple la regla
            if (postcond != ''):
                regla = ''

            # En otro caso
            else:
                # Lectura de la regla siguiente
                regla = ficheroReglas.readline ()

                # Incremento del contador de reglas
                contador = contador + 1

        # Impresion de las caracteristicas del personaje activo
        imprimeCaracteristicas (listaP, indiceP)

        # Impresion de la regla
        print 'regla:', contador, postcond

        # Realizacion de la accion correspondiente
        realizaAccion (postcond, listaMundo, listaEdificios, listaObjetos,
                       listaP, indiceP, listaCasillas, sockCliente)
        
    # Si no le toca el turno
    else:
        enviaEnteroAServidor (sockCliente, 0)
    
# *************************************************************************

# Funcion que carga en una lista los operadores Strips a partir de un fichero
def cargaOperadores (listaOperadores):

    # Apertura del fichero de operadores
    ficheroOperadores = open ('./operadores.txt', 'r')
    
    # Lectura anticipada del operador
    nombre = ficheroOperadores.readline ()
    prec = ficheroOperadores.readline ()
    post = ficheroOperadores.readline ()

    # Eliminacion del \n
    tamano = len (nombre)
    nombre = nombre[:tamano - 1]
    
    # Si hay un operador
    if (nombre != ''):

        # Creacion de un nuevo operador
        unOperador = Operador ()

        # Insercion del nombre del operador
        unOperador.reAsignaNombre (nombre)

        # Obtencion de las precondiciones en lista de tokens
        tokens = split (prec)

        # Obtencion del tamano de las precondiciones
        tamano = len (tokens)
        
        # Asignacion de cada precondicion al operador
        for i in range (tamano):
            unOperador.insertaPrecond (tokens[i])

        # Obtencion de las postcondiciones en lista de tokens
        tokens = split (post)

        # Obtencion del tamano de las postcondiciones
        tamano = len (tokens)

        # Asignacion de cada postcondicion al operador
        for i in range (tamano):
            unOperador.insertaPostcond (tokens[i])

        # Insercion del operador en la lista
        listaOperadores.append (unOperador)
        
    # Recorrido por el fichero de operadores
    while (nombre != ''):
            
        # Lectura del operador siguiente
        nombre = ficheroOperadores.readline ()
        prec = ficheroOperadores.readline ()
        post = ficheroOperadores.readline ()

        # Eliminacion del \n
        tamano = len (nombre)
        nombre = nombre[:tamano - 1]

        # Si hay un operador
        if (nombre != ''):

            # Creacion de un nuevo operador
            unOperador = Operador ()
            
            # Insercion del nombre del operador
            unOperador.reAsignaNombre (nombre)

            # Obtencion de las precondiciones en lista de tokens
            tokens = split (prec)
            
            # Obtencion del tamano de las precondiciones
            tamano = len (tokens)

            # Asignacion de cada precondicion al operador
            for i in range (tamano):
                unOperador.insertaPrecond (tokens[i])

            # Obtencion de las postcondiciones en lista de tokens
            tokens = split (post)

            # Obtencion del tamano de las postcondiciones
            tamano = len (tokens)

            # Asignacion de cada postcondicion al operador
            for i in range (tamano):
                unOperador.insertaPostcond (tokens[i])

            # Insercion del operador en la lista
            listaOperadores.append (unOperador)


# *************************************************************************

# Funcion que devuelve el car del personaje de la lista especificado
def obtieneCar (listaP, indiceP):

    # Obtencion del tipo de escudo
    carEscudo = listaP[indiceP].obtieneEqu (0)

    # Si no tiene escudo
    if (carEscudo == -1):
        carEscudo = 0

    # Si el escudo es de tipo 3
    elif (carEscudo == 3):
        carEscudo = 4

    # Obtencion del tipo de arma
    carArma = listaP[indiceP].obtieneEqu (1)

    # Si no tiene arma
    if (carArma == -1):
        carArma = 0

    # Obtencion del tipo de armadura
    carArmadura = listaP[indiceP].obtieneEqu (2)

    # Si no tiene armadura
    if (carArmadura == -1):
        carArmadura = 0

    # Suma total de todos los car
    car = carEscudo + carArma + carArmadura

    return car

# *************************************************************************

# Funcion que devuelve un objetivo a cumplir en funcion de unas determinadas
# condiciones
def obtieneObjetivo (objetivo, listaEdificios, listaObjetos, listaP,
                     indiceP, listaCasillas):
    
    # 1. Comprobacion de objetivo: comer
    # Obtencion del hambre del personaje
    ham = listaP[indiceP].obtieneAtributo ('ham')
            
    # Obtencion del maxham del personaje
    maxham = listaP[indiceP].obtieneAtributo ('maxham')
            
    # Comprobacion final
    if (ham < maxham/2):
        return 1
    
    # 2. Comprobacion de objetivo: beber
    # Obtencion de la sed del personaje
    sed = listaP[indiceP].obtieneAtributo ('sed')

    # Obtencion de la maxsed del personaje
    maxsed = listaP[indiceP].obtieneAtributo ('maxsed')
            
    # Comprobacion final
    if ((sed < maxsed/3) and ((objetivo >= 2) or (objetivo == 0))):
        return 2
    
    # 3. Comprobacion de objetivo: descansar
    # Obtencion de la energia del personaje
    ene = listaP[indiceP].obtieneAtributo ('ene')

    # Obtencion de la maxene del personaje
    maxene = listaP[indiceP].obtieneAtributo ('maxene')
            
    # Comprobacion final
    if ((ene < maxene/2) and ((objetivo >= 3) or (objetivo == 0))):
        return 3
    
    # 4. Comprobacion de objetivo: curarse
    # Obtencion de los pg del personaje
    pg = listaP[indiceP].obtieneAtributo ('pg')

    # Obtencion de los maxpg del personaje
    maxpg = listaP[indiceP].obtieneAtributo ('maxpg')

    # Obtencion del edificio donde se encuentra el personaje
    edif = listaP[indiceP].obtieneAtributo ('edif')

    # Si esta en el exterior
    if (edif == -1):
        
        # Comprobacion de posadas
        coincide = hayEdificioLejos (1, listaEdificios, listaP, indiceP)

    else:
        coincide = 0
        
    # Comprobacion final
    if ((pg != maxpg) and (coincide >= 1) and
        ((objetivo >= 4) or (objetivo == 0))):
        return 4
    
    # 5. Comprobacion de objetivo: defenderse
    # Obtencion de los pg del personaje
    pg = listaP[indiceP].obtieneAtributo ('pg')

    # Obtencion de los maxpg del personaje
    maxpg = listaP[indiceP].obtieneAtributo ('maxpg')

    # Comprobacion final
    if ((pg != maxpg) and ((objetivo >= 5) or (objetivo == 0))):
        return 5
    
    # 6. Comprobacion de objetivo: finalizarMision
    # Comprobacion con brujas
    coincide = hayObjetoLejos (4, listaObjetos, listaP, indiceP)

    # Comprobacion de mision objetivo
    obj = listaP[indiceP].obtieneAtributo ('obj')
    
    # Comprobacion final
    if (((coincide >= 1) or (obj != 0)) and
        ((objetivo >= 6) or (objetivo == 0))):            
        return 6
    
    # 7. Comprobacion de objetivo: estudiar
    # Obtencion del edificio donde se encuentra el personaje
    edif = listaP[indiceP].obtieneAtributo ('edif')

    # Si esta en el exterior
    if (edif == -1):

        # Comprobacion de bibliotecas
        coincide = hayEdificioLejos (2, listaEdificios, listaP, indiceP)

    else:
        coincide = 0
        
    # Comprobacion final
    if ((coincide >= 1) and ((objetivo >= 7) or (objetivo == 0))):
        return 7
    
    # 8. Comprobacion de objetivo: comprarArma
    # Obtencion del edificio donde se encuentra el personaje
    edif = listaP[indiceP].obtieneAtributo ('edif')

    # Si esta en el exterior
    if (edif == -1):

            # Comprobacion de tiendas de armas
            coincide = hayEdificioLejos (3, listaEdificios, listaP, indiceP)

    else:
        coincide = 0

    # Obtencion del arma del personaje
    arma = listaP[indiceP].obtieneEqu (1)
    
    # Obtencion del mmr del personaje
    mmr = listaP[indiceP].obtieneAtributo ('mmr') + 2

    # Obtencion de la car del personaje
    car = obtieneCar (listaP, indiceP)
    
    # Comprobacion final
    if ((coincide >= 1) and (mmr < 10) and (car < 5) and (arma < 4) and
        ((objetivo >= 8) or (objetivo == 0))):            
        return 8
    
    # 9. Comprobacion de objetivo: comprarEscudo
    # Obtencion del edificio donde se encuentra el personaje
    edif = listaP[indiceP].obtieneAtributo ('edif')

    # Si esta en el exterior
    if (edif == -1):

            # Comprobacion con tiendas de escudos
            coincide = hayEdificioLejos (4, listaEdificios, listaP, indiceP)
            
    else:
        coincide = 0
        
    # Obtencion del escudo del personaje
    escudo = listaP[indiceP].obtieneEqu (0)

    # Obtencion del mmr del personaje
    mmr = listaP[indiceP].obtieneAtributo ('mmr') + 3

    # Obtencion de la car del personaje
    car = obtieneCar (listaP, indiceP)
    
    # Comprobacion final
    if ((coincide == 1) and (mmr < 10) and (car < 5) and (escudo < 3) and
        ((objetivo >= 9) or (objetivo == 0))):
        return 9
    
    # 10. Comprobacion de objetivo: comprarArmadura
    # Obtencion del edificio donde se encuentra el personaje
    edif = listaP[indiceP].obtieneAtributo ('edif')

    # Si esta en el exterior
    if (edif == -1):

            # Comprobacion con tiendas de armaduras
            coincide = hayEdificioLejos (5, listaEdificios, listaP, indiceP)

    else:
        coincide = 0
        
    # Obtencion de la armadura del personaje
    armadura = listaP[indiceP].obtieneEqu (2)

    # Obtencion de la car del personaje
    car = obtieneCar (listaP, indiceP)
    
    # Comprobacion final
    if ((coincide == 1) and (car < 5) and (armadura < 4) and
        ((objetivo >= 10) or (objetivo == 0))):
        return 10

    return 0

# *************************************************************************

# Funcion que inserta las postcondiciones del operador especificado en
# la lista dada
def insertaPostcondiciones (nombreOperador, listaOperadores, lista):

    # Obtencion del tamano de la lista de operadores
    tamano = len (listaOperadores)
    
    # Busqueda del operador por la lista
    for i in range (tamano):

        # Obtencion del nombre del operador
        nombre = listaOperadores[i].obtieneNombre ()

        # Si coinciden los operadores
        if (nombre == nombreOperador):

            # Obtencion del tamano de las postcondiciones
            tamPost = listaOperadores[i].obtieneNPost ()

            # Insercion de las postcondiciones una a una
            for j in range (tamPost):
                lista.append (listaOperadores[i].obtienePostcond (j))

            return
        
# *************************************************************************

# Funcion que devuelve 1 si la cadena especificada se encuentra en la
# lista dada
# En caso contrario devuelve 0
def estaIncluido (cadena, lista):

    # Obtencion del tamano de la lista
    tamano = len (lista)

    # Recorrido por la lista
    for i in range (tamano):

        # Si coinciden
        if (lista[i] == cadena):
            return 1

    return 0
        
# *************************************************************************

# Funcion que devuelve 1 si la cadena especificada aparece en la pila Strips
# En caso contrario devuelve 0
def incluyeAccion (cadena, pila):

    # Obtencion del tamano de la pila
    tamano = len (pila)

    # Busqueda por la pila
    for i in range (tamano):

        # Obtencion del valor del elemento de la pila
        valor = pila[i].obtieneAtributo ('valor')

        # Si coinciden
        if (valor == cadena):
            return 1

    return 0

# *************************************************************************
    
# Funcion que devuelve un operador que incluya en sus postcondiciones la
# precondicion especificada y que no este descartado
def buscaOperador (precond, listaOperadores, descartes):

    # Obtencion del tamano de la lista de operadores
    tamano = len (listaOperadores)

    # Busqueda por la lista
    for i in range (tamano):

        # Obtencion de la lista de postcondiciones
        listaPost = listaOperadores[i].obtienePost ()
        
        # Comprobacion de la precond en la lista de postcondiciones
        incluido = estaIncluido (precond, listaPost)
        
        # Si esta la precondicion incluida
        if (incluido == 1):

            # Obtencion del nombre del operador
            nombreOperador = listaOperadores[i].obtieneNombre ()

            # Comprobacion del operador en descartes
            incluido = estaIncluido (nombreOperador, descartes)

            # Si no esta incluido
            if (incluido == 0):
                return listaOperadores[i]

    return ''

# *************************************************************************

# Funcion que elimina elementos de la pila hasta llegar a la accion
# especificada
def eliminaHastaAccion (pila, accion):

    # Obtencion del tamano de la pila
    tamano = len (pila)

    # Inicializacion de parametros
    contador = tamano - 1
    valor = ''
    
    # Bucle de eliminacion
    while (valor != accion):
        valor = pila[contador].obtieneAtributo ('valor')
        pila.pop (contador)
        contador = contador - 1
                    
# *************************************************************************

# Funcion que devuelve 1 si la precondicion especificada se cumple a partir de
# las listas del mundo dadas
# En caso contrario devuelve 0
def compruebaPrecond (precond, listaMundo, listaEdificios, listaObjetos,
                      listaP, indiceP, listaCasillas):

    # Precondicion = tieneCercaComida
    if (precond == 'tieneCercaComida'):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Comprobacion de comida cerca
        indiceO = obtieneObjetoCerca (posx, posy, 1, listaObjetos,
                                      listaP, indiceP)
        if (indiceO != -1):
            return 1       
        else:
            return 0

    # Precondicion = tieneCercaAgua
    elif (precond == 'tieneCercaAgua'):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Comprobacion de agua cerca
        indiceC = obtieneCasillaCerca (posx, posy, 3, listaCasillas,
                                       listaP, indiceP)                
        if (indiceC != -1):
            return 1
        else:
            return 0
        
    # Precondicion = tieneCercaPosadera
    elif (precond == 'tieneCercaPosadera'):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')
        
        # Comprobacion de posadera cerca
        indiceO = obtieneObjetoCerca (posx, posy, 21, listaObjetos,
                                      listaP, indiceP)
        if (indiceO != -1):
            return 1
        else:
            return 0
        
    # Precondicion = tieneCercaBibliotecaria
    elif (precond == 'tieneCercaBibliotecaria'):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')
        
        # Comprobacion de bibliotecaria cerca
        indiceO = obtieneObjetoCerca (posx, posy, 18, listaObjetos,
                                      listaP, indiceP)
        if (indiceO != -1):
            return 1
        else:
            return 0
        
    # Precondicion = tieneCercaVendedorArmas, tieneCercaVendedorEscudos,
    # tieneCercaVendedorArmaduras
    elif ((precond == 'tieneCercaVendedorArmas') or
          (precond == 'tieneCercaVendedorEscudos') or
          (precond == 'tieneCercaVendedorArmaduras')):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')
        
        # Comprobacion de vendedor cerca
        indiceO = obtieneObjetoCerca (posx, posy, 25, listaObjetos,
                                      listaP, indiceP)
        if (indiceO != -1):
            return 1
        else:
            return 0
        
    # Precondicion = tieneCercaPrisionero
    elif (precond == 'tieneCercaPrisionero'):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Comprobacion de prisionero cerca
        indiceO = obtieneObjetoCerca (posx, posy, 9, listaObjetos,
                                      listaP, indiceP)
        if (indiceO != -1):
            return 1
        else:
            return 0
        
    # Precondicion = tieneCercaCofre
    elif (precond == 'tieneCercaCofre'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Comprobacion de cofre cerca
        indiceO = obtieneObjetoCerca (posx, posy, 3, listaObjetos,
                                      listaP, indiceP)        
        if (indiceO != -1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaBruja
    elif (precond == 'tieneCercaBruja'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Comprobacion de bruja cerca
        indiceO = obtieneObjetoCerca (posx, posy, 4, listaObjetos,
                                      listaP, indiceP)
        if (indiceO != -1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaPersonaje
    elif (precond == 'tieneCercaPersonaje'):

        # Obtencion de las coordenadas del personaje activo
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')
        
        # Comprobacion de personaje cerca
        indiceP1 = obtienePersonajeCerca (posx, posy, listaP)            
        if (indiceP1 != -1):
            return 1        
        else:
            return 0

    # Precondicion = tieneCercaCastillo
    elif (precond == 'tieneCercaCastillo'):
        
        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy') + 1

        # Comprobacion del castillo
        coincide = hayEdificioCerca (posx, posy, 0, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaPosada
    elif (precond == 'tieneCercaPosada'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy') + 1

        # Comprobacion de la posada
        coincide = hayEdificioCerca (posx, posy, 1, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaBiblioteca
    elif (precond == 'tieneCercaBiblioteca'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy') + 1

        # Comprobacion de la biblioteca
        coincide = hayEdificioCerca (posx, posy, 2, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaArmas
    elif (precond == 'tieneCercaArmas'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy') + 1
        
        # Comprobacion de la tienda de armas
        coincide = hayEdificioCerca (posx, posy, 3, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaEscudos
    elif (precond == 'tieneCercaEscudos'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy') + 1
        
        # Comprobacion de la tienda de escudos
        coincide = hayEdificioCerca (posx, posy, 4, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneCercaArmaduras
    elif (precond == 'tieneCercaArmaduras'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy') + 1
        
        # Comprobacion de la tienda de armaduras
        coincide = hayEdificioCerca (posx, posy, 5, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = estaSalida
    elif (precond == 'estaSalida'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')

        # Comprobacion de la salida
        sal = coincideSalida (posx, posy, edif, listaEdificios, listaMundo)
        if (sal == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosComida
    elif (precond == 'tieneLejosComida'):

        # Comprobacion de comida lejos
        indiceO = hayObjetoLejos (1, listaObjetos, listaP, indiceP)
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosAgua
    elif (precond == 'tieneLejosAgua'):

        # Comprobacion de agua lejos
        indiceC = hayCasillaLejos (3, listaCasillas, listaP)
        if (indiceC == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosPosadera
    elif (precond == 'tieneLejosPosadera'):

        # Comprobacion de posadera lejos
        indiceO = hayObjetoLejos (21, listaObjetos, listaP, indiceP)
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosBibliotecaria
    elif (precond == 'tieneLejosBibliotecaria'):

        # Comprobacion de bibliotecaria lejos
        indiceO = hayObjetoLejos (18, listaObjetos, listaP, indiceP)
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosVendedorArmas, tieneLejosVendedorEscudos,
    # tieneLejosVendedorArmaduras
    elif ((precond == 'tieneLejosVendedorArmas') or
          (precond == 'tieneLejosVendedorEscudos') or
          (precond == 'tieneLejosVendedorArmaduras')):

        # Comprobacion de vendedor lejos
        indiceO = hayObjetoLejos (25, listaObjetos, listaP, indiceP)
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosPrisionero
    elif (precond == 'tieneLejosPrisionero'):

        # Comprobacion de prisionero lejos
        indiceO = hayObjetoLejos (9, listaObjetos, listaP, indiceP)
        if (indiceO == 1):
            return 1
        else:
            return 0
        
    # Precondicion = tieneLejosCofre
    elif (precond == 'tieneLejosCofre'):

        # Comprobacion de cofre lejos
        indiceO = hayObjetoLejos (3, listaObjetos, listaP, indiceP)        
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosBruja
    elif (precond == 'tieneLejosBruja'):

        # Comprobacion de bruja lejos
        indiceO = hayObjetoLejos (4, listaObjetos, listaP, indiceP)            
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosPersonaje
    elif (precond == 'tieneLejosPersonaje'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Comprobacion de personaje cerca
        indiceP1 = obtienePersonajeCerca (posx, posy, listaP)
        
        # Comprobacion de personaje lejos
        if ((len (listaP) > 1) and (indiceP1 == -1)):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosPortal
    elif (precond == 'tieneLejosPortal'):

        # Comprobacion de portal lejos
        indiceO = hayObjetoLejos (7, listaObjetos, listaP, indiceP)
        if (indiceO == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosCastillo
    elif (precond == 'tieneLejosCastillo'):

        # Comprobacion del castillo
        coincide = hayEdificioLejos (0, listaEdificios, listaP, indiceP)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosPosada
    elif (precond == 'tieneLejosPosada'):

        # Comprobacion de la posada
        coincide = hayEdificioLejos (1, listaEdificios, listaP, indiceP)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosBiblioteca
    elif (precond == 'tieneLejosBiblioteca'):

        # Comprobacion de la biblioteca
        coincide = hayEdificioLejos (2, listaEdificios, listaP, indiceP)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosArmas
    elif (precond == 'tieneLejosArmas'):

        # Comprobacion de la tienda de armas
        coincide = hayEdificioLejos (3, listaEdificios, listaP, indiceP)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosEscudos
    elif (precond == 'tieneLejosEscudos'):

        # Comprobacion de la tienda de escudos
        coincide = hayEdificioLejos (4, listaEdificios, listaP, indiceP)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = tieneLejosArmaduras
    elif (precond == 'tieneLejosArmaduras'):

        # Comprobacion de la tienda de armaduras
        coincide = hayEdificioLejos (5, listaEdificios, listaP, indiceP)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = salidaLibre
    elif (precond == 'salidaLibre'):

        # Obtencion del edificio donde se encuentra el personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')

        # Obtencion del tipo de edificio
        tipoEdificio = obtieneTipoEdificio (edif, listaEdificios)

        # Obtencion del limite inferior del edificio
        if (tipoEdificio == 0):
            inf = listaMundo[2]
        else:
            inf = listaMundo[4]
            
        # Comprobacion de salida libre
        indiceP1 = coincidePersonaje (0, inf, listaP)
        if (indiceP1 == -1):
            return 1
        else:
            return 0

    # Precondicion = estaExterior
    elif (precond == 'estaExterior'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Comprobacion del edif
        if (edif == -1):
            return 1
        else:
            return 0

    # Precondicion = estaInterior
    elif (precond == 'estaInterior'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')

        # Comprobacion del edif
        if (edif != -1):
            return 1
        else:
            return 0

    # Precondicion = estaCastillo
    elif (precond == 'estaCastillo'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Comprobacion del castillo
        coincide = coincideTipoEdificio (edif, 0, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = estaPosada
    elif (precond == 'estaPosada'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')

        # Comprobacion de la posada
        coincide = coincideTipoEdificio (edif, 1, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = estaBiblioteca
    elif (precond == 'estaBiblioteca'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Comprobacion de la biblioteca
        coincide = coincideTipoEdificio (edif, 2, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0
    
    # Precondicion = estaArmas
    elif (precond == 'estaArmas'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Comprobacion de la tienda de armas
        coincide = coincideTipoEdificio (edif, 3, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = estaEscudos
    elif (precond == 'estaEscudos'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Comprobacion de la tienda de escudos
        coincide = coincideTipoEdificio (edif, 4, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = estaArmaduras
    elif (precond == 'estaArmaduras'):

        # Obtencion del edif del personaje
        edif = listaP[indiceP].obtieneAtributo ('edif')
        
        # Comprobacion de la tienda de escudos
        coincide = coincideTipoEdificio (edif, 5, listaEdificios)
        if (coincide == 1):
            return 1
        else:
            return 0

    # Precondicion = estaPortal
    elif (precond == 'estaPortal'):

        # Obtencion de las coordenadas del personaje
        posx = listaP[indiceP].obtieneAtributo ('posx')
        posy = listaP[indiceP].obtieneAtributo ('posy')

        # Obtencion del indice del objeto coincidente
        indiceO = coincideObjeto (posx, posy, listaObjetos)

        # Si hay un objeto coincidente
        if (indiceO != -1):

            # Obtencion del tipo del objeto
            tipo = listaObjetos[indiceO].obtieneAtributo ('tipo')
        
            # Si es de tipo portal
            if (tipo == 7):
        
                # Obtencion de las coordenadas del objeto
                x = listaObjetos[indiceO].obtieneAtributo ('posx')
                y = listaObjetos[indiceO].obtieneAtributo ('posy')
			    
                # Si la posicion coincide con el centro
                if ((posx == x + 1) and (posy == y)):
                    return 1

                # Si no coincide con el centro
                else:
                    return 0
                
            # Si no es de tipo portal
            else:
                return 0

        # Si no hay ningun objeto coincidente
        else:
            return 0
    
    # Precondicion = tieneDinero
    elif (precond == 'tieneDinero'):

        # Obtencion del dinero del personaje
        monedas = listaP[indiceP].obtieneEqu (3)
        
        # Comprobacion del dinero
        if (monedas >= 50):
            return 1
        else:
            return 0

    # Precondicion = tieneDineroBruja
    elif (precond == 'tieneDineroBruja'):

        # Obtencion del dinero del personaje
        monedas = listaP[indiceP].obtieneEqu (3)
        
        # Obtencion del numero de entrenamientos del personaje
        entr = listaP[indiceP].obtieneAtributo ('entr')
        
        # Comprobacion del dinero
        if (monedas >= (entr + 1) * 50):
            return 1
        else:
            return 0

    # Precondicion = tieneDineroArmas
    elif (precond == 'tieneDineroArmas'):

        # Obtencion del dinero del personaje
        monedas = listaP[indiceP].obtieneEqu (3)

        # Si no tiene suficiente dinero
        if (monedas < 100):
            return 0
        
        # Obtencion del arma del personaje
        arma = listaP[indiceP].obtieneEqu (1)
        
        # Obtencion del tipo del item a comprar
        tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios, 3,
                                    listaObjetos)        
        # Comprobacion de item
        if (arma >= tipo):
            return 0
        else:
            return 1
        
    # Precondicion = tieneDineroEscudos
    elif (precond == 'tieneDineroEscudos'):
        
        # Obtencion del dinero del personaje
        monedas = listaP[indiceP].obtieneEqu (3)
        
        # Si no tiene suficiente dinero
        if (monedas < 100):
            return 0
        
        # Obtencion del escudo del personaje
        escudo = listaP[indiceP].obtieneEqu (0)
        
        # Obtencion del tipo del item a comprar
        tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios, 4,
                                    listaObjetos)        
        # Comprobacion de item
        if (escudo >= tipo):
            return 0
        else:
            return 1
        
    # Precondicion = tieneDineroArmaduras
    elif (precond == 'tieneDineroArmaduras'):

        # Obtencion del dinero del personaje
        monedas = listaP[indiceP].obtieneEqu (3)
        
        # Si no tiene suficiente dinero
        if (monedas < 100):
            return 0
        
        # Obtencion de la armadura del personaje
        armadura = listaP[indiceP].obtieneEqu (2)
        
        # Obtencion del tipo del item a comprar
        tipo = obtieneItemAComprar (listaP, indiceP, listaEdificios, 5,
                                    listaObjetos)        
        # Comprobacion de item
        if (armadura >= tipo):
            return 0
        else:
            return 1
        
    # Precondicion = tienePocionObj
    elif (precond == 'tienePocionObj'):

        # Obtencion del objetivo del personaje
        obj = listaP[indiceP].obtieneAtributo ('obj')

        # Obtencion de la pocion del personaje
        pocion = listaP[indiceP].obtieneEqu (5)

        # Comprobacion de pocion objetivo
        if (obj == pocion):
            return 1
        else:
            return 0

    # Precondicion = tieneObjetivo
    elif (precond == 'tieneObjetivo'):

        # Obtencion del objetivo del personaje
        obj = listaP[indiceP].obtieneAtributo ('obj')
        
        # Comprobacion del objetivo
        if (obj != 0):
            return 1
        else:
            return 0

    # Precondicion = tieneLlave
    elif (precond == 'tieneLlave'):

        # Obtencion de la llave del personaje
        llav = listaP[indiceP].obtieneEqu (4)
        
        # Comprobacion de la llave
        if (llav == 1):
            return 1
        else:
            return 0
                
    return 0

# *************************************************************************

# Funcion que realiza una planificacion strips en base a la informacion
# especificada devolviendo la accion resultante del plan
def strips (postObj, listaOperadores, listaMundo, listaEdificios,
            listaObjetos, listaP, indiceP, listaCasillas):

    # Inicializacion de las listas de Strips
    pila = []
    estado = []
    acciones = []
    descartes = []

    # Inicializacion de la accion del plan
    accion = ''
    
    # Insercion del objetivo en la pila de Strips
    unElemento = ElemStrips ()
    unElemento.reAsignaAtributo ('tipo', 0)
    unElemento.reAsignaAtributo ('valor', postObj)
    pila.append (unElemento)
    
    # Bucle Strips
    while (1):

        # Comprobacion de pila vacia
        if (len (pila) == 0):
            return accion
        
        # Obtencion del tope de la pila
        tope = pila [len (pila) - 1] 
        
        # Obtencion del tipo del tope
        tipo = tope.obtieneAtributo ('tipo')
        
        # Si el tope es de tipo operador
        if (tipo == 3):

            # Obtencion del valor del tope
            nombreOperador = tope.obtieneAtributo ('valor')
            
            # Volcado de las postcondiciones del operador en la lista estado
            insertaPostcondiciones (nombreOperador, listaOperadores, estado)

            # Eliminacion del tope
            pila.pop ()

        # Si el tope es una precondicion
        elif (tipo < 3):

            # Obtencion del valor del tope
            precond = tope.obtieneAtributo ('valor')

            # Si es la precondicion vacio 
            if (precond == 'vacio'):
                esVerdadero = 1

            # Si no es la precondicion vacio
            else:
                
                # Busqueda de la precondicion en la lista de estado
                incluido = estaIncluido (precond, estado)

                # Si no esta en la lista de estado
                if (incluido == 0):

                    # Comprobacion con el estado del mundo actual
                    esVerdadero = compruebaPrecond (precond, listaMundo,
                                                    listaEdificios,
                                                    listaObjetos,
                                                    listaP, indiceP,
                                                    listaCasillas)
                                                
            # Si la precondicion se cumple
            if ((incluido == 1) or (esVerdadero == 1)):
                
                # Si es una precondicion del operador objetivo
                if ((tipo == 1) and
                    ((accion == operadorObjetivo) or (accion == ''))):

                    # Obtencion de la ultima accion
                    accion = acciones [len (acciones) - 1]

                    # Comprobacion de solucion
                    if ((accion != '') and (accion != operadorObjetivo)):
                        return accion
                    
                # Eliminacion del tope
                pila.pop ()

            # Si no se cumple
            else:
                
                # Obtencion de un operador que enlace con la precondicion y
                # que no este descartado
                unOperador = buscaOperador(precond, listaOperadores, descartes)

                # Si hay un operador que enlaza
                if (unOperador != ''):

                    # Obtencion del nombre del operador
                    nombreOperador = unOperador.obtieneNombre ()
                    
                    # Si es el objetivo
                    if (tipo == 0):

                        # Asignacion del operador objetivo
                        operadorObjetivo = nombreOperador

                        # Asignacion del tipo de precondicion
                        tipoPrec = 1

                    # Si no es el objetivo
                    else:

                        # Asignacion del tipo de precondicion
                        tipoPrec = 2
                        
                    # Insercion del operador en la pila
                    unElemento = ElemStrips ()
                    unElemento.reAsignaAtributo ('tipo', 3)
                    unElemento.reAsignaAtributo ('valor', nombreOperador)
                    pila.append (unElemento)

                    # Insercion de las precondiciones en la pila
                    tamPrec = unOperador.obtieneNPrec ()
                    for i in range (tamPrec):
                        prec = unOperador.obtienePrecond (i)
                        unElemento = ElemStrips ()
                        unElemento.reAsignaAtributo ('tipo', tipoPrec)
                        unElemento.reAsignaAtributo ('valor', prec)
                        pila.append (unElemento)

                    # Insercion del operador en la lista de acciones
                    acciones.append (nombreOperador)

                # Si no enlaza ningun operador
                else:

                    # Comprobacion de no solucion                    
                    if (tope.obtieneAtributo ('valor') == postObj):
                        return ''

                    # Bucle de comprobacion de la ultima accion en la pila
                    incluido = 0
                    posicion = len (acciones) - 1
                    while (incluido == 0):
                        
                        # Obtencion de la ultima accion
                        ultima = acciones [posicion]

                        # Comprobacion de la accion
                        incluido = incluyeAccion (ultima, pila)

                        # Si no aparece se coge la accion anterior
                        if (incluido == 0):
                            posicion = posicion - 1

                    # Eliminacion de todos los elementos de la pila hasta
                    # la ultima accion
                    eliminaHastaAccion (pila, ultima)
                    
                    # Eliminacion en la lista de acciones
                    acciones.pop (posicion)
                    
                    # Insercion de la ultima accion en la lista de descartes
                    descartes.append (ultima)
                                        
# *************************************************************************

# Funcion que devuelve una accion a realizar por defecto
def seleccionaAccion (listaMundo, listaEdificios, listaObjetos, listaP,
                      indiceP, listaCasillas):

    # Obtencion de las coordenadas del personaje activo
    posx = listaP[indiceP].obtieneAtributo ('posx')
    posy = listaP[indiceP].obtieneAtributo ('posy')
        
    # Comprobacion de personaje cerca
    indiceP1 = obtienePersonajeCerca (posx, posy, listaP)            

    # Si hay un personaje cerca
    if (indiceP1 != -1):
        accion = 'Robar'

    # Si no hay ningun personaje cerca
    else:
        
        # Si hay un personaje lejos
        if (len (listaP) > 1):
            accion = 'MoverHaciaPersonaje'

        # Si no hay ningun personaje lejos
        else:

            # Obtencion del edificio donde se encuentra el personaje activo
            edif = listaP[indiceP].obtieneAtributo ('edif')

            # Si esta en un edificio
            if (edif != -1):
                
                # Comprobacion de la salida
                sal = coincideSalida (posx, posy, edif, listaEdificios,
                                      listaMundo)
                # Si esta en la salida
                if (sal == 1):
                    return 'Salir'

                # Si no esta en la salida
                else:
                    
                    # Obtencion del tipo de edificio
                    tipoEdificio = obtieneTipoEdificio (edif, listaEdificios)

                    # Obtencion del limite inferior del edificio
                    if (tipoEdificio == 0):
                        inf = listaMundo[2]
                    else:
                        inf = listaMundo[4]

                    # Comprobacion de salida libre
                    indiceP1 = coincidePersonaje (0, inf, listaP)
                    if (indiceP1 == -1):
                        return 'MoverHaciaSalida'

                    # Si la salida no esta libre
                    else:
                        accion = 'MoverHaciaPersonaje'

            # Si esta en el exterior            
            else:
                accion = 'MoverAleatorio'
    
    return accion

# *************************************************************************

# Funcion que toma una decision realizando un algoritmo de planificacion Strips
# Devuelve el objetivo
def tomaDecisionStrips (objetivoActual, listaOperadores, listaMundo,
                        listaEdificios, listaObjetos, listaP, indiceP,
                        listaCasillas, turno, sockCliente):
    
    # Obtencion del socket del cliente
    sock = listaP[indiceP].obtieneAtributo ('sock')
    
    # Si le toca el turno
    if (sock == turno):

        # Obtencion del objetivo
        objetivoActual = obtieneObjetivo (objetivoActual, listaEdificios,
                                          listaObjetos, listaP, indiceP,
                                          listaCasillas)
        
        # Si hay un objetivo
        if (objetivoActual != 0):
            
            # Obtencion de la postcondicion asociada al objetivo
            if (objetivoActual == 1):
                postObj = 'comido'
            
            elif (objetivoActual == 2):
                postObj = 'bebido'

            elif (objetivoActual == 3):
                postObj = 'descansado'

            elif (objetivoActual == 4):
                postObj = 'curado'
                
            elif (objetivoActual == 5):
                postObj = 'defendido'
                
            elif (objetivoActual == 6):
                postObj = 'incrementadasCarac'
                
            elif (objetivoActual == 7):
                postObj = 'incrementadosMH'
                
            elif (objetivoActual == 8):
                postObj = 'tieneArma'

            elif (objetivoActual == 9):
                postObj = 'tieneEscudo'

            elif (objetivoActual == 10):
                postObj = 'tieneArmadura'

        # Si no hay ningun objetivo
        else:
            postObj = ''
            
        # Impresion de las caracteristicas del personaje activo
        imprimeCaracteristicas (listaP, indiceP)
        
        # Si hay objetivo
        if (objetivoActual != 0):
            accion = strips (postObj, listaOperadores, listaMundo,
                             listaEdificios, listaObjetos, listaP, indiceP,
                             listaCasillas)

            # Impresion de la accion resultante
            if (accion != ''):
                print 'objetivo:', postObj, 'accion planificada:', accion
                                
            # Si no es posible ninguna accion
            if (accion == ''):
                
                # Se selecciona una accion por defecto
                accion = seleccionaAccion (listaMundo, listaEdificios,
                                           listaObjetos, listaP, indiceP,
                                           listaCasillas)

                # Impresion de la accion por defecto
                print 'objetivo:', postObj, 'accion por defecto:', accion
                
         # Si no hay objetivo
        else:             
             # Se selecciona una accion por defecto
             accion = seleccionaAccion (listaMundo, listaEdificios,
                                        listaObjetos, listaP, indiceP,
                                        listaCasillas)

             # Impresion de la accion por defecto
             print 'objetivo:', postObj, 'accion por defecto:', accion
             
        # Realizacion de la accion correspondiente
        realizaAccion (accion, listaMundo, listaEdificios, listaObjetos,
                       listaP, indiceP, listaCasillas, sockCliente)

    # Si no le toca el turno
    else:
        enviaEnteroAServidor (sockCliente, 0)

    return objetivoActual

# *************************************************************************

# Funcion que imprime en la shell las caracteristicas del personaje activo
def imprimeCaracteristicas (listaP, indiceP):

    # Obtencion de los atributos de salud
    pg = listaP[indiceP].obtieneAtributo ('pg')
    ene = listaP[indiceP].obtieneAtributo ('ene')
    ham = listaP[indiceP].obtieneAtributo ('ham')
    sed = listaP[indiceP].obtieneAtributo ('sed')
    maxpg = listaP[indiceP].obtieneAtributo ('maxpg')
    maxene = listaP[indiceP].obtieneAtributo ('maxene')
    maxham = listaP[indiceP].obtieneAtributo ('maxham')
    maxsed = listaP[indiceP].obtieneAtributo ('maxsed')
    
    # Obtencion de las habilidades
    fue = listaP[indiceP].obtieneAtributo ('fue')
    con = listaP[indiceP].obtieneAtributo ('con')
    des = listaP[indiceP].obtieneAtributo ('des')
    mh1 = listaP[indiceP].obtieneAtributo ('mh1')
    mh2 = listaP[indiceP].obtieneAtributo ('mh2')
    mmr = listaP[indiceP].obtieneAtributo ('mmr')
    estu = listaP[indiceP].obtieneAtributo ('estu')
    entr = listaP[indiceP].obtieneAtributo ('entr')
    obj = listaP[indiceP].obtieneAtributo ('obj')
    nturnos = listaP[indiceP].obtieneAtributo ('nturnos')

    # Obtencion del equipo
    escudo = listaP[indiceP].obtieneEqu (0)
    if (escudo == -1):
        escudo = ''
        
    arma = listaP[indiceP].obtieneEqu (1)
    if (arma == -1):
        arma = ''
        
    armadura = listaP[indiceP].obtieneEqu (2)
    if (armadura == -1):
        armadura = ''
        
    monedas = listaP[indiceP].obtieneEqu (3)
    llave = listaP[indiceP].obtieneEqu (4)
    if (llave == -1):
        llave = ''
        
    pocion = listaP[indiceP].obtieneEqu (5)       	
    if (pocion == -1):
        pocion = ''
        
    # Obtencion de las coordenadas
    posx = listaP[indiceP].obtieneAtributo ('posx')
    posy = listaP[indiceP].obtieneAtributo ('posy')

    # Impresion de los atributos de salud
    print '\nP.Golpe:', pg, '/', maxpg
    print 'Energia:', ene, '/', maxene
    print 'Hambre:', ham, '/', maxham
    print 'Sed:', sed, '/', maxsed

    # Impresion de las habilidades
    print '\nFuerza:', fue
    print 'Constitucion:', con
    print 'Destreza:', des
    print 'Sigilo:', mh1
    print 'Percepcion:', mh2
    print 'N.Estudio:', estu
    print 'N.Entrenamiento:', entr
    print 'Mision actual:', obj
    print 'M.Reaccion:', mmr
    print 'N.Turnos:', nturnos

    # Impresion del equipo
    print '\nEscudo:', escudo
    print 'Arma:', arma
    print 'Armadura:', armadura
    print 'Monedas:', monedas
    print 'Llave:', llave
    print 'Pocion:', pocion

    # Impresion de las coordenadas
    print '\nposx:', posx, 'posy:', posy
    
# *************************************************************************
