//
// Created by Afiq on 6/1/2025.
//

#ifndef SIMPLE_EMPLOYEE_MODEL_H
#define SIMPLE_EMPLOYEE_MODEL_H

#include <string>

struct SimpleEmployeeModel {
    int id;
    std::string name;
    double averageWorkingHour;

    SimpleEmployeeModel() : id(0), averageWorkingHour(0.0) {
    }

    SimpleEmployeeModel(int id, const std::string &name, double averageWorkingHour) : id(id), name(name),
        averageWorkingHour(averageWorkingHour) {
    }

    bool operator<(const SimpleEmployeeModel &other) const {
        return averageWorkingHour > other.averageWorkingHour;
    }

    bool operator>(const SimpleEmployeeModel &other) const {
        return averageWorkingHour < other.averageWorkingHour;
    }
};

#endif //SIMPLE_EMPLOYEE_MODEL_H
