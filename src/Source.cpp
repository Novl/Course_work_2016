#include "../include/headers.h"
#include "../include/stack.h"

using namespace std;

string s;
stack Stack;


int main(int argv, char* args[])
{		
  	menu();
    cin>>s;
	while (Stack.isValid(s)) //(scanf("%s", str)>0) 
	{
        cin>>s;
    }
    cout<<"Goodbye"<<endl;
	return 0;
}
