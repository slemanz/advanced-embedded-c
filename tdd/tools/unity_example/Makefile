CC= gcc
INCLUDES = -I ../../unity -I src

TEST_DIR = tests
BUILD_DIR = build
UNITY_DIR = ../../unity

TESTS += $(TEST_DIR)/SprintfTest.c 
TESTS += $(TEST_DIR)/SprintfTestRunner.c 

UNITY += $(UNITY_DIR)/unity_fixture.c
UNITY += $(UNITY_DIR)/unity.c

all: test

test: $(TESTS) $(UNITY)
	mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDES) $^ -o $(BUILD_DIR)/run_tests
	./$(BUILD_DIR)/run_tests

clean:
	rm -rf $(BUILD_DIR)/*