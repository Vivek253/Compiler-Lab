//Ex 2

#include<stdio.h>
#include<fstream>
#include<regex>
#include<iostream>
#include<iomanip>
using namespace std;
int state = 0; //0 for comment , 1 for expression
int statetable[][14] = {{6,3,1,2,4,5,0,0,8,10,11,12,21,13},
						{1,1,1,1,1,1,22,1,1,1,1,1,1,1},
						{2,2,2,2,2,2,2,2,2,2,2,2,22,2},
						{3,3,21,21,21,21,25,25,25,25,25,25,21,21},
						{5,5,21,21,21,21,5,5,5,5,5,5,5,5},
						{21,21,21,21,23,21,21,21,21,21,21,21,21,21},
						{6,21,21,21,21,21,23,23,21,21,21,21,21,21},
						{7,7,7,7,7,23,21,7,7,7,7,7,7,7},
						{21,21,21,21,21,21,21,21,9,21,21,21,21,21},
						{21,21,21,21,21,21,21,24,21,21,21,21,21,21},
						{21,21,21,21,21,21,21,28,21,21,21,26,21,21},
						{24,24,21,21,21,21,21,29,21,21,21,27,21,21},
						{21,21,21,21,21,21,21,24,21,21,21,15,21,21},
						{21,21,21,21,21,21,21,21,21,21,21,21,21,14},
						{21,21,21,21,21,21,21,24,21,21,21,21,21,21},
						{21,21,21,21,21,21,21,24,21,21,21,21,21,21},
						{21,21,21,21,21,21,21,24,21,21,21,19,21,21},
						{21,21,21,21,21,21,21,26,21,21,21,21,21,21},
						{21,21,21,21,21,21,21,27,21,21,21,21,21,21},
						{21,21,21,21,21,21,21,24,21,21,21,21,21,21}};				
char buf[10];int bc = 0;
class tester
{
	public:
	char word;
	
	void set(char inval)
	{
		word = inval;
	}
	
	bool is(char x)
	{
		if(word == x)
			return true;
		return false;
	}
	bool isDigit()
	{
		if(word>44&&word<55)
			return true;
		return false;
	}
	bool isLetter()
	{
		return isalpha(word);
	}
	
}w;


int statemachine(char word)
{
	int st;
	w.set(word);	
	if(w.isDigit())
		st = 0;
	else if(w.isLetter())
		st = 1;
	else if(w.is('['))
		st = 2;
	else if(w.is('{'))
		st = 3;
	else if(w.is('\''))
		st = 4;
	else if(w.is('\"'))
		st = 5;
	else if(w.is('\n'))
		st = 6;
	else if(w.is(' '))
		st = 7;
	else if(w.is('|'))
		st = 8;
	else if(w.is('<'))
		st = 9;
	else if(w.is('>'))
		st = 10;
	else if(w.is('='))
		st = 11;
	else if(w.is('}'))
		st = 12;
	else if(w.is('&'))
		st = 13;
		
		
	return statetable[state][st];
}

string bufdisp()
{
	cout<<"\n";
	for(int i = 0 ; i< bc ; i++)
	cout<<buf[i];
	
	return "";
}

int main()
{
	FILE *file = fopen("code.cpp", "r");
	char iget;
	int mode = 1;
	while(((iget = (fgetc(file)))!=EOF)&&mode==1)				//now i'm reading word by word
	{
		cout<<"->"<<state;
		buf[bc++]=iget;
		if(iget == '\/')
		{
			iget =fgetc(file);
			if(iget=='\/')
				iget = '[';
			else if(iget == '*')
			{
				iget = '{'; 
				buf[bc++]='*';
			}
		}
		if(iget == '!')
		{
			iget =  fgetc(file);
			buf[bc++]=iget;
			cout<<bufdisp()<<"-Not equals operator\n";
			bc = 0;
			state = 0;
			
		}
		if(iget == '*')
		{
			iget =  fgetc(file);
			buf[bc++]='/';
			iget = '}';
		}
		state = statemachine(iget);	
	
		if(state==22)
			cout<<bufdisp()<<"-Comment\n";
		else if(state==23)
			cout<<bufdisp()<<"-Constant\n";
		else if(state==24)
			cout<<bufdisp()<<"-Operator\n";
		else if(state==25)
			cout<<bufdisp()<<"-Identifier\n";
			else if(state==26)
			cout<<bufdisp()<<"-Less than or equal to operator\n";
			else if(state==27)
			cout<<bufdisp()<<"-Greater than or equal to operator\n";
			else if(state==28)
			cout<<bufdisp()<<"-Less than operator\n";
			else if(state==29)
			cout<<bufdisp()<<"-Greater than operator\n";
		else if(state==21)
		{
			cout<<"\nError";
			
		}
		if(state>20)
		{
			bc=0;
			state = 0;
		}
		
		
	}

	
	while(mode==2)				//now i'm reading word by word
	{
		cout<<"\nState "<<state;
		buf[bc++]=iget;
		if(iget == '\/')
		{
			iget =fgetc(file);
			if(iget=='\/')
				iget = '[';
			else if(iget == '*')
				iget = '{'; 
		}
		if(iget == '*')
		{
			iget =  fgetc(file);
			iget = '}';
		}
		state = statemachine(iget);	
		if(state==22)
			cout<<buf<<"-Comment\n";
		else if(state==23)
			cout<<buf<<"-Constant\n";
		else if(state==24)
			cout<<buf<<"-Operator\n";
		else if(state==25)
			cout<<buf<<"-Identifier\n";
		else if(state==21)
		cout<<"\n";
		if(state>20)
		{
			bc=0;
		}
		
	}

	return 0;
}

