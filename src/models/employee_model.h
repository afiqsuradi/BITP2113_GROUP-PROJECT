#ifndef EMPLOYEE_MODEL_H
#define EMPLOYEE_MODEL_H

#include <string>
#include "salary_list.h"

struct EmployeeModel
{
    int id;
    std::string name;
    std::string department;
    std::string position;
    SalaryList *salary_payments;

    EmployeeModel();
    EmployeeModel(const EmployeeModel &other);
    EmployeeModel(int id, const std::string &name, const std::string &department,
                  const std::string &position, SalaryList *salary_payments = nullptr);
    EmployeeModel &operator=(const EmployeeModel &other);
    ~EmployeeModel();
};

#endif