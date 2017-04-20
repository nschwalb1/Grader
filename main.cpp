#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <limits>

using namespace std;
#include "classroom.h"

void runTest(){
    Course myClass("My Demo Class", "John Smith");

    /*Test student creations*/
    cout<<"\nTesting student insertions into hash table..."<<endl;
    cout<<"\nBEFORE...";
    myClass.getStudents()->displayAllStudents();
    myClass.getStudents()->insert("Andrews","Bob", 'D');
    myClass.getStudents()->insert("Booth","Kristina", 'S');
    myClass.getStudents()->insert("Smith","Evan", 'E');
    myClass.getStudents()->insert("Smith","Eli", 'O');
    myClass.getStudents()->insert("Smith","Emma", 'A');
    myClass.getStudents()->insert("Nelson","Bill", 'R');
    myClass.getStudents()->insert("James","Robert", 'S');
    myClass.getStudents()->insert("James","Robert", 'T');
    myClass.getStudents()->insert("Yarlin","Carl", 'V');
    myClass.getStudents()->insert("Zamboni","Louis", 'X');
    //myClass.getStudents()->insert("Andrews","Bob", 'D');

    cout<<"\nAFTER...";
    myClass.getStudents()->displayAllStudents();

    cout<<"\nLook good? Press enter to proceed to the next test! >>"<<endl;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    /*Test Student removal*/
    cout<<"\nTesting student removals from hash table..."<<endl;
    cout<<"\nAttempting to remove Eli O. Smith"<<endl;
    if(myClass.getStudents()->remove("Smith") == 1){
        cout<<"Smith removed successfully!"<<endl;
    }
    else{
        cout<<"Removal unsuccessful!"<<endl;
    }
    cin.ignore();
    cout<<"\nAttempting to remove Carl V. Yarlin"<<endl;
    if(myClass.getStudents()->remove("Yarlin") == 1){
        cout<<"Yarlin removed successfully!"<<endl;
    }
    else{
        cout<<"Removal unsuccessful!"<<endl;
    }
    cout<<"\nAttempting to remove Billy O. Brody"<<endl;
    if(myClass.getStudents()->remove("Brody") == 1){
        cout<<"Brody removed successfully!"<<endl;
    }
    else{
        cout<<"Removal unsuccessful!"<<endl;
    }
    myClass.getStudents()->displayAllStudents();

    cout<<"\nLook good? Press enter to proceed to the next test! >>"<<endl;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    /*Test Student search*/
    cout<<"\nTesting student search - Searching for Zamboni..."<<endl;
    myClass.getStudents()->search("Zamboni");

    cout<<"\nLook good? Press enter to proceed to the next test! >>"<<endl;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    /*Test Assignment Creation*/
    cout<<"\nTesting master assignment creation..."<<endl;
    myClass.getStudents()->addAssignmentToAll("HW1","Simple Math Problems");
    myClass.getStudents()->addAssignmentToAll("HW2","Intermediate Math Problems");
    myClass.getStudents()->addAssignmentToAll("HW3","Advanced Math Problems with a bit of a twist!");
    myClass.getStudents()->addAssignmentToAll("Exam 1","Covers all of the math problems to this point");
    myClass.getStudents()->search(0)->getAssignments()->displayAllAssignments();
    cout<<"\nLook good? Press enter to proceed to the next test! >>"<<endl;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    /*Test Assignment Update*/
    cout<<"\nTesting master assignment update..."<<endl;
    cout<<"Let's update assignment #4 - Exam 1\n"<<endl;
    myClass.getStudents()->updateAllAssignments(4);
    myClass.getStudents()->search(0)->getAssignments()->displayAllAssignments();

    cout<<"\nLook good? Press enter to proceed to the next test! >>"<<endl;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    /*Test Assignment Removal*/
    cout<<"\nTesting master assignment removal..."<<endl;
    cout<<"Removing assignment #2 - 'HW2'"<<endl;
    myClass.getStudents()->removeAssignmentFromAll(2);
    myClass.getStudents()->search(0)->getAssignments()->displayAllAssignments();

    cout<<"\nLook good? Press enter to proceed to the next test! >>"<<endl;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');


    /*myClass.getStudents()->search("James")->getAssignments()->search(1)->setGrade(45);
    myClass.getStudents()->search(4)->getAssignments()->search(2)->setGrade(60);
    myClass.getStudents()->search(4)->getAssignments()->search(3)->setGrade(80);
    cout<<"Grade = "<<myClass.getStudents()->search(4)->getGrade();
    //cout<<myClass.getStudents()->search(3)->getAssignments()->search(1)->getName()<<endl;*/
}
void crudSubMenu(string subject){
    if(subject.compare("student") == 0){
        cout<<"1 - Add "<<subject<<endl;
        cout<<"2 - Remove "<<subject<<endl;
    } else{
        cout<<"1 - Add "<<subject<<endl;
        cout<<"2 - Remove "<<subject<<endl;
        cout<<"3 - Update "<<subject<<endl;
    }

}
void runApplication(Course myC){
    Course myClass = myC;

    bool running = true;
    while(running) {
        int menuSelection, crudSubMenuSelection, studentViewSelection, studentSearchSelection, studentSearchIndex, assignmentSearchSelection, assignmentSearchIndex = 0;
        string studentSearchName, assignmentSearchName, ln,fn,an,com;
        Student* current;
        Assignment* currentAssign;
        double tempGrade;
        char mi;
        cout << "\n\nMy Teacher's Pet Menu\n--------------------" << endl;
        cout << "1 - Search for student" << endl;
        cout << "2 - Search assignment" << endl;
        cout << "3 - Add/Remove students" << endl;
        cout << "4 - Add/Remove/Update assignments" << endl;
        cout << "5 - Enter/Change Grades" << endl;
        cout << "6 - View all students" << endl;
        cout << "7 - View all assignments" << endl;
        cout << "           ...          " << endl;
        cout << "10 - Exit (Press anytime to leave)" << endl;
        cout << "Please enter numeric selection here >>";
        cin >> menuSelection;
        switch (menuSelection) {
            case 1:
                cout << "Search by:\n1 - Last Name\n2 - Index #\n>>";
                cin >> studentSearchSelection;
                cin.ignore();
                switch (studentSearchSelection) {
                    case 1:
                        cout << "\nLast name >>";
                        getline(cin, studentSearchName);
                        myClass.getStudents()->search(studentSearchName);
                        break;
                    case 2:
                        cout << "\nIndex # >>";
                        cin >> studentSearchIndex;
                        myClass.getStudents()->search(studentSearchIndex);
                        break;
                    default:
                        cout<<"\nInvalid selection, returning to main menu!\n";
                        break;
                }
                break;
            case 2:
                cout << "Search by:\n1 - Assignment Name\n2 - Index #\n>>";
                cin >> assignmentSearchSelection;
                cin.ignore();
                switch (assignmentSearchSelection) {
                    case 1:
                        cout << "\nAssignment name >>";
                        getline(cin, assignmentSearchName);
                        if (myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName)->getName().compare("DNE") == 0) {
                            myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName);
                            cout << "Search failed!" << endl;
                        }
                        else{
                            cout << myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName)->getNumber()<<" - "<<myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName)->getName()<<": "<<myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName)->getComments()<<endl;
                        }
                        break;
                    case 2:
                        cout << "\nIndex # >>";
                        cin >> assignmentSearchIndex;
                        if (myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex)->getName().compare("DNE") == 0) {
                            myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex);
                            cout << "Search failed!" << endl;
                        }
                        else{
                            cout << myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex)->getNumber()<<" - "<<myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex)->getName()<<": "<<myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex)->getComments()<<endl;                        }
                        break;
                    default:
                        cout<<"\nInvalid selection, returning to main menu!\n";
                        break;
                }
                break;
            case 3:
                crudSubMenu("student");
                cout<<">>";
                cin >> crudSubMenuSelection;
                cin.ignore();
                switch(crudSubMenuSelection){
                    case 1:
                        cout<<"\nEnter the last name >>";
                        getline(cin, ln);
                        cout<<"\nEnter the first name >>";
                        getline(cin, fn);
                        cout<<"\nEnter the middle initial >>";
                        cin >> mi;
                        myClass.getStudents()->insert(ln,fn,mi);
                        break;
                    case 2:
                        cout << "Remove by:\n1 - Last Name\n2 - Index #\n>>";
                        cin >> studentSearchSelection;
                        cin.ignore();
                        switch (studentSearchSelection) {
                            case 1:
                                cout << "\nLast name >>";
                                getline(cin, studentSearchName);
                                myClass.getStudents()->remove(studentSearchName);
                                break;
                            case 2:
                                cout << "\nIndex # >>";
                                cin >> studentSearchIndex;
                                myClass.getStudents()->search(studentSearchIndex);
                                break;
                            default:
                                cout<<"\nInvalid selection, returning to main menu!\n";
                                break;
                        }
                        break;
                    default:
                        cout<<"\nInvalid selection, returning to main menu!\n";
                        break;
                }
                break;
            case 4:
                crudSubMenu("assignment");
                cout<<">>";
                cin >> crudSubMenuSelection;
                cin.ignore();
                switch(crudSubMenuSelection){
                    case 1:
                        cout<<"\nEnter the assignment name >>";
                        getline(cin, an);
                        cout<<"\nEnter any additional comments >>";
                        getline(cin, com);
                        myClass.getStudents()->addAssignmentToAll(an,com);
                        break;
                    case 2:
                        cout << "\nAssignment number >>";
                        cin>>assignmentSearchIndex;
                        myClass.getStudents()->removeAssignmentFromAll(assignmentSearchIndex);
                        break;
                    case 3:
                        cout << "\nAssignment number >>";
                        cin>>assignmentSearchIndex;
                        myClass.getStudents()->updateAllAssignments(assignmentSearchIndex);
                        break;
                    default:
                        cout<<"\nInvalid selection, returning to main menu!\n";
                        break;
                }
                break;
            case 5:
                cout << "Enter grade by:\n1 - Last Name\n2 - Index #\n>>";
                cin >> studentSearchSelection;
                cin.ignore();
                switch (studentSearchSelection) {
                    case 1:
                        cout << "\nLast name >>";
                        getline(cin, studentSearchName);
                        current = myClass.getStudents()->search(studentSearchName);
                        break;
                    case 2:
                        cout << "\nIndex # >>";
                        cin >> studentSearchIndex;
                        current = myClass.getStudents()->search(studentSearchIndex);
                        break;
                    default:
                        cout<<"\nInvalid selection, returning to main menu!\n";
                        break;
                }
                cout << "Choose assignment by:\n1 - Assignment Name\n2 - Index #\n>>";
                cin >> assignmentSearchSelection;
                cin.ignore();
                switch (assignmentSearchSelection) {
                    case 1:
                        cout << "\nAssignment name >>";
                        getline(cin, assignmentSearchName);
                        if (myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName)->getName().compare("DNE") == 0) {
                            myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchName);
                            cout << "This assignment doesn't exist!" << endl;
                        }
                        else{
                            currentAssign = myClass.getStudents()->search(current->getIndex())->getAssignments()->search(assignmentSearchName);
                        }
                        break;
                    case 2:
                        cout << "\nIndex # >>";
                        cin >> assignmentSearchIndex;
                        if (myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex)->getName().compare("DNE") == 0) {
                            myClass.getStudents()->search(0)->getAssignments()->search(assignmentSearchIndex);
                            cout << "This assignment doesn't exist!" << endl;
                        }
                        else{
                            currentAssign = myClass.getStudents()->search(current->getIndex())->getAssignments()->search(assignmentSearchIndex);
                        }
                        break;
                    default:
                        cout<<"\nInvalid selection, returning to main menu!\n";
                        break;
                }
                cout<<"What grade would you like to assign? >>";
                cin >> tempGrade;
                currentAssign->setGrade(tempGrade);
                break;
            case 6:
                myClass.getStudents()->displayAllGrades();
                break;
            case 7:
                myClass.getStudents()->search(0)->getAssignments()->displayAllAssignments();
                break;
            case 10:
                running = false;
                break;
            default:
                break;
        }
    }
}
void initializeApplication(){
    string className, teacherName;
    int loadSelection = 0;
    cout<<"What's your name? >>";
    getline(cin, teacherName);
    cout<<"What class do you teach? >>";
    getline(cin, className);
    Course myClass(className, teacherName);
    cout<<"\nWould you like to:\n1 - Pre-load some students and assignments?\nOr\n2 - Start from scratch?\nPlease enter the # of the desired selection>>";
    cin >> loadSelection;
    cin.ignore();
    switch (loadSelection){
        case 1:
            myClass.getStudents()->insert("Andrews","Bob", 'D');
            myClass.getStudents()->insert("Booth","Kristina", 'S');
            myClass.getStudents()->insert("Smith","Evan", 'E');
            myClass.getStudents()->insert("Nelson","Bill", 'R');
            myClass.getStudents()->insert("James","Robert", 'S');
            myClass.getStudents()->insert("James","Robert", 'T');
            myClass.getStudents()->insert("Yarlin","Carl", 'V');
            myClass.getStudents()->insert("Zamboni","Louis", 'X');
            myClass.getStudents()->insert("Smith","Eli", 'O');
            myClass.getStudents()->insert("Smith","Emma", 'A');
            myClass.getStudents()->addAssignmentToAll("HW1","Simple Math Problems");
            myClass.getStudents()->addAssignmentToAll("HW2","Intermediate Math Problems");
            myClass.getStudents()->addAssignmentToAll("HW3","Advanced Math Problems with a bit of a twist!");
            myClass.getStudents()->addAssignmentToAll("Exam 1","Covers all of the math problems to this point");
            for(int i = 1; i < 11; i++){
                for (int j = 1; j < 5; j++){
                    myClass.getStudents()->search(i)->getAssignments()->search(j)->setGrade(rand()%100);
                }
            }
            break;
        case 2:
            break;
        default:
            cout<<"\nInvalid selection, returning to main menu!\n";
            return;
    }
    runApplication(myClass);
}


int main() {

    bool run = true;
    string className, teacherName;
    cout<<"Hello! Welcome to Teachers Pet, a simple way to manage your students and assignments!\n"<<endl;

    while(run){
        int choice = 0;
        cout<<"Which would you like to do? Please enter the number corresponding to your selection below?"<<endl;
        cout<<"1 - Run the demo"<<endl;
        cout<<"2 - Use the application\n>>";
        cin >> choice;
        cin.ignore();
        switch(choice){
            case 1:
                runTest();
                break;
            case 2:
                initializeApplication();
                break;
        }
        run = false;
    }
    cout<<"Thank you, have a nice day!"<<endl;
    return 0;
}