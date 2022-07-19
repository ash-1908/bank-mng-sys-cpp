#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

// class to represent a bank account
class Account
{
	int acno;
	char name[50];
	int balance;
	char type;

public:
	void createAccount();
	void showAccount() const;
	void modifyAccount();
	void depositAmount(int);
	void withdrawAmount(int);
	void displayDetails() const;
	int getAccountNumber() const;
	int getBalance() const;
	char getAccountType() const;
};

void Account::createAccount()
{
	system("CLS");
	cout << "\nEnter account number: ";
	cin >> acno;
	cout << "\nEnter the name of the account holder: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter type of the account (C/S): ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter the initial amount: ";
	cin >> balance;
	cout << "\n\nAccount Created.";
}

void Account::showAccount() const
{
	cout << "\nAccount Number: " << acno;
	cout << "\nAccount Holder Name: ";
	cout << name;
	cout << "\nType of Account: " << type;
	cout << "\nBalance amount : " << balance;
}

void Account::modifyAccount()
{
	cout << "\nAccount Number: " << acno;
	cout << "\nUpdate Account Holder Name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nUpdate Type of Account: ";
	cin >> type;
	type = toupper(type);
}

void Account::depositAmount(int amount)
{
	balance += amount;
}

void Account::withdrawAmount(int amount)
{
	balance -= amount;
}

void Account::displayDetails() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << balance << endl;
}

int Account::getAccountNumber() const
{
	return acno;
}

int Account::getBalance() const
{
	return balance;
}

char Account::getAccountType() const
{
	return type;
}

void write_account();
void display_account(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
	char ch;
	int num;
	do
	{
		system("CLS");

		cout << "Welcome to Bank Management System";

		cout << "\nMenu:";
		cout << "\n1. NEW ACCOUNT";
		cout << "\n2. DEPOSIT AMOUNT";
		cout << "\n3. WITHDRAW AMOUNT";
		cout << "\n4. BALANCE ENQUIRY";
		cout << "\n5. ALL ACCOUNT HOLDER LIST";
		cout << "\n6. CLOSE AN ACCOUNT";
		cout << "\n7. MODIFY AN ACCOUNT";
		cout << "\n8. EXIT";
		cout << "\nSelect Your Option (1-8): ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout << "\nEnter The account No. : ";
			cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout << "\nEnter The account No. : ";
			cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout << "\nEnter The account No. : ";
			cin >> num;
			display_account(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout << "\nEnter The account No. : ";
			cin >> num;
			delete_account(num);
			break;
		case '7':
			system("CLS");
			cout << "\nEnter The account No. : ";
			cin >> num;
			modify_account(num);
			break;
		case '8':
			system("CLS");
			cout << "\nMade by: Anmol Sharma, Abhi Sharma and Adarsh Singh.";
			break;
		default:
			cout << "\nInvalid choice.\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

void write_account()
{
	Account ac;
	ofstream outFile;
	outFile.open("accounts.dat", ios::binary | ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
	outFile.close();
}

void display_account(int n)
{
	Account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
	{
		if (ac.getAccountNumber() == n)
		{
			ac.displayDetails();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found = false;
	Account ac;
	fstream File;
	File.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
		if (ac.getAccountNumber() == n)
		{
			ac.displayDetails();
			cout << "\nEnter The New Details of account" << endl;
			ac.modifyAccount();
			int pos = (-1) * static_cast<int>(sizeof(Account));
			File.seekp(pos, ios::cur); // fncallat1353
			File.write(reinterpret_cast<char *>(&ac), sizeof(Account));
			cout << "\nRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\nRecord Not Found ";
}

void delete_account(int n)
{
	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
	{
		if (ac.getAccountNumber() != n)
		{
			outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\nRecord Deleted ..";
}

void display_all()
{
	system("CLS");
	Account ac;
	ifstream inFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account)))
	{
		ac.displayDetails();
	}
	inFile.close();
}

void deposit_withdraw(int acno, int option)
{
	int amt;
	bool found = false;
	Account ac;
	fstream File;
	File.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
		if (ac.getAccountNumber() == acno)
		{
			ac.showAccount();
			if (option == 1)
			{
				cout << "\nTO DEPOSITSS AMOUNT";
				cout << "\nEnter The amount to be deposited: ";
				cin >> amt;
				ac.depositAmount(amt);
			}
			if (option == 2)
			{
				cout << "\nTO WITHDRAW AMOUNT";
				cout << "\nEnter The amount to be withdraw: ";
				cin >> amt;
				int bal = ac.getBalance() - amt;
				if (bal < 0)
					cout << "Insufficience balance";
				else
					ac.withdrawAmount(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur); // fn1353
			File.write(reinterpret_cast<char *>(&ac), sizeof(Account));
			cout << "\nRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\nRecord Not Found ";
}
