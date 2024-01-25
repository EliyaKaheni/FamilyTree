#include "family.h"
#include "SHA.h"
#include <windows.h>

using namespace std;

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
            system("cls");
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
            system("cls");
            cout<<"I`m so sorry that we have lost a person, please enter the name: ";
            cin>>name;

            died(family, sha1_encode(name));
            cout<<"Edited succesfully. you`ll be back to the main menu in 5 seconds ... ";

            
            cout<<endl;
            sleep(5);
            break;

        case 3:
            system("cls");
            cout<<"there is "<<family_size(family)<<" people in your family."<<endl;
            
            cout<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 4:
            system("cls");
            cout<<"You are checking if two people are father & (son/daughter) or not"<<endl;
            cout<<"Enter the name of the father: ";
            cin>>father;
            cout<<"Enter the name of the son/daughter: ";
            cin>>name;

            if(dad_is_that_you(sha1_encode(name), sha1_encode(father), family))
                cout<<"Yes. " << father << " is the father of " << name;
            else
                cout<<"No." << father << " isn`t the father of " << name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 5:
            system("cls");
            cout<<"You are checking if two people are mother & (son/daughter) or not"<<endl;
            cout<<"Enter the name of the mother: ";
            cin>>mother;
            cout<<"Enter the name of the son/daughter: ";
            cin>>name;

            if(mom_is_that_you(sha1_encode(name), sha1_encode(mother), family))
                cout<<"Yes. " << mother << " is the mother of the " << name;
            else
                cout<<"No." << mother << " isn`t the mother of the " << name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;

        case 6:
            system("cls");
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
            system("cls");
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
            system("cls");
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
            system("cls");
            cout<<"You wnat to know how many generations have been born after a person"<<endl;
            cout<<"Enter the name of the person: ";
            cin>>name;

            cout<<generations(family, sha1_encode(name), 0)<<" generations have been born after "<< name;
            
            cout<<endl<<"You`ll be back to the main menu in 5 seconds ..."<<endl;
            sleep(5);
            break;
        
        case 10:
            system("cls");
            
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
            system("cls");
            cout<<endl<<"Wish to see you soon <3"<<endl;
            sleep(5);
            break;
        }

    }


    return 0;
}
