#include<iostream>
#include<limits>
#include<vector>
#include<iomanip>
#include<fstream>
using namespace std;

enum enMainMenuPermissons
{
    pAll = -1, 
    pListClients = 1, pAddNewClient = 2,
    pDeleteClient = 4, pUpdateClient = 8,
    pFindClient = 16, pTransaction = 32,
    pManageUsers = 64
};


void showMainMenu(); 
void showTransactionMenu();
void showManageUsersScreen();
bool checkAccessPermission(enMainMenuPermissons permission);
void  goBack2MainMenu();

const string clientFile = "client.txt";
const string userFile = "users.txt";
//----------------------------- Back End -----------------------------

struct stClient
{
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    double balance;
    bool mark4delete = false;
};

vector<string> splitString(string str, string delim = "#//#")
{
    short pos = 0;
    string word = "";

    vector<string> vString;

    while((pos = str.find(delim)) != string::npos)
    {
        word = str.substr(0, pos);
        if(word != "")
        {
            vString.push_back(word);
        }
        str.erase(0, pos + delim.length());
    }
     // handle the last string after delimeter
    if(str != "")
       vString.push_back(str);

    return vString;
}

string convertRecord2String(stClient client, string delim = "#//#")
{
    string word = "";

    word += client.accountNumber + delim;
    word += client.pinCode + delim;
    word += client.name + delim;
    word += client.phone + delim;
    word += to_string(client.balance);

    return word;
}

stClient convertString2Record(string str)
{
    // Split string first
    vector<string> vString = splitString(str, "#//#");
    stClient client;

    client.accountNumber = vString[0];
    client.pinCode = vString[1];
    client.name = vString[2];
    client.phone = vString[3];
    client.balance = stod(vString[4]);

    return client;
}

bool isAccountNumberExist(string accoutNum, string fileName)
{
    fstream myFile;
    myFile.open(fileName, ios::in);


    if(myFile.is_open())
    {
        stClient client;
        string line;

        while(getline(myFile, line))
        {
            client = convertString2Record(line);    
            if(client.accountNumber == accoutNum)
            {
                myFile.close();
                return true; 
            }
           
        }
        myFile.close();
    }
    return false ;
}

stClient readClientInfo()
{
    stClient client;

    cout << "Enter Client Account Number: ";
    getline(cin >> ws, client.accountNumber);

    while(isAccountNumberExist(client.accountNumber, clientFile))
    {
        cout << "Client with [ " << client.accountNumber << " ] Already Exist, Please Enter another one\n";
        cout << "Enter Account Number: ";
        getline(cin >> ws, client.accountNumber);
    }

    cout << "Enter Client Pin Code: ";
    getline(cin, client.pinCode);
    cout <<"Enter Client Name: ";
    getline(cin, client.name);
    cout <<"Enter Client Phone: ";
    getline(cin, client.phone);
    cout <<"Enter Client Balance: ";
    cin >> client.balance;

    return client;
}

// just take the line data and save it in file
void saveLineData2File(string fileName,  string line)
{
    fstream myFile;
    myFile.open(fileName, ios::out | ios::app); // save new data, without remove the exist data

    if(myFile.is_open())
    {
        myFile << line << endl;
        myFile.close();
    }
}

vector<stClient> loadClientData_from_File(string fileName)
{
    vector<stClient> vClient;
    fstream myFile;

    myFile.open(fileName, ios::in); // Get Client From File and put them in vector of struct

    if(myFile.is_open())
    {
        string line;
        stClient client;

        while(getline(myFile, line))
        {
            client = convertString2Record(line);
            vClient.push_back(client);
        }
        myFile.close();
    }

    return vClient;
}

void printClientRecord(stClient client)
{
    cout << "\n### Client Record Info ###\n";
    cout << "Client Account Number : " << client.accountNumber << endl;
    cout << "Client Pin Code : " << client.pinCode << endl ;
    cout << "Client Name : " << client.name << endl;
    cout << "Client Phone : " << client.phone << endl;
    cout << "Client Balance: " << client.balance << endl;

}

