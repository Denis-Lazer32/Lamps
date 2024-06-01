#include <iostream>
#include <vector>
#include <cassert>
#include <locale.h>
#include <math.h>

using namespace std;

class Lamp {
public:
    // Конструктор по умолчанию
    Lamp() : lightPower(0), powerConsumption(0), isOn(false) {}

    // Конструктор инициализации
    Lamp(float lightPower, float powerConsumption) : lightPower(lightPower), powerConsumption(powerConsumption), isOn(false) {}

    // Конструктор копирования
    Lamp(const Lamp& other) : lightPower(other.lightPower), powerConsumption(other.powerConsumption), isOn(other.isOn) {}

    // Методы доступа
    float getLightPower() const {
        return lightPower;
    }

    float getPowerConsumption() const {
        return powerConsumption;
    }

    bool isTurnedOn() const {
        return isOn;
    }

    // Методы управления лампой
    void turnOn() {
        isOn = true;
    }

    void turnOff() {
        isOn = false;
    }

    // Метод идентификации
    virtual string identify() const {
        return "Lamp";
    }

private:
    float lightPower; // Излучаемая сила света лампы
    float powerConsumption; // Потребляемая мощность лампы
    bool isOn; // Флаг, указывающий на включение/выключение лампы
};

class LED_Lamp : public Lamp {
public:
    // Конструктор по умолчанию
    LED_Lamp() : Lamp(), redPower(0), greenPower(0), bluePower(0), redIntensity(0), greenIntensity(0), blueIntensity(0) {}

    // Конструктор инициализации
    LED_Lamp(float lightPower, float powerConsumption, float redPower, float greenPower, float bluePower,
        float redIntensity, float greenIntensity, float blueIntensity)
        : Lamp(lightPower, powerConsumption), redPower(redPower), greenPower(greenPower), bluePower(bluePower),
        redIntensity(redIntensity), greenIntensity(greenIntensity), blueIntensity(blueIntensity) {}

    // Конструктор копирования
    LED_Lamp(const LED_Lamp& other)
        : Lamp(other), redPower(other.redPower), greenPower(other.greenPower), bluePower(other.bluePower),
        redIntensity(other.redIntensity), greenIntensity(other.greenIntensity), blueIntensity(other.blueIntensity) {}

    // Методы доступа для дополнительных свойств LED
    float getRedPower() const {
        return redPower;
    }

    float getGreenPower() const {
        return greenPower;
    }

    float getBluePower() const {
        return bluePower;
    }

    float getRedIntensity() const {
        return redIntensity;
    }

    float getGreenIntensity() const {
        return greenIntensity;
    }

    float getBlueIntensity() const {
        return blueIntensity;
    }

    // Метод для расчёта текущей силы света
    float calculateLightForce() const {
        float totalIntensity = redIntensity + greenIntensity + blueIntensity;
        float redForce = redPower * (redIntensity / totalIntensity);
        float greenForce = greenPower * (greenIntensity / totalIntensity);
        float blueForce = bluePower * (blueIntensity / totalIntensity);
        return redForce + greenForce + blueForce;
    }

    // Метод идентификации
    string identify() const override{
        return "LED Lamp";
    }

private:
    float redPower; // Максимальная мощность красного светодиода
    float greenPower; // Максимальная мощность зелёного светодиода
    float bluePower; // Максимальная мощность синего светодиода
    float redIntensity; // Интенсивность красного светодиода
    float greenIntensity; // Интенсивность зелёного светодиода
    float blueIntensity; // Интенсивность синего светодиода
};

class Room {
public:
    // Конструктор по умолчанию
    Room() : length(10), width(10), height(10) {}

    // Конструктор инициализации
    Room(float lenght, float width, float height, vector<vector<Lamp>> lamps) : length(lenght), width(width), height(height),
        lamps(lamps) {}

    // Конструктор копирования
    Room(const Room& other) : length(other.length), width(other.width), height(other.height) {}

    // Методы доступа
    float getLength() const {
        return length;
    }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

    // Методы для вычислений
    double calculateIlluminance(int x, int y, int z) {
        double illuminance = 0.0;
        // Проходим по всем лампам и суммируем вклад каждой в освещенность
        for (const auto& row : lamps) {
            for (const auto& lamp : row) {
                if (lamp.isTurnedOn()) {
                    double distance = sqrt(pow(sqrt(pow(x, 2) + pow(y, 2)), 2) + pow(z, 2)); // Расстояние от лампы до точки
                    illuminance += lamp.getLightPower() / (4 * 3.14 * pow(distance, 2)) * (z / distance); // Формула расчета освещенности от точечного источника
                }
            }
        }
        return illuminance;
    }

