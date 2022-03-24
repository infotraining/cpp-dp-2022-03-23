#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <iostream>
#include <memory>
#include <vector>
#include "widgets.hpp"
#include "widgets_factory.hpp"

enum class WidgetTheme
{
    motif,
    windows
};

class Window
{
    std::vector<std::unique_ptr<Widget>> widgets;
    AbstractWidgetsFactory& widgets_factory_;

public:
    Window(AbstractWidgetsFactory& widgets_factory) 
    : widgets_factory_{widgets_factory}
    {}
    
    virtual ~Window() = default;

    void display() const
    {
        std::cout << "######################\n";
        for (const auto& w : widgets)
            w->draw();
        std::cout << "######################\n\n";
    }



    void add_widget(std::unique_ptr<Widget> widget)
    {
        widgets.push_back(move(widget));
    }
};

class WindowOne : public Window
{
public:
    WindowOne(AbstractWidgetsFactory& widgets_factory) :
        Window{widgets_factory}
    {
        add_widget(widgets_factory.CreateButton("OK", IconType::ok));
        add_widget(widgets_factory.CreateMenu("File"));
    }
};

class WindowTwo : public Window
{

public:
    WindowTwo(AbstractWidgetsFactory& widgets_factory)
        : Window{widgets_factory}
    {
        add_widget(widgets_factory.CreateMenu("Edit"));
        add_widget(widgets_factory.CreateButton("OK", IconType::ok));
        add_widget(widgets_factory.CreateButton("Cancel", IconType::cancel));
    }
};

#endif /*WINDOW_HPP_*/