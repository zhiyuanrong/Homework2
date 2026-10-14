// ------------------------- Your tests - student_gtests.cpp ----------------------------- //
// Your own GoogleTest suite for the word_count module. It is graded: the autograder runs it
// against a correct implementation and against several with one bug each. A test is worth
// something only when it passes on the correct implementation and fails on a broken one, so a
// test that always fails (or that tests nothing) earns nothing.
//
// Two examples are given. Add tests of your own for to_lowercase, load_stopwords, count_words
// and output_word_counts, and for the edges: an empty document, a document that is all stop
// words, stop words written in mixed case, and the same word in several cases.
// --------------------------------------------------------------------------------------- //

#include <gtest/gtest.h>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include "word_count.hpp"

TEST(WordCountTests, StopwordsAreLoadedCaseInsensitively) {
    std::stringstream stopwords{"The OVER\n"};
    const auto loaded = load_stopwords(stopwords);
    EXPECT_TRUE(loaded.contains("the"));
    EXPECT_TRUE(loaded.contains("over"));
}

TEST(WordCountTests, WordsAreCountedCaseInsensitively) {
    std::stringstream document{"Apple apple APPLE pear"};
    const auto counts = count_words(document, {});
    EXPECT_EQ(counts.at("apple"), 3);
    EXPECT_EQ(counts.at("pear"), 1);
}

// ADD YOUR TESTS HERE:

TEST(WordCountStudentTests, ToLowercaseChangesMixedCase) {
    std::string word = "HeLLo";
    to_lowercase(word);
    EXPECT_EQ(word, "hello");
}

TEST(WordCountStudentTests, ToLowercaseLeavesNumbersAndSymbols) {
    std::string word = "CS45C!";
    to_lowercase(word);
    EXPECT_EQ(word, "cs45c!");
}

TEST(WordCountStudentTests, LoadStopwordsLowercasesAllWords) {
    std::istringstream input("The AND Of");
    std::set<std::string> stopwords = load_stopwords(input);

    EXPECT_TRUE(stopwords.contains("the"));
    EXPECT_TRUE(stopwords.contains("and"));
    EXPECT_TRUE(stopwords.contains("of"));
    EXPECT_FALSE(stopwords.contains("The"));
}

TEST(WordCountStudentTests, LoadStopwordsRemovesDuplicatesUsingSet) {
    std::istringstream input("the The THE and");
    std::set<std::string> stopwords = load_stopwords(input);

    EXPECT_EQ(stopwords.size(), 2);
    EXPECT_TRUE(stopwords.contains("the"));
    EXPECT_TRUE(stopwords.contains("and"));
}

TEST(WordCountStudentTests, CountWordsCountsRepeatsCaseInsensitively) {
    std::istringstream document("Cat cat CAT dog");
    std::set<std::string> stopwords;

    std::map<std::string, int> counts = count_words(document, stopwords);

    EXPECT_EQ(counts["cat"], 3);
    EXPECT_EQ(counts["dog"], 1);
}

TEST(WordCountStudentTests, CountWordsSkipsStopwords) {
    std::istringstream document("cat the dog and cat");
    std::set<std::string> stopwords = {"the", "and"};

    std::map<std::string, int> counts = count_words(document, stopwords);

    EXPECT_EQ(counts["cat"], 2);
    EXPECT_EQ(counts["dog"], 1);
    EXPECT_FALSE(counts.contains("the"));
    EXPECT_FALSE(counts.contains("and"));
}

TEST(WordCountStudentTests, CountWordsLowercasesBeforeCheckingStopwords) {
    std::istringstream document("The THE tHe cat");
    std::set<std::string> stopwords = {"the"};

    std::map<std::string, int> counts = count_words(document, stopwords);

    EXPECT_EQ(counts["cat"], 1);
    EXPECT_FALSE(counts.contains("the"));
}

TEST(WordCountStudentTests, CountWordsEmptyDocumentGivesEmptyMap) {
    std::istringstream document("");
    std::set<std::string> stopwords = {"the", "and"};

    std::map<std::string, int> counts = count_words(document, stopwords);

    EXPECT_TRUE(counts.empty());
}

TEST(WordCountStudentTests, CountWordsAllStopwordsGivesEmptyMap) {
    std::istringstream document("the and THE And");
    std::set<std::string> stopwords = {"the", "and"};

    std::map<std::string, int> counts = count_words(document, stopwords);

    EXPECT_TRUE(counts.empty());
}

TEST(WordCountStudentTests, OutputWordCountsUsesAlphabeticalMapOrder) {
    std::map<std::string, int> counts;
    counts["dog"] = 2;
    counts["cat"] = 3;
    counts["bird"] = 1;

    std::ostringstream output;
    output_word_counts(counts, output);

    EXPECT_EQ(output.str(), "bird 1\ncat 3\ndog 2\n");
}
