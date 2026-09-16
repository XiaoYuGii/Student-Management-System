#ifndef FILE_IO_H
#define FILE_IO_H

#include "linked_list.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

bool saveToCSV  (const LinkedList& list, const std::string& filename);
bool loadFromCSV(LinkedList& list,       const std::string& filename);

inline std::string csvField(const std::string& s) {
    bool needsQuotes = s.find(',') != std::string::npos || s.find('"') != std::string::npos;
    std::string field = s;
    if (needsQuotes) {
        std::string escaped;
        for (char c : field) {
            if (c == '"') escaped.push_back('"');
            else escaped += c;
        }
        return "\"" + escaped + "\"";
    }
    return field;
}

inline std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                token += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    tokens.push_back(token);
    return tokens;
}

inline bool saveToCSV(const LinkedList& list, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "  [ERROR] Cannot open file for writing: "
                  << filename << "\n";
        return false;
    }

    file << "id,name,gender,age,gpa,major\n";

    Node* cur = list.head();
    while (cur) {
        const Student& s = cur->data;
        file << s.id                  << ","
             << csvField(s.name)      << ","
             << csvField(s.gender)    << ","
             << s.age                 << ","
             << std::fixed << std::setprecision(2) << s.gpa << ","
             << csvField(s.major)     << "\n";
        cur = cur->next;
    }

    file.close();
    return true;
}

inline bool loadFromCSV(LinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return true;
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        ++lineNum;
        if (line.empty()) continue;

        if (lineNum == 1 && line.find("id,") == 0) continue;

        std::vector<std::string> fields = splitCSV(line);
        if (fields.size() < 6) {
            std::cerr << "  [WARN] Skipping malformed line "
                      << lineNum << "\n";
            continue;
        }

        try {
            Student s;
            s.id     = std::stoi(fields[0]);
            s.name   = fields[1];
            s.gender = fields[2];
            s.age    = std::stoi(fields[3]);
            s.gpa    = std::stof(fields[4]);
            s.major  = fields[5];
            list.insertBack(s);
        } catch (...) {
            std::cerr << "  [WARN] Parse error on line "
                      << lineNum << " – skipped.\n";
        }
    }

    file.close();
    return true;
}

#endif
