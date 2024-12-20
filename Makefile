CC = gcc
CXX = g++
LD = $(CC)

C_STD = -std=c99
CXX_STD = -std=c++11

INCLUDES = include test
WARN_FLAGS = -Wall -Wextra -pedantic

CFLAGS = $(C_STD) $(addprefix -I,$(INCLUDES)) $(WARN_FLAGS)
CXXFLAGS = $(CXX_STD) $(addprefix -I,$(INCLUDES)) $(WARN_FLAGS)

TEST_SRC = \
	test/print_hist.c \
	test/print_table.c

.PHONY: test cmsis_test
test:
	@$(CXX) $(CXXFLAGS) $@/$@.cpp $(TEST_SRC) -o $@
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
