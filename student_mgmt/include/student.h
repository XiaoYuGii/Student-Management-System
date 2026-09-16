#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student {
    int         id;
    std::string name;
    std::string gender;
    int         age;
    float       gpa;
    std::string major;

    Student()
        : id(0), name(""), gender(""), age(0), gpa(0.0f), major("") {}

    Student(int id, const std::string& name, const std::string& gender,
            int age, float gpa, const std::string& major)
        : id(id), name(name), gender(gender),
          age(age), gpa(gpa), major(major) {}
};

#endif
