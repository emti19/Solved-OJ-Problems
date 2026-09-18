#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

struct Student {
    string name;
    int sub_mid;
    int sub_final;
    double midMean;
    double finalMean;
};

struct Subject{
    string term;
    double mean;
    double median;
    double variance;
};

struct StudentMark {
    string name;
    int mark;
};

void sortMarks(int arr[], int n)
{
    int i,j,temp;

    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                temp =arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}
void sortRanking(StudentMark arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (arr[i].mark > arr[j].mark) {

                StudentMark temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    fstream file("student_scores.csv", ios::in);

    // Studentwise mean marks
    Student student[35];
    //skip the header
    string header;
    getline(file, header);

    string sub_mid;
    string sub_final;
    // int mid_total = 0;
    
    for(int i=0;i<35;i++){
        int student_mid_total = 0;
        int final_total = 0;
        getline(file, student[i].name, ',');
        //mid calculation
        for(int j=0; j<7; j++){
             getline(file, sub_mid, ',');
             student_mid_total += stoi(sub_mid);
            //  cout<<"mid total: "<<i<<":"<<student_mid_total<<" j = "<<j<<endl;
        }
        //final calculation
        for(int k=7; k<13; k++){
             getline(file, sub_final, ',');
             final_total += stoi(sub_final);
            //  cout<<"final total: "<<i<<":"<<final_total<<" k = "<<k<<endl;
        }

        getline(file, sub_final);
        final_total += stoi(sub_final);
 

        student[i].midMean = student_mid_total/7.0;
        student[i].finalMean = final_total/7.0;

        //ignore the rest of the line
        // string rest;
        // getline(file, rest);
    }
    file.close();

    //Subjectwise mean marks
    file.open("student_scores.csv", ios::in);

    //skip the header 
    getline(file, header); //never using the header again

    double marks[35][14];
    int i, j;

    for(i=0; i<35; i++){
        getline(file, student[i].name, ',');
        string mark;
        for(j=0; j<13; j++){
            getline(file, mark, ',');
            marks[i][j] = stoi(mark);
        }

        getline(file, mark);
        marks[i][j] = stoi(mark);
    }

    file.close();

    //Marks

    // cout<<"All Marks"<<endl;

    // for(int i=0; i<35; i++){
    //     for(int j=0;j<14;j++){
    //         cout<<marks[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }



    Subject subject[14]; 
    // int serial;
    for(i=0;i<14;i++){
    double total_mark = 0;
        for(j=0;j<35;j++){
            total_mark += marks[j][i];
            // cout<<marks[j][i]<<" ";
        } 
        subject[i].mean = total_mark/35;
        if (i<7) {
            subject[i].term = "Mid";
        }
        else 
        {
            subject[i].term = "Final";
            
        } 
        
    }
    


    int subjectMarks[14][35];

    for(int subject = 0; subject < 14; subject++){
        for(int student = 0; student<35; student++){
            subjectMarks[subject][student] = marks[student][subject];
        }
    }
 
    for(int subj = 0; subj  < 14; subj++){
        sortMarks(subjectMarks[subj], 35);
        subject[subj].median = subjectMarks[subj][17];
    }

    //variance calculation
    //formula 1/n sum of (mark-mean)^2
     int sum = 0;
     for(int sub = 0; sub < 7; sub++){
        for(int student = 0; student<35; student++){
           sum += (marks[student][sub]-subject[sub].mean)*(marks[student][sub]-subject[sub].mean);
        }
        subject[sub].variance = sum/35;
    }
     sum = 0;
     for(int sub = 7; sub <14; sub++){
        for(int student = 0; student<35; student++){
           sum += (marks[student][sub]-subject[sub].mean)*(marks[student][sub]-subject[sub].mean);
        }
        subject[sub].variance = sum/35;
    }

    cout<< left
        << setw(12) <<"Subject"
        << setw(18) <<"Midterm Mean"
        << setw(18) <<"Midterm Median"
        << setw(18) <<"Midterm variance"
        << setw(18) <<"Final Mean"
        << setw(18) <<"Final Median"
        << setw(18) <<"Final Variance"<<endl;
    

    for(i=0,j=7; i<7 && j<14; i++,j++){
         cout<< left
        << setw(12) <<"Sub"+to_string(i+1)
        << setw(18) <<fixed<<setprecision(2)<<subject[i].mean
        << setw(18) <<subject[i].median
        << setw(18) <<subject[i].variance
        << setw(18) <<fixed<<setprecision(2)<<subject[j].mean
        << setw(18) <<subject[j].median
        << setw(18) <<subject[j].variance<<endl;
    }
     
    //Ranking
    for (int subj = 0; subj < 14; subj++) {

    StudentMark ranking[35];

    for (int stu = 0; stu < 35; stu++) {
        ranking[stu].name = student[stu].name;
        ranking[stu].mark = marks[stu][subj];
    }

    sortRanking(ranking, 35);

    cout<<

    cout << "---------------Sub"
         << (subj % 7) + 1
         << (subj < 7 ? " Midterm" : " Final")
         << " Top---------------" << endl;

    for (int stu = 34, rank = 1; stu >= 30; stu--, rank++) {
        cout << rank << ". "
             << ranking[stu].name
             << " (" << ranking[stu].mark << ")"
             << endl;
    }
}


    return 0;


}