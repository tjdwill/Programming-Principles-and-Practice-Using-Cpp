#include "../../std_lib_facilities.h"

//----------------------------------------------------------------------------
namespace ex02{

extern const string stop;
// invariant checks
void check_valid(const vector<string>&); 
bool is_valid(const vector<int>&);
bool is_unique(vector<string>);
bool can_insert(string, vector<string>);
// bool are_valid(const vector<string>&, const vector<int>&);

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
        void print(); 
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
        int idx {-1}; // keeps track of where to begin indexing for adding ages.
        void read_names(); // add names to database
        void read_ages();
}; // class `NamePairs`

}; // namespace `ex02`