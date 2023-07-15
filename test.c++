#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int marks[3];  // Array to store marks for each subject
    int totalMarks;

    // Function to calculate total marks
    void calculateTotalMarks() {
        totalMarks = 0;
        for (int i = 0; i < 3; i++) {
            totalMarks += marks[i];
        }
    }
};

// Function to compare two students based on total marks
bool compareStudents(const Student& s1, const Student& s2) {
    return s1.totalMarks > s2.totalMarks;
}

// Function to print student details
void printStudentDetails(const Student& student, int schoolRank, int classRank) {
    std::cout << "Name: " << student.name << std::endl;
    std::cout << "Total Marks: " << student.totalMarks << std::endl;
    std::cout << "School Rank: " << schoolRank << std::endl;
    std::cout << "Class Rank: " << classRank << std::endl;
    std::cout << std::endl;
}

// Function to write student details to a file
void writeStudentDetailsToFile(const Student& student, int schoolRank, int classRank) {
    std::ofstream outputFile("rankings.txt", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << "Name: " << student.name << std::endl;
        outputFile << "Total Marks: " << student.totalMarks << std::endl;
        outputFile << "School Rank: " << schoolRank << std::endl;
        outputFile << "Class Rank: " << classRank << std::endl;
        outputFile << std::endl;
        outputFile.close();
    } else {
        std::cerr << "Unable to open the file." << std::endl;
    }
}

int main() {
    const int bioStreamClasses = 3;
    const int mathStreamClasses = 5;
    const int studentsPerClass = 40;

    std::vector<Student> bioStreamStudents(bioStreamClasses * studentsPerClass);
    std::vector<Student> mathStreamStudents(mathStreamClasses * studentsPerClass);

    // Read marks for Bio stream students
    std::ifstream bioStreamFile("bio_stream_marks.txt");
    if (bioStreamFile.is_open()) {
        for (int i = 0; i < bioStreamStudents.size(); i++) {
            bioStreamFile >> bioStreamStudents[i].name;
            for (int j = 0; j < 3; j++) {
                bioStreamFile >> bioStreamStudents[i].marks[j];
            }
            bioStreamStudents[i].calculateTotalMarks();
        }
        bioStreamFile.close();
    } else {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }

    // Read marks for Math stream students
    std::ifstream mathStreamFile("math_stream_marks.txt");
    if (mathStreamFile.is_open()) {
        for (int i = 0; i < mathStreamStudents.size(); i++) {
            mathStreamFile >> mathStreamStudents[i].name;
            for (int j = 0; j < 3; j++) {
                mathStreamFile >> mathStreamStudents[i].marks[j];
            }
            mathStreamStudents[i].calculateTotalMarks();
        }
        mathStreamFile.close();
    } else {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }

    // Sort the students in descending order based on total marks
    std::sort(bioStreamStudents.begin(), bioStreamStudents.end(), compareStudents);
    std::sort(mathStreamStudents.begin(), mathStreamStudents.end(), compareStudents);

    // Calculate and print school and class ranks for Bio stream students
    for (int i = 0; i < bioStreamStudents.size(); i++) {
        int schoolRank = i + 1;
        int classRank = (i % studentsPerClass) + 1;
        printStudentDetails(bioStreamStudents[i], schoolRank, classRank);
        writeStudentDetailsToFile(bioStreamStudents[i], schoolRank, classRank);
    }

    // Calculate and print school and class ranks for Math stream students
    for (int i = 0; i < mathStreamStudents.size(); i++) {
        int schoolRank = i + 1;
        int classRank = (i % studentsPerClass) + 1;
        printStudentDetails(mathStreamStudents[i], schoolRank, classRank);
        writeStudentDetailsToFile(mathStreamStudents[i], schoolRank, classRank);
    }

    return 0;
}
