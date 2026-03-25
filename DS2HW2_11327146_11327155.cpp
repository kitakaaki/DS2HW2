/*11327146 莊立聖 11327155 黃宇謙*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Data {
  int serialNumber = 0;
  std::string schoolCode;
  std::string schoolName;
  std::string departmentCode;
  std::string departmentName;
  std::string dayNight;
  std::string level;
  int studentCount = 0;
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

    void rotateLL(Node* node) {}

    void rotateRR(Node* node) {}

    void rotateLR(Node* node) {}

    void rotateRL(Node* node) {}
  public:
    void insert(std::string key, int value) {}

    int height() { return treeHeight; }

    int count() { return nodeCount; }

    void clear() {}

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
      }
      if (avlTreeExist)
        std::cout << "### AVL tree has been built. ###\n";
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

