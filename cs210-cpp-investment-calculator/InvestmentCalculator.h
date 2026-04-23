/*******************************************************************************
 * Name:    Uri Naor
 * Date:    Feb 13
 * Purpose: Declaration of the InvestmentCalculator class
 ******************************************************************************/

#ifndef InvestmentCalculator_H
#define InvestmentCalculator_H

/*******************************************************************************
                               CLASS DECLARATION
*******************************************************************************/
class InvestmentCalculator {
public:
    /* Member Functions */
    double calculateBalanceWithDeposits(
        double t_startBalance, 
        double t_monthlyDeposit, 
        double t_annualInterest);
    double getAnnualInterestEarned();

private:
    // i've initialized the member directly to avoid writing empty constructors
    double m_annualInterestEarned = 0;
};

#endif /* InvestmentCalculator_H */
