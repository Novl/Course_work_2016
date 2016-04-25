#include "../include/stack.h"

string s;
stack Stack;


int main()//(int argv, char* args[])
{		
  	menu();
    cin>>s;
	while (s.compare("e") != 0) //(scanf("%s", str)>0) 
	{
        if (!Stack.isValid(s))
            cout<<"Enter 'm' to see menu or 'e' to exit"<<endl;
        cin>>s;
    }
    cout<<"Goodbye"<<endl;
	return 0;
}
