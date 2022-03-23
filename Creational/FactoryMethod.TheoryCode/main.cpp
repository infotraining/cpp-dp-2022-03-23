#include "factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Canonical
{
    class Service
    {
        shared_ptr<LoggerCreator> creator_;
        bool is_started_ = false;

    public:
        Service(shared_ptr<LoggerCreator> creator)
            : creator_(creator)
        {
        }

        Service(const Service&) = delete;
        Service& operator=(const Service&) = delete;

        void run()
        {
            // FileLogger logger("log.dat"); // strong coupling

            // unique_ptr<Logger> logger = LoggerFactory::create("DbLogger"); // weaker coupling

            unique_ptr<Logger> logger = creator_->create_logger(); // use of factory factory - loosely coupled
            if (!is_started_)
                start();
            logger->log("Service has been started...");
            process_requests();
            logger->log("Service has processed all requests...");
        }

    protected:
        virtual void start() { }
        virtual void process_requests() { }
    };

    using LoggerFactory = std::unordered_map<std::string, shared_ptr<LoggerCreator>>;
}

using LoggerCreator = std::function<std::unique_ptr<Logger>()>;

class Service
{
    LoggerCreator logger_creator_;
    bool is_started_ = false;

public:
    Service(LoggerCreator creator)
        : logger_creator_(creator)
    {
    }

    Service(const Service&) = delete;
    Service& operator=(const Service&) = delete;

    void run()
    {
        unique_ptr<Logger> logger = logger_creator_(); // use of factory factory - loosely coupled
        if (!is_started_)
            start();
        logger->log("Service has been started...");
        process_requests();
        logger->log("Service has processed all requests...");
    }

protected:
    virtual void start() { }
    virtual void process_requests() { }
};

using LoggerFactory = std::unordered_map<std::string, LoggerCreator>;

int main()
{
    LoggerFactory logger_factory;
    logger_factory.insert(make_pair("ConsoleLogger", std::make_unique<ConsoleLogger>));
    logger_factory.insert(make_pair("FileLogger", []() { return make_unique<FileLogger>("data.log"); }));
    logger_factory.insert(make_pair("DbLogger", []() { return make_unique<DbLogger>("192.168.0.1:9999"); }));

    Service srv(logger_factory.at("ConsoleLogger"));
    srv.run();
}