void add_One_Client2File()
{
    // Enter New Client to add
    stClient client = readClientInfo();
    saveLineData2File(clientFile, convertRecord2String(client));
}

void add_All_Clients2File()
{
    char ans = 'n';
        do
        {
            cout << "Adding New Client\n";
            add_One_Client2File();
            cout << "\nClient Added Successfully, Do you want to add more Clients? [Y/N]: ";
            cin >> ans;
            cin.ignore();
        } while (tolower(ans) == 'y');
}

void print_One_Client(stClient client)
{
    cout << "| " << left << setw(15) << client.accountNumber;
    cout << "| " << left << setw(10) << client.pinCode;
    cout << "| " << left << setw(30) << client.name;
    cout << "| " << left << setw(15) << client.phone;
    cout << "| " << left << setw(10) << client.balance;
}

void print_All_Clients()
{
    vector<stClient> vClient = loadClientData_from_File(clientFile);

    cout << "\n\t\t\t\t The Client Size [ " << vClient.size() << " ] Client(s)\n";
    cout << "\n-----------------------------------------------------------";
    cout << "-------------------------------------------\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(15) << "Client Phone";
    cout << "| " << left << setw(10) << "Client Balance";
    cout << "\n-----------------------------------------------------------";
    cout << "--------------------------------------------\n";
    for(stClient & c : vClient)
    {
        print_One_Client(c);
        cout << endl;
    }
    cout << "-----------------------------------------------------------";
    cout << "--------------------------------------------\n";
}

string getAccountNumber()
{
    string str;
    cout <<"Enter Client Account Number: ";
    cin >> str;
    return str;
}

bool findClient_by_AccountNumber(string accountNumber, vector<stClient> vClient, stClient &client)
{
    for(stClient & c : vClient)
    {
        if(c.accountNumber == accountNumber)
        {
            client = c;
            return true;
        }
    }
    return false ; 
}

bool markClient4Delete(string accountNum, vector<stClient> &vClient)
{
    for(stClient & c: vClient)
    {
        if(c.accountNumber == accountNum)
        {
            c.mark4delete = true;
            return true;
        }
    }
    return false;
}

vector<stClient> saveClientData2File(string fileName, vector<stClient> vClient)
{
    fstream myFile;
    myFile.open(fileName, ios::out); // delete all clients , save new ones


    if(myFile.is_open())
    {
        string line ;

        for(stClient & c : vClient)
        {
            if(c.mark4delete == false)
            {
                line = convertRecord2String(c); 
                myFile << line << endl;
            }
        }
        myFile.close();
    }

    return vClient; // File Now is clean, but vector still containing all clients (incude marked)
}

bool deleteClient_by_AccountNumber(string accountNum, vector<stClient> & vClient)
{
    char ans = 'n';
    stClient client;

    if(findClient_by_AccountNumber(accountNum, vClient, client))
    {
        printClientRecord(client);
        cout << "\n\033[91m Do You want to Delete This Client? [Y/N]: ";
        cin >> ans;
        if(tolower(ans) == 'y')
        {
            markClient4Delete(accountNum, vClient);
            // save all clients except the marked one.
            saveClientData2File(clientFile, vClient);
            // refresh the screen using new client in file
            // Update The vector with new clients
            vClient = loadClientData_from_File(clientFile);
            cout << "\nClient Deleted Successfully\n";
            return true;
        }
       return false;
    }else
    {
        cout << "Client with Account Number [ " << accountNum <<" ] Not Found!\n";
        return false;
    }
}

