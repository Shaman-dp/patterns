/*
 * используется для сохранения и восстановления состояния объекта без нарушения его инкапсуляции
 *
 * NOTE: инкапсуляция - контроль доступа к полям и методам объекта
 *       через модификаторы доступа (publiс, private, protected)
 *
 *  publiс    — открытый доступ
 *  private   — могут обращаться только методы данного класса
 *  protected — похож на private, только есть доступ ещё и у наследников класса
 *
 * если объект (Originator) содержит большие данные, то хранение множества копий может потреблять много памяти
 *
 * */

#include <iostream>
#include <vector>

// абстрактный класс снимка для сохранения состояния игрока
class Memento {
    public:
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual int getHP() = 0;
};

// класс снимка для хранения состояния
class GameMemento : public Memento {
    private:
        int x_, y_, hp_;
    public:
        GameMemento(int x, int y, int hp) : x_(x), y_(y), hp_(hp) {}

        // следующие три метода будут использоваться классом-создателем для восстановления состояния
        int getX() override {
            return x_;
        }

        int getY() override {
            return y_;
        }

        int getHP() override {
            return hp_;
        }
};

// класс создателя (Originator), состояния которого и надо будет сохранять
class Player {
    private:
        int x_, y_, hp_;
    public:
        Player(int startX, int startY, int startHP) : x_(startX), y_(startY), hp_(startHP) {}

        void move(int dx, int dy) {
            x_ += dx;
            y_ += dy;
        }

        void takeDamage(int damage) {
            hp_ -= damage;
            if (hp_ < 0) hp_ = 0;
        }

        void state() const {
            std::cout << "X= " << x_ << ", Y= " << y_ << ", HP= " << hp_ << std::endl;
        }

        // сохранение текущего состояния
        GameMemento* save() {
            return new GameMemento(x_, y_, hp_);
        }

        // восстановление состояния
        void restore(Memento* memento) {
            x_ = memento->getX();
            y_ = memento->getY();
            hp_ = memento->getHP();
        }
};

// класс-хранитель истории (Caretaker)
class GameHistory {
    private:
        std::vector<Memento*> history;
        Player* player_;
    public:
        GameHistory(Player* player): player_(player) {}

        // сохранение состояния
        void backup() {
            history.push_back(player_->save());
        }

        // откат состояния к предыдущему
        void undo() {
            if (!history.empty()) {
                player_->restore(history.back());
                // удаление состояния из истории
                history.pop_back();
                std::cout << "Отмена последнего действия" << std::endl;
            }
        }
};

int main() {
    Player* player = new Player(0, 0, 100);
    GameHistory* history = new GameHistory(player);

    player->state();
    history->backup(); // сохраняем состояние

    player->move(5, 10);
    player->takeDamage(30);
    player->state();
    history->backup(); // сохраняем состояние

    player->move(20, 5);
    player->takeDamage(40);
    player->state();

    history->undo(); // отмена последнего действия
    player->state();

    history->undo(); // откат еще на одно состояние назад
    player->state();

    delete player;
    delete history;

    return 0;
}
