# 🎮 Luau Roblox Practice

A comprehensive C++ desktop application for learning and practicing Luau scripting for Roblox game development.

![Version](https://img.shields.io/badge/version-1.0-blue)
![C++](https://img.shields.io/badge/C++-17-green)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

## 📋 Features

### 🎯 Challenge Mode
- **10 Built-in Challenges** ranging from beginner to advanced
- Progressive difficulty levels (⭐ to ⭐⭐⭐)
- Hint system for guidance
- Solution validation
- Progress tracking

### 📝 Practice Mode
- Free-form coding environment
- Real-time syntax highlighting
- Code analysis on demand
- Save and review your code

### 📚 Code Snippet Library
- Pre-built code snippets organized by category:
  - Basics (Parts, Print statements)
  - Events (Touch detection, Player events)
  - Functions (Templates and examples)
  - Animation (TweenService examples)
  - Networking (RemoteEvents)
  - Data (DataStore operations)
  - GUI (User interface interactions)
- Search functionality
- Easy copy and reference

### 🔍 Code Analyzer
- **Syntax Checking**: Validates Luau syntax
- **Complexity Analysis**: Calculates code complexity scores
- **Best Practices**: Suggests improvements
- **Common Mistakes**: Identifies typical errors
- **Roblox-Specific Checks**: Validates proper API usage

### 📊 Progress Tracking
- Track completed challenges
- Visual progress indicators
- Achievement system
- Persistent progress saving

### 🎨 Syntax Highlighting
- Color-coded Luau keywords
- Roblox API highlighting
- String and comment formatting
- Number highlighting

## 🚀 Getting Started

### Prerequisites

- **C++ Compiler**: g++ (GCC 7.0+) or MSVC (Visual Studio 2017+)
- **CMake**: Version 3.10 or higher (optional)
- **Make**: For Unix-like systems (optional)

### Installation

#### Method 1: Using Make (Linux/macOS)

```bash
# Clone or extract the project
cd LuauRobloxPractice

# Build the project
make

# Run the application
./luau_practice
```

#### Method 2: Using CMake (All platforms)

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the application
./luau_practice
```

#### Method 3: Manual Compilation

```bash
# Compile all source files
g++ -std=c++17 -Iinclude src/main.cpp src/luau_practice.cpp src/app.cpp -o luau_practice

# Run the application
./luau_practice
```

#### Windows (Visual Studio)

```cmd
# Using MSVC compiler
cl /EHsc /std:c++17 /I include src\main.cpp src\luau_practice.cpp src\app.cpp /Fe:luau_practice.exe

# Run
luau_practice.exe
```

## 📖 Usage Guide

### Main Menu Options

1. **📝 Practice Mode**: Free coding environment with syntax highlighting
2. **🎯 Challenge Mode**: Guided challenges with difficulty levels
3. **📚 Code Snippet Library**: Browse and search code examples
4. **🔍 Code Analyzer**: Analyze your code for issues and improvements
5. **📈 View Progress**: Track your learning journey
6. **❓ Help & Documentation**: Quick reference guide
7. **🚪 Exit**: Close the application

### Challenge Difficulty Levels

- **⭐ Beginner (1-2)**: Basic syntax, simple objects, and fundamental concepts
- **⭐⭐ Intermediate (3-4)**: Events, functions, tables, and API usage
- **⭐⭐⭐ Advanced (5)**: Complex systems, data persistence, and advanced patterns

### Code Analysis Features

The analyzer checks for:
- ✅ Syntax correctness
- ⚠️ Common mistakes (assignment vs comparison, etc.)
- 💡 Best practice suggestions
- 🔧 Roblox-specific optimizations
- 📊 Code complexity metrics

## 🎓 Learning Path

### Recommended Challenge Order

1. **Hello Roblox** - Print basics
2. **Create a Part** - Instance creation
3. **Colorful Part** - Object properties
4. **Count to 10** - Loops
5. **Greet Function** - Functions
6. **Table Operations** - Data structures
7. **Touch Detector** - Events
8. **Player Detector** - Character detection
9. **Smooth Movement** - TweenService
10. **Damage System** - Advanced functions

## 📂 Project Structure

```
LuauRobloxPractice/
├── include/
│   └── luau_practice.h          # Header file with class declarations
├── src/
│   ├── main.cpp                 # Entry point
│   ├── luau_practice.cpp        # Core implementations
│   └── app.cpp                  # Application UI and logic
├── examples/                     # Example code directory
├── challenges/                   # Challenge definitions
├── CMakeLists.txt               # CMake configuration
├── Makefile                     # Make configuration
└── README.md                    # This file
```

## 🎨 Features Breakdown

### Syntax Highlighter
```cpp
- Keywords (if, for, function, etc.): Magenta
- Roblox API (Instance, workspace, etc.): Cyan
- Strings: Green
- Comments: Gray
- Numbers: Yellow
```

### Code Snippets Categories
- **Basics**: Fundamental Roblox scripting
- **Events**: Event handling and connections
- **Functions**: Function templates and examples
- **Animation**: TweenService and motion
- **Networking**: RemoteEvents and RemoteFunctions
- **Data**: DataStore operations
- **GUI**: User interface scripting

## 🔧 Advanced Features

### Custom Challenges
You can extend the application by adding custom challenges in the `initializeBuiltInChallenges()` method.

### Progress Persistence
Progress is automatically saved to `progress.dat` and loaded on startup.

### Extensibility
The modular design allows easy addition of:
- New challenge categories
- Additional code snippets
- Custom analysis rules
- Enhanced syntax highlighting themes

## 🐛 Troubleshooting

### Common Issues

**Issue**: Compiler errors about C++17 features
- **Solution**: Ensure your compiler supports C++17 and use `-std=c++17` flag

**Issue**: Terminal colors not displaying correctly
- **Solution**: Use a terminal that supports ANSI color codes (most modern terminals do)

**Issue**: Progress file not saving
- **Solution**: Ensure the application has write permissions in its directory

## 🤝 Contributing

Suggestions for improvements:
1. Add more challenges
2. Expand snippet library
3. Improve code analysis rules
4. Add new learning resources
5. Enhance UI/UX

## 📚 Learning Resources

- **Roblox Creator Hub**: https://create.roblox.com/docs
- **Luau Language**: https://luau-lang.org
- **Roblox DevForum**: https://devforum.roblox.com
- **Roblox API Reference**: https://create.roblox.com/docs/reference/engine

## 📝 Tips for Learning

1. **Start with challenges** - They provide structured learning
2. **Use the snippet library** - Learn from working examples
3. **Analyze your code** - Get feedback on your coding style
4. **Practice regularly** - Use practice mode to experiment
5. **Read the help** - Quick reference for common patterns

## 🎯 Future Enhancements

Potential features for future versions:
- [ ] Code execution simulation
- [ ] Interactive tutorials
- [ ] Multiplayer challenge mode
- [ ] Code sharing and export
- [ ] Custom challenge creator
- [ ] Achievement badges
- [ ] Learning statistics and analytics

## ⚖️ License

This is an educational project for learning Luau and Roblox scripting.

## 🙏 Acknowledgments

- Roblox Corporation for Luau language
- The Roblox developer community
- All contributors to Roblox documentation

## 📞 Support

For issues, questions, or suggestions:
- Review the help section in the application
- Check Roblox documentation
- Visit the Roblox DevForum

---

**Happy Coding! 🚀**

Made with BenBenSIKI for aspiring Roblox developers
