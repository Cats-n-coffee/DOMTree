#include "tree.h"

// from an array to a tree
// and fill the missing info
void Tree::buildTree()
{
    std::vector<std::string> parentStack;
    int currentDepthLevel = 0;

    if ( // initialize the root with the first stack item
        this->root == nullptr
        && this->parsedStack.size() > 0
    ) {
        this->root = this->parsedStack[0];
        parentStack.push_back(this->parsedStack[0]->nodeContent); // or use nodeId?
    }

    for (size_t i = 0; i <= this->parsedStack.size() - 1; ++i) {
        Node *currentNode;

        // if 2 open tags in a row: parent/child
        if (
            (this->parsedStack[i]->isTagNode && !checkIfEndTag(this->parsedStack[i]->nodeContent))
            && (this->parsedStack[i + 1]->isTagNode && !checkIfEndTag(this->parsedStack[i + 1]->nodeContent))
        ) {
            std::cout << "2 OPEN tags in a row" << std::endl;
            currentNode = this->parsedStack[i];
            // std::cout << "current node in original " << currentNode << std::endl;
            std::vector<Node*> directChildren = findDirectChildNodes(i, currentDepthLevel, this->parsedStack[i]);
            currentDepthLevel += 1;
            this->parsedStack[i]->depthLevel = currentDepthLevel;
            this->parsedStack[i]->childNodes = directChildren;
        }
        // if 1 open and 1 text node: --> revise
        // if 2 closed tags in a row: child/parent. Validate the depth level or get rid of check?
        if (
            (this->parsedStack[i]->isTagNode && checkIfEndTag(this->parsedStack[i]->nodeContent))
            && (this->parsedStack[i + 1]->isTagNode && checkIfEndTag(this->parsedStack[i + 1]->nodeContent))
        ) {
            std::cout << "2 CLOSED tags in a row" << std::endl;
        }
        // if 1 closed and 1 open: siblings
        if (
            (this->parsedStack[i]->isTagNode && checkIfEndTag(this->parsedStack[i]->nodeContent))
            && (this->parsedStack[i + 1]->isTagNode && !checkIfEndTag(this->parsedStack[i + 1]->nodeContent))
        ) {
            std::cout << "SIBLINGS" << std::endl;
        }
        // if 1 text node and 1 closed: gives the text node's parent.
    }
};

bool Tree::checkIfEndTag(std::string node)
{
    if (node[1] == '/') return true;
    return false;
}

/* Finds the direct child nodes of the given node and push them to a vector.
 The function iterates over the same parsedStack, but should start at the index AFTER the node
 we assume is a parent (determined by the caller)
*/
std::vector<Node*> Tree::findDirectChildNodes(int currentNodeIndex, int depthLevel, Node *parentId)
{
    std::vector<Node*> directChildren;
    int firstChildIndex = currentNodeIndex + 1;
    Node *currentOpenNode = this->parsedStack[firstChildIndex];

    int sameNodeTypeInStack = 0;

    for (int i = firstChildIndex + 1; i <= this->parsedStack.size() - 1; ++i) {
        // Covers the case when in the stack, we have the same nodeType as currentOpenNode
        // but the current node is not the closing tag we're looking for
        // We keep a count, since we should have open + closed tags, otherwise it's the closing
        // tag we are looking for
        if (
            this->parsedStack[i]->nodeType == currentOpenNode->nodeType
            && !checkIfEndTag(this->parsedStack[i]->nodeContent)
        ) {
            sameNodeTypeInStack += 1;
        }

        if ( // Check if the current node matches the currentOpenNode type and is an end tag
            this->parsedStack[i]->isTagNode
            && this->parsedStack[i]->nodeType == currentOpenNode->nodeType
            && checkIfEndTag(this->parsedStack[i]->nodeContent)
        ) {
            if (sameNodeTypeInStack > 0) {
                sameNodeTypeInStack -= 1;
            } else {
                currentOpenNode->depthLevel = depthLevel + 1;
                currentOpenNode->parentNode = parentId;

                directChildren.push_back(currentOpenNode);

                if ( // Update the currentOpenNode with the next node if not NULL
                    this->parsedStack[i + 1] != nullptr
                    && !checkIfEndTag(this->parsedStack[i + 1]->nodeContent)
                ) {
                    currentOpenNode = this->parsedStack[i + 1];
                    ++i;
                }
            }
        }
    }
    for (int i = 0; i < directChildren.size(); ++i) {
        std::cout << "DIRECT CHILD IS " << directChildren[i]->nodeType << " Parent is " << directChildren[i]->parentNode->nodeType << std::endl;
    }

    return directChildren;
}
