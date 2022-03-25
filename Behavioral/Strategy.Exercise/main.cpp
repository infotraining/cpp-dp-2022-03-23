#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

class Calculator
{
public:
    virtual void calculate(const Data& data, Results& results) = 0;
    virtual ~Calculator() = default;
};

class MinMaxCalculator : public Calculator
{
public:
    virtual void calculate(const Data& data, Results& results)
    {
        double min = *(std::min_element(data.begin(), data.end()));
        double max = *(std::max_element(data.begin(), data.end()));

        results.push_back(StatResult("Min", min));
        results.push_back(StatResult("Max", max));
    }
};

class AvgCalculator : public Calculator
{
public:
    virtual void calculate(const Data& data, Results& results)
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double avg = sum / data.size();

        StatResult result("Avg", avg);
        results.push_back(result);
    }
};

class SumCalculator : public Calculator
{
public:
    virtual void calculate(const Data& data, Results& results)
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);

        results.push_back(StatResult("Sum", sum));
    }
};


// applying Composite Pattern to Calculators hierarchy
class GroupCalculator : public Calculator
{
    std::vector<std::shared_ptr<Calculator>> calcs_;
public:
    virtual void calculate(const Data& data, Results& results)
    {
        for(auto& calc : calcs_)
        {
            calc->calculate(data, results);
        }
    }

    void add(std::shared_ptr<Calculator> calc)
    {
        calcs_.push_back(calc);
    }
};

namespace Alternative_1
{
    class Calculator
    {
    public:
        virtual Results calculate(const Data& data) = 0;
        virtual ~Calculator() = default;
    };
}

namespace Alternative_2
{
    using Calculator = std::function<Results(const Data& data)>;
}

enum StatisticsType
{
    avg,
    min_max,
    sum
};

class DataAnalyzer
{
    std::shared_ptr<Calculator> strategy_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(std::shared_ptr<Calculator> strategy)
        : strategy_ {strategy}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_calculator(std::shared_ptr<Calculator> new_strategy)
    {
        strategy_ = new_strategy;
    }

    void calculate()
    {
        strategy_->calculate(data_, results_);
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    auto std_calculators = std::make_shared<GroupCalculator>();
    std_calculators->add(std::make_shared<AvgCalculator>());
    std_calculators->add(std::make_shared<MinMaxCalculator>());
    std_calculators->add(std::make_shared<SumCalculator>());

    DataAnalyzer da(std_calculators);
    da.load_data("data.dat");
    da.calculate();
    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_data.dat");
    da.calculate();
    show_results(da.results());
}
