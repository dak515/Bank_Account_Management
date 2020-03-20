#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <stack>
#include <string.h>
#include <cstring>

using namespace std;

// When instantiatied, the class's composite object maintains the first and last name of
// the account holder's name
class Name{
private:
	// First name of the account holder
	string firstName;
	// Second name of the account holder
	string secondName;
public:
	// Non-default constructor called when object is created with parameters
	Name(string f, string s){
		firstName = f;
		secondName = s;
	}
	// Default constructor called when object is created without parameters
	Name(){
		firstName = "f";
		secondName = "s";
	}
	// Accessor for first name of the account holder
	string getFirstName(){
		return(firstName);
	}
	// Accessor for second name of the account holder
	string getSecondName(){
		return(secondName);
	}
	// Setter of first name of account holder
	void setFirstName(string f){
		firstName = f;
	}
	// Setter of second name of account holder
	void setSecondName(string s){
		secondName = s;
	}
};

class BankAccount{
private:
	// Declaring an object of type Name
	Name names;
	// Account number of the account holder
	int accountNumber;
	// Account balance of account holder
	double balance;

public:
	// Default constructor assigns 0 to account balance and also provides
	// the account with an account number;
	BankAccount(){
		assignAccountNumber();
		balance = 0;
	}
	// Non-default constructor requires first name, last name and account balance of account holder
	BankAccount(string fname, string sname, double bal){
		// Stores the first name into the object names' first element
		names.setFirstName(fname);
		// Stores the second name into the object names' second element
		names.setSecondName(sname);
		// Assigns an account number to the account created
		assignAccountNumber();
		// Stores the balance of the account holder
		balance = bal;
	}
	// Destructor
	~BankAccount(){
	}
	// Assigns an account number to a new account
	void assignAccountNumber(){
		// Static integer assigned value 1000 which gets
		// incremented everytime an object is created
		static int x = 10000;
		accountNumber = x++;
	}
	// Accessor for account number
	int getAccountNumber(){
		return(accountNumber);
	}
	// Receives amount to be deposited and adds that to the balance
	void deposit(double amount){
		balance += amount;
	}
	// Function enables withdrawal of money
	virtual void withdraw(double amount){
		// Allow for money withdrawal if balance is greater than money to be withdrawn
		if (getBalance() >= amount){
			setBalance(getBalance() - amount);
		}
		// else print that funds are insufficient
		else {
			cout << "Insufficient funds" << endl;
		}
	}
	// Accessor for balance of account
	double getBalance() {
		return(balance);
	}
	// Enables account holder to set balance of the account
	void setBalance(double b) {
		balance = b;
	}
	// Accessor for the first name of the account holder
	string getFN(){
		return(names.getFirstName());
	}
	// Accessor for the second name of the account holder
	string getLN(){
		return(names.getSecondName());
	}
	// Prints details of account
	virtual void printInfo(){
		cout << "////////////////////////////////////////////////////////////////" << endl;
		cout << endl;
		cout << "Name of account holder: " << getFN() << ' ' << getLN() << endl;
		cout << "Account Number: " << getAccountNumber() << endl;
		cout << "Balance: " << getBalance() << endl;
		cout << endl;
		cout << "////////////////////////////////////////////////////////////////" << endl;
	}
};

