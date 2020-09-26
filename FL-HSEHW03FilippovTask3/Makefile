CXX = g++#clang++-10 -stdlib=libc++
CXXFLAGS = -Wall -Werror -std=c++17 -Iinclude -O3
LDFLAGS =

EXE = hw_03
TESTEXE = test_hw_03
SRCDIR = src
TESTDIR = test
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TESTOBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp)) obj/Regexp.o

all: $(EXE) $(TESTEXE)

$(EXE): $(OBJDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

$(TESTEXE): $(OBJDIR) $(TESTOBJECTS) $(OBJECTS)
	$(CXX) $(TESTOBJECTS) -o $(TESTEXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TESTEXE)

.PHONY: clean all
