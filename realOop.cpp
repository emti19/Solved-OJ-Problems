#include<iostream>
#include<fstream>
#include<string>

using namespace std;
 

struct Student{
    string name;
    int marks[14];
};

struct StudentMark {
    string name;
    int mark;
};


int main()
{
    fstream file("student_scores.csv", ios::in);

    string header, studentName;
    getline(file, header); // discarding the level

    //constructing the mark array (2D)

    Student students[35]; 
 
    for(int student=0; student<35; student++){

        getline(file, students[student].name, ','); 

        string subjectMark;

        for(int subject=0; subject<14; subject++){
            if(subject<13) getline(file, subjectMark, ',');
            else getline(file, subjectMark);
            students[student].marks[subject] = stoi(subjectMark);
        }
    }

 
    StudentMark ranking[35];

    for(int subject=0; subject<14; subject++){
        for (int student = 0; student < 35; student++) {
            ranking[student].name = students[student].name;
            ranking[student].mark = students[student].marks[subject];
        }
    }
    

    file.close();
 


    return 0;
}