//
// Created by nschwalb on 4/8/17.
//

#include <string>
#include <vector>
using namespace std;

#ifndef GRADER_CLASSROOM_H
#define GRADER_CLASSROOM_H



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
    int hashfunc(string name){
        char first = name[0];
        int x = toupper(first) - 64;
        return x;
    }
    void insert(string lastName, string firstName, string middleInitial = NULL){
        int key = hashfunc(lastName);
        string currUPLastName;
        for(int i = 0; i < lastName.length(); i++){
            currUPLastName += toupper(lastName[i]);
        }
        Student* previous = nullptr;
        Student* entry = table[key];

        //Determine alphabetical order of the last names for chaining insertion
        while(entry != nullptr){
            if(currUPLastName.compare(entry->getUpperLastName()) > 0){
                previous = entry;
                entry = entry->getNext();
            }
            else{
                if(previous == nullptr){

                }
            }
        }

        if(entry == nullptr){
            table[key] = ;
        }
    }
};



class Class{
    string* className;
    string* teacherName;
    HashTable students;

public:

};

class Assignment{
    int number;
    string name;
    double grade;
    string* comments;
    Assignment* next;
    Assignment* previous;
public:
    int getNumber(){
        return number;
    }
    Assignment* getNext(){
        return next;
    }
};

class AssignmentsList{
    Assignment* first = nullptr;
    Assignment* last = nullptr;
public:
    Assignment* findByNum(int assignmentNumber){
        Assignment* current = first;
        while (current->getNext() != nullptr){
            if (current->getNumber() == assignmentNumber){
                return current;
            }
            current = current->getNext();
        }
        return nullptr;
    }
};

class Student{
    friend class HashTable;
    string lastName; //Key
    string firstName;
    string middleInitial;
    double grade;
    vector<AssignmentsList*> assignments;
    Student* next;
    Student* previous;
public:
    Student(string lastName, string firstName, string middleInitial = NULL){
        this->lastName = lastName;
        this->firstName = firstName;
        this->middleInitial = middleInitial;
        assignments = nullptr;
        grade = NULL;
        next = nullptr;
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
    string getMiddleInitial(){
        return middleInitial;
    }
    void setMiddleInitial(string mi){
        middleInitial = mi;
    }
    double getGrade(){
        return grade;
    }
    void setGrade(){
        //ToDo - write grade calculation from assignments list
    }
    string getUpperLastName(){
        string temp;
        for(int i = 0; i < lastName.length(); i++){
            temp += toupper(lastName[i]);
        }
        return temp;
    }
    Student* getNext(){
        return next;
    }
    void setNext(Student* nt){
        next = nt;
    }
    Student* getPrevious(){
        return previous;
    }
    void setPrevious(Student* pv){
        previous = pv;
    }
};


#endif //GRADER_CLASSROOM_H
