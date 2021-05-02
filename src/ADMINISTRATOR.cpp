#include "ADMINISTRATOR.h"
#include "ACCOUNT.h"
#include "CLIENT.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace std;

ADMINISTRATOR::ADMINISTRATOR()
{
    //ctor
}

void ADMINISTRATOR::login()
{
    int id;
    char pass[10];
    reLogin :
    system("cls");
    cout<<"********************* BANK *********************\n";
    cout<<"***************** ADMINISTRATOR ****************\n";
    cout<<"\n\nEnter ID : ";
    cin>>id;
        if (cin.fail())
        {
            cout<<"\n\nWARNING !!!!\nENTERING NON INTEGER VALUES TO AN INTEGER VARIABLE CAN CAUSE SERIOUS HAPPENINGS.\nDO NOT PERFORM IT UNDER ANY CIRCUMSTANCES!!!!\nCLICK TO CONTINUE";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
            cin.get();
            goto reLogin;
        }
    cout<<"\n\nEnter Password : ";
    cin>>pass;
    cin.ignore();

    if(id != ADMIN_ID)
    {
        cout<<"\n\nYou have typed Wrong ID !!!!\nPress ENTER to go back !!!!";
        cin.get();
        return;
    }
    if(strcmp(pass , ADMIN_PASS))
    {
        cout<<"\n\nYou have typed Wrong Password !!!!\nPress ENTER to go back !!!!";
        cin.get();
        return;
    }
    // After Checking for Correct ID & Password we move to the PORTAL

    portal();
    return;
}

void ADMINISTRATOR::portal()
{
    int choice;
    while(1)
    {
        system("cls");
        cout<<"********************* BANK *********************\n";
        cout<<"***************** ADMINISTRATOR ****************\n";
        cout<<"\n1. View all Accounts\n";
        cout<<"\n2. Delete an Account\n";
        cout<<"\n3. View all Transactions\n";
        cout<<"\n4. Add an Account\n";
        cout<<"\n5. Exit\n";
        cout<<"\n\n Enter Choice :- ";
        cin>>choice;

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
            viewAcc();
        }
        else if (choice == 2)
        {
            delAcc();
        }
        else if (choice == 3)
        {
            viewAllTrans();
        }
        else if (choice == 4)
        {
            addAcc();
        }
        else if (choice == 5)
        {
            return;
        }
    }
}

void ADMINISTRATOR::viewAcc()
{
    ifstream ifile("accounts.dat" , ios::binary);
    ACCOUNT obj;

    if(!ifile)
    {
        cout<<"\n\n\tFile Not Exists !!!!!\n\n\t";
        system("pause");
        return;
    }

    system("cls");
    cout<<"ID"<<'\t'<<"NAME"<<'\t'<<"PASSWORD"<<'\t'<<"BALANCE\n";
    cout<<"--------------------------------------------------------------------------------\n";


    while(ifile.read((char*)&obj , sizeof(obj)))
    {
         obj.outputAdmin();
    }
    cout<<"\n\n\n";

    system("pause");
    ifile.close();
}

void ADMINISTRATOR::addAcc()
{
    ofstream ofile("accounts.dat" , ios::binary | ios::app);
    ACCOUNT obj;

    obj.inputAdmin();

    ofile.write((char*)&obj , sizeof(obj));

    ofile.close();
}

void ADMINISTRATOR::delAcc()
{
    system("cls");
    int id;
    cout<<"********************* BANK *********************\n";
    cout<<"***************** ADMINISTRATOR ****************\n";
    cout << "\n\nEnter Account ID to be Deleted : ";
    cin >> id;

    ifstream ifile("accounts.dat", ios::binary);
    ACCOUNT k;
    vector<ACCOUNT> vec;

    while(ifile.read((char*)&k , sizeof(k)))
    {
        if(k.getID() != id)
            vec.push_back(k);
    }

    ifile.close();

    ofstream ofile("accounts.dat", ios::trunc | ios::binary);

    for(int i=0 ; i<vec.size() ; i++)
        ofile.write((char*)&vec[i], sizeof(vec[i]));

    ofile.close();

    cout<<"\n\n\tAccount Deleted !!!!!\n\n\t";
    system("pause");
    return;
}

void ADMINISTRATOR::viewAllTrans()
{
    ifstream ifile("transactions.dat", ios::binary);
    if(!ifile)
    {
        cout<<"\n\n\tFile Not Exists !!!!!\n\n\t";
        system("pause");
        return;
    }

    TRANSACTION k(0,0,0,'X');

    system("cls");
    cout<<"ID"<<'\t'<<"PREV"<<'\t'<<"NEW"<<'\t'<<"TRANSACTION TYPE\n";
    cout<<"--------------------------------------------------------------------------------\n";
    while(ifile.read((char*)&k, sizeof(k)))
    {
        k.viewTransaction();
    }
    cout<<"\n\n\n";

    ifile.close();
    system("pause");
}

void ADMINISTRATOR::viewList()
{
    ifstream ifile("accounts.dat" , ios::binary);
    ACCOUNT obj;

    if(!ifile)
    {
        cout<<"\n\n\tFile Not Exists !!!!!\n\n\t";
        system("pause");
        return;
    }

    system("cls");
    cout<<"ID"<<'\t'<<"NAME\n";
    cout<<"--------------------------------------------------------------------------------\n";

    while(ifile.read((char*)&obj , sizeof(obj)))
    {
         obj.output();
    }
    cout<<"\n\n\n";

    system("pause");
    ifile.close();
}
