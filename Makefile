CPP=g++
CPPFLAGS=-std=c++0x
EXE_NAME=imageops


$(EXE_NAME): Main.o Image.o unittest.o
	$(CPP) -o $(EXE_NAME) Main.o Image.o $(CPPFLAGS)  

Main.o: main.cpp Image.h
	$(CPP) -c -o Main.o main.cpp $(CPPFLAGS)

Image.o: Image.cpp Image.h
	$(CPP) -c -o Image.o Image.cpp $(CPPFLAGS)

unittest.o: testdriver.cpp Image.h
	$(CPP) -c -o unittest.o testdriver.cpp $(CPPFLAGS)

unittest: unittest.o Image.o
	$(CPP) -o UnitTest unittest.o Image.o $(CPPFLAGS)  

runtest: 
	./UnitTest

clean:
	@rm *.o $(EXE_NAME)

run:
	./$(EXE_NAME)

run+:
	./$(EXE_NAME) -a Lenna_standard.pgm Lenna_hat_mask.pgm add.pgm

run-:
	./$(EXE_NAME) -s Lenna_standard.pgm Lenna_hat_mask.pgm subtract.pgm

run!:
	./$(EXE_NAME) -i shrek_rectangular.pgm invert.pgm

run/:
	./$(EXE_NAME) -l Lenna_standard.pgm Lenna_hat_mask.pgm mask.pgm

run*:
	./$(EXE_NAME) -t shrek_rectangular.pgm 200 threshold.pgm
