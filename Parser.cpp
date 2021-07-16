#include "Parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

Parser::Parser()
{
  std::cout << "in constructor" << std::endl;
  initializeMap();
}


void Parser::parseWords(std::fstream& fileName, const std::string& userFileName, const std::string& dfltToFileName)
{
  fileName.open(userFileName, std::ios::in);


  if (fileName.fail())
  {
    std::cout << "Error opening File" << std::endl;
    std::cout << "Returning to main menu...";
    std::cin.ignore(1000, 10);
  }
  else
  {
    std::string tempWord;
    std::string line;

    while (fileName >> tempWord)
    {
      tempWord = trim(tempWord);

      if(tempWord != "")
        emplace(tempWord);
    }

    std::cout << "Size: " << artConjPrepEtc.size() << std::endl;
    std::cout << "Size: " << parsedWords.size() << std::endl;
    removeNonUsed();
    std::cout << "Size: " << artConjPrepEtc.size() << std::endl;
    // for (auto iterator = artConjPrepEtc.begin(); iterator != artConjPrepEtc.end(); ++iterator)
    // {
    //   if (iterator->second == 0)
    //   {
    //     std::cout << iterator->first << std::endl;
    //
    //   }
    // }
    printWords(dfltToFileName);
  }
  fileName.close();
}


void Parser::printWords(const std::string& dfltToFileName) const
{
  std::fstream fileName;
  std::vector<std::pair<std::string, int>> vectorParsedWords;  //used to sort the parsedWords map in order by value
  std::vector<std::pair<std::string, int>> vectorArtConjPrepEtc;  //used to sort the artConjPrepEtc map in order by value

  //copy maps to vectors
  for(auto pair : parsedWords)
    vectorParsedWords.push_back(pair);

  for(auto pair : artConjPrepEtc)
    vectorArtConjPrepEtc.push_back(pair);


  //sort vectors by value in [key, value] pair
  std::sort(vectorParsedWords.begin(), vectorParsedWords.end(), [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second > b.second; });
  std::sort(vectorArtConjPrepEtc.begin(), vectorArtConjPrepEtc.end(), [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second > b.second; });

  //open file for manipulation and write
  fileName.open(dfltToFileName, std::ios::out);


  if (fileName.fail())
  {
    std::cout << "Error opening File" << std::endl;
    std::cout << "Returning to main menu...";
    std::cin.ignore(1000, 10);
  }
  else
  {
    fileName << std::left << std::setw(10) << "Count" << std::setw(30) << "Words" << std::setw(10) << "Count" << std::setw(30) << "Common Words" << "\n";
    fileName << std::left << std::setw(10) << "-----" << std::setw(30) << "-----" << std::setw(10) << "-----" << std::setw(30) << "------------" << "\n";

    //make iterators
    std::vector<std::pair<std::string, int>>::const_iterator iterator1 = vectorParsedWords.begin();
    std::vector<std::pair<std::string, int>>::const_iterator iterator2 = vectorArtConjPrepEtc.begin();

    std::vector<std::pair<std::string, int>>::const_iterator start;
    std::vector<std::pair<std::string, int>>::const_iterator end;

    //need to find out which data structure is larger in order for the output to correctly write
    if (vectorParsedWords.size() > vectorArtConjPrepEtc.size())
    {
      start = vectorParsedWords.begin();
      end = vectorParsedWords.end();
    }
    else
    {
      start = vectorArtConjPrepEtc.begin();
      end = vectorArtConjPrepEtc.end();
    }

    bool endFlag1 = false;
    bool endFlag2 = false;

    while (start != end)
    {
      if((iterator1 != vectorParsedWords.end()) && endFlag2)
      {
        fileName << std::right << std::setw(5) << iterator1->second << "     " << std::left << std::setw(30) << iterator1->first;
        iterator1++;
      }
      else if (iterator1 != vectorParsedWords.end())
      {
        fileName << std::right << std::setw(5) << iterator1->second << "     " << std::left << std::setw(30) << iterator1->first;
        iterator1++;
      }
      else if(endFlag2) {
        fileName << std::right << std::setw(5) << " " << std::setw(30) << " ";
      }
      else if(iterator1 == vectorParsedWords.end())
      {
        fileName << std::right << std::setw(5) << iterator1->second << "     " << std::left << std::setw(30) << iterator1->first;
        endFlag1 = true;
      }

      if(iterator2 != vectorArtConjPrepEtc.end() && endFlag1)
      {
        fileName << std::right << std::setw(5) << iterator1->second << "     " << std::left << std::setw(30) << iterator1->first << std::endl;
        iterator2++;
      }
      else if (iterator2 != vectorArtConjPrepEtc.end())
      {
        fileName << std::right << std::setw(5) << iterator2->second << "     " << std::left << std::setw(30) << iterator2->first << std::endl;
        iterator2++;
      }
      else if(endFlag1)
      {
        fileName << std::setw(5) << " " << std::setw(30) << " ";
      }
      else if(iterator2 == vectorArtConjPrepEtc.end())
      {
        fileName << std::endl;
        endFlag2 = true;
      }

      start++;
    }
  }

  fileName.close();
}


bool Parser::isValidChar(const std::string& ln, const int& element)
{
  std::cout << ln << ": " << ln.at(element);
    if ((ln.at(element) >= 65 && ln.at(element) <= 90) || (ln.at(element) >= 97 && ln.at(element) <= 122))
    {
      std::cout << " returned 1" << std::endl;
      return 1;
    }
    else
    {
      std::cout << " returned 0" << std::endl;
      return 0;
    }

}

std::string Parser::trim(const std::string& stringToTrim)
{
  std::string tempString = stringToTrim;
  int allLettersInvalid = 0;
  //trim the front
  for (int beginning = 0; beginning < tempString.size(); ++beginning)
  {
    if (isValidChar(tempString, beginning))
    {
      tempString = tempString.substr(beginning, tempString.size() - beginning);
      break;
    }
    else
    {
      allLettersInvalid++;
      if (allLettersInvalid == tempString.size())
      {
        tempString = "";
        return tempString;
      }
    }
  }

  //trim the back
  for (int end = tempString.size() - 1; end >= 0; --end)
  {
      if (!isValidChar(tempString, end))
      {
        continue;
      }
      else if (isValidChar(tempString, end))
      {
        tempString = tempString.substr(0, end + 1);
        break;
      }
  }

  return tempString;
}


void Parser::emplace(const std::string& tmpWord)
{
  int tempInt;

  if (artConjPrepEtc.count(tmpWord))
  {
    tempInt = artConjPrepEtc.at(tmpWord);
    tempInt++;
    artConjPrepEtc[tmpWord] = tempInt;
  }
  else if (parsedWords.count(tmpWord))
  {
    tempInt = parsedWords.at(tmpWord);
    tempInt++;
    parsedWords[tmpWord] = tempInt;
  }
  else
    parsedWords.emplace(tmpWord, 1);
}


void Parser::initializeMap()
{
  std::cout << "in initializeMap" << std::endl;
  std::string tempWord;

  std::fstream file("wordsPartsOfSpeech.txt", std::ios::in);

  while (file.good())
  {
    getline(file, tempWord);
    artConjPrepEtc.emplace(tempWord, 0);
  }

  file.close();
}


void Parser::removeNonUsed()
{
  for (auto iterator = artConjPrepEtc.begin(); iterator != artConjPrepEtc.end(); ++iterator)
  {
    if (iterator->second == 0)
    {
      artConjPrepEtc.erase(iterator->first);
      iterator--;
      if(iterator != artConjPrepEtc.begin())
        iterator--;
    }
  }
}
