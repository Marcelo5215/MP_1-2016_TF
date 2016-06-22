CXX = g++
CXXFLAGS = -I$(IDIR) -g -Wall -ftest-coverage -fprofile-arcs
IDIR = ../include
ODIR = ../obj
LIBS = -lgtest -lgtest_main -lpthread --coverage -lgcov

_DEPS = lista.h grafo.h gerenciador.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = test.o lista.o grafo.o gerenciador.o
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

test: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
