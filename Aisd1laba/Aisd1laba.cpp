#include <iostream>
#include <stdexcept>
using namespace std;

struct Elem{
    string data; 
    Elem* next, * prev;
};

class List{
    Elem* Head, * Tail;
    int Count;
public:
    List();
    List(const List&);
    ~List();
    int GetCount();
    void DelAll();
    void Del(int pos = 0);
    void Insert(int pos = 0);
    void AddTail(string n);
    void AddHead(string n);
    void Print();
    void Print(int pos);
    List operator - ();
};

List::List(){
    Head = Tail = NULL;
    Count = 0;
}

List::List(const List& L){
    Head = Tail = NULL;
    Count = 0;
    Elem* temp = L.Head;
    while (temp != 0){
        AddTail(temp->data);
        temp = temp->next;
    }
}

List::~List(){
    DelAll();
}

void List::AddHead(string n){
    Elem* temp = new Elem;
    temp->prev = 0;
    temp->data = n;
    temp->next = Head;
    if (Head != 0)
        Head->prev = temp;
    if (Count == 0)
        Head = Tail = temp;
    else
        Head = temp;
    Count++;
}

void List::AddTail(string n){
    Elem* temp = new Elem;
    temp->next = 0;
    temp->data = n;
    temp->prev = Tail;
    if (Tail != 0)
        Tail->next = temp;
    if (Count == 0)
        Head = Tail = temp;
    else
        Tail = temp;
    Count++;
}

void List::Insert(int pos){
    if (pos == 0){
        cout << "Введите позицию, на месте которой добавится элемент: ";
        cin >> pos;

    }
    if (pos < 1 || pos > Count + 1){
        cout << "Неверная позиция\n";
        return;
    }
    if (pos == Count + 1){
        string data;
        cout << "Введите элемент: ";
        cin >> data;
        AddTail(data);
        return;
    }
    else if (pos == 1){
        string data;
        cout << "Введите элемент: ";
        cin >> data;
        AddHead(data);
        return;
    }
    int i = 1;
    Elem* Ins = Head;

    while (i < pos){
        Ins = Ins->next;
        i++;
    }
    Elem* PrevIns = Ins->prev;
    Elem* temp = new Elem;

    cout << "Введите элемент: ";
    cin >> temp->data;

    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

void List::Del(int pos){
    if (pos == 0){
        cout << "Введите позицию: ";
        cin >> pos;
    }
    if (pos < 1 || pos > Count){
        cout << "Неверная позиция\n";
        return;
    }
    int i = 1;
    Elem* Del = Head;
    while (i < pos){
        Del = Del->next;
        i++;
    }
    Elem* PrevDel = Del->prev;
    Elem* AfterDel = Del->next;

    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    delete Del;

    Count--;
}

void List::Print(int pos){
    if (pos < 1 || pos > Count){
        cout << "Неверная позиция\n";
        return;
    }
    Elem* temp;

    if (pos <= Count / 2){
        temp = Head;
        int i = 1;
        while (i < pos)
        {
            temp = temp->next;
            i++;
        }
    }
    else{
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            temp = temp->prev;
            i++;
        }
    }
    cout << pos << " элемент: ";
    cout << temp->data << endl;
}

