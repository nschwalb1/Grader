//
// Created by nschwalb on 4/8/17.
//

#include <string>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

#ifndef GRADER_CLASSROOM_H
#define GRADER_CLASSROOM_H


class Assignment{
    int number;
    string name;
    double grade;
    string comments;
    Assignment* next;
    Assignment* previous;
public:
    Assignment(string nam, string comm = NULL){
        name = nam;
        comments = comm;
        grade = -1;
    }
    int getNumber(){
        return number;
    }
    void setnumber(int num){
        number = num;
    }
    Assignment* getNext(){
        return next;
    }
    void setNext(Assignment* nx){
        next =nx;
    }
    Assignment* getPrevious(){
        return previous;
    }
    void setPrevious(Assignment* prev){
        previous = prev;
    }
    void setName(string nm){
        name = nm;
    }
    string getName(){
        return name;
    }
    void setComments(string cm){
        comments = cm;
    }
    string getComments(){
        return comments;
    }
    void setGrade(double gd){
        grade = gd;
    }
    double getGrade(){
        return grade;
    }

};

class AssignmentsList{
    Assignment* first;
    Assignment* last;
public:
    AssignmentsList(){
        first = nullptr;
        last = nullptr;
    }

    ~AssignmentsList(){
        Assignment* currentNode = first;
        while (first){
            first = first->getNext();
            delete currentNode;
            currentNode = first;
        }
    }

    void insert(string name, string comments = NULL){
        Assignment* newAssignment = new Assignment(name, comments);
        newAssignment->setNext(nullptr);
        if(first == nullptr){
            first = newAssignment;
        } else{
            last->setNext(newAssignment);
        }
        last = newAssignment;
        index();
    }

    void remove(int number){
        Assignment* current = first;
        Assignment* previous = nullptr;
        if(first == nullptr){
            cout<<"Sorry, but there are no assignments to remove!\n"<<endl;
            return;
        }
        while(current != nullptr){
            if(current->getNumber() == number){
                if(previous == nullptr){
                    first = current->getNext();
                    delete current;
                    index();
                    cout<<"Assignment removed!"<<endl;
                    return;
                } else{
                    previous->setNext(current->getNext());
                    delete current;
                    index();
                    cout<<"Assignment removed!"<<endl;
                    return;
                }
            }
            previous = current;
            current = current->getNext();
        }
    }
    //Update flag enum: 1 = name, 2 = comment
    void update(int assignmentNumber, int flag, string update){
        Assignment* current = search(assignmentNumber);
        switch (flag){
            case 1:
                current->setName(update);
                break;
            case 2:
                current->setComments(update);
                break;
            default:
                return;
        }
        cout<<"Assignment updated!"<<endl;
    }

    Assignment* search(int assignmentNumber){
        Assignment* dne = new Assignment("DNE","DNE");
        Assignment* current = first;
        while (current != nullptr){
            if (current->getNumber() == assignmentNumber){
                return current;
            }
            current = current->getNext();
        }
        return dne;
    }

    Assignment* search(string assignmentName){
        Assignment* dne = new Assignment("DNE","DNE");
        Assignment* current = first;
        while (current != nullptr){
            if (current->getName().compare(assignmentName) == 0){
                return current;
            }
            current = current->getNext();
        }
        return dne;
    }

    double calculateGrade(){
        Assignment* current = first;
        double grade;
        vector<double> grades;
        while(current != nullptr){
            if(current->getGrade() >= 0){
                grades.push_back(current->getGrade());
            }
            current = current->getNext();
        }
        if(grades.size()>1){
            grade = accumulate(grades.begin(),grades.end(),0.0)/grades.size();
            return grade;
        } else if (grades.size() == 1){
            return grades.at(0);
        } else{
            return 0;
        }
    }

    void index(){
        int count = 1;
        Assignment* current = first;
        while(current != nullptr){
            current->setnumber(count);
            current = current->getNext();
            count++;
        }
    }

    void displayAllAssignments(){
        Assignment* current = first;
        cout<<"\nAll Assignments"<<endl;
        cout<<"# - Assignment Name: Assignment Comments"<<endl;
        cout<<"-----------------------------------------"<<endl;
        while(current != nullptr){
            cout<<current->getNumber()<<" - "<<current->getName()<<": "<<current->getComments()<<endl;
            current = current->getNext();
        }
        cout<<"-----------------------------------------"<<endl;
    }
};

