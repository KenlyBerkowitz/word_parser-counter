#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Parser.h"
//#include <cctype> //for toupper
using namespace std;


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


void clearScreen();
void displayMenu();
void getSwitchChoice(int&);
void createTextFile(fstream&, const string&, string&);
bool isValidFileName(const string&);
void selectFile(string&);


int main()
{
  int userSwitchChoice;
  string dfltFromFileName = "parseFrom.txt";
  string dfltToFileName = "parseTo.txt";
  string userFileName = "";
  fstream textFile;
  bool hasMadeFile;
  Parser parser;

  do
  {
    clearScreen();
    displayMenu();

    getSwitchChoice(userSwitchChoice);
    switch(userSwitchChoice)
    {
      case 1:
          createTextFile(textFile, dfltFromFileName, userFileName);
          break;
      case 2:
          selectFile(userFileName);
          parser.parseWords(textFile, userFileName, dfltToFileName);
          break;
      default:
          cout << "Hope this helped. Bye! \n";
    }
  } while (userSwitchChoice != 0);

  return 0;
}


void clearScreen()
{
  #ifdef _WIN32
    system("CLS");
  #else
    system("clear");
  #endif

  cout <<"\n\n\n" << endl;
}


void displayMenu()
{
  cout << "  ** ** * ** ** ** ** ** ** ** ** * ** **  " << endl
       << "  ** **   Word Parser and Counter   ** **  " << endl
       << "  ** ** * ** ** ** ** ** ** ** ** * ** **  " << endl
       << endl << endl
       << "  Select an action from the menu below. \n\n"
       << "  1. Create Empty Text File (create file with .txt extension)\n"
       << "  2. Parse Words In File\n"
       << "  0. Enter zero to quit the program" << endl << endl;
}


void getSwitchChoice(int& userChoice)
{
  cout << "Select a number from the option menu above [ex: 1] : ";
  do
  {
    cin >> userChoice;
    cin.ignore(1000, 10);

    if(userChoice < 0 && userChoice > 2)
      cout << endl << "Invalid input.\n Please enter another number 0 - 2 : ";

  } while (userChoice < 0 && userChoice > 2);
}


void createTextFile(fstream& file, const string& defaultFile, string& userFN)
{
  cout << "I will make a file in order for you to copy and paste into.\n"
       << "Please enter a file name with a '.txt' extension. \n"
       << "If you want to use the default file name, just press Enter/Return. \n" << endl;

  bool flag;
  do
  {
    flag = false;
    cout << "Enter file name: ";
    getline(cin, userFN);

    if (userFN == "")
      userFN = defaultFile;
    else if (isValidFileName(userFN))
    {
      cout << "Invalid! You need to have a valid extension for you file name\n"
           << "E.G. : [needToParse.txt] \n\n";
      flag = true;
    }
  } while (flag);

  file.open(userFN, ios::in);
  file.close();
  if (file.fail())
  {
    file.open(userFN, ios::out);
    file << "Copy and paste over this text";
    file.close();
  }
  else
  {
    cout << "File already exists... \n";

  }


  file.clear();

}


bool isValidFileName(const string& fileName)
{
  string parsedExtension;
  parsedExtension = fileName.substr(fileName.length() - 4, 4);

  if (parsedExtension == ".txt")
    return 0;

  return 1;
}


void selectFile(string& userFN)
{
  bool flag1;
  bool flag2;
  if (userFN.empty())
  {
    do
    {
      flag1 = false;
      cout << "Enter the file/file path that you would like to parse: ";
      getline(cin, userFN);

      if (isValidFileName(userFN))
      {
        cout << "Invalid! You need to have a valid extension for you file name\n"
             << "E.G. : [needToParse.txt] \n\n";
        flag1 = true;
      }
    } while(flag1);
  }
  else
  {
    char decision;
    cout << "File on hand: " << userFN << "\nWould you like to use the file that you created? [Y/N]: ";
    cin >> decision;
    if (toupper(decision) == 'N')
    {
      do
      {
        flag2 = false;

        cout << "\nEnter the file/file path that you would like to parse: ";
        getline(cin, userFN);

        if (isValidFileName(userFN))
        {
          cout << "Invalid! You need to have a valid extension for you file name\n"
               << "E.G. : [needToParse.txt] \n\n";
          flag2 = true;
        }
      } while (flag2);
    }
  }  //else
}
