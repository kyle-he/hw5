#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

string replace(string word, char floating_char, int position) {
    if (word[position] == '-') {
        word[position] = floating_char;
    }
    return word;
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> words;

    if (floating.size() == 0) {
        bool allFixed = true;
        for (size_t i = 0; i < in.size(); i++) {
            if (in[i] == '-') {
                string ALPHA = "abcdefghijklmnopqrstuvwxyz";
                for (int a = 0; a < 26; a++) {
                    string temp = replace(in, ALPHA[a], i);
                    set<string> matches = wordle(temp, floating, dict);
                    words.insert(matches.begin(), matches.end());
                }
                allFixed = false;
            }
        }
        if (allFixed) {
            if (dict.find(in) != dict.end()){
                words.insert(in);
            }
            return words;
        }
    } else {
        for (size_t i = 0; i < in.size(); i++) {
            string temp = replace(in, floating[0], i);
            if (in[i] == '-') {
                set<string> matches = wordle(temp, floating.substr(1), dict);
                words.insert(matches.begin(), matches.end());
            }
        }
        return words;
    }

    return words;
}