CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./deps/saci-tests
LDLIBS = 

DEPS_DIR = ./deps/saci-tests
DEPS_SRCS = $(wildcard $(DEPS_DIR)/*.c)
DEPS_OBJS = $(patsubst $(DEPS_DIR)/%.c, $(OUT_DIR)/%.o, $(DEPS_SRCS))

TEST_SRCS = $(wildcard *.c)
TEST_EXES = $(patsubst %.c, $(OUT_DIR)/%, $(TEST_SRCS))

OUT_DIR = ./build

.PHONY: all clean

all: $(DEPS_OBJS) $(TEST_EXES)
	@for test in $(TEST_EXES); do \
		echo "Running $$test..."; \
		$$test || exit 1; \
	done

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: $(DEPS_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%: %.c $(DEPS_OBJS) | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(DEPS_OBJS) $(LDLIBS)

clean:
	rm -rf $(OUT_DIR)
