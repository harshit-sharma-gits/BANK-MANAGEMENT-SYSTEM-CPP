#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <cstdlib>

/*      -- ACCOUNT CLASS --
**      * Responsible to Handle the Accounts Functions
**
**      * Moreover data in the binary File 'accounts.dat'
**        is stored using this class' format
*/

class ACCOUNT
{
private:
    int accID;
    char accName[10];
    char passWord[10];
    unsigned int balance;
public:
        ACCOUNT();
        void output();
        void outputAdmin();
        void inputAdmin();
        int getID();
        char* getPASS();
        unsigned int getBalance();
        void setBalance(unsigned int);
        virtual ~ACCOUNT();
};

#endif // ACCOUNT_H
