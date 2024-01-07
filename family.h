#include<bits/stdc++.h>
using namespace std;

struct Person;
void print(Person &p);
int family_size(vector<Person> family);
void died(vector<Person> &family, string p);
int find(vector<Person> family, string _name);
void furthest(const std::vector<Person>& family);
int generations(vector<Person> &family, string p1, int gen=0);
bool relationsihp(string p1, string p2, vector<Person> family);
string same_ancester(string p1, string p2, vector<Person> family);
map<int, string> how_far(const vector<Person> &family, string p1);
bool bro_or_sis(string _name, string _sibling, vector<Person> family);
bool mom_is_that_you(string _name, string _mother, vector<Person> family);
bool dad_is_that_you(string _name, string _father, vector<Person> family);
void add(Person &p, string _name, string _father, string _mother, vector<Person> &family);
vector<string> ancestor_finder(string p1, vector<string> &ancestors, vector<Person> &family);


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
        p.mother->childs.push_back(p);
        family.push_back(*p.mother);
    }
    else {
        p.mother = &family[motherIndex];
        p.mother->childs.push_back(p);
    }

    int fatherIndex = find(family, _father);
    if(fatherIndex == -1){
        p.father = new Person;
        p.father->name = _father;
        p.father->childs.push_back(p);
        family.push_back(*p.father);
    }
    else {
        p.father = &family[fatherIndex];
        p.father->childs.push_back(p);
    }

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
void died(vector<Person> &family, string p){
    family[find(family, p)].name += " R.I.P";
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

// Find all ancestors of a person
vector<string> ancestor_finder(string p1, vector<string> &ancestors, vector<Person> &family){
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

// Returns the same ancester of two people
string same_ancester(string p1, string p2, vector<Person> family){
    vector<string> anc1;
    vector<string> anc2;
    
    anc1 = ancestor_finder(p1, anc1, family);
    anc2 = ancestor_finder(p2, anc2, family);

    for(int i=0; i<anc1.size(); i++){
        for(int j=0; j<anc2.size(); j++){
            if(anc1[i] == anc2[j])
                return anc1[i] + " " + anc1[i+1];
        }
    }

    return "Not found";

}

// Are two people related or not?
bool relationsihp(string p1, string p2, vector<Person> family){
    queue<string> q; 
    vector<string> visited;  

    q.push(p1);  
    visited.push_back(p1); 

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        int i = find(family, current);
        Person a = family[i];

        if (a.father && find(visited.begin(), visited.end(), a.father->name) == visited.end()) {
            q.push(a.father->name);
            if(a.father->name == p2)
                return 1;  
            visited.push_back(a.father->name);  
        }

        if (a.mother && find(visited.begin(), visited.end(), a.mother->name) == visited.end()) {
            q.push(a.mother->name); 
            if(a.father->name == p2)
                return 1;
            visited.push_back(a.mother->name);
        }

        if(a.father) {
            for(auto &child : a.father->childs) {
                if(child.name != current && find(visited.begin(), visited.end() ,child.name) == visited.end()) {
                    q.push(child.name);
                    if(a.father->name == p2)
                        return 1;
                    visited.push_back(child.name);
                }
            }
        }
    }

    return 0;
    
}

// How many generation are related to this person
int generations(vector<Person> &family, string p1, int gen=0){
    Person p = family[find(family, p1)];

    if (p.childs.size() == 0) {
        return gen;
    }
    else {
        int maxDepth = gen;
        for (int i = 0; i < p.childs.size(); i++) {
            int childDepth = generations(family, p.childs[i].name, gen + 1);
            maxDepth = max(maxDepth, childDepth);
        }
        return maxDepth;  
    }
}

// Maximum distance of a person to another related person in the family
map<int, string> how_far(const vector<Person> &family, string p1){
    queue<string> q; 
    vector<string> visited;  
    vector<string> relatives;

    q.push(p1);  
    visited.push_back(p1); 
    relatives.push_back(p1);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        int i = find(family, current);
        Person a = family[i];

        if (a.father && find(visited.begin(), visited.end(), a.father->name) == visited.end()) {
            relatives.push_back(a.father->name);
            q.push(a.father->name);  
            visited.push_back(a.father->name);  
        }

        if (a.mother && find(visited.begin(), visited.end(), a.mother->name) == visited.end()) {
            relatives.push_back(a.mother->name);
            q.push(a.mother->name); 
            visited.push_back(a.mother->name);
        }

        if(a.father) {
            for(auto &child : a.father->childs) {
                if(child.name != current && find(visited.begin(), visited.end() ,child.name) == visited.end()) {
                    relatives.push_back(child.name);
                    q.push(child.name);
                    visited.push_back(child.name);
                }
            }
        }
    }


    map<int, string> ans;
    ans[relatives.size()] = relatives[relatives.size()-1];
    return ans;
}

// Who two people have the furthest distance in the family
void furthest(const std::vector<Person>& family){
    map<pair<int, string>, string> answers;

    for (int i=0; i<family.size(); i++) {
        map<int, string> temp;
        temp = how_far(family, family[i].name);
        auto it = temp.rbegin();
        int distance = it->first;
        string name = it->second;

        answers[{distance, name}] = family[i].name;
    }

    auto last_pair = *answers.rbegin();
    cout<<"The furthest relationship in your family is between: ";
    cout<<last_pair.first.second << " & " << last_pair.second<<endl; 

}
