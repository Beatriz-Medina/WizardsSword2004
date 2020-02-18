#! /usr/bin/env python

# **************************************************************************
#			  creaMundo.py	-  description
#   	                       ------------------
# Wizard's Sword
# desarrollado por	: (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


from random import *
from elemento import *
from funciones import *

# Inicializacion de parametros
mundoInf = -50
mundoSup = 50

castilInf = -10
castilSup = 10

casaInf = -3
casaSup = 3

nEdificios = 18
listaEdificios = []

nObjetos = 747 
listaObjetos = []

# *************************************************************************

print "Creando los edificios..."

# Creacion del fichero de edificios
ficheroEdificios = open ("edificios.dat", "w")

# Insercion de edificios en el fichero
for i in range (nEdificios):

    # Asignacion de atributos del edificio
    id = i
    
    # Asignacion del tipo de edificio
    if ((id == 0) or (id == 6) or (id == 12)):
        tipo = 0

    elif ((id == 1) or (id == 7) or (id == 13)):
        tipo = 1

    elif ((id == 2) or (id == 8) or (id == 14)):
        tipo = 2

    elif ((id == 3) or (id == 9) or (id == 15)):
        tipo = 3

    elif ((id == 4) or (id == 10) or (id == 16)):
        tipo = 4

    elif ((id == 5) or (id == 11) or (id == 17)):
        tipo = 5

    # Asignacion de la longitud y tamano (x,y) del edificio segun el tipo
    if (tipo == 0):
        longx = casilx = 3
        longy = casily = 3
        llav = 1
    else:
        longx = casilx = 2
        longy = casily = 2
        llav = 0
        
    # Generacion de una posicion (x,y) aleatoria para el edificio  
    posx = randint (mundoInf, mundoSup - 1)
    posy = randint (mundoInf, mundoSup - 1)

    # Creacion de un elemento edificio
    unEdificio = Elemento (posx, posy, casilx, casily, -1)

    # Comprobacion de que el edificio no este dentro de otro edificio ni
    # sobrepase los limites
    while ((dentro (unEdificio, listaEdificios, 1) != -1) or
           (dentroLimites (unEdificio, mundoInf, mundoSup) == 0)):

           # Generacion de otra posicion aleatoria
           posx = randint (mundoInf, mundoSup - 1)
           posy = randint (mundoInf, mundoSup - 1)

           # Creacion de otro elemento edificio
           unEdificio = Elemento (posx, posy, casilx, casily, -1)
           
    # Escritura de los atributos en el fichero
    ficheroEdificios.write ("%d " %id)
    ficheroEdificios.write ("%d " %tipo)
    ficheroEdificios.write ("%d " %llav)
    ficheroEdificios.write ("%d " %posx)
    ficheroEdificios.write ("%d " %posy)
    ficheroEdificios.write ("%d " %longx)
    ficheroEdificios.write ("%d " %longy)
    ficheroEdificios.write ("%d " %casilx)
    ficheroEdificios.write ("%d\n" %casily)

    # Insercion del elemento edificio en la lista de edificios
    listaEdificios.append (unEdificio)

# Cierre del fichero de edificios
ficheroEdificios.close ()

print "OK"

# *************************************************************************

print "Creando los objetos..."

# Creacion del fichero de objetos
ficheroObjetos = open ("objetos.dat", "w")

