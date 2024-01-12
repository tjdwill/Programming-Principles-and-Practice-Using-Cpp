/*
    @title: PPP Ch.10 Drill
    @author: tjdwill
    @date: 11 January 2024
*/
#include "../../std_lib_facilities.h"


//----------------------------------------------------------------------------
// Infrastructure
struct Point{
    Point(){}
    Point(double i, double j)
        : x(i), y(j) {}
    double x {};
    double y {};
};

ostream& operator << (ostream& os, const Point& p){
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}


istream& operator >> (istream& ist, Point& p)
{
    // make `ist` throw if it goes bad.
    ist.exceptions(ist.exceptions()|ios_base::badbit);  
    char ch1, ch2, ch3 {};
    double x, y {};
    ist >> ch1 >> x >> ch2 >> y >> ch3;
    
    if (!ist) return ist;
    // check for valid format
    if (!(ch1 == '(' && ch2 == ',' && ch3 == ')')){
        ist.clear(ios_base::failbit);
        return ist;
    }
    p = Point{x, y};
    
    return ist;
}

bool operator == (const Point& a, const Point& b) {return a.x == b.x && a.y == b.y;}

bool operator != (const Point& a, const Point& b) {return !(a==b);}

class EOFError{};
Point get_point(istream& ist, const string& invalid_msg="", const string& greeting = "")
{
    // Keep trying until we get a valid point.
    Point pt {};
    cout << greeting;
    string dump;
    while (true){
        ist >> pt;
        if (!ist){
            if (ist.eof()) throw EOFError{};
            ist.clear();
            ist >> dump;
            cerr << invalid_msg;
        }
        else return pt;
    }
}

void fill_vector(vector<Point>& v, istream& ist)
{
    for (int i {0}; i<v.size(); ++i) 
        v[i] = get_point(ist, "Invalid Point format. Use `(x, y)`\n");
}

void print_vector(const vector<Point>& v, const string& msg="")
{
    cout << msg;
    for (Point p: v)
        cout << p << ' ';
    cout <<'\n';
}
//----------------------------------------------------------------------------
int main()
try{
    constexpr int size {7};
    const string filename {"mydata.txt"};
    vector<Point> original_points(size);
    ofstream outfile {filename};

    cout << "Please insert " << size << " point(s) (whitespace-separated):\n";
    fill_vector(original_points, cin);
    print_vector(original_points, "Received Point(s):\n");
    for (Point p: original_points){
        outfile << p << '\n';
    }
    cout << '\n';

    outfile.close();

    vector<Point> processed_points {};
    ifstream infile {filename};
    if (!infile) error("Unable to open file ", filename);
    while (true){
        try{
            processed_points.push_back(get_point(infile));
        }
        catch(EOFError){;}
        if (!infile) break;
    }
    if (processed_points.size() != original_points.size()) error("Size Inconsistency.\n");
    for (int i{}; i<original_points.size(); ++i)
        if (processed_points[i] != original_points[i]) error("Point Inconsistency.\n");

    print_vector(original_points, "Original:\n");
    print_vector(processed_points, "Processed:\n");


}
catch(runtime_error& e){
    cerr << "Error: " << e.what() << '\n';
}
catch(...){
    cerr << "Unanticipated Error.\n";
}
//----------------------------------------------------------------------------
