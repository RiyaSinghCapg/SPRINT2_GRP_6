INC=../inc
SRC=../src
BIN=../bin
OBJ=../obj

CFLAGS = -c -g -w
LFLAGS = -o
GCC = gcc #-fprofile-arcs -ftest-coverage
IFLAGS = -I $(INC)


all : $(BIN)/crcClient $(BIN)/crcServer

$(OBJ)/login.o : $(SRC)/login.c
	$(GCC) $(CFLAGS) $(SRC)/login.c $(IFLAGS)
	mv *.o ../obj

$(OBJ)/textToBinary.o : $(SRC)/textToBinary.c
	$(GCC) $(CFLAGS) $(SRC)/textToBinary.c $(IFLAGS)
	mv *.o ../obj
	
$(OBJ)/checkCRCServer.o : $(SRC)/checkCRCServer.c
	$(GCC) $(CFLAGS) $(SRC)/checkCRCServer.c $(IFLAGS)
	mv *.o ../obj

	
$(OBJ)/checkNum.o : $(SRC)/checkNum.c
	$(GCC) $(CFLAGS) $(SRC)/checkNum.c $(IFLAGS)
	mv *.o ../obj

	
$(OBJ)/CRCgenerator.o : $(SRC)/CRCgenerator.c
	$(GCC) $(CFLAGS) $(SRC)/CRCgenerator.c $(IFLAGS)
	mv *.o ../obj

$(OBJ)/client.o : $(SRC)/client.c
	$(GCC) $(CFLAGS) $(SRC)/client.c $(IFLAGS)
	mv *.o ../obj

$(BIN)/crcClient : $(OBJ)/login.o $(OBJ)/textToBinary.o $(OBJ)/CRCgenerator.o $(OBJ)/client.o
	 $(GCC) $(OBJ)/login.o $(OBJ)/textToBinary.o $(OBJ)/CRCgenerator.o $(OBJ)/client.o $(LFLAGS) $(BIN)/crcClient

$(OBJ)/server.o : $(SRC)/server.c
	$(GCC) $(CFLAGS) $(SRC)/server.c $(IFLAGS)
	mv *.o ../obj

$(BIN)/crcServer : $(OBJ)/checkCRCServer.o $(OBJ)/checkNum.o $(OBJ)/server.o 
	$(GCC)  $(OBJ)/checkCRCServer.o $(OBJ)/checkNum.o $(OBJ)/server.o $(LFLAGS) $(BIN)/crcServer

clean:
	rm -f $(OBJ)/*.o $(BIN)/crcClient $(BIN)/crcServer




