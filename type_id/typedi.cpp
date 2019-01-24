#include <iostream>  
#include <typeinfo>  //for 'typeid' to work  

class Person {  
    public:
    // ... Person members ...
    virtual ~Person() {}
};

class Employee : public Person {
    // ... Employee members ..
};

int main () {  
    Person person;  
    Employee employee;  
    Person *ptr = &employee;  
    int t = 3;  

    std::cout << typeid(t).name() << std::endl;  
    std::cout << typeid(person).name() << std::endl;   // Person (statically known at compile-time)  
    std::cout << typeid(employee).name() << std::endl; // Employee (statically known at compile-time)  
    std::cout << typeid(ptr).name() << std::endl;      // Person * (statically known at compile-time)  
    std::cout << typeid(*ptr).name() << std::endl;     // Employee (looked up dynamically at run-time  
                                                       // because it is the dereference of a pointer
                                                       // to a polymorphic class)  
 }  