stClient changeClientRecord(string accountNum)
{
    stClient client;

    client.accountNumber = accountNum;

    cout << "Enter Client Pin Code: ";
    getline(cin >> ws, client.pinCode);
    cout << "Enter Client Name: ";
    getline(cin, client.name);
    cout << "Enter Client Phone: ";
    getline(cin, client.phone);
    cout << "Enter Client Balance: ";
    cin >> client.balance;

    return client;
}

bool updateClient_by_AccountNumber(string accountNum, vector<stClient> & vClient)
{
    char ans = 'n'; 
    stClient client;

    if(findClient_by_AccountNumber(accountNum, vClient, client))
    {
        printClientRecord(client);
        cout << "\nDo You Want to UPdate this Client ? [Y/N]: ";
        cin >> ans;
        if(tolower(ans) == 'y') 
        {
            for(stClient & c : vClient)  
            {
                if(c.accountNumber == accountNum)
                {
                    c = changeClientRecord(accountNum);
                    break;
                }
            }
            saveClientData2File(clientFile, vClient);
            vClient = loadClientData_from_File(clientFile);
            cout << "\n Client Updated Successfully\n";
            return true; 
        }
        return false;
    }else
    {
        cout <<"Client with Account number [ " << accountNum << " ] not found\n"; 
        return false; 
    }
}

void showAccessDeniedMessage()
{
    cout << "\n------------------------------------------\n";
    cout << "Access Denied, \nYou Don't Have permission to do this. \nPlease Contact Your Admin.";
    cout << "\n-------------------------------------------\n";
}

void showAddNewClientScreen()
{
    system("clear");
    cout << "\033[92m";
    cout << "\n====================================\n";
    cout << "\t Adding New client Screen";
    cout << "\n====================================\n";
    add_All_Clients2File();
}

void showAllClientsScreen()
{
    if(!checkAccessPermission(enMainMenuPermissons::pListClients))
    {
        showAccessDeniedMessage();
        return;
    }

    system("clear");
    cout << "\033[93m";
    cout << "\033[1m";
    cout << "\n====================================\n";
    cout << "\t Show All clients Screen";
    cout << "\n====================================\n";

    print_All_Clients();

}

void showFindClientByAccountNumberScreen()
{
    if(!checkAccessPermission(enMainMenuPermissons::pFindClient))
    {
        showAccessDeniedMessage();
        return;
    }


    system("clear");
    cout << "\n===================================================\n";
    cout << "\t Find Client By Account Number Screen";
    cout << "\n===================================================\n";

    string accountNum = getAccountNumber();
    vector<stClient> vClient = loadClientData_from_File(clientFile);
    stClient client; 

    if(findClient_by_AccountNumber(accountNum, vClient, client))
        printClientRecord(client);
    else
        cout <<"Client With Account Number [ " << accountNum << " ] is Not Found!\n";
}

void showDeleteClientScreen()
{
    if(!checkAccessPermission(enMainMenuPermissons::pDeleteClient))
    {
        showAccessDeniedMessage();
        return;
    }
    system("clear");
    cout << "\n===================================================\n";
    cout << "\t Delete Client Screen";
    cout << "\n===================================================\n";

    string accountNum = getAccountNumber();
    vector<stClient> vClient = loadClientData_from_File(clientFile);

    deleteClient_by_AccountNumber(accountNum, vClient);   

}

void showUpdateClientScreen()
{
    if(!checkAccessPermission(enMainMenuPermissons::pUpdateClient))
    {
        showAccessDeniedMessage();
        return;
    }
    system("clear");
    cout << "\n===================================================\n";
    cout << "\t Update Client Screen";
    cout << "\n===================================================\n";

    string accountNum = getAccountNumber();
    vector<stClient> vClient = loadClientData_from_File(clientFile);

    updateClient_by_AccountNumber(accountNum, vClient);

}

void showLogoutScren()
{
    system("clear");
    cout << "===================================\n";
    cout << "\t Logout Screen\n";
    cout << "===================================\n";

}

//-------------------------- [1] Transaction Menu Screen -----------------------

