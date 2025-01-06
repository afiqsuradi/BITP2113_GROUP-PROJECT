#include "employee_model.h"

EmployeeModel::EmployeeModel()
    : id(0), name(""), department(""), position(""), salary_payments(nullptr) {}

EmployeeModel::EmployeeModel(const EmployeeModel &other)
    : id(other.id), name(other.name), department(other.department),
      position(other.position), salary_payments(nullptr)
{
    if (other.salary_payments)
    {
        salary_payments = new SalaryList(*other.salary_payments);
    }
}

EmployeeModel::EmployeeModel(int id, const std::string &name,
                             const std::string &department,
                             const std::string &position,
                             SalaryList *salary_payments)
    : id(id), name(name), department(department),
      position(position), salary_payments(salary_payments) {}

EmployeeModel &EmployeeModel::operator=(const EmployeeModel &other)
{
    if (this != &other)
    {
        id = other.id;
        name = other.name;
        department = other.department;
        position = other.position;

        delete salary_payments;
        salary_payments = other.salary_payments ? new SalaryList(*other.salary_payments) : nullptr;
    }
    return *this;
}

EmployeeModel::~EmployeeModel()
{
    delete salary_payments;
}