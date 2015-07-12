IDIR = include
CC = gcc
CFLAGS = -Wall -c -I $(IDIR)
ODIR = obj
SRC = beagleblack_gpio.c
LFLAGS = -Wall
_EXE = tests_gpio.o tests_lcd.o
EXE = $(patsubst %,$(ODIR)/%,$(_EXE))
_OBJ = beagleblack_gpio.o beagleblack_lcd.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: tests_gpio tests_lcd

tests_gpio: $(_OBJ) $(_EXE)
	$(CC) $(LFLAGS) $(OBJ) $(ODIR)/$@.o -o $@
	
tests_lcd: $(_OBJ) $(_EXE)
	$(CC) $(LFLAGS) $(OBJ) $(ODIR)/$@.o -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) $<
	mv $@ $(ODIR)

clean: 
	rm $(ODIR)/*o 