    double calculatePower() {
        float power = 0.0;
        // Проходим по всем лампам и суммируем мощность
        for (const auto& row : lamps)
            for (const auto& lamp : row)
                if (lamp.isTurnedOn())
                    power += lamp.getPowerConsumption();
        return power;
    }

    // Метод идентификации
    virtual string identify() const {
        return "Room";
    }
private:
    float length;
    float width;
    float height;
    vector<vector<Lamp>> lamps;
};


// Тестируем конструктор по умолчанию
void testDefaultConstructor();

// Тестируем конструктор инициализации
void testInitializationConstructor();

// Тестируем конструктор копирования
void testCopyConstructor();

// Тестируем методы доступа
void testAccessMethods();

// Функция для расчета освещенности точки в кабинете
double calculateIlluminance(const vector<vector<Lamp>>& lamps, int x, int y, int z);

// Функция для расчета мощности элетропотребления
double calculatePower(const vector<vector<Lamp>>& lamps);

// Запуск основной программы после тестов
void run();

int main() {
    setlocale(LC_ALL, "Russian");

    // Вызываем тесты
    testDefaultConstructor();
    testInitializationConstructor();
    testCopyConstructor();
    testAccessMethods();
    cout << "Все тесты прошли успешно!" << endl;

    // Сама программа
    run();

    return 0;
}


void testDefaultConstructor() {
    Lamp lamp;
    assert(lamp.getLightPower() == 0);
    assert(lamp.getPowerConsumption() == 0);
    assert(!lamp.isTurnedOn());
    cout << "Lamp Тест 1 прошёл успешно!" << endl;

    LED_Lamp led_lamp;
    assert(led_lamp.getLightPower() == 0);
    assert(led_lamp.getPowerConsumption() == 0);
    assert(!led_lamp.isTurnedOn());
    assert(led_lamp.getRedPower() == 0);
    assert(led_lamp.getGreenPower() == 0);
    assert(led_lamp.getBluePower() == 0);
    assert(led_lamp.getRedIntensity() == 0);
    assert(led_lamp.getGreenIntensity() == 0);
    assert(led_lamp.getBlueIntensity() == 0);
    cout << "LED_Lamp Тест 1 прошёл успешно!" << endl;

    Room room;
    assert(room.getLength() == 10);
    assert(room.getWidth() == 10);
    assert(room.getHeight() == 10);
    cout << "Room Тест 1 прошёл успешно!" << endl;
}

void testInitializationConstructor() {
    Lamp lamp(1000, 100);
    assert(lamp.getLightPower() == 1000);
    assert(lamp.getPowerConsumption() == 100);
    assert(!lamp.isTurnedOn());
    cout << "Lamp Тест 2 прошёл успешно!" << endl;

    LED_Lamp led_lamp(1000, 100, 500, 300, 700, 0.5, 0.5, 0.5);
    assert(led_lamp.getLightPower() == 1000);
    assert(led_lamp.getPowerConsumption() == 100);
    assert(!led_lamp.isTurnedOn());
    assert(led_lamp.getRedPower() == 500);
    assert(led_lamp.getGreenPower() == 300);
    assert(led_lamp.getBluePower() == 700);
    assert(led_lamp.getRedIntensity() == 0.5);
    assert(led_lamp.getGreenIntensity() == 0.5);
    assert(led_lamp.getBlueIntensity() == 0.5);
    cout << "LED_Lamp Тест 2 прошёл успешно!" << endl;

    vector<vector<Lamp>> lamps;
    vector<Lamp> buffer;
    buffer.push_back(lamp);
    lamps.push_back(buffer);
    Room room(5, 4, 3, lamps);
    assert(room.getLength() == 5);
    assert(room.getWidth() == 4);
    assert(room.getHeight() == 3);
    cout << "Room Тест 2 прошёл успешно!" << endl;
}

