#include <bits/stdc++.h>
using namespace std;

// Functions & Structures 
struct Person;
void print(Person &p);
int family_size(vector<Person> family);
void died(vector<Person> &family, int i);
int find(vector<Person> family, string _name);
bool bro_or_sis(string _name, string _sibling, vector<Person> family);
bool mom_is_that_you(string _name, string _mother, vector<Person> family);
bool dad_is_that_you(string _name, string _father, vector<Person> family);
void add(Person &p, string _name, string _father, string _mother, vector<Person> &family);


// A structure for each person 
struct Person{
    string name;
    Person* father = nullptr;  
    Person* mother = nullptr;
    vector<Person> childs;
};

// Add function
void add(Person &p, string _name, string _father, string _mother, vector<Person> &family){
    p.name = _name;
    
    int motherIndex = find(family, _mother);
    if(motherIndex == -1){
        p.mother = new Person;
        p.mother->name = _mother;
        family.push_back(*p.mother);
    }
    else {
        p.mother = &family[motherIndex];
    }
    p.mother->childs.push_back(p);
    
    int fatherIndex = find(family, _father);
    if(fatherIndex == -1){
        p.father = new Person;
        p.father->name = _father;
        family.push_back(*p.father);
    }
    else {
        p.father = &family[fatherIndex];
    }
    p.father->childs.push_back(p);

    family.push_back(p);
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

// A person died
void died(vector<Person> &family, int i){
    family[i].name += " R.I.P";
}

// Father check
bool dad_is_that_you(string _name, string _father, vector<Person> family){
    int i = find(family, _name);
    Person temp = family[i];
    return temp.father->name == _father || temp.father->name == (_father + " R.I.P");
}

// Mother check
bool mom_is_that_you(string _name, string _mother, vector<Person> family){
    int i = find(family, _name);
    Person temp = family[i];
    return temp.mother->name == _mother || temp.mother->name == (_mother + " R.I.P");
}

// Sibling check
bool bro_or_sis(string _name, string _sibling, vector<Person> family){
    
    int i = find(family, _name);
    Person temp = family[i];

    int j = find(family, _sibling);
    Person temp2 = family[j];

    if (!temp.father or !temp2.father)
        return 0;
    return (temp.father->name == temp2.father->name) && (temp.mother->name == temp2.mother->name);
}

// int generations(vector<Person> family, int i){
//     Person p = family[i];
//     int max_gen = 0;
//     if (p.childs.size()==0)
//         return 0;
    
//     else {

//         return 
//     }
// }

// returns all ancesters of a person
vector<string> ancestor_finder(vector<Person> &family, string p1, vector<string> &ancestors){
    queue<string> q; 
    unordered_set<string> visited;  
    
    q.push(p1);  
    visited.insert(p1); 

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        int i = find(family, current);
        Person a = family[i];

        if (a.father && visited.find(a.father->name) == visited.end()) {
            ancestors.push_back(a.father->name);
            q.push(a.father->name);  
            visited.insert(a.father->name);  
        }

        if (a.mother && visited.find(a.mother->name) == visited.end()) {
            ancestors.push_back(a.mother->name);
            q.push(a.mother->name); 
            visited.insert(a.mother->name);
        }
    }

    return ancestors;
}

// returns the same ancester of two person
string same_ancester(vector<Person> family, string p1, string p2){
    vector<string> anc1;
    vector<string> anc2;
    
    anc1 = ancestor_finder(family, p1, anc1);
    anc2 = ancestor_finder(family, p2, anc2);

    for(int i=0; i<anc1.size(); i++){
        for(int j=0; j<anc2.size(); j++){
            if(anc1[i] == anc2[j])
                return anc1[i] + " " + anc1[i+1];
        }
    }

    return "Not found";

}

int main(){

    vector<Person> family;
    Person p;
    add(p, "ali", "akbar", "mariya", family);

    Person h;
    add(h, "ahmad", "naser", "mahsa", family);

    Person m;
    add(m, "armita", "ehsan", "lale", family);

    Person n;
    add(n, "narges", "ebrahim", "ladan", family);

    Person o;
    add(o, "amir", "ali", "narges", family);

    Person q;
    add(q, "arash", "ebrahim", "ladan", family);

    Person w;
    add(w, "ala", "arash", "mandana", family);

    cout<<same_ancester(family, "ala", "amir");


    return 0;
}
