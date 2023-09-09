CC = g++ -std=c++11 -c 
CL = g++ -std=c++11
BUILDDIR = Source

all: utrip.out

utrip.out: Main.o Utrip.o Hotel.o User.o Filter.o IO.o Room.o Reserve.o Sort.o
	$(CL) Main.o Utrip.o Hotel.o User.o Filter.o IO.o Room.o Reserve.o Sort.o -o utrip.out 

Main.o: $(BUILDDIR)/Main.cpp $(BUILDDIR)/Utrip.hpp $(BUILDDIR)/IO.hpp
	$(CC) $(BUILDDIR)/Main.cpp

Utrip.o: $(BUILDDIR)/Utrip.cpp $(BUILDDIR)/Utrip.hpp $(BUILDDIR)/Filter.hpp $(BUILDDIR)/ImportException.hpp $(BUILDDIR)/Hotel.hpp $(BUILDDIR)/User.hpp
	$(CC) $(BUILDDIR)/Utrip.cpp

Hotel.o: $(BUILDDIR)/Hotel.cpp $(BUILDDIR)/Hotel.hpp $(BUILDDIR)/Room.hpp
	$(CC) $(BUILDDIR)/Hotel.cpp 

User.o: $(BUILDDIR)/User.cpp $(BUILDDIR)/User.hpp $(BUILDDIR)/Reserve.hpp 
	$(CC) $(BUILDDIR)/User.cpp 

Filter.o: $(BUILDDIR)/Filter.cpp $(BUILDDIR)/Filter.hpp $(BUILDDIR)/ImportException.hpp
	$(CC) $(BUILDDIR)/Filter.cpp 

IO.o: $(BUILDDIR)/IO.cpp $(BUILDDIR)/IO.hpp 
	$(CC) $(BUILDDIR)/IO.cpp 

Room.o: $(BUILDDIR)/Room.cpp $(BUILDDIR)/Room.hpp 
	$(CC) $(BUILDDIR)/Room.cpp 

Reserve.o: $(BUILDDIR)/Reserve.cpp $(BUILDDIR)/Reserve.hpp 
	$(CC) $(BUILDDIR)/Reserve.cpp 

Sort.o: $(BUILDDIR)/Sort.cpp $(BUILDDIR)/Sort.hpp 
	$(CC) $(BUILDDIR)/Sort.cpp 
	
.PHONY: clean
clean:
	rm -r *.o
	rm utrip.out