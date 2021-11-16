
# overridable parameters

PREFIX?=/usr/local

EXE?=${NAME}

LIB?=lib${NAME}.a

PROG?=$(wildcard main.c)
TEST?=$(wildcard test.c)
HDRS?=$(wildcard ${NAME}*.h)
SRCS?=$(wildcard ${NAME}*.c)

LANGUAGE?=-std=c11
WARNINGS?=-pedantic -Wall -Wextra -Wno-unused
DEBUG?=-g
OPTIMIZE?=-Os
DEFINES?=
INCLUDES?=-I.

################################################################################

UPNAME=$(shell echo ${NAME} | tr 'a-z' 'A-Z')

CFLAGS=${LANGUAGE} ${WARNINGS} ${DEBUG} ${OPTIMIZE}
CPPFLAGS=${DEFINES} -DIN_${UPNAME} ${INCLUDES}

OBJS=$(SRCS:.c=.o)

ALLTGTS=$(if ${PROG},${EXE}) $(if ${SRCS},${LIB}) $(if ${TEST},test)
ALLSRCS=$(if ${PROG},${PROG}) $(if ${SRCS},${SRCS}) $(if ${TEST},${TEST})
ALLOBJS=$(ALLSRCS:.c=.o)
ALLDEPS=$(ALLSRCS:.c=.d)

# define default target first
default: all

# include/update dependencies
-include ${ALLDEPS}

# main target
all: ${ALLTGTS}

# rule for the program
ifneq (${EXE},)
${EXE}: ${PROG} ${LIB}
	${CC} ${CPPFLAGS} -DIN_${UPNAME}_PROG ${CFLAGS} -o $@ $^
	size $@
endif

# rule for the library
ifneq (${LIB},)
${LIB}: ${OBJS}
	rm -f $@ && ${AR} -crs $@ $^
	size $@
endif

# rules for the test
ifneq (${TEST},)
check: test
	./test
.PHONY: check

test: ${TEST} ${LIB}
	${CC} ${CPPFLAGS} -DIN_${UPNAME}_TEST ${CFLAGS} -o $@ $^
	size $@
endif

# generate dependencies
%.d: %.c
	@echo updating $@
	@set -e; rm -f $@; \
	${CC} -M ${CPPFLAGS} $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# build rule for C files
%.o: %.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c -o $@ $<

# package install
install: all
ifneq (${PROG},)
	mkdir -p ${PREFIX}/bin
	install ${BIN} ${PREFIX}/bin
endif
ifneq (${SRCS},)
	mkdir -p ${PREFIX}/lib
	install ${LIB} ${PREFIX}/lib
endif
ifneq (${HDRS},)
	mkdir -p ${PREFIX}/include
	install -t ${PREFIX}/include ${HDRS}
endif
.PHONY: install

# package uninstall
uninstall:
ifneq (${PROG},)
	rm -f ${PREFIX}/bin/${EXE}
endif
ifneq (${SRCS},)
	rm -f ${PREFIX}/lib/${LIB}
endif
ifneq (${HDRS},)
	for f in ${HDRS}; do rm -f ${PREFIX}/include/$$f; done
endif
.PHONY: uninstall

# source cleanup
clean:
	rm -f ${ALLOBJS} ${ALLDEPS} ${ALLTGTS}
.PHONY: clean
