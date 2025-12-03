#include <stdio.h>

double calculateRepayment(double loan, double rate, int years, double installment) {
    if (loan <= 0 || years == 0) {
        printf("Loan fully repaid or no years left.\n");
        return 0;
    }

    loan = loan - installment;
    if (loan < 0) loan = 0;

    loan = loan + (loan * rate);

    printf("Year %d: Remaining loan = %.2f\n", years, loan);

    double remaining = calculateRepayment(loan, rate, years - 1, installment);

    return installment + remaining;
}

int main() {
    double loan = 100000;
    double rate = 0.05;
    int years = 3;
    double installment = 30000;

    printf("Loan Repayment Schedule:\n\n");

    double totalPaid = calculateRepayment(loan, rate, years, installment);

    printf("\nTotal repayment over %d years = %.2f\n", years, totalPaid);

    return 0;
}

