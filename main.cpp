#include "../include/luau_practice.h"
#include <iostream>

int main() {
    try {
        LuauPractice::LuauPracticeApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