bool depositeOperation(string accountNum,double amount, vector<stClient>& vClient)
{
    char ans  = 'n';

    cout << "Are you sure you want to perform this transaction? [Y/N]: ";
    cin >> ans;
    if(tolower(ans)== 'y')
    {
        for(stClient & c : vClient)
        {
            if(c.accountNumber == accountNum)
            {
                c.balance += amount;
                saveClientData2File(clientFile, vClient);
                cout << "\033[92mDone Successfully. New Balance is: " << c.balance << endl;
                return true;
            }
        }
    } 

    return false;
}

void printClientBalance(stClient client)
{
    cout << "| " << left << setw(15) << client.accountNumber;
    cout << "| " << left << setw(25) << client.name;
    cout << "| " << left << setw(12) << client.balance;
}

void printAllClientsBalance(vector<stClient> vClient)
{
    double sum  = 0;
    cout << "\n\t\tThe Clients are " << vClient.size() << " Client.\n";
    cout << "-----------------------------------------------------------\n"; 
    cout << "| " << left << setw(15) << "Account Number"; 
    cout << "| " << left << setw(25) << "Client Name"; 
    cout << "| " << left << setw(12) << "Client Balance"; 
    cout << "\n----------------------------------------------------------\n"; 
    
    if(vClient.size() == 0)
       cout << "\tNoClients Avaliable on System!\n";
    else
    {
        for(stClient & c : vClient)
        {
            printClientBalance(c); 
            cout << endl; 
            sum+=c.balance;
        }
    }
    cout << "------------------------------------------------------------\n"; 
    cout << "The Total Balance for Clients: " << sum << endl;
}

void showDepositScreen()
{
  system("clear");
  cout << "======================================\n";
  cout << "\t Depsit Screen\n";
  cout << "======================================\n";
  
  vector<stClient> vClient = loadClientData_from_File(clientFile);
  string accountNum = getAccountNumber();

  stClient client;

  while(!findClient_by_AccountNumber(accountNum, vClient, client))
  {
    cout << "Client with Accout Number [ " <<accountNum<< " ] not found\n";
    accountNum = getAccountNumber(); 
  }

  printClientRecord(client);

  double amount = 0;
  cout << "\nEnter the Amount to Deposit: ";
  cin >> amount;

  depositeOperation(accountNum, amount, vClient);

}

void showWithdrawScreen()
{
  system("clear");
  cout << "======================================\n";
  cout << "\t Withdraw Screen\n";
  cout << "======================================\n";
  
  vector<stClient> vClient = loadClientData_from_File(clientFile);
  string accountNum = getAccountNumber();

  stClient client;

  while(!findClient_by_AccountNumber(accountNum, vClient, client))
  {
    cout << "Client with Accout Number [ " <<accountNum<< " ] not found\n";
    accountNum = getAccountNumber(); 
  }   
  printClientRecord(client);

  double amount = 0;
  cout << "\nEnter Amount to Withdraw: ";
  cin >> amount;

  while(amount > client.balance)
  {
    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << client.balance << endl;
    cout << "please ener another amount: ";
    cin >> amount;
  }
   
  depositeOperation(accountNum, amount * -1, vClient);

}

void showTotalBalanceScreen()
{
  system("clear");
  cout << "======================================\n";
  cout << "\t Total Balance Screen\n";
  cout << "======================================\n";
  
  vector<stClient> vClient = loadClientData_from_File(clientFile);   
  printAllClientsBalance(vClient);
}

enum enTransactionOption
{
    deposit = 1, withdraw = 2, 
    totalBalance = 3, mainMenu = 4
}; 


void goBack2TransactionScreen()
{
    cout << "\nPress Ener to go back to transaction Screen..\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    showTransactionMenu();

}

short readTransactionOption()
{
    short num = 0;
    cout << "choose what do you want to do? [1 - 4] : ";
    cin >> num;
    return num;
}

