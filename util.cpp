#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  //immediately converts rawWords to lowercase for convenience
  string newWords = convToLower(rawWords);
  string word = "";
  std::set<string> finalWords;

  for(size_t i = 0; i < newWords.size(); ++i) { 
    //check for punctuation or spaces to split up 
    if(ispunct(newWords[i]) || newWords[i] == ' ') {
        if(word.length() > 1) finalWords.insert(word);
        //reset the word for the next iteration
        word = "";
    } else word = word + newWords[i]; //or else just adds the character to word
  }

  //checks one more time if word has more than one character
  if(word.length() > 1) finalWords.insert(word);
  return finalWords;
  
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
