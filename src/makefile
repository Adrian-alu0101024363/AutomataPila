all: main.cc nfa.cc State.cc Transition.cc 

CXX=g++
CXXFLAGS=-g -w

OBJS = main.o nfa.o State.o Transition.o 


all: ${OBJS}
	$(CXX) $(CXXFLAGS) -o pushdown ${OBJS}

clean:
	rm -rf *.o pushdown