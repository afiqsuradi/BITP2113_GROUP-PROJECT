#include "salary_list.h"
#include <iomanip>
#include "salary_model.h"

void SalaryList::print() const
{
    if (isEmpty())
    {
        std::cout << "No salary records found.\n";
        return;
    }

    Node<SalaryModel> *current = head;
    double totalSalary = 0.0;

    std::cout << "\nSalary Payment Details:\n";
    std::cout << "======================\n\n";

    std::cout << std::fixed << std::setprecision(2);

    while (current != nullptr)
    {
        const SalaryModel &salary = current->data;
        std::cout << "Payment ID: " << salary.id << "\n"
                  << "paymentYear" << salary.paymentYear << "\n"
                  << "paymentMonth" << salary.paymentMonth << "\n"
                  << "grossPay" << salary.grossPay << "\n"
                  << "hoursWorked" << salary.hoursWorked << "\n"
                  << "----------------------\n";

        totalSalary += salary.grossPay;
        current = current->next;
    }

    std::cout << "\nSummary:\n"
              << "Total Payments: " << getSize() << "\n"
              << "Total Amount: $" << totalSalary << "\n"
              << "Average Payment: $" << (getSize() > 0 ? totalSalary / getSize() : 0.0) << "\n";
}