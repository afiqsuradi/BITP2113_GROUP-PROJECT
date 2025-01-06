#ifndef SALARY_LIST_H
#define SALARY_LIST_H

#include "linked_list.h"
#include "salary_model.h"

class SalaryList : public LinkedList<SalaryModel>
{
public:
    SalaryList() : LinkedList<SalaryModel>() {}
    SalaryList(const SalaryList &other) : LinkedList<SalaryModel>(other) {}
    SalaryList &operator=(const SalaryList &other)
    {
        LinkedList<SalaryModel>::operator=(other);
        return *this;
    }

    void print() const;
};

#endif