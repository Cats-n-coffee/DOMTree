#pragma once
#include <iostream>
#include <string>
#include <vector>

typedef struct Node Node;

struct Node {
    std::string nodeType = ""; // ex: <body>
    bool isTagNode = false; // tag vs text
    std::string textContent = ""; // for text nodes?
    Node *parentNode;
    std::vector<Node> childNodes;
};

class Tree
{
    public:
        std::vector<Node> &parsedStack;
        Tree(std::vector<Node>& stack): parsedStack(stack) {};
        
        Node root;

        void buildTree();
};