/*
 * Адаптер позволяет объекту работать с другим интерфейсом, который он изначально не поддерживает.
 *
 * */

#include <iostream>

class Socket {
    public:
        int getVoltage() {
            return 220;
        }
};

class Device {
    public:
        void connect(int voltage) {
            if (voltage == 110) {
                std::cout << "Устройство работает" << std::endl;
            } else {
                std::cout << "Устройство отключено (Неправильное напряжение: " << voltage << "V)" << std::endl;
            }
        }
};

class SocketAdapter {
    private:
        // использование Socket* позволяет адаптеру работать с оригинальным объектом без дублирования
        Socket* socket_;

    public:
        SocketAdapter(Socket* socket) : socket_(socket) {}

        int adaptVoltage() {
            return socket_->getVoltage() / 2;
        }
};

int main() {
    // объект "socket" создаётся в стеке
    Socket socket;
    Device device;

    /*
     * если необходимо создать объект в куче (heap), то:
     * Socket* socket = new Socket();
     * SocketAdapter adapter(socket);
     * device.connect(socket->getVoltage());
     * delete socket; // не забываем удалить объект после использования
     * */

    // попытка подключить устройство к розетке неподходящим напряжением
    device.connect(socket.getVoltage());

    SocketAdapter adapter(&socket);

    // подключение устройства через адаптер
    device.connect(adapter.adaptVoltage());

    return 0;
}