void List::Print(){
    if (Count != 0){
        Elem* temp = Head;
        cout << "( ";
        while (temp->next != 0){
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}

void List::DelAll(){
    while (Count != 0)
        Del(1);
}

int List::GetCount(){
    return Count;
}

List List::operator - (){
    List Result;
    Elem* temp = Head;
    while (temp != 0){
        Result.AddHead(temp->data);
        temp = temp->next;
    }
    return Result;
}


void LinkedList() {
    List L;
    const int n = 10;
    string a[n];
    for (int i = 0;i < n;i++) {
        std::cout << "Введите " << (i + 1) << " элемент:";
        string x;
        std::cin >> x;
        a[i] = x;

    }
    for (int i = 0; i < n; i++)
        if (i <= 4)
            L.AddHead(a[i]);
        else
            L.AddTail(a[i]);

    cout << "Список:";
    L.Print();
    cout << endl;
  
    L.Insert();
    cout << "Список:";
    L.Print();

    std::cout << "Введите позицию элемента, который вы хотите вывести:";
    int x1;
    cin >> x1;
    L.Print(x1);

    std::cout << "Введите позицию элемента, который вы хотите удалить:";
    int x2;
    cin >> x2;
    L.Del(x2);
    cout << "Список:";
    L.Print();

    std::cout << "Введите элемент, который вы хотите вставить в конец списка:";
    string x4;
    cin >> x4;
    L.AddTail(x4);
    cout << "Список:";
    L.Print();

    std::cout << "Введите элемент, который вы хотите вставить в начало списка:";
    string x5;
    cin >> x5;
    L.AddHead(x5);
    cout << "Список:";
    L.Print();

    std::cout << "Переворот списка:";
    List reversedList = -L;
    cout << "Список:";
    reversedList.Print();

    cout << "Длина списка: ";
    int len=L.GetCount();
    cout << len << "\n";

    std::cout << "Удаление списка\n";
    L.DelAll();
  
}
//
//
//
template <class T>
class DynamicArray {
private:
    T* arr; 
    int size; 
    int capacity; 

public:
    DynamicArray() {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void add(T value) {
        if (size == capacity) {
            T* temp = new T[capacity * 2]; 
            for (int i = 0; i < size; i++) {
                temp[i] = arr[i]; 
            }
            delete[] arr; 
            arr = temp; 
            capacity *= 2; 
        }
        arr[size] = value; 
        size++; 
    }

    void set(int index, T value) {
        if (index >= 0 && index < size) {
            arr[index] = value; 
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    T get(int index) {

        if (index >= 0 && index < size) {
            return arr[index]; 
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    int getSize() {
        return size;
    }

    void remove(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1]; 
            }
            size--; 
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }
};
void DynamicArr() {
    DynamicArray<std::string> array;
    int elements;
    std::cout << "Введите количесво элементов массива: ";
    std::cin >> elements;
    for (int i = 0;i < elements;i++) {
        std::cout << "Введите " << (i + 1) << " элемент массива:";
        std::string x;
        std::cin >> x;
        array.add(x);
    }

    std::cout << "Размер: " << array.getSize() << std::endl;

    for (int i = 0; i < array.getSize(); i++) {
        std::cout << "Элемент по индексу " << i << ": " << array.get(i) << std::endl;
    }
    std::cout << "Введите индекс элемента массива, который вы хотите заменить:";
    int Index;
    std::cin >> Index;
    if (Index<0 || Index>array.getSize() - 1)
        cout << "Ошибка\n";
    else {
        std::cout << "Введите элемент массива:";
        std::string Element;
        std::cin >> Element;
        array.set(Index, Element);
        std::cout << "Массив после замены элемента:" << std::endl;
        for (int i = 0;i < array.getSize();i++) {
            std::cout << "Элемент по индексу " << i << ": " << array.get(i) << std::endl;
            std::cout << "Элемент по индексу " << Index << " после замены :" << array.get(Index) << std::endl;

        }
    }

    std::cout << "Введите индекс элемента массива, который вы хотите удалить:";
    int Index1;
    std::cin >> Index1;
    if (Index<0 || Index>array.getSize() - 1)
        cout << "Ошибка\n";
    else {
        array.remove(Index1);
        std::cout << "Размер после удаления: " << array.getSize() << std::endl;
        std::cout << "Массив после удаления элемента:" << std::endl;
        for (int i = 0;i < array.getSize();i++) {
            std::cout << "Элемент по индексу " << i << ": " << array.get(i) << std::endl;

        }
        std::cout << "Элемент по индексу " << Index1 << " после удаления :" << array.get(Index1) << std::endl;
    }
    
    std::cout << "Введите элемента массива, который вы хотите добавить:";
    std::string x;
    std::cin >> x;
    array.add(x);
    std::cout << "Размер: " << array.getSize() << std::endl;

    for (int i = 0; i < array.getSize(); i++) {
        std::cout << "Элемент по индексу " << i << ": " << array.get(i) << std::endl;
    }

   
}
//
//
//
template <class T>
class Stack {
private:
    Node<T>* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            top = newNode;
        }
        else {
            top->next = newNode;
            newNode->prev = top;
            top = newNode;
        }
        size++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Стек пустой");
        }
        T popped = top->data;
        Node<T>* temp = top;
        top = top->prev;
        if (top != nullptr) {
            top->next = nullptr;
        }
        delete temp;
        size--;
        return popped;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Стек пустой");
        }
        return top->data;
    }
};

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}
bool isFunction(const std::string& token) {
    return token == "sin" || token == "cos";
}
bool isOperand(const std::string& token) {
    return std::isdigit(token[0]);
}

