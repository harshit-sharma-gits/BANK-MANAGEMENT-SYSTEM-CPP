#include "CLIENT.h"
#include "ACCOUNT.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;

CLIENT::CLIENT()
{
    //ctor
}

void CLIENT::login()
{
    int id;
    bool i=false;
    char pass[10];
    reLogin :
    system("cls");
    cout<<"********************* BANK *********************\n";
    cout<<"******************** CLIENT ********************\n";
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
    cin.ignore();
    cin.getline(pass , 10);

    ACCOUNT obj;
    ifstream ifile("accounts.dat" ,ios::binary);
    if(!ifile)
    {
        cout<<"\n\nERROR : No Account is there to Login !!!!\n\n";
        system("pause");
        return;
    }

    while(ifile.read((char*)&obj , sizeof(obj)))
    {
        if(id == obj.getID())
        {
            i=true;
            break;
        }
    }

    if(!i)
    {
        cout<<"\n\nYou have Entered Wrong ID !!!!\nPress ENTER to go back !!!!";
        cin.get();
        cin.ignore();
        return;
    }

    if(strcmp(pass , obj.getPASS()))
    {
        cout<<"\n\nYou have Entered Wrong Password !!!!\nPress ENTER to go back !!!!";
        cin.get();
        cin.ignore();
        return;
    }

    portal(obj);
    return;
}

void CLIENT::portal(ACCOUNT obj)
{
    int choice;
    while(1)
    {
        system("cls");
        cout<<"********************* BANK *********************\n";
        cout<<"******************** CLIENT ********************\n";
        cout<<"\n1. View your Details\n";
        cout<<"\n2. Deposit Money\n";
        cout<<"\n3. Withdraw Money\n";
        cout<<"\n4. View your Transactions\n";
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
            viewDetails(obj);
        }
        else if (choice == 2)
        {
            obj = deposit(obj);
        }
        else if (choice == 3)
        {
            obj = withdraw(obj);
        }
        else if (choice == 4)
        {
            viewTransac(obj);
        }
        else if (choice == 5)
        {
            return;
        }
    }
}

void CLIENT::viewDetails(ACCOUNT obj)
{
    ifstream ifile("accounts.dat" , ios::binary);

    if(!ifile)
    {
        cout<<"\n\n\tFile Not Exists !!!!!\n\n\t";
        system("pause");
        return;
    }

    system("cls");
    cout<<"ID"<<'\t'<<"NAME"<<'\t'<<"PASSWORD"<<'\t'<<"BALANCE\n";
    cout<<"--------------------------------------------------------------------------------\n";

    obj.outputAdmin();
    cout<<"\n\n\n";

    system("pause");
    ifile.close();
}

ACCOUNT CLIENT::withdraw(ACCOUNT obj)
{
rewithdraw:
    unsigned int amt;
    system("cls");
    cout<<"********************* BANK *********************\n";
    cout<<"******************** CLIENT ********************\n";
    cout<<"\n\nEnter Amount to Withdraw : ";
    cin>>amt;
    if (cin.fail())
        {
            cout<<"\n\nWARNING !!!!\nENTERING INVALID VALUES TO AN INTEGER VARIABLE CAN CAUSE SERIOUS HAPPENINGS.\nDO NOT PERFORM IT UNDER ANY CIRCUMSTANCES!!!!\nCLICK TO CONTINUE";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
            cin.get();
            goto rewithdraw;
        }

    if(amt > obj.getBalance())
    {
        cout << "\n\n\tNot Enough Balance !!! Only Amount of " << obj.getBalance() << " is present !!!\n";
        system("pause");
        goto rewithdraw;
    }
    else
    {
        unsigned int prevBalance = obj.getBalance();
        obj.setBalance(prevBalance - amt);

        ifstream ifile("accounts.dat", ios::binary);
        ACCOUNT k;
        vector<ACCOUNT> vec;

        while(ifile.read((char*)&k , sizeof(k)))
        {
            if(k.getID() != obj.getID())
                vec.push_back(k);
            else
                vec.push_back(obj);
        }

        ifile.close();

        ofstream ofile("accounts.dat", ios::trunc | ios::binary);

        for(int i=0 ; i<vec.size() ; i++)
            ofile.write((char*)&vec[i], sizeof(vec[i]));

        ofile.close();

        ////////// ADDING TO TRANSACTION //////////

        TRANSACTION Tobj(obj.getID(), prevBalance, obj.getBalance(), 'w');
        ofstream of("transactions.dat", ios::binary | ios::app);
        of.write((char*)&Tobj, sizeof(Tobj));
        of.close();

        ///////////////////////////////////////////

        cout << "\n\n\tSuccessful Withdrawal !!!\n";
        cout << "\tPrevious Balance = " << prevBalance << '\n';
        cout << "\tNew Balance = " << obj.getBalance() << "\n\n";
        system("pause");

        return obj;
        }
}

