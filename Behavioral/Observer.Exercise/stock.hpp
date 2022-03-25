#ifndef STOCK_HPP_
#define STOCK_HPP_

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

class Observer
{
public:
    virtual void update(const std::string& symbol, double price) = 0;
    virtual ~Observer()
    {
    }
};

// Subject
class Stock
{
private:
    std::string symbol_;
    double price_;
    std::set<std::weak_ptr<Observer>, std::owner_less<std::weak_ptr<Observer>>> observers_;

public:
    Stock(const std::string& symbol, double price)
        : symbol_(symbol)
        , price_(price)
    {
    }

    std::string get_symbol() const
    {
        return symbol_;
    }

    double get_price() const
    {
        return price_;
    }

    // TODO: rejestracja obserwatora
    void register_observer(std::shared_ptr<Observer> obs)
    {
        observers_.insert(obs);
    }

    // TODO: wyrejestrowanie obserwatora
    void deregister_observer(std::shared_ptr<Observer> obs)
    {
        observers_.erase(obs);
    }

    void set_price(double price)
    {
        price_ = price;

        // TODO: powiadomienie inwestorów o zmianie kursu...
        notify_em_all();
    }

    void notify_em_all()
    {
        for (auto& obs : observers_)
        {
            std::cout << "Notifying 1" << std::endl;
            std::shared_ptr<Observer> active_observer = obs.lock();
            if (active_observer)
                active_observer->update(symbol_, price_);
        }
    }
};

class Investor : public Observer
{
    std::string name_;

public:
    Investor(const std::string& name)
        : name_(name)
    {
    }

    void update(const std::string& symbol, double price)
    {
        std::cout << "Investor: " << name_ << " is notified - Stock " << symbol << " has changed price to " << price << std::endl;
    }
};

#endif /*STOCK_HPP_*/