# Insercion de objetos en el fichero
for i in range (nObjetos):
    
    # Asignacion de atributos del objeto
    id = i
    
    # Asignacion del tipo del objeto
    # Arbol (Total: 300)
    if (id == 0):
        tipo = 0     
        longx = 3
        longy = 3
        casilx = 2
        casily = 1
        edif = -1
        equ = -1

    # Setas (Total: 150)
    elif (id == 300):
        tipo = 1    
        longx = casilx = 1
        longy = casily =1
        edif = -1
        equ = -1

    # Miel (Total: 50)
    elif (id == 450):
        tipo = 2    
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = -1

    # Cofre exterior (Total: 35)
    # Cofre exterior llave (Total: 3)
    elif (id == 500):
        tipo = 3    
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 0
                
    # Cofre exterior monedas (Total: 26)
    elif (id == 503):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 11
        
    # Cofre exterior pocion1 (Total: 1)
    elif (id == 529):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 1
        
    # Cofre exterior pocion2 (Total: 1)
    elif (id == 530):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 2
        
    # Cofre exterior pocion3 (Total: 1)
    elif (id == 531):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 3
        
    # Cofre exterior pocion4 (Total: 1)
    elif (id == 532):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 4
        
    # Cofre exterior pocion5 (Total: 1)
    elif (id == 533):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 5
        
    # Cofre exterior pocion6 (Total: 1)
    elif (id == 534):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = 6
        
    # Cofre castillo1 (Total: 5)
    # Cofre castillo1 pocion7 (Total: 1)
    elif (id == 535):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = 7
        
    # Cofre castillo1 pocion8 (Total: 1)
    elif (id == 536):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = 8
        
    # Cofre castillo1 monedas (Total: 3)
    elif (id == 537):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = 11
        
    # Cofre castillo2 (Total: 5)
    # Cofre castillo2 pocion9 (Total: 1) 
    elif (id == 540):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = 9
        
    # Cofre castillo2 monedas (Total: 4) 
    elif (id == 541):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = 11
        
    # Cofre castillo3 (Total: 5)
    # Cofre castillo3 pocion10 (Total: 1)
    elif (id == 545):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = 10
        
    # Cofre castillo3 monedas (Total: 4)
    elif (id == 546):
        tipo = 3
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = 11
        
    # Bruja (Total: 5)   
    elif (id == 550):
        tipo = 4
        longx = casilx = 1
        longy = casily = 1
        edif = -1
        equ = -1

    # Candelabro castillo1 (Total: 10)
    elif (id == 555):
        tipo = 5
        longx = 2
        longy = 2
        casilx = 1
        casily = 1
        edif = 0
        equ = -1
        
    # Candelabro castillo2 (Total: 10)
    elif (id == 565):
        tipo = 5     
        longx = 2
        longy = 2
        casilx = 1
        casily = 1
        edif = 6
        equ = -1
        
    # Candelabro castillo3 (Total: 10)
    elif (id == 575):
        tipo = 5
        longx = 2
        longy = 2
        casilx = 1
        casily = 1
        edif = 12
        equ = -1
        
    # Huesos castillo1 (Total: 5)
    elif (id == 585):
        tipo = 6
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = -1
        
    # Huesos castillo2 (Total: 5)
    elif (id == 590):
        tipo = 6
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = -1
        
    # Huesos castillo3 (Total: 5)
    elif (id == 595):
        tipo = 6
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = -1
        
    # Portal magico castillo1 (Total: 2)
    elif (id == 600):
        tipo = 7
        longx = 3
        longy = 3
        casilx = 3
        casily = 1
        edif = 0
        equ = -1

    # Portal magico castillo2 (Total: 2)
    elif (id == 602):
        tipo = 7
        longx = 3
        longy = 3
        casilx = 3
        casily = 1
        edif = 6
        equ = -1
        
    # Portal magico castillo3 (Total: 2)
    elif (id == 604):
        tipo = 7
        longx = 3
        longy = 3
        casilx = 3
        casily = 1
        edif = 12
        equ = -1
        
    # Estatua castillo1 (Total: 3)
    elif (id == 606):
        tipo = 8
        longx = 2
        longy = 2
        casilx = 1
        casily = 1
        edif = 0
        equ = -1
        
    # Estatua castillo2 (Total: 3)
    elif (id == 609):
        tipo = 8
        longx = 2
        longy = 2
        casilx = 1
        casily = 1
        edif = 6
        equ = -1
        
    # Estatua castillo3 (Total: 3)
    elif (id == 612):
        tipo = 8
        longx = 2
        longy = 2
        casilx = 1
        casily = 1
        edif = 12
        equ = -1        

    # Esclava1 castillo1 (Total: 1)
    elif (id == 615):
        tipo = 9
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = -1
        
    # Esclava1 castillo2 (Total: 1)
    elif (id == 616):
        tipo = 9
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = -1
        
    # Esclava1 castillo3 (Total: 1)
    elif (id == 617):
        tipo = 9
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = -1
        
    # Esclava2 castillo1 (Total: 1)
    elif (id == 618):
        tipo = 11
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = -1
        
    # Esclava2 castillo2 (Total: 1)
    elif (id == 619):
        tipo = 11
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = -1
        
    # Esclava2 castillo3 (Total: 1)
    elif (id == 620):
        tipo = 11
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = -1
        
    # Esclavo1 castillo1 (Total: 1)
    elif (id == 621):
        tipo = 13
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = -1
        
    # Esclavo1 castillo2 (Total: 1)
    elif (id == 622):
        tipo = 13
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = -1
        
    # Esclavo1 castillo1 (Total: 1)
    elif (id == 623):
        tipo = 13
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = -1
        
    # Esclavo2 castillo1 (Total: 1)
    elif (id == 624):
        tipo = 15
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = -1
        
    # Esclavo2 castillo2 (Total: 1)
    elif (id == 625):
        tipo = 15
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = -1
        
    # Esclavo2 castillo3 (Total: 1)
    elif (id == 626):
        tipo = 15
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = -1

    # Pinchos castillo1 (Total: 10)
    elif (id == 627):
        tipo = 17
        longx = casilx = 1
        longy = casily = 1
        edif = 0
        equ = -1

    # Pinchos castillo2 (Total: 10)
    elif (id == 637):
        tipo = 17
        longx = casilx = 1
        longy = casily = 1
        edif = 6
        equ = -1

    # Pinchos castillo3 (Total: 10)
    elif (id == 647):
        tipo = 17
        longx = casilx = 1
        longy = casily = 1
        edif = 12
        equ = -1

    # Bibliotecaria biblioteca1 (Total: 1)
    elif (id == 657):
        tipo = 18
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 2
        equ = -1

    # Bibliotecaria biblioteca2 (Total: 1)
    elif (id == 658):
        tipo = 18
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 8
        equ = -1
        
    # Bibliotecaria biblioteca3 (Total: 1)
    elif (id == 659):
        tipo = 18
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 14
        equ = -1
        
    # Mesa posada1 (Total: 1)
    elif (id == 660):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 1
        equ = -1

    # Mesa posada2 (Total: 1)
    elif (id == 661):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 7
        equ = -1

    # Mesa posada3 (Total: 1)
    elif (id == 662):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 13
        equ = -1

    # Mesa biblioteca1 (Total: 1)
    elif (id == 663):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 2
        equ = -1
        
    # Mesa biblioteca2 (Total: 1)
    elif (id == 664):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 8
        equ = -1

    # Mesa biblioteca3 (Total: 1)
    elif (id == 665):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 14
        equ = -1

    # Mesa tienda armas1 (Total: 1)
    elif (id == 666):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1

    # Mesa tienda armas2 (Total: 1)
    elif (id == 667):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1

    # Mesa tienda armas3 (Total: 1)
    elif (id == 668):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Mesa tienda escudos1 (Total: 1)
    elif (id == 669):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 4
        equ = -1
        
    # Mesa tienda escudos2 (Total: 1)
    elif (id == 670):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 10
        equ = -1
        
    # Mesa tienda escudos3 (Total: 1)
    elif (id == 671):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 16
        equ = -1
        
    # Mesa tienda armaduras1 (Total: 1)
    elif (id == 672):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Mesa tienda armaduras2 (Total: 1)
    elif (id == 673):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1

    # Mesa tienda armaduras3 (Total: 1)
    elif (id == 674):
        tipo = 19
        posx = -2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1
        
    # Biblioteca biblioteca1 (Total: 1)
    elif (id == 675):
        tipo = 20    
        posx = -1
        posy = 1
        longx = 2
        longy = 2
        casilx = 2
        casily = 1
        edif = 2
        equ = -1
        
    # Biblioteca biblioteca2 (Total: 1)
    elif (id == 676):
        tipo = 20    
        posx = -1
        posy = 1
        longx = 2
        longy = 2
        casilx = 2
        casily = 1
        edif = 8
        equ = -1
        
    # Biblioteca biblioteca3 (Total: 1)
    elif (id == 677):
        tipo = 20    
        posx = -1
        posy = 1
        longx = 2
        longy = 2
        casilx = 2
        casily = 1
        edif = 14
        equ = -1
        
    # Biblioteca biblioteca1 (Total: 1)
    elif (id == 678):
        tipo = 20
        posx = 1
        posy = 1
        longx = 2
        longy = 2
        casilx = 2
        casily = 1
        edif = 2
        equ = -1

    # Biblioteca biblioteca2 (Total: 1)
    elif (id == 679):
        tipo = 20
        posx = 1
        posy = 1
        longx = 2
        longy = 2
        casilx = 2
        casily = 1
        edif = 8
        equ = -1
        
    # Biblioteca biblioteca3 (Total: 1)
    elif (id == 680):
        tipo = 20
        posx = 1
        posy = 1
        longx = 2
        longy = 2
        casilx = 2
        casily = 1
        edif = 14
        equ = -1
        
    # Posadera posada1 (Total: 1)
    elif (id == 681):
        tipo = 21
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 1
        equ = -1

    # Posadera posada2 (Total: 1)
    elif (id == 682):
        tipo = 21    
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 7
        equ = -1
        
    # Posadera posada3 (Total: 1)
    elif (id == 683):
        tipo = 21    
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 13
        equ = -1
        
    # Cama posada1 (Total: 1)
    elif (id == 684):
        tipo = 22
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 1
        equ = -1
        
    # Cama posada2 (Total: 1)
    elif (id == 685):
        tipo = 22
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 7
        equ = -1
        
    # Cama posada3 (Total: 1)
    elif (id == 686):
        tipo = 22
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 13
        equ = -1
        
    # Vela posada1 (Total: 1)
    elif (id == 687):
        tipo = 23
        posx = 1
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 1
        equ = -1
        
    # Vela posada2 (Total: 1)
    elif (id == 688):
        tipo = 23
        posx = 1
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 7
        equ = -1
        
    # Vela posada3 (Total: 1)
    elif (id == 689):
        tipo = 23
        posx = 1
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 13
        equ = -1

    # Vela biblioteca1 (Total: 1)
    elif (id == 690):
        tipo = 23
        posx = 2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 2
        equ = -1
        
    # Vela biblioteca2 (Total: 1)
    elif (id == 691):
        tipo = 23
        posx = 2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 8
        equ = -1
        
    # Vela biblioteca3 (Total: 1)
    elif (id == 692):
        tipo = 23
        posx = 2
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 14
        equ = -1
        
    # Escoba posada1 (Total: 1)
    elif (id == 693):
        tipo = 24
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 1                
        equ = -1
        
    # Escoba posada2 (Total: 1)
    elif (id == 694):
        tipo = 24
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 7                
        equ = -1
        
    # Escoba posada3 (Total: 1)
    elif (id == 695):
        tipo = 24
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 13                
        equ = -1
        
    # Armero tienda armas1 (Total: 1)
    elif (id == 696):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1
        
    # Armero tienda armas2 (Total: 1)
    elif (id == 697):
        tipo = 25    
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1
        
    # Armero tienda armas3 (Total: 1)
    elif (id == 698):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Armero tienda escudos1 (Total: 1)
    elif (id == 699):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 4
        equ = -1
        
    # Armero tienda escudos2 (Total: 1)
    elif (id == 700):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 10
        equ = -1
        
    # Armero tienda escudos3 (Total: 1)
    elif (id == 701):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 16
        equ = -1
        
    # Armero tienda armaduras1 (Total: 1)
    elif (id == 702):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Armero tienda armaduras2 (Total: 1)
    elif (id == 703):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1
        
    # Armero tienda armaduras3 (Total: 1)
    elif (id == 704):
        tipo = 25
        posx = -3
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1
        
    # Estatua de armadura tienda armas1 (Total: 1)
    elif (id == 705):
        tipo = 26
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1
        
    # Estatua de armadura tienda armas2 (Total: 1)
    elif (id == 706):
        tipo = 26    
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1
        
    # Estatua de armadura tienda armas3 (Total: 1)
    elif (id == 707):
        tipo = 26
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Estatua de armadura tienda escudos1 (Total: 1)
    elif (id == 708):
        tipo = 26
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 4
        equ = -1
        
    # Estatua de armadura tienda escudos2 (Total: 1)
    elif (id == 709):
        tipo = 26
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 10
        equ = -1
        
    # Estatua de armadura tienda escudos3 (Total: 1)
    elif (id == 710):
        tipo = 26
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 16
        equ = -1
        
    # Espada1 tienda armas1 (Total: 1)
    elif (id == 711):
        tipo = 27
        posx = 0
        posy = -1
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1
        
    # Espada1 tienda armas2 (Total: 1)
    elif (id == 712):
        tipo = 27     
        posx = 0
        posy = -1
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1
        
    # Espada1 tienda armas3 (Total: 1)
    elif (id == 713):
        tipo = 27
        posx = 0
        posy = -1
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Espada2 tienda armas1 (Total: 1)
    elif (id == 714):
        tipo = 28
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1
        
    # Espada2 tienda armas2 (Total: 1)
    elif (id == 715):
        tipo = 28
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1
        
    # Espada2 tienda armas3 (Total: 1)
    elif (id == 716):
        tipo = 28
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Hacha tienda armas1 (Total: 1)
    elif (id == 717):
        tipo = 29
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1
        
    # Hacha tienda armas2 (Total: 1)
    elif (id == 718):
        tipo = 29    
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1
        
    # Hacha tienda armas3 (Total: 1)
    elif (id == 719):
        tipo = 29
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Bola y cadena tienda armas1 (Total: 1)
    elif (id == 720):
        tipo = 30
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 3
        equ = -1
        
    # Bola y cadena tienda armas2 (Total: 1)
    elif (id == 721):
        tipo = 30
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 9
        equ = -1
        
    # Bola y cadena tienda armas3 (Total: 1)
    elif (id == 722):
        tipo = 30
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 15
        equ = -1
        
    # Escudo1 tienda escudos1 (Total: 1)
    elif (id == 723):
        tipo = 31
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 4
        equ = -1
        
    # Escudo1 tienda escudos2 (Total: 1)
    elif (id == 724):
        tipo = 31
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 10
        equ = -1
        
    # Escudo1 tienda escudos3 (Total: 1)
    elif (id == 725):
        tipo = 31
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 16
        equ = -1
        
    # Escudo2 tienda escudos1 (Total: 1)
    elif (id == 726):
        tipo = 32
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 4
        equ = -1
        
    # Escudo2 tienda escudos2 (Total: 1)
    elif (id == 727):
        tipo = 32    
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 10
        equ = -1
        
    # Escudo2 tienda escudos3 (Total: 1)
    elif (id == 728):
        tipo = 32
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 16
        equ = -1
        
    # Escudo3 tienda escudos1 (Total: 1)
    elif (id == 729):
        tipo = 33
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 4
        equ = -1
        
    # Escudo3 tienda escudos2 (Total: 1)
    elif (id == 730):
        tipo = 33
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 10
        equ = -1
        
    # Escudo3 tienda escudos3 (Total: 1)
    elif (id == 731):
        tipo = 33   
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 16
        equ = -1
        
    # Maniqui tienda armaduras1 (Total: 1)
    elif (id == 732):
        tipo = 34
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Maniqui tienda armaduras2 (Total: 1)
    elif (id == 733):
        tipo = 34   
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1
        
    # Maniqui tienda armaduras3 (Total: 1)
    elif (id == 734):
        tipo = 34   
        posx = 2
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1
        
    # Cuero tienda armaduras1 (Total: 1)
    elif (id == 735):
        tipo = 35
        posx = 0
        posy = -1
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Cuero tienda armaduras2 (Total: 1)
    elif (id == 736):
        tipo = 35    
        posx = 0
        posy = -1
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1
        
    # Cuero tienda armaduras3 (Total: 1)
    elif (id == 737):
        tipo = 35
        posx = 0
        posy = -1
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1
        
    # Cota tienda armaduras1 (Total: 1)
    elif (id == 738):
        tipo = 36
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Cota tienda armaduras2 (Total: 1)
    elif (id == 739):
        tipo = 36
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1
        
    # Cota tienda armaduras3 (Total: 1)
    elif (id == 740):
        tipo = 36
        posx = 0
        posy = 0
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1
        
    # Armadura tienda armaduras1 (Total: 1)
    elif (id == 741):
        tipo = 37
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Armadura tienda armaduras2 (Total: 1)
    elif (id == 742):
        tipo = 37
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1

    # Armadura tienda armaduras3 (Total: 1)
    elif (id == 743):
        tipo = 37
        posx = 0
        posy = 1
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1
        
    # Coraza tienda armaduras1 (Total: 1)
    elif (id == 744):
        tipo = 38
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 5
        equ = -1
        
    # Coraza tienda armaduras2 (Total: 1)
    elif (id == 745):
        tipo = 38    
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 11
        equ = -1
        
    # Coraza tienda armaduras3 (Total: 1)
    elif (id == 746):
        tipo = 38
        posx = 0
        posy = 2
        longx = casilx = 1
        longy = casily = 1
        edif = 17
        equ = -1

    # Si el objeto es de tipo pinchos es invisible
    if (tipo == 17):
        visi = 0

    else:
        visi = 1
        
    # Si el objeto es del exterior o de un castillo, se posiciona al azar
    if (tipo < 18):
        
        if (((id >= 0) and (id < 535)) or (id == 550)):
            casillaInf = mundoInf
            casillaSup = mundoSup

        else:
            casillaInf = castilInf + 1
            casillaSup = castilSup - 1

        # Generacion de una posicion (x,y) aleatoria para el objeto 
        posx = randint (casillaInf, casillaSup - 1)
        posy = randint (casillaInf, casillaSup - 1)

        # Creacion de un elemento objeto
        unObjeto = Elemento (posx, posy, casilx, casily, edif)
        
        # Comprobacion de que el objeto no este dentro de algun edificio ni
        # coincida con otro objeto ni sobrepase los limites
        while ((dentro (unObjeto, listaEdificios, 1) != -1) or
               (dentro (unObjeto, listaObjetos, 0) != -1) or
               (dentroLimites (unObjeto, casillaInf, casillaSup) == 0)):

            # Generacion de otra posicion aleatoria
            posx = randint (casillaInf, casillaSup - 1)
            posy = randint (casillaInf, casillaSup - 1)

            # Creacion de otro elemento objeto
            unObjeto = Elemento (posx, posy, casilx, casily, edif)
    else:
        # Creacion del objeto interior
        unObjeto = Elemento (posx, posy, casilx, casily, edif)
        
    # Escritura de los atributos en el fichero
    ficheroObjetos.write ("%d " %id)
    ficheroObjetos.write ("%d " %tipo)
    ficheroObjetos.write ("%d " %visi)
    ficheroObjetos.write ("%d " %posx)
    ficheroObjetos.write ("%d " %posy)
    ficheroObjetos.write ("%d " %longx)
    ficheroObjetos.write ("%d " %longy)
    ficheroObjetos.write ("%d " %casilx)
    ficheroObjetos.write ("%d " %casily)
    ficheroObjetos.write ("%d " %edif)
    ficheroObjetos.write ("%d\n" %equ)

    # Insercion del elemento objeto en la lista de objetos
    listaObjetos.append (unObjeto)

