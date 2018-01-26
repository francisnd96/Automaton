# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main modelmain

modelmain:	main.cpp ModelState.o Transition.o ModelAutomaton.o
	$(CXX) $(CXXFLAGS) main.cpp ModelState.o Transition.o ModelAutomaton.o -o modelmain

main:	main.cpp State.o Transition.o Automaton.o
	$(CXX) $(CXXFLAGS) main.cpp State.o Transition.o Automaton.o -o main

State.o: State.cpp State.h 
	$(CXX) $(CXXFLAGS) -c State.cpp 

#ModelState.o: ModelState.cpp ModelState.h 
#	$(CXX) $(CXXFLAGS) -c ModelState.cpp 

Transition.o: Transition.cpp Transition.h
	$(CXX) $(CXXFLAGS) -c Transition.cpp

Automaton.o: Automaton.cpp Automaton.h
	$(CXX) $(CXXFLAGS) -c Automaton.cpp

#ModelAutomaton.o: ModelAutomaton.cpp ModelAutomaton.h
#	$(CXX) $(CXXFLAGS) -c ModelAutomaton.cpp

deepclean: 
	rm -f *~ *.o main modelmain *.exe *.stackdump BundleMain TreeMain

clean:
	-rm -f *~ *.o *.stackdump

