INC=../inc
SRC=../src
BIN=../bin
OBJ=../obj

CFLAGS = -c -g -w
LFLAGS = -o
GCC = gcc
IFLAGS = -I $(INC)


all : $(BIN)/crcClient $(BIN)/crcServer

$(OBJ)/login.o : $(SRC)/login.c
	$(GCC) $(CFLAGS) $(SRC)/login.c $(IFLAGS)
	mv *.o ../obj

$(OBJ)/textToBinary.o : $(SRC)/textToBinary.c
	$(GCC) $(CFLAGS) $(SRC)/textToBinary.c $(IFLAGS)
	mv *.o ../obj

$(OBJ)/client.o : $(SRC)/client.c
	$(GCC) $(CFLAGS) $(SRC)/client.c $(IFLAGS)
	mv *.o ../obj

$(BIN)/crcClient : $(OBJ)/login.o $(OBJ)/textToBinary.o $(OBJ)/client.o
	 $(GCC) $(OBJ)/login.o $(OBJ)/textToBinary.o $(OBJ)/client.o $(LFLAGS) $(BIN)/crcClient

$(OBJ)/server.o : $(SRC)/server.c
	$(GCC) $(CFLAGS) $(SRC)/server.c $(IFLAGS)
	mv *.o ../obj

$(BIN)/crcServer : $(OBJ)/server.o 
	$(GCC)  $(OBJ)/server.o $(LFLAGS) $(BIN)/crcServer

clean:
	rm -f $(OBJ)/*.o $(BIN)/crcClient $(BIN)/crcServer




