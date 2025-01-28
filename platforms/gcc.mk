CXX = g++
LD = $(CXX)

LDFLAGS = -shared

STDC_FLAGS = -ansi
STDCXX_FLAGS = -ansi

INC_FLAGS = $(addprefix -I,$(INCLUDES))
DEF_FLAGS = $(addprefix -D,$(DEFINES))
OPT_FLAGS = $(addprefix -O,$(OPT_LEVEL))
WARN_FLAGS = -Wall -Wextra -pedantic
DEPEND_FLAGS =
# quad float literal
EXTRA_FLAGS += -fext-numeric-literals

LDLIBS = $(addprefix -l,$(LIBS))

%.dll: %.cpp.o
	$(info $() $()  LD   $@)
	@$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.cpp.o: %.cpp
	$(info $() $()  CXX  $@)
	@$(CXX) -c $(CXXFLAGS) $^ -o $@
