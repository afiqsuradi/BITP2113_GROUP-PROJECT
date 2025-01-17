#include "sorter.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>


/*
 * Im adding this task to my suicide note 🥲🙏
 */

template<typename T>
void Sorter::splitList(Node<T> *source, Node<T> **frontRef, Node<T> **backRef) {
    if (source == nullptr || source->next == nullptr) {
        *frontRef = source;
        *backRef = nullptr;
        return;
    }
    Node<T> *slow = source;
    Node<T> *fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

template<typename T>
Node<T> *Sorter::mergeImproved(Node<T> *a, Node<T> *b, long long *swaps) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Node<T> *merged = nullptr;
    if (a->data.id <= b->data.id) {
        merged = a;
        merged->next = mergeImproved(a->next, b, swaps);
    } else {
        (*swaps)++;
        merged = b;
        merged->next = mergeImproved(a, b->next, swaps);
    }
    return merged;
}

template<typename T>
Node<T> *Sorter::mergeSortRecurImproved(Node<T> *head, long long *swaps) {
    if (head == nullptr || head->next == nullptr) return head;
    Node<T> *front;
    Node<T> *back;
    splitList(head, &front, &back);

    front = mergeSortRecurImproved(front, swaps);
    back = mergeSortRecurImproved(back, swaps);

    return mergeImproved(front, back, swaps);
}

void Sorter::mergeSortImproved(EmployeeList *employees) {
    if (employees->isEmpty()) return;
    long long swaps = 0;

    auto start = std::chrono::high_resolution_clock::now();
    std::time_t startTimeT = std::chrono::system_clock::to_time_t(start);
    std::tm *localStartTime = std::localtime(&startTimeT);
    auto startCalculation = start;
    Node<EmployeeModel> *sortedHead = mergeSortRecurImproved(employees->getHead(), &swaps);


    employees->setHead(sortedHead);
    Node<EmployeeModel> *current = employees->getHead();
    if (current != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        employees->setTail(current);
    } else {
        employees->setTail(nullptr);
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::time_t endTimeT = std::chrono::system_clock::to_time_t(end);
    std::tm *localEndTime = std::localtime(&endTimeT);
    auto endCalculation = end;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation - startCalculation);

    std::cout << "Improved Merge Sort Start Time: ";
    std::cout << std::put_time(localStartTime, "%H:%M:%S") << std::endl;
    std::cout << "Improved Merge Sort End Time: ";
    std::cout << std::put_time(localEndTime, "%H:%M:%S") << std::endl;
    std::cout << "Time taken by Improved Merge Sort: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Merge Decisions Performed: " << swaps << std::endl;
}

void Sorter::mergeSort(EmployeeList *employees) {
    if (employees->isEmpty())
        return;
    long long swaps = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    Node<EmployeeModel> *sortedHead = mergeSortRecurImproved(employees->getHead(), &swaps);

    employees->setHead(sortedHead);
    Node<EmployeeModel> *current = employees->getHead();
    if (current != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        employees->setTail(current);
    } else {
        employees->setTail(nullptr);
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    auto startTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(startCalculation.time_since_epoch()).
            count();
    auto endTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation.time_since_epoch()).count();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation - startCalculation);

    std::cout << "Merge Sort Start Time: ";
    std::cout << startTimeUnix << " ms " << std::endl;
    std::cout << "Merge Sort End Time: ";
    std::cout << endTimeUnix << " ms " << std::endl;
    std::cout << "Time taken by Merge Sort: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Merge Performed: " << swaps << std::endl;
}

template<typename T>
Node<T> *Sorter::merge(Node<T> *a, Node<T> *b, long long *swaps) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    // Check if merge is needed (unnecessary, slowed down this shit)
    Node<T> *a_tail = a;
    while (a_tail->next != nullptr) {
        a_tail = a_tail->next;
    }

    if (a_tail->data.id <= b->data.id) {
        // Already sorted, just append
        a_tail->next = b;
        return a;
    }

    Node<T> *merged = nullptr;
    if (a->data.id <= b->data.id) {
        merged = a;
        merged->next = merge(a->next, b, swaps);
    } else {
        (*swaps)++;
        merged = b;
        merged->next = merge(a, b->next, swaps);
    }
    return merged;
}

template<typename T>
Node<T> *Sorter::mergeSortRecur(Node<T> *head, long long *swaps) {
    if (head == nullptr || head->next == nullptr) return head;

    Node<T> *front;
    Node<T> *back;
    splitList(head, &front, &back);

    front = mergeSortRecurImproved(front, swaps);
    back = mergeSortRecurImproved(back, swaps);

    return mergeImproved(front, back, swaps);
}

void Sorter::insertionSort(EmployeeList *employees) {
    if (employees->isEmpty())
        return;

    long long swaps = 0;

    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    Node<EmployeeModel> *sorted = nullptr;
    Node<EmployeeModel> *unsorted = employees->getHead();

    while (unsorted != nullptr) {
        Node<EmployeeModel> *current = unsorted;
        unsorted = unsorted->next;

        if (sorted == nullptr || current->data.id <= sorted->data.id) {
            current->next = sorted;
            sorted = current;
        } else {
            Node<EmployeeModel> *insertPosition = sorted;
            Node<EmployeeModel> *prevInsertPosition = nullptr;
            while (insertPosition != nullptr && insertPosition->data.id < current->data.id) {
                prevInsertPosition = insertPosition;
                insertPosition = insertPosition->next;
                swaps++;
            }
            current->next = insertPosition;
            if (prevInsertPosition != nullptr) {
                prevInsertPosition->next = current;
            } else {
                sorted = current;
            }
        }
    }

    employees->setHead(sorted);
    Node<EmployeeModel> *current = employees->getHead();
    if (current != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        employees->setTail(current);
    } else {
        employees->setTail(nullptr);
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    auto startTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(startCalculation.time_since_epoch()).
            count();
    auto endTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation.time_since_epoch()).count();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation - startCalculation);

    std::cout << "Insertion Sort Start Time: ";
    std::cout << startTimeUnix << " ms " << std::endl;
    std::cout << "Insertion Sort End Time: ";
    std::cout << endTimeUnix << " ms " << std::endl;
    std::cout << "Time taken by Insertion Sort: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Swaps Performed: " << swaps << std::endl;
}

