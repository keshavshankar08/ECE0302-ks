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
	bool isStart = false, isContent = true, isInvalid = false;
	string tokenTag = "", tokenContent = "";
	
	//loop through string
	for(char c : inputString){
		//if at start of tag
		if(c == '<' && !isStart){
			//if theres content already
			if(tokenContent.length() > 0){
				//loop through content and remove white spaces
				string tempTokenContent = "";
				for(int i = 0; i < tokenContent.length(); i++){
					if(tokenContent[i] != ' '){
						tempTokenContent += tokenContent[i];
					}
					else{
						break;
					}
				}
				tokenContent = tempTokenContent;
				
				//create token with tag info
				TokenStruct token;
				token.tokenString = tokenContent;
				token.tokenType = CONTENT;

				//push token to vector
				tokenizedInputVector.push_back(token);
			}

			//reset strings
			tokenContent = "";
			tokenTag = "";
			isStart = true;
			isContent = false;
		}
		//store the tag
		else if(c == '>' && isStart){
			//add char to tag
			tokenTag += c;

			//create token with tag info
			TokenStruct token;

			//-----removing tags from string-----
			//if content
			if(tokenTag[0] != '<'){
				continue;
			}
			//if declaration tag
			else if(tokenTag[1] == '?'){
				tokenTag = tokenTag.substr(2,tokenTag.length()-4);
			}
			//if full tag with both delimiters 
			else{
				string tempTokenTag = "";
				//loop through everything after delimiter
				for(int i = 1; i < tokenTag.length(); i++){
					//if end/empty tag
					if((tokenTag[i] == '?' || tokenTag[i] == '/') && i == 1){
						continue;
					}
					//if end delimiter is empty tag, declaration tag
					else if((tokenTag[i] == ' ' || tokenTag[i] == '>') || ((tokenTag[i] == '?' || tokenTag[i] == '/') && i == tokenTag.length()-2)){
						break;
					}
					//copy over tag
					else{
						tempTokenTag += tokenTag[i];
					}
				}
				//update token tag
				tokenTag = tempTokenTag;
			}

			//get delimtters + tag 
			string startTag = tokenTag.substr(0,2), endTag = tokenTag.substr(tokenTag.length()-2,2);
			StringTokenType tempTokenType;

			//find token type
			if(tokenTag[0] != '<'){
				tempTokenType = CONTENT;
			}
			else if(endTag == "/>"){
				tempTokenType = EMPTY_TAG;
			}
			else if(startTag == "<?"){
				tempTokenType = DECLARATION;
			}
			else if(startTag == "</"){
				tempTokenType = END_TAG;
			}
			else if(startTag[0] == '<'){
				tempTokenType = START_TAG;
			}

			//update token and push to vector
			token.tokenString = tokenTag;
			token.tokenType = tempTokenType;
			tokenizedInputVector.push_back(token);	

			//reset strings
			tokenTag = "";
			tokenContent = "";
			isStart = false;
			isContent = true;
			continue;
		}
		//if theres a dupe of delimiters, invalid format
		else if((c == '<' && isStart) || (c == '>' && !isStart)){
			//clear the vector and fail test
			tokenizedInputVector.clear();
			tokenizeFlag = false;

			return false;
		}

		//if at start
		if(isStart == true){
			//add the char to token string
			tokenTag += c;
		}
		//if inside delimiter
		else if(isContent){
			//store char to content string
			tokenContent += c;

			//check and remove spaces from start
			if(tokenContent[0] == ' '){
				tokenContent.erase(0,1);
			}
		}
	}

	//if all pass, successful tokenize
	tokenizeFlag = true;

	return true;
}  // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	//if there are tags
	if(tokenizedInputVector.size() > 0){
		//var with all invalid chars
		char invalid[] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '/', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '`', '{', '|', '}', '~', ' ', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		
		//for each token in vector
		for(TokenStruct token : tokenizedInputVector){
			//for each char in token's tag name
			for(char currStringChar : token.tokenString){
				//for each invalid char
				for(char currInvalidChar : invalid){
					//if token name char is invalid
					if(currStringChar == currInvalidChar){
						//unsuccessful parse
						parseFlag = false;

						return false;
					}
				}
			}
		}
	}
	//if there are no tags
	else{
		//unsuccessful parse
		parseFlag = false;

		return false;
	}

	string tag, begin, end;
	//loop through token vector
	for(TokenStruct token : tokenizedInputVector){
		//get delimtters + tags
		begin = token.tokenString.substr(0,2);
		end = token.tokenString.substr(tag.length()-2,2);

		//if empty tag, delcaration tag, or content element
		if(token.tokenType == EMPTY_TAG || token.tokenType == DECLARATION || token.tokenType == CONTENT){
			continue;
		}
		//if end tag
		else if(token.tokenType == END_TAG){
			//-----removing tags from string-----
			//if content
			if(token.tokenString[0] != '<'){
				continue;
			}
			//if declaration tag
			else if(token.tokenString[1] == '?'){
				token.tokenString = token.tokenString.substr(2,token.tokenString.length()-4);
			}
			//if full tag with both delimiters 
			else{
				string tempTokenTag = "";
				//loop through everything after delimiter
				for(int i = 1; i < token.tokenString.length(); i++){
					//if end/empty tag
					if((token.tokenString[i] == '?' || token.tokenString[i] == '/') && i == 1){
						continue;
					}
					//if end delimiter is empty tag, declaration tag
					else if((token.tokenString[i] == ' ' || token.tokenString[i] == '>') || ((token.tokenString[i] == '?' || token.tokenString[i] == '/') && i == token.tokenString.length()-2)){
						break;
					}
					//copy over tag
					else{
						tempTokenTag += token.tokenString[i];
					}
				}
				//update token tag
				token.tokenString = tempTokenTag;
			}

			//Check if match to top of stack. If not, we fail the nested test
			if(token.tokenString == parseStack->peek())
				parseStack->pop();
			else{
				parseStack->clear();
				parseFlag = false;

				return false;
			}
		}
		//Start tag
		else if(token.tokenType == START_TAG){
			string tempTokenTag = "";
			//loop through everything after delimiter
			for(int i = 1; i < token.tokenString.length(); i++){
				//if end/empty tag
				if((token.tokenString[i] == '?' || token.tokenString[i] == '/') && i == 1){
					continue;
				}
				//if end delimiter is empty tag, declaration tag
				else if((token.tokenString[i] == ' ' || token.tokenString[i] == '>') || ((token.tokenString[i] == '?' || token.tokenString[i] == '/') && i == token.tokenString.length()-2)){
					break;
				}
				//copy over tag
				else{
					tempTokenTag += token.tokenString[i];
				}
			}
			//update token tag
			token.tokenString = tempTokenTag;
			parseStack->push(token.tokenString);
		}
	}

	//check parse flag
	if(parseStack->size() > 0){
		//invalid so parse fail
		parseFlag = false;

		return false;
	}
	else{
		//valid so parse success
		parseFlag = true;

		return true;
	}
	//reset stack
	parseStack->clear();
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	//clear success flags
	tokenizeFlag = false;
	parseFlag = false;

	//clear internal data structures
	tokenizedInputVector.clear();
	elementNameBag->clear();
	parseStack->clear();
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
		//clear bag
		elementNameBag->clear();

		//loop through vector of tokens
		for(TokenStruct t : tokenizedInputVector){
			//if target is start or empty tag
			if(t.tokenType == START_TAG || t.tokenType == EMPTY_TAG){
				//add the token name to bag
				elementNameBag->add(t.tokenString);
			}
		}

		return true;
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
		//clear bag
		elementNameBag->clear();

		//loop through vector
		for(TokenStruct t : tokenizedInputVector){
			//if target is start or empty tag
			if(t.tokenType == START_TAG || t.tokenType == EMPTY_TAG){
				//add the token name to bag
				elementNameBag->add(t.tokenString);
			}
		}

		return true;
	}
	//else, input not tokenized/parsed
	else{
		throw(logic_error("Error not tokenized/parsed"));
	}
}

