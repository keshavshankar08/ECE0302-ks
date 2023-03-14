// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	elementNameBag = new Bag<string>;
	parseStack = new Stack<string>;
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	//delete bag and stack
	delete elementNameBag;
	delete parseStack;

	//clear internal data structures
	clear();
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	//create token
	TokenStruct token;

	//other vars
	string tagName, decTagName, tagType;

	//stop/start vars
	int start, stop, tempCurrPoint;
	
	int currentPoint = 0;
	int buffer = 0;
	int alpha = 0;
	bool needsTesting = false;

	//loop through string input
	while(currentPoint < inputString.length() - 1){
		//string to store data between < and >
		string currentString = "";

		tagName = "";
		tagType = "";
		decTagName = "";

		//----------TAGS----------
		//find start of tag
		if(inputString[currentPoint] == '<'){
			//set pointer to one after start tag
			tempCurrPoint = currentPoint + 1;

			//read everything until end tag
			while(inputString[currentPoint] != '>'){
				//copy info between delimiters
				while(inputString[tempCurrPoint] != '>'){
					currentString += inputString[tempCurrPoint];

					//update pointers
					currentPoint++;
					tempCurrPoint++;
				}
				
				//if the copied string is end tag
				if(currentString[0] == '/'){
					//store tag type to token
					tagType = "END_TAG";
					token.tokenType = END_TAG;

					//needs to be tested
					needsTesting = true;

					//copy over tag name, excluding identification char
					for(int j = 1; j < currentString.length(); j++){
						tagName+= currentString[j];
					}
				}
				//if the copied string is empty tag
				else if(currentString[currentString.length() - 1] == '/'){
					//store tag type to token
					tagType = "EMPTY_TAG";
					token.tokenType = EMPTY_TAG;

					//needs to be tested
					needsTesting = true;

					//copy over tag name 
					for(int j  = 0; j < currentString.length() - 1; j++){
						tagName+=  currentString[j];
					}
				}
				//if the copied string is declaration tag
				else if(currentString[0]== '?' && currentString[currentString.length()-1] == '?'){
					//store tag type to token
					tagType = "DECLARATION";
					token.tokenType = DECLARATION;

					//needs to be tested
					needsTesting = false;

					//copy over tag name, excluding identification char
					for(int j = 1;  j < currentString.length() - 1; j++){
						tagName+= currentString[j];
					}
				}
				//else the  copied string is start tag
				else{
					//store tag type to token
					tagType = "START_TAG";
					token.tokenType = START_TAG;

					//needs to be tested
					needsTesting = true;

					//copy over tag name
					int j = 0;
					while(currentString[j] != '>' && j < currentString.length()){
						tagName += currentString[j];
						j++;

						//stop if blank space found
						if(currentString[j]== ' ')
						{
							break;
						}
					}
				}

				//store tagname to token
				token.tokenString = tagName;

				//if tag, need to test validity
				if(needsTesting == true)
				{
					//checking invalid beginning character
					char invalidBeginChars[] = {' ', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
					for(int posInval = 0; posInval < 13; posInval++){
						if(tagName[0] == invalidBeginChars[posInval]){
							return false;
						}
					}
					
					//checking invalid characters in tagname
					for (int a = 0; a < tagName.length()-1; a++)
					{
						char ch = tagName[a];
						char invalidChars[] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '/', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '`', '{', '|', '}', '~', '.'};
						for(int posInval = 0; posInval < 29; posInval++){
							if(ch == invalidChars[posInval]){
								return false;
							}
						}
					}
				}

				//since valid, push tag token to vector
				tokenizedInputVector.push_back(token);

				//update current point in string based on tag read
				if(tagType== "DECLARATION"){
					currentPoint++;
					buffer = 4;
				}
				else if(tagType == "START_TAG"){
					currentPoint++;
				}
				else if(tagType == "EMPTY_TAG"){
					currentPoint++;
				}
				else if(tagType == "END_TAG"){
					currentPoint++;
				}
			}
			alpha++;
		}

		//----------CONTENT----------
		//if not a tag start/stop
		if(inputString[currentPoint] != '<' && inputString[currentPoint] != '>'){
			//until a tag detected
			while(inputString[currentPoint] != '<'){
				//copy over element to tagname
				tagName += inputString[currentPoint];
				
				//update pointer
				currentPoint++;
			}
			
			//count how many spaces in element
			int numSpaces = 0;
			for(int k = 0; k < tagName.length(); k++){
				if(isspace(tagName[k])){
					numSpaces++;
				}
			}

			//if valid element
			if(numSpaces < tagName.length()){
				//set token data
				token.tokenString = tagName;
				token.tokenType = CONTENT;

				//push token to vector
				tokenizedInputVector.push_back(token);
			}
		}
		
		//move cursor after > if element not just read
		if(token.tokenType != CONTENT){
			currentPoint++;
		}

		//skip over spaces
		if(isspace(inputString[currentPoint])){
			currentPoint++;
			buffer++;
		}
	}

	//update tokenize flag since valid
	tokenizeFlag = true;

	return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	//create token
	_TokenStruct_ token;
	string temp;
	
	//loop through vector
	for(int i = 0; i < tokenizedInputVector.size(); i++){
		//give token current vector element
		token = tokenizedInputVector.at(i);
		
		//store string of token
		temp = token.tokenString;
		
		//if type 1
		if(token.tokenType == 1){
			//don't add to bag, but push to stack
			parseStack->push(temp);
		}
		//if type 2
		else if(token.tokenType == 2){
			//get top of stack
			string peekVal = parseStack->peek();

			//if not at top of stack
			if(peekVal != temp){
				return false;
			}
			//if at top of stack
			else{
				//add it to bag and remove from stack
				elementNameBag->add(temp);
				parseStack->pop();
			}
		}
		//if type 3
		else if(token.tokenType == 3){
			//add to bag, not in stack
			elementNameBag->add(temp);
		}
	}

	//update parse flag
	parseFlag = true;

	return true;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	//clear bag and stack
	delete elementNameBag;
	delete parseStack;

	//clear vector
	int i = 0; 
	//while not at end
	while(i < tokenizedInputVector.size()){
		//pop element from vector and increment loop
		tokenizedInputVector.pop_back();
		i++;
	}
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	//if tokenizeInputstring() and parseTokenizedInput() are true
	if(tokenizeFlag && parseFlag){
		//loop through data
		for(int i = 0; i < elementNameBag->size(); i++){
			//check if target string at that position
			if(elementNameBag->contains(inputString)){
				return true;
			}
		}
		return false;
	}
	//else, input not tokenized/parsed
	else{
		throw(logic_error("Error"));
	}
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	//if tokenizeInputstring() and parseTokenizedInput() are true
	if(tokenizeFlag == true && parseFlag == true){
		//vars for num occurances and bag data
		int count = 0;
		vector<string> data = elementNameBag->toVector();

		//loop through vector and count num occurances
		for(int i = 0; i < data.size(); i++){
			if(data.at(i) == inputString){
				count++;
			}
		}

		return count;
	}
	//else, input not tokenized/parsed
	else{
		throw(logic_error("Error not tokenized/parsed"));
	}
}

