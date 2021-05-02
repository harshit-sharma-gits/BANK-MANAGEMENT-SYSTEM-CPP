#include "ACCOUNT.h"
#include <iostream>
#include <cstring>

using namespace std;

ACCOUNT::ACCOUNT()
{
    accID = 0;
    strcpy(accName , "NULL");
    strcpy(passWord , "NULL");
    balance = 0;
}

void ACCOUNT::output()
{
    cout<<accID<<'\t'<<accName<<'\n';
}

void ACCOUNT::outputAdmin()
{
    cout<<accID<<'\t'<<accName<<'\t'<<passWord<<"\t\t"<<balance<<'\n';
}

void ACCOUNT::inputAdmin()
{
    system("cls");
    cout<<"---------------- New Account Creation ----------------\n\n";
    cout<<"Enter Name : ";
    cin.ignore();
    cin.getline(accName , 10);
    cout<<"Enter ID : ";
    cin>>accID;
    cout<<"Make Password : ";
    cin.ignore();
    cin.getline(passWord , 10);
}

int ACCOUNT::getID()
{
    return accID;
}

char* ACCOUNT::getPASS()
{
    return passWord;
}

unsigned int ACCOUNT::getBalance()
{
    return balance;
}

void ACCOUNT::setBalance(unsigned int amt)
{
    balance = amt;
}

ACCOUNT::~ACCOUNT()
{
    //dtor
}
