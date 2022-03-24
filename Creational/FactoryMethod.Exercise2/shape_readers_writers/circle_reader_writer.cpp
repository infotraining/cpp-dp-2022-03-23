#include "circle_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../circle.hpp"

using namespace std;
using namespace Drawing;
using namespace Drawing::IO;

namespace
{
    bool is_registered = SingletonShapeRWFactory::instance().register_creator(make_type_index<Circle>(), std::make_unique<CircleReaderWriter>);
}

void CircleReaderWriter::read(Shape& shp, std::istream& in)
{
    Circle& c = static_cast<Circle&>(shp);

    Point pt;
    int r;

    in >> pt >> r;

    c.set_coord(pt);
    c.set_radius(r);

}

void CircleReaderWriter::write(const Shape& shp, std::ostream& out)
{
    const Circle& c = static_cast<const Circle&>(shp);

    out << Circle::id << " " << c.coord() << " " << c.radius() << std::endl;
}
