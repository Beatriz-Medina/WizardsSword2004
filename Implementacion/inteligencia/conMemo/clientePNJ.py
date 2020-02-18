#! /usr/bin/env python

# **************************************************************************
#			   clientePNJ.py   -  description
#   	                       ------------------
# Wizard's Sword
# desarrollado por	: (C) 2004 by M Beatriz Medina Yanez
# *************************************************************************


from sys import *
from socket import *
from time import *
from funciones import *

try:
    
    # Definicion de la direccion IP servidor y del puerto
    host = '127.0.0.1'
    port = 50007
    
    # Creacion del socket del cliente
    sockCliente = socket (AF_INET, SOCK_STREAM, 0)
    
    # Conexion del cliente
    sockCliente.connect ((host, port))
    
    # Obtencion del numero de argumentos
    argc = len (argv)

    # Si no hay argumentos
    if (argc == 1):
        esp = 4
        inte = 0

    # Si hay un solo argumento
    elif (argc == 2):
        esp = int (argv[1])
        inte = 0

    # Si hay dos argumentos al menos
    else:
        esp = int (argv[1])
        inte = int (argv[2])

    # Comprobacion de argumentos
    if ((esp < 0) or (esp > 4)):
        esp = 4

    if ((inte < 0) or (inte > 1)):
        inte = 0

    if ((esp == 4) and (inte != 0)):
        inte = 0
        
    # Envio de la especie al servidor
    enviaEnteroAServidor (sockCliente, esp)

    # Inicializacion de la lista del tamano del mundo
    # mundoInf, mundoSup, castilInf, castilSup, casaInf, casaSup
    listaMundo = []
        
    # Recepcion del tamano del mundo e insercion en la lista
    for i in range (6):
        
        tamano = recibeEnteroDeServidor (sockCliente)
        listaMundo.append (tamano)

    # Inicializacion de la lista de items
    listaItem = []

    # Si la inteligencia es deliberativa
    if (inte == 1):
        
        # Inicializacion del objetivo actual
        objetivoActual = None
        
        # Inicializacion de la lista de operadores
        listaOperadores = []

        # Carga de los operadores
        cargaOperadores (listaOperadores)

    # Bucle principal
    fin = 0
    while (fin == 0):
        
        # Recepcion del flag de envio
        env = recibeEnteroDeServidor (sockCliente)
        
        # Recepcion del turno
        turno = recibeEnteroDeServidor (sockCliente)
        
        # Si el flag de envio esta activo
        if (env > 0):
            
            # Inicializacion de las listas
            listaObjetos = []
            listaP = []

            if (env == 2):                
                listaEdificios = []
                listaCasillas = []

            # Carga del mundo
            indiceP = cargaMundo (listaEdificios, listaObjetos, listaP,
                                  listaCasillas, env, sockCliente)

            # Si el personaje activo no existe
            if (indiceP == -1):
                
                # Envio del flag de desconexion
                enviaEnteroAServidor (sockCliente, -1)
                
                # Cierre
                fin = 1
                
        # Si el personaje activo existe
        if (fin == 0):                                
            
            # Si la inteligencia es reactiva
            if (inte == 0):
                tomaDecisionReglas (listaMundo, listaEdificios, listaObjetos,
                                    listaP, indiceP, listaCasillas, turno,
                                    sockCliente, listaItem)
            # Si es deliberativa
            else:
                objetivoActual = tomaDecisionStrips (objetivoActual,
                                                     listaOperadores,
                                                     listaMundo,
                                                     listaEdificios,
                                                     listaObjetos,
                                                     listaP, indiceP,
                                                     listaCasillas, turno,
                                                     sockCliente, listaItem)
            # Retardo
            sleep (0.6)
                
    # Cierre del socket
    sockCliente.close ()

except (KeyboardInterrupt, EOFError):
    enviaEnteroAServidor (sockCliente, -1)	      
    sleep (1)

# *************************************************************************
