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


.PHONY: mf_test cmsis_test

mf_test:
	@$(CXX) $(CXXFLAGS) test/$@.cpp $(TEST_SRC) /Fe:$@
	@$@

cmsis_test:
	@$(CC) $(CFLAGS) -ICMSIS-DSP/Include test/$@.c $(TEST_SRC) $(CMSIS_SRC) /Fe:$@
	@$@
