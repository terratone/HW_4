//  Реализовать базу данных ГАИ по штрафным квитанциям с помощью бинарного дерева. Ключом будет служить номер автомашины, значением узла — список 
//  правонарушений. Если квитанция добавляется в первый раз, то в дереве появляется новый узел, а в списке данные по правонарушению; если нет, то 
//  данные заносятся в существующий список. Необходимо также реализовать следующие операции:
//  Полная распечатка базы данных(по номерам машин и списку правонарушений, числящихся за ними);
//  Распечатка данных по заданному номеру;
//  Распечатка данных по диапазону номеров;

#include <iostream>
#include <list> // Для использования списков
#include <string>

using namespace std;

// Структура данных для узла списка правонарушений
struct Violation {
    string description;
    int fineAmount;

    Violation(string desc, int amount) : description(desc), fineAmount(amount) {}
};

// Структура данных для узла дерева базы данных ГАИ
struct TreeNode {
    string carNumber;
    list<Violation> violations;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string num) : carNumber(num), violations(), left(nullptr), right(nullptr) {}
};

class TrafficPoliceDatabase {
private:
    TreeNode* root;

public:
    TrafficPoliceDatabase() : root(nullptr) {}

    // Метод добавления квитанции (правонарушения) в базу данных
    void addViolation(const string& carNumber, const string& violationDesc, int fineAmount) {
        root = addViolationHelper(root, carNumber, violationDesc, fineAmount);
    }

    // Вспомогательный метод для добавления квитанции
    TreeNode* addViolationHelper(TreeNode* node, const string& carNumber, const string& violationDesc, int fineAmount) {
        if (node == nullptr) {
            node = new TreeNode(carNumber);
            node->violations.push_back(Violation(violationDesc, fineAmount));
        }
        else if (carNumber == node->carNumber) {
            node->violations.push_back(Violation(violationDesc, fineAmount));
        }
        else if (carNumber < node->carNumber) {
            node->left = addViolationHelper(node->left, carNumber, violationDesc, fineAmount);
        }
        else {
            node->right = addViolationHelper(node->right, carNumber, violationDesc, fineAmount);
        }
        return node;
    }

    // Метод для печати всей базы данных
    void printDatabase() {
        printDatabaseHelper(root);
    }

    // Вспомогательный метод для печати базы данных (обход в порядке инфикса)
    void printDatabaseHelper(TreeNode* node) {
        if (node != nullptr) {
            printDatabaseHelper(node->left);
            cout << "Car number: " << node->carNumber << std::endl;
            for (const auto& violation : node->violations) {
                cout << "Violation: " << violation.description << ", Amount of fine: " << violation.fineAmount << std::endl;
            }
            printDatabaseHelper(node->right);
        }
    }

    // Метод для печати данных по заданному номеру машины
    void printDataByCarNumber(const string& carNumber) {
        printDataByCarNumberHelper(root, carNumber);
    }

    // Вспомогательный метод для печати данных по заданному номеру (обход в глубину)
    void printDataByCarNumberHelper(TreeNode* node, const std::string& carNumber) {
        if (node != nullptr) {
            if (carNumber == node->carNumber) {
                cout << "Car number: " << node->carNumber << endl;
                for (const auto& violation : node->violations) {
                    cout << "Violation: " << violation.description << ", Amount of fine: " << violation.fineAmount << endl;
                }
            }
            else if (carNumber < node->carNumber) {
                printDataByCarNumberHelper(node->left, carNumber);
            }
            else {
                printDataByCarNumberHelper(node->right, carNumber);
            }
        }
    }

    // Метод для печати данных по диапазону номеров
    void printDataInRange(const string& startNumber, const string& endNumber) {
        printDataInRangeHelper(root, startNumber, endNumber);
    }

    // Вспомогательный метод для печати данных по диапазону номеров (обход в глубину)
    void printDataInRangeHelper(TreeNode* node, const string& startNumber, const string& endNumber) {
        if (node != nullptr) {
            if (startNumber <= node->carNumber) {
                printDataInRangeHelper(node->left, startNumber, endNumber);
            }
            if (startNumber <= node->carNumber && node->carNumber <= endNumber) {
                cout << "Car number: " << node->carNumber << endl;
                for (const auto& violation : node->violations) {
                    cout << "Violation: " << violation.description << ", Amount of fine: " << violation.fineAmount << endl;
                }
            }
            if (node->carNumber <= endNumber) {
                printDataInRangeHelper(node->right, startNumber, endNumber);
            }
        }
    }
};

int main() {


    TrafficPoliceDatabase database;

    database.addViolation("AA1234BB", "Speeding", 1000);
    database.addViolation("AA1234BB", "Traffic rules violation", 1500);
    database.addViolation("BC5678DF", "Illegal parking", 500);

    cout << "Complete printout of database:\n";
    database.printDatabase();

    cout << "\nPrintout by car number (AA1234BB):\n";
    database.printDataByCarNumber("AA1234BB");

    cout << "\nPrinting data by number range (AA0000AA - ZZ9999ZZ):\n";
    database.printDataInRange("AA0000AA", "ZZ9999ZZ");

    return 0;
}