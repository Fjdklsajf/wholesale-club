#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "member.h"
#include "set.h"
#include "date.h"
#include "receipt.h"
#include "item.h"

using namespace std;

/*******************************************************************************
 *  printMoney
 *    Return a string of the value given in money format (ex. $23.85)
 *    - returns std::string
 ******************************************************************************/
std::string printMoney(double num);

/*******************************************************************************
 *  idComparison
 *    Returns true if a's id is smaller than b's
 *    - returns bool
 ******************************************************************************/
bool idComparison(Member &a, Member& b);

/*******************************************************************************
 *  nameComparison
 *    Returns true if a's name is smaller than b's
 *    - returns bool
 ******************************************************************************/
bool nameComparison(Member &a, Member& b);

/******************************************************************************
 *
 *  Constructor MainWindow
 *_____________________________________________________________________________
 *  initialize variables and set up Ui
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    varibles are initalized and mainwindow is set up
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    pullFromMemberFile();
    pullFromSalesFiles();
    ui->setupUi(this);
    ui->endDate->setVisible(false);
    ui->endLabel->setVisible(false);
    ui->startLabel->setText("Date");
    ui->idEntry->setValidator(new QIntValidator(0, 99999, this) );
    ui->yearEntry->setValidator(new QIntValidator(0, 9999, this) );
    QRegExp rx("^[a-zA-Z ]+$");
    ui->nameEntry->setValidator(new QRegExpValidator(rx, this));
    ui->yearEntry->setVisible(false);
    fillMemberComboBox();
    fillMemberComboBox2();
}

/******************************************************************************
 *
 *  Destructor MainWindow
 *_____________________________________________________________________________
 *  Update members file and delete Ui
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    members file is updated and ui is deleted
 *****************************************************************************/
MainWindow::~MainWindow()
{
    writeToMemberFile();
    delete ui;
}

/******************************************************************************
 *
 *  Accessor getBasic: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return basic members
 *  - returns Set
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    basic members are returned
 *****************************************************************************/
Set MainWindow::getBasic()
{
    Set retVal;
    for (unsigned long i =0;i< members.length();i++)
    {
        if (members[i].isBasic())
            retVal.insert(members[i]);
    }
    return retVal;
}

/******************************************************************************
 *
 *  Accessor getPreferred: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return preferred members
 *  - returns Set
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    preferred members are returned
 ******************************************************************************/
Set MainWindow::getPreferred()
{
    Set retVal;
    for (unsigned long i =0;i< members.length();i++)
    {
        if (!(members[i].isBasic()))
            retVal.insert(members[i]);
    }
    return retVal;
}

/******************************************************************************
 *
 *  Accessor getAllMembers: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return all members
 *  - returns Set
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    all members are returned
 ******************************************************************************/
Set MainWindow::getAllMembers()
{
    return members;
}

/******************************************************************************
 *
 *  Accessor getMember: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return the member with given id
 *  - returns Member&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    member with given id exist in members
 *
 *  POST-CONDITIONS
 *    Member with given id is returned
 ******************************************************************************/
Member & MainWindow::getMember(int id)
{
    for (unsigned long i = 0; i < members.length();i++)
    {
        if (members[i].getId() == id)
            return members[i];
    }
}

/******************************************************************************
 *
 *  Accessor getMember: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return the member with given name
 *  - returns Member&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    member with given name exist in members
 *
 *  POST-CONDITIONS
 *    Member with given name is returned
 ******************************************************************************/
Member & MainWindow::getMember(string name)
{
    for (unsigned long i = 0; i < members.length();i++)
    {
        if (members[i].getName() == name)
            return members[i];
    }
}

/******************************************************************************
 *
 *  Method pullFromMemberFile: Class MainWindow
 *_____________________________________________________________________________
 *  extract member information from the file and add each of them to the set
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    members are updated
 ******************************************************************************/
void MainWindow::pullFromMemberFile()
{
    std::ifstream inputFile;
    inputFile.open("memberFile.txt");
    if(inputFile.fail()){
        std::cout << "File Not Found" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::string name;
        std::string idString;
        std::string memberStatus;
        std::string monthString;
        std::string dayString;
        std::string yearString;
        int month;
        int day;
        int year;
        unsigned int id;
        bool isBasic;
        while(inputFile.good())
        {
            getline(inputFile, name, '\n');
            getline(inputFile, idString, '\n');
            getline(inputFile, memberStatus, '\n');
            getline(inputFile, monthString, '/');
            getline(inputFile, dayString, '/');
            getline(inputFile, yearString, '\n');
            month = std::stoi(monthString);
            day = std::stoi(dayString);
            year = std::stoi(yearString);
            id = std::stoi(idString);
            if (memberStatus == "Basic")
                isBasic = true;
            else
                isBasic = false;
            members.insert(Member(name,id,0,Date(day,month,year), isBasic));
        }
        inputFile.close();
    }
}

