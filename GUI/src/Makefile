CXX = g++
CXXFLAGS = -I$(IDIR) -g -Wall
IDIR = ../include
ODIR = ../obj
LIBS = -lncurses

_DEPS = lista.h grafo.h gerenciador.h ggui.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = gui.o lista.o grafo.o gerenciador.o ggui.o
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

gui: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
