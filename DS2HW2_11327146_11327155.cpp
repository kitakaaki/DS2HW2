/*11327146 莊立聖 11327155 黃宇謙*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Data {
  int serialNumber = 1;
  std::string schoolCode;
  std::string schoolName;
  std::string departmentCode;
  std::string departmentName;
  std::string dayNight;
  std::string level;
  int studentCount = 1;
  int teacherCount = 0;
  int graduateCount = 0;
  std::string countyCity;
  std::string systemType;
};

class TwoThreeTree {
  private:
    struct Node {
      int key;
      std::vector<int> values;
      std::vector<Node*> children;
      Node* parent;
      int keyCount;
    };

    Node* root = nullptr;

    int treeHeight;

    int nodeCount;
  public:
    void insert(int key, int value) {}

    int height() { return treeHeight; }

    int count() { return nodeCount; }

    void clear() {}

    std::vector<int> rootData() { 
      if (root)  
      return root->values;
      return {}; 
    }

    TwoThreeTree() : treeHeight(0), nodeCount(0) {}
};

class AVLtree {
  private:
    struct Node {
      std::string key;
      std::vector<int> values;
      Node* left;
      Node* right;
      int height;
    };

    Node* root = nullptr;

    int treeHeight;

    int nodeCount;

    int getNodeHeight(Node* node) {
      return node ? node->height : 0;
    }

    Node* rotateLL(Node* node) {
      Node *newNode = node->left;
      node->left = newNode->right;
      newNode->right = node;
      updateHeight(node);
      updateHeight(newNode);
      return newNode;
    }

    Node* rotateRR(Node* node) {
      Node *newNode = node->right;
      node->right = newNode->left;
      newNode->left = node;
      updateHeight(node);
      updateHeight(newNode);
      return newNode;
    }

    Node* rotateLR(Node* node) {
      node->left = rotateRR(node->left);
      return rotateLL(node);
    }

    Node* rotateRL(Node* node) {
      node->right = rotateLL(node->right);
      return rotateRR(node);
    }
  
    Node* verifyBalance(Node* node) {
      int balanceFactor = getBalanceFactor(node);
      if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0) {
          return rotateLL(node);
        } else {
          return rotateLR(node);
        }
      } else if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
          return rotateRR(node);
        } else {
          return rotateRL(node);
        }
      }
      return node;
    }

    int getBalanceFactor(Node* node) {
      int leftHeight = getNodeHeight(node->left);
      int rightHeight = getNodeHeight(node->right);
      return leftHeight - rightHeight;
    }

    void updateHeight(Node* node) {
      int leftHeight = getNodeHeight(node->left);
      int rightHeight = getNodeHeight(node->right);
      node->height = std::max(leftHeight, rightHeight) + 1;
    }
  public:
    Node* insertNode(std::string key, int value, Node* node) {
      if (key == node->key) {
        node->values.push_back(value);
        return node;
      } else if (key < node->key) {
        if (node->left) {
          node->left = insertNode(key, value, node->left);
        } else {
          node->left = new Node{key, {value}, nullptr, nullptr, 1};
          nodeCount++;
        }
      } else {
        if (node->right) {
          node->right = insertNode(key, value, node->right);
        } else {
          node->right = new Node{key, {value}, nullptr, nullptr, 1};
          nodeCount++;
        }
      }
      updateHeight(node);
      node = verifyBalance(node);
      return node;
    }

    void insert(std::string key, int value) {
      if (!root) {
        nodeCount++;
        root = new Node{key, {value}, nullptr, nullptr, 1};
        treeHeight = root->height;
        return;
      }
      root = insertNode(key, value, root);
      treeHeight = root->height;
    }

    int height() { return treeHeight; }

    int count() { return nodeCount; }

    void clearTrees(Node* node) {
      if (!node) return;
      clearTrees(node->left);
      clearTrees(node->right);
      delete node;
    }

    void clear() {
      clearTrees(root);
      root = nullptr;
      treeHeight = 0;
      nodeCount = 0;
    }

    std::vector<int> rootData() { 
      if (root)  
      return root->values;
      return {}; 
    }

    AVLtree() : treeHeight(0), nodeCount(0) {}
};

class IO {
  public:
    static bool readData(const std::string& fileName, std::vector<Data>& dataList) {
      std::ifstream file("input" + fileName + ".txt");
      if (!file.is_open()) {
        return false;
      }
      dataList.clear();
      for (int i = 0; i < 3; i++) {
        std::string header;
        std::getline(file, header);
      }
      int serialNumber = 1;
      std::string line;
      while (std::getline(file, line)) {
        std::istringstream iss(line);
        Data data;
        data.serialNumber = serialNumber++;
        std::getline(iss, data.schoolCode, '\t');
        std::getline(iss, data.schoolName, '\t');
        std::getline(iss, data.departmentCode, '\t');
        std::getline(iss, data.departmentName, '\t');
        std::getline(iss, data.dayNight, '\t');
        std::getline(iss, data.level, '\t');
        std::string studentCountStr;
        std::getline(iss, studentCountStr, '\t');
        // remove "" and , from the string, e.g. "1,234" -> 1234
        studentCountStr.erase(std::remove(studentCountStr.begin(), studentCountStr.end(), '"'), studentCountStr.end());
        studentCountStr.erase(std::remove(studentCountStr.begin(), studentCountStr.end(), ','), studentCountStr.end());
        data.studentCount = std::stoi(studentCountStr);
        std::string teacherCountStr, graduateCountStr;
        std::getline(iss, teacherCountStr, '\t');
        std::getline(iss, graduateCountStr, '\t');
        data.teacherCount = std::stoi(teacherCountStr);
        data.graduateCount = std::stoi(graduateCountStr);
        std::getline(iss, data.countyCity, '\t');
        std::getline(iss, data.systemType, '\t');
        dataList.push_back(data);
      }
      file.close();
      return true;
    }

    static void displayNodes(const std::vector<Data>& datas) {
      int serialIndex = 1;
      for (const auto& data : datas) {
        std::cout << serialIndex++ << ": [";
        std::cout << data.serialNumber << "] ";
        std::cout << data.schoolName << " " << data.departmentName << " ";
        std::cout << data.dayNight << " " << data.level << " ";
        std::cout << data.studentCount << " " << data.graduateCount << "\n";
      }
    }
};

class Menu {
  private:
    std::vector<Data> dataList;
    TwoThreeTree twoThreeTree;
    bool avlTreeExist;
    AVLtree avlTree;
    bool dataListExist;

    void mission1() {
      while (true) {
        std::cout << "Input a file number ([0] Quit): ";
        std::string fileNumber;
        std::cin >> fileNumber;
        if (fileNumber == "0")
          return;
        if (!IO::readData(fileNumber, dataList)) {
          std::cout << "\n### input" << fileNumber << ".txt does not exist! ###\n\n";
        } else {
          break;
        }
      }
      avlTreeExist = false;
      twoThreeTree.clear();
      dataListExist = true;
      for (auto& data : dataList) {
        twoThreeTree.insert(data.graduateCount, data.serialNumber);
      }
      std::cout << "Tree height = " << twoThreeTree.height() << "\n";
      std::cout << "Number of nodes = " << twoThreeTree.count() << "\n";
      IO::displayNodes(makeNodesList(twoThreeTree.rootData()));
      std::cout << "\n\n";
    }

    void mission2() {
      if (!dataListExist) {
        std::cout << "### Choose 1 first. ###\n\n";
        return;
      }
      if (!avlTreeExist) {
        avlTree.clear();
        for (const auto& data : dataList) {
          avlTree.insert(data.schoolName, data.serialNumber);
        }
      avlTreeExist = true;
      } else {
        std::cout << "### AVL tree has been built. ###\n";
      }
      std::cout << "Tree height = " << avlTree.height() << "\n";
      std::cout << "Number of nodes = " << avlTree.count() << "\n";
      IO::displayNodes(makeNodesList(avlTree.rootData()));
      std::cout << "\n\n";
    }

    std::vector<Data> makeNodesList(const std::vector<int>& pairs) {
      std::vector<Data> nodesList;
      for (const auto& pair: pairs) {
        if (pair - 1 >= 0 && pair - 1 < (int)dataList.size())
        nodesList.push_back(dataList[pair-1]);
      }
      return nodesList;
    }
  public:
    void run() {
      std::string choice;
      while (true) {
        std::cout << "* Data Structures and Algorithms *\n";
        std::cout << "****** Balanced Search Tree ******\n";
        std::cout << "* 0. QUIT                        *\n";
        std::cout << "* 1. Build 23 tree               *\n";
        std::cout << "* 2. Build AVL tree              *\n";
        std::cout << "**********************************\n";
        std::cout << "Input a choice(0, 1, 2): ";
        std::cin >> choice;
        if (choice == "0") {
          return;
        } else if (choice == "1") {
          mission1();
        } else if (choice == "2") {
          mission2();
        } else {
          std::cout << "\nCommand does not exist!\n\n";
        }
      }
    }

    Menu() : avlTreeExist(false), dataListExist(false) {}
};

int main () {
  Menu menu;
  menu.run();
  return 0;
}

