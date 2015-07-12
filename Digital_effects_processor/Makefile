# -------------------------------------------------
# Makefile for DEP project
# Author: ivan.pavic2@fer.hr
# Version: 1.0
# -------------------------------------------------

INCDIR = inc
CC = gcc
CFLAGS = -Wall -I $(INCDIR)
OBJDIR = obj
SRCDIR = src
BINDIR = bin
LFLAGS = -Wall -I $(INCDIR) -lpthread -ljack -lfftw3 -lm
LINKER = gcc -o
EXE = DEP_main
 
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(EXE): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
