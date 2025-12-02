CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/database.cpp \
       $(SRC_DIR)/record.cpp \
       $(SRC_DIR)/table.cpp \
	   $(SRC_DIR)/UI.cpp \
       main.cpp

OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
