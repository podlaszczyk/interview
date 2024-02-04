#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

struct Directory
{
    std::string name;
    std::vector<Directory> children;

    explicit Directory(const std::string& name)
        : name(name){};

    explicit Directory(const std::vector<std::string>& tokens)
    {
        if (tokens.size() == 1) {
            name = tokens[0];
            return;
        }

        name = tokens[0];
        const auto tokenVec = std::vector<std::string>(tokens.begin() + 1, tokens.end());
        const Directory child = Directory(tokenVec);
        children.push_back(child);
    }

    bool operator==(const Directory& obj2) const
    {
        return name == obj2.name;
    }
};

void printDirectory(const Directory& dir, int indent)
{
    std::cout << std::setw(indent) << " " << dir.name << "\n";
    indent += 4;

    for (const auto& child : dir.children) {
        printDirectory(child, indent);
    }
}

std::vector<Directory> mergeDirectories(const std::vector<Directory>& directories)
{
    std::vector<Directory> result;

    for (const auto& dir : directories) {
        auto it = std::find(result.begin(), result.end(), dir);
        if (it == result.end()) // does not exists
        {
            result.push_back(dir);
        }
        else { // exists

            auto child = *dir.children.begin();
            auto childIt = std::find(it->children.begin(), it->children.end(), child);
            if (childIt == it->children.end()) // does not find in children
            {
                it->children.push_back(child);
            }
            else { // exists in children
                childIt->children.push_back(*child.children.begin());
            }
        }
    }
    return result;
}

int main()
{
    const auto path = "inputDataExtended";
    std::ifstream file(path);
    try {
        if (!file) {
            throw std::domain_error("Wrong data");
        }
    }
    catch (const std::exception& exception) {
        return -1;
    }

    std::string line;

    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    std::vector<Directory> directories;
    for (const auto& line : lines) {
        std::vector<std::string> tokens;
        for (const auto& tokenRange : line | std::views::split('.')) {
            std::string token{};
            std::ranges::copy(tokenRange, std::back_inserter(token));
            tokens.push_back(token);
        }
        const Directory dir(tokens);
        directories.push_back(dir);
    }

    for (auto& dir : directories) {
        printDirectory(dir, 0);
        std::cout << "\n";
    }

    auto merged = mergeDirectories(directories);

    std::cout << "after merge \n";
    for (auto& dir : merged) {
        printDirectory(dir, 0);
        std::cout << "\n";
    }

    return 0;
}
