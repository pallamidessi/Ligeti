

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

weierstrassLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I$(weierstrassLIB_PATH)include -I$(EZ_PATH)boost

OBJS = weierstrass.o weierstrassIndividual.o 

LIBS = -lpthread 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :
 

#END OF USER MAKEFILE OPTIONS

TARGET =	weierstrass

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(weierstrassLIB_PATH)/libeasea.a $(EZ_PATH)boost/program_options.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp weierstrass.png weierstrass.dat weierstrass.prm weierstrass.mak Makefile weierstrass.vcproj weierstrass.csv weierstrass.r weierstrass.plot weierstrass.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp weierstrass.png weierstrass.dat weierstrass.prm weierstrass.mak Makefile weierstrass.vcproj weierstrass.csv weierstrass.r weierstrass.plot weierstrass.pop
endif

