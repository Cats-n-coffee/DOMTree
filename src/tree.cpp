#include "tree.h"

// from an array to a tree
// and fill the missing info
void Tree::buildTree()
{
    std::cout << "treeee" << std::endl;
    std::string currentParent;

    if ( // initialize the root with the first stack item
        this->root.nodeType.length() == 0
        && this->parsedStack.size() > 0
    ) {
        this->root = this->parsedStack[0];
    }

    for (int i = 0; i < this->parsedStack.size(); i++) {
        Node currentNode;

        if (currentParent[0] == '<' && currentParent.length() > 0) {
            // check if we have a parent
        }
    }
};

// do we need an intermediate structure or just a way
// to keep track of: current node, potential children.