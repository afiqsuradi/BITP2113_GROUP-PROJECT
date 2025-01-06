#include "employee_analytics.h"
#include <iomanip>
#include "productive_employee_per_department_list.h"
#include <numeric>
#include <fstream>
#include <algorithm>

void EmployeeAnalytics::calculateAverageSalaryPerDepartment(const EmployeeList &employees) {
    LinkedList<DepartmentCountModel> departmentCounts;

    Node<EmployeeModel> *current = employees.getHead();
    while (current != nullptr) {
        const EmployeeModel &employee = current->data;
        double totalSalary = 0;
        int salaryCount = 0;

        //calculate sum salary per employee
        if (employee.salary_payments != nullptr) {
            Node<SalaryModel> *currentSalary = employee.salary_payments->getHead();
            while (currentSalary != nullptr) {
                totalSalary += currentSalary->data.grossPay;
                salaryCount++;
                currentSalary = currentSalary->next;
            }
        }

        if (salaryCount > 0) {
            DepartmentCountModel departmentData(employee.department);
            if (!findDepartmentCount(departmentCounts, employee.department, departmentData)) {
                departmentData.count = 1;
                departmentData.totalSalary = totalSalary / salaryCount;
                insertDepartmentCount(departmentCounts, departmentData);
            } else {
                updateDepartmentCount(departmentCounts, employee.department, totalSalary / salaryCount);
            }
        }
        current = current->next;
    }

    std::cout << "\n--- Average Salary Per Department ---" << std::endl;
    printDepartmentCount(departmentCounts);
    std::cout << "------------------------------------\n" << std::endl;
}

void EmployeeAnalytics::calculatePerformanceBasedBonus(const EmployeeList &employees, double bonusPercentage,
                                                       const std::string &filePath) {
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return; // Exit if file couldn't be opened
    }

    outputFile << "--- Performance-Based Bonus Calculation ---" << std::endl;
    Node<EmployeeModel> *current = employees.getHead();
    while (current != nullptr) {
        const EmployeeModel &employee = current->data;
        double avgHoursWorked = calculateAverageHoursWorked(employee.salary_payments);
        if (avgHoursWorked > 0) {
            double bonusAmount = 0;
            double totalSalary = 0;
            int count = 0;
            if (employee.salary_payments != nullptr) {
                Node<SalaryModel> *currentSalary = employee.salary_payments->getHead();
                while (currentSalary != nullptr) {
                    totalSalary += currentSalary->data.grossPay;
                    count++;
                    currentSalary = currentSalary->next;
                }
            }
            if (count > 0)
                bonusAmount = (totalSalary / count) * (bonusPercentage / 100.0);

            outputFile << "Employee ID: " << employee.id
                    << ", Name: " << employee.name
                    << ", Department: " << employee.department
                    << ", Average Hours Worked: " << std::fixed << std::setprecision(2) << avgHoursWorked
                    << ", Bonus: RM" << std::fixed << std::setprecision(2) << bonusAmount << std::endl;
        } else {
            outputFile << "Employee ID: " << employee.id
                    << ", Name: " << employee.name
                    << ", Department: " << employee.department
                    << ", No salary data recorded, no bonus" << std::endl;
        }
        current = current->next;
    }
    outputFile << "------------------------------------" << std::endl;
    outputFile.close();
    std::cout << "Bonus data written to file: " << filePath << std::endl;
}


