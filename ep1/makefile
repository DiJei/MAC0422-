IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
vpath %.c src

_DEPS = util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ep1shFunc.o ep1sh.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o:  %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lreadline 

ep1sh: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -lreadline 


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 