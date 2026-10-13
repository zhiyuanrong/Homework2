#include "word_count.hpp"
#include <string>
#include <cctype>

void to_lowercase(std::string& str){
	for(char& c : str){
		c = std::tolower(c);
	}
}

std::set<std::string> load_stopwords(std::istream& stopwords){
	std::string word;
	std::set<std::string> words;
	while(stopwords >> word){
		to_lowercase(word);
		words.insert(word)
	}
	
	return words;
}
