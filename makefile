TARGET = RPG

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

clean:
	rm -rf $(OBJDIR) *.o $(TARGET)