#include "../std_lib_facilities.h"

int main(){
    string recipient;
    string friend_name;
    char friend_sex = 0;
    int age = -1;
    
    cout << "Enter the letter recipient's name and age:\n";
    cin >> recipient >> age;
    if (age <= 0 || age > 110)
        simple_error("Surely you're joking!");
    cout << "Enter the friend's name and sex:\n";
    cin >> friend_name >> friend_sex;
    // the letter
    cout << "\nDear " << recipient << ",\n"
        << "\tHow are you? I'm fine, myself. I miss you. ";
    if (friend_sex == 'm')
        cout << "If you see " << friend_name << " please ask him to call me. ";
    if (friend_sex == 'f')
        cout << "If you see " << friend_name << " please ask her to call me. ";
    cout << "I hear you just had a birthday and have been blessed to reach " << age
        << " years old. That's incredible! ";
    if (age < 12)
        cout << "Next year, you'll be " << age + 1
            << ". As if you didn't know that already! ";
    if (age == 17)
        cout << "Next year, you'll be able to vote. Have fun with that.\n";
    if (age > 70)
        cout << "I hope you are enjoying retirement withcha bad self.\n";
    cout << "\n\nYours sincerely,\n\n" << "Tj\n";
}
