#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <exception>


using namespace std; 
using std::runtime_error;


class WithdrawAmountExceedsBalance {
public:
	WithdrawAmountExceedsBalance() {
		"The amount you attempted to withdraw exceeds your balance"; 
	}
	string what() { 
		cout << endl;
		return "Please re-enter another value"; 
	}
};

class MinimumBalanceLessThanZero {
public:
	MinimumBalanceLessThanZero() {
		"The minimum balance in the account cannot be lesser than zero";
	}
	string what() {
		cout << endl;
		return "Please re-enter another value";
	}
};

class DepositLessThanZero {
public:
	DepositLessThanZero() {
		"The deposit number value entered cannot be lesser than zero";
	}
	string what() {
		cout << endl;
		return "Please re-enter another value";
	}
};



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
		while (amount < 0){
			try {
				throw DepositLessThanZero();
			}
			catch (DepositLessThanZero &depositLessThanZero) {
				cout << endl;
				cout << "Deposit amount must be greater than or equal to zero" << endl;
				cout << endl;
				cout << "Please re-enter another amount" << endl;
				cin >> amount;
			}
		}
		balance += amount;
		cout << endl;
		cout << "////////////////////////////////////////////////////////////////" << endl;
	}
	// Function enables withdrawal of money
	virtual void withdraw(double amount) = 0;
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
class CheckingAccount :public BankAccount{
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

	double amount;
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
	double setMinBalance(){
		// minBalance = m;
		cout << endl;
		cout << " ************ Assignment 5 *********** " << endl;
		cout << endl;
		cout << " ---- Set a minimum balance for " << this->getFN() << "'s checking account" << endl;
		cout << " ---- If you enter a negative number, it'll throw and handle an error" << endl;
		cout << endl;
		double m;
		cout << "Enter a minimum balance: " << endl;
		while (cin >> m){
			try {
				if (m < 0) {
					throw MinimumBalanceLessThanZero();
				}
				else {
					minBalance = m;
					break;
				}
			}
			catch (MinimumBalanceLessThanZero &minimumBalanceLessThanZero){
				cout << endl;
				cout << "Minimum balance to be maintained in the account cannot be negative" << endl;
				cout << endl;
				cout << "Enter another minimum balance: ";
			}
		}

		cout << endl;
		cout << "////////////////////////////////////////////////////////////////" << endl;
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
			// if after withdrawing money, the balance is still greater than
			// minimum balance to be maintained
			if ((getBalance() - amount) >= minBalance)
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
	// Write check function calls for withdrawal function
	void writeCheck(double a){
		withdraw(a);
	}
	// Prints all account details
	void printInfo(){

		cout << *this;
	}

	friend ostream& operator<< (std::ostream &out, CheckingAccount &c)
	{	
		out << endl;
		out << endl;
		out << "**** Overloading the cout operator **** " << endl;
		out << endl;
		out << endl;
		out << "Name of the account holder: " << c.getFN() << ' ' << c.getLN() << endl;
		out << "Account Number: " << c.getAccountNumber() << endl;
		out << "Account Type: " << c.type << endl;
		out << "Interest Rate: " << c.interestRate << endl;
		out << "Balance: " << c.getBalance() << endl;
		out << endl;
		out << "////////////////////////////////////////////////////////////////" << endl;
		return out;
	}
};

// Derived class from Bank Account
class SavingAccount :public BankAccount{
private:
	// Stores interest rate
	double IR;
	// type of account
	string type;
public:
	// Constructor receives first name, last name and balance
	SavingAccount(string fname, string sname, double bal) :BankAccount(fname, sname, bal){
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
		setBalance(getBalance() + (getBalance()*IR));
	}
	// Function enables withdrawal of money
	void withdraw(double amount){
		// Allow for money withdrawal if balance is greater than money to be withdrawn
		if (getBalance() >= amount){
			setBalance(getBalance() - amount);
		}
	}
		
	// Prints account details
	void printInfo(){

		cout << *this;
	}

