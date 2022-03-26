#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;
int convert(string);
class Medicine
{
    public:
        string name;
        string codeNo;
        int expiryMonth;
        int expiryYear;
        int quantity;
        bool isExpired;
        bool quantityLess;

        void expired()
        {
            time_t now = time(0);
            string dt = ctime(&now);
            int month=convert(dt.substr(4,3));
            stringstream obj(dt.substr(20,4));
            int year;
            obj>>year;
            if(expiryYear>year)
            {
                isExpired=false;
            }
            else if(expiryYear==year)
            {
                if(expiryMonth>month)
                {
                    isExpired=false;
                }
                else
                    isExpired=true;
            }
            else
                isExpired=true;
        }
        void isQuantityLess()
        {
            if(quantity<=20)
                quantityLess=true;
            else
                quantityLess=false;
        }
};

void loadmedicines(Medicine *database,int);
void printdata(Medicine *database,int);
void sellmed(Medicine *database,int);
void incstk(Medicine *database,int);
void ttlinq(Medicine *database,int);
void savemedicines(Medicine *database,int,Medicine *database1,int);
void savemedicines(Medicine *database,int);
void addmedicine(Medicine *database,int);
void removemedicine(Medicine *database,int);
int length();
int getFirstIndexOf(char,string);
int getLastIndexOf(char,string);
int getNextIndexOf(char,string,int);
bool newmed=false;

int main()
{
    start:
    bool exit=false;
    int l=length();
    if(l==0)
    {
        Medicine obj;
        cout<<"DATABASE FILE IS EMPTY\nPLEASE ADD 1 MEDICINE TO THE DATABASE TO START THE PROGRAM\n";
        cout<<"\nEnter medicine name:";
        cin>>obj.name;
        cout<<"\nEnter the quantity:";
        cin>>obj.quantity;
        cout<<"\nEnter the expiry month:";
        cin>>obj.expiryMonth;
        cout<<"\nEnter the expiry year:";
        cin>>obj.expiryYear;
        cout<<"\nEnter the code no:";
        cin>>obj.codeNo;
        cout<<"\n";
        fstream st;
        st.open("E:\Database.txt",ios::out);
        if(!st)
        {
            cout<<"File creation failed";
        }
        else
        {
            st<<obj.codeNo<<"-"<<obj.expiryMonth<<"-"<<obj.expiryYear<<"-"<<obj.quantity<<"-"<<obj.name;
        }
        st.close();
        goto start;
    }
    else if(l>0)
    {
        Medicine database[l];
        loadmedicines(database,l);
        while(exit==false)
        {
            cout<<"\n\t\t\t\t---------------------------------------------------------------\n";
            cout<<"\t\t\t\t*\t\tWELCOME TO THE BEST PHARMACEUTICALS\t      *\n";
            cout<<"\t\t\t\t*\t\t  PRESS 1 FOR SELLING MEDICINE\t\t      *\n";
            cout<<"\t\t\t\t*\t\t  PRESS 2 FOR INCREASING STOCK\t\t      *\n";
            cout<<"\t\t\t\t*\t\tPRESS 3 FOR INDIVIDUAL STOCK DETAILS\t      *\n";
            cout<<"\t\t\t\t*\t\t    PRESS 4 FOR TOTAL INQUIRY\t\t      *\n";
            cout<<"\t\t\t\t*\t  PRESS 5 TO ADD A NEW MEDICINE TO THE DATABASE\t      *\n";
            cout<<"\t\t\t\t*\t\t  PRESS 6 TO REMOVE A MEDICINE\t\t      *\n";
            cout<<"\t\t\t\t*\t\t         PRESS 7 TO EXIT\t\t      *\n";
            cout<<"\t\t\t\t--------------------------------------------------------------\n";
            int c;
            cin>>c;
            switch(c)
            {
                case 1:
                    sellmed(database,l);
                    savemedicines(database,l);
                    break;
                case 2:
                    incstk(database,l);
                    savemedicines(database,l);
                    break;
                case 3:
                    ttlinq(database,l);
                    break;
                case 4:
                    printdata(database,l);
                    break;
                case 5:
                    addmedicine(database,l);
                    goto start;
                    break;
                case 6:
                    removemedicine(database,l);
                    savemedicines(database,l-1);
                    goto start;
                    break;
                case 7:
                    exit=true;
                    savemedicines(database,l);
                    break;
                default:
                    cout<<"Wrong input\n";
            }
        }
    }
    return 0;
}

void addmedicine(Medicine *database,int l)
{
    newmed=true;
    cout<<"\nEnter no of new medicines:";
    int sizee;
    cin>>sizee;
    Medicine newDatabase[sizee];
    for(int i=0;i<sizee;i++)
    {
        cout<<"\nEnter medicine name:";
        cin>>newDatabase[i].name;
        cout<<"\nEnter the quantity:";
        cin>>newDatabase[i].quantity;
        cout<<"\nEnter the expiry month:";
        cin>>newDatabase[i].expiryMonth;
        cout<<"\nEnter the expiry year:";
        cin>>newDatabase[i].expiryYear;
        cout<<"\nEnter the code no:";
        cin>>newDatabase[i].codeNo;
        cout<<"\n";
        newDatabase[i].expired();
        newDatabase[i].isQuantityLess();
    }
    savemedicines(database,l,newDatabase,sizee);
}

