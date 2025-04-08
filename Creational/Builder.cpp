#include <iostream>

// класс для видов транспорта
class Transport {
    private:
        std::string name_;
        bool hasGPS_;
        bool hasPassengerPlace_;
    public:
        void setName(std::string name) {
            name_ = name;
        };

        void setGPS(bool hasGPS) {
            hasGPS_ = hasGPS;
        };

        void setPassengerPlace(bool hasPassengerPlace) {
            hasPassengerPlace_ = hasPassengerPlace;
        };

        void info() const {
            std::cout << name_ << std::endl;
            std::cout << (hasGPS_ ? "with GPS" : "without GPS") << std::endl;
            std::cout << (hasPassengerPlace_ ? "with Passenger place" : "without Passenger place") << std::endl;
        };
};

// абстрактный класс-строитель
class TransportBuilder {
    public:
        virtual Transport buildTransport() = 0;
        virtual void buildName() = 0;
        virtual void buildGPS() = 0;
        virtual void buildPassengerPlace() = 0;
};

// класс-конструктор для легкового автомобиля
class PassengerCarBuider : public TransportBuilder {
    private:
        Transport transport_;
    public:
        Transport buildTransport() override {
            return transport_;
        };

        void buildName() override {
            transport_.setName("Passenger");
        };

        void buildGPS() override {
            transport_.setGPS(true);
        };

        void buildPassengerPlace() override {
            transport_.setPassengerPlace(true);
        };
};

// класс-конструктор для грузового автомобиля
class TruckCarBuider : public TransportBuilder {
    private:
        Transport transport_;
    public:
        Transport buildTransport() override {
            return transport_;
        };

        void buildName() override {
            transport_.setName("Truck");
        };

        void buildGPS() override {
            transport_.setGPS(false);
        };

        void buildPassengerPlace() override {
            transport_.setPassengerPlace(false);
        };
};

class Director {
    public:
        Transport makeTransport(TransportBuilder& builder) {
            builder.buildName();
            builder.buildGPS();
            builder.buildPassengerPlace();
            return builder.buildTransport();
        };
};

int main() {
    Director director;

    PassengerCarBuider passengerCarBuider;
    Transport passengerCar = director.makeTransport(passengerCarBuider);
    passengerCar.info();

    TruckCarBuider truckCarBuider;
    Transport truckCar = director.makeTransport(truckCarBuider);
    truckCar.info();

    return 0;
}