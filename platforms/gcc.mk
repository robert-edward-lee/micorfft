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
EXTRA_FLAGS =

LDLIBS = $(addprefix -l,$(LIBS))

.PHONY: test mf_test cmsis_test

build_test: gen_test
	@echo '  CXX ' c_wrapper
	@$(CXX) -c $(CXXFLAGS) c_wrapper.cpp -o c_wrapper.cpp.o
	@echo '  LD  ' c_wrapper
	@$(LD) $(LDFLAGS) -o $(SHARED_LIB) c_wrapper.cpp.o $(LDLIBS)

mf_test:
	@$(CXX) $(CXXFLAGS) test/$@.cpp $(TEST_SRC) /Fe:$@
	@$@

cmsis_test:
	@$(CC) $(CFLAGS) -ICMSIS-DSP/Include test/$@.c $(TEST_SRC) $(CMSIS_SRC) /Fe:$@
	@$@
