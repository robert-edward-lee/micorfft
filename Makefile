CC = gcc
CXX = g++
LD = $(CC)

INCLUDES = include test

CFLAGS = $(addprefix -I,$(INCLUDES))
CXXFLAGS = $(addprefix -I,$(INCLUDES))


.PHONY: test
test:
	@$(CXX) $(CXXFLAGS) $@/$@.cpp $@/print_hist.c -o $@
	@./$@
