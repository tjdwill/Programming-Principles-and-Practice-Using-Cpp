// Implementation of the Book class
// tjdwill
// 1 January 2024

#include "../headers/biblio.hpp"

namespace Biblio{

Book::Book(
    string title,
    string author,
    Genre genre,
    string isbn,
    Chrono::Date copyright
)
: title(title), author(author), genre(genre), isbn(isbn), copyright(copyright)
{
    if (!is_valid_isbn(isbn)) throw BookError("Invalid ISBN.\n");
}

string Book::get_title() const {return title;}
string Book::get_author() const {return author;}
Genre Book::get_genre() const {return genre;}
string Book::get_isbn() const {return isbn;}
Chrono::Date Book::get_copyright() const {return copyright;}
bool Book::is_available() {return available;}
void Book::checkout () {
    if (!available) throw BookError(title + " is unavailable.\n");
    available = false;
}
void Book::return_book() {
    if (available) throw BookError(title + "is already available.\n");
    available = true;
}


Book::BookError::BookError(const string& str)
: err_msg(str) {}

const string& Book::BookError::what() {return err_msg;}
//----------------------------------------------------------------------------
// Helper Functions
bool is_valid_isbn(const string isbn){
    // Iterate through string to determine valid isbn
    // Format: n-n-n-x (integer, integer, integer, digit or letter).
    constexpr int min_size {7};
    constexpr int total_hyph {3};
    if (isbn.size() < min_size) return false;
    if (!isdigit(isbn[0])) return false;

    char current {};
    char prev{isbn[0]};
    int num_hyphens{};
    for (int i {1}; i<isbn.size(); ++i)
    {
        current = isbn[i];
        if (!isdigit(current)){
            if (num_hyphens < total_hyph && current == '-' && isdigit(prev))
                ++num_hyphens;
            else if (
                (
                    num_hyphens == total_hyph && 
                    isalpha(current) && 
                    i==isbn.size()-1 && 
                    prev=='-'
                )
            ) 
                break;
            else
                return false;
        }
        prev = current;
    }
    return true;
}

void return_book(Book& book){
    try
    {
        book.return_book();
    }
    catch(Book::BookError& e){
        ; // pass
    }
}

void checkout_book(Book& book){
    try
    {
        book.checkout();
    }
    catch(Book::BookError& e){
        ; // pass
    }
}

bool operator==(Book& a, Book& b){
    // ISBNs are meant to be unique to a given book
    return a.get_isbn() == b.get_isbn();
}

bool operator!=(Book& a, Book& b){return !(a==b);}

ostream& operator<<(ostream& os, const Book& book){
    os << "Title:\t" << book.get_title() << '\n'
        << "Author:\t" << book.get_author() << '\n'
        << "ISBN: \t" << book.get_isbn() << '\n';
    return os;
}

}  // namespace Biblio

