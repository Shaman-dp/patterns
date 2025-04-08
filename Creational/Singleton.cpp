/*
 *
 * Гарантирует наличие единственного экземпляра класса
 * Глобальная точка доступа
 *
 * */

#include <iostream>

class Singleton {
    private:
        // NOTE: Статические переменные и методы относятся к классу,
        // а не к конкретному объекту (т.е. переменная будет общей для всех объектов класса).
        static Singleton* p;

        // Скрываем конструктор, чтобы невозможно было создать объект из пользовательского кода
        Singleton() {
            std::cout << "Одиночка создан" << std::endl;
        };

    public:
        // Удаляем конструктор копирования и оператор присваивания
        // "= delete" гарантирует, что даже у наследников методы будут недоступны
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        // метод для доступа к единственному экземпляру
        // static потому что можно обратиться без создания объекта
        static Singleton* getInstance() {
            if (p == nullptr) {
                p = new Singleton();
            }
            return p;
        }

        void showMessage() {
            std::cout << "some data" << std::endl;
        }

        static void destroy() {
            if (p != nullptr) {
                delete p;
                p = nullptr;
                std::cout << "Одиночка удален" << std::endl;
            }
        }
};

// Определение указателя на класс
// NOTE: Статические переменные объявляются в классе, но инициализируются отдельно вне его
Singleton* Singleton::p = nullptr;

int main() {

    Singleton* singleton1 = Singleton::getInstance();
    singleton1->showMessage();

    Singleton* singleton2 = Singleton::getInstance();
    singleton2->showMessage();

    // проверка, что объекты одинаковые
    if (singleton1 == singleton2) {
        std::cout << "указывают на один объект" << std::endl;
    }

    // Освобождаем память
    Singleton::destroy();

    return 0;
}