void testCopyConstructor() {
    Lamp lamp(1000, 100);
    Lamp copyLamp(lamp);
    assert(copyLamp.getLightPower() == lamp.getLightPower());
    assert(copyLamp.getPowerConsumption() == lamp.getPowerConsumption());
    assert(copyLamp.isTurnedOn() == lamp.isTurnedOn());
    cout << "Lamp Тест 3 прошёл успешно!" << endl;

    LED_Lamp led_lamp(1000, 100, 500, 300, 700, 0.5, 0.5, 0.5);
    LED_Lamp led_copyLamp(led_lamp);
    assert(led_copyLamp.getLightPower() == led_lamp.getLightPower());
    assert(led_copyLamp.getPowerConsumption() == led_lamp.getPowerConsumption());
    assert(led_copyLamp.isTurnedOn() == led_lamp.isTurnedOn());
    assert(led_copyLamp.getRedPower() == led_lamp.getRedPower());
    assert(led_copyLamp.getGreenPower() == led_lamp.getGreenPower());
    assert(led_copyLamp.getBluePower() == led_lamp.getBluePower());
    assert(led_copyLamp.getRedIntensity() == led_lamp.getRedIntensity());
    assert(led_copyLamp.getGreenIntensity() == led_lamp.getGreenIntensity());
    assert(led_copyLamp.getBlueIntensity() == led_lamp.getBlueIntensity());
    cout << "LED_Lamp Тест 3 прошёл успешно!" << endl;

    vector<vector<Lamp>> lamps;
    vector<Lamp> buffer;
    buffer.push_back(lamp);
    lamps.push_back(buffer);
    Room room(5, 4, 3, lamps);
    Room copyRoom(room);
    assert(room.getLength() == 5);
    assert(room.getWidth() == 4);
    assert(room.getHeight() == 3);
    cout << "Room Тест 3 прошёл успешно!" << endl;
}

void testAccessMethods() {
    Lamp lamp(1000, 100);
    assert(lamp.getLightPower() == 1000);
    assert(lamp.getPowerConsumption() == 100);
    assert(!lamp.isTurnedOn());
    lamp.turnOn();
    assert(lamp.isTurnedOn());
    lamp.turnOff();
    assert(!lamp.isTurnedOn());
    assert(lamp.identify() == "Lamp");
    cout << "Lamp Тест 4 прошёл успешно!" << endl;

    LED_Lamp led_lamp(1000, 100, 500, 300, 700, 0.5, 0.5, 0.5);
    assert(led_lamp.getLightPower() == 1000);
    assert(led_lamp.getPowerConsumption() == 100);
    assert(!led_lamp.isTurnedOn());
    led_lamp.turnOn();
    assert(led_lamp.isTurnedOn());
    led_lamp.turnOff();
    assert(!led_lamp.isTurnedOn());
    assert(led_lamp.getLightPower() == 1000);
    assert(led_lamp.getPowerConsumption() == 100);
    assert(!led_lamp.isTurnedOn());
    assert(led_lamp.getRedPower() == 500);
    assert(led_lamp.getGreenPower() == 300);
    assert(led_lamp.getBluePower() == 700);
    assert(led_lamp.getRedIntensity() == 0.5);
    assert(led_lamp.getGreenIntensity() == 0.5);
    assert(led_lamp.getBlueIntensity() == 0.5);
    //assert(led_lamp.calculateLightForce() == 500);
    assert(led_lamp.identify() == "LED Lamp");
    cout << "LED_Lamp Тест 4 прошёл успешно!" << endl;

    //Lamp* lamp2 = &led_lamp;
    //cout << lamp2->identify();

    vector<vector<Lamp>> lamps;
    vector<Lamp> buffer;
    buffer.push_back(lamp);
    lamps.push_back(buffer);
    Room room(5, 4, 3, lamps);
    assert(room.calculateIlluminance(0, 0, 0) == 0);
    assert(room.calculatePower() == 0);
    cout << "Room Тест 4 прошёл успешно!" << endl;
}

void run() {
    cout << endl << "Запуск основной программы..." << endl;

    int n, m, k;
    vector<vector<Lamp>> lamps;

    cout << "Введите число ламп по вертикали и горизонтали:" << endl;
    cin >> n;
    cin >> m;

    cout << "Введите силу света и потребляемую мощность каждой лампы:" << endl;
    for (int i = 0; i < n; i++) {
        vector<Lamp> buffer;
        for (int j = 0; j < m; j++) {
            int lightPower = 0, powerConsumption = 0;
            cin >> lightPower >> powerConsumption;
            Lamp lamp(lightPower, powerConsumption);
            buffer.push_back(lamp);
        }
        lamps.push_back(buffer);
    }

    cout << "Введите число включенных ламп:" << endl;
    cin >> k;

    cout << "Введите координаты каждой включённой лампы:" << endl;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        lamps[x][y].turnOn();
    }

    cout << "Введите размеры комнаты:" << endl;
    float length, width, height;
    cin >> length >> width >> height;

    Room apartment(length, width, height, lamps);

    cout << "Введите координаты точки, для вычисления освещённости:" << endl;
    int x, y, z;
    cin >> x >> y >> z;

    cout << "Освещённость в точке (" << x << ", " << y << ", " << z << "): " << apartment.calculateIlluminance(x + 1, y + 1, z + 1) << endl;
    cout << "Мощность электропотребления: " << apartment.calculatePower() << endl;
}
