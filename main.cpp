/*
    BANK MANAGEMENT SYSTEM - By Harshit Sharma

    This project uses Four Classes -
    * ACCOUNT
    * ADMINISTRATOR
    * CLIENT
    * TRANSACTION

    And two Data Files -
    * "accounts.dat"
    * "transactions.dat"
*/

#include <iostream>
#include <unistd.h>
#include <limits>
#include <cstdlib>
#include "ADMINISTRATOR.h"
#include "CLIENT.h"

using namespace std;

//////// Just for fun Loading Function :) /////////
void LOADING();

///// For handling all the Administrator Work /////
ADMINISTRATOR admin;

///////// For handling all the Client Work ////////
CLIENT client;

/////////////////// MAIN METHOD ///////////////////
int main()
{
    LOADING();
    int choice;
    while(1)
    {
        system("cls");
        cout<<"********************* BANK *********************\n";
        cout<<"\n1. Log in to Your Account\n";
        cout<<"\n2. Log in as Administrator Account\n";
        cout<<"\n3. View all Accounts List\n";
        cout<<"\n4. Exit\n";
        cout<<"\n\n Enter Choice :- ";
        cin>>choice;

        /*  When something other than integer is inputted in an integer variable
        **  Then cin fails to input any further
        **  So to reset cin we use the following code in the condition :-
        */
        if (cin.fail())
        {
            cout<<"\n\nWARNING !!!!\nENTERING NON INTEGER VALUES TO AN INTEGER VARIABLE CAN CAUSE SERIOUS HAPPENINGS.\nDO NOT PERFORM IT UNDER ANY CIRCUMSTANCES!!!!\nCLICK TO CONTINUE";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
            cin.get();
            continue;
        }

        if(choice == 1)
        {
            client.login();
        }
        else if (choice == 2)
        {
            admin.login();
        }
        else if (choice == 3)
        {
            admin.viewList();
        }
        else if (choice == 4)
        {
            exit(0);
        }
    }
}

/////// LOADING FUNCTION IMPLEMENTATION ///////

void LOADING()
{
    for (int i=0; i<=100 ; i++)
    {
        system("cls");
        cout<<"\n\n\n\n\n\t\tBank is Loading : ";
        cout<<i<<" %";
        usleep(100);
    }
    cout<<"\n\n\n\n\n\t\tLoaded Successfully !!!!";
    usleep(1000);
}
