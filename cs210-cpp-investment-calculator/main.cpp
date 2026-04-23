/*******************************************************************************
 * Name:    Uri Naor
 * Date:    Feb 13
 * Purpose: Calculates and compares investment growth with 
 * and without monthly deposits using compound interest
 ******************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

#include "InvestmentCalculator.h"

/*******************************************************************************
                                FORWARD DECLARATIONS
*******************************************************************************/
void outputInstructionsAndGetInput(
    double &t_initialInvestment, 
    double &t_monthlyDeposit, 
    double &t_annualInterest, 
    double &t_numberYears);

void displayInfo(
    InvestmentCalculator &t_calc,
    double t_initialInvestment, 
    double t_monthlyDeposit, 
    double t_annualInterest, 
    double t_numberYears,
    string t_displayTitle);

/*******************************************************************************
                                     MAIN
*******************************************************************************/
int main()
{
    string runAgain; 

    // loop to allow user to test different values
    do {
        double initialInvestment = -1;
        double monthlyDeposit = -1;
        double annualInterest = -1;
        double numberYears = -1;

        // gets input and updates the variables by reference
        outputInstructionsAndGetInput(
            initialInvestment, 
            monthlyDeposit,
            annualInterest, 
            numberYears);

        InvestmentCalculator calc;
        
        // prints the info without additional deposits - I passed 0 as deposit 
        // to reuse the class function
        displayInfo(
            calc, 
            initialInvestment, 
            0, 
            annualInterest, 
            numberYears, 
            "Balance and Interest WITHOUT Additional Monthly Deposits");
        
        // prints info with deposits
        displayInfo(
            calc, 
            initialInvestment, 
            monthlyDeposit, 
            annualInterest, 
            numberYears, 
            "Balance and Interest WITH Additional Monthly Deposits");

        // check if user wants to run again
        runAgain = "";
        while (runAgain != "y" && runAgain != "Y" && runAgain != "n" && runAgain != "N") {
            cout << "\nWould you like to test different values? (y/n): ";
            cin >> runAgain;
        }

    } while (runAgain == "y" || runAgain == "Y"); 

    return 0;
}

/*******************************************************************************
                                HELPER FUNCTIONS
*******************************************************************************/
void outputInstructionsAndGetInput(
    double &t_initialInvestment, 
    double &t_monthlyDeposit, 
    double &t_annualInterest, 
    double &t_numberYears) {

    cout << "***************************" << endl;
    cout << "********Data Input*********" << endl;
    cout << "(All input must be positive)" << endl;

    // reset variables for re-runs
    t_initialInvestment = -1;
    t_monthlyDeposit = -1;
    t_annualInterest = -1;
    t_numberYears = -1;

    while (t_initialInvestment < 0) {
        cout << "Initial Investment Amount: $";
        cin >> t_initialInvestment;
        
        // handle non-numeric input
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            t_initialInvestment = -1; 
            cout << "Invalid input. Please enter a numeric value.\n";
        }
    }

    while (t_monthlyDeposit < 0) {
        cout << "Monthly Deposit: $";
        cin >> t_monthlyDeposit;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t_monthlyDeposit = -1;
            cout << "Invalid input. Please enter a numeric value.\n";
        }
    }

    while (t_annualInterest < 0) {
        cout << "Annual Interest: %";
        cin >> t_annualInterest;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t_annualInterest = -1;
            cout << "Invalid input. Please enter a numeric value.\n";
        }
    }

    while (t_numberYears <= 0) {
        cout << "Number of years: ";
        cin >> t_numberYears;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t_numberYears = -1;
            cout << "Invalid input. Please enter a numeric value.\n";
        }
    }

    cout << "Press any key to continue . . .";

    // wait for key press
    cin.ignore();
    cin.get();
}

void displayInfo(
    InvestmentCalculator &t_calc,
    double t_initialInvestment, 
    double t_monthlyDeposit, 
    double t_annualInterest, 
    double t_numberYears,
    string t_displayTitle) {
        
        cout << endl;
        cout << t_displayTitle << endl;
        cout << "======================================================" << endl;
        cout << "Year         Year End Balance         Year End Earned Interest" << endl;
        cout << "======================================================" << endl;

        double currentBalance = t_initialInvestment;

        // loop for each year
        for (int year = 1; year <= t_numberYears; year++) {
            // calculate currentBalance
            currentBalance = t_calc.calculateBalanceWithDeposits(
                currentBalance, t_monthlyDeposit, t_annualInterest);
            
                // get updated interest earned
                double annualInterestEarned = t_calc.getAnnualInterestEarned();

                cout << fixed << setprecision(2);
                cout << year << "                  $" << currentBalance;
                cout << "                  $" << annualInterestEarned << endl;
        }
}
