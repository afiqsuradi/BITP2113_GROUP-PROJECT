#ifndef PRODUCTIVE_EMPLOYEE_PER_DEPARTMENT_MODEL_H
#define PRODUCTIVE_EMPLOYEE_PER_DEPARTMENT_MODEL_H

#include <string>
#include "linked_list.h"
#include "simple_employee_list.h"

struct ProductiveEmployeePerDepartmentModel {
    std::string employeeDepartment;
    SimpleEmployeeList *employeeList;

	ProductiveEmployeePerDepartmentModel() : employeeDepartment(""), employeeList(nullptr){}
    ProductiveEmployeePerDepartmentModel(const std::string &name, SimpleEmployeeList *list) : employeeDepartment(name), employeeList(list){}
};


#endif