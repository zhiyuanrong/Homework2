#include "word_count.hpp"
#include <string>
#include <cctype>
#include <fstream>
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
		words.insert(word);
	}
	
	return words;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords){
	std::string word;
	std::map<std::string, int> words;
	while(document >> word){
		to_lowercase(word);

 	       bool is_stopword = stopwords.count(word) > 0;

        	if (!is_stopword) {
                 	 words[word]++;
       		 }
    }

    return words;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output){
	for(const auto& pair : word_counts){
		output << pair.first << " " << pair.second << '\n';
	}
}
