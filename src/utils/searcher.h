#ifndef SEARCHER_H
#define SEARCHER_H

#include "linked_list.h"
#include <chrono>
#include <string>
#include <array>
#include "employee_list.h"
#include "employee_model.h"

class Searcher {
public:
    static void displayResult(Node<EmployeeModel> *result, int &targetId, std::string searchType);

    static void displayTime(std::chrono::time_point<std::chrono::system_clock> startCalculation,
                            std::chrono::time_point<std::chrono::system_clock> endCalculation);

    static void linearSearch(EmployeeList *employees, std::array<int, 100> &targetIds);

    static void linearSearchImproved(EmployeeList *employees, std::array<int, 100> &targetIds);

    static void binarySearch(EmployeeList *employees, std::array<int, 100> &targetIds);

    static void binarySearchImproved(EmployeeList *employees, std::array<int, 100> &targetIds);

private:
    template<typename T>
    static Node<T> *getMiddle(Node<T> *head);

    template<typename T>
    static Node<T> *binarySearchRecur(Node<T> *head, int targetId);

    template<typename T>
    static Node<T> *getMiddleImproved(Node<T> *start, Node<T> *end);
};

#endif
