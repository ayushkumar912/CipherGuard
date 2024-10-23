# Makefile for DES encryption application

# Variables
CXX = g++
CXXFLAGS = -std=c++11 -I/opt/homebrew/Cellar/openssl@3/3.3.2/include -Iinclude 
LDFLAGS = -L/opt/homebrew/Cellar/openssl@3/3.3.2/lib -lssl -lcrypto
SRC = src/main.cpp src/des_cbc.cpp
TARGET = main

# File paths
DATA_DIR = data
ORIGINAL_FILE = $(DATA_DIR)/data.txt
ENCRYPTED_FILE = $(DATA_DIR)/encrypted.txt
DECRYPTED_FILE = $(DATA_DIR)/decrypted.txt

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean up build files and data files
clean:  # Changed Clean to clean
	rm -f $(TARGET) $(ORIGINAL_FILE) $(ENCRYPTED_FILE) $(DECRYPTED_FILE)

# Phony targets
.PHONY: all clean
