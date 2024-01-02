#include "chrono.hpp"


namespace Biblio{


// ---------------------------------------------------------------------------
// BOOK Interface
enum class Genre{
    fiction, nonfiction, periodical, biography, children
};

class Book{
    public:
        // Constructor(s)
        Book(string, string, Genre, string, Chrono::Date);

        // Methods
        string title() const;
        string author() const;
        Genre genre() const;
        string isbn() const;
        Chrono::Date copyright() const;
        bool is_available();
        void checkout();
        void return_book();
        
        // Error(s)
        class BookError: Chrono::Date::DateError{};  // try inheritance
    private:
        string title;
        string author;
        Genre genre;
        string isbn;
        Chrono::Date copyright;  // Dates < 1970???
        bool available;
};

// Helper Functions

bool is_valid_isbn(const string);
void return_book(Book&);
void checkout_book(Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
ostream& operator<<(ostream&, const Book&);


}  // namespace Biblio