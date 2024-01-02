// Implementation of the Book class
// tjdwill
// 1 January 2024

#include "biblio.hpp"

namespace Biblio{

Book::Book(
    string title,
    string author,
    Genre genre,
    string isbn,
    Chrono::Date copyright
)
: title(title), author(author), genre(genre), isbn(isbn), copyright(copyright) {
    if !is_valid_isbn(isbn) throw BookError("Invalid ISBN.\n");
}


bool is_valid_isbn(const string isbn){
    // Iterate through string to determine valid isbn
    // Format: n-n-n-x (integer, integer, integer, digit or letter).
    constexpr min_size {7};
    constexpr total_hyph {3};
    if (isbn.size() < min_size) return false;
    if !isdigit(isbn[0]) return false;

    char current {};
    char prev{isbn[0]};
    int num_hyphens{};
    for (int i {1}, i<isbn.size(), ++i)
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
}  // namespace Biblio