ACCOUNT CLIENT::deposit(ACCOUNT obj)
{
redeposit:
    unsigned int amt;
    system("cls");
    cout<<"********************* BANK *********************\n";
    cout<<"******************** CLIENT ********************\n";
    cout<<"\n\nEnter Amount to Deposit : ";
    cin>>amt;
    if (cin.fail())
        {
            cout<<"\n\nWARNING !!!!\nENTERING INVALID VALUES TO AN INTEGER VARIABLE CAN CAUSE SERIOUS HAPPENINGS.\nDO NOT PERFORM IT UNDER ANY CIRCUMSTANCES!!!!\nCLICK TO CONTINUE";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
            cin.get();
            goto redeposit;
        }

    unsigned int prevBalance = obj.getBalance();
    obj.setBalance(prevBalance+amt);

    ifstream ifile("accounts.dat", ios::binary);
    ACCOUNT k;
    vector<ACCOUNT> vec;

    while(ifile.read((char*)&k , sizeof(k)))
    {
        if(k.getID() != obj.getID())
            vec.push_back(k);
        else
            vec.push_back(obj);
    }

    ifile.close();

    ofstream ofile("accounts.dat", ios::trunc | ios::binary);

    for(int i=0 ; i<vec.size() ; i++)
        ofile.write((char*)&vec[i], sizeof(vec[i]));

    ofile.close();

    ////////// ADDING TO TRANSACTION //////////

    TRANSACTION Tobj(obj.getID(), prevBalance, obj.getBalance(), 'd');
    ofstream of("transactions.dat", ios::binary | ios::app);
    of.write((char*)&Tobj, sizeof(Tobj));
    of.close();

    ///////////////////////////////////////////

    cout << "\n\n\tSuccessfully Deposited !!!\n";
    cout << "\tPrevious Balance = " << prevBalance << '\n';
    cout << "\tNew Balance = " << obj.getBalance() << "\n\n";
    system("pause");

    return obj;
}

void CLIENT::viewTransac(ACCOUNT obj)
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
        if(obj.getID() == k.getID())
            k.viewTransaction();
    }
    cout<<"\n\n\n";

    system("pause");
    ifile.close();
}

CLIENT::~CLIENT()
{
    //dtor
}


////////////////////////// TRANSACTION //////////////////////////

TRANSACTION::TRANSACTION(int id, int pB, int nB, char Ttype)
{
    userID = id;
    prevBalance = pB;
    newBalance = nB;
    type = Ttype;
}

void TRANSACTION::viewTransaction()
{
    if(type == 'w')
        cout << userID << '\t' << prevBalance << '\t' << newBalance << '\t' << "Withdrawal\n";
    else
        cout << userID << '\t' << prevBalance << '\t' << newBalance << '\t' << "Deposition\n";

}

void TRANSACTION::makeTransaction(int id, int pB, int nB, char Ttype)
{
    ofstream ofile("transactions.dat", ios::binary | ios::app);

    TRANSACTION k(id,pB,nB,Ttype);

    ofile.write((char*)&k, sizeof(k));
    ofile.close();
}

/*  In this project i haven't used the tradition approach to change the data file
**
**  Traditional Approach was to create a 'temp' data file and transfer the data to real file with the changes
**
**  But somehow remove() and rename() functions were not working in my IDE :/
**
**  So i built-up my approach :-
**  First of all Transferring the data of original file to a VECTOR with the changes
**  Then opening the original file in truncate mode and then transfer the data from VECTOR to the file !!!!
*/
