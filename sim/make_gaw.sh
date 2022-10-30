echo 'gcc -c -g -I/usr/include/jsoncpp -I/opt/redpitaya/include -D_RED_PITAYA -O0 -DVERSION= -DREVISION= gaw.c -o gaw.o'
gcc -c -g -I/usr/include/jsoncpp -I/opt/redpitaya/include -D_RED_PITAYA -O0 -DVERSION= -DREVISION= gaw.c -o gaw.o
echo 'gcc -g gaw.o -pthread -ljsoncpp -lzmq -lstdc++ -ljsoncpp  -L/opt/redpitaya/lib -lrp -lm -lpthread -l:librp.so -o gaw'
gcc -g gaw.o -pthread -ljsoncpp -lzmq -lstdc++ -ljsoncpp  -L/opt/redpitaya/lib -lrp -lm -lpthread -l:librp.so -o gaw

