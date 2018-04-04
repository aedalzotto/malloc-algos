EXEC := mmalgo

CC := g++
CP := cp
MK := mkdir
RM := rm

SRCDIR := src
BUILDDIR := build
EXECDIR := bin
SHAREDIR := share/$(EXEC)

TARGET := $(EXECDIR)/$(EXEC)

SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))
CFLAGS := -g -Wall
PKGCFG := `pkg-config --cflags --libs gtkmm-3.0`
LDFLAGS := -ldl -lboost_system -lboost_filesystem
INCLUDES := -I./$(SRCDIR)/include

GLADEFILES := $(wildcard $(SRCDIR)/*.glade)
CPGLADE := $(addprefix $(SHAREDIR)/,$(notdir $(GLADEFILES)))


all: $(TARGET) $(CPGLADE)

buildrun: all
	./$(TARGET)

run:
	./$(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(MK) -p $(EXECDIR)
	$(CC) $^ -o $(TARGET) $(LDFLAGS) $(PKGCFG) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $<"
	@$(MK) -p $(BUILDDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES) $(PKGCFG)

$(CPGLADE): $(GLADEFILES)
	@echo "Copying glade files..."
	@$(MK) -p $(SHAREDIR)
	@$(CP) $< $@

clean:
	@echo "Cleaning..."
	@$(RM) -rf $(BUILDDIR) $(EXECDIR) $(SHAREDIR)

.PHONY: clean