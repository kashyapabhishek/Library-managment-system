#include<fstream>
#include<iostream>

using namespace std;
class testt{
public:
    int a;
    int b;
    testt(int x, int y){
        a = x;
         b= y;
    }
};

int main(){

    char data[100];

    ofstream out;
    out.open("t.txt");

    cout << "Writing to the file" << endl;
   cout << "Enter your name: ";
   cin.getline(data, 100);

   out<<data<<endl;

   testt t(10, 20);
   cout<<t<<endl;
   out<<data<<endl;

   return 0;
}


