#ifndef WIDGETS_FACTORY_HPP_
#define WIDGETS_FACTORY_HPP_

#include "widgets.hpp"
#include <memory>

class AbstractWidgetsFactory
{
public:
    virtual std::unique_ptr<Widget> CreateButton(const std::string& text, IconType icon) = 0;
    virtual std::unique_ptr<Widget> CreateMenu(const std::string& text) = 0;

    virtual ~AbstractWidgetsFactory() = default;
};

class MotifWidgetsFactory : public AbstractWidgetsFactory
{
public:
    std::unique_ptr<Widget> CreateButton(const std::string& text, IconType icon) override
    {
        return std::make_unique<MotifButton>(text, icon);
    }
    std::unique_ptr<Widget> CreateMenu(const std::string& text) override
    {
        return std::make_unique<MotifMenu>(text);
    }
};

class WindowsfWidgetsFactory : public AbstractWidgetsFactory
{
public:
    std::unique_ptr<Widget> CreateButton(const std::string& text, IconType icon) override
    {
        return std::make_unique<WindowsButton>(text, icon);
    }
    std::unique_ptr<Widget> CreateMenu(const std::string& text) override
    {
        return std::make_unique<WindowsMenu>(text);
    }
};

#endif /*WIDGETS_FACTORY_HPP_*/