	friend ostream& operator<< (std::ostream &out, SavingAccount &s)
	{
		out << "////////////////////////////////////////////////////////////////" << endl;
		out << endl;
		out << endl;
		out << "**** Overloading the cout operator **** " << endl;
		out << endl;
		out << endl;
		out << "Name of the account holder: " << s.getFN() << ' ' << s.getLN() << endl;
		out << "Account Number: " << s.getAccountNumber() << endl;
		out << "Account Type: " << s.type << endl;
		out << "Interest Rate: " << s.getIR() << endl;
		out << "Balance: " << s.getBalance() << endl;
		out << endl;
		out << "////////////////////////////////////////////////////////////////" << endl;
		return out;
	}
};

void callWithdraw(BankAccount *derived) {
	double a;

	cout << endl;
	cout << endl;
	cout << " -- The callWithdraw function is asking for calling the withdraw function of a class at run-time" << endl;
	cout << " -- The object received here is of type BankAccount" << endl;
	cout << " -- More specifically, in this example, we will call the withdraw function of Jack's account (a CheckingAccount derived from BankAccount)" << endl;
	cout << " -- The withdraw function of the object will be called shortly" << endl;
	cout << endl;
	cout << " ****************** How much money would you like to withdraw?	" << endl;
	cout << endl;
	cout << "(If you enter a withdrawal value more than the balance, it'll throw and handle and error)" << endl;
	cout << endl;
	cout << "Try entering a number above Jack's balance which is 1000" << endl;
	cout << endl;
	while (cin >> a) {
		try{
			if ((*derived).getBalance() < a){
				// print
				throw WithdrawAmountExceedsBalance();
			}
			else {
				derived->withdraw(a);
				break;
			}
		}
		catch (WithdrawAmountExceedsBalance &withdrawAmountExceedsBalance){
			cout << endl;
			cout << "You have insufficient funds" << endl;
			cout << withdrawAmountExceedsBalance.what() << endl;
		}
	}
	cout << endl;
	cout << "////////////////////////////////////////////////////////////////" << endl;
}

void callDeposit(BankAccount *derivedAnother) {
	double d;
	cout << endl;
	cout << endl;
	cout << " -- The callDeposit function is asking for calling the deposit function of a class at run-time" << endl;
	cout << " -- The object received here is of type BankAccount" << endl;
	cout << " -- More specifically, in this example, we will call the derived function of deposit from Samir's account" << endl;
	cout << " -- That is a SavingsAccount derived from class BankAccount" << endl;
	cout << " -- The deposit function of the object will be called shortly" << endl;
	cout << endl;
	cout << " ****************** How much money would you like to deposit?	" << endl;
	cout << endl;
	cout << "(If you enter a negative deposit value, it'll throw and handle and error)" << endl;
	cout << endl;
	cin >> d;
	derivedAnother->deposit(d);
	cout << endl;
	cout << "////////////////////////////////////////////////////////////////" << endl;
}


int main() {
	BankAccount *ptr;
	BankAccount *ptr2;

	CheckingAccount jackAccount("Jack", "Legend", 1000);
	SavingAccount samirAccount("Samir", "Abdullah", 450);

	jackAccount.setMinBalance();

	ptr = &jackAccount;
	callWithdraw(ptr);

	ptr2 = &samirAccount;
	callDeposit(ptr2);

	cout << jackAccount;
	cout << samirAccount;

	cout << endl;
	cout << "////////////////////////////////////////////////////////////////" << endl;
	cout << endl;

	cout << "Following is the array of 3 bank account's information being printed on the screen" << endl;
	cout << endl;
	SavingAccount henryAccount("Henry", "Locke", 1000);
	BankAccount *accArray[3];
	accArray[0] = &jackAccount;
	accArray[1] = &samirAccount;
	accArray[2] = &henryAccount;

	for (int i = 0; i < 3; i++){
		(*accArray[i]).printInfo();
	}
	

	/* jackAccount.printInfo();
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
	samirAccount.printInfo(); */



	system("pause");
	return(0);
}
