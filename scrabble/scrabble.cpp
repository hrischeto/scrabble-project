/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Hristina Krumova
* @idnumber 9MI0600381
* @compiler VC
*
*
*
*/

#include <iostream>
#include <fstream>

constexpr size_t SIZE = 100;
constexpr size_t NUMBER_OF_VOWELS = 5;

void menu(int& menuChoise){
	std::cout << "1 Start a new game!" << std::endl;
	std::cout << "\n  Settings\n" << std::endl;
	std::cout << "2\t Letters preferences" << std::endl;
	std::cout << "3\t Rounds preferences" << std::endl;
	std::cout << "\n4 Add to dictionary" << std::endl;
	std::cout << "\n5 Exit" << std::endl;

	std::cout << "\nChoose number of option from the menu:" << std::endl;

	std::cin >> menuChoise;
}

void print(const char* str)
{
	if (!str)
		return;

	std::cout << "\n Your letters are:" << std::endl;
	while (*str)
	{
		std::cout << *str << " ";
		str++;
	}
	std::cout << std::endl;
	
}

void generateLetters(char* givenLetters, int numberOfLetters) {

	if (!givenLetters) {
		std::cout << "Error!\n";
		return;
	}

	
	char vowelArr[NUMBER_OF_VOWELS +1] = {'a','e','i','o','u'};

	srand(time(nullptr));//see if it works without that

	for (int i = 0;i < 3;i++) {//add more words to dict

		givenLetters[i] = vowelArr[ rand() % NUMBER_OF_VOWELS];
	}

	for (int i = 3;i < numberOfLetters;i++) {

		givenLetters[i] = 'a' + rand() % 26;
	}

	givenLetters[numberOfLetters] = 0;

	print(givenLetters);
}

void getWord(char* inputWord) {
	if (!inputWord) {
		std::cout<<"Error!\n";
		return;
	}

	std::cout << "\nWrite a word with your letters:" << std::endl;
	std::cin >> inputWord;
}

bool linearSearch(char* givenLetters, char searched) {
	if (!givenLetters)
		return 0;
	while (*givenLetters) {
		if ((searched == *givenLetters) && (*givenLetters != '*')) {
			*givenLetters = '*';
			return 1;
		}
		givenLetters++;
	}
	return 0;
}

//char** creatematrix(int rows) {
//	char** dictionary = new char*[rows];
//
//	for (int i = 0;i < rows;i++) {
//		int cols;
//		dictionary[i] = new char[cols + 1];
//		dictionary[i][0] = cols;
//	}
//}

bool compareWords(char* inputWord, char* wordFromDict) {

	if (!inputWord || !wordFromDict)
		return 0;
	while (*inputWord) {

		if (*inputWord != *wordFromDict)
			return 0;

		inputWord++;
		wordFromDict++;
	}

	if (*wordFromDict)
		return 0;
	return 1;
}
bool isWordInDict(char* inputWord, std::ifstream& dictionary) {

	char wordFromDict[SIZE + 1];
	bool isValid = 0;

	dictionary >> wordFromDict;
	int wordsRead = 1;
	while (*wordFromDict){
		
		isValid = compareWords(inputWord, wordFromDict);
		
		if(isValid)
			return isValid;

		dictionary.ignore();
		dictionary >> wordFromDict;
		wordsRead++;
	}

	//dictionary.seekg(0, ios::beg);
	return 0;
}

void checkWord(char* inputWord, char* givenLetters, int& gamePoints, std::ifstream& dictionary)
{
	if (!inputWord||!givenLetters)
		return;

	int pointsFromCurrentWord = 0;
	bool isLetterAvailable = 0;

	size_t strLen = 0;
	while (*inputWord) {
		
		isLetterAvailable = linearSearch(givenLetters, *inputWord);

		if (isLetterAvailable) {
		pointsFromCurrentWord++;
		}
		else
			return;

		strLen++;
		inputWord++;
	}

	inputWord -= strLen;
	bool isValid = isWordInDict(inputWord, dictionary);

	if (isValid) {
		gamePoints += pointsFromCurrentWord;
		return;
	}

	return;
}

void playGame(std::ifstream& dictionary)
{
	int rounds = 2;
	int numberOfLetters = 20;
	char givenLetters[SIZE];
	char inputWord[SIZE + 1];
	int gamePoints = 0;



	for (int i = 0;i < rounds;i++){
		generateLetters(givenLetters, numberOfLetters);

		getWord(inputWord);

		checkWord(inputWord, givenLetters, gamePoints, dictionary);

		std::cout << "Your points so far are " << gamePoints << "!" << std::endl;
	}

	std::cout << "GAME OVER!\n Your total points are " << gamePoints << "!" << std::endl;
	std::cout << "Returning to menu."<<std::endl;
}

void scrabble() {

	std::ifstream dictionary;
	dictionary.open("scrabble_dict.txt");
	if (!dictionary.is_open()) {
		std::cout << "error!\n";
		return;
	}

	int menuChoise;
	menu(menuChoise);

	switch (menuChoise) {

	case 1:
		playGame(dictionary);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;

	}

	dictionary.clear();
	dictionary.close();
}

int main()
{
	scrabble();
}


