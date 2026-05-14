#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>

// ЗАВДАННЯ 1: КЛАСИ PAIR ТА RECTANGLE (УСПАДКУВАННЯ)

class Pair {
protected:
    double first;
    double second;

public:
    Pair(double f = 0.0, double s = 0.0) : first(f), second(s) {
        std::cout << "[LOG]: Створено об'єкт Pair" << std::endl;
    }

    void setFirst(double f) { first = f; }
    void setSecond(double s) { second = s; }

    double getFirst() const { return first; }
    double getSecond() const { return second; }

    double multiply() const {
        return first * second;
    }

    virtual void printInfo() const {
        std::cout << "Пара чисел: (" << first << "; " << second << ")" << std::endl;
        std::cout << "Добуток: " << multiply() << std::endl;
    }

    virtual ~Pair() {}
};

class Rectangle : public Pair {
public:
    Rectangle(double sideA = 0.0, double sideB = 0.0) : Pair(sideA, sideB) {
        std::cout << "[LOG]: Створено об'єкт Rectangle" << std::endl;
    }

    double calculatePerimeter() const {
        return 2 * (first + second);
    }

    double calculateArea() const {
        return multiply();
    }

    void printInfo() const override {
        std::cout << "=== Параметри прямокутника ===" << std::endl;
        std::cout << "Сторона A: " << first << std::endl;
        std::cout << "Сторона B: " << second << std::endl;
        std::cout << "Периметр:  " << calculatePerimeter() << std::endl;
        std::cout << "Площа:     " << calculateArea() << std::endl;
        std::cout << "==============================" << std::endl;
    }
};

// ЗАВДАННЯ 2: БІНАРНЕ ДЕРЕВО (ІЄРАРХІЯ ТА КОМПОЗИЦІЯ)

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void deleteTree(TreeNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        deleteTree(root);
        root = nullptr;
    }

    void insert(int value) {
        TreeNode* newNode = new TreeNode(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* temp = q.front();
            q.pop();

            if (temp->left == nullptr) {
                temp->left = newNode;
                return;
            }
            else {
                q.push(temp->left);
            }

            if (temp->right == nullptr) {
                temp->right = newNode;
                return;
            }
            else {
                q.push(temp->right);
            }
        }
    }

    void displayBFS() const {
        if (root == nullptr) {
            std::cout << "Дерево порожнє!" << std::endl;
            return;
        }

        std::cout << "BFS обхід дерева: ";
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            std::cout << "[" << current->data << "] ";
            q.pop();

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        std::cout << std::endl;
    }
};

// ЗАВДАННЯ 3: POINT ТА COLORPOINT (ОПЕРАТОРИ ТА КОПІЮВАННЯ)

class Point {
protected:
    int x;
    int y;

public:
    Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) {}

    Point(const Point& other) {
        this->x = other.x;
        this->y = other.y;
        std::cout << "[LOG]: Викликано конструктор копіювання Point" << std::endl;
    }

    Point& operator=(const Point& other) {
        if (this != &other) {
            this->x = other.x;
            this->y = other.y;
            std::cout << "[LOG]: Викликано оператор присвоювання Point" << std::endl;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "X: " << p.x << ", Y: " << p.y;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        std::cout << "Введіть X: "; is >> p.x;
        std::cout << "Введіть Y: "; is >> p.y;
        return is;
    }
};

class ColorPoint : public Point {
private:
    std::string color;

public:
    ColorPoint(int xVal = 0, int yVal = 0, std::string col = "None")
        : Point(xVal, yVal), color(col) {
    }

    ColorPoint(const ColorPoint& other) : Point(other) {
        this->color = other.color;
        std::cout << "[LOG]: Викликано конструктор копіювання ColorPoint" << std::endl;
    }

    ColorPoint& operator=(const ColorPoint& other) {
        if (this != &other) {
            Point::operator=(other); 
            this->color = other.color;
            std::cout << "[LOG]: Викликано оператор присвоювання ColorPoint" << std::endl;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const ColorPoint& cp) {
        os << static_cast<const Point&>(cp) << " | Колір: " << cp.color;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ColorPoint& cp) {
        is >> static_cast<Point&>(cp);
        std::cout << "Введіть назву кольору: ";
        is >> cp.color;
        return is;
    }
};

// МЕНЮ

void showMenu() {
    std::cout << "           ЛАБОРАТОРНА РОБОТА  #5         " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Завдання 1.13: Класи Pair та Rectangle" << std::endl;
    std::cout << "2. Завдання 2.13: Бінарне дерево (BFS)" << std::endl;
    std::cout << "3. Завдання 3.13: Point та ColorPoint" << std::endl;
    std::cout << "0. Вийти з програми" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Ваш вибір: ";
}

int main() {
    setlocale(LC_ALL, "Ukrainian");

    int choice;
    do {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Помилка вводу! Спробуйте ще раз." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            std::cout << "\n--- ТЕСТУВАННЯ ЗАВДАННЯ 1 ---" << std::endl;
            double a, b;
            std::cout << "Введіть довжини сторін прямокутника: ";
            std::cin >> a >> b;
            Rectangle myRect(a, b);
            myRect.printInfo();
            break;
        }
        case 2: {
            std::cout << "\n--- ТЕСТУВАННЯ ЗАВДАННЯ 2 ---" << std::endl;
            BinaryTree tree;
            int count, val;
            std::cout << "Скільки елементів додати у дерево? ";
            std::cin >> count;
            for (int i = 0; i < count; ++i) {
                std::cout << "Елемент #" << i + 1 << ": ";
                std::cin >> val;
                tree.insert(val);
            }
            tree.displayBFS();
            break;
        }
        case 3: {
            std::cout << "\n--- ТЕСТУВАННЯ ЗАВДАННЯ 3 ---" << std::endl;
            ColorPoint p1;
            std::cout << "Створення точки p1 (ввід):" << std::endl;
            std::cin >> p1;

            std::cout << "\nСтворення p2 через конструктор копіювання (p2 = p1):" << std::endl;
            ColorPoint p2 = p1;

            std::cout << "\nСтворення p3 та використання оператора присвоювання:" << std::endl;
            ColorPoint p3(1, 1, "Black");
            std::cout << "До присвоєння p3: " << p3 << std::endl;
            p3 = p1;

            std::cout << "\nРЕЗУЛЬТАТИ:" << std::endl;
            std::cout << "p1: " << p1 << std::endl;
            std::cout << "p2: " << p2 << std::endl;
            std::cout << "p3: " << p3 << std::endl;
            break;
        }
        case 0:
            std::cout << "Завершення роботи. До побачення!" << std::endl;
            break;
        default:
            std::cout << "Такого пункту меню не існує!" << std::endl;
        }
    } while (choice != 0);

    return 0;
}