CXX = g++
CXXFLAGS = -O2

SRC_DIR     := src
OBJ_DIR     := obj

TARGETS1 := ../bin/TFG

TARGETS2 := ../bin/Tiempos

SOURCES1 := $(shell find src -name "[A-SU-Z]*.cpp") src/TFG.cpp

OBJECTS1 := $(patsubst src/%.cpp,obj/%.o,$(SOURCES1))

SOURCES2 := $(shell find src -name "[A-SU-Z]*.cpp") src/Tiempos.cpp

OBJECTS2 := $(patsubst src/%.cpp,obj/%.o,$(SOURCES2))

HEADERS := $(shell find include -name "*.h")
HEADERDIRS := $(sort $(dir $(HEADERS)))

INCLUDEFLAGS := $(addprefix -I,$(HEADERDIRS))

all: $(TARGETS1) $(TARGETS2)

$(TARGETS1): $(OBJECTS1)
	$(CXX) $^ -o $@

$(TARGETS2): $(OBJECTS2)
	$(CXX) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -c $(INCLUDEFLAGS) -o $@
	
clean:
	rm -f $(OBJECTS1) $(TARGETS1) $(OBJECTS2) $(TARGETS2)
