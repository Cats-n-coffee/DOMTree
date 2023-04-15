#include "parser.h"

// Read lines from html file
void Parser::readLinesFromFile()
{
    // need something to look ahead? that's to check syntax
    std::string trimedLine = leftTrim(this->fileData);
    std::cout << "build " << trimedLine << std::endl;
    this->readCharacter(trimedLine);
}

// cursor to move on each char, checks for endl
void Parser::move()
{

}

// Reads each char and determines tag vs text node
void Parser::readCharacter(std::string line)
{
    bool isTag = false;
    Node newNode;
    Node prevNode;
    int index = 0;

    while (index < line.length()) {
        // should verify for each beginning of tag with <
        if (line[index] == '<') { // html tag beginning
            // we assume that we have a text node before a new html tag
            if (this->currentNode.length() && !isTag) {
                // push the textNode to the stack
                if (prevNode.nodeType.length() > 0) { // check for parent node
                    newNode.parentNode = &prevNode;
                } else {
                    newNode.parentNode = nullptr;
                }
                newNode.isTagNode = false;
                newNode.nodeType = "text";
                newNode.textContent = this->currentNode;
                this->parsedStack.push_back(newNode);
            }
            if (this->currentNode.length()) {
                // beginning of new tag, reset currentNode
                prevNode.nodeType = this->currentNode;
                this->currentNode = "";
            }
            isTag = true;
            this->currentNode += line[index];
        } 
        if (line[index] == '>') { // html tag end, push to stack
            this->currentNode += line[index];
            // push tag node to the stack
            if (prevNode.nodeType.length() == 0) {
                newNode.parentNode = &prevNode;
            } else {
                newNode.parentNode = nullptr;
            }
            newNode.isTagNode = true;
            newNode.nodeType = this->currentNode;
            newNode.textContent = "";
            this->parsedStack.push_back(newNode);
            // Reset
            prevNode.nodeType = this->currentNode;
            this->currentNode = "";
            isTag = false;
        }
        else if (line[index] != '<' && line[index] != '>') {
            this->currentNode += line[index];
        }

        index++;
    }

    for (Node str: this->parsedStack) {
        std::cout << "stack " << str.nodeType << std::endl; 
    }
}
// https://stackoverflow.com/questions/30033582/what-is-the-symbol-for-whitespace-in-c

void Parser::buildTag()
{

}

void Parser::buildTextNode()
{

}