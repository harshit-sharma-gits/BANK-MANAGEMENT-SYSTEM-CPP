#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include "ACCOUNT.h"

/*      -- CLIENT & TRANSACTION CLASS --
**
**      * CLIENT Class is responsible to Handle Client Menu
**
**      * TRANSACTION Class is responsible to Handle & Save
**        Transactions
**
**      * CLIENT Class' Functions accept an ACCOUNT object as
**        arguement, for saving the Details of LOGGED IN user
**
*/

class CLIENT
{
private:
        void portal(ACCOUNT);
        void viewDetails(ACCOUNT);
        void viewTransac(ACCOUNT);
        ACCOUNT withdraw(ACCOUNT);
        ACCOUNT deposit(ACCOUNT);
public:
        CLIENT();
        void login();
        virtual ~CLIENT();
};

class TRANSACTION
{
private:
        int userID;
        int prevBalance, newBalance;
        char type;                      // Transaction Type - 'w' or 'd'
public:
        TRANSACTION(int,int,int,char);
        void makeTransaction(int id, int pB, int nB, char Ttype);
        void viewTransaction();
        int getID()
        {
            return userID;
        }
        void viewAllTransactions();     // Function for ADMIN Use
};
#endif // CLIENT_H
