CC= gcc
CFLAGS = -c -Wall -std=gnu99 -O0

BUILD_DIR 	= build
TEST_DIR 	= tests
UNITY_DIR 	= ../unity
SRC_DIR 	= src

INCLUDES += -I ../unity
INCLUDES += -I tests
INCLUDES += -I src

SRC 	+= $(BUILD_DIR)/LedDriver.o

TESTS 	+= $(BUILD_DIR)/LedDriverTests.o
TESTS 	+= $(BUILD_DIR)/AllTestRunner.o

UNITY 	+= $(BUILD_DIR)/unity_fixture.o
UNITY 	+= $(BUILD_DIR)/unity.o

all: $(BUILD_DIR) test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TEST_DIR)/$(*).c

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(UNITY_DIR)/$(*).c

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(SRC_DIR)/$(*).c

test: $(TESTS) $(UNITY) $(SRC)
	$(CC) $^ -o $(BUILD_DIR)/run_tests
	./$(BUILD_DIR)/run_tests


clean:
	rm -rf $(BUILD_DIR)/*