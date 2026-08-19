CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

TARGET := matchingEngine
SRCS := main.cpp
HEADERS := order.h trade.h orderbook.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)