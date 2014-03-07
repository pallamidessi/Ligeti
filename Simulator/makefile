CFLAGS = -Wall -g -O0 -fpermissive 
CC = g++
LDFLAGS=-lm -lpthread -lboost_system -lboost_thread -lboost_filesystem 
LIB_EASEA=$(EZ_PATH)libeasea/include
INC_PATH = include
SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin
VPATH = src:include:obj:bin
TARGET=Simulator

ALL:$(TARGET) 

$(TARGET):main.o Reader.o 
	$(CC) $(CFLAGS) -o $@ $(OBJ_PATH)/main.o  $(OBJ_PATH)/Reader.o $(EZ_PATH)libeasea/libeasea.a $(LDFLAGS)
	mv $@ bin/.

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $(OBJ_PATH)/$@  -I$(LIB_EASEA) $(LDFLAGS)

clean : 
	rm -r doc/ $(OBJ_PATH)/*.o $(BIN_PATH)/$(TARGET) 

tar:
	tar czvf Simulator.tar.gz *

doc:
	doxygen Doxyfile
