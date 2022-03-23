#include "rectangle.hpp"
#include <memory>
#include "shape_readers_writers/rectangle_reader_writer.hpp"

Drawing::Rectangle::Rectangle(int x, int y, int w, int h)
    : ShapeBase{x, y}
    , width_{w}
    , height_{h}
{
}

void Drawing::Rectangle::draw() const
{
    std::cout << "Drawing rectangle at " << coord() << " with width: " << width_
              << " and height: " << height_ << std::endl;
}

std::unique_ptr<Drawing::IO::ShapeReaderWriter> Drawing::Rectangle::create_rw()
{
    return std::make_unique<Drawing::IO::RectangleReaderWriter>();
}