#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

// #include <boost/algorithm/string/case_conv.hpp>
// #include <boost/archive/text_iarchive.hpp>
// #include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <string>
#include <algorithm>

class Document
{
    std::string text_;

public:
    class Memento
    {
    private:
        std::string snapshot_;

        friend class Document;
    };

    Document() : text_{}
    {
    }

    Document(const std::string& text) : text_{text}
    {
    }

    std::string text() const
    {
        return text_;
    }

    size_t length() const
    {
        return text_.size();
    }

    void add_text(const std::string& txt)
    {
        text_ += txt;
    }

    void to_upper()
    {
        //boost::to_upper(text_);
        std::transform(text_.begin(), text_.end(),text_.begin(), ::toupper);
    }

    void to_lower()
    {
        //boost::to_lower(text_);
        std::transform(text_.begin(), text_.end(),text_.begin(), ::tolower);
    }

    void clear()
    {
        text_.clear();
    }

    Memento create_memento() const
    {
        std::stringstream archive_stream;
        
        archive_stream << text_;

        Memento memento;
        memento.snapshot_ = archive_stream.str();

        return memento;
    }

    void set_memento(Memento& memento)
    {
        std::stringstream archive_stream{memento.snapshot_};
        archive_stream >> text_;
    }

    void replace(size_t start_pos, size_t count, const std::string& text)
    {
        text_.replace(start_pos, count, text);
    }
};

#endif
