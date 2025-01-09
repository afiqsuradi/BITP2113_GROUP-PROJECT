#include "searcher.h"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>


void Searcher::displayResult(Node<EmployeeModel> *result, int &targetId, std::string searchType) {
    if (result != nullptr) {
        std::cout << searchType << ": Employee with ID " << targetId << " found. " << std::endl;
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

void Searcher::linearSearch(EmployeeList *employees, std::array<int, 100> &targetIds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    for (int targetId: targetIds) {
        Node<EmployeeModel> *current = employees->getHead();
        Node<EmployeeModel> *result = nullptr;

        while (current != nullptr) {
            if (current->data.id == targetId) {
                result = current;
                break;
            }
            current = current->next;
        }
        displayResult(result, targetId, "Linear Search");
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
}

void Searcher::linearSearchImproved(EmployeeList *employees, std::array<int, 100> &targetIds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;
    for (int targetId: targetIds) {
        Node<EmployeeModel> *current = employees->getHead();
        Node<EmployeeModel> *result = nullptr;

        while (current != nullptr) {
            if (current->data.id == targetId) {
                result = current;
                break;
            }
            current = current->next;
        }
        displayResult(result, targetId, "Linear Search (Improved)");
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
}


void Searcher::binarySearch(EmployeeList *employees, std::array<int, 100> &targetIds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;
    for (int targetId: targetIds) {
        Node<EmployeeModel> *result = binarySearchRecur(employees->getHead(), targetId);
        displayResult(result, targetId, "Binary Search");
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
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
Node<T> *Searcher::binarySearchRecur(Node<T> *head, int targetId) {
    if (head == nullptr) return nullptr;

    Node<T> *middle = getMiddle(head);
    if (middle->data.id == targetId) return middle;

    if (middle->data.id > targetId) {
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        while (temp != middle) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == nullptr) {
            return Searcher::binarySearchRecur<T>(nullptr, targetId); // Explicitly specify type T
        } else {
            prev->next = nullptr;
            Node<T> *result = binarySearchRecur(head, targetId);
            prev->next = middle;
            return result;
        }
    }
    if (middle->next == nullptr) return nullptr;
    return binarySearchRecur(middle->next, targetId);
}

void Searcher::binarySearchImproved(EmployeeList *employees, std::array<int, 100> &targetIds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    for (int targetId: targetIds) {
        Node<EmployeeModel> *startNode = employees->getHead();
        Node<EmployeeModel> *endNode = nullptr;
        Node<EmployeeModel> *result = nullptr;

        while (startNode != endNode) {
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
        displayResult(result, targetId, "Binary Search (Optimized)");
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    displayTime(startCalculation, endCalculation);
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
