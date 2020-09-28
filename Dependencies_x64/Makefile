#-------------------------------------MACROS-------------------------------------------

# Specify compiler
CC=g++
# Specify linker
LINK=g++

#Obj files
OBJ = obj/AParticle.o obj/CParticle.o obj/Vector3.o 

#Flags used by compiler/linker
#-Wall : enable warning during construction
#-g : provide debugging information
#-fPIC : seems to be an option for dynamic linking apparently need to be specified to create shared object
CFLAGS = -Wall -g -fPIC

#Dir where you can find the dependencies
INCLUDES = -I.

#Clean function
CLEAN = rm
#Clean flags
#-f : ignore non existen files
#-v : explain what is being done
CLEANFLAGS = -fv
#--------------------------------------------------------------------------------------

#-------------------------------------TARGETS------------------------------------------
#Create a shared library for the Games namespace
#-shared : specify that we are going to create a shared object 
#-o : output files 
bin/libphsqengine.so : ${OBJ}
	${CC} ${CFLAGS} ${INCLUDES} -shared -o $@ ${OBJ}

obj/.cpp.o : 
	${LINK} ${CFLAGS} ${INCLUDES} -c $<

.PHONY : clean
clean : 
	${CLEAN} ${CLEANFLAGS} bin/* obj/*
#--------------------------------------------------------------------------------------