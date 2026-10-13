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
		words.insert(word)
	}
	
	return words;
}









int main() {

  ifstream stopwords_file("stopwords.txt");

  const auto stopwords = load_stopwords(stopwords_file);


  ifstream document("sample_doc.txt");

  const auto word_counts = count_words(document, stopwords);


  ofstream output("frequency.txt");

  output_word_counts(word_counts, output);

}
