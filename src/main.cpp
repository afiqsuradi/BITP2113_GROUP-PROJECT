#include <iostream>
#include "linked_list.h"
#include "libs/employee_list.h"
#include "utils/sorter.h"
#include "utils/searcher.h"
#include "utils/employee_analytics.h"
#include "controllers/employee_controller.h"
#include "controllers/ui_controller.cpp"
#include <string>
#include <cstdlib>

int main() {
    Sorter sorter;
    std::string bonusGenPath = "employee_annual_bonus.txt";
    EmployeeController employeeController("employee_data_shuffled.json");
    int exitProgram = 0, operationChoice = 0, searchId = 0;
    long long duration = 0;
    UiController uiController(&exitProgram, &operationChoice);
    size_t employeeSize = employeeController.getEmployees()->getSize();
    while (!exitProgram) {
        operationChoice = 0;
        searchId = 0;
        duration = 0;

        uiController.displayMenu(&employeeSize);
        switch (static_cast<OperationEnum>(operationChoice)) {
            case SORT_TECHNIQUE_ONE:
                uiController.clearScreen();
                Sorter::insertionSort(employeeController.getEmployees());

                employeeController.getEmployees()->printEmployees(100);
                system("pause");
                break;
            case SORT_TECHNIQUE_ONE_IMPROVED:
                uiController.clearScreen();
                Sorter::insertionSortImproved(employeeController.getEmployees());

                employeeController.getEmployees()->printEmployees(100);
                system("pause");
                break;
            case SORT_TECHNIQUE_TWO:
                uiController.clearScreen();
                Sorter::mergeSort(employeeController.getEmployees());

                employeeController.getEmployees()->printEmployees(100);
                system("pause");
                break;
            case SORT_TECHNIQUE_TWO_IMPROVED:
                uiController.clearScreen();
                Sorter::mergeSortImproved(employeeController.getEmployees());
                employeeController.getEmployees()->printEmployees(100);
                system("pause");
                break;
            case SORT_COMPARE:
                uiController.clearScreen();
                UiController::displayHeader("Technique 1 (Insertion Sort)");
                Sorter::insertionSort(employeeController.getEmployees());
                std::cout << "\n\n\n";
                employeeController.loadFromJson();
                UiController::displayHeader("Technique 2 (Merge Sort)");
                Sorter::mergeSort(employeeController.getEmployees());
                system("pause");
                break;
            case SORT_COMPARE_IMPROVED:
                uiController.clearScreen();
                UiController::displayHeader("Technique 1 (Insertion Sort)");
                Sorter::insertionSortImproved(employeeController.getEmployees());
                std::cout << "\n\n\n";
                employeeController.loadFromJson();
                UiController::displayHeader("Technique 2 (Merge Sort)");
                Sorter::mergeSortImproved(employeeController.getEmployees());
                system("pause");
                break;
            case SEARCH_TECHNIQUE_ONE:

                uiController.clearScreen();
                UiController::displayHeader("Technique 1 (Linear Search)");
                std::cout << "Please enter employee id you want to search: ";
                std::cin >> searchId;
                Searcher::linearSearch(employeeController.getEmployees(), searchId);
                system("pause");
                break;
            case SEARCH_TECHNIQUE_TWO:

                uiController.clearScreen();
                UiController::displayHeader("Technique 2 (binary Search)");
                std::cout << "Please enter employee id you want to search: ";
                std::cin >> searchId;
                Searcher::binarySearch(employeeController.getEmployees(), searchId);
                system("pause");
                break;
            case SEARCH_TECHNIQUE_ONE_IMPROVED:
                uiController.clearScreen();
                UiController::displayHeader("Technique 1 (Linear Search)");
                std::cout << "Please enter employee id you want to search: ";
                std::cin >> searchId;
                Searcher::linearSearchImproved(employeeController.getEmployees(), searchId);
                system("pause");
                break;
            case SEARCH_TECHNIQUE_TWO_IMPROVED:
                uiController.clearScreen();
                UiController::displayHeader("Technique 2 (binary Search)");
                std::cout << "Please enter employee id you want to search: ";
                std::cin >> searchId;
                Searcher::binarySearchImproved(employeeController.getEmployees(), searchId);
                system("pause");
                break;
            case SEARCH_COMPARE:
                uiController.clearScreen();
                std::cout << "Please enter employee id you want to search: ";
                std::cin >> searchId;
                UiController::displayHeader("Technique 1 (Linear Search)");
                Searcher::linearSearch(employeeController.getEmployees(), searchId);
                std::cout << "\n\n\n";
                UiController::displayHeader("Technique 2 (Binary Search)");
                Searcher::binarySearch(employeeController.getEmployees(), searchId);
                system("pause");
                break;
            case SEARCH_COMPARE_IMPROVED:
                uiController.clearScreen();
                std::cout << "Please enter employee id you want to search: ";
                std::cin >> searchId;
                UiController::displayHeader("Improved Technique 1 (Linear Search)");
                Searcher::linearSearchImproved(employeeController.getEmployees(), searchId);
                std::cout << "\n\n\n";
                UiController::displayHeader("Improved Technique 2 (Binary Search)");
                Searcher::binarySearchImproved(employeeController.getEmployees(), searchId);
                system("pause");
                break;
            case ADDITIONAL_ONE:
                uiController.clearScreen();
                EmployeeAnalytics::calculateAverageSalaryPerDepartment(*employeeController.getEmployees());
                system("pause");
                break;
            case ADDITIONAL_TWO:
                uiController.clearScreen();
                EmployeeAnalytics::findMostProductiveEmployeesPerDepartment(*employeeController.getEmployees(), 10);
                system("pause");
                break;
            case ADDITIONAL_THREE:
                uiController.clearScreen();
                EmployeeAnalytics::calculatePerformanceBasedBonus(*employeeController.getEmployees(), 0.1,
                                                                  bonusGenPath);
                system("pause");
                break;
            case DATA_RELOAD:
                uiController.clearScreen();
                std::cout << "Reloading data..." << std::endl;
                employeeController.loadFromJson();
                break;
            default: break;
        }
    }
    return 0;
}