/******************************************************************************
 *
 *  Method writeToMemberFile: Class MainWindow
 *_____________________________________________________________________________
 *  write each member's information back to the memeber file
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    members file is updated
 ******************************************************************************/
void MainWindow::writeToMemberFile()
{

    std::ofstream outputFile("memberFile.txt");
    std::string memberStatus;

    for (unsigned long i = 0; i < members.length();i++)
    {
        outputFile << members[i].getName() << std::endl;
        outputFile << members[i].getId() << std::endl;
        if (members[i].isBasic())
            memberStatus = "Basic";
        else
            memberStatus = "Preferred";
        outputFile << memberStatus << std::endl;
        outputFile << members[i].getExpDate().getMonth() << "/";
        outputFile << members[i].getExpDate().getDate() << "/";
        outputFile << members[i].getExpDate().getYear() << std::endl;
    }
    outputFile.close();
}

/******************************************************************************
 *
 *  Method pullFromSalesFiles: Class MainWindow
 *_____________________________________________________________________________
 *  extract all available sales files, create receipts based on items purchased
 *      and add them to appropriate members
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Sales are added to corresponding members
 ******************************************************************************/
void MainWindow::pullFromSalesFiles()
{
    ifstream myFile;
    myFile.open("Sale_day1.txt");
    string name;
    double price;
    string stringDate, stringMonth, stringYear;
    int date, month, year;
    int quantity;
    int id;
    if (myFile.is_open())
    {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();

           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
    }

    else cout << "Unable to open file1";
    myFile.open("Sale_day2.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file2";
    myFile.open("Sale_day3.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file3";
    myFile.open("Sale_day4.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file4";
    myFile.open("Sale_day5.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file5";
    myFile.open("Sale_day6.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file6";
    myFile.open("Sale_day7.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file7";
    myFile.open("Sale_day8.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file8";
    myFile.open("Sale_day9.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file9";
    myFile.open("Sale_day10.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file10";
    myFile.open("Sale_day11.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file11";
    myFile.open("Sale_day12.txt");
    if (myFile.is_open())
     {
       while (!myFile.eof())
       {
           getline(myFile,stringMonth,'/');
           month = stoi(stringMonth);
           getline(myFile,stringDate, '/');
           date = stoi(stringDate);
           getline(myFile,stringYear, '\n');
           year = stoi(stringYear);
           myFile>>id;
           myFile.ignore();
           getline(myFile,name,'\n');
           myFile>>price;
           myFile>>quantity;
           myFile.ignore();
           Member temp;
           temp.setId(id);
           if (members.contains(temp))
           {
           getMember(id).addReceipt(Receipt(Date(date,month,year),
                                            Item(name,price),quantity));
           }
       }
       myFile.close();
     }
    else cout << "Unable to open file12";
}

/******************************************************************************
 *
 *  Method fillMemberComboBox: Class MainWindow
 *_____________________________________________________________________________
 *  Display each existing member's name and id in the combo box, 
 *      sorted by their names. Used for removeMember
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    All members are shown through the combo box
 ******************************************************************************/
void MainWindow::fillMemberComboBox()
{
    ui->memberComboBox->clear();
    ui->memberComboBox->insertItem(0,"Select Member");
    members.sort(nameComparison);
    for (size_t i = members.length()-1; i > 0;i--)
    {
        ui->memberComboBox->insertItem(1, QString::fromStdString(to_string(members[i].getId()) + "-" + members[i].getName()));
    }
    ui->memberComboBox->insertItem(1, QString::fromStdString(to_string(members[0].getId()) + "-" + members[0].getName()));
}

/******************************************************************************
 *
 *  Method fillMemberComboBox2: Class MainWindow
 *_____________________________________________________________________________
 *  Display each existing member's name and id in the combo box, 
 *      sorted by their names. Used for removeMember
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    All members are shown through the combo box
 ******************************************************************************/
void MainWindow::fillMemberComboBox2()
{
    ui->memberComboBox2->clear();
    ui->memberComboBox2->insertItem(0,"Select Member");
    members.sort(nameComparison);
    for (size_t i = members.length()-1; i > 0;i--)
    {
        ui->memberComboBox2->insertItem(1, QString::fromStdString(to_string(members[i].getId()) + "-" + members[i].getName()));
    }
    ui->memberComboBox2->insertItem(1, QString::fromStdString(to_string(members[0].getId()) + "-" + members[0].getName()));
}

/******************************************************************************
 *
 *  Method removeMember: Class MainWindow
 *_____________________________________________________________________________
 *  member with the given id is remove from the Set of members
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a member is removed and combo boxes are updated
 ******************************************************************************/
void MainWindow::removeMember(int id)
{
    Member memberToRemove = Member();
    memberToRemove.setId(id);
    members.erase(memberToRemove);
    fillMemberComboBox();
    fillMemberComboBox2();
}

/******************************************************************************
 *
 *  Method displayDailySales: Class MainWindow
 *_____________________________________________________________________________
 *  Display sales on a given Date and members type. 
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    d is valid
 *    flag == 'a' || flag == 'b || flag == 'p
 *
 *  POST-CONDITIONS
 *    daily sales display is returned as a string
 ******************************************************************************/
std::string MainWindow::displayDailySales(const Date& d,char flag) {
    std::string display;
    Receipt totalReceipt;
    Set membersToQuery;
    if (flag == 'a')
        membersToQuery = members;
    if (flag == 'b')
        membersToQuery = getBasic();
    if (flag == 'p')
        membersToQuery = getPreferred();
    Set validMembers,totalShoppers;
    int numOfBasic = 0, numOfPreferred = 0;

    for(std::size_t i = 0; i < membersToQuery.length(); i++) {
        std::vector<Receipt> temp = membersToQuery[i].getReceipts();
        for(auto it = temp.begin(); it != temp.end(); it++) {
            if(it->getDate() == d) {
                totalReceipt += *it;
                validMembers.insert(membersToQuery[i]);
            }
        }
    }
    for(std::size_t i = 0; i < members.length(); i++) {
        std::vector<Receipt> temp = members[i].getReceipts();
        for(auto it = temp.begin(); it != temp.end(); it++) {
            if(it->getDate() == d) {
                totalShoppers.insert(members[i]);
            }
        }
    }

    if(validMembers.length() == 0) {
        return "No sales for that type of member on that day\n";
    }

    for(std::size_t i = 0; i < totalShoppers.length(); i++) {
        if(totalShoppers[i].isBasic()) {
            numOfBasic++;
        }
    }
    numOfPreferred = totalShoppers.length() - numOfBasic;

    display += d.printMonth() + ' ' + to_string(d.getDate());
    display += ", ";
    display += to_string(d.getYear());

    display += "\n\nItems sold:\n";

    std::map<Item, int> items = totalReceipt.getItems();
    for(auto it = items.begin(); it != items.end(); it++) {
        display += it->first.getName();
        display += " ($";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << it->first.getPrice();
        std::string price = stream.str();
        display += price;
        display += ")  x ";
        display += to_string(it->second);
        display += '\n';
    }
    display += "Total Revenue: $";
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << totalReceipt.totalCost();
    std::string totalCost = stream.str();
    display += totalCost;
    display += "\n\n";

    validMembers.sort(nameComparison);
    display += "Members of the Selected Type:\n";
    for(std::size_t i = 0; i < validMembers.length(); i++) {
        display += validMembers[i].getName();
        display += "\n";
    }
    display += "Number of Basic Members: ";
    display += to_string(numOfBasic);
    display += "\nNumber of Preferred Members: ";
    display += to_string(numOfPreferred);
    display += "\n\n";

    return display;
}

/******************************************************************************
 *
 *  Method getItemQuantities: Class MainWindow
 *_____________________________________________________________________________
 *  Display all items purchased by the given member type, sorted by item name
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    flag == 'a' || flag == 'b || flag == 'p
 *
 *  POST-CONDITIONS
 *    item quantities display is returned as a string
 ******************************************************************************/
std::string MainWindow::getItemQuantities(char flag)
{
    std::string display;
    Receipt totalReceipt;
    Set membersToQuery;
    if (flag == 'a')
        membersToQuery = members;
    if (flag == 'b')
        membersToQuery = getBasic();
    if (flag == 'p')
        membersToQuery = getPreferred();
    Set validMembers,totalShoppers;

    for(std::size_t i = 0; i < membersToQuery.length(); i++) {
        std::vector<Receipt> temp = membersToQuery[i].getReceipts();
        for(auto it = temp.begin(); it != temp.end(); it++) {
            {
                totalReceipt += *it;
            }
        }
    }
    display += "Items sold:\n\n";

    std::map<Item, int> items = totalReceipt.getItems();
    for(auto it = items.begin(); it != items.end(); it++) {
        display += it->first.getName();
        display += " ($";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << it->first.getPrice();
        std::string price = stream.str();
        display += price;
        display += ")  x ";
        display += to_string(it->second);
        display += '\n';
    }

    return display;
}

/******************************************************************************
 *
 *  Method getAllMemberPurchases: Class MainWindow
 *_____________________________________________________________________________
 *  Display all member purchases based on the given member flag.
 *      Each member activated by the flag will have all their past purchases
 *      displayed. A grand total of all purchased amount will also be displayed.
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    flag == 'a' || flag == 'b || flag == 'p
 *
 *  POST-CONDITIONS
 *    member purcahses display is returned as a string
 ******************************************************************************/
string MainWindow::getAllMemberPurchases(char flag)
{
    std::string display;
    display += "All Member Purchases\n\n";
    Receipt totalReceipt;
    Set membersToQuery;
    if (flag == 'a')
        membersToQuery = members;
    if (flag == 'b')
        membersToQuery = getBasic();
    if (flag == 'p')
        membersToQuery = getPreferred();
    membersToQuery.sort(idComparison);
    for(std::size_t i = 0; i < membersToQuery.length(); i++) {
        Receipt memberTotalReceipt;
        std::vector<Receipt> temp = membersToQuery[i].getReceipts();
        for(auto it = temp.begin(); it != temp.end(); it++) {
            memberTotalReceipt += *it;
            totalReceipt += *it;
        }
        display += "(";
        display += to_string(membersToQuery[i].getId());
        display += ") ";
        display += membersToQuery[i].getName() +="\n";
        if (temp.size() == 0)
        {
            display += "No Purchases For This Member";
        }
        std::map<Item, int> items = memberTotalReceipt.getItems();
        for(auto it = items.begin(); it != items.end(); it++) {
            display += it->first.getName();
            display += " ($";
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << it->first.getPrice();
            std::string price = stream.str();
            display += price;
            display += ")  x ";
            display += to_string(it->second);
            display += '\n';
        }
        display += "\n\n";
    }
    display += "\n\n\nGrand Total: ";
    std::map<Item, int> items = totalReceipt.getItems();
    double grandTotal = 0;
    for(auto it = items.begin(); it != items.end(); it++) {
        grandTotal += (it->second)*(it->first.getPrice());
    }
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << grandTotal;
    std::string total = stream.str();
    display += "$ ";
    display += total;
    return display;
}

/******************************************************************************
 *
 *  Method getYearlyReport: Class MainWindow
 *_____________________________________________________________________________
 *  Get all purcahses in the given year and given member flag. Status of every
 *      item sold is shown. the worst item, best item, as well as total revenue 
 *      are also displayed. 
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *      Year must be between 1980 and 2080
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    year >= 1980 && year <= 2080
 *    flag == 'a' || flag == 'b || flag == 'p
 *
 *  POST-CONDITIONS
 *    yearly report display is returned as a string
 ******************************************************************************/
std::string MainWindow::getYearlyReport(int year, char flag) {
    Set membersToQuery;
    if (flag == 'a')
        membersToQuery = members;
    if (flag == 'b')
        membersToQuery = getBasic();
    if (flag == 'p')
        membersToQuery = getPreferred();
    if(year < 1980 || year > 2080) {
        return "Invalid year\n";
    } else if (membersToQuery.length() <= 0) {
        return "No Items Sold in that Year\n";
    }

    std::string display;
    Receipt combined;

    for(size_t i = 0; i < membersToQuery.length(); i++) {
        auto receipts = membersToQuery[i].getReceipts();
        for(auto it = receipts.begin(); it != receipts.end(); it++) {
            if(it->getDate().getYear() == year) {
                combined += *it;
            }
        }
    }
    if(combined.itemsSize() <= 0) {
        return "No Items Sold in that Year\n";
    }

    auto items = combined.getItems();
    std::map<Item, int>::iterator best, worst;
    double bestRevenue, worstRevenue, totalRevenue;
    best = items.begin();
    worst = items.begin();
    bestRevenue = combined.getItemCost(best->first);
    worstRevenue = combined.getItemCost(worst->first);
    totalRevenue = combined.totalCost();

    for(auto it = items.begin(); it != items.end(); it++) {
        double revenue = combined.getItemCost(it->first);
        if(revenue > bestRevenue) {
            bestRevenue = revenue;
            best = it;
        }
        if(revenue < worstRevenue) {
            worstRevenue = revenue;
            worst = it;
        }
    }

    display = combined.printItems();
    display += "\nWorst Item: " + worst->first.getName() + '(' + printMoney(worst->first.getPrice()) + ") x"
            + std::to_string(worst->second) + '\n';
    display += "Total: " + printMoney(worstRevenue) + "\n\n";
    display += "Best Item: " + best->first.getName() + '(' + printMoney(best->first.getPrice()) + ") x"
            + std::to_string(best->second) + '\n';
    display += "Total: " + printMoney(bestRevenue) + "\n\n";
    display += "Total Revenue: " + printMoney(totalRevenue) + '\n';

    return display;
}

/******************************************************************************
 *
 *  Method getRebateReport: Class MainWindow
 *_____________________________________________________________________________
 *  The rebate amount of every preferred members are displayed.
 *      Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *
 *  POST-CONDITIONS
 *    rebate report display is returned as a string
 ******************************************************************************/
string MainWindow::getRebateReport()
{
    Set preferredMembers = getPreferred();
    preferredMembers.sort(idComparison);
    string display;
    display += "Rebate Report:\n\n";
    for (size_t i =0;i<preferredMembers.length();i++)
    {
        display += "(";
        display += to_string(preferredMembers[i].getId());
        display +=") ";
        display += preferredMembers[i].getName();
        display +="\n";
        display +="Rebate Amount: ";
        std::stringstream stream;
        double rebate = (preferredMembers[i].getTotalSpent()*.05)/1.0875;

        stream << std::fixed << std::setprecision(2) << rebate;
        display += stream.str();
        display += "\n\n";
    }
    return display;
}

/******************************************************************************
 *
 *  Method getMemberPurchases: Class MainWindow
 *_____________________________________________________________________________
 *  Display all past purchases of a given member.
 *      Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    desiredMember exists in members
 *
 *  POST-CONDITIONS
 *    member puchase display is returned as a string
 ******************************************************************************/
std::string MainWindow::getMemberPurchases(Member desiredMember)
{
    Receipt memberTotalReceipt;
    string display;
    std::vector<Receipt> temp = desiredMember.getReceipts();
    for(auto it = temp.begin(); it != temp.end(); it++) {
        memberTotalReceipt += *it;
    }
    display += "(";
    display += to_string(desiredMember.getId());
    display += ") ";
    display += desiredMember.getName() +=":\n\n";
    if (temp.size() == 0)
    {
        display += "No Purchases For This Member";
    }
    std::map<Item, int> items = memberTotalReceipt.getItems();
    for(auto it = items.begin(); it != items.end(); it++) {
        display += it->first.getName();
        display += " ($";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << it->first.getPrice();
        std::string price = stream.str();
        display += price;
        display += ")  x ";
        display += to_string(it->second);
        display += '\n';
    }
    display += "\n\n";
    return display;
}

/******************************************************************************
 *
 *  Method getMemberDues: Class MainWindow
 *_____________________________________________________________________________
 *  For members with given expiration month and fits the member flag,
 *      display their expected dues ($60 / $75). Sorted by names.
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    month >= 1 && month <= 12
 *    flag == 'a' || flag == 'b || flag == 'p
 *
 *  POST-CONDITIONS
 *    member dues of a given month's display is returned as a string
 ******************************************************************************/
std::string MainWindow::getMemberDues(int month, char flag) {
    std::string display;
    Set basic, preferred, validBasic, validPreferred;
    basic = getBasic();
    preferred = getPreferred();
    if (flag == 'b' || flag == 'a'){
        for(std::size_t i = 0; i < basic.length(); i++) {
            if(basic[i].getExpDate().getMonth() == month) {
                validBasic.insert(basic[i]);
            }
        }
    }

    if (flag == 'p' || flag == 'a')
    {
        for(std::size_t i = 0; i < preferred.length(); i++) {
            if(preferred[i].getExpDate().getMonth() == month) {
                validPreferred.insert(preferred[i]);
            }
        }
    }
    if((validBasic.length() == 0) && (validPreferred.length() == 0)){
            return "No members with dues that month.\n";
        }
    validBasic.sort(nameComparison);
    validPreferred.sort(nameComparison);

    switch(month) {
        case 1:
            display = "January:\n\n";
            break;
        case 2:
            display = "February:\n\n";
            break;
        case 3:
            display = "March:\n\n";
            break;
        case 4:
            display = "April:\n\n";
            break;
        case 5:
            display = "Mar:\n\n";
            break;
        case 6:
            display = "June:\n\n";
            break;
        case 7:
            display = "July:\n\n";
            break;
        case 8:
            display = "August:\n\n";
            break;
        case 9:
            display = "September:\n\n";
            break;
        case 10:
            display = "October:\n\n";
            break;
        case 11:
            display = "November:\n\n";
            break;
        default:
            display = "December:\n\n";
            break;
    }

    if (flag == 'b' || flag == 'a')
    {
        display += "Basic Members:\n";
        for(std::size_t i = 0; i < validBasic.length(); i++) {
            display += "Name: ";
            display += validBasic[i].getName();
            display += "\nDues: $60.00";
            display += "\n\n";
        }
    }
    if (flag == 'a')
    {
        display += "\n";
    }
    if (flag == 'p' || flag == 'a')
    {
        display += "Preferred Members:\n";
        for(std::size_t i = 0; i < validPreferred.length(); i++) {
            display += "Name: ";
            display += validPreferred[i].getName();
            display += "\nDues: $75.00";
            display += "\n\n";
        }
    }
    return display;
}

/******************************************************************************
 *
 *  Method getMemberDues: Class MainWindow
 *_____________________________________________________________________________
 *  Display members in the member flag their expected dues, sorted by names.
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    flag == 'a' || flag == 'b || flag == 'p
 *
 *  POST-CONDITIONS
 *    all member dues display is returned as a string
 ******************************************************************************/
string MainWindow::getMemberDues(char flag)
{
    Set basic = getBasic();
    Set preferred = getPreferred();
    string retVal;
    basic.sort(nameComparison);
    preferred.sort(nameComparison);

    if ((flag == 'a')|| (flag == 'b'))
    {
        retVal += "Basic:\n";
        for (unsigned long i = 0; i< basic.length();i++)
        {
            retVal += "Name: ";
            retVal += basic[i].getName();
            retVal += ", Dues: $60.00\n\n";
        }
    }

    if ((flag == 'a') || (flag == 'p'))
    {
        retVal += "Preferred:\n";
        for (unsigned long i = 0; i< preferred.length();i++)
        {
            retVal += "Name: ";
            retVal += preferred[i].getName();
            retVal += ", Dues: $75.00\n\n";
        }
    }

    return retVal;
}


/******************************************************************************
 *
 *  void MainWindow::on_generateReportButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the generate report button is clicked. It fills
 *  in the report area with the appropriate report
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The report has been generated and filled into the text box
 *****************************************************************************/
void MainWindow::on_generateReportButton_clicked()
{
    int selection = ui -> reportComboBox -> currentIndex() + 1;
    Date start = Date(ui->startDate->date().day(),
                      ui->startDate->date().month(),
                      ui->startDate->date().year());
    Date end = Date(ui->endDate->date().day(),ui->endDate->date().month(),
                    ui->endDate->date().year());
    char flag;
    if (ui->allMembersSelector->isChecked())
    {
        flag = 'a';
    }
    if (ui->basicMembersSelector->isChecked())
    {
        flag = 'b';
    }
    if (ui->preferredMembersSelector->isChecked())
    {
        flag = 'p';
    }
    switch(selection)
    {

    //daily sales report
    case 1:
        ui->reportArea->setText(QString::fromStdString(displayDailySales(start,flag)));
        break;
    case 2:
        ui->reportArea->setText(QString::fromStdString(getMemberDues(flag)));
        break;
    case 3:
        ui->reportArea->setText(QString::fromStdString(getItemQuantities(flag)));
        break;
    case 4:
        ui->reportArea->setText(QString::fromStdString(getAllMemberPurchases(flag)));
        break;
    case 5:
    {
        int year = (ui->yearEntry->text()).toInt();
        ui->reportArea->setText(QString::fromStdString(getYearlyReport(year,flag)));
        break;
    }
    case 6:
        ui->reportArea->setText(QString::fromStdString(getRebateReport()));
        break;
    }
}


/******************************************************************************
 *
 *  void MainWindow::on_reportComboBox_currentIndexChanged(int index)
 *_____________________________________________________________________________
 *  This slot is triggered when index changes on the report combobox
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The index has changed on the report combobox
 *****************************************************************************/
void MainWindow::on_reportComboBox_currentIndexChanged(int index)
//IN - the current index post change
{
    ui->endDate->setVisible(false);
    ui->startDate->setVisible(false);
    ui->startLabel->setVisible(false);
    ui->endLabel->setVisible(false);
    ui->yearEntry->setVisible(false);
    ui->basicMembersSelector->setVisible(true);
    ui->allMembersSelector->setVisible(true);
    ui->preferredMembersSelector->setVisible(true);
    ui->memberSelectorLabel->setVisible(true);
    ui->reportArea->setText("");
    switch (index +1)
    {
    case 1:
        ui->endDate->setVisible(true);
        ui->startDate->setVisible(true);
        ui->startLabel->setText("Date");
        ui->endDate->setVisible(false);
        ui->endLabel->setVisible(false);
        ui->startLabel->setText("Date");
        break;
    case 5:
        ui->startLabel->setVisible(true);
        ui->startLabel->setText("Year");
        ui->yearEntry->setVisible(true);
        break;
    case 6:
        ui->basicMembersSelector->setVisible(false);
        ui->allMembersSelector->setVisible(false);
        ui->preferredMembersSelector->setVisible(false);
        ui->memberSelectorLabel->setVisible(false);
        break;
    }
}

/******************************************************************************
 *
 *  void MainWindow::on_getDuesButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the get dues button is clicked
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The dues are displayed in the appropriate area
 *****************************************************************************/
void MainWindow::on_getDuesButton_clicked()
{
    char flag;
    if (ui->allMembersSelectorExpDues->isChecked())
    {
        flag = 'a';
    }
    if (ui->basicMembersSelectorExpDues->isChecked())
    {
        flag = 'b';
    }
    if (ui->preferredMembersSelectorExpDues->isChecked())
    {
        flag = 'p';
    }

    ui->duesForMonthTextArea->setText(QString::fromStdString(getMemberDues(ui->monthSelector->value(),flag)));

}


/******************************************************************************
 *
 *  void MainWindow::on_addMemberButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the add member button is clicked
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The member with the specified attributes has been added
 *****************************************************************************/
void MainWindow::on_addMemberButton_clicked()
{
    if ((ui->nameEntry->text() == "") ||(ui->idEntry->text() == ""))
        return;
    string name = ui->nameEntry->text().toStdString();
    int id = ui->idEntry->text().toInt();
    bool isBasic = true;
    if (ui->typeComboBox->currentText() == "Preferred")
        isBasic = false;
    Date expDate = Date(ui->expDateEntry->date().day(),
                        ui->expDateEntry->date().month(),
                        ui->expDateEntry->date().year());
    members.insert(Member(name,id,0,expDate,isBasic));
    ui->nameEntry->setText("");
    ui->idEntry->setText("");
    fillMemberComboBox();
    fillMemberComboBox2();
}

/******************************************************************************
 *
 *  void MainWindow::on_removeMemberButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the remove member button is clicked
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The selected member has been removed
 *****************************************************************************/
void MainWindow::on_removeMemberButton_clicked()
{
    if (ui->memberComboBox->currentText() == "Select Member"){
        return;
    }
    removeMember(stoi(ui->memberComboBox->currentText().toStdString().substr(0,5)));
}

/******************************************************************************
 *
 *  void MainWindow::on_determineWorthButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the determine worth button is clicked
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The text area underneath the button has been filled with info specifying
 *    whether or not the member should switch memberships
 *****************************************************************************/
void MainWindow::on_determineWorthButton_clicked()
{
    if (ui->memberComboBox2->currentText() == "Select Member")
    {
        return;
    }
    Member selectedMember = getMember(stoi(ui->memberComboBox2->currentText().toStdString().substr(0,5)));
    double amountSpent = (selectedMember.getTotalSpent())/1.0875;
    double rebateAmount = amountSpent*.05;
    string display;
    if(selectedMember.isBasic())
    {
        display += "That member is currently a basic member.\n\n";
        if (rebateAmount >15)
        {
            display += "That member should switch to a premium membership.";
        }
        else
        {
            display += "That member should remain a basic member.";
        }
    }
    else
    {
        display += "That member is currently a premium member.\n\n";
        if (rebateAmount > 15)
        {
            display += "That member should remain a premium member.";
        }
        else
        {
            display += "That member should switch to a basic membership.";
        }
    }
    ui->membershipWorthField->setText(QString::fromStdString(display));
}

/******************************************************************************
 *
 *  void MainWindow::on_itemSearchButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the item search button is clicked
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The quantity and price boxes have been filled with the appropriate
 *    information
 *****************************************************************************/
void MainWindow::on_itemSearchButton_clicked()
{
    string itemName = ui->itemNameEntry->text().toStdString();
    itemName[0] = toupper(itemName[0]);
    bool found = false;
    Receipt totalReceipt;
    double totalSold = 0;
    double totalPrice = 0;
    for(std::size_t i = 0; i < members.length(); i++) {
        std::vector<Receipt> temp = members[i].getReceipts();
        for(auto it = temp.begin(); it != temp.end(); it++) {
            {
                totalReceipt += *it;
            }
        }
    }


    std::map<Item, int> items = totalReceipt.getItems();
    for(auto it = items.begin(); it != items.end(); it++) {
        if (itemName == it->first.getName())
        {
            found = true;
            totalSold = it->second;
            totalPrice = (it->first.getPrice())*totalSold;
        }
    }
    if (!found)
    {
        ui->numberSoldBox->setText("N/A");
        ui->totalSalesBox->setText("N/A");
        return;
    }
    QString price = "$ ";
    ui->numberSoldBox->setText(QString::number(totalSold));
    ui->totalSalesBox->setText(price + QString::number(totalPrice));
}


/******************************************************************************
 *
 *  void MainWindow::on_generateMemberReportButton_clicked()
 *_____________________________________________________________________________
 *  This slot is triggered when the generate member report button is clicked
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    None
 *
 *  POST-CONDITIONS
 *    The member info has been filled in the report area undeneath
 *****************************************************************************/
void MainWindow::on_generateMemberReportButton_clicked()
{
    QRegExp re("\\d*");
    string data = ui->memberInfoEntry->text().toStdString();
    if (ui->memberInfoEntry->text() == "")
    {
        ui->memberReportArea->setText("Member Not Found");
        return;
    }
    bool nameEntered = false;
    bool found = false;
    Member temp;
    Member desiredMember;
    if (ui->nameIdComboBox->currentIndex() == 0)
    {
        nameEntered = true;
    }
    if (nameEntered)
    {
        temp.setName(data);
        found = members.contains(temp);
        if (!found)
        {
            ui->memberReportArea->setText("Member Not Found");
            return;
        }
        desiredMember = getMember(data);
        ui->memberReportArea->setText(QString::fromStdString(getMemberPurchases(desiredMember)));
    }
    else
    {


        if (!re.exactMatch(ui->memberInfoEntry->text()))
        {
            ui->memberReportArea->setText("Not a valid ID");
            return;
        }
        temp.setId(std::stoi(data));
        found = members.contains(temp);
        if (!found)
        {
            ui->memberReportArea->setText("Member Not Found");
            return;
        }
        desiredMember = getMember(std::stoi(data));
        ui->memberReportArea->setText(QString::fromStdString(getMemberPurchases(desiredMember)));
    }
}

/******************************************************************************
 *
 *  FUNCTION printMoney
 *_____________________________________________________________________________
 *  Convert given num to money (ex. $23.85)
 *  - returns std::string
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    num >= 0;
 *
 *  POST-CONDITIONS
 *    num is money format is returned as a string
 ******************************************************************************/
std::string printMoney(double num) {
    std::string display;
    int price = num * 100;
    display += '$' + std::to_string(price/100) + '.';
    if(price % 100 < 10) {
        display += '0';
    }
    display += std::to_string(price%100);

    return display;
}

/******************************************************************************
 *
 *  FUNCTION idComparison
 *_____________________________________________________________________________
 *  compares a and b's ids
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Returns true if a's id is smaller than b's
 ******************************************************************************/
bool idComparison(Member &a, Member& b)
{
    return a.getId() < b.getId();
}

/******************************************************************************
 *
 *  FUNCTION nameComparison
 *_____________________________________________________________________________
 *  compares a and b's names
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Returns true if a's name is smaller than b's
 ******************************************************************************/
bool nameComparison(Member& a, Member& b)
{
    return a.getName() < b.getName();
}
