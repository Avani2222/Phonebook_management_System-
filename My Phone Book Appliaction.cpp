#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
using namespace std;
int menue();
int Add_Num();
int Show_Records();
int Search_with_serial_number();
int Record_Deletion();
int Update_Record();
class PhoneBook 
{
    int srno;
    string n;
    string m;
    string e;
    string g;
    public:
    int getSrNo() {return srno;}
    int  storeData()
    {
        cout<<"\n.......CREATE NEW PHONE RECORD.........\n";
        cout<<"Enter Serial Number : "; 
		cin>>srno; cin.ignore();
        cout<<"Enter Record Name   : ";
		getline(cin, n);
        cout<<"Enter Mobile Number : "; 
		getline(cin, m);
        cout<<"Enter E-Mail I. D.  : "; 
		getline(cin, e);
        cout<<"Enter Record Group  : "; 
		getline(cin, g);
        cout<<endl;
    }
    int  showData()
    {
        cout<<"\n...............PHONE BOOK RECORD...............\n";
        cout<<"Sr. No.    : "<<srno<<endl;
        cout<<"Name       : "<<n<<endl;
        cout<<"Mobile No. : "<<m<<endl;
        cout<<"Email ID   : "<<e<<endl;
        cout<<"Group      : "<<g<<endl;
    }
}p;
int  NumberSum()
{
    ofstream fout;
    fout.open("PhonBook.dat",ios::out|ios::binary|ios::app);
    p.storeData();
    fout.write((char*)&p,sizeof(p));
    fout.close();
    cout<<"\nRecord Saved to File......\n";
}
int  Show_Records()
{
    ifstream fin;
    fin.open("PhonBook.dat",ios::out|ios::binary|ios::app);
    while(fin.read((char*)&p,sizeof(p)))
    {
        p.showData();
    }
    fin.close();
    cout<<"\nReading of Data File Completed......\n";
}
int Search_with_serial_number()
{
    ifstream fin;
    int n, flag=0;
    fin.open("PhonBook.dat",ios::out|ios::binary|ios::app);
    cout<<"Enter Serial Number of Record To Display: ";
    cin>>n;
    while(fin.read((char*)&p,sizeof(p)))
    {
        if(n==p.getSrNo())
        {
            p.showData();
            flag++;
            cout<<"\n\n.....Record Found and Displayed......\n";
        }
    }
    fin.close();
    if(flag==0)
        cout<<"\nThe Record of Serial Number "<<n<<" is not in file....\n";
    cout<<"\nReading of Data File Completed......\n";
}
int  Record_Deletion()
{
    ifstream fin;
    ofstream fout;
    int n, flag=0;
    fin.open("PhonBook.dat",ios::out|ios::binary|ios::app);
    fout.open("temp.dat",ios::out|ios::binary);
    cout<<"Enter Serial Number of Record To Delete : ";
    cin>>n;
    while(fin.read((char*)&p,sizeof(p)))
    {
        if(n==p.getSrNo())
        {
            cout<<"\nThe Following record is deleted....\n";
            p.showData();
            flag++;
        }
        else
        {
            fout.write((char*)&p,sizeof(p));
        }
    }
    fin.close();
    fout.close();
    if(flag==0)
    {
        cout<<"\nThe Record of Serial Number "<<n<<" is not in file....\n";
    cout<<"\nReading of Data File Completed......\n";
    remove("PhonBook.dat");
    rename("temp.dat","PhonBook.dat");
    }
}
int  Update_Record()
{
    fstream fio;
    int n, flag=0,pos;
    fio.open("PhonBook.dat",ios::out|ios::binary|ios::in);

    cout<<"Enter Serial Number of Record To Modify : ";
    cin>>n;
    while(fio.read((char*)&p,sizeof(p)))
    {
        pos=fio.tellg();
        if(n==p.getSrNo())
        {
            cout<<"\nThe Following record will be modified....\n";
            p.showData();
            flag++;
            cout<<"\nRe-Enter the New Details.....\n";
            p.storeData();
            fio.seekg(pos-sizeof(p));
            fio.write((char*)&p,sizeof(p));
            cout<<"\n....Data Modified Successfully....\n";
        }
    }
    fio.close();
    if(flag==0)
        cout<<"\nThe Record of Serial Number "<<n<<" is not in file....\n";
    cout<<"\nReading of Data File Completed......\n";
}
void menue()
{
    int ch;
    do
    {
        //clrscr();
        cout<<"............................................\n";
        cout<<"           PHONE BOOK MANAGEMENT\n";
        cout<<"............................................\n\n";
        cout<<"::::::::::::::: PROGRAM MENU :::::::::::::::\n";
        cout<<"0. Exit\n";
        cout<<"1. Save New Phone Record\n";
        cout<<"2. Display All Saved Records\n";
        cout<<"3. Search Specific Record\n";
        cout<<"4. Delete Specific Record\n";
        cout<<"5. Modify Existing Record\n";
        cout<<"Enter Your Choice  ";
        cin>>ch;
        //clrscr();
        switch(ch)
        {
            case 1: NumberSum(); break;
            case 2: Show_Records(); 
			break;
            case 3:Search_with_serial_number();
			 break;
            case 4: Record_Deletion();
			 break;
            case 5: Update_Record(); 
			break;
        }
        getch();
    }
	while(ch);
}
int main()
{
    menue();
    return 0;
}
