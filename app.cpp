#include "../include/luau_practice.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <algorithm>

namespace LuauPractice {

// ============================================================================
// LuauPracticeApp Implementation
// ============================================================================

LuauPracticeApp::LuauPracticeApp() {
    challengeManager.loadChallenges();
    snippetLibrary.loadSnippets();
    progressTracker.loadProgress("progress.dat");
}

void LuauPracticeApp::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string LuauPracticeApp::getUserInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void LuauPracticeApp::displayCode(const std::string& code) {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << highlighter.highlight(code) << "\n";
    std::cout << std::string(70, '=') << "\n";
}

void LuauPracticeApp::displayMainMenu() {
    clearScreen();
    std::cout << "\033[1;36m";
    std::cout << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║      █░░ █░█ ▄▀█ █░█   █▀█ █▀█ ▄▀█ █▀▀ ▀█▀ █ █▀▀ █▀▀       ║
    ║      █▄▄ █▄█ █▀█ █▄█   █▀▀ █▀▄ █▀█ █▄▄ ░█░ █ █▄▄ ██▄       ║
    ║                                                               ║
    ║           Roblox Luau Scripting Practice Platform            ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝
)" << "\033[0m\n";

    auto progress = progressTracker.getProgress();
    std::cout << "\n  \033[1;33m📊 Progress: " << progress.challengesCompleted 
              << " challenges completed\033[0m\n\n";
    
    std::cout << "  \033[1;32m╔════════════════════════════════════════════════════════╗\033[0m\n";
    std::cout << "  \033[1;32m║                      MAIN MENU                         ║\033[0m\n";
    std::cout << "  \033[1;32m╠════════════════════════════════════════════════════════╣\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  1. 📝 Practice Mode (Free Coding)                     \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  2. 🎯 Challenge Mode (Guided Challenges)              \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  3. 📚 Code Snippet Library                            \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  4. 🔍 Code Analyzer                                   \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  5. 📈 View Progress                                   \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  6. ❓ Help & Documentation                            \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m║\033[0m  7. 🚪 Exit                                            \033[1;32m║\033[0m\n";
    std::cout << "  \033[1;32m╚════════════════════════════════════════════════════════╝\033[0m\n\n";
}

void LuauPracticeApp::practiceMode() {
    clearScreen();
    std::cout << "\033[1;36m=== PRACTICE MODE ===\033[0m\n\n";
    std::cout << "Enter your Luau code below. Type 'END' on a new line when finished.\n";
    std::cout << "Type 'ANALYZE' to analyze your code.\n";
    std::cout << "Type 'BACK' to return to main menu.\n\n";
    
    std::string code;
    std::string line;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        if (line == "END") {
            if (!code.empty()) {
                std::cout << "\n\033[1;32m✓ Code saved!\033[0m\n";
                displayCode(code);
                std::cout << "\nWhat would you like to do?\n";
                std::cout << "1. Analyze code\n";
                std::cout << "2. Start new code\n";
                std::cout << "3. Back to menu\n";
                
                std::string choice = getUserInput("\nChoice: ");
                if (choice == "1") {
                    auto result = analyzer.analyze(code);
                    
                    std::cout << "\n\033[1;36m=== ANALYSIS RESULTS ===\033[0m\n";
                    std::cout << "Complexity Score: " << result.complexity << "\n\n";
                    
                    if (!result.errors.empty()) {
                        std::cout << "\033[1;31m❌ Errors:\033[0m\n";
                        for (const auto& error : result.errors) {
                            std::cout << "  • " << error << "\n";
                        }
                        std::cout << "\n";
                    }
                    
                    if (!result.warnings.empty()) {
                        std::cout << "\033[1;33m⚠️  Warnings:\033[0m\n";
                        for (const auto& warning : result.warnings) {
                            std::cout << "  • " << warning << "\n";
                        }
                        std::cout << "\n";
                    }
                    
                    if (!result.suggestions.empty()) {
                        std::cout << "\033[1;34m💡 Suggestions:\033[0m\n";
                        for (const auto& suggestion : result.suggestions) {
                            std::cout << "  • " << suggestion << "\n";
                        }
                        std::cout << "\n";
                    }
                    
                    if (result.errors.empty() && result.warnings.empty()) {
                        std::cout << "\033[1;32m✓ No issues found! Great job!\033[0m\n\n";
                    }
                    
                    getUserInput("Press Enter to continue...");
                }
                code.clear();
            }
            break;
        } else if (line == "BACK") {
            break;
        } else if (line == "ANALYZE" && !code.empty()) {
            auto result = analyzer.analyze(code);
            std::cout << "\n\033[1;36mQuick Analysis:\033[0m Complexity: " << result.complexity;
            if (!result.warnings.empty()) {
                std::cout << ", " << result.warnings.size() << " warning(s)";
            }
            std::cout << "\n";
        } else {
            code += line + "\n";
        }
    }
}

