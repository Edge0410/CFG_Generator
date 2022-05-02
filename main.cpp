#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

unordered_map<char, vector<pair<int, string>>> Productions;
vector<char> nonTerminals;
vector<char> Terminals;
int Length, nrNonTerminals, nrTerminals, nrProductions;
char startSymbol;
bool wordFound = false;

int findSententialForm(string Word)
{
    for(int j = 0; j<Word.length(); j++)
    {
        if((Word[j] >= 'A' && Word[j] <= 'Z'))
            return j;
    }
    return -1;
}

void writeWord(string Word)
{
    for(int i = 0; i < Word.length(); i++)
        if(Word[i] != '/')
            fout<<Word[i];
    fout<<'\n';
}

void Generate(int currentLength, string currentWord)
{
    if(currentLength == 0) // mergem pe simbolul de start
    {
        for(int i = 0; i<Productions[startSymbol].size(); i++){
            currentWord = Productions[startSymbol][i].second;
            currentLength = Productions[startSymbol][i].first;
            Generate(currentLength, currentWord);
        }
    }
    else // avem o parte din cuvant deja
    {
        if(currentLength <= Length)
        {
            int nextSentential = findSententialForm(currentWord);
            if(nextSentential == -1 && currentLength == Length)
            {
                wordFound = true;
                writeWord(currentWord);
            }
            else
            {
                char Symbol = currentWord[nextSentential];
                for(int i = 0; i<Productions[Symbol].size(); i++){
                    string newWord = currentWord;
                    newWord.replace(nextSentential, 1, Productions[Symbol][i].second);
                    currentLength += Productions[Symbol][i].first;
                    Generate(currentLength, newWord);
                    currentLength -= Productions[Symbol][i].first;
                }
            }
        }
    }
}


int main() {
    char nonTerminal, Terminal, Symbol;
    string Production;
    fin>>nrNonTerminals;
    for(int i = 1; i<= nrNonTerminals; i++)
    {
        fin>>nonTerminal;
        if(i == 1)
            startSymbol = nonTerminal;
        nonTerminals.push_back(nonTerminal);
    }

    fin>>nrTerminals;
    for(int i = 1; i<=nrTerminals; i++)
    {
        fin>>Terminal;
        Terminals.push_back(Terminal);
    }

    fin>>nrProductions;
    for(int i = 1; i<=nrProductions; i++)
    {
        fin>>Symbol>>Production;
        int insideTerminals = 0;
        for(int j = 0; j<Production.length(); j++)
        {
            if(Production[j] >= 'a' && Production[j] <= 'z')
                insideTerminals++;
        }
        Productions[Symbol].push_back({insideTerminals, Production});
    }

    fin>>Length;

    Generate(0, "");

    return 0;
}
