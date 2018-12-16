#include "concordance.h"
#include "word.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 

Concordance::Concordance(std::string filename)
{
    m_filename = filename;
    m_line = 1;
}

void Concordance::parse()
{
    std::ifstream file(m_filename.c_str());
    while(!file.eof())
    {
        std::string word = next_word(file);
        add_word(word,m_line);
    }
} 
  
void Concordance::add_word(std::string word, int line)
{
    int index = -1;
    for(int i=0;i<m_word_stats.size();i++)
    {
        if(m_word_stats[i].get_word() == word)
        {
            index = 1;
            break;
        }
    }
    if(index == -1)
    {
        Word w(word);
        w.add_line(line);
        m_word_stats.push_back(w);
    }
    else
    {
        m_word_stats[index].add_count(1);
        m_word_stats[index].add_line(line);
    }
}

bool Concordance::is_whitespace(char c)
{
  return (c == ' ' || c == '\n' ||  c == '\t');
}
bool Concordance::is_poun(char c)
{
    return (c == '.' || c == ',' ||  c == '?'|| c == '!' || c == '(' ||  c == ')'||c == ';' || c == ':' ||  c == '\"' || c == '\'');
}

void Concordance::eat_whitespace(std::ifstream& input)
{
    for(;;)
    {
        char c;
        input.get(c);
        if(input.eof())
            break;
        if(!is_whitespace(c))
        {
            input.putback(c); // this will put the character back on the input stream
            break;
        }
    }
}

void Concordance::eat_poun(std::ifstream& input)
{
    for(;;)
    {
        char c;
        input.get(c);
        if(input.eof())
            break;
        if(!is_poun(c))
        {
            input.putback(c); // this will put the character back on the input stream
            break;
        }
    }
}

std::string Concordance::next_word(std::ifstream& input)
{
    std::string word;
    for(;;)
    {
        char c;
        input.get(c);
        if(input.eof())
            break;
        if(!is_whitespace(c))
        {
            word += c;
        }
        else
        {
            eat_whitespace(input);
            break;
        }
    }
    return word;
}

int Concordance::find_word(std::string word) const
{
    // search the Word vector, and return the index in the vector.
    int index = 0;
    while(index<m_word_stats.size())
    {
        if(m_word_stats[index].get_word() == word)
        {
            break;
        }
        else
        {
            index++;
        }
    }
    return index;    
}

void Concordance::print() const
{
    // print out the concordance
    for(int i=0;i<m_word_stats.size();i++)
    {
        std::cout << m_word_stats[i].get_word(); 
        m_word_stats[i].print();
    }
}
