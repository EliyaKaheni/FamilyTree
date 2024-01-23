#include <bits/stdc++.h>
// Library effective with Windows
// #include <windows.h>
 
// Library effective with Linux
#include <unistd.h>
#include "SHA.h"

using namespace std;

// Functions & Structures 
struct Person;
void print(Person &p);
int family_size(vector<Person> family);
void died(vector<Person> &family, string p);
int find(vector<Person> family, string _name);
void furthest(const std::vector<Person>& family);
int generations(vector<Person> &family, string p1, int gen=0);
bool relationship(string p1, string p2, vector<Person> family);
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

// Find all ancestors of a person using BFS
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

// Are two people related or not? using BFS
bool relationship(string p1, string p2, vector<Person> family){
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
int generations(vector<Person> &family, string p1, int gen){
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

// Maximum distance of a person to another related person in the family BFS
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

// Which two people have the furthest distance in the family
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

// Saves the family tree
void save(vector<Person> family){
    string jsonString = "{\n    ";
    int i=0;
    for( ; i<family.size()-1 ; i++){
        Person person = family[i];
        if(person.father){
            jsonString += "\"" + person.name + "\": [ ";
            jsonString += "\"" + person.father->name + "\" " + ", ";
            jsonString += "\"" + person.mother->name + "\" " + " ]";
            jsonString += ",\n    ";
        }
    }
        jsonString += "\"" + family[i].name + "\": [ ";
        jsonString += "\"" + family[i].father->name + "\" " + ", ";
        jsonString += "\"" + family[i].mother->name + "\" " + " ]";
        jsonString += "\n";
        jsonString += "}";

        ofstream outFile("familyData.json");

        if (outFile.is_open()) {
            outFile << jsonString;
            outFile.close();
        }
     
}

int main(){

    // Definition of the family
    vector<Person> family;

    // Sample family: uncomment if you need
    Person p;
    add(p, sha1_encode("ali"), sha1_encode("akbar"), sha1_encode("mariya"), family);

    Person h;
    add(h, sha1_encode("ahmad"), sha1_encode("naser"), sha1_encode("mahsa"), family);

    Person m;
    add(m, sha1_encode("armita"), sha1_encode("ehsan"), sha1_encode("lale"), family);

    Person n;
    add(n, sha1_encode("narges"), sha1_encode("ebrahim"), sha1_encode("ladan"), family);

    Person o;
    add(o, sha1_encode("amir"), sha1_encode("ali"), sha1_encode("narges"), family);

    Person q;
    add(q, sha1_encode("arash"), sha1_encode("ebrahim"), sha1_encode("ladan"), family);

    Person w;
    add(w, sha1_encode("alaa"), sha1_encode("ali"), sha1_encode("narges"), family);

    // Main Menu
    bool LifeIsBeautiful = true;
    while(LifeIsBeautiful){
        int task;
        cout<<"^^^^^^^^^^Hello Mysterious Family^^^^^^^^^^"<<endl;
        cout<<"you can easily and safely make your family tree using these commands:"<<endl;
        cout<<"1. Adding a person"<<endl;
        cout<<"2. A person is dead"<<endl;
        cout<<"3. Size of the family"<<endl<<endl;
        cout<<"4. Checking (Father & son/daughter)"<<endl;
        cout<<"5. Checking (Mother & son/daughter)"<<endl;
        cout<<"6. Checking (Siblings)"<<endl;
        cout<<"7. Checking (Distant relatives)"<<endl<<endl;
        cout<<"8. Tell me the (Common ancestor)"<<endl;
        cout<<"9. Tell me the (Furthest born)"<<endl;
        cout<<"10. Tell me the (Furthest ralativeness)"<<endl<<endl;
        cout<<"11. Visualize"<<endl<<endl;
        cout<<"0.  Quit"<<endl<<endl<<endl;
        
        cout<<"Please enter your command: ";
        cin>>task;

        string name, father, mother, name2;
        Person P;
        switch(task){

        case 1:
            system("clear");
            cout<<"You are adding a person to the family tree:"<<endl;
            cout<<"please enter the name of the person: ";
            cin>>name;
            cout<<"please enter the name of the father of the person: ";
            cin>>father;
            cout<<"please enter the name of the mother of the person: ";
            cin>>mother;
            
            add(P, sha1_encode(name), sha1_encode(father), sha1_encode(mother), family);
            cout<<"Added succesfully. you`ll be back to the main menu in 5 seconds ... ";

            cout<<endl;
            sleep(5);
            break;
        
        case 2:
            system("clear");
            cout<<"I`m so sorry that we have lost a person, please enter the name: ";
            cin>>name;

            died(family, sha1_encode(name));
            cout<<"Edited succesfully. you`ll be back to the main menu in 5 seconds ... ";

            
            cout<<endl;
            sleep(5);
            break;

        case 3:
            system("clear");
            cout<<"there is "<<family_size(family)<<" people in your family."<<endl;
            
            cout<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 4:
            system("clear");
            cout<<"You are checking if two people are father & (son/daughter) or not"<<endl;
            cout<<"Enter the name of the father: ";
            cin>>father;
            cout<<"Enter the name of the son/daughter: ";
            cin>>name;

            if(dad_is_that_you(sha1_encode(name), sha1_encode(father), family))
                cout<<"Yes. " << father << " is the father of  " << name;
            else
                cout<<"No." << father << " isn`t the father of " << name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 5:
            system("clear");
            cout<<"You are checking if two people are mother & (son/daughter) or not"<<endl;
            cout<<"Enter the name of the mother: ";
            cin>>mother;
            cout<<"Enter the name of the son/daughter: ";
            cin>>name;

            if(mom_is_that_you(sha1_encode(name), sha1_encode(mother), family))
                cout<<"Yes. " << mother << " is the mother of " << name;
            else
                cout<<"No." << mother << " isn`t the mother of " << name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 6:
            system("clear");
            cout<<"You are checking if two people are siblings or not"<<endl;
            cout<<"Enter the name of the fist person: ";
            cin>>name;
            cout<<"Enter the name of the second person: ";
            cin>>name2;

            if(bro_or_sis(sha1_encode(name), sha1_encode(name2), family))
                cout<<"Yes. " << name << " & " << name2 << " are siblings.";
            else
                cout<<"No. " << name << " & " << name2 << " aren`t siblings.";
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 7:
            system("clear");
            cout<<"You are checking if two people are distant relatives or not"<<endl;
            cout<<"Enter the name of the fist person: ";
            cin>>name;
            cout<<"Enter the name of the second person: ";
            cin>>name2;

            if(relationship(sha1_encode(name), sha1_encode(name2), family))
                cout<<"Yes. " << name << " & " << name2 << " are relatives.";
            else
                cout<<"No. " << name << " & " << name2 << " aren`t relatives.";
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 8:
            system("clear");
            cout<<"You are looking for the common ancestor of two people"<<endl;
            cout<<"Enter the name of the fist person: ";
            cin>>name;
            cout<<"Enter the name of the second person: ";
            cin>>name2;

            father = same_ancester(sha1_encode(name), sha1_encode(name2), family);
            if(father != "Not found")
                cout<<father<< " is ancestor of both of them"<<endl;
            else
                cout<<"They don`t have same ancestors"<<endl;

            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 9:
            system("clear");
            cout<<"You wnat to know how many generations have been born after a person"<<endl;
            cout<<"Enter the name of the person: ";
            cin>>name;

            cout<<generations(family, sha1_encode(name), 0)<<" generations have been born after "<< name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 10:
            system("clear");
            
            furthest(family);
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 11:
            save(family);
            cout<<"Your family datas saved and you can see it now ...";
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 0:
            LifeIsBeautiful = false;
            system("clear");
            cout<<endl<<"Wish to see you soon <3"<<endl;
            sleep(5);
            break;
        }

    }


    return 0;
}