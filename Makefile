# Config variables
IDIR = ../include
CC = g++
CFLAGS = -I$(IDIR) -pthread

# Add the header files to this list
_DEPS = Bankers.h cpu_algo.h reader_writer.h paging_algo.h mvt.h Disk_Scheduling.h producer_consumer.h mft.h title.h sleeping_barber.h Dining_Philosophers.h

DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

# Add the files with the .o extension to this list
OBJ = main.o Bankers.o cpu_algo.o reader_writer.o paging_algo.o mvt.o Disk_Scheduling.o producer_consumer.o mft.o title.o sleeping_barber.o Dining_Philosophers.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
# Update clean command if using Linux: rm -f *.o *~
clean:
	del /Q /S *.o *.exe
