# -----------------------------------#
#              Makefile              #
#         Author: Sang Nguyen        #
#         Created:  Dec 2019         #
# -----------------------------------#

# Executable name
TARGET    = main

CC        = gcc
# compiling flags
CFLAGS    = -std=c99 -Wall -I.
SO_FLAGS  = -shared -fPIC

SO_TARGET = linear_rg.so
SO_SRC    = ./src/linear_regression.c

LINKER    = gcc
# linking flags
LFLAGS    = -Wall -I -lm

# change these to proper directories where each file should be
SRCDIR    = ./src
INCDIR    = ./inc
OBJDIR    = ./obj
BINDIR    = ./bin
SO_DIR    = ./share_obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm        = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

so:
	@mkdir -p $(SO_DIR)
	@$(CC) $(SO_SRC) $(CFLAGS) $(SO_FLAGS) -o $(SO_DIR)/$(SO_TARGET)
	@echo "Create shared object for linear_regression.c in $(SO_DIR)/$(SO_TARGET)"

.PHONY: clean
clean:
	@$(rm) -rf $(OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) -rf $(BINDIR)
	@echo "Executable removed!"
