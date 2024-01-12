/*
    I am aware that include guards exist and should be used to prevent
    duplication and coupling, but we have yet to be introduced to that
    in the book, so I am using a highly-coupled structure as a result :(
*/
#include "../headers/chrono.hpp"


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
        string get_title() const;
        string get_author() const;
        Genre get_genre() const;
        string get_isbn() const;
        Chrono::Date get_copyright() const;
        bool is_available();
        void checkout();
        void return_book();
        
        // Error(s)
        class BookError{
            public: 
                BookError(const string&);
                const string& what();
            private:
                string err_msg;
        };  // try inheritance
    private:
        string title;
        string author;
        Genre genre;
        string isbn;
        Chrono::Date copyright;  // Dates < 1970???
        bool available {true};
};

// Helper Functions

bool is_valid_isbn(const string);
void return_book(Book&);
void checkout_book(Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
ostream& operator<<(ostream&, const Book&);


}  // namespace Biblio