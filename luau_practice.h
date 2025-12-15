#ifndef LUAU_PRACTICE_H
#define LUAU_PRACTICE_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace LuauPractice {

// Represents a Luau code snippet
struct CodeSnippet {
    std::string title;
    std::string description;
    std::string code;
    std::string category;
    int difficulty; // 1-5
};

// Represents a practice challenge
struct Challenge {
    std::string id;
    std::string title;
    std::string description;
    std::string starterCode;
    std::string solution;
    std::vector<std::string> hints;
    std::string testCases;
    int difficulty;
};

// Syntax highlighter for Luau
class SyntaxHighlighter {
public:
    std::string highlight(const std::string& code);
    void setTheme(const std::string& theme);
    
private:
    std::map<std::string, std::string> keywords;
    std::map<std::string, std::string> robloxAPI;
    void initializeKeywords();
    void initializeRobloxAPI();
};

// Code analyzer
class CodeAnalyzer {
public:
    struct AnalysisResult {
        std::vector<std::string> warnings;
        std::vector<std::string> suggestions;
        std::vector<std::string> errors;
        int complexity;
    };
    
    AnalysisResult analyze(const std::string& code);
    
private:
    bool checkSyntax(const std::string& code);
    std::vector<std::string> findCommonMistakes(const std::string& code);
    int calculateComplexity(const std::string& code);
};

// Challenge manager
class ChallengeManager {
public:
    ChallengeManager();
    void loadChallenges();
    Challenge getChallenge(const std::string& id);
    std::vector<Challenge> getChallengesByDifficulty(int difficulty);
    std::vector<Challenge> getAllChallenges();
    bool validateSolution(const std::string& challengeId, const std::string& code);
    
private:
    std::vector<Challenge> challenges;
    void initializeBuiltInChallenges();
};

// Code snippet library
class SnippetLibrary {
public:
    SnippetLibrary();
    void loadSnippets();
    void addSnippet(const CodeSnippet& snippet);
    std::vector<CodeSnippet> getSnippetsByCategory(const std::string& category);
    std::vector<CodeSnippet> searchSnippets(const std::string& query);
    std::vector<std::string> getCategories();
    
private:
    std::vector<CodeSnippet> snippets;
    void initializeBuiltInSnippets();
};

// User progress tracker
class ProgressTracker {
public:
    struct UserProgress {
        int challengesCompleted;
        int totalChallenges;
        std::vector<std::string> completedChallengeIds;
        int currentStreak;
        std::map<std::string, int> categoryProgress;
    };
    
    void markChallengeComplete(const std::string& challengeId);
    UserProgress getProgress();
    void saveProgress(const std::string& filename);
    void loadProgress(const std::string& filename);
    
private:
    UserProgress progress;
};

// Main application controller
class LuauPracticeApp {
public:
    LuauPracticeApp();
    void run();
    void displayMainMenu();
    void practiceMode();
    void challengeMode();
    void snippetBrowser();
    void analyzeCode();
    void showProgress();
    void showHelp();
    
private:
    SyntaxHighlighter highlighter;
    CodeAnalyzer analyzer;
    ChallengeManager challengeManager;
    SnippetLibrary snippetLibrary;
    ProgressTracker progressTracker;
    
    void clearScreen();
    std::string getUserInput(const std::string& prompt);
    void displayCode(const std::string& code);
};

} // namespace LuauPractice

#endif // LUAU_PRACTICE_H
