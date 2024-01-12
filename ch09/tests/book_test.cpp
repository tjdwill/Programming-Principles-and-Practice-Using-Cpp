/*
    I am aware that include guards exist and should be used to prevent
    duplication and coupling, but we have yet to be introduced to that
    in the book, so I am using a highly-coupled structure as a result :(
*/
#include "../headers/biblio.hpp"


using Biblio::Book;
int main()
try{
    using Biblio::is_valid_isbn;
    Book b1 = Book(
        "Pride and Prejudice", "Jane Austen", Biblio::Genre::fiction, "9780-1404-3072-1", Chrono::Date()
    );
    cout << b1;

    /*
        Title:	Pride and Prejudice
        Author:	Jane Austen
        ISBN: 	9780-1404-3072-1
    */

    // Test ISBN validations
    cout << is_valid_isbn("0a45-1234-23-x") << '\n';
    cout << is_valid_isbn("5---") << '\n';
    cout << is_valid_isbn("5-5-5-5") << '\n';  // true
    cout << is_valid_isbn("t45-111-111-1") << '\n';
    cout << is_valid_isbn("1234-5678-9-0x") << '\n';
    cout << is_valid_isbn("1234-5678-09-j") << '\n';  //  true

    /*
        0
        0
        1
        0
        0
        1
    */
    
}
catch(Book::BookError& e){
    cerr << "Error: " << e.what() << '\n';
}
catch(...){
    cerr << "Unexpected Error.\n";
}