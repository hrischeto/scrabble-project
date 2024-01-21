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
* game of Scrabble
*
*/

#include <iostream>
#include <fstream>

constexpr size_t SIZE = 100;
constexpr size_t NUMBER_OF_VOWELS = 5;

void menu(char& menuChoice){
	std::cout << "1 Start a new game!" << std::endl;
	std::cout << "\n2 Settings" << std::endl;
	std::cout << "\n\ta Letters Preferences" << std::endl;
	std::cout << "\n\tb Rounds Preferences" << std::endl;
	std::cout << "\n3 Add to dictionary" << std::endl;
	std::cout << "\n4 Exit" << std::endl;


	std::cout << "\nChoose option from the menu:" << std::endl;

	std::cin >> menuChoice;
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

	srand(time(nullptr));

	for (int i = 0;i < 3;i++) {

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
	std::cout << "If you want to change your letters, enter 1" << std::endl;
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
	bool isPresent = 0;

	dictionary >> wordFromDict;
	while (*wordFromDict){
		
		isPresent = compareWords(inputWord, wordFromDict);
		
		if (isPresent) {
			dictionary.seekg(0, std::ios::beg);
			return 1;
		}

		dictionary.ignore();
		dictionary >> wordFromDict;	
	}

	dictionary.clear();
	dictionary.seekg(0, std::ios::beg);
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
	bool isInDict = isWordInDict(inputWord, dictionary);

	if (isInDict) {
		gamePoints += pointsFromCurrentWord;
		return;
	}

	return;
}

void playGame(std::ifstream& dictionary, int numberOfLetters, int rounds)
{
	
	char givenLetters[SIZE];
	char inputWord[SIZE + 1];
	int gamePoints = 0;



	for (int i = 0;i < rounds;i++){
		generateLetters(givenLetters, numberOfLetters);

		getWord(inputWord);

		if (*inputWord == '1')
			continue;

		checkWord(inputWord, givenLetters, gamePoints, dictionary);

		std::cout << "\nYour points so far are: " << gamePoints << "!" << std::endl;
	}

	std::cout << "\nGAME OVER!\n\nGood job! Your total points are " << gamePoints << "." << std::endl;
	std::cout << "\nReturning to menu."<<std::endl;
	std::cout << '\n';

}

void lettersPreferences(int& numberOfLetters)
{
	std::cout << "\nCurrently you are playing with " << numberOfLetters << " letters." << std::endl;
	std::cout << "With how many letters do you want to play? Enter a number between 1 and 100:" << std::endl;
	std::cin >> numberOfLetters;

	while (numberOfLetters < 1 || numberOfLetters>100)
	{
		std::cout << "Enter a valid number between 1 and 100." << std::endl;
		std::cin >> numberOfLetters;
	}

}

void roundsPreferences(int& rounds) {

	std::cout << "\nYou will play " << rounds << " rounds." << std::endl;
	std::cout << "How many rounds do you want to play?" << std::endl;
	std::cin >> rounds;

}

bool areSymbolsValid(const char* newWord) {

	if (!newWord) {
		std::cout << "Error" << std::endl;
		return 0;
	}

	while (*newWord) {
		if (*newWord < 'a' || *newWord > 'z')
			return 0;
		newWord++;
	}

	return 1;
}

void writeInFile() {

	std::ofstream dictionary("scrabble_dict.txt", std::ios::app);
	//std::ofstream dictionary;
	//dictionary.open("");
	if (!dictionary.is_open()){

		std::cout << "Error!" << std::endl;
		return;
	}
	
	char newWord[SIZE + 1];

	std::cout << "Write the word you want to add to the dictionary with small letters:" << std::endl;
	std::cin >> newWord;

	bool areLettersValid = areSymbolsValid(newWord);

	if (areLettersValid) {
		//dictionary.seekp(50, std::ios::end);
		dictionary << newWord;
		dictionary << '\n';
	}
	else
		std::cout << "Invalid input!" << std::endl;

	dictionary.clear();
	dictionary.close();
	return;
	
}

void initiateGame(std::ifstream& dictionary) {
	char menuChoice;
	menu(menuChoice);

	const int defaultNumber = 10;
	int numberOfLetters = defaultNumber;
	int rounds = defaultNumber;

	switch (menuChoice) {

	case '1':		//start game

		std::cout << "START!" << std::endl;
		playGame(dictionary, numberOfLetters, rounds);
		initiateGame(dictionary);
		break;

	case '2':		//settings
		std::cout << "Choose 'a' or 'b'." << std::endl;
		std::cin >> menuChoice;

		switch (menuChoice) {

		case 'a':	 //letters

			lettersPreferences(numberOfLetters);
			playGame(dictionary, numberOfLetters, rounds);
			initiateGame(dictionary);
			break;

		case 'b':	//rounds

			roundsPreferences(rounds);
			playGame(dictionary, numberOfLetters, rounds);
			initiateGame(dictionary);
			break;
		}
		break;

	case 'a':	 //letters

		lettersPreferences(numberOfLetters);
		playGame(dictionary, numberOfLetters, rounds);
		initiateGame(dictionary);
		break;

	case 'b':	//rounds

		roundsPreferences(rounds);
		playGame(dictionary, numberOfLetters, rounds);
		initiateGame(dictionary);
		break;

	case '3': //add to dictionary

		writeInFile();
		break;

	case '4':		//exit
		return;


	}

}

void scrabble() {

	std::ifstream dictionary;
	dictionary.open("scrabble_dict.txt");
	if (!dictionary.is_open()) {
		std::cout << "Error!"<<  std::endl;
		return;
	}

	initiateGame(dictionary);

	dictionary.clear();
	dictionary.close();
}

int main()
{
	scrabble();
}


