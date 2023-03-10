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
	Tokenize = false;
	Parse = false;
	clear();
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	TokenStruct myStruct;
	string tempString, tagName, decTagName, tagType, strLengthTrack;
	int start, stop, a;
	
	int cursor = 0;
	int buffer = 0;
	int alpha = 0;
	bool test = false;
	std:: cout << "The length of the string is : " << inputString.length() << std::endl;
	while(cursor < inputString.length()-1)
	{
		tempString = "";
		tagName = "";
		tagType = "";
		decTagName = "";
		if(inputString[cursor] == '<')
		{
			
			a= cursor + 1;
			while (inputString[cursor] != '>')
			{
				while(inputString[a] != '>')
				{
					tempString += inputString[a];
					strLengthTrack += inputString[a];
					cursor++;
					a++;
				}
				
				std::cout << "TempString: " << tempString << std::endl;
				std::cout << "this is the potential tag: " << tempString <<  std::endl;

				if(tempString[0] == '/')
				{
					tagType = "END_TAG";
					test = true;
					for(int j  = 1; j < tempString.length(); j++)
					{
						tagName+= tempString[j];	//fixes tagName
					}
					std::cout << "TagName: " << tagName << std::endl;
				}
				else if(tempString[tempString.length()-1] == '/' )	//last character 
				{
					tagType = "EMPTY_TAG";
					test = true;
					for(int j  = 0; j < tempString.length()-1; j++)
					{
						tagName+=  tempString[j];
					}
					std::cout << "Tagname: " << tagName << std::endl;
				}
				else if(tempString[0]== '?' && tempString[tempString.length()-1] == '?')
				{
					tagType = "DECLARATION";
					test = false;
					int count = 0;
					int b = 0;
					for (int j = 1;  j < tempString.length()-1; j++)
					{
						tagName+= tempString[j];
					}
					std::cout << "Tagname: " <<tagName << std::endl;
				}
				else
				{
					tagType = "START_TAG";
					test = true;
					int j = 0;
					while(tempString[j]!= '>' && j < tempString.length())
					{
						tagName+=tempString[j];
						j++;
						if(tempString[j]== ' ')
						{
							break;
						}
					}
					std::cout << "Tag Type: " << tagType << std::endl;
				}

				if(tagType == "END_TAG")
				{
					std::cout << "Token is EndTag" << std:: endl;
					myStruct.tokenType = END_TAG;
				}
				else if (tagType == "START_TAG")
				{
					std::cout << "Token is StartTag" << std:: endl;
					myStruct.tokenType = START_TAG;
				}
				else if(tagType == "EMPTY_TAG")
				{
					std::cout << "Token is EmptyTag" << std:: endl;
					myStruct.tokenType = EMPTY_TAG;
				}
				else if (tagType == "DECLARATION")
				{
					std::cout << "Token is Declaration" << std:: endl;
					myStruct.tokenType = DECLARATION;
				}
				myStruct.tokenString = tagName;

				if(test == true)	//we SHOULD test
				{
					if (tagName[0]== ' ' || tagName[0]== '-' || tagName[0] == '.')
					{
						return false;
					}
					switch (tagName[0])
					{
						case '0':
							return false;
							break;
						case '1':
							return false;
							break;
						case '2':
							return false;
							break;
						case '3':
							return false;
							break;
						case '4':
							return false;
							break;
						case '5':
							return false;
							break;
						case '6':
							return false;
							break;
						case '7':
							return false;
							break;
						case '8':
							return false;
							break;
						case '9':
							return false;
							break;
						default:
							std:: cout << "there are no illegal characters at first index" << std::endl;
							break;
					}
					
					for (int a = 0; a < tagName.length()-1; a++)
					{
						char ch = tagName[a];
						switch (ch)
						{
							case '!' :
								
								return false;
								break;
							case '"' :
								return false;
								break;
							case '#' :
								return false;
								break;
							case '$' :
								return false;
								break;
							case '%' :
								return false;
								break;
							case '&' :
								return false;
								break;				
							case '\'' :
								return false;
								break;	
							case '(' :
								return false;
								break;	
							case ')' :
								return false;
								break;	
							case '*' :
								return false;
								break;	
							case '+' :
								return false;
								break;	
							case ',' :
								return false;
								break;
							case '/' :
								return false;
								break;
							case ';' :
								return false;
								break;
							case '<' :
								return false;
								break;
							case '=' :
								return false;
								break;
							case '>' :
								return false;
								break;
							case '?' :
								return false;
								break;
							case '@' :
								return false;
								break;
							case '[' :
								return false;
								break;
							case '\\' :
								return false;
								break;
							case ']' :
								return false;
								break;
							case '^' :
								return false;
								break;
							case '`' :
								return false;
								break;
							case '{' :
								return false;
								break;
							case '|' :
								return false;
								break;
							case '}' :
								return false;
								break;
							case '~' :
								return false;
								break;
							case ' ' :
								
								return false;
								break;						
							default:
								break;
						}
					}
				}
				tokenizedInputVector.push_back(myStruct);
				std:: cout << "successfully pushed back to vector" << std:: endl;
				if(tagType== "DECLARATION")
				{
					cursor++;
					buffer = 4;
				}
				else if (tagType == "START_TAG")
				{
					cursor++;
				}
				else if(tagType == "EMPTY_TAG")
				{
					cursor++;
				}
				else if (tagType == "END_TAG")
				{
					cursor++;
				}
			}
			alpha++;
		}

		if(inputString[cursor] != '<' && inputString[cursor] != '>')
		{
			while (inputString[cursor] != '<')
			{
				tagName += inputString[cursor];	//make tag name equal the content
				cursor++;
			}
				std::cout << "Tagname: " << tagName << std::endl;
			int tempInt = tagName.length();
			int numSpace = 0;
			for (int b = 0; b < tempInt; b++)
			{
				if(isspace(tagName[b]))
					numSpace++;
			}
			if(numSpace < tempInt)
			{
				myStruct.tokenString = tagName;
				myStruct.tokenType = CONTENT;
				tokenizedInputVector.push_back(myStruct);
				std:: cout << "successfully pushed back to vector" << std:: endl;
			}	
		} 
		if(myStruct.tokenType != CONTENT)
		{
			cursor++;
		}
		if(isspace(inputString[cursor]))
		{
			cursor++;
			buffer++;
		}
	}
	Tokenize = true;
	return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	_TokenStruct_ vecStruct;
	bool found = false;
	string tempString, peekString;
	
	for(int i = 0; i < tokenizedInputVector.size(); i++){
		vecStruct = tokenizedInputVector.at(i);
		tempString = vecStruct.tokenString;
		if(vecStruct.tokenType == 1){
			parseStack->push(tempString);
		}
		if(vecStruct.tokenType == 2){
			peekString = parseStack->peek();
			if(peekString != tempString){
				return false;
			}
			else{
				elementNameBag->add(tempString);
				parseStack->pop();
			}
		}
		if(vecStruct.tokenType == 3){
			elementNameBag->add(tempString);
		}
	}
	Parse = true;
	return true;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	delete elementNameBag;
	delete parseStack;
	int i = 0; 
	while(i < tokenizedInputVector.size()){
		tokenizedInputVector.pop_back();
		i++;
	}
	tokenizedInputVector = vector<TokenStruct>();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	if(Parse && Tokenize){
		for(int i = 0; i < elementNameBag->size(); i++){
			if(elementNameBag->contains(inputString)){
				return true;
			}
		}
		return false;
	}
	throw(logic_error("Error"));
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if(Parse && Tokenize){
		int count = 1;
		vector<string> vec1 = elementNameBag->toVector();

		for(int i = 0; i < elementNameBag->size(); i++){
			if(vec1.at(i) == inputString){
				count++;
			}
		}

		vec1 = vector<string>();
		return count;
	}

	throw(logic_error("Error"));
}

