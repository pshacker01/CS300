#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;           // Unique identifier for the course
    string courseTitle;            // Title of the course
    vector<string> prerequisites;  // List of prerequisites
};

// Function to load courses from a CSV file
vector<Course> loadCourses(const string& fileName) {
    vector<Course> courses;
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;

        // Parse courseNumber and courseTitle
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        // Trim spaces
        courseNumber.erase(0, courseNumber.find_first_not_of(" \t"));
        courseNumber.erase(courseNumber.find_last_not_of(" \t") + 1);
        courseTitle.erase(0, courseTitle.find_first_not_of(" \t"));
        courseTitle.erase(courseTitle.find_last_not_of(" \t") + 1);

        if (courseNumber.empty() || courseTitle.empty()) {
            cout << "Error: Invalid format in line: " << line << endl;
            continue;
        }

        // Parse prerequisites
        vector<string> prerequisites;
        while (getline(ss, prereq, ',')) {
            prereq.erase(0, prereq.find_first_not_of(" \t"));
            prereq.erase(prereq.find_last_not_of(" \t") + 1);
            if (!prereq.empty()) {
                prerequisites.push_back(prereq);
            }
        }

        // Create Course object and add to vector
        courses.emplace_back(Course{ courseNumber, courseTitle, prerequisites });
    }

    file.close();
    return courses;
}

// Function to display all courses in alphanumeric order
void displayAllCourses(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;

    // Sort courses by courseNumber
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    // Print sorted courses
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ": " << course.courseTitle << endl;
    }
}

// Function to display information about a specific course
void displayCourse(const vector<Course>& courses, const string& courseNumber) {
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << course.courseNumber << ": " << course.courseTitle << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
            else {
                cout << "Prerequisites: None" << endl;
            }
            return;
        }
    }
    cout << "Error: Course not found." << endl;
}

// Main program
int main() {
    vector<Course> courses;
    string fileName;
    int choice = 0;

    while (choice != 9) {
        // Display menu
        cout << "\nMenu:" << endl;
        cout << "1. Load Courses" << endl;
        cout << "2. Display All Courses" << endl;
        cout << "3. Display Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
        case 1:
            // Load courses
            cout << "Enter file name (e.g., C:\\Users\\User\\Downloads\\CS 300 ABCU_Advising_Program_Input.csv): ";
            getline(cin, fileName);
            courses = loadCourses(fileName);
            if (!courses.empty()) {
                cout << courses.size() << " courses loaded successfully!" << endl;
            }
            else {
                cout << "No courses loaded. Please check the file path or format." << endl;
            }
            break;

        case 2:
            // Display all courses
            if (courses.empty()) {
                cout << "Error: No courses loaded. Please load courses first." << endl;
            }
            else {
                displayAllCourses(courses);
            }
            break;

        case 3:
            // Display course information
            if (courses.empty()) {
                cout << "Error: No courses loaded. Please load courses first." << endl;
            }
            else {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;
                displayCourse(courses, courseNumber);
            }
            break;

        case 9:
            cout << "Goodbye! Thank you for using the Course Planner." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
