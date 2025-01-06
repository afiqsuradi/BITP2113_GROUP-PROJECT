#include "salary_model.h"

SalaryModel::SalaryModel() : id(0), paymentYear(0), paymentMonth(0), grossPay(0), hoursWorked(0) {}
SalaryModel::SalaryModel(int id, int paymentYear, int paymentMonth, double grossPay, int hoursWorked) : id(id), paymentYear(paymentYear), paymentMonth(paymentMonth), grossPay(grossPay), hoursWorked(hoursWorked) {}