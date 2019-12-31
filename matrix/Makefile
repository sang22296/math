# -----------------------------------#
#              Makefile              #
#         Author: Sang Nguyen        #
#         Created:  Dec 2019         #
# -----------------------------------#

# Executable name
TARGET   = linear_regression

CC       = gcc
# compiling flags
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags
LFLAGS   = -Wall -I -lm

# change these to proper directories where each file should be
SRCDIR   = ./src
INCDIR   = ./inc
OBJDIR   = ./obj
BINDIR   = ./bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p bin/
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p obj/
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
