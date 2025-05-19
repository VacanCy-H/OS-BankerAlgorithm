CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = 

# 源文件路径
SRC_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# 目标可执行文件名称
EXECUTABLE = banker

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
