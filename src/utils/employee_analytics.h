#ifndef EMPLOYEE_ANALYTICS_H
#define EMPLOYEE_ANALYTICS_H

#include <iostream>
#include <string>
#include "employee_list.h"
#include "linked_list.h"
#include "department_count_model.h"

class EmployeeAnalytics {
public:
    static void calculateAverageSalaryPerDepartment(const EmployeeList &employees);

    static void calculatePerformanceBasedBonus(const EmployeeList &employees, double bonusPercentage,
                                               const std::string &filePath);

    static void findMostProductiveEmployeesPerDepartment(const EmployeeList &employees, int topN);

private:
    static double calculateAverageHoursWorked(const SalaryList *salaries);

    static bool findDepartmentCount(const LinkedList<DepartmentCountModel> &list, const std::string &department,
                                    DepartmentCountModel &result);

    static void insertDepartmentCount(LinkedList<DepartmentCountModel> &list, const DepartmentCountModel &data);

    static void updateDepartmentCount(LinkedList<DepartmentCountModel> &list, const std::string &department,
                                      double totalSalary);

    static void printDepartmentCount(const LinkedList<DepartmentCountModel> &list);
};


#endif
