# StudentRecordManagement

## Overview
The **Student Record System** is a C++ program that manages student records, including their details, semester-wise marks, and CGPA calculations. It also identifies semester-wise toppers for each branch and the entire college.

## Features
- Add new students with their semester-wise marks.
- Display all student records.
- Search and display student details using their roll number.
- Delete student records.
- Calculate and store CGPA for students.
- Find semester-wise toppers for each branch and the entire college.

## Installation
To run the program, follow these steps:
1. Ensure you have a C++ compiler (such as g++).
2. Clone or download this repository.
3. Compile the program using:
   ```sh
   g++ student_record_toppers.cpp -o student_record_system
   ```
4. Run the compiled program:
   ```sh
   ./student_record_system
   ```

## Usage
Upon running the program, you will be presented with a menu:
```
1. Add Student
2. Display All Students
3. Display Student
4. Delete Student
5. Find Semester Toppers
6. Exit
Enter choice:
```

### Adding a Student
- Enter the student's full name, ID, roll number, and branch.
- Input marks for each semester (8 semesters, each with 8-12 subjects).
- The system calculates the CGPA automatically.

### Displaying Student Records
- Option 2 displays all students.
- Option 3 prompts for a roll number and shows that student's details.

### Deleting a Student
- Enter the roll number to delete the student record.

### Finding Semester Toppers
- Displays the top scorer in each semester for every branch and the overall college topper.


