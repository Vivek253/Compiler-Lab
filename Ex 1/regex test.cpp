#include<iostream>
#include<regex>
using namespace std;

main()
{
	regex st("(.*)\\((.*)\\)\\;");
	string a = "scanf('hello';";
	if(regex_match(a,st))
	cout<<"yay";
	
	regex st2("\"(.*)\"");
	string a2 = "\"3ddd\"";
	if(regex_match(a2,st2))
	cout<<"yay2222";
	
	cout<<a2.length();
	
	return 0;
}
