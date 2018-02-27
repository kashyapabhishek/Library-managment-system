// ###################################################################################################
// ##                                       HEADER                                                  ##
// ###################################################################################################

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdio>
//#include <conio.h>
using namespace std;
void search_book(string);
void search_book_by_subject(string);
void search_book_by_id(int);
 void issuebook(string,string);
 void returnbook(string, string);

static string usernamegloble= " ";

// ###################################################################################################
// ##                                       BOOK                                                    ##
// ###################################################################################################

class book{
private:
    string book_name;
    string author_name;
    float book_price;
    long book_id;
    string book_subject;
    int no_of_book;

public:
    void createbook(){
            cout<<"[+] Enter the details of book [+]"<<endl;

            cout<<endl<<setw(10)<<"Enter book id:\t";
            cin>>book_id;

            cout<<endl<<setw(10)<<"Enter book subject:\t";
            cin>>book_subject;

            cout<<endl<<setw(10)<<"Enter book name:\t";
            cin>>book_name;

            cout<<endl<<setw(10)<<"Enter book author name:\t";
            cin>>author_name;

            cout<<endl<<setw(10)<<"Enter book price:\t";
            cin>>book_price;

            cout<<endl<<setw(10)<<"Enter book set No:\t";
            cin>>no_of_book;

    }

    void updatebook(){
            cout<<"[+] Update book details [+]"<<endl;

            cout<<endl<<setw(10)<<"Enter book subject:\t";
            cin>>book_subject;

            cout<<endl<<setw(10)<<"Enter book name:\t";
            cin>>book_name;

            cout<<endl<<setw(10)<<"Enter book author name:\t";
            cin>>author_name;

            cout<<endl<<setw(10)<<"Enter book price:\t";
            cin>>book_price;

            cout<<endl<<setw(10)<<"Enter book set No:\t";
            cin>>no_of_book;

    }

    string show_book(){
            cout<<"[+] details of book [+]"<<endl;

            cout<<endl<<setw(10)<<"Book name: "<<book_name;

            cout<<endl<<setw(10)<<"Book id: "<<book_id;

            cout<<endl<<setw(10)<<"Book subject: "<<book_subject;

            cout<<endl<<setw(10)<<"Book author: "<<author_name;

            cout<<endl<<setw(10)<<"Book price: "<<book_price;

    }

    long retbno()
    {
        return book_id;
    }

    string getbookname(){
        return book_name;
    }
    string getbookbysubject(){
        return book_subject;
    }


};



// ###################################################################################################
// ##                                       USER                                                   ##
// ###################################################################################################


class user{
    string username;
    int password;
    string name;
    string useraddress;
    string books[5];

public:
    void createuser(){
        cout<<endl<<endl<<"Enter username: ";
        cin>>username;
        cout<<endl<<"Enter password: ";
        cin>>password;
        cout<<endl<<"Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout<<endl<<"Enter address: ";
        cin.ignore();
        getline(cin, useraddress);
        cout<<endl<<"Account created as "<<username<<endl<<endl;
    }

    string getusername(){
        return username;
    }
    int getpassword(){
        return password;
    }

};

class issuandreturn{


public:
    string username;
    string books[5];
    int flage = 0;
    int count = -1;

    void issue(string user, string name){
        username = user;
        count += 1;
        books[count] = name;


    }

    string user(){
        return username;
    }

    void deletebook(string b){
        for(int i = 0; i<= count; i++){
            if(books[i] == b){
                books[i] = " ";
            }
        }
    }

    int book(string b){
        for(int i = 0; i<= count; i++){
            if(books[i] == b){
                return 1;
            }
            else{
                return 0;
            }
        }

    }

    int bcount(){

        return count;
    }

};