void LuauPracticeApp::challengeMode() {
    while (true) {
        clearScreen();
        std::cout << "\033[1;36m=== CHALLENGE MODE ===\033[0m\n\n";
        
        auto challenges = challengeManager.getAllChallenges();
        auto progress = progressTracker.getProgress();
        
        std::cout << "Select difficulty level:\n";
        std::cout << "  1. ⭐ Beginner (Difficulty 1-2)\n";
        std::cout << "  2. ⭐⭐ Intermediate (Difficulty 3-4)\n";
        std::cout << "  3. ⭐⭐⭐ Advanced (Difficulty 5)\n";
        std::cout << "  4. 📋 View all challenges\n";
        std::cout << "  5. ← Back to main menu\n\n";
        
        std::string choice = getUserInput("Choice: ");
        
        if (choice == "5") {
            break;
        }
        
        std::vector<Challenge> filteredChallenges;
        
        if (choice == "1") {
            for (const auto& c : challenges) {
                if (c.difficulty <= 2) filteredChallenges.push_back(c);
            }
        } else if (choice == "2") {
            for (const auto& c : challenges) {
                if (c.difficulty >= 3 && c.difficulty <= 4) filteredChallenges.push_back(c);
            }
        } else if (choice == "3") {
            for (const auto& c : challenges) {
                if (c.difficulty == 5) filteredChallenges.push_back(c);
            }
        } else if (choice == "4") {
            filteredChallenges = challenges;
        } else {
            continue;
        }
        
        clearScreen();
        std::cout << "\033[1;36m=== AVAILABLE CHALLENGES ===\033[0m\n\n";
        
        for (size_t i = 0; i < filteredChallenges.size(); i++) {
            bool completed = std::find(progress.completedChallengeIds.begin(),
                                      progress.completedChallengeIds.end(),
                                      filteredChallenges[i].id) != progress.completedChallengeIds.end();
            
            std::cout << "  " << (i + 1) << ". ";
            if (completed) std::cout << "\033[1;32m✓\033[0m ";
            std::cout << filteredChallenges[i].title;
            std::cout << " ";
            for (int j = 0; j < filteredChallenges[i].difficulty; j++) {
                std::cout << "⭐";
            }
            std::cout << "\n     " << filteredChallenges[i].description << "\n\n";
        }
        
        std::cout << "  0. ← Back\n\n";
        
        std::string challengeChoice = getUserInput("Select challenge: ");
        
        if (challengeChoice == "0") {
            continue;
        }
        
        int idx = std::stoi(challengeChoice) - 1;
        if (idx >= 0 && idx < static_cast<int>(filteredChallenges.size())) {
            Challenge selectedChallenge = filteredChallenges[idx];
            
            clearScreen();
            std::cout << "\033[1;36m=== " << selectedChallenge.title << " ===\033[0m\n\n";
            std::cout << "📝 Description: " << selectedChallenge.description << "\n";
            std::cout << "⭐ Difficulty: " << selectedChallenge.difficulty << "\n\n";
            
            std::cout << "Starter Code:\n";
            displayCode(selectedChallenge.starterCode);
            
            std::cout << "\nOptions:\n";
            std::cout << "  1. 💻 Start coding\n";
            std::cout << "  2. 💡 Show hints\n";
            std::cout << "  3. 🔍 Show solution\n";
            std::cout << "  4. ← Back\n\n";
            
            std::string optionChoice = getUserInput("Choice: ");
            
            if (optionChoice == "1") {
                std::cout << "\n\033[1;33mEnter your solution (type 'END' when done):\033[0m\n\n";
                
                std::string solution;
                std::string line;
                
                while (true) {
                    std::cout << "> ";
                    std::getline(std::cin, line);
                    
                    if (line == "END") {
                        break;
                    }
                    solution += line + "\n";
                }
                
                if (challengeManager.validateSolution(selectedChallenge.id, solution)) {
                    std::cout << "\n\033[1;32m🎉 Correct! Challenge completed!\033[0m\n";
                    progressTracker.markChallengeComplete(selectedChallenge.id);
                    progressTracker.saveProgress("progress.dat");
                } else {
                    std::cout << "\n\033[1;33m⚠️  Not quite right. Try again or check the hints!\033[0m\n";
                }
                
                getUserInput("\nPress Enter to continue...");
                
            } else if (optionChoice == "2") {
                std::cout << "\n\033[1;34m💡 Hints:\033[0m\n";
                for (size_t i = 0; i < selectedChallenge.hints.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << selectedChallenge.hints[i] << "\n";
                }
                getUserInput("\nPress Enter to continue...");
                
            } else if (optionChoice == "3") {
                std::cout << "\n\033[1;35m🔍 Solution:\033[0m\n";
                displayCode(selectedChallenge.solution);
                getUserInput("\nPress Enter to continue...");
            }
        }
    }
}

