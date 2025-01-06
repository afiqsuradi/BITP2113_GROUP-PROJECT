#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H

#include <string>
#include "json.hpp"
#include "employee_list.h"

class EmployeeController {
private:
    EmployeeList *employees;
    std::string filePath;

public:
    EmployeeController(const std::string &filepath);

    ~EmployeeController();

    EmployeeList *getEmployees() const;

    void printAll() const;

    bool loadFromJson();

    nlohmann::json employeeToJson() const;

    void saveToJson(const std::string &filepath) const;
};

#endif
