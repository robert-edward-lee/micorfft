CC = gcc
CXX = g++
LD = $(CC)

INCLUDES = include

CFLAGS = $(addprefix -I,$(INCLUDES))
CXXFLAGS = $(addprefix -I,$(INCLUDES))

test:
	@$(CXX) $(CXXFLAGS) $@.cpp -o $@
	@./$@
