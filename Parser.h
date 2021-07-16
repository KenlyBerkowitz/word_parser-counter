#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <string>

class Parser
{
public:
  Parser();
  void parseWords(std::fstream& fileName, const std::string& userFileName, const std::string& dfltToFileName);
  void printWords(const std::string& dfltToFileName) const;

private:
  std::map<std::string, int> parsedWords;      // parsed words used in doc. Also counts them. No articles, prepositions, and conjuctions
  std::map<std::string, int> artConjPrepEtc;   // a map consisting of articles, prepositions, and conjuctions

  bool isValidChar(const std::string& ln, const int& element);
  void emplace(const std::string& tmpWord);
  void initializeMap();
  void removeNonUsed();
  std::string trim(const std::string& stringToTrim);

};

#endif