// Derived class from Bank Account
class CheckingAccount:public BankAccount{
private:
	// Interest rate that increases balance of account holder when money is deposited
	double interestRate;
	// Maintains a minimum balance that the account is recommended to have
	double minBalance;
	// Charged in addition to the amount to be withdrawn if balance is lesser than
	// minimum balance and greater than 0
	double serviceCharge;
	// Stores that this account created is of type Checking
	string type;
public:
	// Constructor which requires first name, second name and balance of the account holder
	CheckingAccount(string fname, string sname, double balance) : BankAccount(fname, sname, balance){
		// Initializing service charge to 15
		serviceCharge = 15;
		// Initializing the minimum balance to 200
		minBalance = 200;
		// Initializing the interest rate to 0.04
		interestRate = 0.04;
		// Type of account
		type = "Checking Account";
	}
	// Setter of the interest rate
	void setInterestRate(double r){
		interestRate = r;
	}
	// Accessor of the interest rate
	double getInterestRate(){
		return(interestRate);
	}
	// Accessor for minimum balance that the account is recommended to maintain
	double getMinBalance(){
		return(minBalance);
	}
	// Setter of the minimum balance
	void setMinBalance(double m){
		minBalance = m;
	}
	// Setter of the service charge
	void setServiceCharges(double s){
		serviceCharge = s;
	}
	// Accessor of service charge
	double getServiceCharges(){
		return(serviceCharge);
	}
	// Balance after including interest rate
	void postInterest(){
		setBalance(getBalance() + (getBalance()*interestRate));
	}
	// Function to allow for withdrawal of money, receives amount to be withdrawn
	void withdraw(double amount){
		// if balance is lesser than the amount to be withdrawn
		if (getBalance() < amount){
			// print
			cout << "You have insufficient funds" << endl;
		}
		// if balance is greater than amount to be withdrawn
		else {
			// if after withdrawing money, the balance is still greater than
			// minimum balance to be maintained
			if ((getBalance() - amount)>=minBalance)
			{	// allow for withdrawal and change balance
				setBalance(getBalance() - amount);
			}
			// else if balance after withdrawal will be lesser than or equal to
			// minimum balance and balance exluding amount and service charge is greater than 0
			else if (getBalance() - amount < minBalance && getBalance() - (amount + serviceCharge) > 0){
				// allow for withdrawal but subtract service charge of 15
				setBalance(getBalance() - (amount + serviceCharge));
			}
			// else if balance after withdrawal will be lesser than or equal to
			// minimum balance and balance exluding amount and service charge is lesser than 0
			else if (getBalance() - amount < minBalance && getBalance() - (amount + serviceCharge) < 0){
				// don't allow for withdrawal and print
				cout << "You have insufficient FUNDS!!" << endl;
			}
		}
	}
	// Write check function calls for withdrawal function
	void writeCheck(double a){
		withdraw(a);
	}
	// Prints all account details
	void printInfo(){
		cout << "////////////////////////////////////////////////////////////////" << endl;
		cout << endl;
		cout << "Name of account holder: " << getFN() << ' ' << getLN() << endl;
		cout << "Account Number: " << getAccountNumber() << endl;
		cout << "Account Type: " << type << endl;
		cout << "Interest Rate: " << interestRate << endl;
		cout << "Balance: " << getBalance() << endl;
		cout << endl;
		cout << "////////////////////////////////////////////////////////////////" << endl;
	}
};

// Derived class from Bank Account
class SavingAccount:public BankAccount{
private:
	// Stores interest rate
	double IR;
	// type of account
	string type;
public:
	// Constructor receives first name, last name and balance
	SavingAccount(string fname, string sname, double bal):BankAccount(fname, sname, bal){
		// Sets type of account to Savings Account
		type = "Savings Account";
		// Initializes the interest rate to 0.6
		IR = 0.6;
	}
	// Setter for interest rate
	void setIR(double r){
		IR = r;
	}
	// Accessor of interest rate
	double getIR(){
		return(IR);
	}
	// Balance after including interest rate
	void postInterest(){
		setBalance(getBalance()+(getBalance()*IR));
	}
	// Function enables withdrawal of money
	void withdraw(double amount){
		// Allow for money withdrawal if balance is greater than money to be withdrawn
		if (getBalance() >= amount){
			setBalance(getBalance()-amount);
		}
		// else print that funds are insufficient
		else {
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "Insufficient funds in "<< getFN() << "'s account for withdrawal of money"<< endl;
			cout << endl;
			cout << "Therefore, "<<getFN() << "'s balance will remain the same" << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
		}
	}
	// Prints account details
	void printInfo(){
		cout << "////////////////////////////////////////////////////////////////" << endl;
		cout << endl;
		cout << "Name of account holder: " << getFN() << ' ' << getLN() << endl;
		cout << "Account Number: " << getAccountNumber() << endl;
		cout << "Account Type: " << type << endl;
		cout << "Interest Rate: " << IR << endl;
		cout << "Balance: " << getBalance() << endl;
		cout << endl;
		cout << "////////////////////////////////////////////////////////////////" << endl;
	}
};


int main() {

	CheckingAccount jackAccount("Jack", "Legend", 1000);
	SavingAccount samirAccount("Samir", "Abdullah", 450);

	jackAccount.printInfo();
	samirAccount.printInfo();

	jackAccount.deposit(100);
	samirAccount.deposit(100);

	jackAccount.printInfo();
	samirAccount.printInfo();

	jackAccount.postInterest();
	samirAccount.postInterest();

	jackAccount.printInfo();
	samirAccount.printInfo();

	jackAccount.writeCheck(1000);
	samirAccount.withdraw(900);

	jackAccount.printInfo();
	samirAccount.printInfo();



	system("pause");
	return(0);
}
