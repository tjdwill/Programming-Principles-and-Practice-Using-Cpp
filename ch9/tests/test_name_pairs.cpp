#include "../headers/name_pairs.hpp"

vector<string> valid_names {"Bill", "Robert", "Antonio", "Nicole", "Michelle"};
vector<string> invalid_names {"Bill", "Robert", "Nicole", "Antonio", "Nicole"};
vector<string> invalid_names2 {"Bill", "Robert", ex02::stop, "Antonio", "Nicole"};

vector<int> valid_ages {30, 25, 100, 0, 10000000};
vector<int> invalid_ages {-30, 25, 100, 0, 10000000};
vector<int> invalid_ages_sz {25, 100, 0, 10000000};

int main()
try{
    ; // Check compilation errors
    ex02::NamePairs test_default {};  // default construction
    ex02::NamePairs test_valid {valid_names, valid_ages};
    /*
        The following invalid entries all produced expected error messages.
    */
    // ex02::NamePairs test_invalid {invalid_names, valid_ages};
    // ex02::NamePairs test_invalid2 {invalid_names2, valid_ages};
    // ex02::NamePairs test_invalid_age {valid_names, invalid_ages};
    // ex02::NamePairs test_invalid_sz {valid_names, invalid_ages_sz};

    test_default.print();
    test_valid.print();

    cout << "\nSorted:";
    test_default.sort();
    test_valid.sort();
    test_default.print();
    test_valid.print();
    
    cout << "\nTesting name-pair updates.\n";
    test_valid.update();
    test_valid.print();
    cout << "Success!\n";
}
catch(ex02::NamePairs::InitError& e){
    cerr << "Error: " << e.what() << '\n';
}
catch(...){
    cerr << "Unknown Exception.\n";
}