void removemedicine(Medicine *database,int l)
{
    bool found=false;
    cout<<"\nEnter medicine name:";
    string s;
    cin>>s;
    for(int i=0;i<l;i++)
    {
         if(database[i].name==s)
         {
             found=true;
             for(int x=i;x<l-1;x++)
             {
                 database[x].name=database[x+1].name;
                 database[x].codeNo=database[x+1].codeNo;
                 database[x].expiryMonth=database[x+1].expiryMonth;
                 database[x].expiryYear=database[x+1].expiryYear;
                 database[x].quantity=database[x+1].quantity;
                 database[x].isExpired=database[x+1].isExpired;
                 database[x].quantityLess=database[x+1].quantityLess;
             }
             database[l-1].name="";
             database[l-1].codeNo="";
             database[l-1].expiryMonth=0;
             database[l-1].expiryYear=0;
             database[l-1].quantity=0;
         }
    }
     if(found==false)
        cout<<"Medicine not found";
}

int length()
{
    string s;
    ifstream obj("E:\Database.txt");
    int l=0;
     while (getline(obj, s))
        l++;
    return l;
}

void savemedicines(Medicine *database,int l,Medicine *database2,int length2)
{
    fstream st;
    st.open("E:\Database.txt",ios::out);
    if(!st)
    {
        cout<<"File creation failed";
    }
    else
    {
        for(int i=0;i<l;i++)
        {
            st<<database[i].codeNo<<"-"<<database[i].expiryMonth<<"-"<<database[i].expiryYear<<"-"<<database[i].quantity<<"-"<<database[i].name;
            if(i<l-1)
                st<<"\n";
        }
        if(newmed==true)
        {
            st<<"\n";
            for(int i=0;i<length2;i++)
            {
                st<<database2[i].codeNo<<"-"<<database2[i].expiryMonth<<"-"<<database2[i].expiryYear<<"-"<<database2[i].quantity<<"-"<<database2[i].name;
                if(i<length2-1)
                    st<<"\n";
            }
        }
        st.close();
    }
}

void savemedicines(Medicine *database,int l)
{
        fstream st;
        st.open("E:\Database.txt",ios::out);
        if(!st)
        {
            cout<<"File creation failed";
        }
        else
        {
            for(int i=0;i<l;i++)
            {
                st<<database[i].codeNo<<"-"<<database[i].expiryMonth<<"-"<<database[i].expiryYear<<"-"<<database[i].quantity<<"-"<<database[i].name;
                if(i<l-1)
                    st<<"\n";
            }
            st.close();
        }
}

void loadmedicines(Medicine *database,int l)
{
    fstream st;
    st.open("E:\Database.txt",ios::in);
    if(!st)
    {
        cout<<"No such file";
    }
    else
    {
        int i=0;
        while (!st.eof())
        {
            string s;
            st>>s;
            int f=getFirstIndexOf('-',s);
            int ls=getLastIndexOf('-',s);
            Medicine obj;
            obj.codeNo=s.substr(0,f);
            stringstream obj1(s.substr(f+1,getNextIndexOf('-',s,f)));
            obj1>>obj.expiryMonth;
            if(obj.expiryMonth>9)
            {
                stringstream geek(s.substr(f+4,4));
                geek>>obj.expiryYear;
                stringstream geeks(s.substr(f+9,ls));
                geeks>>obj.quantity;
            }
            else
            {
                stringstream geek(s.substr(f+3,4));
                geek>>obj.expiryYear;
                stringstream geeks(s.substr(f+8,ls));
                geeks>>obj.quantity;
            }
            obj.name=s.substr(ls+1,s.length()-ls);
            database[i]=obj;
            database[i].isQuantityLess();
            database[i].expired();
            i++;
        }
    }
    st.close();
}

void printdata(Medicine *database,int l)
{
    cout<<"\n";
    for(int i=0;i<l;i++)
    {
        cout<<"******************************\n";
        cout<<"Name: "<<database[i].name<<"\n";
        cout<<"Code no :"<<database[i].codeNo<<"\n";
        cout<<"Expiry date: "<<database[i].expiryMonth<<"-"<<database[i].expiryYear<<"\n";
        cout<<"Quantity left: "<<database[i].quantity<<"\n";
        if(database[i].isExpired==true)
            cout<<"******EXPIRED******\n";
        if(database[i].quantityLess==true)
            cout<<"******QUANTITY BELOW LIMIT******\n";
        cout<<"******************************\n\n";
    }
}

