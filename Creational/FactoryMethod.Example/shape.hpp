#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"
#include <functional>
#include <unordered_map>


namespace Drawing
{
    namespace IO
    {
        class ShapeReaderWriter;
    }

    // inteface
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        virtual std::unique_ptr<IO::ShapeReaderWriter> create_rw() = 0;
    };

    // abstract class
    class ShapeBase : public Shape
    {
        Point coord_; // composition
    public:
        Point coord() const
        {
            return coord_;
        }

        void set_coord(const Point& pt)
        {
            coord_ = pt;
        }

        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }
    };
   
    template <typename TProduct_, typename TCreator_ = std::function<std::unique_ptr<TProduct_>()>, typename TId_ = std::string>
    class GenericFactory
    {   
        std::unordered_map<TId_, TCreator_> creators_;
    public:
        GenericFactory() = default;

        bool register_creator(TId_ id, TCreator_ creator)
        {
            return creators_.emplace(std::move(id), std::move(creator)).second;
        }

        std::unique_ptr<TProduct_> create(const TId_& id)
        {
            auto& creator = creators_.at(id);
            return creator();
        }
    };

    using ShapeFactory = GenericFactory<Shape>;
}

#endif // SHAPE_HPP
