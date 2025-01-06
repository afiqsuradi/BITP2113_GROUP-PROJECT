#ifndef SORTER_H
#define SORTER_H

#include <employee_controller.h>

#include "employee_list.h"

class Sorter {
public:
    static void insertionSort(EmployeeList *employees);

    static void insertionSortImproved(EmployeeList *employees);

    static void mergeSortIterative(EmployeeList &employee);

    static void mergeSort(EmployeeList *employees);

    static void mergeSortImproved(EmployeeList *employees);

    static void mergeSortIterative(EmployeeList *employees);

private:
    static Node<EmployeeModel> *splitIterative(Node<EmployeeModel> *head);

    static Node<EmployeeModel> *mergeIterative(Node<EmployeeModel> *left, Node<EmployeeModel> *right);

    template<typename T>
    static Node<T> *mergeSortRecur(Node<T> *head, long long *mergeDecisions);

    template<typename T>
    static Node<T> *mergeSortRecurImproved(Node<T> *head, long long *swaps);

    template<typename T>
    static void splitList(Node<T> *source, Node<T> **frontRef, Node<T> **backRef);

    template<typename T>
    static Node<T> *merge(Node<T> *a, Node<T> *b, long long *mergeDecisions);

    template<typename T>
    static Node<T> *mergeImproved(Node<T> *a, Node<T> *b, long long *swaps);
};

#endif
