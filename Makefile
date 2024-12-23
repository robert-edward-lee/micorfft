PROJECT_NAME = mf
SHARED_LIB = c_wrapper.dll

CC = gcc
CXX = g++
LD = $(CC)

C_STD = -std=c99
CXX_STD = -std=c++11

DEFINES =
INCLUDES = include test
OPT_LEVEL = 3
WARN_FLAGS = -Wall -Wextra -pedantic
LIBS =

CFLAGS = \
	$(addprefix -D,$(DEFINES)) \
	$(addprefix -I,$(INCLUDES)) \
	$(addprefix -O,$(OPT_LEVEL)) \
	$(WARN_FLAGS) \
	$(C_STD)
CXXFLAGS = \
	$(addprefix -D,$(DEFINES)) \
	$(addprefix -I,$(INCLUDES)) \
	$(addprefix -O,$(OPT_LEVEL)) \
	$(WARN_FLAGS) \
	$(CXX_STD)
LDFLAGS = -shared \
	$(addprefix -l,$(LIBS))

TEST_SRC = \
	test/print_hist.c \
	test/print_table.c

.PHONY: test mf_test cmsis_test

test:
	@echo '  CXX ' c_wrapper
	@$(CXX) -c $(CXXFLAGS) test/c_wrapper.cpp -o test/c_wrapper.cpp.o
	@echo '  LD  ' c_wrapper
	@$(LD) $(LDFLAGS) -o $(SHARED_LIB) test/c_wrapper.cpp.o $(LDLIBS)
	@echo '  PY  ' pytest
	@python test/pytest

mf_test:
	@$(CXX) $(CXXFLAGS) test/$@.cpp $(TEST_SRC) -o $@
	@./$@

CMSIS_SRC = \
	CMSIS-DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c \
	CMSIS-DSP/Source/TransformFunctions/arm_cfft_init_f32.c \
	CMSIS-DSP/Source/CommonTables/arm_common_tables.c \
	CMSIS-DSP/Source/CommonTables/arm_const_structs.c \
	CMSIS-DSP/Source/TransformFunctions/arm_bitreversal2.c \
	CMSIS-DSP/Source/TransformFunctions/arm_cfft_f32.c \
	CMSIS-DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c \
	CMSIS-DSP/Source/TransformFunctions/arm_rfft_fast_f32.c

cmsis_test:
	@$(CC) $(CFLAGS) $(addprefix -D,$(CMSIS_DEFS)) -ICMSIS-DSP/Include test/$@.c $(TEST_SRC) $(CMSIS_SRC) -o $@
	@./$@

WORK_DIRS = . test include include/mf include/mf/utils

format:
	@clang-format -style=file:./.clang-format -i \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.c,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.cpp,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.h,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.hpp,$(dir))) \
		2> /dev/null ||:

clean:
	@$(RM) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.a,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.d,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.dll,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.exe,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.o,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.obj,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.tds,$(dir))) \
		2> /dev/null ||:
