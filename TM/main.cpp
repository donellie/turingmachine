// =====================================
//  Turing Machine (C++ Implementation)
// ===============
// File main.cpp
// ===============




// ###############
#include "run.h"
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
void evenTest()
{
	system("cls");
	cout<<"TESTING IF STRING IS EVEN";
	string value;
        
    ifstream Read;
	Read.open("input13.txt");
    if (Read.is_open())
    {
		while ( !Read.eof() )
       {
			getline(Read,value);
			if(value != "b")
			{
			 cout << "\nString From file: " << value << endl;
			 if(value.length()%2==1)
			 {
				  cout << "\nEVEN\n";
			 }	
			 else if(value.length()%2==0)
			 {
				cout << "\nODD\n";
			 }
		   }
	   }
       Read.close();
    }
    else cout << "Unable to open file";
    
	system("pause");
}
int main (uint argc, char** argv)
{
	int choice;

	cout<<"WELCOME TO TURING MACHINE SIMULATION";
	cout<<"\nPRESS (1) TO TEST IF STRING IS A PALLINDROME OR (2) TO TEST IF IT IS EVEN: \n";
	cin>>choice;
	switch(choice)
	{
	case 1: {
		       Run::run (argc, argv);
	           system("pause");
			}
	case 2: {
		     evenTest();
			}
	default: cout<<"CHOICE NOT ACCEPTED PLEASE SELECT A CORRECT CHOICE (1) OR (2)";
	}
	
  return 0;
}
