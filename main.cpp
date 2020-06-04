#include <iostream>
#include <map>
#include <vector>

#define DEBUG 1

class Node
{
public:
    bool isSelect = false;
    int name = -1;
    bool isWalked = false;
    std::string parent = "";
    std::vector<Node *> linkedNodes;
};

std::vector<Node *> &readNodes(int numOfNodes)
{
    std::vector<Node *> *nodes = new std::vector<Node *>();

    for (int i = 0; i < numOfNodes; ++i)
    {
        Node *node = new Node();
        node->name = i;
        nodes->push_back(node);
    }

    for (int i = 0; i < numOfNodes; ++i)
    {
        Node *node = nodes->at(i);
        for (int j = 0; j < numOfNodes; ++j)
        {
            int n = 0;
            std::cin >> n;

            if (n == 1)
            {
                node->linkedNodes.push_back(nodes->at(j));
            }
        }
    }

    for (int i = 0; i < numOfNodes; ++i)
    {
        int sel = 0;
        std::cin >> sel;
        if (sel == 1)
        {
            nodes->at(i)->isSelect = true;
        }
    }

    return *nodes;
}

bool hasParent(Node &node, Node &parent)
{
    std::string parentOfNode = node.parent;
    std::string temP = "";
    bool result = false;
    for (char c : parentOfNode)
    {
        if (c == ',')
        {
            int pName = atoi(temP.c_str());
            temP = "";
            if (result == pName)
            {
                result = true;
                break;
            }
        }
        else
        {
            temP += c;
        }
    }
    return result;
}

int walkedCount = 0;
int branchCount = 0;
int minBranchCount = 0;
int okNodes = 0;
std::string walkedNode = "";
std::vector<std::string> walkedNodes;
Node *rootOfRoot = nullptr;

void visit(Node &root)
{
    std::cout << root.name;
    walkedNode += root.name;
    if (root.linkedNodes.size() > 1)
    {
        int isAllWalkedCount = 0;
        for (auto child : root.linkedNodes)
        {
            isAllWalkedCount += child->isWalked ? 1 : 0;
        }
        if (isAllWalkedCount != root.linkedNodes.size())
        {
            ++branchCount;
        }
    }
    root.isWalked = true;
    for (int i = 0; i < root.linkedNodes.size(); ++i)
    {
        auto &child = *root.linkedNodes.at(i);

        if (hasParent(child, root))
        {
            continue;
        }

        if (child.isWalked)
        {
            continue;
        }
        else
        {
            child.parent += root.name + ",";
            visit(child);
        }
    }

    if (root.name == rootOfRoot->name)
    {
        std::cout << std::endl;
        std::cout << branchCount - 1 << std::endl
                  << std::endl;
        walkedNodes.push_back(walkedNode);
    }
    ++walkedCount;
}

int walkNodes(std::vector<Node *> nodes)
{
    std::vector<Node *> *trees = new std::vector<Node *>();

    minBranchCount = INT_MAX;

    for (auto *node : nodes)
    {
        for (auto *n : nodes)
        {
            n->isWalked = false;
        }

        branchCount = 0;
        walkedCount = 0;
        walkedNode = "";
        rootOfRoot = node;
        visit(*node);

        if (--branchCount < minBranchCount)
        {
            minBranchCount = branchCount;
        }
    }

    //std::cout << "Min branch count: " << minBranchCount << std::endl;

    return minBranchCount;
}

int main(int argc, char const *argv[])
{
    std::vector<int> answers;
    int numOfNodes = 0;

    std::cin >> numOfNodes;
    while (numOfNodes != 0 && numOfNodes != -1)
    {
        std::vector<Node *> &nodes = readNodes(numOfNodes);

#if DEBUG
        //Print nodes relationship
        std::cout << "---------- Print nodes relationship [Start] ----------" << std::endl;
        for (Node *node : nodes)
        {
            std::cout << node->name << " | " << std::flush;
            for (Node *lNode : node->linkedNodes)
            {
                std::cout << lNode->name << " " << std::flush;
            }
            std::cout << std::endl;
        }
        std::cout << "---------- Print nodes relationship [End] ----------" << std::endl;
#endif

        answers.push_back(walkNodes(nodes));
        //TODO Do something here

        std::cin >> numOfNodes;
    }

    for (auto answer : answers)
    {
        std::cout << answer << std::endl;
    }

    return 0;
}
