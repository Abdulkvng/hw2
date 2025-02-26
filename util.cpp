#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>
#include <string>

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
    set<std::string> wordlist;
    string Currword;
//building word char by char
    for ( size_t i = 0 ; i < rawWords.size() ; i++){
 char c = rawWords[i];
 if (isalnum(c)){
  Currword += tolower(c);}
  else{
    if (Currword.size() >= 2){
      wordlist.insert(Currword);
    }
    Currword.clear();
  }
        }
if ( Currword.size() >= 2){
  wordlist.insert(Currword);
}
return wordlist;}
    // read in strings - and parse them into set 

// stringstream
//and and or at begininning, cinn those two words, 
// if and search both 
// if or search either keyword



// cin till punctuation if encoutner 
// if string before less than 2 ignore string







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
