################################################################################
#                              НАСТРОЙКА ПРОЕКТА                               #
################################################################################
PROJECT_NAME = mf

PYTEST_DIR = pytest_modules
PYTESTS = $(basename $(notdir $(wildcard $(PYTEST_DIR)/*.py)))
TESTS = $(addprefix c_wrapper_,$(PYTESTS))
TEST_SRCS = $(addsuffix .cpp,$(TESTS))
TEST_OBJS = $(addsuffix .o,$(TEST_SRCS))
TEST_LIBS = $(addsuffix .dll,$(TESTS))

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

ifeq ($(CC),gcc)
include platforms/gcc.mk
else ifeq ($(CC),clang)
include platforms/clang.mk
else ifeq ($(CC),cl)
include platforms/msvc.mk
else
$(error Unknown compiler!)
endif

WORK_DIRS = . test include include/mf/* include/mf/*/*

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
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.log,$(dir))) \
		c_wrapper* 2> /dev/null ||:

test: gen_test run_test

run_test: build_test
	$(info $() $()  PY   pytest)
	@python pytest -r

build_test: gen_test $(TEST_LIBS)

gen_test:
	$(info $() $()  GEN  c_wrappers)
	@python pytest -g
