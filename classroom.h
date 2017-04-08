//
// Created by nschwalb on 4/8/17.
//

#include <string>
#include <vector>
using namespace std:

#ifndef GRADER_CLASSROOM_H
#define GRADER_CLASSROOM_H

class Class{
    string* className;
    string* teacherName;
    vector<Student*> students;

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
};

class AssignmentsList{
    Assignment* first = nullptr;
    Assignment* last = nullptr;
public:
    void findByNum(int assignmentNumber){
        Assignment* current = first;
        bool found = false;
        while (!found){
            if (current->getNumber() == assignmentNumber){
                //print assignment details;
            }
            found = true;
        }

    }
};

class Student{
    string* name;
    int* number;
    vector<AssignmentsList*> assignments;

};


#endif //GRADER_CLASSROOM_H
