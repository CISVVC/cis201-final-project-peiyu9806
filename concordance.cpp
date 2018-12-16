#include "concordance.h"

Concordance::Concordance(std::string filename)
{
    m_filename = filename;
}

void Concordance::parse()
{
    for(int i=0;i<m_word_stats.size();i++)
    {
        std::cout << m_word_stats[i].get_word() << ":" << std::endl;
    }
}

bool Concordance::is_whitespace(char c)
{
  return (c == ' ' || c == '\n' ||  c == '\t');
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

int Concordance::find_word(std::string word)
{
    // search the Word vector, and return the index in the vector.
    std::ifstream file(m_filename.c_str());
    int line = 0;
    int count = 0;
    int index = 0;
    while(!file.eof())
    {
        char c;
        file.get(c);
        if(word == next_word(file))
        {
            m_word_stats.push_back(next_word(file));
            m_word_stats[count].add_count(count);
            index = count;
            count++;
        }
        if(c == '\n')
        {
            break;
        }
        line++;
        m_word_stats[line].add_line(line);
    }
    return index;
}

void Concordance::print()
{
    // print out the concordance
    std::string result[0][0];
    for (int i = 0; i < m_word_stats.size(); i++)
    {
        for (int j = 0; j < 1; j++)
        {
            result[i][j] = m_word_stats[i].get_word(),m_word_stats[i].print();
        }
    }
    for (int i = 0; i < m_word_stats.size(); i++)
    {
        for (int j = 0; j < 1; j++)
        {
            std::cout << result[i][j];
        }
    }     
}

