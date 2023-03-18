// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

static std::string removeDelimiter(std::string s);
static void addToBad(Bag<std::string>* elementNameBag, std::vector<TokenStruct> tokenizedInputVector);

/**
 * @brief Construct a new XMLParser::XMLParser object
 * 
 */
XMLParser::XMLParser()
{
	elementNameBag = new Bag<std::string>();
	parseStack = new Stack<std::string>();
}  // end default constructor

/**
 * @brief Destroy the XMLParser::XMLParser object
 * 
 */
XMLParser::~XMLParser()
{
	//clear internal data structures
	clear();
	
	//delete bag and stack
	delete elementNameBag;
	delete parseStack;

}  // end destructor

/**
 * @brief breaks a string into tokens if possible
 * 
 * @param inputString 
 * @return true 
 * @return false 
 */
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	//flags for checking position/info in string
	bool tagStart = false, elementContent = true;

	//strings to store temp token tag and string
	string tokenTag = "", tokenContent = "";
	
	//loop through string
	for(char c : inputString){
		//if at start of tag
		if(c == '<' && !tagStart){
			//if theres content already
			if(tokenContent.length() > 0){
				//loop through content and remove whitespaces
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
			tagStart = true;
			elementContent = false;
		}
		//store the tag
		else if(c == '>' && tagStart){
			//add char to tag
			tokenTag += c;

			//create token with tag info
			TokenStruct token;
			token.tokenString = removeDelimiter(tokenTag);

			//get delimtters + tag 
			string startTag = tokenTag.substr(0,2), endTag = tokenTag.substr(tokenTag.length() - 2,2);
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
			token.tokenType = tempTokenType;
			tokenizedInputVector.push_back(token);	

			//reset strings
			tokenTag = "";
			tokenContent = "";
			tagStart = false;
			elementContent = true;

			continue;
		}
		//if theres a dupe of delimiters, invalid format
		else if((c == '<' && tagStart) || (c == '>' && !tagStart)){
			//clear the vector and fail tokenize
			tokenizedInputVector.clear();
			tokenizeFlag = false;

			return false;
		}

		//if at start
		if(tagStart == true){
			//add the char to token string
			tokenTag += c;
		}
		//if inside delimiter
		else if(elementContent){
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

/**
 * @brief parses all tokens to make sure they are valid
 * 
 * @return true 
 * @return false 
 */
bool XMLParser::parseTokenizedInput()
{
	//if there are tags
	if(tokenizedInputVector.size() > 0){
		//var with all invalid chars
		char invalid[] = {'!','"','#','$','%','&','\'','(',')','*','+',',','/',';','<','=','>','?','@','[','\\',']','^','`','{','|','}','~',' ','-'};
		string temp;
		//for each token in vector
		for(TokenStruct token : tokenizedInputVector){
			//for each char in token's tag name
			for(char currStringChar : temp){
				//for each invalid char
				for(char currInvalidChar : invalid){
					//if token name char is invalid
					if(currStringChar == currInvalidChar){
						//unsuccessful parse
						parseFlag = false;

						return false;
					}
				}
				if(isdigit(currStringChar) == true){
					parseFlag = false;
					return false;
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
	
	string tagStart = "", tagEnd = "";
	//loop through token vector
	for(TokenStruct token : tokenizedInputVector){
		//get delimtters + tags
		tagStart = token.tokenString.substr(0,2);
		tagEnd = token.tokenString.substr(token.tokenString.length() - 2, 2);

		//if empty tag, delcaration tag, or content element
		if(token.tokenType == EMPTY_TAG || token.tokenType == DECLARATION || token.tokenType == CONTENT){
			//do nothing
			continue;
		}
		//if end tag
		else if(token.tokenType == END_TAG){
			//remove delimter
			string tempTokenString = removeDelimiter(token.tokenString);

			//if match
			if(tempTokenString == parseStack->peek()){
				//remove
				parseStack->pop();
			}
			else if(parseStack->peek()[0] == '-' || parseStack->peek()[0] == ',' || parseStack->peek()[0] == '.' || isdigit(parseStack->peek()[0])){
				//unsuccessful parse
				parseStack->clear();
				parseFlag = false;

				return false;
			}
			else{
				//unsuccessful parse
				parseStack->clear();
				parseFlag = false;

				return false;
			}
		}
		//Start tag
		else if(token.tokenType == START_TAG){			
			//update string
			parseStack->push(removeDelimiter(token.tokenString));
		}
	}

	//check parse flag
	if(parseStack->size() > 0){
		//invalid since not empty, so parse fail
		parseStack->clear();
		parseFlag = false;	
		
		return false;
	}
	else{
		//valid so parse success
		parseStack->clear();
		parseFlag = true;
		
		return true;
	}
}

/**
 * @brief clears all vars
 * 
 */
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

/**
 * @brief returns vector
 * 
 * @return vector<TokenStruct> 
 */
vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

/**
 * @brief determines if a target string is contained in any token's string
 * 
 * @param inputString 
 * @return true 
 * @return false 
 */
bool XMLParser::containsElementName(const std::string &inputString) const
{
	if(tokenizeFlag && parseFlag){
		//add the valid tags to bag
		addToBad(elementNameBag, tokenizedInputVector);

		//loop through bag and see if contained
		return elementNameBag->contains(inputString);
	}
	else{
		return false;
	}
}

/**
 * @brief determines the number of occurances of a target string
 * 
 * @param inputString 
 * @return int 
 */
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if(tokenizeFlag && parseFlag){
		//add the valid tags to bag
		addToBad(elementNameBag, tokenizedInputVector);
		
		//loop through bag and get frequency
		return elementNameBag->getFrequencyOf(inputString);
	}
	else{
		return -1;
	}
}

/**
 * @brief removes the attributes and delimters from a string
 * 
 * @param s 
 * @return std::string 
 */
static std::string removeDelimiter(std::string s){
	//If content, dont change
	if(s[0] != '<'){
		return s;
	}
	//If declaration tag
	else if(s[1] == '?'){
		//get rid of <? and ?>
		return s.substr(2,s.length() - 4);
	}
	//else its a full tag
	else{
		string element = "";
		//loop through everything after delimiter
		for(int i = 1; i < s.length(); i++){
			//if end/empty tag
			if((s[i] == '?' || s[i] == '/') && i == 1)
				continue;
				//if end delimiter is empty tag, declaration tag
			else if((s[i] == ' ' || s[i] == '>') || ((s[i] == '?' || s[i] == '/') && i == s.length()-2)) //2nd char from end
				break;
			//copy over tag otherwise
			else 
				element += s[i];
		}
		return element;
	}
}

/**
 * @brief adds all valid token tags' strings to bag
 * 
 * @param elementNameBag 
 * @param tokenizedInputVector 
 */
static void addToBad(Bag<std::string>* elementNameBag, std::vector<TokenStruct> tokenizedInputVector){
	elementNameBag->clear();
	for(TokenStruct t : tokenizedInputVector){

		if(t.tokenType == END_TAG || t.tokenType == DECLARATION || t.tokenType == CONTENT){
			continue;
		}
		else if(t.tokenType == START_TAG || t.tokenType == EMPTY_TAG){
			elementNameBag->add(t.tokenString);
		}
	}
}