CFLAGS = -Wall -g -O0 -fpermissive
CC = g++
LIB=-lm -lpthread 
LIB_EASEA=$(EZ_PATH)libeasea/include
LIB_OSCPACK=lib/oscpack
INC_PATH = include
SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin
VPATH = src:include:obj:bin
TARGET=Simulator

ALL:$(TARGET) 

$(TARGET):  
	$(CC) $(CFLAGS) -o $@ $(OBJ_PATH)/  $(LIB)
	mv $@ bin/.

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $(OBJ_PATH)/$@ -I$(LIB_OSCPACK) -I$(LIB_EASEA) $(LIB)

clean : 
	rm -r doc/ $(OBJ_PATH)/*.o $(BIN_PATH)/$(TARGET) 

tar:
	tar czvf AudioMonitor.tar.gz *

doc:
	doxygen Doxyfile