void EmployeeAnalytics::findMostProductiveEmployeesPerDepartment(const EmployeeList &employees, int topN) {
    ProductiveEmployeePerDepartmentList departmentProductivityList;

    Node<EmployeeModel> *currentEmployee = employees.getHead();
    while (currentEmployee != nullptr) {
        const EmployeeModel &employee = currentEmployee->data;
        double avgHours = calculateAverageHoursWorked(employee.salary_payments);
        SimpleEmployeeModel simpleEmployee(employee.id, employee.name, avgHours);

        Node<ProductiveEmployeePerDepartmentModel> *currentDepartment = departmentProductivityList.getHead();
        bool departmentFound = false;
        while (currentDepartment != nullptr) {
            if (currentDepartment->data.employeeDepartment == employee.department) {
                departmentFound = true;
                currentDepartment->data.employeeList->pushBack(simpleEmployee);
                break;
            }
            currentDepartment = currentDepartment->next;
        }

        if (!departmentFound) {
            SimpleEmployeeList *newEmployeeList = new SimpleEmployeeList();
            newEmployeeList->pushBack(simpleEmployee);
            ProductiveEmployeePerDepartmentModel newDepartment(employee.department, newEmployeeList);
            departmentProductivityList.pushBack(newDepartment);
        }
        currentEmployee = currentEmployee->next;
    }
    Node<ProductiveEmployeePerDepartmentModel> *currentDepartment = departmentProductivityList.getHead();
    while (currentDepartment != nullptr) {
        SimpleEmployeeList *employeeList = currentDepartment->data.employeeList;
        Node<SimpleEmployeeModel> *sortHead = employeeList->getHead();
        for (Node<SimpleEmployeeModel> *i = sortHead; i != nullptr; i = i->next) {
            for (Node<SimpleEmployeeModel> *j = i->next; j != nullptr; j = j->next) {
                if (j->data < i->data) {
                    std::swap(i->data, j->data);
                }
            }
        }

        std::cout << "#############################\n";
        std::cout << currentDepartment->data.employeeDepartment << std::endl;
        std::cout << "#############################\n";
        Node<SimpleEmployeeModel> *currentSimpleEmployee = employeeList->getHead();
        for (int i = 0; i < std::min(static_cast<int>(employeeList->getSize()), topN); i++) {
            if (currentSimpleEmployee != nullptr) {
                std::cout << "Employee Name :" << currentSimpleEmployee->data.name << ",\t Average Working Hour:" <<
                        std::fixed << std::setprecision(2) <<
                        currentSimpleEmployee->data.averageWorkingHour << std::endl;
                currentSimpleEmployee = currentSimpleEmployee->next;
            }
            if ((i + 1) >= (std::min(static_cast<int>(employeeList->getSize()), topN))) std::cout << "\n\n";
        }
        currentDepartment = currentDepartment->next;
    }
}

double EmployeeAnalytics::calculateAverageHoursWorked(const SalaryList *salaries) {
    if (salaries == nullptr || salaries->isEmpty()) {
        return 0.0;
    }

    double totalHours = 0.0;
    int count = 0;
    Node<SalaryModel> *current = salaries->getHead();
    while (current != nullptr) {
        totalHours += current->data.hoursWorked;
        count++;
        current = current->next;
    }
    return count > 0 ? totalHours / count : 0.0;
}

bool EmployeeAnalytics::findDepartmentCount(const LinkedList<DepartmentCountModel> &list, const std::string &department,
                                            DepartmentCountModel &result) {
    Node<DepartmentCountModel> *current = list.getHead();
    while (current != nullptr) {
        if (current->data.department == department) {
            result = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}

void EmployeeAnalytics::insertDepartmentCount(LinkedList<DepartmentCountModel> &list,
                                              const DepartmentCountModel &data) {
    list.pushBack(data);
}

void EmployeeAnalytics::updateDepartmentCount(LinkedList<DepartmentCountModel> &list, const std::string &department,
                                              double totalSalary) {
    Node<DepartmentCountModel> *current = list.getHead();
    while (current != nullptr) {
        if (current->data.department == department) {
            current->data.count++;
            current->data.totalSalary += totalSalary;
            break;
        }
        current = current->next;
    }
}

void EmployeeAnalytics::printDepartmentCount(const LinkedList<DepartmentCountModel> &list) {
    Node<DepartmentCountModel> *current = list.getHead();
    while (current != nullptr) {
        double averageSalary = current->data.totalSalary / current->data.count;
        std::cout << "Department: " << current->data.department
                << ", Average Salary: RM" << std::fixed << std::setprecision(2) << averageSalary << std::endl;
        current = current->next;
    }
}
