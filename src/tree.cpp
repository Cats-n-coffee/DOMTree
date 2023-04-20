#include "tree.h"

// from an array to a tree
// and fill the missing info
void Tree::buildTree()
{
    std::cout << "treeee" << std::endl;
    std::vector<std::string> parentStack;

    std::vector<Node*>::iterator iterPrint, endPrint;
    for (iterPrint = this->parsedStack.begin(), endPrint = this->parsedStack.end(); iterPrint != endPrint; ++iterPrint) {
        std::cout << "in tree " << (*iterPrint)->nodeType << " id is " << (*iterPrint)->nodeId << std::endl; 
    }

    if ( // initialize the root with the first stack item
        this->root == nullptr
        && this->parsedStack.size() > 0
    ) {
        this->root = this->parsedStack[0];
        parentStack.push_back(this->parsedStack[0]->nodeType); // or use nodeId?
    }

    std::vector<Node*>::iterator iter; // might reverse this loop
    for (iter = this->parsedStack.begin(); iter != this->parsedStack.end(); ++iter) {
        // SHOULD THIS FOR LOOP BE A FIRST ITERATION TO FIND A DEEP LAYER
        // Check if the first parent is a Tag? Might do later for check of valid HTML
        Node currentNode;

        if (
            (*iter)->isTagNode
            && (*iter)->nodeType[1] != '/' // from the end tag sounds easier
        ) {
            parentStack.push_back((*iter)->nodeType);
            this->root->childNodes.push_back((*iter)->nodeId);
        }
    }
};

// do we need an intermediate structure or just a way
// to keep track of: current node, potential children.