#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BankException : public exception
{
protected:
    string message;

public:
    BankException(string msg)
    {
        message = msg;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.")
    {
    }
};

class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.")
    {
    }
};

class BankAccount
{
private:
    string name;
    double balance;

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        balance -= amount;
    }

    void display()
    {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

int main()
{
    string name;
    double balance, depositAmount, withdrawAmount1, withdrawAmount2;

    cout << "Enter account holder name: ";
    cin >> name;

    cout << "Enter initial balance: ";
    cin >> balance;

    BankAccount account(name, balance);

    cout << "\nInitial Account Details:" << endl;
    account.display();

    cout << "\nEnter deposit amount: ";
    cin >> depositAmount;

    cout << "Enter first withdrawal amount: ";
    cin >> withdrawAmount1;

    cout << "Enter second withdrawal amount: ";
    cin >> withdrawAmount2;

    try
    {
        cout << "\nDepositing Rs. " << depositAmount << "..." << endl;
        account.deposit(depositAmount);

        cout << "Withdrawing Rs. " << withdrawAmount1 << "..." << endl;
        account.withdraw(withdrawAmount1);

        cout << "Withdrawing Rs. " << withdrawAmount2 << "..." << endl;
        account.withdraw(withdrawAmount2);
    }
    catch (const InsufficientFundsException &e)
    {
        cout << e.what() << endl;
    }
    catch (const InvalidAmountException &e)
    {
        cout << e.what() << endl;
    }
    catch (const BankException &e)
    {
        cout << "Bank Exception: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "General Exception: " << e.what() << endl;
    }

    cout << "\nFinal Account Details:" << endl;
    account.display();

    return 0;
}