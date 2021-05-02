#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <cstdlib>

#define     ADMIN_ID        69
#define     ADMIN_PASS      "imadmin"

/*
**      -- ADMINISTRATOR CLASS --
**      * Responsible to Handle Administrator Functions
**lude <cstdlib
**      * When Logging in the Administrator, ID would be 69 and
**        password is 'iamadmin'
*/

class ADMINISTRATOR
{
private:
        void portal();//////////
        void viewAcc();
        void delAcc();
        void viewAllTrans();
        void addAcc();
public:
        ADMINISTRATOR();
        void login();
        void viewList();
};

#endif // ADMINISTRATOR_H