class Student{
    string lastName; //Key
    string firstName;
    char middleInitial;
    AssignmentsList* assignments;
    double grade;
    Student* next;
    int index;
public:
    Student(string lastName, string firstName, char middleInitial = NULL){
        this->lastName = lastName;
        this->firstName = firstName;
        this->middleInitial = middleInitial;
        assignments = new AssignmentsList();
        next = nullptr;
        grade = -1;
    }
    string getLastName(){
        return lastName;
    }
    void setLastName(string ln){
        lastName = ln;
    }
    string getFirstName(){
        return firstName;
    }
    void setFirstName(string fn){
        firstName = fn;
    }
    char getMiddleInitial(){
        return middleInitial;
    }
    void setMiddleInitial(char mi){
        middleInitial = mi;
    }
    double getGrade(){
        grade = assignments->calculateGrade();
        return grade;
    }
    string getUpperLastName(){
        string temp;
        for(int i = 0; i < lastName.length(); i++){
            temp += toupper(lastName[i]);
        }
        return temp;
    }
    string getUpperFirstName(){
        string temp;
        for(int i = 0; i < firstName.length(); i++){
            temp += toupper(firstName[i]);
        }
        return temp;
    }
    Student* getNext(){
        return next;
    }
    void setNext(Student* nt){
        next = nt;
    }
    int getIndex(){
        return index;
    }
    void setIndex(int ix){
        index = ix;
    }
    AssignmentsList* getAssignments(){
        return assignments;
    }
};

class HashTable{
    int tableSize;
    Student **table;
public:
    HashTable(int tableSize){
        this->tableSize = tableSize;
        table = new Student * [tableSize];
        table[0] = new Student("Master","Master");
        for(int i = 1; i < tableSize; i++){
            table[i] = nullptr;
        }
    }

    ~HashTable(){
        for (int i = 0; i < tableSize; i++){
            Student* entryNode = table[i];
            while(entryNode != nullptr){
                Student* previousNode = entryNode;
                entryNode = entryNode->getNext();
                delete previousNode;
            }
        }
        delete table;
    }

    int hashfunc(string name){
        char first = name[0];
        int x = toupper(first) - 64;
        return x;
    }

    Student* search(string lastName){
        Student* dne = new Student("DNE","DNE");
        int selection;
        int key = hashfunc(lastName);
        Student* search = table[key];
        vector<Student*> results;
        string currUPLastName;
        for(int i = 0; i < lastName.length(); i++){
            currUPLastName += toupper(lastName[i]);
        }
        while(search != nullptr){
            if(currUPLastName.compare(search->getUpperLastName()) == 0){
                results.push_back(search);
            }
            search = search->getNext();
        }
        if(results.size() > 1){
            cout<<"\n";
            for(int i =0; i < results.size();i++){
                cout<<"Student #"<<results.at(i)->getIndex()<<" - "<<results.at(i)->getFirstName()<<" "<<results.at(i)->getMiddleInitial()<<"."<<endl;
            }
            cout<<"There are several students with that name, please enter the # of the student you would like information on. (Enter -1 if the student does not appear in the list): ";
            cin >> selection;
            if(selection == -1){
                return dne;
            }
            else{
                for(int i =0; i < results.size();i++){
                    if(selection == results.at(i)->getIndex()){
                        if(results.at(i)->getIndex() != 0){
                            cout<<results.at(i)->getIndex()<<" - "<<results.at(i)->getFirstName()<<" "<<results.at(i)->getMiddleInitial()<<". "<<results.at(i)->getLastName()<<": "<<results.at(i)->getGrade()<<endl;
                        }
                        return results.at(i);
                    }
                }
            }
        }
        else if(results.size() == 1){
            cout<<results.at(0)->getIndex()<<" - "<<results.at(0)->getFirstName()<<" "<<results.at(0)->getMiddleInitial()<<". "<<results.at(0)->getLastName()<<": "<<results.at(0)->getGrade()<<endl;
            return results.at(0);
        }
        else{
            cout<<"There is no student with the last name "<<lastName<<" in this class - "<<endl;
            return dne;
        }
    }

