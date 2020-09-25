CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17 -Iinclude -g
LDFLAGS = -lncurses

EXE = hw_02
TESTEXE = test_hw_02
SRCDIR = src
TESTDIR = test
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TESTOBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp)) obj/Board.o

all: $(EXE) $(TESTEXE)

$(EXE): $(OBJDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

$(TESTEXE): $(OBJDIR) $(TESTOBJECTS)
	$(CXX) $(TESTOBJECTS) -o $(TESTEXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TESTEXE)

.PHONY: clean all
