#ifndef EMPLOYEE_LIST_H
#define EMPLOYEE_LIST_H

#include "linked_list.h"
#include "employee_model.h"

class EmployeeList : public LinkedList<EmployeeModel> {
public:
    void print() const;

    void printEmployees(int limit) const;

    static void printEmployee(Node<EmployeeModel> *employee);
};

#endif
