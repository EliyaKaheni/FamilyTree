#include <bits/stdc++.h>
using namespace std;

struct Person;
void print(Person &p);
void family_size(vector<Person> family);
int find(vector<Person> family, string _name);
void add(Person &p, string _name, string _father, string _mother, vector<Person> &family);


// A structure for each person 
struct Person{
    string name;
    Person* father = nullptr;  
    Person* mother = nullptr;
};

// Add function
void add(Person &p, string _name, string _father, string _mother, vector<Person> &family){
    p.name = _name;
    
    p.father = new Person;
    p.father->name = _father;
    
    p.mother = new Person;
    p.mother->name = _mother;

    family.push_back(p);
    
    if(find(family, p.mother->name) == -1)
        family.push_back(*p.mother);
    if(find(family, p.father->name) == -1)
        family.push_back(*p.father);
    
}

// Prints the name of a person
void print(Person &p){
    cout<<p.name<<endl;
}

// Finds a Person
int find(vector<Person> family, string _name){
    for(int i=0; i<family.size(); i++){
        Person temp = family[i];
        if(temp.name==_name)
            return i;
    }
    return -1;
}

// Returns the size of the family
int family_size(vector<Person> family){
    return family.size();
}

int main(){

    vector<Person> family;
    Person p;
    add(p, "ali", "akbar", "mariya", family);

    Person h;
    add(h, "ahmad", "naser", "mahsa", family);

    Person m;
    add(m, "armita", "ebrahim", "ladan", family);

    Person n;
    add(n, "narges", "ali", "armita", family);

    cout<<family_size(family);
    
    return 0;
}