void Sorter::insertionSortImproved(EmployeeList *employees) {
    if (employees->isEmpty())
        return;

    long long swaps = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    Node<EmployeeModel> *sorted = nullptr;
    Node<EmployeeModel> *unsorted = employees->getHead();

    while (unsorted != nullptr) {
        Node<EmployeeModel> *current = unsorted;
        unsorted = unsorted->next;

        if (sorted == nullptr || current->data.id <= sorted->data.id) {
            current->next = sorted;
            sorted = current;
        } else {
            Node<EmployeeModel> *insertPosition = sorted;
            while (insertPosition->next != nullptr && insertPosition->next->data.id < current->data.id) {
                insertPosition = insertPosition->next;
            }

            current->next = insertPosition->next;
            if (insertPosition->next != current) {
                swaps++;
            }
            insertPosition->next = current;
        }
    }


    employees->setHead(sorted);
    Node<EmployeeModel> *current = employees->getHead();
    if (current != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        employees->setTail(current);
    } else {
        employees->setTail(nullptr);
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    auto startTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(startCalculation.time_since_epoch()).
            count();
    auto endTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation.time_since_epoch()).count();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation - startCalculation);

    std::cout << "Improved Insertion Sort Start Time: ";
    std::cout << startTimeUnix << " ms " << std::endl;
    std::cout << "Improved Insertion Sort End Time: ";
    std::cout << endTimeUnix << " ms " << std::endl;
    std::cout << "Time taken by Improved Insertion Sort: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Swaps Performed: " << swaps << std::endl;
}

Node<EmployeeModel> *Sorter::splitIterative(Node<EmployeeModel> *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node<EmployeeModel> *slow = head;
    Node<EmployeeModel> *fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node<EmployeeModel> *temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node<EmployeeModel> *Sorter::mergeIterative(Node<EmployeeModel> *left, Node<EmployeeModel> *right, long long &swaps) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    Node<EmployeeModel> *result = nullptr;
    Node<EmployeeModel> *tail = nullptr;


    while (left != nullptr && right != nullptr) {
        if (left->data.id <= right->data.id) {
            if (result == nullptr) {
                result = left;
                tail = left;
            } else {
                tail->next = left;
                tail = left;
            }
            left = left->next;
        } else {
            swaps++;
            if (result == nullptr) {
                result = right;
                tail = right;
            } else {
                tail->next = right;
                tail = right;
            }
            right = right->next;
        }
    }

    if (left != nullptr) {
        tail->next = left;
    }
    if (right != nullptr) {
        tail->next = right;
    }


    return result;
}

void Sorter::mergeSortIterative(EmployeeList *employee) {
    long long swaps = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto startCalculation = start;

    if (employee->getHead() == nullptr || employee->getHead()->next == nullptr) {
        return;
    }

    Node<Node<EmployeeModel> *> *head = new Node(employee->getHead());
    Node<Node<EmployeeModel> *> *tail = head;

    Node<EmployeeModel> *curr = employee->getHead();
    while (curr != nullptr) {
        if (curr != employee->getHead()) {
            tail->next = new Node<Node<EmployeeModel> *>(curr);
            tail = tail->next;
        }
        curr = curr->next;
        tail->data->next = nullptr;
    }

    while (head->next != nullptr) {
        Node<Node<EmployeeModel> *> *newHead = nullptr;
        Node<Node<EmployeeModel> *> *newTail = nullptr;

        Node<Node<EmployeeModel> *> *current = head;
        while (current != nullptr) {
            Node<Node<EmployeeModel> *> *left = current;
            Node<Node<EmployeeModel> *> *right = (current->next != nullptr) ? current->next : nullptr;
            current = (right != nullptr) ? right->next : nullptr;

            Node<EmployeeModel> *merged = mergeIterative(left->data, (right != nullptr) ? right->data : nullptr, swaps);
            if (newHead == nullptr) {
                newHead = new Node<Node<EmployeeModel> *>(merged);
                newTail = newHead;
            } else {
                newTail->next = new Node<Node<EmployeeModel> *>(merged);
                newTail = newTail->next;
            }
        }
        Node<Node<EmployeeModel> *> *temp = head;
        while (temp != nullptr) {
            Node<Node<EmployeeModel> *> *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        head = newHead;
        tail = newTail;
    }
    employee->setHead(head->data);
    employee->fixTail();
    delete head;

    auto end = std::chrono::high_resolution_clock::now();
    auto endCalculation = end;
    auto startTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(startCalculation.time_since_epoch()).
            count();
    auto endTimeUnix = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation.time_since_epoch()).count();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endCalculation - startCalculation);

    std::cout << "Merge Sort Start Time: " << startTimeUnix << " ms" << std::endl;
    std::cout << "Merge Sort End Time: " << endTimeUnix << " ms" << std::endl;
    std::cout << "Time taken by Merge Sort: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Merge Performed: " << swaps << std::endl;
}

