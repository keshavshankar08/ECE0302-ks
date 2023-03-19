// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

std::string removeDelimiter(std::string s);
void addToBad(Bag<std::string>* elementNameBag, std::vector<TokenStruct> tokenizedInputVector);

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
	string tagOfToken, contentOfToken;
	
	//loop through the input string
	for(char c : inputString){
		//if new tag found not at start
		if(c == '<' && !tagStart){
			//check if theres already content in token
			if(contentOfToken.length() > 0){
				//loop through content
				string tempContentOfToken;
				for(int i = 0; i < contentOfToken.length(); i++){
					//transfer all non whitespace chars to temp
					if(contentOfToken[i] != ' '){
						tempContentOfToken += contentOfToken[i];
					}
					//else, whitespace and skip over
					else{
						continue;
					}

				}
				
				//create new token with tag info
				TokenStruct token;
				token.tokenString = tempContentOfToken;
				token.tokenType = CONTENT;

				//push new token to vector
				tokenizedInputVector.push_back(token);
			}

			//reset temporary holder strings
			contentOfToken = "";
			tagOfToken = "";
			tagStart = true;//since not at start, set start
			elementContent = false;
		}
		//if tag started and now at end, store it
		else if(c == '>' && tagStart){
			//add the char to the temp holder
			tagOfToken += c;

			//create new token with tag info
			TokenStruct token;
			token.tokenString = removeDelimiter(tagOfToken);

			//get the start and end content of the tag
			string startTag = tagOfToken.substr(0,2), endTag = tagOfToken.substr(tagOfToken.length() - 2,2);
			
			//var to store the type once found
			StringTokenType tempTokenType;

			//find token type based on tag limit content
			if(tagOfToken[0] != '<'){
				tempTokenType = CONTENT;
			}
			else if(startTag == "<?"){
				tempTokenType = DECLARATION;
			}
			else if(endTag == "/>"){
				tempTokenType = EMPTY_TAG;
			}
			else if(startTag == "</"){
				tempTokenType = END_TAG;
			}
			else if(startTag[0] == '<'){
				tempTokenType = START_TAG;
			}

			//update new token and push to vector
			token.tokenType = tempTokenType;
			tokenizedInputVector.push_back(token);	

			//reset temporary holder strings
			tagOfToken = "";
			contentOfToken = "";
			tagStart = false;//tag finished so set to not started
			elementContent = true;//was content so update

			continue;
		}
		//if thers a dupe of delimiters at start or end
		else if((c == '<' && tagStart) || (c == '>' && !tagStart)){
			//clear vector
			tokenizedInputVector.clear();

			//fail tokenize flags
			tokenizeFlag = false;

			return false;
		}

		//if the tag started
		if(tagStart == true){
			//add the char to token tag
			tagOfToken += c;
		}
		//if reading the content
		else if(elementContent){
			//add the char to the token content
			contentOfToken += c;

			//remove spaces before valid content
			if(contentOfToken[0] == ' '){
				contentOfToken = contentOfToken.substr(1,contentOfToken.size());
			}
		}
	}

	//nothign fail so update tokenize flags to pass
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
	//if there are tokens
	if(tokenizedInputVector.size() > 0){
		//var with all invalid chars
		char invalid[] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '/', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '`', '{', '|', '}', '~', ' ', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		string vec;
		//for each token in vector
		for(TokenStruct token : tokenizedInputVector){
			//for each char in token's tag name
			for(char currStringChar : vec){
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
	//else there are no tokens and parse fails
	else{
		//unsuccessful parse
		parseFlag = false;

		return false;
	}
	
	//vars to store the endpoint content of tag
	string tagStart = "", tagEnd = "";

	//loop through token vector
	for(TokenStruct token : tokenizedInputVector){
		//get current tokens endpoint contents
		tagStart = token.tokenString.substr(0,2);
		tagEnd = token.tokenString.substr(token.tokenString.length() - 2, 2);

		//do nothing if empty tag, delcaration tag, or content element
		if(token.tokenType == EMPTY_TAG || token.tokenType == DECLARATION || token.tokenType == CONTENT){
			continue;
		}
		//if its a end tag, need to compare to stack
		else if(token.tokenType == END_TAG){
			//remove from stack if matches current value
			if(removeDelimiter(token.tokenString) == parseStack->peek()){
				parseStack->pop();
			}
			//fail parse if the tag starts with invalid char
			else if(parseStack->peek()[0] == '-' || parseStack->peek()[0] == ',' || parseStack->peek()[0] == '.' || isdigit(parseStack->peek()[0])){
				//clear stack
				parseStack->clear();

				//change flags
				parseFlag = false;

				return false;
			}
			//otherwise it fails parse
			else{
				//clear stack
				parseStack->clear();

				//change flags
				parseFlag = false;

				return false;
			}
		}
		//if its a start tag, need to add to stack
		else if(token.tokenType == START_TAG){			
			//update string
			parseStack->push(removeDelimiter(token.tokenString));
		}
	}

	//final checks based on whats left of stack
	//if the staack still has items, it fails the parse
	if(parseStack->size() > 0){
		//clear stack
		parseStack->clear();

		//update flags
		parseFlag = false;	
		
		return false;
	}
	//if the stack no longer has items, it passes the parse
	else{
		//clear stack
		parseStack->clear();

		//update flags
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
	//if tokenizing and parsing passed
	if(tokenizeFlag && parseFlag){
		//add the valid tags to bag
		addToBad(elementNameBag, tokenizedInputVector);

		//loop through bag and see if contained
		return elementNameBag->contains(inputString);
	}
	//else it doesnt have element
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
	//if tokenizing and parsing passed
	if(tokenizeFlag && parseFlag){
		//add the valid tags to bag
		addToBad(elementNameBag, tokenizedInputVector);
		
		//loop through bag and get frequency
		return elementNameBag->getFrequencyOf(inputString);
	}
	//else -1 deafult output
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
std::string removeDelimiter(std::string s){
	//If content, dont change
	if(s[0] != '<'){
		return s;
	}
	//If declaration
	else if(s[1] == '?'){
		//get rid of <? and ?>
		return s.substr(2, s.length() - (2*2));
	}
	//else its a full tag
	else{
		string sNew;
		//loop through everything after delimiter
		for(int i = 1; i < s.length(); i++){
			//skip over if end or declaration at second position
			if((s[i] == ' ' || s[i] == '>') || ((s[i] == '?' || s[i] == '/') && (i == s.length() - 2))){
				break;
			}
			//dont do anything if declaration or end
			else if((s[i] == '?' || s[i] == '/') && i == 1){
				continue;
			}
			//copy over tag otherwise
			else{
				sNew += s[i];
			}
		}
		return sNew;
	}
}

/**
 * @brief adds all valid token tags' strings to bag
 * 
 * @param elementNameBag 
 * @param tokenizedInputVector 
 */
void addToBad(Bag<std::string>* elementNameBag, std::vector<TokenStruct> tokenizedInputVector){
	//clears bag
	elementNameBag->clear();

	//loop through tokens
	for(TokenStruct t : tokenizedInputVector){
		//dont do anyting for end content or declaration tag
		if(t.tokenType == END_TAG || t.tokenType == DECLARATION || t.tokenType == CONTENT){
			continue;
		}
		//add it to the bag if start or empty tag
		else if(t.tokenType == START_TAG || t.tokenType == EMPTY_TAG){
			elementNameBag->add(t.tokenString);
		}
	}
}