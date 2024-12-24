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

test:
	@echo '  CXX ' c_wrapper
	@$(CXX) /c $(CXXFLAGS) test/c_wrapper.cpp /Fo:test/c_wrapper.cpp.o
	@echo '  LD  ' c_wrapper
	@$(LD) $(LDFLAGS) /out:$(SHARED_LIB) test/c_wrapper.cpp.o $(LDLIBS)
	@echo '  PY  ' pytest
	@python test/pytest

mf_test:
	@$(CXX) $(CXXFLAGS) test/$@.cpp $(TEST_SRC) -o $@
	@./$@

cmsis_test:
	@$(CC) $(CFLAGS) -ICMSIS-DSP/Include test/$@.c $(TEST_SRC) $(CMSIS_SRC) -o $@
	@./$@
