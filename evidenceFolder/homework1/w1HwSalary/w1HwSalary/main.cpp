#include <iostream>
#include <iomanip>
using namespace std;


float calculateAnnualBaseSalary(int); //work out annual salary (no bonus)
float calculateChristmasBonus(float); //work out Christmas bonus
float calculateAnnualSalary(float, float); //work out final annual salary
float calculateDecemberSalary(float, float); //work out December salary
int myClampInt(int, int, int);


int salaryHwMain()			//computeDecemberSalary
{

	//read in the salary point
	cout << "Enter the salary point: ";
	int salaryPoint;
	cin >> salaryPoint;
	salaryPoint = myClampInt(1, 24, salaryPoint);
	const float annualBaseSalary = calculateAnnualBaseSalary(salaryPoint);
	//produce Christmas bonus
	const float christmasBonus = calculateChristmasBonus(annualBaseSalary);
	//produce final annual salary (incl. bonus)
	const float annualSalary = calculateAnnualSalary(annualBaseSalary, christmasBonus);
	//produce December salary (incl. bonus)
	const float decemberSalary = calculateDecemberSalary(annualBaseSalary, christmasBonus);

	const unsigned char poundSign(156);

	//output annual salary
	cout.setf(ios::fixed);
	cout << setprecision(2);
	cout << "Annual salary is: " << poundSign << annualSalary << endl;
	//output December salary
	cout << "December monthly salary is: " << poundSign << decemberSalary << endl;

	return 0;
}



float calculateAnnualBaseSalary(int pointsIn) {
	const float scalePointValue(2000.0f);
	//produce annual base salary (without bonus)
	return pointsIn * scalePointValue;
}


float calculateChristmasBonus(float annualBaseSalaryIn) {
	/*
	const float bonusRate(2.5f);
	return ((annualBaseSalaryIn * bonusRate) / 100.0f);
	*/
	return (annualBaseSalaryIn * 0.025);// - annualBaseSalaryIn; 
}


float calculateAnnualSalary(float annualBaseSalaryIn, float christmasBonusIn) {
	return annualBaseSalaryIn + christmasBonusIn;
}


float calculateDecemberSalary(float annualBaseSalary, float christmasBonus) {
	const float monthlySalary(annualBaseSalary / 12);
	return monthlySalary + christmasBonus;
}


int myClampInt(int minIn, int maxIn, int valueIn) {
	return (minIn <= valueIn) ? ((maxIn >= valueIn) ? valueIn : maxIn) : minIn;
}


int main() {
	salaryHwMain();
}