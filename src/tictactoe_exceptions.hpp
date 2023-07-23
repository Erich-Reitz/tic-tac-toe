#include <exception>

struct NoOptionSelected : public std::exception {
    [[nodiscard]] const char *what () const noexcept override {
        return "Cannot start game without selecting X's or O's" ;
    }
};