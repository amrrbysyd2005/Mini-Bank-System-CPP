#include <iostream>
#include<string>
#include<limits>
#include <cctype>
#include <stdlib.h>
using namespace std;
int NumOfAccounts = 0;
bool IsValidNumber(double num, char condition) {
    switch (condition) {
    case '>':
        if (num > 0) return true;
        else return false;
    case '<':
        if (num < 0) return true;
        else return false;
    default:
        cout << "Invalid Condition!" << endl;
        return  false;
    }
}

double ReadDoubleNumbers(const string& str, char condition) {
    double num;
    while (true) {
        cout<<str;
        cin >> num;
        if (cin.fail()||!IsValidNumber(num,condition)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a positive number\t";
        }
        else return num;
    }
}

int ReadIntNumbers(const string& str, char condition) {
    int num;
    while (true) {
        cout<<str;
        cin >> num;
        if (cin.fail() || !IsValidNumber(num, condition)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a positive number\t";
        }
        else return num;
    }
}



string ReadString(const string& str) {
    string Reply;
    cout<<str;
    getline(cin >> ws, Reply);
    return Reply;
 }
bool IsAllDigits(string str) {
    if (str.empty())return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}
void separator() {
    system("cls");
    cout << "\n*******************************\n" << endl;
}
enum Operations {
    Check_Balance = 1, Deposit = 2, Withdraw = 3, Change_PIN = 4, Delete = 5, Exit = 6
};
struct Client {
    string AccountNumber;
    string Name;
    double Balance = 0;
    string PIN;
};
string ReadAccountNumber() {
    string AccountNumber;
    while (true) {
        AccountNumber = ReadString("Enter Your Account Number ( 6 digits )?\t");
        short len = AccountNumber.length();

        if (!IsAllDigits(AccountNumber) || len != 6) {
            cout<<"Invalid Account Number\n";
        }
        else return AccountNumber;
    }
}

string ReadPIN(const string& str) {
    string PIN;

    while (true) {
        PIN = ReadString(str);
        int len = PIN.length();
        if (!IsAllDigits(PIN) || len != 4) {
            cout<<"Invalid Password\n";
        }
        else return PIN;
    }
}
bool isFull() {
    if (NumOfAccounts >= 100) return true;
    else return false;
}
bool isRepeated(Client clientGroup[]) {
    for (int i = 0; i < NumOfAccounts - 1; i++) {
        if (clientGroup[NumOfAccounts].AccountNumber == clientGroup[i].AccountNumber)
            return true;
        
    }return false;
}
void FillClientInfo(Client clientGroup[]) {
    do {
        clientGroup[NumOfAccounts].AccountNumber = ReadAccountNumber();
        if (isRepeated(clientGroup)) {
            cout<<"This account is exist already!\n";
            cout<<"Enter a new account\n";
        }
        else break;
    } while (true);
    clientGroup[NumOfAccounts].Name = ReadString("Enter Your Name?\t");
    clientGroup[NumOfAccounts].PIN = ReadPIN("Enter Your Password?\t");
}
void CreateClientsAccount(Client clientGroup[]) {

    if (!isFull()) {
        cout<<"\n==== Sign up ====\n";
        cout << "Enter The client Information:" << endl;
        separator();
        FillClientInfo(clientGroup);
        separator();
        NumOfAccounts++;
    }
    else cout << "Overflow!" << endl;
}

int FindAt(Client clientGroup[], string AccountNumber) {
    for (int i = 0; i < NumOfAccounts; i++) {
        if (AccountNumber == clientGroup[i].AccountNumber) return i;

    }return -1;
}



int CheckAccountNumber(Client clientGroup[], Client& client) {
    char choice; int index = 0;
    while (true) {
        client.AccountNumber = ReadAccountNumber();
        index = FindAt(clientGroup, client.AccountNumber);
        if (index >= 0) return index;
        cout<<"Account not found\n";
        cout << "If you want to register a new account, click Y\t";
        cin >> choice;
        choice = toupper(choice);
        if (choice == 'Y') {
            CreateClientsAccount(clientGroup);

        }
    }return index;
}
void blockAccount(bool BlockList[], int index) {
    BlockList[index] = true;
    cout << "This Account is Blocked" << endl;
    return;
}

bool CheckPIN(Client client[], int index) {
   int failedAttempts = 0;
   while (failedAttempts < 3) {
       string PIN = ReadPIN("Enter PIN?\t");
       if (PIN == client[index].PIN)
           return true;
       failedAttempts++;
       cout << "You have " << 3 - failedAttempts << " tries" << endl;
   }return false;
}


