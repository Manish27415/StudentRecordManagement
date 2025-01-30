#include <bits/stdc++.h>

using namespace std;

struct Student {
    string fullName;
    string studentID;
    int rollNumber;
    string branch;
    vector < vector < float >> semesterMarks;
    float cgpa;
};

class StudentRecordSystem {
    private: vector < Student > studentRecords;
    map < string,
    int > branchToppers;
    int collegeTopperRollNumber;

    public: void addStudent();
    void displayAllStudents();
    void displayStudent(int rollNumber);
    void deleteStudent(int rollNumber);
    void calculateCGPA(int rollNumber);
    int binarySearch(int rollNumber);
    void findSemesterToppers();
};

int StudentRecordSystem::binarySearch(int rollNumber) {
    int left = 0, right = studentRecords.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (studentRecords[mid].rollNumber == rollNumber)
            return mid;
        else if (studentRecords[mid].rollNumber < rollNumber)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void StudentRecordSystem::addStudent() {
    Student newStudent;
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, newStudent.fullName);
    cout << "Enter Student ID: ";
    cin >> newStudent.studentID;
    cout << "Enter Roll Number: ";
    cin >> newStudent.rollNumber;
    cout << "Enter Branch: ";
    cin >> newStudent.branch;

    newStudent.semesterMarks.resize(8);
    for (int sem = 0; sem < 8; sem++) {
        int numSubjects;
        cout << "Enter number of subjects for semester " << sem + 1 << " (8-12): ";
        cin >> numSubjects;
        newStudent.semesterMarks[sem].resize(numSubjects);
        cout << "Enter marks for semester " << sem + 1 << ": ";
        for (int sub = 0; sub < numSubjects; sub++) {
            cin >> newStudent.semesterMarks[sem][sub];
        }
    }

    studentRecords.push_back(newStudent);
    sort(studentRecords.begin(), studentRecords.end(), [](const Student & a,
        const Student & b) {
        return a.rollNumber < b.rollNumber;
    });
    calculateCGPA(newStudent.rollNumber);
    cout << "Student record added successfully!\n";
}

void StudentRecordSystem::calculateCGPA(int rollNumber) {
    int index = binarySearch(rollNumber);
    if (index != -1) {
        Student & s = studentRecords[index];
        float totalGPA = 0;
        int totalSubjects = 0;

        for (const auto & semMarks: s.semesterMarks) {
            float semesterTotal = 0;
            for (float mark: semMarks) {
                semesterTotal += mark;
            }
            totalGPA += (semesterTotal / semMarks.size()) / 10;
            totalSubjects += semMarks.size();
        }
        s.cgpa = totalGPA / 8;
    }
}

void StudentRecordSystem::findSemesterToppers() {
    vector < map < string, pair < int, float >>> branchToppers(8); 
    vector < pair < int, float >> collegeToppers(8, {
        0,
        0.0
    });

    for (const auto & student: studentRecords) {
        for (int sem = 0; sem < 8; sem++) {
            float semesterTotal = accumulate(student.semesterMarks[sem].begin(), student.semesterMarks[sem].end(), 0.0);
            float avgMarks = semesterTotal / student.semesterMarks[sem].size();

            if (branchToppers[sem][student.branch].second < avgMarks) {
                branchToppers[sem][student.branch] = {
                    student.rollNumber,
                    avgMarks
                };
            }
            if (collegeToppers[sem].second < avgMarks) {
                collegeToppers[sem] = {
                    student.rollNumber,
                    avgMarks
                };
            }
        }
    }

    for (int sem = 0; sem < 8; sem++) {
        cout << "\nSemester " << sem + 1 << " Toppers:";
        for (const auto & [branch, topper]: branchToppers[sem]) {
            cout << "\nBranch: " << branch << " - Roll Number: " << topper.first << " - Avg Marks: " << topper.second;
        }
        cout << "\nCollege Topper: Roll Number: " << collegeToppers[sem].first << " - Avg Marks: " << collegeToppers[sem].second << "\n";
    }
}

void StudentRecordSystem::displayAllStudents() {
    for (const auto & student: studentRecords) {
        cout << "\nRoll Number: " << student.rollNumber;
        cout << "\nFull Name: " << student.fullName;
        cout << "\nStudent ID: " << student.studentID;
        cout << "\nBranch: " << student.branch;
        cout << "\nCGPA: " << student.cgpa << "\n";
    }
}

void StudentRecordSystem::displayStudent(int rollNumber) {
    int index = binarySearch(rollNumber);
    if (index != -1) {
        Student s = studentRecords[index];
        cout << "\nFull Name: " << s.fullName;
        cout << "\nStudent ID: " << s.studentID;
        cout << "\nBranch: " << s.branch;
        cout << "\nCGPA: " << s.cgpa;
    } else {
        cout << "Student not found!\n";
    }
}

void StudentRecordSystem::deleteStudent(int rollNumber) {
    int index = binarySearch(rollNumber);
    if (index != -1) {
        studentRecords.erase(studentRecords.begin() + index);
        cout << "Student record deleted successfully!\n";
    } else {
        cout << "Student not found!\n";
    }
}

int main() {
    StudentRecordSystem system;
    int choice, rollNumber;

    while (true) {
        cout << "\n1. Add Student\n2. Display All Students\n3. Display Student\n4. Delete Student\n5. Find Semester Toppers\n6. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addStudent();
                break;
            case 2:
                system.displayAllStudents();
                break;
            case 3:
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                system.displayStudent(rollNumber);
                break;
            case 4:
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                system.deleteStudent(rollNumber);
                break;
            case 5:
                system.findSemesterToppers();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