void peformTransactionScreen(enTransactionOption option)
{
    switch(option)
    {
        case enTransactionOption::deposit :
        {
            showDepositScreen();
            goBack2TransactionScreen();
            break;
        }
        case enTransactionOption::withdraw : 
        {
            showWithdrawScreen();
            goBack2TransactionScreen();
            break;
        }
        case enTransactionOption::totalBalance : 
        {
            showTotalBalanceScreen();
            goBack2TransactionScreen();
            break;
        }
        case enTransactionOption::mainMenu :
        {
            showMainMenu();
            break;
        }
    }

}

void showTransactionMenu()
{
    if(!checkAccessPermission(enMainMenuPermissons::pTransaction))
    {
        showAccessDeniedMessage();
        goBack2MainMenu();
        return;
    }
    system("clear");
    cout << "==================================\n";
    cout << "\t transaction Screen.\n";
    cout << "==================================\n";
    cout << "\t[1] Deposite.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "==================================\n";
    peformTransactionScreen((enTransactionOption)readTransactionOption());
}

//--------------------------- [2] Manage User Screen ------------------------------


struct  stUser 
{
    string name;
    string password;
    int permission;
    bool mark4delete = false;
};

stUser currentUser;


string convertUserRecord2String(stUser user, string delim = "#//#")
{
    string word = "";

    word += user.name + delim;
    word += user.password + delim;
    word += to_string(user.permission); 

    return word;
}

stUser convertLine2UserRecord(string str, string delim = "#//#")
{
    stUser user;

    vector<string> vString = splitString(str, delim);

    user.name = vString[0];
    user.password = vString[1];
    user.permission = stoi(vString[2]);

    return user;
}

bool isUserNameExist(string userName, string fileName)
{
    fstream myFile;
    myFile.open(fileName, ios::in);

    if(myFile.is_open())
    {
        string line;
        stUser user;
        while(getline(myFile, line))
        {
            user = convertLine2UserRecord(line);
            if(user.name == userName)
            {
                myFile.close(); 
                return true;
            }
        }
        myFile.close();
    }
    return false;
}

int readPermissions()
{
    char ans = 'n';
    int permission = 0;

    cout << "\nDo You want to Read full Access? [Y/N] : ";
    cin >> ans; 

    if(ans == 'Y' || ans == 'y')
    {
        return -1;
    }

    cout << "\nDo You Want to give access to: \n";
    cout << "\nShow Client List? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pListClients;
    }

    cout << "\nAdd New Client? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pAddNewClient;
    }

    cout << "\nDelete client? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pDeleteClient;
    }

    cout << "\nUpdate Client? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pUpdateClient;
    }

    cout << "\nFind Client? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pFindClient;
    }

    cout << "\nTransaction? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pTransaction;
    }

    cout << "\nManage Users? [Y/N]: ";
    cin >> ans;
    if(ans == 'Y' || ans == 'y')
    {
        permission += enMainMenuPermissons::pManageUsers;
    }

    return permission;
}

stUser readUserInfo()
{
    stUser user;
    cout << "\nEnter username? : ";
    getline(cin >> ws, user.name);
    
    while(isUserNameExist(user.name, userFile))
    {
        cout << "This User [ " << user.name << " ] is Already Exist, Please Enter Another user: \n";
        getline(cin >> ws, user.name);
    }

    cout << "Enter Password? : ";
    getline(cin, user.password);
    
    user.permission = readPermissions();

    return user;
}

void saveUserLine2File(string fileName, string line)
{
    fstream myFile;
    myFile.open(fileName, ios::out | ios::app);

    if(myFile.is_open())
    {
        myFile << line << endl;
        myFile.close();
    }
}

void add_One_User()
{
    stUser user  = readUserInfo();
    saveUserLine2File(userFile, convertUserRecord2String(user));
}

