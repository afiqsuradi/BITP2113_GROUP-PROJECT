#include <iostream>
#include <string>
#include "operation_enum.h"

class UiController {
private:
    int *quitProgram, *operationChoice, menuChoice = 0;

    void handleDisplayMenu() {
        getChoice(menuChoice);
        switch (menuChoice) {
            case 1:
                displaySortingTechniquesChoices();
                break;
            case 2:
                displaySearchingTechnique();
                break;
            case 3:
                displayAddiotionalFunctionalities();
                break;
            case 4:
                *operationChoice = DATA_RELOAD;
                break;
            case 5:
                *quitProgram = 1;
                break;
            default:
                *operationChoice = NO_OPERATION;
                break;
        }
    }

    void handleSortingTechniquesChoices() {
        int techniqueChoice = 0;
        getChoice(menuChoice);
        switch (menuChoice) {
            case 1:
                displayTechniqueVersionChoice("Technique 1 (Insertion Sort)");
                getChoice(techniqueChoice);
                if (techniqueChoice == 1) {
                    *operationChoice = SORT_TECHNIQUE_ONE;
                } else if (techniqueChoice == 2) {
                    *operationChoice = SORT_TECHNIQUE_ONE_IMPROVED;
                }
                break;
            case 2:
                displayTechniqueVersionChoice("Technique 2 (Merge Sort)");
                getChoice(techniqueChoice);
                if (techniqueChoice == 1) {
                    *operationChoice = SORT_TECHNIQUE_TWO;
                } else if (techniqueChoice == 2) {
                    *operationChoice = SORT_TECHNIQUE_TWO_IMPROVED;
                }
                break;
            case 3:
                displayTechniqueVersionChoice("Technique Comparison");
                getChoice(techniqueChoice);
                if (techniqueChoice == 1) {
                    *operationChoice = SORT_COMPARE;
                } else if (techniqueChoice == 2) {
                    *operationChoice = SORT_COMPARE_IMPROVED;
                }
                break;
            default:
                *operationChoice = NO_OPERATION;
                break;
        }
    }

    void handleSearchingTechnique() {
        int techniqueChoice = 0;
        std::cout << "Choice: ";
        std::cin >> menuChoice;
        switch (menuChoice) {
            case 1:
                displayTechniqueVersionChoice("Technique 1 (Linear Search)");
                getChoice(techniqueChoice);
                if (techniqueChoice == 1) {
                    *operationChoice = SEARCH_TECHNIQUE_ONE;
                } else if (techniqueChoice == 2) {
                    *operationChoice = SEARCH_TECHNIQUE_ONE_IMPROVED;
                }
                break;
            case 2:
                displayTechniqueVersionChoice("Technique 2 (Binary Search)");
                getChoice(techniqueChoice);
                if (techniqueChoice == 1) {
                    *operationChoice = SEARCH_TECHNIQUE_TWO;
                } else if (techniqueChoice == 2) {
                    *operationChoice = SEARCH_TECHNIQUE_TWO_IMPROVED;
                }
                break;
            case 3:
                displayTechniqueVersionChoice("Technique Comparison");
                getChoice(techniqueChoice);
                if (techniqueChoice == 1) {
                    *operationChoice = SEARCH_COMPARE;
                } else if (techniqueChoice == 2) {
                    *operationChoice = SEARCH_COMPARE_IMPROVED;
                }
                break;
            default:
                *operationChoice = NO_OPERATION;
                break;
        }
    }

    void handleAddiotionalFunctionalities() {
        getChoice(menuChoice);
        switch (menuChoice) {
            case 1:
                *operationChoice = ADDITIONAL_ONE;
                break;
            case 2:
                *operationChoice = ADDITIONAL_TWO;
                break;
            case 3:
                *operationChoice = ADDITIONAL_THREE;
                break;
            default:
                *operationChoice = NO_OPERATION;
                break;
        }
    }

    static void getChoice(int &choice) {
        std::cout << "Choice: ";
        std::cin >> choice;
    }

public:
    UiController(int *quitProgram, int *operationChoice) : quitProgram(quitProgram), operationChoice(operationChoice) {
    }

    static void displayHeader(const std::string &title) {
        std::cout << "====================================" << std::endl;
        std::cout << title << std::endl;
        std::cout << "====================================" << std::endl;
    }

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void displayMenu(size_t *employeeSize) {
        clearScreen();
        std::cout << "========================================" << std::endl;
        std::cout << "Welcome to the Employee Database System" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Employee Data Loaded: " << *employeeSize << std::endl
                << std::endl
                << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1.  Sorting Techniques" << std::endl;
        std::cout << "2.  Searching Techniques" << std::endl;
        std::cout << "3.  Additional Functionalities" << std::endl;
        std::cout << "4.  Reload Employee Data" << std::endl;
        std::cout << "5.  Exit" << std::endl;
        handleDisplayMenu();
    }

    void displaySortingTechniquesChoices() {
        clearScreen();
        std::cout << "========================================" << std::endl;
        std::cout << "Sorting Techniques" << std::endl;
        std::cout << "========================================" << std::endl
                << std::endl
                << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1.  Sort Data Using Technique 1 (Insertion Sort)" << std::endl;
        std::cout << "2.  Sort Data Using Technique 2 (Merge Sort)" << std::endl;
        std::cout << "3.  Compare Sorting Techniques" << std::endl;
        std::cout << "4.  Back to Main Menu" << std::endl
                << std::endl;
        handleSortingTechniquesChoices();
    }

    void displayTechniqueVersionChoice(const std::string &title) {
        clearScreen();
        displayHeader(title);
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1.  Normal Version" << std::endl;
        std::cout << "2.  Improved Version" << std::endl;
        std::cout << "3.  Back to Main Menu" << std::endl
                << std::endl;
    }


    void displaySearchingTechnique() {
        clearScreen();
        std::cout << "========================================" << std::endl;
        std::cout << "Searching Techniques" << std::endl;
        std::cout << "========================================" << std::endl
                << std::endl
                << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1.  Search Data Using Technique 1 (Linear Search)" << std::endl;
        std::cout << "2.  Search Data Using Technique 2 (Binary Search)" << std::endl;
        std::cout << "3.  Compare Searching Runtimes" << std::endl;
        std::cout << "4.  Back to Main Menu" << std::endl
                << std::endl;
        handleSearchingTechnique();
    }

    void displayAddiotionalFunctionalities() {
        clearScreen();
        std::cout << "========================================" << std::endl;
        std::cout << "Additional Functionalities" << std::endl;
        std::cout << "========================================" << std::endl
                << std::endl
                << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1. Average Salary Calculation per Department" << std::endl;
        std::cout << "2. Most Productive Employee Per Department" << std::endl;
        std::cout << "3. Performance-Based Bonus Calculation" << std::endl;
        std::cout << "4. Back to Main Menu" << std::endl
                << std::endl;
        handleAddiotionalFunctionalities();
    }
};
