#ifndef WIDGETS_HPP_
#define WIDGETS_HPP_

#include <iostream>
#include <memory>
#include <vector>

using namespace std;


enum class IconType
{
    none,
    ok,
    cancel,
    warning,
    error
};

class Widget
{
public:
    virtual void draw() = 0;
    virtual ~Widget() = default;
};

class Button : public Widget
{
    std::string caption_;
    IconType icon_type_;

public:
    Button(const std::string& caption, IconType icon_type)
        : caption_{caption}
        , icon_type_{icon_type}
    {
    }

    std::string caption() const
    {
        return caption_;
    }

    IconType icon() const
    {
        return icon_type_;
    }
};

class Menu : public Widget
{
    std::string text_;

public:
    Menu(const std::string& text)
        : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }
};

class MotifButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "MotifButton [ " << caption() << " ]\n";
    }
};

class MotifMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "MotifMenu { " << text() << " }\n";
    }
};

class WindowsButton : public Button
{
public:
    using Button::Button;

    void draw() override
    {
        cout << "WindowsButton [ " << caption() << " ]\n";
    }
};

class WindowsMenu : public Menu
{
public:
    using Menu::Menu;

    void draw() override
    {
        cout << "WindowsMenu { " << text() << " }\n";
    }
};

#endif /*WIDGETS_HPP_*/