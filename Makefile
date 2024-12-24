################################################################################
#                              НАСТРОЙКА ПРОЕКТА                               #
################################################################################
PROJECT_NAME = mf
SHARED_LIB = c_wrapper.dll

################################################################################
#                              НАСТРОЙКА ТУЛЧЕЙНА                              #
################################################################################
CC = gcc
CFLAGS = \
	$(DEF_FLAGS) \
	$(DEPEND_FLAGS) \
	$(EXTRA_FLAGS) \
	$(INC_FLAGS) \
	$(OPT_FLAGS) \
	$(WARN_FLAGS) \
	$(STDC_FLAGS)
CXXFLAGS = \
	$(DEF_FLAGS) \
	$(DEPEND_FLAGS) \
	$(EXTRA_FLAGS) \
	$(INC_FLAGS) \
	$(OPT_FLAGS) \
	$(WARN_FLAGS) \
	$(STDCXX_FLAGS)

DEFINES =
INCLUDES = include test
OPT_LEVEL = 3
LIBS =

TEST_SRC = \
	test/print_hist.c \
	test/print_table.c

CMSIS_SRC = \
	CMSIS-DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c \
	CMSIS-DSP/Source/TransformFunctions/arm_cfft_init_f32.c \
	CMSIS-DSP/Source/CommonTables/arm_common_tables.c \
	CMSIS-DSP/Source/CommonTables/arm_const_structs.c \
	CMSIS-DSP/Source/TransformFunctions/arm_bitreversal2.c \
	CMSIS-DSP/Source/TransformFunctions/arm_cfft_f32.c \
	CMSIS-DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c \
	CMSIS-DSP/Source/TransformFunctions/arm_rfft_fast_f32.c

ifeq ($(CC),gcc)
include platforms/gcc.mk
else ifeq ($(CC),clang)
include platforms/clang.mk
else ifeq ($(CC),cl)
include platforms/msvc.mk
else
$(error Unknown compiler!)
endif

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
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.exp,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.lib,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.o,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.obj,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.tds,$(dir))) \
		2> /dev/null ||:
