#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "member.h"
#include "set.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    /******************************
     ** CONSTRUCTOR & DESTRUCTOR **
     ******************************/
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /***************
     ** ACCESSORS **
     ***************/
    Set getBasic();
    Set getPreferred();
    Set getAllMembers();
    Member & getMember(int id);
    Member & getMember(std::string name);

    /***********************************
     ** MODIFICATION MEMBER FUNCTIONS **
     ***********************************/
    void pullFromMemberFile();
    void writeToMemberFile();
    void pullFromSalesFiles();
    void fillMemberComboBox();
    void fillMemberComboBox2();
    void removeMember(int id);

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    std::string displayDailySales(const Date& d, char flag);
    std::string getItemQuantities(char flag);
    std::string getAllMemberPurchases(char flag);
    std::string getYearlyReport(int year, char flag);
    std::string getRebateReport();
    std::string getMemberPurchases(Member desiredMember);
    std::string getMemberDues(int month, char flag);
    std::string getMemberDues(char flag);
    

    private slots:

    void on_generateReportButton_clicked();

    void on_reportComboBox_currentIndexChanged(int index);

    void on_getDuesButton_clicked();

    void on_addMemberButton_clicked();

    void on_removeMemberButton_clicked();

    void on_determineWorthButton_clicked();

    void on_itemSearchButton_clicked();

    void on_generateMemberReportButton_clicked();

  private:
    Ui::MainWindow *ui;
    Set members;
};
/*******************************************************************************
 *  MainWindow Class
 *    Imitates the member system of a wholesale store
 *******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/*******************************************************************************
 *  MainWindow(QWidget *parent = nullptr)
 *    Constructor; initialize variables and set up Ui
 *    Parameters: QWidget *parent
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  ~MainWindow()
 *    Destructor; Update members file and delete Ui
 *    Parameters: none
 *    Return: void
 *******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/*******************************************************************************
 *  Set getBasic() const;
 *
 *    Accessor; This method will return basic members
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: Set
 *******************************************************************************/

/*******************************************************************************
 *  Set getPreferred() const;
 *
 *    Accessor; This method will return preferred members
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: Set
 *******************************************************************************/

/*******************************************************************************
 *  Set getAllMembers() const;
 *
 *    Accessor; This method will return all members
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: Set
 *******************************************************************************/

/*******************************************************************************
 *  Member& getMember(int id) const;
 *
 *    Accessor; This method will return a member with given id
 * -----------------------------------------------------------------------------
 *    Parameters: int
 * -----------------------------------------------------------------------------
 *    Return: Member&
 *******************************************************************************/

/*******************************************************************************
 *  Member& getMember(std::string name) const;
 *
 *    Accessor; This method will return a member with given name
 * -----------------------------------------------------------------------------
 *    Parameters: std::string
 * -----------------------------------------------------------------------------
 *    Return: Member&
 *******************************************************************************/


/***********************************
 ** MODIFICATION MEMBER FUNCTIONS **
 ***********************************/

/*******************************************************************************
 *  void pullFromMemberFile();
 *
 *    extract member information from the file and add each of them to the set
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void writeToMemberFileName();
 *
 *    write each member's information back to the memeber file
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void pullFromSalesFiles();
 *
 *    extract all available sales files, create receipts based on items purchased
 *      and add them to appropriate members
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void fillMemberComboBox();
 *
 *    Display each existing member's name and id in the combo box, 
 *      sorted by their names. Used for removeMember
 * -----------------------------------------------------------------------------
 *    Parameters: non
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void fillMemberComboBox2();
 *
 *    Display each existing member's name and id in the combo box, 
 *      sorted by their names. Used for determining premium worth
 * -----------------------------------------------------------------------------
 *    Parameters: 
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  void removeMember(int id);
 *
 *    member with the given id is remove from the Set of members
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/*******************************************************************************
 *  std::string displayDailySales(const Date& d, char flag) const;
 *
 *    Display sales on a given Date and members type. 
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: const Date&, char
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getItemQuantities(char flag) const;
 *
 *    Display all items purchased by the given member type, sorted by item name
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: char
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getAllMemberPurchases(char flag) const;
 *
 *    Display all member purchases based on the given member flag.
 *      Each member activated by the flag will have all their past purchases
 *      displayed. A grand total of all purchased amount will also be displayed.
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: char
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getYearlyReport(int year, char flag) const;
 *
 *    Get all purcahses in the given year and given member flag. Status of every
 *      item sold is shown. the worst item, best item, as well as total revenue 
 *      are also displayed. 
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 *      Year must be between 1980 and 2080
 * -----------------------------------------------------------------------------
 *    Parameters: int, char
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getRebateReport() const;
 *
 *    The rebate amount of every preferred members are displayed.
 *      Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getMemberPurchases(Member desiredMember) const;
 *
 *    Display all past purchases of a given member.
 *      Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: Member
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getmemberDues(int month, char flag) const;
 *
 *    For members with given expiration month and fits the member flag,
 *      display their expected dues ($60 / $75). Sorted by names.
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: int, char
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/

/*******************************************************************************
 *  std::string getMemberDues(char flag) const;
 *
 *    Display members in the member flag their expected dues, sorted by names.
 *      Flag must be 'a', 'b', or 'p'. Display is returned as a std::string.
 * -----------------------------------------------------------------------------
 *    Parameters: char
 * -----------------------------------------------------------------------------
 *    Return: std::string
 *******************************************************************************/


/*******************
 ** Private Slots **
 *******************/

/*******************************************************************************
 *  void on_generateReportButton_clicked();
 *
 *    Detects user selection and generates one of the following functions 
 *      for only basic members, only preferred members, or all members:
 *      displayDailySales()
 *      getMemberDues()
 *      getItemQuantities()
 *      getAllMemberPurchases()
 *      getYearlyReport()
 *      getRebateReport
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_reportComboBox_currentIndexChanged(int index);
 *
 *    This slot is triggered when the report type index is changed.It slightly
 *    modifies the display
 * -----------------------------------------------------------------------------
 *    Parameters: (int) - the index of the report combobox
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_getDuesButton_clicked();
 *
 *    This slot is triggered when the get dues button is clicked. It is
 *    responsible for displaying the member dues for a particular month.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_addMemberButton_clicked();
 *
 *    This slot is triggered when the add member button is clicked. It adds
 *    the specified member to the list of members.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_removeMemberButton_clicked();
 *
 *    This slot is triggered when the remove member button is clicked.
 *    It removes the member from the list.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_determineWorthButton_clicked();
 *
 *    This slot is triggered when the determine worth button is clicked.
 *    It fills the text area underneath with information regarding whether
 *    or not the selected member should be a premium or a basic member.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_itemSearchButton_clicked();
 *
 *    This slot is triggered when the item search button is clicked.
 *    It fills the two boxes underneath it with information regarding the
 *    quantity and total sales value of an item.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

/*******************************************************************************
 *  void on_generateMemberReportButton_clicked();
 *
 *    This slot is triggerred when the member report button is clicked. It
 *    fills the area underneath with information about a specific member.
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: none
 *******************************************************************************/

#endif // MAINWINDOW_H
