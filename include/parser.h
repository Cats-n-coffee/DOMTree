#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "tree.h"

class Parser
{
    public:
        std::vector<Node*> &parsedStack;
        Parser(std::vector<Node*>& stack): parsedStack(stack) {};
        std::string fileData = "";
        std::string currentNode = "";

        void readLinesFromFile();
        void readCharacter(std::string line);
        void buildTag();
        void buildTextNode();
        std::string getNodeContent(std::string currentNode);
};