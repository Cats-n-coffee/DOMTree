#include "main.h"

int main()
{
    std::vector<Node> parsedStack;
    Parser parser(parsedStack);
    Tree tree(parsedStack);

    std::ifstream file ("./assets/htmlTest.html");
    if (!file) {
        std::cout << "Error reading HTML file" << std::endl;
        return 0;
    }
    // read + parse the whole file
    // then close once stack is built?
    // build the tree from the stack after
    if (file.is_open()) {
        while(getline(file, parser.fileData)) {
            parser.readLinesFromFile();
        }
    }

    file.close();
    std::cout << "closed file" << std::endl;
    std::cout << "stack has " << parsedStack.empty() << " size is "<< parsedStack.size() << std::endl;
    if (!parsedStack.empty()) {
        std::cout << "stack HAS STUFF" << std::endl;
        tree.buildTree();
    }

    return 0;
}