void sellmed(Medicine *database,int l)
{
    cout<<"\nEnter medicine name:";
    string name;
    cin>>name;
    bool medfound=false;
    for(int i=0;i<l;i++)
    {
        if(database[i].name==name)
        {
            medfound=true;
            if(database[i].isExpired==false)
            {
                cout<<"Enter quantity:";
                int quantity;
                cin>>quantity;
                if(database[i].quantity>=quantity)
                {
                    database[i].quantity=database[i].quantity-quantity;
                    cout<<"\nMedicine sold\n\n";
                    cout<<"******************************\n";
                    cout<<"Name: "<<database[i].name<<"\n";
                    cout<<"Code no :"<<database[i].codeNo<<"\n";
                    cout<<"Expiry date: "<<database[i].expiryMonth<<"-"<<database[i].expiryYear<<"\n";
                    cout<<"Quantity left: "<<database[i].quantity<<"\n";
                    database[i].isQuantityLess();
                    if(database[i].isExpired==true)
                        cout<<"******EXPIRED******\n";
                    if(database[i].quantityLess==true)
                        cout<<"******QUANTITY BELOW LIMIT******\n";
                    cout<<"******************************\n\n";
                    savemedicines(database,l);
                }
                else
                {
                    cout<<"******************************\n";
                    cout<<"Quantity not available"<<"\n";
                    cout<<"******************************\n\n";
                    database[i].isQuantityLess();
                }
            }
            else
            {
                cout<<"******************************\n";
                cout<<"Product has expired\n";
                cout<<"******************************\n\n";
                database[i].isExpired=true;
            }
            break;
        }
    }
    if(medfound==false)
    {
        cout<<"******************************\n";
        cout<<"Medicine not found\n"<<"\n";
        cout<<"******************************\n\n";
    }
}

void incstk(Medicine *database,int l)
{
    cout<<"\nEnter medicine name:";
    string s;
    cin>>s;
    bool found=false;
    for(int i=0;i<l;i++)
    {
        if(database[i].name==s)
        {
            cout<<"Enter amount to increase by:";
            int amt;
            cin>>amt;
            if(database[i].isExpired==true)
            {
                cout<<"\n******PRODUCT EXPIRED HENCE REMOVED OLD STOCK******";
                database[i].quantity=amt;
                database[i].expired();
                cout<<"\nEnter the new expiry month:";
                cin>>database[i].expiryMonth;
                cout<<"\nEnter the new expiry year:";
                cin>>database[i].expiryYear;
                database[i].expired();
            }
            else
            {
                database[i].quantity=database[i].quantity+amt;
            }
            found=true;
            database[i].isQuantityLess();
            cout<<"\nMedicine stock increased\n";
            cout<<"******************************\n";
            cout<<"Name: "<<database[i].name<<"\n";
            cout<<"Code no :"<<database[i].codeNo<<"\n";
            cout<<"Expiry date: "<<database[i].expiryMonth<<"-"<<database[i].expiryYear<<"\n";
            cout<<"Quantity left: "<<database[i].quantity<<"\n";
            if(database[i].isExpired==true)
                cout<<"******EXPIRED******\n";
            if(database[i].quantityLess==true)
                cout<<"******QUANTITY BELOW LIMIT******\n";
            cout<<"******************************\n\n";
        }
    }
    if(found==false)
        cout<<"Medicine not found";
}

void ttlinq(Medicine *database,int l)
{
    bool found=false;
    cout<<"\nEnter medicine name:";
    string s;
    cin>>s;
    for(int i=0;i<l;i++)
    {
         if(database[i].name==s)
         {
             found=true;
             cout<<"\n******************************\n";
             cout<<"Name: "<<database[i].name<<"\n";
             cout<<"Code no :"<<database[i].codeNo<<"\n";

             cout<<"Expiry date: "<<database[i].expiryMonth<<"-"<<database[i].expiryYear<<"\n";
             cout<<"Quantity left: "<<database[i].quantity<<"\n";
             if(database[i].isExpired==true)
                cout<<"******EXPIRED******\n";
             if(database[i].quantityLess==true)
                cout<<"******QUANTITY BELOW LIMIT******\n";
             cout<<"******************************\n\n";
         }
    }
     if(found==false)
        cout<<"Medicine not found";
}

int convert(string s)
{
    if(s=="Jan")
        return 1;

    if(s=="Feb")
        return 2;

    if(s=="Mar")
        return 3;

    if(s=="Apr")
        return 4;

    if(s=="May")
        return 5;

    if(s=="Jun")
        return 6;

    if(s=="Jul")
        return 7;

    if(s=="Aug")
        return 8;

    if(s=="Sep")
        return 9;

    if(s=="Oct")
        return 10;

    if(s=="Nov")
        return 11;

    if(s=="Dec")
        return 12;
}

int getFirstIndexOf(char ch,string s)
{
    for(int i=0;i<s.length();i++)
    {
        if(s[i]==ch)
        {
            return i;
            break;
        }
    }
}

int getLastIndexOf(char ch,string s)
{
    for(int i=s.length();i>0;i--)
    {
        if(s[i]==ch)
        {
            return i;
            break;
        }
    }
}

int getNextIndexOf(char ch,string s,int i)
{
    for(;i<s.length();i++)
    {
        if(s[i]==ch)
        {
            return i;
            break;
        }
    }
}
