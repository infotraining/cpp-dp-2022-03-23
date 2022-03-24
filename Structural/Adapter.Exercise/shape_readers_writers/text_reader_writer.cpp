#include "text_reader_writer.hpp"
#include "../shape_factories.hpp"
#include "../text.hpp"

using namespace std;
using namespace Drawing;
using namespace IO;

// TODO - register creator for a TextReaderWriter class
namespace
{
    bool is_registered = SingletonShapeRWFactory::instance()
        .register_creator(make_type_index<Text>(), std::make_unique<TextReaderWriter>);
}

void TextReaderWriter::read(Shape& shp, istream& in)
{
    Text& text = static_cast<Text&>(shp);

    Point pt;
    std::string str;

    in >> pt >> str;

    text.set_coord(pt);
    text.set_text(str);
}

void TextReaderWriter::write(const Shape& shp, ostream& out)
{
    const Text& text = static_cast<const Text&>(shp);
    out << Text::id << " " << text.coord() << " " << text.text() << "\n";
}
