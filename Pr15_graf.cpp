#include <iostream>
#include <fstream>
#include <Windows.h>

struct DairyProduct {
    char name[50];
    double weight;
    double fatContent;
    char manufacturer[50];
    double price;
};

// Функция для ввода данных
void inputProduct(DairyProduct& product) {
    std::cout << "Введите название: ";
    std::cin >> product.name;
    std::cout << "Введите вес (кг): ";
    std::cin >> product.weight;
    std::cout << "Введите жирность (%): ";
    std::cin >> product.fatContent;
    std::cout << "Введите производителя: ";
    std::cin >> product.manufacturer;
    std::cout << "Введите цену: ";
    std::cin >> product.price;
}

// Функция для вывода данных
void printProduct(const DairyProduct& product) {
    std::cout << "Название: " << product.name << "\n"
        << "Вес: " << product.weight << " кг\n"
        << "Жирность: " << product.fatContent << " %\n"
        << "Производитель: " << product.manufacturer << "\n"
        << "Цена: " << product.price << " руб\n";
}

// Функция для записи данных в файл
void writeToFile(const char* filename, const DairyProduct* products, int count, double totalCost) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Ошибка открытия файла для записи\n";
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
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cout << "Ошибка открытия файла для чтения\n";
        return;
    }
    char line[256];
    while (inFile.getline(line, sizeof(line))) {
        std::cout << line << "\n";
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

    std::cout << "Введите количество продуктов: ";
    std::cin >> count;

    if (count > maxProducts) {
        std::cout << "Превышено максимальное количество продуктов\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "\nПродукт " << i + 1 << ":\n";
        inputProduct(products[i]);
        totalCost += products[i].price;
    }

    std::cout << "\nСуммарная стоимость всех продуктов: " << totalCost << " руб\n";

    // Запись данных в файл
    writeToFile(filename, products, count, totalCost);

    // Чтение данных из файла
    std::cout << "\nДанные из файла:\n";
    readFromFile(filename);

    return 0;
}