# Cierre del fichero de objetos
ficheroObjetos.close ()

print "OK"

# *************************************************************************

print "Creando las casillas del mundo..."

# Creacion del fichero de casillas
ficheroCasillas = open ("casillas.dat", "w")

# Insercion del tamano del mundo en el fichero
ficheroCasillas.write ("%d " %mundoInf)
ficheroCasillas.write ("%d " %mundoSup)
ficheroCasillas.write ("%d " %castilInf)
ficheroCasillas.write ("%d " %castilSup)
ficheroCasillas.write ("%d " %casaInf)
ficheroCasillas.write ("%d\n" %casaSup)

# Inicializacion de parametros
aleatorioAnterior = -1

# Insercion de casillas en el fichero
for i in range (mundoInf, mundoSup):
    for j in range (mundoInf, mundoSup):

        # Asignacion del tipo de la casilla
        aleatorio = randint (0, 99)

        while (aleatorio == aleatorioAnterior):
            aleatorio = randint (0, 99)

        aleatorioAnterior = aleatorio
        
        if ((aleatorio >= 0) and (aleatorio < 95)):
            tipo = 0
                    
        elif ((aleatorio >= 95) and (aleatorio < 97)):
            tipo = 1
                    
        elif ((aleatorio >= 97) and (aleatorio < 99)):
            tipo = 2
                    
        elif (aleatorio == 99):
            tipo = 3

        # Escritura de la casilla en el fichero
        ficheroCasillas.write ("%d " %tipo)
        ficheroCasillas.write ("%d " %i)
        ficheroCasillas.write ("%d\n" %j)

# Cierre del fichero de casillas
ficheroCasillas.close ()

print "OK"

# *************************************************************************
