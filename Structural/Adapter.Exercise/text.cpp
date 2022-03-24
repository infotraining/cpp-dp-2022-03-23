#include "text.hpp"
#include "shape_factories.hpp"

namespace
{
    bool is_registered = Drawing::SingletonShapeFactory::instance()
        .register_creator(Drawing::Text::id, std::make_unique<Drawing::Text>);
}
