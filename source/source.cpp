#include <iostream>
#include <string>

using namespace std;

class Transport {
protected:
    string name;
    double capacity;

public:
    Transport(string n, double c) : name(n), capacity(c) {}
    virtual void deliver() = 0;
    virtual ~Transport() {}
};

class Truck : public Transport {
private:
    string fuelType;

public:
    Truck(string n, double c, string fuel) : Transport(n, c), fuelType(fuel) {}

    void deliver() override {
        cout << "Грузовик \"" << name << "\" перевозит " << capacity
            << " тонн груза по трассе. Использует топливо: " << fuelType << ".\n";
    }
};

class Ship : public Transport {
private:
    double draftDepth;

public:
    Ship(string n, double c, double draft) : Transport(n, c), draftDepth(draft) {}

    void deliver() override {
        cout << "Судно \"" << name << "\" доставляет " << capacity
            << " тонн груза по морскому пути. Осадка судна: " << draftDepth << " м.\n";
    }
};

class Plane : public Transport {
private:
    int maxAltitude;

public:
    Plane(string n, double c, int altitude) : Transport(n, c), maxAltitude(altitude) {}

    void deliver() override {
        cout << "Самолёт \"" << name << "\" выполняет воздушную доставку "
            << capacity << " тонн груза. Максимальная высота полёта: " << maxAltitude << " м.\n";
    }
};

class TransportFactory {
public:
    virtual Transport* createTransport() = 0;
    virtual ~TransportFactory() {}
};

class TruckFactory : public TransportFactory {
public:
    Transport* createTransport() override {
        string name, fuelType;
        double capacity;
        cout << "Введите название грузовика: ";
        cin >> name;
        cout << "Введите грузоподъёмность (тонн): ";
        cin >> capacity;
        cout << "Введите тип топлива (бензин/дизель): ";
        cin >> fuelType;
        return new Truck(name, capacity, fuelType);
    }
};

class ShipFactory : public TransportFactory {
public:
    Transport* createTransport() override {
        string name;
        double capacity, draft;
        cout << "Введите название судна: ";
        cin >> name;
        cout << "Введите грузоподъёмность (тонн): ";
        cin >> capacity;
        cout << "Введите осадку судна (м): ";
        cin >> draft;
        return new Ship(name, capacity, draft);
    }
};

class PlaneFactory : public TransportFactory {
public:
    Transport* createTransport() override {
        string name;
        double capacity;
        int altitude;
        cout << "Введите название самолёта: ";
        cin >> name;
        cout << "Введите грузоподъёмность (тонн): ";
        cin >> capacity;
        cout << "Введите максимальную высоту полета (м): ";
        cin >> altitude;
        return new Plane(name, capacity, altitude);
    }
};

// Клиентский код
void createAndDeliver(TransportFactory& factory) {
    Transport* transport = factory.createTransport();
    transport->deliver();
    delete transport;
}

int main() {
    setlocale(LC_ALL, "ru");

    int choice;
    cout << "Выберите транспорт:\n1 - Грузовик \n2 - Судно \n3 - Самолёт \nВаш выбор: ";
    cin >> choice;

    if (choice == 1) {
        TruckFactory factory;
        createAndDeliver(factory);
    }
    else if (choice == 2) {
        ShipFactory factory;
        createAndDeliver(factory);
    }
    else if (choice == 3) {
        PlaneFactory factory;
        createAndDeliver(factory);
    }
    else {
        cout << "Некорректный ввод.\n";
        return 1;
    }

    return 0;
}
