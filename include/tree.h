#pragma once
#include <iostream>
#include <string>
#include <vector>

typedef struct Node Node;

struct Node {
    std::string nodeType = ""; // ex: body
    std::string nodeContent = ""; // ex: <body> or "some string"
    bool isTagNode = false; // tag vs text
    std::string textContent = ""; // for text nodes?
    Node *nodeId = nullptr;
    int depthLevel = 0;
    Node *parentNode = nullptr;
    std::vector<Node*> childNodes;
};

class Tree
{
    public:
        std::vector<Node*> &parsedStack;
        Tree(std::vector<Node*>& stack): parsedStack(stack) {};
        
        Node *root = nullptr;

        void buildTree();

    private:
        bool checkIfEndTag(std::string node);
        std::vector<Node*> findDirectChildNodes(int currentNodeIndex, int depthLevel, Node *parentId);
};