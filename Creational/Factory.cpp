/*
 * клиентский код не зависит от конкретных классов, а работает только с интерфейсами или абстрактными классами
 * позволяет легко добавлять новые типы объектов, просто создавая новые подклассы фабрики
 *
 * */

#include <iostream>

// абстрактный класс для видов транспорта
// NOTE: объект абстрактного класса создать не получится (например так "Transport transport;")
class Transport {
    public:
        virtual void move() = 0; // конструкция "virtual ... = 0;" используется для обозначения абстрактного класса
};

// такая конструкция обозначает наследование класса Car от класса Transport
class Car : public Transport {
    public:
        // спецификатор "override" обозначает переопределение виртуального метода
        void move() override {
            std::cout << "Едет" << std::endl;
        };
};

class Ship : public Transport {
    public:
        void move() override {
            std::cout << "Плывет" << std::endl;
        };
};

class Airplane : public Transport {
    public:
        void move() override {
            std::cout << "Летит" << std::endl;
        };
};

// абстрактный класс для салона
class Market {
    public:
        // мы не можем создать объект класса Transport,
        // но мы можем описать общий механизм взаимодействия с наследниками класса Transport
        virtual Transport* create() = 0;
};

class CarMarket : public Market {
    public:
        Transport* create() override {
            return new Car();
        };
};

class ShipMarket : public Market {
    public:
        Transport* create() override {
            return new Ship();
        };
};

class AirplaneMarket : public Market {
    public:
        Transport* create() override {
            return new Airplane();
        };
};

int main() {
    CarMarket carMarket;
    Transport* car = carMarket.create();
    car->move();

    ShipMarket shipMarket;
    Transport* ship = shipMarket.create();
    ship->move();

    AirplaneMarket airplaneMarket;
    Transport* airplane = airplaneMarket.create();
    airplane->move();

    return 0;
}