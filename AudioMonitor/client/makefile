CFLAGS = -Wall -g -O0
#OBJECTS = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
#OBJECTS_DIR = $(patsubst src/%.c, objets/%.o, $(wildcard src/*.c))
CC = g++
LIB=
LIB_PATH= lib
INC_PATH =include/
SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin
VPATH = src:include:obj:bin
TARGET=AudioMonitorClient

ALL:$(TARGET) 

#AudioMonitorClient:mainFrame.o AudioMonitorServer.o EASEAClientData.o Compositor.o OSCWrapper.o
#	gcc $(CFLAGS) -o $@ $(OBJ_PATH)/mainFrame.o $(OBJ_PATH)/AudioMonitorServer.o $(OBJ_PATH)/EASEAClientData.o $(OBJ_PATH)/Compositor.o $(OBJ_PATH)/OSCWrapper.o  $(LIB)
#	mv $@ bin/.

AudioMonitorClient: AudioMonitorModule.o AudioMonitorClient.o 
	$(CC) $(CFLAGS) -o $@ $(OBJ_PATH)/AudioMonitorClient.o $(OBJ_PATH)/AudioMonitorModule.o   $(LIB)
	mv $@ bin/.

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $(OBJ_PATH)/$@ -I $(LIB_PATH) $(LIB)

clean : 
	rm $(OBJ_PATH)/*.o $(BIN_PATH)/$(TARGET)

tar:
	tar czvf AudioMonitor.tar.gz $(SRC_PATH) $(INC_PATH) $(LIB_PATH) makefile

doc:
	doxygen Doxyfile
