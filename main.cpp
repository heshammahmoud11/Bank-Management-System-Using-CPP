#include<iostream>
#include<limits>
#include<vector>
#include<iomanip>
#include<fstream>
using namespace std;

void showMainMenu(); 
const string clientFile = "client.txt";
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
    client.balance = stoi(vString[4]);

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
            cout << "Client Added Successfully, Do you want to add more Clients? [Y/N]: ";
            cin >> ans;
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

    cout << "\n\t The Client Size [ " << vClient.size() << " ] Client(s)\n";
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

void showAddNewClientScreen()
{
    system("clear");
    cout << "\n====================================\n";
    cout << "\t Adding New client Screen";
    cout << "\n====================================\n";
    add_All_Clients2File();
}

void showAllClientsScreen()
{
    system("clear");
    cout << "\n====================================\n";
    cout << "\t Show All clients Screen";
    cout << "\n====================================\n";

    print_All_Clients();

}

// ---------------------------- Front End ------------------------------

enum enMenuOptions
{
    eShowClient = 1, eAddClient = 2,
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

short chooseOption()
{
    short num;
    cout << "Choose What do you want to do ? [1 : 8] : ";
    cin >> num;
    return num;
}

void showMainMenu()
{
    system("clear");
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
}

int main()
{
 // showMainMenu();
 //showAddNewClientScreen();
 showAllClientsScreen();

    return 0;
}