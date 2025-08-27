#include <iostream>
using namespace std;

class Person {
private:            // Access specifier
    string name;    // Data member (variable)
    int age;

public:             // Access specifier
    // Constructor
    Person(string n, int a) {
        name = n;
        age = a;
    }

    // Member function
    void introduce() {
        cout << "Hi, I'm " << name << " and I'm " << age << " years old." << endl;
    }
};

int main() {
    Person p1("Pranam", 25);   // Object creation
    p1.introduce();            // Calling member function
}
