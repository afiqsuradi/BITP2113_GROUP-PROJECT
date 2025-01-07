#include "searcher.h"

// #include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

void Searcher::displayResult(Node<EmployeeModel> *result, int &targetId, std::string searchType) {
    if (result != nullptr) {
        std::cout << searchType << ": Employee with ID " << targetId << " found. " << std::endl;
        // EmployeeList::printEmployee(result);
    } else {
        std::cout << searchType << ": Employee with ID " << targetId << " not found. " << std::endl;
    }
}

void Searcher::displayTime(std::chrono::time_point<std::chrono::system_clock> startCalculation,
                           std::chrono::time_point<std::chrono::system_clock> endCalculation) {
    auto startTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(startCalculation.time_since_epoch()).
            count();
    auto endTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation.time_since_epoch()).count();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation - startCalculation);
    std::cout << "Start Time: ";
    std::cout << startTimeUnix << " ms " << std::endl;
    std::cout << "End Time: ";
    std::cout << endTimeUnix << " ms " << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
}


Node<EmployeeModel> *Searcher::linearSearch(EmployeeList *employees, int targetId) {
    long long duration = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    Node<EmployeeModel> *current = employees->getHead();
    Node<EmployeeModel> *result = nullptr;
    int iterationCount = 0;

    while (current != nullptr) {
        iterationCount++;
        if (current->data.id == targetId) {
            result = current;
        }
        current = current->next;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
    displayResult(result, targetId, "Linear Search");

    std::cout << "Linear Search Iterations: " << iterationCount << std::endl;

    return result;
}

Node<EmployeeModel> *Searcher::linearSearchImproved(EmployeeList *employees, int targetId) {
    long long duration = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    Node<EmployeeModel> *current = employees->getHead();
    Node<EmployeeModel> *result = nullptr;
    int iterationCount = 0;

    while (current != nullptr) {
        iterationCount++;
        if (current->data.id == targetId) {
            result = current;
            break;
        }
        current = current->next;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
    displayResult(result, targetId, "Linear Search (Improved)");

    std::cout << "Linear Search (Improved) Iterations: " << iterationCount << std::endl;

    return result;
}


Node<EmployeeModel> *Searcher::binarySearch(EmployeeList *employees, int targetId) {
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;
    int iterationCount = 0;

    Node<EmployeeModel> *result = binarySearchRecur(employees->getHead(), targetId, iterationCount);

    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
    displayResult(result, targetId, "Binary Search");
    std::cout << "Binary Search Iterations: " << iterationCount << std::endl;
    return result;
}

template<typename T>
Node<T> *Searcher::getMiddle(Node<T> *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node<T> *slow = head;
    Node<T> *fast = head->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}


template<typename T>
Node<T> *Searcher::binarySearchRecur(Node<T> *head, int targetId, int &iterationCount) {
    if (head == nullptr) return nullptr;

    iterationCount++;

    Node<T> *middle = getMiddle(head);
    if (middle->data.id == targetId) return middle;

    if (middle->data.id > targetId) {
        Node<T> *temp = head;
        while (temp->next != middle) {
            temp = temp->next;
        }
        temp->next = nullptr; // Split the list
        return binarySearchRecur(head, targetId, iterationCount);
    }
    if (middle->next == nullptr) return nullptr;

    return binarySearchRecur(middle->next, targetId, iterationCount);
}

Node<EmployeeModel> *Searcher::binarySearchImproved(EmployeeList *employees, int targetId) {
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;


    Node<EmployeeModel> *startNode = employees->getHead();
    Node<EmployeeModel> *endNode = nullptr;

    Node<EmployeeModel> *result = nullptr;
    int iterationCount = 0;

    while (startNode != endNode) {
        iterationCount++;

        Node<EmployeeModel> *mid = getMiddleImproved(startNode, endNode);

        if (mid == nullptr) {
            break;
        }

        if (mid->data.id == targetId) {
            result = mid;
            break;
        }

        if (mid->data.id > targetId) {
            endNode = mid;
        } else {
            startNode = mid->next;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
    displayResult(result, targetId, "Binary Search (Optimized)");
    std::cout << "Binary Search (Optimized) Iterations: " << iterationCount << std::endl;
    return result;
}

template<typename T>
Node<T> *Searcher::getMiddleImproved(Node<T> *start, Node<T> *end) {
    if (start == nullptr || start == end) {
        return nullptr;
    }
    Node<T> *slow = start;
    Node<T> *fast = start;

    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
