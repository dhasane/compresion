
CC = g++

COMP = compresion
MAIN = compMain
EXENAME = comp

todo: $(COMP).o
	$(CC) -o $(EXENAME) $(COMP).o $(MAIN).cpp

%.o: %.cpp
	$(CC) -c $@ $<

clean:
	rm *.o $(EXENAME)
