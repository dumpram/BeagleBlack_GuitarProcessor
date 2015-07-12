IDIR = ../BeagleBlack_C/include
CC = gcc
CFLAGS = -Wall -c -I $(IDIR)
ODIR = obj
SRC = beagleblack_gpio.c
LFLAGS = -Wall -lpthread
_EXE = MultiThreadIPC.o
EXE = $(patsubst %,$(ODIR)/%,$(_EXE))
_OBJ = beagleblack_gpio.o beagleblack_lcd.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: MultiThreadIPC

MultiThreadIPC: $(_OBJ) $(_EXE)
	$(CC) $(LFLAGS) $(OBJ) $(ODIR)/$@.o -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) $<
	mv $@ $(ODIR)

clean: 
	rm $(ODIR)/*o 