void LuauPracticeApp::snippetBrowser() {
    while (true) {
        clearScreen();
        std::cout << "\033[1;36m=== CODE SNIPPET LIBRARY ===\033[0m\n\n";
        
        auto categories = snippetLibrary.getCategories();
        
        std::cout << "Browse by category:\n";
        for (size_t i = 0; i < categories.size(); i++) {
            std::cout << "  " << (i + 1) << ". " << categories[i] << "\n";
        }
        std::cout << "  " << (categories.size() + 1) << ". 🔍 Search snippets\n";
        std::cout << "  0. ← Back to main menu\n\n";
        
        std::string choice = getUserInput("Choice: ");
        
        if (choice == "0") {
            break;
        }
        
        int idx = std::stoi(choice) - 1;
        
        if (idx >= 0 && idx < static_cast<int>(categories.size())) {
            auto snippets = snippetLibrary.getSnippetsByCategory(categories[idx]);
            
            clearScreen();
            std::cout << "\033[1;36m=== " << categories[idx] << " Snippets ===\033[0m\n\n";
            
            for (size_t i = 0; i < snippets.size(); i++) {
                std::cout << "  " << (i + 1) << ". " << snippets[i].title << "\n";
                std::cout << "     " << snippets[i].description << "\n\n";
            }
            
            std::cout << "  0. ← Back\n\n";
            
            std::string snippetChoice = getUserInput("Select snippet to view: ");
            
            if (snippetChoice != "0") {
                int snippetIdx = std::stoi(snippetChoice) - 1;
                if (snippetIdx >= 0 && snippetIdx < static_cast<int>(snippets.size())) {
                    clearScreen();
                    std::cout << "\033[1;36m=== " << snippets[snippetIdx].title << " ===\033[0m\n";
                    std::cout << snippets[snippetIdx].description << "\n";
                    displayCode(snippets[snippetIdx].code);
                    getUserInput("\nPress Enter to continue...");
                }
            }
            
        } else if (choice == std::to_string(categories.size() + 1)) {
            std::string query = getUserInput("\nEnter search term: ");
            auto results = snippetLibrary.searchSnippets(query);
            
            if (results.empty()) {
                std::cout << "\n\033[1;33mNo snippets found matching '" << query << "'\033[0m\n";
                getUserInput("Press Enter to continue...");
            } else {
                clearScreen();
                std::cout << "\033[1;36m=== Search Results for '" << query << "' ===\033[0m\n\n";
                
                for (size_t i = 0; i < results.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << results[i].title << "\n";
                    std::cout << "     " << results[i].description << "\n\n";
                }
                
                getUserInput("Press Enter to continue...");
            }
        }
    }
}

void LuauPracticeApp::analyzeCode() {
    clearScreen();
    std::cout << "\033[1;36m=== CODE ANALYZER ===\033[0m\n\n";
    std::cout << "Enter your Luau code. Type 'END' on a new line when finished.\n\n";
    
    std::string code;
    std::string line;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        
        if (line == "END") {
            break;
        }
        code += line + "\n";
    }
    
    if (!code.empty()) {
        auto result = analyzer.analyze(code);
        
        std::cout << "\n\033[1;36m╔════════════════════════════════════════════╗\033[0m\n";
        std::cout << "\033[1;36m║         ANALYSIS RESULTS                   ║\033[0m\n";
        std::cout << "\033[1;36m╚════════════════════════════════════════════╝\033[0m\n\n";
        
        std::cout << "📊 Complexity Score: " << result.complexity << "\n\n";
        
        if (!result.errors.empty()) {
            std::cout << "\033[1;31m❌ ERRORS (" << result.errors.size() << "):\033[0m\n";
            for (const auto& error : result.errors) {
                std::cout << "  • " << error << "\n";
            }
            std::cout << "\n";
        }
        
        if (!result.warnings.empty()) {
            std::cout << "\033[1;33m⚠️  WARNINGS (" << result.warnings.size() << "):\033[0m\n";
            for (const auto& warning : result.warnings) {
                std::cout << "  • " << warning << "\n";
            }
            std::cout << "\n";
        }
        
        if (!result.suggestions.empty()) {
            std::cout << "\033[1;34m💡 SUGGESTIONS (" << result.suggestions.size() << "):\033[0m\n";
            for (const auto& suggestion : result.suggestions) {
                std::cout << "  • " << suggestion << "\n";
            }
            std::cout << "\n";
        }
        
        if (result.errors.empty() && result.warnings.empty()) {
            std::cout << "\033[1;32m✓ Excellent! No issues found!\033[0m\n\n";
        }
    }
    
    getUserInput("Press Enter to continue...");
}