void add_All_Users()
{
    char ans = 'n';

    do
    {
        cout << "\nAdding New User\n";
        add_One_User();
        cout << "\nUser Added Successfully, Do you want to add another User? [Y/N]: ";
        cin >> ans;
    } while (tolower(ans) == 'y');
    
}

vector<stUser> loadUserDataFromFile(string fileName)
{
    vector<stUser> vUsers;

    fstream myFile;
    myFile.open(fileName, ios::in);

    if(myFile.is_open())
    {
        stUser user;
        string line;

        while(getline(myFile, line))
        {
            user = convertLine2UserRecord(line);
            vUsers.push_back(user);
        }
        myFile.close();
    }

    return vUsers;
}

string getUserName()
{
    string str;
    cout << "Please Enter The Username ?: ";
    cin >> str;
    return str;
}

bool findUser_by_Username(string userName, vector<stUser> vUsers, stUser &user)
{
    for(stUser & c : vUsers)
    {
        if(c.name == userName)
        {
            user = c;
            return true;
        }
    }
    return false;
}

bool markUser4Delete_by_Username(string username, vector<stUser> &vUsers)
{
    for(stUser & c : vUsers)
    {
        if(c.name == username)
        {
            c.mark4delete = true;
            return true;
        }
    }
    return false;
}

vector<stUser> saveUserData2File(string fileName, vector<stUser> vUsers)
{
    fstream myFile;
    myFile.open(fileName, ios::out); // write new users only

    string line;

    if(myFile.is_open())
    {
        for(stUser & c : vUsers)
        {
            if(c.mark4delete == false)
            {
                myFile << convertUserRecord2String(c) << endl;
            }
        }

        myFile.close();
    }
    return vUsers;
}

void printUserCard(stUser user)
{
    cout << "\n### User Information ###\n";
    cout << "Username : " << user.name << endl;
    cout << "Password: " << user.password << endl;
    cout << "Permission: " << user.permission << endl;
}

bool deleteUser_by_Username(string userName, vector<stUser>&vUsers)
{
    if(userName == "Admin")
    {
        cout << "\nYou Can Not Delete This User.\n";
        return false;
    }

    char ans = 'n'; 
    stUser user;

    if(findUser_by_Username(userName, vUsers, user))
    {
        printUserCard(user);

        cout << "\n Do you want to delete User? [Y/N] : ";
        cin >> ans;
        if(tolower(ans) == 'y')
        {
            markUser4Delete_by_Username(userName, vUsers);
            saveUserData2File(userFile, vUsers); 
            // Refresh the vector with new user in file 
            vUsers = loadUserDataFromFile(userFile);

            cout << "\nUser Deleted Successfully.\n";
            return true;
        }
        return false;

    }else
    {
        cout << "\nUser with username [ " << userName << " ] Not Found!\n";
        return false;
    }
}

stUser getUserRecord2Update(string userName)
{
    stUser user;
    user.name = userName ;

    cout << "Enter User Password: ";
    getline(cin >> ws, user.password);

    user.permission = readPermissions();

    return user;
}

bool updateUser_by_UserName(string userName, vector<stUser> & vUsers)
{
    stUser user;
    char ans = 'n';

    if(findUser_by_Username(userName, vUsers, user))
    {
        printUserCard(user);

        cout << "\nDo You want to UPdate this User? [Y/N]: ";
        cin >> ans;
        if(tolower(ans) == 'y')
        {
            for(stUser & c : vUsers)
            {
                if(c.name == userName)
                {
                    c = getUserRecord2Update(userName);
                    break;
                }
            }
            saveUserData2File(userFile, vUsers);
            vUsers = loadUserDataFromFile(userFile);
            cout <<"\nUser Updated Successfully\n";
            return true;
        }
        return false;

    }else
    {
        cout << "User with UserName [ " << userName << " ] is Not Found!\n";
        return false;
    }
}

