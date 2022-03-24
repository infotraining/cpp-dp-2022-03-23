#include <cassert>
#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;

class Engine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual std::unique_ptr<Engine> clone() const = 0;
    virtual ~Engine() = default;
};

// CRTP Idiom
template <typename TEngine_, typename TEngineBase_ = Engine>
class CloneableEngine : public TEngineBase_
{
public:
    std::unique_ptr<Engine> clone() const override
    {
        return std::make_unique<TEngine_>(*static_cast<const TEngine_*>(this));
    }
};

class Diesel : public CloneableEngine<Diesel>
{
public:
    void start() override
    {
        cout << "Diesel starts\n";
    }

    void stop() override
    {
        cout << "Diesel stops\n";
    }
};

class TDI : public CloneableEngine<TDI, Diesel>
{
public:
    void start() override
    {
        cout << "TDI starts\n";
    }

    void stop() override
    {
        cout << "TDI stops\n";
    }
};

class Hybrid : public CloneableEngine<Hybrid>
{
public:
    void start() override
    {
        cout << "Hybrid starts\n";
    }

    void stop() override
    {
        cout << "Hybrid stops\n";
    }
};

class Car
{
    std::unique_ptr<Engine> engine_;

public:
    Car(std::unique_ptr<Engine> engine)
        : engine_ {move(engine)}
    {
    }

    Car(const Car& source) : engine_{source.engine_->clone()}
    {
    }

    Car(Car&&) = default;

    void drive(int km)
    {
        engine_->start();
        cout << "Driving " << km << " kms\n";
        engine_->stop();
    }
};

int main()
{
    {
        Car c1 {std::make_unique<TDI>()};
        c1.drive(100);

        cout << "\n";

        Car c2 = c1;
        c2.drive(200);
    }
}
