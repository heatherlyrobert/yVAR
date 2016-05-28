#*============================----beg-of-source---============================*#

#*---(configuration)------------------*#
BASE    = yVAR

#*---(standard variables)-------------*#
COMP    = gcc -c -ansi -g -pg -Wall -Wextra
#COMP    = tcc -Wall -Wunsupported -g -bench
AS_LIB  = -shared -soname lib${BASE}.so.1  -o lib${BASE}.so.1.0
INCS    = 

LINK    = gcc
LIBS    = -L/usr/local/lib -L/lib64 -L/usr/lib64

COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
PRINTF  = @printf


#
#*---(main)---------------------------*#
#

#all               : ${BASE}.so.1.0 ${BASE}.a test
all               : ${BASE}.so.1.0 ${BASE}.a
#all                : tcc


#
#*---(parts)--------------------------*#
#


tcc                : ${BASE}.h ${BASE}.c
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "compile ${BASE} using tcc\n"
	${COMP}   ${AS_LIB}  ${LIBS}  ${BASE}.c

test               : ${BASE}.unit
	${PRINTF} "\n#---((make test driver))------------------\n"
	uUNIT    ${BASE}
	mv ${BASE}_unit.code ${BASE}_unit.c
	gcc -Wall -o ${BASE}_unit  ${BASE}_unit.c  ${LIBS} -lyUNIT -lyVAR

${BASE}.so.1.0     : ${BASE}.o
	${PRINTF} "\n#---((make dynamic version))--------------\n"
	${LINK}  -shared -Wl,-soname,lib${BASE}.so.1  ${LIBS}  -o lib${BASE}.so.1.0  ${BASE}.o

${BASE}.a          : ${BASE}.o
	${PRINTF} "\n#---((make static version))---------------\n"
	ar       rcs  lib${BASE}.a  ${BASE}.o

${BASE}.o          : ${BASE}.h ${BASE}.c
	${PRINTF} "\n#---((compile source code))---------------\n"
	${COMP}  -fPIC ${INCS} ${BASE}.c



#
#*---(utilities)----------------------*#
#

clean              :
	${PRINTF} "\n#---((remove working files))--------------\n"
	${CLEAN}  *.o
	${CLEAN}  *~
	${CLEAN}  temp*

bigclean           :
	${PRINTF} "\n#---((remove swap files))-----------------\n"
	${CLEAN}  '.'*.sw?

install            :
	${PRINTF} "\n#---((install current version))-----------\n"
	sha1sum   lib${BASE}.so.1.0
	_lib      -s  ${BASE}
	_lib      -a  ${BASE}
	ldconfig
	rm -f     /usr/share/man/man3/${BASE}.3.bz2
	cp -f     ${BASE}.3    /usr/share/man/man3/
	bzip2     /usr/share/man/man3/${BASE}.3
	chmod     0644  /usr/share/man/man3/${BASE}.3.bz2

remove             :
	${PRINTF} "\n#---((remove existing version))-----------\n"
	_lib      -d  ${BASE}
	ldconfig

#*============================----end-of-source---============================*#
