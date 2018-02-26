#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
//#include<windows.h>
using namespace std;
class hard;

class tools{
     friend class hard;
private:
    char id[5];
    char tname[15];

    char cost[10];

public:

    char quantity[5];

    char* getid(){
        return id;
    }
    void getinput()
    {
        cout<<"\nEnter the ID_no : ";
        cin>>id;
        cout<<"\nEnter the ITEM NAME: ";
        cin>>tname;
        cout<<"\nEnter ITEM COST : ";
        cin>>cost;
    }

    void disptoolso()
    {
        cout<<"\t\t"<<id<<"     "<<tname<<"     "<<quantity<<"     "<<cost<<"\n\n\n";
    }
    void disptools(){
        cout<<"\t\t"<<id<<"     "<<tname<<"\t\t"<<cost<<"\n\n";
    }
};
class hard{
public:
    void del();
    void del(char);
    void update();
    void viewall();
    void inputinfile();
    void placeorder();
};
void hard::update(){
    fstream file("t.txt",ios::in|ios::out|ios::app);
    tools t;
    cout<<"\nSpecify tool ID_no to update : ";
     char i[5];
    cin>>i;
    ofstream temp;
    temp.open("temp.txt");
    int flag=0;
    file.seekg(0,ios::beg);
    temp.seekp(0,ios::beg);
    while(file.read((char*)&t,sizeof(t)))
    {
        if(strcmp(t.id,i)!=0)//if not same
        {
            temp.write((char*)&t,sizeof(t));
        }
        else
            flag=1;//if same deleted
    }
    if(flag==0)
    {
        cout<<"\nTool ID"<<" "<<i<<" not present";
    }
    else{
        tools b;
        b.getinput();
        temp.write((char*)&b,sizeof(b));
        cout<<"Record Updated";
    }
    file.clear();
    file.close();
    temp.close();
    remove("t.txt");
    rename("temp.txt","t.txt");
    }

void hard::del()
{
    fstream file("t.txt",ios::in|ios::out|ios::app);
    tools t;
    cout<<"\nSpecify tool ID_no to delete : ";
     char i[5];
    cin>>i;
    ofstream temp;
    temp.open("temp.txt");
    int flag=0;
    file.seekg(0,ios::beg);
    temp.seekp(0,ios::beg);
    while(file.read((char*)&t,sizeof(t)))
    {
        if(strcmp(t.id,i)!=0)//if not same
        {
            temp.write((char*)&t,sizeof(t));
        }
        else
            flag=1;//if same deleted
    }
    if(flag==0)
    {
        cout<<"\nTool ID"<<" "<<i<<" not present";
    }
    else
        cout<<"Record Deleted";
    file.clear();
    file.close();
    temp.close();
    remove("t.txt");
    rename("temp.txt","t.txt");

}
void hard::placeorder(){
    char name[20];
    cout<<"\nEnter your name : ";
    cin>>name;
    strcat(name,".txt");
    fstream file("t.txt",ios::in |ios::out|ios::app);
    file.seekg(0,ios::beg);
    cout<<"\nEnter the item_ID to buy the item\n";
    cout<<"Enter -1 to end the item list";
    fstream newfile(name,ios::out |ios::in | ios::trunc );
    int sum=0,price=0;
    if(newfile.is_open()){
    while(true){
        xyz:cout<<"\nEnter another item_ID : ";
        char it[5];
        cin>>it;
        char mi[3]={'-','1'};
        if(!strcmp(it,mi)) {goto abc;}
        tools t;
        file.seekg(0,ios::beg);
        while(file.read((char*)&t,sizeof(t))){
            if(!strcmp(t.getid(),it)){
                //cout<<"got";
                cout<<"Enter quantity : ";
                cin>>t.quantity;
                price=atoi(t.quantity)*atoi(t.cost);
                sum+=price;
                cout<<price;
                newfile.write((char*)&t,sizeof(t));goto xyz;
            }
        }
        cout<<"\nNo such item left in the store";
        file.clear();
        file.seekg(0,ios::beg);goto xyz;
        newfile.clear();


    }
    abc:
        newfile.clear();
        newfile.seekg(0,ios::beg);
        cout<<"\nYou ordered :\n ";
        tools t1;
        while(newfile.read((char*)&t1,sizeof(t1))){
            t1.disptoolso();cout<<"\n";
        }
        cout<<"\nTotal Price is "<<sum;
    }
    else
        cout<<"\nFailed opening the file for ORDERING";
}

void hard::viewall()
{
    fstream file("t.txt",ios::in);
    file.seekg(0,ios::beg);
    tools t;
    while(file.read((char*)&t,sizeof(t)))
    {
        t.disptools();
    }
    file.clear();
    file.close();
}
void hard::inputinfile()
{
    ifstream file("t.txt");
    ofstream file1("t.txt",ios::app);

    tools t;
    t.getinput();

    file.seekg(0,ios::beg);
    file1.seekp(0,ios::end);
    tools r;
    int flag=0;
    while(file.read((char*)&r,sizeof(r))){
        if(strcmp(t.getid(),r.getid())==0){
            cout<<"\nItem ID already exist !!";
            flag=1;
            break;
        }
    }
    if(flag==0){
            file1.seekp(0,ios::end);
            file1.write((char*)&t,sizeof(t));
            t.disptools();
    }
    file.seekg(0,ios::beg);
    file.clear();
    file.close();
}

int main(){
    cout<<"********************************BILLING SYSTEM******************************";
    system("color 4d");
    hard obj;
    while(true){
        cout<<"\n\nEnter the choice : \n";
        int k;
        cout<<"1. VIEW All Items : \n";
        cout<<"2. INPUT an Item : \n";

        cout<<"3. UPDATE an Item : \n";
        cout<<"4. REMOVE an Item : \n";
        cout<<"5. PLACE an Order: \n";
        cout<<"6. EXIT\n";
        cin>>k;
        if(k==1){
         cout<<"\t\tID    Item_Name    Price\n ";
         obj.viewall();
         cout<<"\n***************************************************************************";
        }

        if(k==2){obj.inputinfile();
        cout<<"\n***************************************************************************";
        }

        if(k==3){obj.update();
        cout<<"\n***************************************************************************";
        }

        if(k==4){obj.del();
        cout<<"\n***************************************************************************";
        }

        if(k==5){obj.placeorder();
        cout<<"\n***************************************************************************";

        }
        if(k==6){exit(1);}
    }
return 0;
}