int getPrecedence(const std::string& operatorToken) {
    if (operatorToken == "+" || operatorToken == "-") {
        return 1;
    }
    else if (operatorToken == "*" || operatorToken == "/") {
        return 2;
    }
    else if (operatorToken == "^") {
        return 3;
    }
    else {
        return 0;
    }
}

std::string infixToRPN(const std::string& infixExpression) {
    Stack<std::string> operatorStack;
    std::stringstream postfixExpression;

    std::istringstream iss(infixExpression);
    std::string token;
    while (iss >> token) {
        if (isOperand(token)) {
            postfixExpression << token << " ";
        }
        else if (isFunction(token)) {
            operatorStack.push(token);
        }
        else if (isOperator(token)) {
            while (!operatorStack.isEmpty() && isOperator(operatorStack.peek()) && getPrecedence(operatorStack.peek()) >= getPrecedence(token)) {
                postfixExpression << operatorStack.peek() << " ";
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
        else if (token == "(") {
            operatorStack.push(token);
        }
        else if (token == ")") {
            while (!operatorStack.isEmpty() && operatorStack.peek() != "(") {
                postfixExpression << operatorStack.peek() << " ";
                operatorStack.pop();
            }

            if (!operatorStack.isEmpty() && operatorStack.peek() == "(") {
                operatorStack.pop();
            }
            else {
                //    // Mismatched parentheses
                return "";
            }
        }
    }

    while (!operatorStack.isEmpty()) {

        postfixExpression << operatorStack.peek() << " ";
        operatorStack.pop();
    }

    return postfixExpression.str();
}

void StackSortSt() {
    setlocale(LC_ALL, "Russian");
    std::string infixExpression;
    std::cout << "Введите инфиксное выражение (отделять символы пробелом): ";
    std::cin.get();
    std::getline(std::cin, infixExpression);

    std::string postfixExpression = infixToRPN(infixExpression);
    std::cout << "Постфиксное выражение: " << postfixExpression << std::endl;

}
//
//
//

int prompt_menu_item() {
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1. Двусвязный список\n"
        << "2. Динамичиский массив\n"
        << "3. Стек\n"
        << "4. Выход\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}
void main() {
    int x = 0;
    setlocale(LC_ALL, "Russian");
    while (x == 0) {
        int variant = prompt_menu_item();

        switch (variant) {
        case 1:
            cout << "Двусвязный список " << endl;
            LinkedList();
            break;
        case 2:
            cout << "Динамичиский массив" << endl;
            DynamicArr();
            break;
        case 3:
            cout << "Стек" << endl;
            StackSortSt();

            break;
        case 4:
            cout << "Выход из программы..." << endl;
            exit(EXIT_SUCCESS);
            break;
        default:
            cerr << "Вы выбрали неверный вариант" << endl;
        }
    }
}














