CC = gcc
CXX = g++
LD = g++

TEST_DIR = tests
BUILD_DIR = build
UNITY_DIR = ../../unity

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

CFLAGS = -Wall -Wextra -g
CXXFLAGS = $(CFLAGS)
LDFLAGS = -lCppUTest -lCppUTestExt

.PHONY: all clean test

all: test

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

test: $(TEST_OBJS)
	$(LD) -o $(BUILD_DIR)/run_tests $^ $(LDFLAGS)
	$(BUILD_DIR)/run_tests

clean:
	rm -rf $(BUILD_DIR)/*