void printOneUser(stUser user)
{
    cout << "| " << left << setw(15) << user.name;
    cout << "| " << left << setw(15) << user.password;
    cout << "| " << left << setw(15) << user.permission;
}

void showAllUsersScreen()
{
    system("clear");
    vector<stUser> vUsers = loadUserDataFromFile(userFile);
    cout << "\n\t\tUsers Size is [ " << vUsers.size() << " ] user(s)\n";
    cout << "--------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Username";
    cout << "| " << left << setw(15) << "Password";
    cout <<  "| " << left << setw(15) << "Permission";
    cout << "\n------------------------------------------------\n";

    if(vUsers.size() == 0)
      cout << "NO Users Available\n";
    else 
        for(stUser & c : vUsers)
        {
            printOneUser(c);
            cout << endl;
        }
    cout << "--------------------------------------------------\n";

}

void showAddNewUserScreen()
{
    system("clear");
    cout << "===================================\n";
    cout << "\tAdd New User Screen\n";
    cout << "===================================\n";

    add_All_Users();
}

void showDeleteUserScreen()
{
    system("clear");
    cout << "===================================\n";
    cout << "\tDelete User Screen\n";
    cout << "===================================\n";

    string userName =  getUserName();
    vector<stUser> vUsers = loadUserDataFromFile(userFile);

    deleteUser_by_Username(userName, vUsers);
   
}

void showUpdateUserScreen()
{
    system("clear");
    cout << "===================================\n";
    cout << "\tUpdate User Screen\n";
    cout << "===================================\n";

    string userName = getUserName();
    vector<stUser> vUsers = loadUserDataFromFile(userFile);

    updateUser_by_UserName(userName, vUsers);

}

void showFindUserScreen()
{
    system("clear");
    cout << "===================================\n";
    cout << "\tFind User Screen\n";
    cout << "===================================\n";

    string userName = getUserName();
    vector<stUser> vUsers = loadUserDataFromFile(userFile);
    stUser user;

    if(findUser_by_Username(userName, vUsers, user))
        printUserCard(user);
    else
        cout << "\nuser with UserName [ " << userName << " ] Not Found!\n";
}



// --------------------------- manage user (front end) --------------------------

bool checkAccessPermission(enMainMenuPermissons permission)
{
    if(currentUser.permission == enMainMenuPermissons::pAll)
        return true;
    if((permission & currentUser.permission) == permission)
        return true;
    else
        return false;
}


short chooseManageOption()
{
    short num;
    cout << "Choose what you want to do? [1 - 6] : ";
    cin >> num;
    return num;
}

enum enManageUser
{
    elistUser = 1, eAddNewUser = 2,
    eDeleteUser = 3, eUpdateUser = 4,
    eFindUser = 5, eMainMenu = 6
}; 

void goback2ManageUser()
{
    cout <<"\nPress Any Key to go back to Manage User Menu....\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    showManageUsersScreen();
}

void performeManageUserScreen(enManageUser option)
{
    switch(option)
    {
        case enManageUser::elistUser :
        {
            showAllUsersScreen();
            goback2ManageUser();
            break; 
        }
        case enManageUser::eAddNewUser :
        {
            showAddNewUserScreen();
            goback2ManageUser();
            break;
        }
        case enManageUser::eDeleteUser :
        {
            showDeleteUserScreen();
            goback2ManageUser();
            break;
        }
        case enManageUser::eUpdateUser : 
        {
            showUpdateUserScreen();
            goback2ManageUser();
            break;
        }
        case enManageUser::eFindUser :
        {
            showFindUserScreen();
            goback2ManageUser();
            break;
        }
        case enManageUser::eMainMenu :
        {
            showMainMenu();
        }
    }
}

