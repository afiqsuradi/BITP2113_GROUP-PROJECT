#ifndef DEPARTMENT_COUNT_MODEL_H
#define DEPARTMENT_COUNT_MODEL_H

#include <string>

struct DepartmentCountModel {
    std::string department;
    int count;
    double totalSalary;

    DepartmentCountModel() : count(0), totalSalary(0.0) {
    }

    DepartmentCountModel(const std::string &dept) : department(dept), count(0), totalSalary(0.0) {
    }

    bool operator==(const DepartmentCountModel &other) const {
        return department == other.department;
    }
};
#endif
