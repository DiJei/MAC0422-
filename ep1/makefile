IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
vpath %.c src

all: ep1 ep1sh
#ep1sh
_DEPS = ep1sh_util.h ep1_util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ep1sh_func.o ep1sh.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJB = ep1_func.o ep1.o 
OBJB = $(patsubst %,$(ODIR)/%,$(_OBJB))


$(ODIR)/%.o:  %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lreadline -pthread

ep1: $(OBJB)
	gcc -o $@ $^ $(CFLAGS) -pthread -lreadline 

ep1sh: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lreadline 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 