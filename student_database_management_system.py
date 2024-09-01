import re
import datetime
import time

class Scheme:
    def __init__(self, subject_code, subject_title, max_marks_sessional, max_marks_theory):
        self.subject_code = subject_code
        self.subject_title = subject_title
        self.max_marks_sessional = max_marks_sessional
        self.max_marks_theory = max_marks_theory

class Student:
    def __init__(self, enrollment_number, name, father_name, dob, semester, admission_year, marks_sessional, marks_theory):
        self.enrollment_number = enrollment_number
        self.name = name
        self.father_name = father_name
        self.dob = dob
        self.semester = semester
        self.admission_year = admission_year
        self.marks_sessional = marks_sessional
        self.marks_theory = marks_theory

# Global lists to store student and scheme records
students = []
schemes = []

# Function to log actions
def log_action(action):
    with open("actions_log.txt", "a") as log_file:
        log_file.write(action + "\n")

# Function to validate Date of Birth format
def is_valid_dob(dob):
    try:
        day, month, year = map(int, dob.split('-'))
        datetime.datetime(year, month, day)
        return 1900 <= year <= datetime.datetime.now().year
    except ValueError:
        return False

# Function to add a scheme to the database
def add_scheme():
    subject_code = input("Enter Subject Code: ")
    subject_title = input("Enter Subject Title: ")
    max_marks_sessional = int(input("Enter Maximum Marks for Sessional: "))
    max_marks_theory = int(input("Enter Maximum Marks for Theory: "))
    schemes.append(Scheme(subject_code, subject_title, max_marks_sessional, max_marks_theory))
    print("Scheme added successfully.")
    log_action(f"Scheme added: {subject_code}")

# Function to delete a scheme from the database
def delete_scheme(subject_code):
    global schemes
    schemes = [scheme for scheme in schemes if scheme.subject_code != subject_code]
    print("Scheme deleted successfully.")
    log_action(f"Scheme deleted: {subject_code}")

# Function to update a scheme in the database
def update_scheme(subject_code):
    for scheme in schemes:
        if scheme.subject_code == subject_code:
            scheme.subject_title = input("Enter new Subject Title: ")
            scheme.max_marks_sessional = int(input("Enter new Maximum Marks for Sessional: "))
            scheme.max_marks_theory = int(input("Enter new Maximum Marks for Theory: "))
            print("Scheme updated successfully.")
            log_action(f"Scheme updated: {subject_code}")
            return
    print("Scheme not found.")

# Function to add a student to the records
def add_student():
    enrollment_number = int(input("Enter Enrollment Number: "))
    name = input("Enter Student Name: ")
    father_name = input("Enter Father's Name: ")
    while True:
        dob = input("Enter Date of Birth (DD-MM-YYYY): ")
        if is_valid_dob(dob):
            break
        print("Invalid DOB format. Please enter in DD-MM-YYYY format.")
    semester = int(input("Enter Semester: "))
    admission_year = int(input("Enter Year of Admission: "))
    marks_sessional = int(input("Enter Marks Awarded in Sessional: "))
    marks_theory = int(input("Enter Marks Awarded in Theory: "))
    students.append(Student(enrollment_number, name, father_name, dob, semester, admission_year, marks_sessional, marks_theory))
    print("Student added successfully.")
    log_action(f"Student added: Enrollment Number {enrollment_number}")

# Function to measure the performance of certain operations
def measure_performance():
    start_time = time.time()
    add_student()  # Example: measuring time for addition
    end_time = time.time()
    print(f"Time taken for addition: {end_time - start_time:.2f} seconds")

# Function to print the report card of a student
def print_report_card(enrollment_number):
    for student in students:
        if student.enrollment_number == enrollment_number:
            print(f"Report Card for {student.name} ({student.enrollment_number})")
            print(f"Semester: {student.semester}, Year of Admission: {student.admission_year}")
            print(f"Marks Awarded - Sessional: {student.marks_sessional}, Theory: {student.marks_theory}")
            return
    print("Student not found.")

# Function to display all student records
def display_all_records():
    if not students:
        print("No student records available.")
        return
    for student in students:
        print(f"Enrollment Number: {student.enrollment_number}")
        print(f"Name: {student.name}")
        print(f"Father's Name: {student.father_name}")
        print(f"Date of Birth: {student.dob}")
        print(f"Semester: {student.semester}")
        print(f"Admission Year: {student.admission_year}")
        print(f"Marks - Sessional: {student.marks_sessional}, Theory: {student.marks_theory}")
        print("------------------------------")

# Function to sort students by a specified field
def sort_students_by_field(field):
    if field not in ["name", "enrollment_number"]:
        print("Invalid field. Available fields: name, enrollment_number")
        return

    if field == "name":
        students.sort(key=lambda x: x.name)
    elif field == "enrollment_number":
        students.sort(key=lambda x: x.enrollment_number)
    
    print(f"Students sorted by {field}.")

# Main function to display menu and handle user choices
def main():
    while True:
        print("\n1. Add Scheme")
        print("2. Delete Scheme")
        print("3. Update Scheme")
        print("4. Add Student")
        print("5. Print Report Card")
        print("6. Measure Performance")
        print("7. Sort Students")
        print("8. Display All Records")
        print("0. Exit")
        choice = int(input("Enter your choice: "))
        if choice == 1:
            add_scheme()
        elif choice == 2:
            subject_code = input("Enter Subject Code to delete: ")
            delete_scheme(subject_code)
        elif choice == 3:
            subject_code = input("Enter Subject Code to update: ")
            update_scheme(subject_code)
        elif choice == 4:
            add_student()
        elif choice == 5:
            enrollment_number = int(input("Enter Enrollment Number to print report: "))
            print_report_card(enrollment_number)
        elif choice == 6:
            measure_performance()
        elif choice == 7:
            field = input("Enter field to sort by (name/enrollment_number): ")
            sort_students_by_field(field)
        elif choice == 8:
            display_all_records()
        elif choice == 0:
            print("Exiting program.")
            log_action("Program exited.")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()