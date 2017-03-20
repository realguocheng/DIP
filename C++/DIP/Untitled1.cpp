#include<stdio.h>
#include<fstream>
#include <stdlib.h>
#include <iostream>
using namespace std;
//int main(){
//    ifstream f("D:\\Download\\data.txt");
//   // char buffer[5];
//    while(!f.eof()){
//        //f.getline(buffer,4);
//        //count++;
////        if(count==6200000)
////        {
////            cout<<"ff"<<endl;
////            count=0;
////        }
//        //cout<<"get"<<endl;
//        //if(a!=29653)
//            //cout<<buffer<<endl;
//    //cout<<a<<endl;
//    int a;
//    f>>a;
//    cout<<a<<endl;
//    }
//    cout<<"done"<<endl;
//
//}


   int main () {
       char buffer[256];
       ifstream in("D:\\Download\\mouse0\\mouse0.raw");
       if (! in.is_open())
       { cout << "Error opening file"; exit (1); }
       while (!in.eof() )
       {
           in.getline (buffer,100);
           cout << buffer << endl;
       }
       return 0;
   }
