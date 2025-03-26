
/*
 * Упрощает использование сложной системы
 * Скрывает детали реализации
 *
 * Пример - система управления "умными" устройствами.
 *
 * */

#include <iostream>

class Speaker {
    public:
        void on() {
            std::cout << "Колонка включена" << std::endl;
        };
        void off() {
            std::cout << "Колонка выключена" << std::endl;
        };
};

class Lamp {
    public:
        void on() {
            std::cout << "Освещение включено" << std::endl;
        };
        void off() {
            std::cout << "Освещение выключено" << std::endl;
        };
};

class AC {
    public:
        void on() {
            std::cout << "Кондиционер включен" << std::endl;
        };
        void off() {
            std::cout << "Кондиционер выключен" << std::endl;
        };
};

// Класс фасада в виде панели управления устройствами
class ControlPanel {
    private:
        Speaker speaker;
        Lamp lamp;
        AC ac;

    public:
        void atHome() {
            speaker.on();
            lamp.on();
            ac.on();
        };
        void toSleep() {
            speaker.off();
            lamp.off();
            ac.off();
        };
};

int main() {
    ControlPanel controlPanel;

    std::cout << "Я пришел домой" << std::endl;
    controlPanel.atHome();

    std::cout << "\nЯ ложусь спать" << std::endl;
    controlPanel.toSleep();

    return 0;
}
