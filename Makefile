CXX := mpic++
CC := mpic++
CXXFLAGS := -g -std=c++11 -Wall # -D_DEBUG_BT

SRCEXT = cpp
SRCDIR = src
BUILDDIR = build
TARGET = bin/Main

SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*~
	rm -f $(BUILDDIR)/*.o
	rm -f $(TARGET)
.PHONY: clean
