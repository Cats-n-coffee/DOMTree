IDIR = ../include
OUTDIR = ../out/treeOut
CC = g++
CFLAGS = -std=c++17 -I$(IDIR)

_DEPS = utils.h parser.h main.h tree.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJDIR = obj
_OBJ = main.o parser.o utils.o tree.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(OUTDIR) $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCDIR)/*~ 