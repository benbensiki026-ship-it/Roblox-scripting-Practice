#include "../include/luau_practice.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <regex>
#include <iomanip>

namespace LuauPractice {

// ============================================================================
// SyntaxHighlighter Implementation
// ============================================================================

void SyntaxHighlighter::initializeKeywords() {
    // Luau keywords
    std::vector<std::string> kwList = {
        "and", "break", "do", "else", "elseif", "end", "false", "for", "function",
        "if", "in", "local", "nil", "not", "or", "repeat", "return", "then",
        "true", "until", "while", "continue", "export", "type"
    };
    
    for (const auto& kw : kwList) {
        keywords[kw] = "\033[1;35m" + kw + "\033[0m"; // Magenta
    }
}

void SyntaxHighlighter::initializeRobloxAPI() {
    // Common Roblox API elements
    std::vector<std::string> apiList = {
        "Instance", "Vector3", "CFrame", "Color3", "UDim2", "Enum",
        "workspace", "game", "script", "print", "warn", "wait",
        "Part", "Model", "Workspace", "Players", "ReplicatedStorage",
        "ServerScriptService", "StarterPlayer", "Humanoid"
    };
    
    for (const auto& api : apiList) {
        robloxAPI[api] = "\033[1;36m" + api + "\033[0m"; // Cyan
    }
}

std::string SyntaxHighlighter::highlight(const std::string& code) {
    if (keywords.empty()) initializeKeywords();
    if (robloxAPI.empty()) initializeRobloxAPI();
    
    std::string result = code;
    
    // Highlight keywords
    for (const auto& [keyword, colored] : keywords) {
        std::regex wordRegex("\\b" + keyword + "\\b");
        result = std::regex_replace(result, wordRegex, colored);
    }
    
    // Highlight Roblox API
    for (const auto& [api, colored] : robloxAPI) {
        std::regex wordRegex("\\b" + api + "\\b");
        result = std::regex_replace(result, wordRegex, colored);
    }
    
    // Highlight strings
    std::regex stringRegex("\"([^\"]*)\"");
    result = std::regex_replace(result, stringRegex, "\033[1;32m\"$1\"\033[0m");
    
    // Highlight comments
    std::regex commentRegex("--(.*)$");
    result = std::regex_replace(result, commentRegex, "\033[2;37m--$1\033[0m");
    
    // Highlight numbers
    std::regex numberRegex("\\b([0-9]+\\.?[0-9]*)\\b");
    result = std::regex_replace(result, numberRegex, "\033[1;33m$1\033[0m");
    
    return result;
}

void SyntaxHighlighter::setTheme(const std::string& theme) {
    // Theme switching could be implemented here
}

// ============================================================================
// CodeAnalyzer Implementation
// ============================================================================

CodeAnalyzer::AnalysisResult CodeAnalyzer::analyze(const std::string& code) {
    AnalysisResult result;
    
    // Check syntax
    if (!checkSyntax(code)) {
        result.errors.push_back("Syntax error detected in code");
    }
    
    // Find common mistakes
    auto mistakes = findCommonMistakes(code);
    result.warnings.insert(result.warnings.end(), mistakes.begin(), mistakes.end());
    
    // Calculate complexity
    result.complexity = calculateComplexity(code);
    
    // Add suggestions
    if (code.find("wait()") != std::string::npos) {
        result.suggestions.push_back("Consider using task.wait() instead of wait() for better performance");
    }
    
    if (code.find("while true do") != std::string::npos) {
        result.warnings.push_back("Infinite loop detected - ensure proper break conditions");
    }
    
    if (code.find("game.Players.LocalPlayer") != std::string::npos) {
        result.suggestions.push_back("LocalPlayer should only be accessed from LocalScripts");
    }
    
    return result;
}

bool CodeAnalyzer::checkSyntax(const std::string& code) {
    // Basic syntax checking
    int endCount = 0;
    std::istringstream iss(code);
    std::string line;
    
    while (std::getline(iss, line)) {
        if (line.find("function") != std::string::npos || 
            line.find("if") != std::string::npos ||
            line.find("for") != std::string::npos ||
            line.find("while") != std::string::npos) {
            endCount++;
        }
        if (line.find("end") != std::string::npos) {
            endCount--;
        }
    }
    
    return endCount == 0;
}

std::vector<std::string> CodeAnalyzer::findCommonMistakes(const std::string& code) {
    std::vector<std::string> mistakes;
    
    if (code.find("=") != std::string::npos && code.find("==") == std::string::npos) {
        // Check if assignment in condition (common mistake)
        if (code.find("if") != std::string::npos) {
            mistakes.push_back("Possible assignment operator (=) used in condition instead of comparison (==)");
        }
    }
    
    if (code.find("FindFirstChild") != std::string::npos && code.find("WaitForChild") == std::string::npos) {
        mistakes.push_back("Consider using WaitForChild instead of FindFirstChild for more reliable code");
    }
    
    return mistakes;
}

int CodeAnalyzer::calculateComplexity(const std::string& code) {
    int complexity = 1; // Base complexity
    
    // Count control structures
    complexity += std::count(code.begin(), code.end(), '\n') / 10;
    
    std::istringstream iss(code);
    std::string line;
    while (std::getline(iss, line)) {
        if (line.find("if") != std::string::npos) complexity++;
        if (line.find("for") != std::string::npos) complexity++;
        if (line.find("while") != std::string::npos) complexity++;
        if (line.find("function") != std::string::npos) complexity++;
    }
    
    return complexity;
}

// ============================================================================
// ChallengeManager Implementation
// ============================================================================

ChallengeManager::ChallengeManager() {
    initializeBuiltInChallenges();
}

void ChallengeManager::initializeBuiltInChallenges() {
    // Challenge 1: Hello World
    Challenge c1;
    c1.id = "hello_world";
    c1.title = "Hello Roblox";
    c1.description = "Print 'Hello, Roblox!' to the console";
    c1.starterCode = "-- Write your code here\n\n";
    c1.solution = "print(\"Hello, Roblox!\")";
    c1.hints = {"Use the print() function", "Strings are enclosed in quotes"};
    c1.difficulty = 1;
    challenges.push_back(c1);
    
    // Challenge 2: Create a Part
    Challenge c2;
    c2.id = "create_part";
    c2.title = "Create a Part";
    c2.description = "Create a new Part and parent it to workspace";
    c2.starterCode = "-- Create a part and add it to workspace\n\n";
    c2.solution = "local part = Instance.new(\"Part\")\npart.Parent = workspace";
    c2.hints = {"Use Instance.new()", "Set the Parent property to workspace"};
    c2.difficulty = 1;
    challenges.push_back(c2);
    
    // Challenge 3: Part Properties
    Challenge c3;
    c3.id = "part_properties";
    c3.title = "Colorful Part";
    c3.description = "Create a red part with size (10, 5, 10) and place it at position (0, 10, 0)";
    c3.starterCode = "-- Create a colored part with specific size and position\nlocal part = Instance.new(\"Part\")\npart.Parent = workspace\n\n-- Your code here\n";
    c3.solution = "local part = Instance.new(\"Part\")\npart.Parent = workspace\npart.Size = Vector3.new(10, 5, 10)\npart.Position = Vector3.new(0, 10, 0)\npart.BrickColor = BrickColor.new(\"Bright red\")";
    c3.hints = {"Use Vector3.new() for size and position", "Use BrickColor.new() for color"};
    c3.difficulty = 2;
    challenges.push_back(c3);
    
    // Challenge 4: Loop Practice
    Challenge c4;
    c4.id = "loop_practice";
    c4.title = "Count to 10";
    c4.description = "Use a for loop to print numbers from 1 to 10";
    c4.starterCode = "-- Write a for loop to count from 1 to 10\n\n";
    c4.solution = "for i = 1, 10 do\n    print(i)\nend";
    c4.hints = {"Use for i = start, end do", "Don't forget the 'end' keyword"};
    c4.difficulty = 2;
    challenges.push_back(c4);
    
    // Challenge 5: Function Creation
    Challenge c5;
    c5.id = "function_basic";
    c5.title = "Greet Function";
    c5.description = "Create a function called 'greet' that takes a name parameter and prints 'Hello, [name]!'";
    c5.starterCode = "-- Create a greet function\n\n";
    c5.solution = "local function greet(name)\n    print(\"Hello, \" .. name .. \"!\")\nend\n\ngreet(\"Player\")";
    c5.hints = {"Use 'local function' to define a function", "Use .. for string concatenation"};
    c5.difficulty = 2;
    challenges.push_back(c5);
    
    // Challenge 6: Table Operations
    Challenge c6;
    c6.id = "table_basics";
    c6.title = "Table Operations";
    c6.description = "Create a table with 3 player names and print each one using a loop";
    c6.starterCode = "-- Create a table and iterate through it\n\n";
    c6.solution = "local players = {\"Alice\", \"Bob\", \"Charlie\"}\nfor i, name in ipairs(players) do\n    print(name)\nend";
    c6.hints = {"Tables use curly braces {}", "Use ipairs() to iterate over arrays"};
    c6.difficulty = 3;
    challenges.push_back(c6);
    
    // Challenge 7: Touch Detection
    Challenge c7;
    c7.id = "touch_detection";
    c7.title = "Touch Detector";
    c7.description = "Create a part that prints 'Touched!' when a player touches it";
    c7.starterCode = "local part = Instance.new(\"Part\")\npart.Parent = workspace\n\n-- Add touch detection here\n";
    c7.solution = "local part = Instance.new(\"Part\")\npart.Parent = workspace\n\npart.Touched:Connect(function(hit)\n    print(\"Touched!\")\nend)";
    c7.hints = {"Use the Touched event", "Connect events with :Connect()"};
    c7.difficulty = 3;
    challenges.push_back(c7);
    
    // Challenge 8: Player Detection
    Challenge c8;
    c8.id = "player_detection";
    c8.title = "Player Detector";
    c8.description = "Detect when a player's character touches a part and print the player's name";
    c8.starterCode = "local part = Instance.new(\"Part\")\npart.Parent = workspace\n\n-- Detect player touch\n";
    c8.solution = "local part = Instance.new(\"Part\")\npart.Parent = workspace\n\npart.Touched:Connect(function(hit)\n    local humanoid = hit.Parent:FindFirstChild(\"Humanoid\")\n    if humanoid then\n        local player = game.Players:GetPlayerFromCharacter(hit.Parent)\n        if player then\n            print(player.Name)\n        end\n    end\nend)";
    c8.hints = {"Check for Humanoid in the parent", "Use GetPlayerFromCharacter()"};
    c8.difficulty = 4;
    challenges.push_back(c8);
    
    // Challenge 9: Tween Animation
    Challenge c9;
    c9.id = "tween_basic";
    c9.title = "Smooth Movement";
    c9.description = "Use TweenService to smoothly move a part to position (0, 20, 0) over 2 seconds";
    c9.starterCode = "local TweenService = game:GetService(\"TweenService\")\nlocal part = Instance.new(\"Part\")\npart.Parent = workspace\n\n-- Create and play tween\n";
    c9.solution = "local TweenService = game:GetService(\"TweenService\")\nlocal part = Instance.new(\"Part\")\npart.Parent = workspace\n\nlocal goal = {Position = Vector3.new(0, 20, 0)}\nlocal info = TweenInfo.new(2)\nlocal tween = TweenService:Create(part, info, goal)\ntween:Play()";
    c9.hints = {"Create a goal table with properties", "Use TweenInfo.new() for timing"};
    c9.difficulty = 4;
    challenges.push_back(c9);
    
    // Challenge 10: Advanced Function
    Challenge c10;
    c10.id = "damage_function";
    c10.title = "Damage System";
    c10.description = "Create a function that damages a player's humanoid by a specified amount";
    c10.starterCode = "-- Create a damage function\n\n";
    c10.solution = "local function damagePlayer(player, amount)\n    local character = player.Character\n    if character then\n        local humanoid = character:FindFirstChild(\"Humanoid\")\n        if humanoid then\n            humanoid.Health = humanoid.Health - amount\n        end\n    end\nend";
    c10.hints = {"Get the character from the player", "Modify the Humanoid.Health property"};
    c10.difficulty = 5;
    challenges.push_back(c10);
}

void ChallengeManager::loadChallenges() {
    // Could load from file in future
}

Challenge ChallengeManager::getChallenge(const std::string& id) {
    for (const auto& challenge : challenges) {
        if (challenge.id == id) {
            return challenge;
        }
    }
    return Challenge();
}

std::vector<Challenge> ChallengeManager::getChallengesByDifficulty(int difficulty) {
    std::vector<Challenge> result;
    for (const auto& challenge : challenges) {
        if (challenge.difficulty == difficulty) {
            result.push_back(challenge);
        }
    }
    return result;
}

std::vector<Challenge> ChallengeManager::getAllChallenges() {
    return challenges;
}

bool ChallengeManager::validateSolution(const std::string& challengeId, const std::string& code) {
    // Basic validation - in a real implementation, this would execute and test the code
    Challenge challenge = getChallenge(challengeId);
    
    // Simple keyword checking for validation
    if (challengeId == "hello_world") {
        return code.find("print") != std::string::npos;
    } else if (challengeId == "create_part") {
        return code.find("Instance.new") != std::string::npos && 
               code.find("workspace") != std::string::npos;
    }
    
    return true; // Simplified validation
}

// ============================================================================
// SnippetLibrary Implementation
// ============================================================================

SnippetLibrary::SnippetLibrary() {
    initializeBuiltInSnippets();
}

void SnippetLibrary::initializeBuiltInSnippets() {
    // Basic snippets
    snippets.push_back({
        "Create Part",
        "Creates a basic part in workspace",
        "local part = Instance.new(\"Part\")\npart.Parent = workspace\npart.Anchored = true",
        "Basics",
        1
    });
    
    snippets.push_back({
        "Print Function",
        "Basic print statement",
        "print(\"Hello, World!\")",
        "Basics",
        1
    });
    
    // Events
    snippets.push_back({
        "Touch Event",
        "Detects when something touches a part",
        "part.Touched:Connect(function(hit)\n    print(\"Something touched the part!\")\nend)",
        "Events",
        2
    });
    
    snippets.push_back({
        "Player Joined Event",
        "Detects when a player joins the game",
        "game.Players.PlayerAdded:Connect(function(player)\n    print(player.Name .. \" joined the game!\")\nend)",
        "Events",
        2
    });
    
    // Functions
    snippets.push_back({
        "Basic Function",
        "Template for a basic function",
        "local function functionName(parameter)\n    -- Code here\n    return result\nend",
        "Functions",
        2
    });
    
    // Tweening
    snippets.push_back({
        "Tween Part",
        "Smoothly moves a part using TweenService",
        "local TweenService = game:GetService(\"TweenService\")\n\nlocal part = workspace.Part\nlocal goal = {Position = Vector3.new(0, 10, 0)}\nlocal tweenInfo = TweenInfo.new(1)\n\nlocal tween = TweenService:Create(part, tweenInfo, goal)\ntween:Play()",
        "Animation",
        3
    });
    
    // Remote Events
    snippets.push_back({
        "Remote Event (Server)",
        "Server-side remote event handler",
        "local ReplicatedStorage = game:GetService(\"ReplicatedStorage\")\nlocal remoteEvent = ReplicatedStorage:WaitForChild(\"RemoteEvent\")\n\nremoteEvent.OnServerEvent:Connect(function(player, ...)\n    -- Handle event\nend)",
        "Networking",
        4
    });
    
    snippets.push_back({
        "Remote Event (Client)",
        "Client-side remote event usage",
        "local ReplicatedStorage = game:GetService(\"ReplicatedStorage\")\nlocal remoteEvent = ReplicatedStorage:WaitForChild(\"RemoteEvent\")\n\nremoteEvent:FireServer(data)",
        "Networking",
        4
    });
    
    // DataStore
    snippets.push_back({
        "DataStore Save",
        "Save player data using DataStore",
        "local DataStoreService = game:GetService(\"DataStoreService\")\nlocal playerData = DataStoreService:GetDataStore(\"PlayerData\")\n\nlocal function saveData(player)\n    local success, err = pcall(function()\n        playerData:SetAsync(player.UserId, data)\n    end)\n    if not success then\n        warn(\"Failed to save data: \" .. err)\n    end\nend",
        "Data",
        5
    });
    
    // GUI
    snippets.push_back({
        "Button Click",
        "Handle GUI button click",
        "local button = script.Parent\n\nbutton.MouseButton1Click:Connect(function()\n    print(\"Button clicked!\")\nend)",
        "GUI",
        2
    });
}

void SnippetLibrary::loadSnippets() {
    // Could load from file
}

void SnippetLibrary::addSnippet(const CodeSnippet& snippet) {
    snippets.push_back(snippet);
}

std::vector<CodeSnippet> SnippetLibrary::getSnippetsByCategory(const std::string& category) {
    std::vector<CodeSnippet> result;
    for (const auto& snippet : snippets) {
        if (snippet.category == category) {
            result.push_back(snippet);
        }
    }
    return result;
}

std::vector<CodeSnippet> SnippetLibrary::searchSnippets(const std::string& query) {
    std::vector<CodeSnippet> result;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    for (const auto& snippet : snippets) {
        std::string lowerTitle = snippet.title;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        
        if (lowerTitle.find(lowerQuery) != std::string::npos) {
            result.push_back(snippet);
        }
    }
    return result;
}

std::vector<std::string> SnippetLibrary::getCategories() {
    std::vector<std::string> categories;
    for (const auto& snippet : snippets) {
        if (std::find(categories.begin(), categories.end(), snippet.category) == categories.end()) {
            categories.push_back(snippet.category);
        }
    }
    return categories;
}

// ============================================================================
// ProgressTracker Implementation
// ============================================================================

void ProgressTracker::markChallengeComplete(const std::string& challengeId) {
    if (std::find(progress.completedChallengeIds.begin(), 
                  progress.completedChallengeIds.end(), 
                  challengeId) == progress.completedChallengeIds.end()) {
        progress.completedChallengeIds.push_back(challengeId);
        progress.challengesCompleted++;
    }
}

ProgressTracker::UserProgress ProgressTracker::getProgress() {
    return progress;
}

void ProgressTracker::saveProgress(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << progress.challengesCompleted << "\n";
        for (const auto& id : progress.completedChallengeIds) {
            file << id << "\n";
        }
        file.close();
    }
}

void ProgressTracker::loadProgress(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> progress.challengesCompleted;
        file.ignore();
        std::string id;
        while (std::getline(file, id)) {
            progress.completedChallengeIds.push_back(id);
        }
        file.close();
    }
}

} // namespace LuauPractice
