SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := raytrace

CC := clang++
SRCEXT := cpp
CFLAGS := -std=c++11 -g -O2
LIB := -L lib -lpthread -lX11
INC := -I include

SRC := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJ := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SRC:.$(SRCEXT)=.o))
DEP := $(OBJ:.o=.d)

.PHONY: clean all

all: $(TARGETDIR)/$(TARGET)

$(TARGETDIR)/$(TARGET): $(OBJ)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	$(CC) $^ -o $(TARGETDIR)/$(TARGET) $(LIB)

-include $(DEP)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) -MMD -MP $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGETDIR)

