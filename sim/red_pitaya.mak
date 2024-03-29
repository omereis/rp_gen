#*****************************************************************************\
#                                 Makefile                                    |
#*****************************************************************************/
#
#	Adding source, e.g. file.cpp/h by:
#		add file.o to OBJECTS
#		add file.h to INCLUDES
#		add rule for file.o that depends on file.cpp AND all includes
#*****************************************************************************/
CPP = gcc
CFLAGS = -std=c++14 -g -I/usr/include/jsoncpp
CFLAGS += -I/opt/redpitaya/include -D_RED_PITAYA -O0
CFLAGS += -DVERSION=$(VERSION) -DREVISION=$(REVISION)

OBJECTS = rp_gen.o signal_params.o cli_options.o misc.o trim.o
INCLUDES = rp_gen.h signal_params.h cli_options.h misc.h trim.h red_pitaya.mak
SOURCES = rp_gen.cpp signal_params.cpp cli_options.cpp misc.cpp trim.cpp
#LDFLAGS = -pthread -ljsoncpp -lstdc++ -ljsoncpp -lm
#LDFLAGS += -L/opt/redpitaya/lib
#LDFLAGS = -pthread -ljsoncpp -lzmq -lstdc++ -ljsoncpp
LDFLAGS = -pthread -ljsoncpp -lzmq -lstdc++ -ljsoncpp  -L/opt/redpitaya/lib -lrp
LDLIBS = -lm -lpthread -l:librp.so


RP_OBJ = rp_gen.o signal_params.o cli_options.o trim.o misc.o
#RP_SRC = rp_server.cpp rp_setup.cpp trim.cpp misc.cpp mca_params.cpp calc_mca.cpp
#RP_INC = 

all: rp_gen

.cpp.o:
	$(CPP) -c $(CFLAGS) $< -o $@

rp_gen: $(RP_OBJ)
	$(CPP) -g $(RP_OBJ) $(LDFLAGS) $(LDLIBS) -o $@

#read_json: $(OBJECTS)
#	$(CPP) -g $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm *.o

clean_all:
	rm *.o rp_client rp_server