class users{
    string book_name;
    string book_subject;
    char ch;
    int option;
    bool check = true;

public:
    users(){
        cout<<"[+] Wlecome to the library management system [+]"<<endl;
        cout<<setw(10)<<"[1] Search Book by name"<<endl;
        cout<<setw(10)<<"[2] Return Book"<<endl;
        cin>>option;
        switch(option){
            case 1:{
            while(check){
                cout<<"Enter Book Name"<<endl;
                    cin.ignore();
                    getline(cin, book_name);
                    search_book(book_name);
                    cout<<endl<<"Want to search again y/n?"<<endl;
                    cin>>ch;
                    if(ch == 'n' || ch == 'N')
                        check = false;
            }

            }

                break;
                case 2:
                    cout<<"Enter Book name"<<endl;
                    cin>>book_name;
                    returnbook(usernamegloble,book_name);
                    cout<<endl<<" Returned book "<<endl;

                break;
                default:
                    cout<<"[-] Enter option is wrong!!"<<endl;
                break;
        }

    }
};

// class library:public admin, public user{
//     library(){

//     }
// };


// ###################################################################################################
// ##                                    GLOBAL FUNCTION                                            ##
// ###################################################################################################

book b1, b2;
fstream fp, fp1;
user u;
issuandreturn ib;


// ###################################################################################################
// ##                                    WRITING FUNCTION                                           ##
// ###################################################################################################

void write_book()
{
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do{
        b1.createbook();
        fp.write((char*)&b1, sizeof(b1));
        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;

    }while(ch=='y'||ch=='Y');
    fp.close();
}

void issuebook(string user,string bookname)
{
    char ch;
    int flage = 0;
    fp.open("issuandreturn.dat", ios::out | ios::app);
    fp1.open("issuandreturn.dat", ios::in);
    while(fp1.read((char*)&ib,sizeof(issuandreturn)))
    {
        if(ib.user() == user )
        {
            if(ib.bcount() < 5){
                ib.issue(user,bookname);
                flage = 1;
            }
            else{
                cout<<"max book already issued"<<endl;
                flage = 1;
            }

        }
    }

    if(flage == 0){
        ib.issue(user,bookname);
        fp.write((char*)&ib, sizeof(issuandreturn));
    }

    fp.close();
    fp1.close();
}

void returnbook(string user,string bookname)
{
    char ch;
    fp.open("issuandreturn.dat", ios::out | ios::app);
    fp1.open("issuandreturn.dat", ios::in);
    while(fp1.read((char*)&ib,sizeof(issuandreturn)))
    {
        if(ib.user() == user && ib.book(bookname) == 1)
        {
            ib.deletebook(bookname);
            fp.write((char*)&ib, sizeof(issuandreturn));
        }
    }

    fp.close();
    fp1.close();
}


// ###################################################################################################
// ##                                      READ FUNCTION                                            ##
// ###################################################################################################
void display_usrbook(int nn)
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&b1,sizeof(book)))
    {
        if(b1.retbno() == nn)
        {
            b1.show_book();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";

}

void search_book(string nn)
{
    char ch;
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&b1,sizeof(book)))
    {
        if(b1.getbookname() == nn)
        {
            b1.show_book();
             cout<<endl<<"Want to issue book y/n?"<<endl;
                    cin>>ch;
                    if(ch == 'y' || ch == 'y' )
                        issuebook(usernamegloble,nn);
            flag=1;
        }
    }

    fp.close();
    if(flag==0){

        cout<<"\n\nBook does not exist";
    }

}

void search_book_by_id(int nn)
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&b1,sizeof(book)))
    {
        if(b1.retbno() == nn)
        {
            b1.show_book();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";

}

void search_book_by_subject(string nn)
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&b1,sizeof(book)))
    {
        if(b1.getbookbysubject() == nn)
        {
            b1.show_book();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nBook does not exist";

}

// ###################################################################################################
// ##                                      UPDATE FUNCTION                                          ##
// ###################################################################################################

void book_update(){
    int n;
    bool found = true;
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book ID. of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&b1,sizeof(book)) && found==true)
    {
        if(b1.retbno() == n)
        {
            b1.createbook();
            cout<<"\nEnter The New Details of book"<<endl;
            b1.updatebook();
            int pos=-1*sizeof(b1);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&b1,sizeof(book));
                cout<<"\n\n\t Record Updated";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Record Not Found ";

}

