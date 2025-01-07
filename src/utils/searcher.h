#ifndef SEARCHER_H
#define SEARCHER_H

#include "employee_list.h"
#include <chrono>

class Searcher {
public:
    static Node<EmployeeModel> *linearSearch(EmployeeList *employees, int targetId);

    static Node<EmployeeModel> *linearSearchImproved(EmployeeList *employees, int targetId);

    static Node<EmployeeModel> *binarySearch(EmployeeList *employees, int targetId);

    static Node<EmployeeModel> *binarySearchImproved(EmployeeList *employees, int targetId);

private:
    template<typename T>
    static Node<T> *getMiddle(Node<T> *head);

    template<typename T>
    static Node<T> *binarySearchRecur(Node<T> *head, int targetId, int &iterationCount);

    template<class T>
    static Node<T> *getMiddleImproved(Node<T> *start, Node<T> *end);

    static void displayResult(Node<EmployeeModel> *result, int &targetId, std::string searchType);

    static void displayTime(std::chrono::time_point<std::chrono::system_clock> startTime,
                            std::chrono::time_point<std::chrono::system_clock> endTime);
};

#endif
