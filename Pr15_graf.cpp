#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

struct DairyProduct {
    char name[50];
    double weight;
    double fatContent;
    char manufacturer[50];
    double price;
};

// Функция для ввода данных
void inputProduct(DairyProduct& product) {
    cout << "Введите название: ";
    cin >> product.name;
    cout << "Введите вес (кг): ";
    cin >> product.weight;
    cout << "Введите жирность (%): ";
    cin >> product.fatContent;
    cout << "Введите производителя: ";
    cin >> product.manufacturer;
    cout << "Введите цену: ";
    cin >> product.price;
}

// Функция для вывода данных
void printProduct(const DairyProduct& product) {
    cout << "Название: " << product.name << "\n"
        << "Вес: " << product.weight << " кг\n"
        << "Жирность: " << product.fatContent << " %\n"
        << "Производитель: " << product.manufacturer << "\n"
        << "Цена: " << product.price << " руб\n";
}

// Функция для записи данных в файл
void writeToFile(const char* filename, const DairyProduct* products, int count, double totalCost) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Ошибка открытия файла для записи\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        outFile << "Название: " << products[i].name << "\n"
            << "Вес: " << products[i].weight << " кг\n"
            << "Жирность: " << products[i].fatContent << " %\n"
            << "Производитель: " << products[i].manufacturer << "\n"
            << "Цена: " << products[i].price << " руб\n\n";
    }
    outFile << "Суммарная стоимость всех продуктов: " << totalCost << " руб\n";
    outFile.close();
}

// Функция для чтения данных из файла
void readFromFile(const char* filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения\n";
        return;
    }
    char line[256];
    while (inFile.getline(line, sizeof(line))) {
        cout << line << "\n";
    }
    inFile.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int maxProducts = 100; // Максимальное количество продуктов
    DairyProduct products[maxProducts];
    int count = 0;
    char filename[] = "dairy_products.txt";
    double totalCost = 0;

    cout << "Введите количество продуктов: ";
    cin >> count;

    if (count > maxProducts) {
        cout << "Превышено максимальное количество продуктов\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        cout << "\nПродукт " << i + 1 << ":\n";
        inputProduct(products[i]);
        totalCost += products[i].price;
    }

    cout << "\nСуммарная стоимость всех продуктов: " << totalCost << " руб\n";

    // Запись данных в файл
    writeToFile(filename, products, count, totalCost);

    // Чтение данных из файла
    cout << "\nДанные из файла:\n";
    readFromFile(filename);

    return 0;
}