// ###################################################################################################
// ##                                      CHECK USERNAME                                           ##
// ###################################################################################################
    bool check_user(string usern, int pass){
        bool flag= false;
        fp.open("user.dat",ios::in);
        while(fp.read((char*)&u,sizeof(user)))
        {
            if(u.getusername().compare(usern) == 0)
            {
                if(u.getpassword() == pass)
                flag=true;
            }
        }

        fp.close();
        return flag;

    }

    void create_user(){
        u.createuser();
        fp.open("user.dat", ios::out | ios::app);
        fp.write((char*)&u, sizeof(user));
        fp.close();
    }



// ###################################################################################################
// ##                                       DELETE                                                  ##
// ###################################################################################################



void delete_book()
{
    int n;
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&b1,sizeof(book)))
    {
        if(b1.retbno()!= n)
        {
            fp2.write((char*)&b1,sizeof(book));
        }
    }

    fp2.close();
        fp.close();
        remove("book.dat");
        rename("Temp.dat","book.dat");
        cout<<"\n\n\tRecord Deleted ..";
        //getch();
}

// ###################################################################################################
// ##                                       ADMIN                                                   ##
// ###################################################################################################


class admin{
public:
    void menu(){
        bool check = true;
        int option;
        while(check){
            cout<<"[+] Wlecome to the library management system admin page[+]"<<endl;
            cout<<setw(10)<<"[1] Search Book"<<endl;
            cout<<setw(10)<<"[2] Delete Book"<<endl;
            cout<<setw(10)<<"[3] Add Book"<<endl;
            cout<<setw(10)<<"[4] Update Book"<<endl;
            cout<<setw(10)<<"[5] Exit"<<endl;

            cin>>option;
            switch(option){
                case 1:
                    cout<<"Enter book id"<<endl;
                    int temp;
                    cin>>temp;
                    display_usrbook(temp);
                break;
                case 2:
                     delete_book();
                     cout<<endl<<"Book Delete sucessfull !!"<<endl;
                break;
                case 3:
                     write_book();
                     cout<<endl<<"Book writen sucessfull !!"<<endl;
                break;
                case 4:
                     book_update();
                     cout<<endl<<"Book update sucessfull !!"<<endl;
                break;
                case 5:
                     check = false;
                break;
                default:
                    cout<<"[-] Enter option is wrong!!"<<endl;
                break;
            }
        }
    }

private:
    int option;
    bool check;
};

int main(){
    char option = 'y';
    int choice;
    do{
            cout<<"[+] Wlecome to the library / enter option given below [+]"<<endl;
            cout<<setw(10)<<"[1] user "<<endl;
            cout<<setw(10)<<"[2] Admin "<<endl;
            cout<<setw(10)<<"[3] Create account as user"<<endl;
            cout<<setw(10)<<"[4] Exit"<<endl<<endl;
            cin>>choice;
            if(choice == 1){
                string username;
                int password;
                cout<<"Enter username:  ";
                cin>>username;
                cout<<endl<<"Enter password: ";
                cin>>password;
                cout<<endl<<endl;
                if(check_user(username, password)){
                    users u1;
                    usernamegloble = username;
                }else{
                    cout<<endl<<"Username or password is incorrect "<<endl;
                }

            }else if(choice == 2){
                string username;
                int password;
                cout<<"Enter username:  ";
                cin>>username;
                cout<<endl<<"Enter password: ";
                cin>>password;
                cout<<endl<<endl;
                if(username == "admin" && password == 12345){
                    admin ad;
                    ad.menu();
                }else{
                    cout<<endl<<"Username or password is incorrect "<<endl;
                }

            }else if (choice == 3){

                create_user();

            }else if (choice == 4){
                option = 'n';
            }else{
                cout<<endl<<endl<<"[-][-] worng option selected !! [-][-]"<<endl;
            }
    }while(option == 'Y' || option == 'y');
    return 0;
}

