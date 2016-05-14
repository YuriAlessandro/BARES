##########
# MACROS #
##########
## DIRS
INCDIR = include
BINDIR = bin
SRCDIR = src
OBJDIR = objs

# TARGET
TARGET = $(BINDIR)/exe

## EXTENSIONS
SRCEXT = cpp

## SOURCES LIST
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

## OBJECTS
OBJS = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

## COMPILER
CC = g++

## FLAGS
WARN = -Wall
INCFLAG = -I $(INCDIR)
CFLAGS = $(WARN) $(INCFLAG) -std=c++11 -c

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET): $(OBJS)
	@echo "Compilando..."
	$(CC) -o $@ $^

clean:
	@echo "Limpando..."
	@rm -rf $(OBJDIR)/*
	@rm -rf $(TARGET)

.PHONY: clean
