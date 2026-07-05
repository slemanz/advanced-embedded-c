CC= gcc
CXX = g++
LD = g++

CFLAGS = -c -Wall -O0
LDFLAGS = -lCppUTest -lCppUTestExt

BUILD_DIR 	= build
TEST_DIR 	= tests
SRC_DIR 	= src

INCLUDES += -I tests
INCLUDES += -I src

#SRC 	+= $(BUILD_DIR)/LedDriver.o

TESTS 	+= $(BUILD_DIR)/AllTests.o
TESTS 	+= $(BUILD_DIR)/LightControllerSpy.o
TESTS 	+= $(BUILD_DIR)/LightControllerSpyTest.o


all: $(BUILD_DIR) test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TEST_DIR)/$(*).cpp

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TEST_DIR)/$(*).c

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(UNITY_DIR)/$(*).c

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(SRC_DIR)/$(*).c

test: $(TESTS) $(SRC)
	$(LD) $^ -o $(BUILD_DIR)/run_tests $(LDFLAGS) 
	./$(BUILD_DIR)/run_tests


clean:
	rm -rf $(BUILD_DIR)/*