#include <iostream>
#include <vector>

class Car
{
public:
    int id;
    Car() {}
    Car(int id): id(id) {}
    virtual ~Car() {}
};

class Sedan: public Car
{
public:
    Sedan(int id): Car(id) {}
};

class Hatchback: public Car
{
public:
    Hatchback(int id): Car(id) {}
};

class Dealership
{
public:

    Dealership(int parkingLot) {
        curr = 0;
        numCars = parkingLot;
        cars = std::vector<Car*>();
    }

    void receiveCar(Car* car) {
        cars.push_back(car);
        curr++;
    }

    Car* sellCar(int i) {
        Car* car = cars[i];
        cars.erase(cars.begin() + i);
        curr--;

        return car;
    }

    int testDrive(int idx) {
        std::cout << "Testing car" << cars[idx]->id << "\n";
        // if user is happy -> he will buy the car
        if (idx % 3 == 0)
            return 1;
        return 0;
    }

    std::vector<Car*> viewLot() {
        return cars;
    }

private:
    int numCars;
    int curr;
    std::vector<Car*> cars;
};

int main(void)
{
    const int numCars = 10;
    Dealership dealership(numCars);

    for (int i = 0; i < numCars; ++i)
    {
        Car car;
        if (i % 2 == 0) {
            car = Sedan(i);
        } else {
            car = Hatchback(i);
        }
        dealership.receiveCar(&car);
    }

    size_t i = 0;
    auto dealerLot = dealership.viewLot();
    for (auto it = dealerLot.begin(); it != dealerLot.end(); it++) {
        if (dealership.testDrive(i)) {
            dealership.sellCar(i);
        }
        i++;
    }

    return 0;
}