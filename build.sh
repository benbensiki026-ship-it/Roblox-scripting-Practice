#!/bin/bash
# Build script for Linux/macOS

echo "========================================"
echo " Luau Roblox Practice - Build Script"
echo "========================================"
echo ""

# Check if g++ is available
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ compiler not found!"
    echo "Please install g++ (e.g., sudo apt install g++ on Ubuntu)"
    exit 1
fi

echo "Building project..."
echo ""

# Create build directory if it doesn't exist
mkdir -p build

# Compile the project
g++ -std=c++17 -Wall -Wextra -Iinclude \
    src/main.cpp \
    src/luau_practice.cpp \
    src/app.cpp \
    -o luau_practice

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo ""
    echo "========================================"
    echo " Build successful!"
    echo "========================================"
    echo ""
    echo "Run the program with: ./luau_practice"
    echo ""
    
    # Make executable
    chmod +x luau_practice
else
    echo ""
    echo "========================================"
    echo " Build failed!"
    echo "========================================"
    echo ""
    exit 1
fi
