#include <iostream>
#include <vector>

using namespace std;

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<double> grades(numCourses);
    vector<int> credits(numCourses);
    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; ++i) {
        cout << "Enter grade for course " << (i + 1) << " (e.g., 4.0 for A, 3.0 for B, etc.): ";
        cin >> grades[i];
        cout << "Enter number of credits for course " << (i + 1) << ": ";
        cin >> credits[i];

        totalGradePoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }

    if (totalCredits == 0) {
        cout << "Error: Total credits cannot be zero." << endl;
        return 1;
    }

    double gpa = totalGradePoints / totalCredits;

    cout << "\nCGPA Calculation:\n";
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Total Credits: " << totalCredits << endl;
    cout << "GPA for the semester: " << gpa << endl;

    return 0;
}

