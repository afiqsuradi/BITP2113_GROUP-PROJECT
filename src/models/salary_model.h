#ifndef SALARY_MODEL_H
#define SALARY_MODEL_H

struct SalaryModel
{

    int id;
    int paymentYear;
    int paymentMonth;
    double grossPay;
    int hoursWorked;
    SalaryModel();
    SalaryModel(int id, int paymentYear, int paymentMonth, double grossPay, int hoursWorked);
};

#endif