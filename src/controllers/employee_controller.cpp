#include "employee_controller.h"
#include <fstream>
#include <string>
#include <iomanip> // For std::put_time
#include <iostream>


EmployeeController::EmployeeController(const std::string &filepath) {
    employees = new EmployeeList();
    this->filePath = filepath;
    loadFromJson();
}

EmployeeController::~EmployeeController() {
    delete employees;
}

EmployeeList *EmployeeController::getEmployees() const {
    return employees;
}

void EmployeeController::printAll() const {
    if (employees == nullptr) {
        std::cerr << "Error: employee list is null" << std::endl;
        return;
    }
    employees->print();
}

bool EmployeeController::loadFromJson() {
    std::ifstream file(this->filePath);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file: " << this->filePath << std::endl;
        return false;
    }
    nlohmann::json json_data;
    try {
        file >> json_data;
    } catch (const nlohmann::json::parse_error &ex) {
        std::cerr << "Error parsing JSON file: " << ex.what() << std::endl;
        return false;
    }

    if (!json_data.is_array()) {
        std::cerr << "Error: JSON data must be an array of objects" << std::endl;
        return false;
    }
    employees->clear();
    for (const auto &empJson: json_data) {
        EmployeeModel *empData = new EmployeeModel();
        SalaryList *salaryList = new SalaryList();
        if (empJson.contains("id") && empJson["id"].is_number_integer())
            empData->id = empJson["id"];
        if (empJson.contains("name") && empJson["name"].is_string())
            empData->name = empJson["name"];
        if (empJson.contains("department") && empJson["department"].is_string())
            empData->department = empJson["department"];
        if (empJson.contains("position") && empJson["position"].is_string())
            empData->position = empJson["position"];
        if (empJson.contains("Salary") && empJson["Salary"].is_array()) {
            for (const auto &salJson: empJson["Salary"]) {
                SalaryModel *salaryData = new SalaryModel();
                if (salJson.contains("id") && salJson["id"].is_number_integer()) // Corrected key name here
                    salaryData->id = salJson["id"];

                if (salJson.contains("payment_year") && salJson["payment_year"].is_number_integer())
                    salaryData->paymentYear = salJson["payment_year"];

                if (salJson.contains("payment_month") && salJson["payment_month"].is_number_integer())
                    salaryData->paymentMonth = salJson["payment_month"];

                if (salJson.contains("gross_pay") && salJson["gross_pay"].is_number())
                    salaryData->grossPay = salJson["gross_pay"];

                if (salJson.contains("hours_worked") && salJson["hours_worked"].is_number())
                    salaryData->hoursWorked = salJson["hours_worked"];

                salaryList->pushBack(*salaryData);
                delete salaryData;
            }
        }
        empData->salary_payments = salaryList;
        employees->pushBack(*empData);
        delete empData;
    }
    return true;
}

nlohmann::json EmployeeController::employeeToJson() const {
    nlohmann::json json_data = nlohmann::json::array();

    Node<EmployeeModel> *current = employees->getHead();
    while (current) {
        nlohmann::json emp_json;
        emp_json["id"] = current->data.id;
        emp_json["name"] = current->data.name;
        emp_json["department"] = current->data.department;
        emp_json["position"] = current->data.position;

        nlohmann::json salary_arr = nlohmann::json::array();
        Node<SalaryModel> *current_salary = current->data.salary_payments->getHead();
        while (current_salary) {
            nlohmann::json sal_json;
            sal_json["id"] = current_salary->data.id;
            sal_json["payment_year"] = current_salary->data.paymentYear;
            sal_json["payment_month"] = current_salary->data.paymentMonth;
            sal_json["gross_pay"] = current_salary->data.grossPay;
            sal_json["hours_worked"] = current_salary->data.hoursWorked;
            salary_arr.push_back(sal_json);
            current_salary = current_salary->next;
        }
        emp_json["Salary"] = salary_arr;
        json_data.push_back(emp_json);
        current = current->next;
    }
    return json_data;
}

void EmployeeController::saveToJson(const std::string &filepath) const {
    nlohmann::json json_data = employeeToJson();
    std::ofstream file(filepath);
    if (file.is_open()) {
        file << std::setw(4) << json_data << std::endl;
        file.close();
        std::cout << "JSON data written to " << filepath << std::endl;
    } else {
        std::cerr << "Unable to open file for writing" << std::endl;
    }
}