double deposit(Client &client) {
    double value;
    value = ReadDoubleNumbers("How much money do you need to deposit?\t",'>');
    client.Balance += value;
    return value;
}

double withdraw(Client& client) {
    double value;
    value = ReadDoubleNumbers("How much money do you need to Withdraw?\t", '>');
    if (value > client.Balance) {
       
        return -1;
    }
    client.Balance -= value;
    return value;
}

void changePIN(Client& client) {
    string PIN = ReadPIN("Enter the new PIN:\t");
    client.PIN = PIN;

}

void DeleteAccount(Client client[],int index) {
    char isSure;
    cout<<"Are you sure ? (Y / N)\t";
    cin >> isSure;
    isSure = toupper(isSure);
    if (isSure != 'Y') return;
    int i = index;
    while (i < NumOfAccounts-1) {
        client[i] = client[i+1];
        i++;
    }
    NumOfAccounts--;
}

void Menu() {
    system("cls");
    cout << "==== List of Choices ====" << endl;
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Change PIN\n";
    cout << "5. Delete\n";
    cout << "6. Exit\n";
    cout << "=========================" << endl;
}
void AfterLogin(Client client[], int &index) {
    int choice=0; char ch='0';
    do {
        Menu();
        choice = ReadIntNumbers("\nEnter Your Choice:\t",'>');
        switch ((Operations)choice) {
        case Operations::Check_Balance:
            cout << "Your Balance = " << client[index].Balance << endl;
            break;
        case Operations::Deposit: {
            double depoVal = deposit(client[index]);
            cout << "Your Deposit = " << depoVal << " $" << endl;
            cout << "Your Balance = " << client[index].Balance << endl;
        }
                                break;
        case Operations::Withdraw: {

            double amountWit = withdraw(client[index]);
            if (amountWit == -1) {
                cout << "Insufficient Balance " << endl;
            }
            else {
                cout << "Your Withdraw = " << amountWit << " $" << endl;
                cout << "Your Balance = " << client[index].Balance << endl;
            }
        }
                                 break;
        case Operations::Change_PIN:
            changePIN(client[index]);
            return;
        case Operations::Delete:
            DeleteAccount(client, index);
            return;
        case Operations::Exit:
            return;
        default:
            cout<<"Invalid Choice!\n";
            break;
        };
        cout<<"If You Want to Continue Press 'Y':\t";
        cin >> ch;
        ch = toupper(ch);
    } while (ch == 'Y');
}

void login(Client clientGroup[],bool Block[]) {
    Client client; int index;
    cout<<"\n==== Log in ====\n";
    index = CheckAccountNumber(clientGroup, client);
    if (index == -1) return;
    if (!Block[index]) {
        if (!CheckPIN(clientGroup, index)) {
            blockAccount(Block, index);
        }
        else {
            AfterLogin(clientGroup, index);
        }
    }
    else {
        cout << "This account is blocked\n";
    }
}
void fillBlock_False(bool Block[]) {
    for (int i = 0; i < 100; i++) {
        Block[i] = false;
    }
}
bool isEmpty() {
    return NumOfAccounts == 0;
}

bool isContinue() {
    char cont;
    cout<<"Do You Want To Continue (Y OR N):\t";
    cin >> cont;
    cont = toupper(cont);
    if (cont == 'Y') return true;
    else return false;
}

void Choices(Client clients[], bool Block[]) {
    system("cls");
    int ch; char cont;
    do {
        cout<<"\n===== Mini Bank System =====\n\n";
        cout<<"1. Create an account\n";
        cout<<"2. Log in\n";
        cout<<"\n==============================\n";
        ch = ReadIntNumbers("\nEnter Your Choice: ",'>');
        switch (ch) {
        case 1:
            CreateClientsAccount(clients);
            if (!isContinue()) {
                return;
            }break;

        case 2:

            if (!isEmpty()) {
                login(clients, Block);
                if (!isContinue()) {
                    return;
                }break;
            }
            else {
                cout << "No account is exist" << endl;
            }
            
            break;
        default:
            cout << "You have to insert (1 or 2)" << endl;
        }
    } while (true);
}

int main()
{
    Client clients[100];
    bool Block[100];
    fillBlock_False(Block);
    Choices(clients, Block);

}
