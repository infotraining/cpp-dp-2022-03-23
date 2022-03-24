#ifndef TEXT_HPP
#define TEXT_HPP

#include "paragraph.hpp"
#include "shape.hpp"
#include <string>

namespace Drawing
{
    // TODO - adapt Paragraph class to Shape interface
    class Text : public ShapeBase, private LegacyCode::Paragraph
    {
    public:    
        constexpr static auto id = "Text";
        
        Text(int x = 0, int y = 0, const std::string& text = "")    
            : ShapeBase{x, y}, LegacyCode::Paragraph(text.c_str())
        {}

        std::string text() const 
        {
            return get_paragraph();
        }

        void set_text(const std::string& text)
        {
            set_paragraph(text.c_str());
        }

        void draw() const
        {
            render_at(coord().x, coord().y);
        }
    };
}

#endif