void LuauPracticeApp::showProgress() {
    clearScreen();
    auto progress = progressTracker.getProgress();
    
    std::cout << "\033[1;36m=== YOUR PROGRESS ===\033[0m\n\n";
    std::cout << "📊 Challenges Completed: " << progress.challengesCompleted << "\n";
    std::cout << "🎯 Total Challenges: " << challengeManager.getAllChallenges().size() << "\n\n";
    
    double percentage = (progress.challengesCompleted * 100.0) / challengeManager.getAllChallenges().size();
    std::cout << "Progress: [";
    int bars = static_cast<int>(percentage / 2);
    for (int i = 0; i < 50; i++) {
        if (i < bars) std::cout << "█";
        else std::cout << "░";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << percentage << "%\n\n";
    
    if (!progress.completedChallengeIds.empty()) {
        std::cout << "\033[1;32m✓ Completed Challenges:\033[0m\n";
        for (const auto& id : progress.completedChallengeIds) {
            auto challenge = challengeManager.getChallenge(id);
            std::cout << "  • " << challenge.title << "\n";
        }
        std::cout << "\n";
    }
    
    getUserInput("Press Enter to continue...");
}

void LuauPracticeApp::showHelp() {
    clearScreen();
    std::cout << "\033[1;36m=== HELP & DOCUMENTATION ===\033[0m\n\n";
    
    std::cout << "📚 \033[1;33mLuau Basics:\033[0m\n";
    std::cout << "  • Variables: local myVar = 10\n";
    std::cout << "  • Functions: local function myFunc() end\n";
    std::cout << "  • Conditionals: if condition then ... end\n";
    std::cout << "  • Loops: for i = 1, 10 do ... end\n";
    std::cout << "  • Tables: local myTable = {1, 2, 3}\n\n";
    
    std::cout << "🎮 \033[1;33mCommon Roblox Objects:\033[0m\n";
    std::cout << "  • workspace: The 3D game world\n";
    std::cout << "  • game.Players: Player management\n";
    std::cout << "  • ReplicatedStorage: Shared objects\n";
    std::cout << "  • ServerScriptService: Server-side scripts\n\n";
    
    std::cout << "💡 \033[1;33mUseful Functions:\033[0m\n";
    std::cout << "  • print(message): Output to console\n";
    std::cout << "  • wait(seconds): Pause execution\n";
    std::cout << "  • Instance.new(className): Create object\n";
    std::cout << "  • :Connect(function): Connect to events\n\n";
    
    std::cout << "🔗 \033[1;33mResources:\033[0m\n";
    std::cout << "  • Roblox Developer Hub: https://create.roblox.com/docs\n";
    std::cout << "  • Luau Documentation: https://luau-lang.org\n";
    std::cout << "  • DevForum: https://devforum.roblox.com\n\n";
    
    getUserInput("Press Enter to continue...");
}

void LuauPracticeApp::run() {
    bool running = true;
    
    while (running) {
        displayMainMenu();
        std::string choice = getUserInput("Enter your choice: ");
        
        if (choice == "1") {
            practiceMode();
        } else if (choice == "2") {
            challengeMode();
        } else if (choice == "3") {
            snippetBrowser();
        } else if (choice == "4") {
            analyzeCode();
        } else if (choice == "5") {
            showProgress();
        } else if (choice == "6") {
            showHelp();
        } else if (choice == "7") {
            clearScreen();
            std::cout << "\n\033[1;36mThank you for using Luau Practice!\033[0m\n";
            std::cout << "Keep coding and happy developing! 🚀\n\n";
            running = false;
        } else {
            std::cout << "\n\033[1;31mInvalid choice. Please try again.\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

} // namespace LuauPractice
