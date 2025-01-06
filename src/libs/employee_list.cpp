#include "employee_list.h"
#include "employee_model.h"

void EmployeeList::print() const {
    Node<EmployeeModel> *current = head;
    while (current) {
        const EmployeeModel &emp = current->data;
        std::cout << "ID: " << emp.id << "\n"
                << "Name: " << emp.name << "\n"
                << "Department: " << emp.department << "\n"
                << "Position: " << emp.position << "\n"
                << "Salary Payments:\n";
        // emp.salary_payments->print();
        if (current->next != nullptr) {
            current = current->next;
        } else {
            break;
        }
    }
}

void EmployeeList::printEmployee(Node<EmployeeModel> *employee) {
    std::cout << "ID: " << employee->data.id << "\n"
            << "Name: " << employee->data.name << "\n"
            << "Department: " << employee->data.department << "\n"
            << "Position: " << employee->data.position << "\n";
}

void EmployeeList::printEmployees(int limit) const {
    Node<EmployeeModel> *current = head;
    while (current != nullptr && limit > 0) {
        printEmployee(current);
        current = current->next;
        --limit;
    }
}
