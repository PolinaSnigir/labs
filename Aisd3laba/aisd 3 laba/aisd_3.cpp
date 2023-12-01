#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//
template <class T>
class StackNode {
public:
    T data;
    StackNode<T>* next;

    StackNode(T const& newData) : data(newData), next(nullptr) {}
};

template <class T>
class Stack {
private:
    StackNode<T>* top;
public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(T val) {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T popped = top->data;
        StackNode<T>* temp = top;
        top = top->next;
        delete temp;
        return popped;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top->data;
    }
};
//
struct Node {
    int key;
    Node* left, * right;
    int height;

    Node(int k) : key(k), left(NULL), right(NULL), height(1) {}
};
bool isValidCharacter(char c) {
    return (c == '(' || c == ')' || (c >= '0' && c <= '9'));
}

bool isValidBinaryTree(string s) {
    Stack<char> st;

    for (char c : s) {
        if (!isValidCharacter(c)) {
            cerr << "Ошибка: Неверный символ во входной строке." << endl;
            return false;
        }

        if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            if (st.isEmpty() || st.peek() != '(') {
                cerr << "Error: Mismatched parentheses." << endl;
                return false;
            }
            st.pop();
        }
    }

    if (!st.isEmpty()) {
        cerr << "Ошибка: Несоответствие скобок." << endl;
        return false;
    }

    return true;
}

Node* constructtree(string s, int* start) {
    if (!isValidBinaryTree(s)) {
        cerr << "Ошибка: Неверная структура бинарного дерева." << endl;
        return nullptr;
    }


    if (s.size() == 0 || *start >= s.size())
        return NULL;


    if (*start < s.size() && s[*start] == '(') {
        *start = *start + 1;
    }

    int num = 0;

    while (*start < s.size() && s[*start] != '(' && s[*start] != ')') {
        int num_here = (int)(s[*start] - '0');
        num = num * 10 + num_here;
        *start = *start + 1;
    }

    struct Node* root = NULL;
    if (num > 0)
        root = new Node(num);

    if (*start < s.size() && s[*start] == '(') {
        *start = *start + 1;
        root->left = constructtree(s, start);
    }

    if (*start < s.size() && s[*start] == ')') {
        *start = *start + 1;
        return root;
    }

    if (*start < s.size() && s[*start] == '(') {
        *start = *start + 1;
        root->right = constructtree(s, start);
    }
    if (*start < s.size() && s[*start] == ')') {
        *start = *start + 1;
    }
    return root;
}

void preorder(Node* root) {
    if (root == NULL)
        return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

//
class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1) {
            if (key < node->left->key) {
                return rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balance < -1) {
            if (key > node->right->key) {
                return rotateLeft(node);
            }
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;

                if (!temp) {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1) {
            if (getBalance(root->left) >= 0)
                return rotateRight(root);
            else {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }

        if (balance < -1) {
            if (getBalance(root->right) <= 0)
                return rotateLeft(root);
            else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        return root;
    }

    Node* search(Node* root, int key) {
        if (!root || root->key == key)
            return root;

        if (key < root->key)
            return search(root->left, key);

        return search(root->right, key);
    }

    void inOrder(Node* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void preOrder(Node* root) {
        if (root) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void postOrder(Node* root) {
        if (root) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->key << " ";
        }
    }

public:
    AVLTree() : root(NULL) {}

    void insert(int key) {  //вставка
        root = insert(root, key);
    }

    void remove(int key) {     //удаление
        root = deleteNode(root, key);
    }

    Node* find(int key) {      //поиск
        return search(root, key);
    }

    void breadthFirstTraversal() {  //обход в ширину 
        if (!root) return;

        Stack<Node*> currentLevel, nextLevel;
        currentLevel.push(root);

        while (!currentLevel.isEmpty()) {
            Node* current = currentLevel.peek();
            currentLevel.pop();

            cout << current->key << " ";

            if (current->right) nextLevel.push(current->right);
            if (current->left) nextLevel.push(current->left);

            if (currentLevel.isEmpty()) {
                swap(currentLevel, nextLevel);
            }
        }
    }

    void depthFirstTraversal() { //обход в глубину
        cout << "Inorder: "; //симметричный 
        inOrder(root);
        cout << endl;

        cout << "Preorder: ";  //прямой
        preOrder(root);
        cout << endl;

        cout << "Postorder: ";  //обратный
        postOrder(root);
        cout << endl;
    }
};

//
int main() {
    setlocale(LC_ALL, "Russian");
    ifstream inputFile("C:\\Users\\polinasnigir\\source\\repos\\aisd 3 laba\\input.txt"); // Предполагается, что ввод хранится в файле с именем "input.txt"
    if (!inputFile.is_open()) {
        cerr << "Невозможно открыть файл." << endl;
        return 1;
    }

    string s;
    getline(inputFile, s);
    inputFile.close();

    int start = 0;
    Node* root = constructtree(s, &start);

    if (root != nullptr) {
        cout << "Преобразование в прямом порядке:";
        preorder(root);
        cout << endl;
    }

    
    AVLTree avl;
   
    Stack<Node*> tempStack;
    tempStack.push(root);

    while (!tempStack.isEmpty()) {
        Node* current = tempStack.peek();
        tempStack.pop();

        avl.insert(current->key);

        if (current->right) tempStack.push(current->right);
        if (current->left) tempStack.push(current->left);
    }

    cout << "Обход дерева в ширину (AVL): ";
    avl.breadthFirstTraversal();
    cout << endl;

    cout << "Обход дерева в глубину (AVL): ";
    cout << endl;
    avl.depthFirstTraversal();
    cout << endl;

    int delete_element = 5;
    avl.remove(delete_element);

    cout << "Дерево после удаления "<<delete_element<<": ";
    avl.breadthFirstTraversal();
    cout << endl;

    int keyToFind = 7;
    Node* foundNode = avl.find(keyToFind);
    if (foundNode)
        cout << keyToFind << " найдено в дереве." << endl;
    else
        cout << keyToFind << " не найдено в дереве." << endl;

    int element_to_add = 10;
    avl.insert(element_to_add);
    cout << "Дерево после добавления " << element_to_add << ": ";
    avl.breadthFirstTraversal();
    cout << endl;

    return 0;
}
