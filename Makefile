#*============================---(source-start)---============================*#

#*---(current variables)--------------*#
BASE    = yVAR
DEBUG   = yVAR_debug
UNIT    = yVAR_unit
HDIR    = /home/system/yVAR.var_testing
MNUM    = 3
MDIR    = /usr/share/man/man${MNUM}
#*---(compilier variables)------------*#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include 
LINK    = gcc
LIBDIR  = -L/usr/local/lib
LIBS    = ${LIBDIR} 
LIBD    = ${LIBDIR}   -lyLOG
LIBU    = ${LIBDIR}   -lyLOG   -lyUNIT   -lyVAR
#*---(file lists)---------------------*#
HEADS   = ${BASE}.h    ${BASE}_priv.h
OBJS    = ${BASE}.os
OBJD    = ${BASE}.o
OBJU    = ${UNIT}.o    ${BASE}.o
#*---(make variables)-----------------*#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#*---(executables)--------------------*#
all                : ${BASE} ${DEBUG} ${UNIT}

${BASE}            : ${OBJS}
	${LINK}  -shared -Wl,-soname,lib${BASE}.so.1    ${LIBS}  -o lib${BASE}.so.1.0       ${OBJS}
	ar       rcs  lib${BASE}.a               ${OBJS}

${DEBUG}           : ${OBJD}
	${LINK}  -shared -Wl,-soname,lib${DEBUG}.so.1   ${LIBD}  -o lib${DEBUG}.so.1.0      ${OBJD}
	ar       rcs  lib${DEBUG}.a              ${OBJD}

${UNIT}            : ${OBJU}
	${LINK}  -o ${UNIT}          ${LIBU}     ${OBJU}


#*---(components)---------------------*#
${BASE}.o        : ${HEADS}   ${BASE}.c
	${COMP}  -fPIC  ${BASE}.c                             ${INCS}

${BASE}.os       : ${HEADS}   ${BASE}.c
	${STRIP}        ${BASE}.c         > ${BASE}.cs
	${COMP}  -fPIC  ${BASE}.cs       -o ${BASE}.os        ${INCS}

${UNIT}.o        : ${HEADS}   ${BASE}.unit
	koios           ${BASE}
	${COMP}         ${UNIT}.c                             ${INCS}



#*---(housecleaning)------------------*#
clean              :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "cleaning out local object, backup, and temp files\n"
	${CLEAN} lib${BASE}.so.1
	${CLEAN} lib${BASE}.so.1.0
	${CLEAN} lib${BASE}.a
	${CLEAN} lib${DEBUG}.so.1
	${CLEAN} lib${DEBUG}.so.1.0
	${CLEAN} lib${DEBUG}.a
	${CLEAN} *.o
	${CLEAN} *.cs
	${CLEAN} *.os
	${CLEAN} *~
	${CLEAN} temp*
	${CLEAN} ${BASE}_unit.c

bigclean           :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "clean out local swap files\n"
	${CLEAN}  '.'*.sw?

remove             :
	${PRINT}  "\n--------------------------------------\n"
	${PRINT}  "remove ${BASE} from production\n"
	_lib      -d  ${BASE}
	_lib      -d  ${DEBUG}
	ldconfig
	rm -f       ${MDIR}/${BASE}.${MNUM}.bz2

install            :
	#---(production version)--------------#
	@sha1sum   lib${BASE}.so.1.0
	_lib      -s  ${BASE}
	_lib      -a  ${BASE}
	ldconfig
	#---(debug version)-------------------#
	# use "no header" version as the header is not named with _debug
	@sha1sum   lib${DEBUG}.so.1.0
	_lib      -S  ${DEBUG}
	_lib      -A  ${DEBUG}
	ldconfig
	#---(documentation)-------------------#
	rm -f       ${MDIR}/${BASE}.${MNUM}.bz2
	cp -f       ${BASE}.${MNUM}                ${MDIR}/
	bzip2       ${MDIR}/${BASE}.${MNUM}
	chmod 0644  ${MDIR}/${BASE}.${MNUM}.bz2



#*============================----end-of-source---============================*#
