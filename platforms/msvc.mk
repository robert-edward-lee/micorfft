CXX = cl
LD = link

LDFLAGS = /DLL /nologo

STDC_FLAGS =
STDCXX_FLAGS =

INC_FLAGS = $(addprefix /I,$(INCLUDES))
DEF_FLAGS = $(addprefix /D,$(DEFINES))
# OPT_FLAGS = $(addprefix /O,$(OPT_LEVEL))
WARN_FLAGS = /W4
DEPEND_FLAGS =
EXTRA_FLAGS = /nologo

LDLIBS = $(addprefix /l,$(LIBS))

.PHONY: test mf_test cmsis_test

build_test: gen_test
	@echo '  CXX ' c_wrapper
	@$(CXX) /c $(CXXFLAGS) c_wrapper.cpp
	@echo '  LD  ' c_wrapper
	@$(LD) $(LDFLAGS) /out:$(SHARED_LIB) c_wrapper.obj $(LDLIBS)

mf_test:
	@$(CXX) $(CXXFLAGS) test/$@.cpp $(TEST_SRC) -o $@
	@./$@

cmsis_test:
	@$(CC) $(CFLAGS) -ICMSIS-DSP/Include test/$@.c $(TEST_SRC) $(CMSIS_SRC) -o $@
	@./$@
