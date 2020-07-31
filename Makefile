# -----------------------------------#
#              Makefile              #
#         Author: Sang Nguyen        #
#         Created:  Dec 2019         #
# -----------------------------------#

# Executable name
TARGET    = main

CC        = gcc
# compiling flags
CFLAGS    = -std=c99 -Wall -I. -lm
SO_FLAGS  = -shared -fPIC

SO_TARGET = ML_algo.so
SO_SRC    = ./src/linear_regression.c

COMPILER    = gcc
# linking flags
# LFLAGS    = -Wall -I. -lm
LFLAGS    = -I. -lm

# change these to proper directories where each file should be
SRCDIR    = $(shell find -name "src")
INCDIR    = $(shell find -name "inc")
OBJDIR    = ./obj
BINDIR    = ./bin
SO_DIR    = ./share_obj

SOURCES  := $(shell find $(SRCDIR) -name '*.c')
INCLUDES := $(shell find $(INCDIR) -name '*.h')
OBJECTS  := $(SOURCES: %.c=%.o)
rm        = rm -f


$(BINDIR)/$(TARGET): $(SOURCES)
	@mkdir -p $(BINDIR)
	@$(COMPILER) $(SOURCES) $(LFLAGS) -o $@
	@echo "Build complete!"

share_obj: $(SOURCES)
	@mkdir -p $(SO_DIR)
	@$(CC) $(SOURCES) $(CFLAGS) $(SO_FLAGS) -o $(SO_DIR)/$(SO_TARGET)
	@echo "Create shared object for ML algo in $(SO_DIR)/$(SO_TARGET)"

.PHONY: clean
clean:
	@$(rm) -rf $(OBJDIR) 
	@$(rm) -rf $(BINDIR) $(SO_DIR)
	@echo "Cleanup complete!"
