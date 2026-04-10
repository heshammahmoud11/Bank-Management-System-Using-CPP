#include<iostream>
#include<limits>
#include<vector>
#include<fstream>
#include<string>
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

void showAddNewClientScreen()
{
    system("clear");
    cout << "\n====================================\n";
    cout << "\t Adding New client Screen";
    cout << "\n====================================\n";
    add_All_Clients2File();
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
 showAddNewClientScreen();

    return 0;
}