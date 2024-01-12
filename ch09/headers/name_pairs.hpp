#include "../../std_lib_facilities.h"

//----------------------------------------------------------------------------

namespace ex02{

extern const string stop;
// invariant checks
void check_valid(const vector<string>&); 
bool is_valid(const vector<int>&);
bool is_valid (const int&); // Ah, here is one case where we can do this (See Exercise 8.14 in book).
bool is_unique(vector<string>);
bool can_insert(const string&, const vector<string>&);


// Create a NamePairs class
// All of the previous versions of this problem assume unique names, so I will
// as well.

class NamePairs{
    public:
    // constructors    
        NamePairs();
        NamePairs(const vector<string>& name_list, const vector<int>& age_list);
    // methods
        void update();
        void sort();
        const vector<string>& get_names() const;
        const vector<int>& get_ages() const;
    // Exception Def
    class InitError {
        public:
            InitError(string msg = "")
                : err_msg(msg) {}
            string what();
        private:
            string err_msg {};
    };  // end InitError Declaration

    private:
        vector<string> names;
        vector<int> ages;
        void read_names(); // add names to database
        void read_ages();
}; // class `NamePairs`

ostream& operator<<(ostream&, const NamePairs&);
bool operator==(const NamePairs&, const NamePairs&);
bool operator!=(const NamePairs&, const NamePairs&);
} // namespace `ex02`