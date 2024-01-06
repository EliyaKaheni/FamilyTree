#include "family.h"
#include <unistd.h>

int main(){

    // Definition of the family
    vector<Person> family;

    // Sample family: uncomment if you need
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
    add(w, "ala", "ali", "narges", family);

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
            
            add(P, name, father, mother, family);
            cout<<"Added succesfully. you`ll be back to the main menu in 5 seconds ... ";

            cout<<endl;
            sleep(5);
            break;
        
        case 2:
            system("clear");
            cout<<"I`m so sorry that we have lost a person, please enter the name: ";
            cin>>name;

            died(family, name);
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

            if(dad_is_that_you(name, father, family))
                cout<<"Yes. " << father << " is the father of the " << name;
            else
                cout<<"No." << father << " isn`t the father of the " << name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 5:
            system("clear");
            cout<<"You are checking if two people are mother & (son/daughter) or not"<<endl;
            cout<<"Enter the name of the mother: ";
            cin>>father;
            cout<<"Enter the name of the son/daughter: ";
            cin>>name;

            if(mom_is_that_you(name, father, family))
                cout<<"Yes. " << mother << " is the mother of the " << name;
            else
                cout<<"No." << mother << " isn`t the mother of the " << name;
            
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

            if(bro_or_sis(name, name2, family))
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

            if(relationsihp(name, name2, family))
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

            father = same_ancester(name, name2, family);
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

            cout<<generations(family, name, 0)<<" generations have been born after "<< name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 10:
            system("clear");
            
            furthest(family);
            
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