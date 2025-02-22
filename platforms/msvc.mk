CXX = cl
LD = link

LDFLAGS = /DLL /nologo

STDC_FLAGS =
STDCXX_FLAGS =

INC_FLAGS = $(addprefix /I,$(INCLUDES))
DEF_FLAGS = $(addprefix /D,$(DEFINES))
# OPT_FLAGS = $(addprefix /O,$(OPT_LEVEL))
# WARN_FLAGS = /W4
DEPEND_FLAGS =
EXTRA_FLAGS += /nologo

LDLIBS = $(addprefix /l,$(LIBS))

%.dll: %.cpp.o
	$(info $() $()  LD   $@)
	@$(LD) $(LDFLAGS) $^ /out:$@ $(LDLIBS)

%.cpp.o: %.cpp
	$(info $() $()  CXX  $@)
	@$(CXX) /c $(CXXFLAGS) $^ /Fo$@
