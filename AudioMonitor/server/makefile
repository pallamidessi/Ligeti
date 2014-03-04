CFLAGS = -Wall -g -O0 -fpermissive
#OBJECTS = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
#OBJECTS_DIR = $(patsubst src/%.c, objets/%.o, $(wildcard src/*.c))
CC = g++
LIB=-lm -lpthread 
LIB_EASEA=$(EZ_PATH)libeasea/include
LIB_OSCPACK=lib/oscpack
INC_PATH = include
SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin
VPATH = src:include:obj:bin
TARGET=AudioMonitor

ALL:$(TARGET) 

#AudioMonitor:mainFrame.o AudioMonitorServer.o EASEAClientData.o Compositor.o OSCWrapper.o
#	gcc $(CFLAGS) -o $@ $(OBJ_PATH)/mainFrame.o $(OBJ_PATH)/AudioMonitorServer.o $(OBJ_PATH)/EASEAClientData.o $(OBJ_PATH)/Compositor.o $(OBJ_PATH)/OSCWrapper.o  $(LIB)
#	mv $@ bin/.

AudioMonitor:mainFrame.o AudioMonitorServer.o EASEAClientData.o Compositor.o  
	$(CC) $(CFLAGS) -o $@ $(OBJ_PATH)/mainFrame.o $(OBJ_PATH)/AudioMonitorServer.o $(OBJ_PATH)/EASEAClientData.o  $(OBJ_PATH)/Compositor.o $(LIB_OSCPACK)/ip/IpEndpointName.o $(LIB_OSCPACK)/osc/OscOutboundPacketStream.o $(LIB_OSCPACK)/osc/OscTypes.o $(LIB_OSCPACK)/ip/posix/UdpSocket.o $(LIB_OSCPACK)/ip/posix/NetworkingUtils.o $(EZ_PATH)libeasea/libeasea.a  $(LIB)
	mv $@ bin/.

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $(OBJ_PATH)/$@ -I$(LIB_OSCPACK) -I$(LIB_EASEA) $(LIB)

clean : 
	rm -r doc/ $(OBJ_PATH)/*.o $(BIN_PATH)/$(TARGET) 

tar:
	tar czvf AudioMonitor.tar.gz $(SRC_PATH) $(INC_PATH) $(LIB_PATH) makefile

doc:
	doxygen Doxyfile
