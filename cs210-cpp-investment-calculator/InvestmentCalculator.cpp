/*******************************************************************************
 * Name:    Uri Naor
 * Date:    Feb 13
 * Purpose: Implementation of InvestmentCalculator
 ******************************************************************************/

#include "InvestmentCalculator.h"

const int MONTHS_IN_YEAR = 12;

/*******************************************************************************
                                MEMBER FUNCTIONS
*******************************************************************************/
double InvestmentCalculator::calculateBalanceWithDeposits(
    double t_startBalance,
    double t_monthlyDeposit,
    double t_annualInterest) {

    double updatedBalance = t_startBalance;
    double monthlyInterestRate = (t_annualInterest / 100.0) / MONTHS_IN_YEAR;

    m_annualInterestEarned = 0;

    for (int i = 0; i < MONTHS_IN_YEAR; i++) {
        updatedBalance = updatedBalance + t_monthlyDeposit;
        double monthlyInterestAmount = updatedBalance * monthlyInterestRate;

        // update annual interest earned so that we will be able to access it later
        m_annualInterestEarned += monthlyInterestAmount;
        updatedBalance += monthlyInterestAmount;
    }

    return updatedBalance;
}

double InvestmentCalculator::getAnnualInterestEarned() {
    return m_annualInterestEarned;
}
