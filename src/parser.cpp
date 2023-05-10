#include "parser.h"

// Read lines from html file
void Parser::readLinesFromFile()
{
    // need something to look ahead? that's to check syntax
    std::string trimedLine = leftTrim(this->fileData);
    this->readCharacter(trimedLine);
}

// Reads each char and determines tag vs text node
void Parser::readCharacter(std::string line)
{
    bool isTag = false;
    std::string currentNode;
    int index = 0;

    while (index < line.length()) {
        // should verify for each beginning of tag with '<'
        if (line[index] == '<') { // html tag beginning
            // we assume that we have a text node before a new html tag
            if (currentNode.length() && !isTag) {
                // push the textNode to the stack
                Node *newNode = new Node();
                this->parsedStack.push_back(newNode);
                // figure out the next line
                std::cout << "Node *newNode " << newNode << " &newNode " << &newNode << std::endl;
                newNode->isTagNode = false;
                newNode->nodeType = "text";
                newNode->nodeContent = currentNode;
                newNode->nodeId = newNode;
                newNode->textContent = currentNode;                
            }
            if (currentNode.length()) {
                // beginning of new tag, reset currentNode
                currentNode = "";
            }
            isTag = true;
            currentNode += line[index];
        } 
        if (line[index] == '>') { // html tag end, push to stack
            currentNode += line[index];

            // push tag node to the stack
            Node *newNode = new Node();
            this->parsedStack.push_back(newNode);
            std::cout << "Node *newNode " << newNode << " &newNode " << &newNode << std::endl;
            newNode->isTagNode = true;
            newNode->nodeType = getNodeContent(currentNode);
            newNode->nodeContent = currentNode;
            newNode->nodeId = newNode;
            newNode->textContent = "";

            // Reset
            currentNode = "";
            isTag = false;
        }
        else if (line[index] != '<' && line[index] != '>') {
            currentNode += line[index];
        }

        index++;
    }
}
// Need to improve once we have HTML attributes
std::string Parser::getNodeContent(std::string currentNode)
{
    std::string nodeName;

    if (currentNode[1] == '/') {
        nodeName = std::string(currentNode.begin() + 2, currentNode.end() - 1);
    } else {
        nodeName = std::string(currentNode.begin() + 1, currentNode.end() - 1);
    }

    return nodeName;
}

void Parser::buildTag()
{
    // might need to move logic for building tag nodes in here,
    // because we need to add attributes and other info
}

void Parser::buildTextNode()
{

}