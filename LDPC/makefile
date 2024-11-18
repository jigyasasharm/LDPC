CXX = clang++
CXXFLAGS = -std=gnu++14 -Wall -g -Iinclude
SRCDIR = src
INCDIR = include
TARGET = main

all: $(TARGET)

$(TARGET): main.cpp $(SRCDIR)/ldpc_matrix.cpp $(SRCDIR)/awgn_channel.cpp $(SRCDIR)/ldpc_decoder.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp $(SRCDIR)/ldpc_matrix.cpp $(SRCDIR)/awgn_channel.cpp $(SRCDIR)/ldpc_decoder.cpp

clean:
	rm -f $(TARGET)