void showManageUsersScreen()
{
    if(!checkAccessPermission(enMainMenuPermissons::pManageUsers))
    {
        showAccessDeniedMessage();
        goBack2MainMenu();
        return;
    }

    system("clear"); 
    cout << "===============================================\n";
    cout << "\t Manage Users Menu Screen\n";
    cout << "===============================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===============================================\n";
    performeManageUserScreen((enManageUser)chooseManageOption());
}



//--------------------------- [2] End Manage User Screen ------------------------------

//-------------------------- [3] Main Menu Screen -----------------------------------
enum enMenuOptions
{
    eShowAllClients = 1, eAddClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransaction = 6,
    eManageUsers = 7, eLogout = 8
}; 

void goBack2MainMenu()
{
    cout << "\nPress Enter to go back to Main Menu....";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    showMainMenu(); 
}

short readMainMenuOption()
{
    short num;
    cout << "Choose What do you want to do ? [1 - 8] : ";
    cin >> num;
    return num;
} 

void performMainMenuOptoin(enMenuOptions option)
{
    switch(option)
    {
        case enMenuOptions::eShowAllClients :
        {
            showAllClientsScreen();
            goBack2MainMenu();
            break;
        }
        case enMenuOptions::eAddClient :
        {
            showAddNewClientScreen();
            goBack2MainMenu();
            break;
        }
        case enMenuOptions::eDeleteClient :
        {
            showDeleteClientScreen();
            goBack2MainMenu();
            break;
        }
        case enMenuOptions::eUpdateClient :
        {
            showUpdateClientScreen();
            goBack2MainMenu();
            break;
        }
        case enMenuOptions::eFindClient :
        {
            showFindClientByAccountNumberScreen();
            goBack2MainMenu();
            break;
        }
        case enMenuOptions::eTransaction :
        {
            showTransactionMenu();
            break;
        }
        case enMenuOptions::eManageUsers :
        {
            showManageUsersScreen();
            break;
        }
        case enMenuOptions::eLogout  :
        {
            showLogoutScren();
            break;
        }
    }
}

bool findUser_by_userName_and_Password(string userName, string password, stUser & user)
{
    vector<stUser> vUsers = loadUserDataFromFile(userFile); 

    for(stUser & c : vUsers)
    {
        if(c.name == userName && c.password == password)
        {
            user = c;
            return true;
        }
    }

    return false;
}

bool loadUserInfo(string userName, string password)
{
    if(findUser_by_userName_and_Password(userName, password, currentUser))
      return true;
    else
      return false;
}


void showMainMenu()
{ 
    system("clear");
    cout << "\033[96m";
    cout << "\033[1m";
    cout <<"===============================================\n";
    cout <<"\t\t Main Menu Screen\n";
    cout <<"===============================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n"; 
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n"; 
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout <<"===============================================\n";
    performMainMenuOptoin((enMenuOptions)readMainMenuOption());
}

void longIn()
{
    bool longinFaild = false;
    string userName, password;


    do
    {
        system("clear");
        cout << "----------------------------------------------\n";
        cout << "\t\t\033[1mLogin Screen\n";
        cout << "\n---------------------------------------------\n";

        if(longinFaild)
        {
            cout << "\nInvalid Username/Password.\n";
        }
        
        cout << "Enter User Name: ";
        cin >> userName;
        cout << "Enter Password: ";
        cin >> password;

        longinFaild = !loadUserInfo(userName, password);

    } while (longinFaild);
    
     
    showMainMenu(); 

}



int main()
{
    longIn();
// showAddNewUserScreen();
// showAllUsersScreen();
// showDeleteUserScreen();
// showUpdateUserScreen();
// showFindUserScreen();
    return 0;
}


/*  

--------------- Linux system color code -----------
const string RESET   = "\033[0m";
const string RED     = "\033[91m";
const string GREEN   = "\033[92m";
const string YELLOW  = "\033[93m";
const string BLUE    = "\033[94m";
const string CYAN    = "\033[96m";
const string WHITE   = "\033[97m";
const string BOLD    = "\033[1m";


*/