/*11327146 莊立聖 11327155 黃宇謙*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>

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

template <class T1, class T2> class TwoThreeTree {
  private:
    struct Node {
      T1 key;
      std::vector<T2> values;
      std::vector<Node*> children;
      Node* parent;
      int keyCount;
    };

    Node* root = nullptr;

    int treeHeight;

    int nodeCount;
  public:
    void insert(T1 key, T2 value) {}

    int height() { return treeHeight; }

    int nodeCount() { return nodeCount; }

    std::pair<T1, std::vector<T2>> rootData() { return std::make_pair(root->key, root->values); }
};

template <class T1, class T2> class AVLtree {
  private:
    struct Node {
      T1 key;
      std::vector<T2> values;
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
    void insert(T1 key, T2 value) {}

    int height() { return treeHeight; }

    int nodeCount() { return nodeCount; }

    std::pair<T1, std::vector<T2>> rootData() { return std::make_pair(root->key, root->values); }
};

template <class T1, class T2> class IO {
  public:
    static void readData(const std::string& fileName, std::vector<std::pair<T1, T2>>& dataList) {}

    static void displayNode(const std::vector<T2>& values) {}
};

template <class T1, class T2> class Menu {
  private:
    static void mission1() {}

    static void mission2() {}
  public:
    static void run() {}
};

int main () {
  Menu<int, Data>::run();
  return 0;
}

