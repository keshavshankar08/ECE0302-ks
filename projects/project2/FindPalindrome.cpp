#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i]);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string> candidateStringVector, vector<string> currentStringVector)
{	
	if(currentStringVector.size() == 0){
		//copy vector into one string
		string copyVector = "";
		for(int i = 0; i < candidateStringVector.size(); i++){
			copyVector += candidateStringVector[i];
		}

		//if combined string is palindrome, increment count and add vector to list of vectors
		if(isPalindrome(copyVector) == true){
			numPalindromes += 1;
			palindromes.push_back(candidateStringVector);
		}
	}
	//else, try new combo
	else{
		for(int j = 0; j < currentStringVector.size(); j++){
			//create copies of params
			vector<string> tempCandidate = candidateStringVector, tempCurrent = currentStringVector;

			//take current beginning and add to end of candidate
			tempCandidate.push_back(tempCurrent[j]);
			tempCurrent.erase(tempCurrent.begin() + j);

			//if palindrome possible, recuursively call to find another combo
			if(cutTest2(tempCandidate, tempCurrent)){
				recursiveFindPalindromes(tempCandidate, tempCurrent);
			}
		}
	}
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	numPalindromes = 0;
}

FindPalindrome::~FindPalindrome()
{
	
}

int FindPalindrome::number() const
{
	return numPalindromes;
}

void FindPalindrome::clear()
{
	totalSentence.clear();
	palindromes.clear();
	numPalindromes = 0;
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	//create blank array for size of alphabet
	int checkArr[26];
	for(int i = 0; i < 26; i++){
		checkArr[i] = 0;
	}

	//copy over vector to combined string
	string stringVectorCopy = "";
	for(int j = 0; j < stringVector.size(); j++){
		stringVectorCopy += stringVector[j];
	}

	//make combined string lowercase
	convertToLowerCase(stringVectorCopy);

	//increment check values by 1 
	for(int k = 0; k < stringVectorCopy.length(); k++){
		checkArr[stringVectorCopy[k] - 97] += 1;
	}

	//check flag
	int check = 2;

	//if more than one check found odd, vector fails
	for(int l = 0; l < 26; l++){
		if(checkArr[l] % 2 == 1){
			if(!(--check)){
				return false;
			}
		}
	}

	//vector passes if nothing fails
	return true;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1, const vector<string> & stringVector2)
{
	//vars for copying vectors into
	string stringVector1Copy = "", stringVector2Copy = "";

	//copy vector 1 into combined string
	for(int i = 0; i < stringVector1.size(); i++){
		stringVector1Copy += stringVector1[i];
	}
	convertToLowerCase(stringVector1Copy);

	//copy vector 2 into combineed string
	for(int j = 0; j < stringVector2.size(); j++){
		stringVector2Copy += stringVector2[j];
	}
	convertToLowerCase(stringVector2Copy);

	//find the bigger vector as combined string
	string smallerString, biggerString;
	//if vector 2 bigger
	if(stringVector1Copy.length() <= stringVector2Copy.length()){
		smallerString = stringVector1Copy;
		biggerString = stringVector2Copy;
	}
	//if vector 1 bigger
	else{
		smallerString = stringVector2Copy;
		biggerString = stringVector1Copy;
	}

	//check arrays with size of alphabet
	int check1[26], check2[26];
	for(int k = 0; k < 26; k++){
		check1[k] = 0;
		check2[k] = 0;
	}

	//increment check values by 1
	for(int l = 0; l < smallerString.length(); l++){
		check1[smallerString[l]-97] += 1;
	}
	for(int m = 0; m < biggerString.length(); m++){
		check2[biggerString[m]-97] += 1;
	}

	//fails if smaller check over bigger check
	for(int n = 0; n < 26; n++){
		if(check1[n] > check2[n]){
			return false;
		}
	}

	//if nothing fails, passes
	return true;
}

bool FindPalindrome::add(const string & value)
{
	//invalid string if not a-z char
	for(int i = 0; i < value.size(); i++){
		if(isalpha(value.at(i)) == false){
			return false;
		}
	}

	//create lowercase copy of string
	string valueCopy = value;
	convertToLowerCase(valueCopy);

	//invalid string if already in vector
	for(string x : totalSentence){//for each loop to go word by word
		convertToLowerCase(x);
		if(valueCopy.compare(x) == 0){
			return false;
		}
	}

	//if valid string, add to vector and increment count
	totalSentence.push_back(value);
	numPalindromes++;

	//recompute palindromes
	vector<string> newSentence;
	palindromes.clear();
	numPalindromes = 0;
	recursiveFindPalindromes(newSentence, totalSentence);

	//add successful
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	//check if each string in vector valid
	for(int i = 0; i < stringVector.size(); i++){
		//invalid string if not a-z char
		for(int j = 0; j < stringVector[i].size(); j++){
			if(isalpha(stringVector[i].at(j)) == false){
				return false;
			}
		}

		//create lowercase copy of current string in vector
		string stringVectorValueCopy = stringVector[i];
		convertToLowerCase(stringVectorValueCopy);
		
		//invalid string if already in vector
		for(string x : totalSentence){//for each loop to go word by word
			convertToLowerCase(x);
			if(stringVectorValueCopy.compare(x) == 0){
				return false;
			}
		}

		//invalid string if two of same string in input vector
		for(int k = 0; k < stringVector.size(); k++){
			string stringVectorInputValueCopy = stringVector[k];
			convertToLowerCase(stringVectorInputValueCopy);

			//skipping over when outer is inner element
			if(i == k){
				//do nothing
			}
			else if(stringVectorValueCopy == stringVectorInputValueCopy){
				return false;
			}
		}
	}

	//if valid vector
	totalSentence.insert(end(totalSentence), begin(stringVector), end(stringVector));
	numPalindromes += stringVector.size();

	//recompute palindromes
	vector<string> empty;
	palindromes.clear();
	numPalindromes = 0;
	recursiveFindPalindromes(empty, totalSentence);

	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromes;
}

