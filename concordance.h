#ifndef CONCORDANCE_H
#define CONCORDANCE_H
#include "word.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Concordance
{
public:
    Concordance(std::string filename);
    void parse();
    std::string next_word(std::ifstream &input);
    bool is_whitespace(char c);
    void eat_whitespace(std::ifstream &input);
    int find_word(std::string word) const;
    void print() const;
    void add_word(std::string word,int line);
    bool is_poun(char c);
    void eat_poun(std::ifstream &input);
private:
    std::vector<Word> m_word_stats;
    std::string m_filename;
    int m_line;
};

#endif