    Student* search(int index){
        Student* dne = new Student("DNE","DNE");
        Student* current;
        for(int i =0; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                if(current->getIndex() == index){
                    if(current->getIndex() != 0){
                        cout<<current->getIndex()<<" - "<<current->getFirstName()<<" "<<current->getMiddleInitial()<<". "<<current->getLastName()<<": "<<current->getGrade()<<endl;
                    }
                    return current;
                }
                current = current->getNext();
            }
        }
        cout << "Sorry, there aren't that many students in the class! - "<<endl;
        return dne;
    }

    void insert(string lastName, string firstName, char middleInitial = NULL){
        Student* current = new Student(lastName, firstName, middleInitial);
        int key = hashfunc(lastName);
        string currUPLastName, currUPFirstName;
        char currUpMI;
        for(int i = 0; i < lastName.length(); i++){
            currUPLastName += toupper(lastName[i]);
        }
        for(int i = 0; i < firstName.length(); i++){
            currUPFirstName += toupper(firstName[i]);
        }
        if(middleInitial != NULL){
            currUpMI = toupper(middleInitial);
        }
        else{
            currUpMI = middleInitial;
        }
        Student* previous = nullptr;
        Student* entry = table[key];
        //Determine alphabetical order of the last names for chaining insertion
        while(entry != nullptr){
            if(currUPLastName.compare(entry->getUpperLastName()) > 0){
                previous = entry;
                entry = entry->getNext();
            }
                //Check for same last name
            else if(currUPLastName.compare(entry->getUpperLastName()) == 0){
                if(currUPFirstName.compare(entry->getUpperFirstName()) > 0){
                    previous = entry;
                    entry = entry->getNext();
                }
                else if(currUPFirstName.compare(entry->getUpperFirstName()) == 0){
                    if(currUpMI > entry->getMiddleInitial()){
                        previous = entry;
                        entry = entry->getNext();
                    }
                    else if(currUpMI == entry->getMiddleInitial()){
                        char answer;
                        cout<<"There is already a " << current->getFirstName() << " " << current->getMiddleInitial() << ". " << current->getLastName() <<" in your class. Would you like to add another? (y/n) >>";
                        cin >> answer;
                        if (answer == 'y'){
                            if(previous == nullptr){
                                current->setNext(table[key]);
                                table[key] = current;
                                index();
                                return;
                            }
                            else{
                                current->setNext(entry);
                                previous->setNext(current);
                                index();
                                return;
                            }
                        } else{
                            return;
                        }
                    }
                    else{
                        if(previous == nullptr){
                            current->setNext(table[key]);
                            table[key] = current;
                            index();
                            return;
                        }
                        else{
                            current->setNext(entry);
                            previous->setNext(current);
                            index();
                            return;
                        }
                    }
                }
                else{
                    if(previous == nullptr){
                        current->setNext(table[key]);
                        table[key] = current;
                        index();
                        return;
                    }
                    else{
                        current->setNext(entry);
                        previous->setNext(current);
                        index();
                        return;
                    }
                }
            }
            else{
                //Set the head of the list = to the newest entry, as it is first alphabetically for that index
                if(previous == nullptr){
                    current->setNext(table[key]);
                    table[key] = current;
                    index();
                    return;
                }
                else{
                    current->setNext(entry);
                    previous->setNext(current);
                    index();
                    return;
                }
            }
        }
        if(entry == nullptr && previous == nullptr){
            table[key] = current;
            //cout<<"Successful insertion!"<<endl;
            index();
            return;
        }
        else{
            previous->setNext(current);
            index();
        }
    }

    int remove(string lastName){
        int key = hashfunc(lastName);
        Student* previous = nullptr;
        Student* search = table[key];
        Student* toDelete;
        vector<Student*> results;
        string currUPLastName;
        cout<<"\n";
        for(int i = 0; i < lastName.length(); i++){
            currUPLastName += toupper(lastName[i]);
        }
        if(search == nullptr){
            cout<<"There is no student with the last name "<<lastName<<" in this class - ";
            return -1;
        }
        while (search != nullptr){
            if(currUPLastName.compare(search->getUpperLastName()) == 0){
                results.push_back(search);
            }
            search = search->getNext();
        }
        if(results.size() > 1){
            int selection;
            cout<<"Student Removal Options"<<endl;
            cout<<"# - Student Name"<<endl;
            cout<<"-------------------------"<<endl;
            for(int i =0; i < results.size(); i++){
                cout<< results.at(i)->getIndex()<<" - "<< results.at(i)->getFirstName()<<" "<<results.at(i)->getMiddleInitial()<<"."<<endl;
            }
            cout<<"-------------------------"<<endl;
            cout<<"There are several students with that last name, please enter the # of the student you would like to remove from this class: ";
            cin >> selection;
            cout<<"\n";
            remove(selection);
            cout<<"Student removed!"<<endl;
            return 1;
        }
        else if(results.size() == 1){
            remove(results.at(0)->getIndex());
            cout<<"Student removed!"<<endl;
            return 1;
        }
        else{
            cout<<"There is no student with the last name "<<lastName<<" in this class - ";
            return -1;
        }
    }

    int remove(int ix){
        Student* previous;
        Student* current;
        for(int i =1; i < tableSize; i++){
            previous = nullptr;
            current = table[i];
            while(current != nullptr){
                if(current->getIndex() == ix){
                    if(previous == nullptr){
                        table[i] = current->getNext();
                        delete current;
                        index();
                        return 1;
                    }
                    else{
                        previous->setNext(current->getNext());
                        delete current;
                        return 1;
                    }
                }
                previous = current;
                current = current->getNext();
            }
        }
        cout << "Sorry, there aren't that many students in the class - "<<endl;
        return -1;
    }

    void index(){
        int count = 1;
        Student* current;
        for(int i =1; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                current->setIndex(count);
                current = current->getNext();
                count++;
            }
        }
    }

    void addAssignmentToAll(string name, string comments){
        Student* current;
        for(int i =0; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                current->getAssignments()->insert(name,comments);
                current = current->getNext();
            }
        }
    }

    void removeAssignmentFromAll(int num){
        Student* current;
        for(int i =0; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                current->getAssignments()->remove(num);
                current = current->getNext();
            }
        }
    }

    void updateAllAssignments(int assignmentNumber){
        int selection;
        string update;
        Student* current;
        cout<<"\nAssignment Update Options"<<endl;
        cout<<"# - Field"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"1 - Name\n2 - Comments"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"What would you like to update about this assignment? Please enter the number corresponding to your selection from above >>";
        cin >> selection;
        cin.ignore();
        switch (selection) {
            case 1:
                cout << "Please enter the new name >> ";
                getline(cin, update);
                break;
            case 2:
                cout << "Please enter the new comments >> ";
                getline(cin, update);
                break;
            default:
                cout << "Sorry, that is not a valid entry!" << endl;
                return;
        }
        for(int i =0; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                current->getAssignments()->update(assignmentNumber, selection, update);
                current = current->getNext();
            }
        }
        cout<<"Assignment # "<<assignmentNumber<<" has been updated with "<< update<<endl;
    }

    void displayAllStudents(){
        cout<<"\nAll Students"<<endl;
        cout<<"# - Student Name"<<endl;
        cout<<"-------------------------"<<endl;
        Student* current;
        for(int i =1; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                cout<<current->getIndex()<<" - "<<current->getFirstName()<<" "<<current->getMiddleInitial()<<". "<<current->getLastName()<<endl;
                current = current->getNext();
            }
        }
        cout<<"-------------------------"<<endl;
    }

    void displayAllGrades(){
        cout<<"\nAll Grades"<<endl;
        cout<<"# - Student Name: Grade"<<endl;
        cout<<"-------------------------"<<endl;
        Student* current;
        for(int i =1; i < tableSize; i++){
            current = table[i];
            while(current != nullptr){
                cout<<current->getIndex()<<" - "<<current->getFirstName()<<" "<<current->getMiddleInitial()<<". "<<current->getLastName()<<": "<<current->getGrade()<<endl;
                current = current->getNext();
            }
        }
        cout<<"-------------------------"<<endl;
    }

};

class Course{
    string className;
    string teacherName;
    HashTable* students;
public:
    Course(string cN, string tN){
        className = cN;
        teacherName = tN;
        students = new HashTable(27);
        cout<<"Class Created!\nTeacher: "<<teacherName<<"\n"<<"Class: "<<className<<endl;
    }
    HashTable* getStudents(){
        return students;
    }
};

#endif //GRADER_CLASSROOM_H
