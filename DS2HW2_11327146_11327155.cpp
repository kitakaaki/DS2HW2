/*11327146 莊立聖 11327155 黃宇謙*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

struct Data {
  int serialNumber = 1;
  std::string schoolName;
  std::string departmentName;
  std::string dayNight;
  std::string level;
  int studentCount = 1;
  int graduateCount = 0;
};

class TwoThreeTree {
  private:
    struct Entry {
        int key;
        std::vector<int> serial;
    };

    struct Node {
      Entry keys[3];
      Node* child[4];
      int count;

      Node() : count(0) {
          for (int i = 0; i < 4; i++) child[i] = nullptr;
      }

      Node(int key, int serial) : count(1) {
        keys[0].key = key;
        keys[0].serial.push_back(serial);
        for (int i = 0; i < 4; i++) child[i] = nullptr;
      }

      Node(int key, const std::vector<int>& serial) : count(1) {
          keys[0].key = key;
          keys[0].serial = serial;
          for (int i = 0; i < 4; i++) child[i] = nullptr;
      }

      ~Node() {
        for (int i = 0; i < 4; i++) {
            if (child[i] != nullptr) {
                delete child[i];
                child[i] = nullptr;
            }
        }
      }

      bool isLeaf() { return child[0] == nullptr; }
    };

    struct SplitData {
      bool active = false;
      int key;
      std::vector<int> serial;
      Node* rightNode = nullptr;
    };

    Node* root = nullptr;
    int treeHeight;
    int nodeCount;

    // for adding key to current nodes, help sorting the keys
    void addKeyToLeaf(Node* curr, int key, int serial) {
      int i = curr->count - 1;
        // shifting position for the new inserted keys
      while (i >= 0 && key < curr->keys[i].key) {
          curr->keys[i + 1] = curr->keys[i];
          i--;
      }
      
      // insert the new key
      curr->keys[i + 1].key = key;
      curr->keys[i + 1].serial.clear();
      curr->keys[i + 1].serial.push_back(serial);
      curr->count++;
    }

    // for adding key to current nodes, help sorting the keys, and help shifting the key's childs to the correct position
    void addKeyToInternalNode(Node* curr, int key, const std::vector<int>& serial, Node* rightNode) {
        int i = curr->count - 1;

        // shifting position for the new inserted keys
        while (i >= 0 && key < curr->keys[i].key) {
            curr->keys[i + 1] = curr->keys[i];
            curr->child[i + 2] = curr->child[i + 1];
            i--;
        }

        // insert the new key
        curr->keys[i + 1].key = key;
        curr->keys[i + 1].serial = serial;
        // shifting new key's child to the correct pos
        curr->child[i + 2] = rightNode;
        curr->count++;
    }

    // for splitting the nodes
    Node* split(Node* curr, SplitData* lastSplit) {
      lastSplit->active = true;
      lastSplit->key = curr->keys[1].key;
      lastSplit->serial = curr->keys[1].serial;
      Node* newNode = new Node(curr->keys[2].key, curr->keys[2].serial);
      lastSplit->rightNode = newNode;
      nodeCount++;
      if (!curr->isLeaf()) {
        // assigning rightnode's child
        newNode->child[0] = curr->child[2];
        newNode->child[1] = curr->child[3];
        curr->child[2] = nullptr;
        curr->child[3] = nullptr;
      }
      curr->count = 1; // deleting the node's right key 
      return curr;
    }

    Node* insertNode(int key, int serial, Node* curr, SplitData* lastSplit) {
      if (curr == nullptr) return nullptr;
      // for checking if the key is the same
      for (int i = 0; i < curr->count; i++) {
          if (curr->keys[i].key == key) {
              curr->keys[i].serial.push_back(serial);
              return curr;
          }
      }

      if (curr->isLeaf()) {
          addKeyToLeaf(curr, key, serial);
          // if node got three keys then it needs to split
          if (curr->count == 3) {
              return split(curr, lastSplit); 
          }
          return curr;
      }

      // if current is not a leaf, find the correct child to descend
      Node* nextChild = nullptr;
      if (key < curr->keys[0].key) {
          nextChild = curr->child[0];
      } else if (curr->count == 1 || key < curr->keys[1].key) {
          nextChild = curr->child[1];
      } else {
          nextChild = curr->child[2];
      }

      insertNode(key, serial, nextChild, lastSplit);

      // check if there's new key ascended
      if (lastSplit->active) {
        addKeyToInternalNode(curr, lastSplit->key, lastSplit->serial, lastSplit->rightNode);
        lastSplit->active = false;

        if (curr->count == 3) {
            return split(curr, lastSplit);
        }
      }

      return curr;
    }

  public:
    void insert(int key, int serial) {
      if (!root) {
        root = new Node{key, serial};
        nodeCount++;
        treeHeight++;
        return;
      }
      SplitData lastSplit;
      root = insertNode(key, serial, root, &lastSplit);

      if (lastSplit.active) {
        // create new root node, and increase tree height
        Node* newRoot = new Node(lastSplit.key, lastSplit.serial);
        newRoot->child[0] = root;
        newRoot->child[1] = lastSplit.rightNode;
        
        root = newRoot;
        treeHeight++;
        nodeCount++;
      }
    }

    int height() { return treeHeight; }

    int count() { return nodeCount; }

    void clear() {
      if (root != nullptr) {
            delete root;
            root = nullptr;
        }
        treeHeight = 0;
        nodeCount = 0;
      }

    std::vector<int> rootData() { 
      std::vector<int> serials;
      if (root) {
        for (int i = 0; i < root->count; i++) {
          serials.insert(serials.end(), root->keys[i].serial.begin(), root->keys[i].serial.end());
        }
      }
      return serials;
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

    void clearTrees(Node* node) {
      if (!node) return;
      clearTrees(node->left);
      clearTrees(node->right);
      delete node;
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

    ~AVLtree() {
      clear();
    }
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
        std::string unusedField;
        std::getline(iss, unusedField, '\t');
        std::getline(iss, data.schoolName, '\t');
        std::getline(iss, unusedField, '\t');
        std::getline(iss, data.departmentName, '\t');
        std::getline(iss, data.dayNight, '\t');
        std::getline(iss, data.level, '\t');
        std::string studentCountStr;
        std::getline(iss, studentCountStr, '\t');
        // remove "" and , from the string, e.g. "1,234" -> 1234
        studentCountStr.erase(std::remove(studentCountStr.begin(), studentCountStr.end(), '"'), studentCountStr.end());
        studentCountStr.erase(std::remove(studentCountStr.begin(), studentCountStr.end(), ','), studentCountStr.end());
        data.studentCount = std::stoi(studentCountStr);
        std::string graduateCountStr;
        std::getline(iss, unusedField, '\t');
        std::getline(iss, graduateCountStr, '\t');
        data.graduateCount = std::stoi(graduateCountStr);
        std::getline(iss, unusedField, '\t');
        std::getline(iss, unusedField, '\t');
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
        std::cout << data.schoolName << ", " << data.departmentName << ", ";
        std::cout << data.dayNight << ", " << data.level << ", ";
        std::cout << data.studentCount << ", " << data.graduateCount << "\n";
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
        dataListExist = false;
        std::cout << "\nInput a file number ([0] Quit): ";
        std::string fileNumber;
        std::cin >> fileNumber;
        if (fileNumber == "0") {
          std::cout << "\n";
          return;
        }
        if (!IO::readData(fileNumber, dataList)) {
          std::cout << "\n### input" << fileNumber << ".txt does not exist! ###\n";
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