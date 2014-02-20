

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

listsortLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I$(listsortLIB_PATH)include -I$(EZ_PATH)boost

OBJS = listsort.o listsortIndividual.o 

LIBS = -lpthread 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :
 
CPPFLAGS+=

#END OF USER MAKEFILE OPTIONS

TARGET =	listsort

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(listsortLIB_PATH)/libeasea.a $(EZ_PATH)boost/program_options.a $(LIBS)

	
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
	-del $(TARGET).exe *.o *.cpp *.hpp listsort.png listsort.dat listsort.prm listsort.mak Makefile listsort.vcproj listsort.csv listsort.r listsort.plot listsort.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp listsort.png listsort.dat listsort.prm listsort.mak Makefile listsort.vcproj listsort.csv listsort.r listsort.plot listsort.pop
endif

