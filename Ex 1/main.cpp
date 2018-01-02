#include<stdio.h>
#include<fstream>
#include<regex>
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

struct identifier
{
	int type;
	string name,value;	
}idnt[100];
//type 2 = int 4 = float 1 = char 8 = double
int idcount = 0;
int nva = 0; //next value assign mode
int typebuff=-1;
bool any = false;
string wordbuff;
	int keywordscount = 8; 
	string keywords[] = {"string,""if","else","for","int","float","char","double"};
	int arithcount = 5;
	string arith[] = {"+","-","*","/","%"};
	int arithasscount = 5;
	string arithass[] = {"+=","-=","*=","/=","%="};
	int logicalcount = 3;
	string logical[] = {"&&","||","!"}; 
	int relationalcount = 6;
	string relational[] = {"<","<=",">",">=","==","!="};
	int bitwisecount = 5;
	string bitwise[] = {"^","&","|","<<",">>"};
	int unarycount = 3;
	string unary[] = {"-","++","--"};
	int assignmentcount = 1;
	string assignment[] = {"="};
	int splcount = 10;
	string spl[] = {";",",",".","[","]","(",")","{","}","[]"};
	int fncount = 4;
	string fn[] = {"printf","scanf","getch","clrscr"};


//do symbol table and identification
class tester
{
	public:
	string word;

	
	bool tests(string *st,int n)
	{
		int i;
		for(i=0;i<n;i++)
		{

			if(word.compare(st[i])==0)
				return true;
		}
		return false;
	}
	
	void set(string inval)
	{
		word = inval;
	}

	void testKeyword()
	{	
		if(tests(keywords,keywordscount))
			{
				cout<<"\n"<<word<<" - Keyword";
				any = true;
				if(!word.compare("int"))
					typebuff = 2;
				else if(!word.compare("char"))
					typebuff = 1;
				else if(!word.compare("float"))
					typebuff = 4;
				else if(!word.compare("double"))
					typebuff = 8;
				else if(!word.compare("string"))
					typebuff = 0;
			}
		
	}

	void testArith()
	{	
		if(tests(arith,arithcount))
			{
				cout<<"\n"<<word<<" - Arithmetic operator";
				any = true;
			}
	}

	void testArithAss()
	{	
		if(tests(arithass,arithasscount))
		{
			cout<<"\n"<<word<<" - Arithmetic assignment operator";
			any = true;
		}
	}		

	void testLogical()
	{	
		if(tests(logical,logicalcount))
		{
			cout<<"\n"<<word<<" - Logical operator";
			any = true;
		}
	}

	void testRelational()
	{	
		if(tests(relational,relationalcount))
		{
			cout<<"\n"<<word<<" - Relational operator";
			any = true;
		}
	}

	void testBitwise()
	{	
		if(tests(bitwise,bitwisecount))
		{
			cout<<"\n"<<word<<" - Bitwise operator";
			any = true;
		}
	}

	void testUnary()
	{	
		if(tests(unary,unarycount))
		{
			cout<<"\n"<<word<<" - Unary operator";
			any = true;
		}
	}

	void testAssignment()
	{	
		if(tests(assignment,assignmentcount))
		{	
			cout<<"\n"<<word<<" - Assignment operator";
			any = true;
			if(nva==1)
				nva++;
		}
	}

	void testSpl()
	{	
		if(tests(spl,splcount))
		{
			cout<<"\n"<<word<<" - Special operator";
			any = true;
		}
	}
	
	void updatetable()
	{	
		if(nva==2)
				{
					idnt[idcount].name = wordbuff;
					idnt[idcount].type = typebuff;
					idnt[idcount++].value = word;
					nva = 0;
				}
	}
	
	void testIntC()
	{	
			regex integer("(\\+|-)?[[:digit:]]+");
			if(regex_match(word,integer))
			{
				cout<<"\n"<<word<<" - Integer constant";
				any = true;
				updatetable();
			}
	}
	
	void testCharC()
	{	
			regex character("\'[[:alnum:]]\'");
			if(regex_match(word,character))
			{
				cout<<"\n"<<word<<" - Character constant";
				any = true;
				updatetable();
			}
	}

	void testStringC()
	{	
			regex character("\"(.*)\"");
			if(regex_match(word,character))
			{
				cout<<"\n"<<word<<" - String constant";
				any = true;
				updatetable();
			}
	}



	void testPpd()
	{
		if((word.at(0))=='#')
		{
			cout<<"\n"<<word<<" - Preprocessor Directive";
			any = true;
		}
	}

	void testFnCall()
	{
		regex fn("(.*)\\((.*)\\)(.*)");
		if(regex_match(word,fn))
		{
			cout<<"\n"<<word<<" - Function call";
			any = true;
		}
	}

	void allfail()
	{
		if(!any)
		{
			cout<<"\n"<<word<<" - Identifier";
			wordbuff = word;
			nva=1;		//nextvalue assign mode
		}
	}

};

string gettype(int val)
{
	if(val==1)
		return "char";
	else if(val==2)
		return "int";
	else if(val==4)
		return "float";
	else if(val==8)
		return "double";
	else if(val==0)
		return("string");
	
	return "NA";
}
/*
void showtable()
{
	int i;
	int baseaddress = 1000;
	cout<<"\n\nIdentifiers\n\n";
	cout<<setw(10)<<"Id Name"<<setw(10)<<"Type"<<setw(10)<<"Bytes"<<setw(10)<<"Location"<<setw(10)<<"Value";
	for(i = 0 ; i < idcount ; i++)
	{
		cout<<"\n";
		cout<<setw(10)<<idnt[i].name<<setw(10)<<gettype(idnt[i].type);
		if(typebuff!=0)
			cout<<setw(10)<<idnt[i].type;
		else
			cout<<setw(10)<<sizeof(idnt[i].value);
		cout<<setw(10)<<baseaddress<<setw(10)<<idnt[i].value;
		if(typebuff!=0)
			baseaddress+=idnt[i].type;
		else
			baseaddress+=sizeof(idnt[i].value);
	}
}
*/

int main()
{
	tester word;
	ifstream f ;
	f.open("code.cpp");
	
	string inp;
	
	while(f>>inp)				//now i'm reading word by word
	{
		any = false;
		int f = 0;
		word.set(inp);
		cout<<inp<<"\n";
		word.testKeyword();
		cout<<f++<<"\n";
		word.testArith();
		cout<<f++<<"\n";
		word.testArithAss();
		cout<<f++<<"\n";
		word.testLogical();
		cout<<f++<<"\n";
		word.testRelational();
		cout<<f++<<"\n";
		word.testBitwise();
		cout<<f++<<"\n";
		word.testUnary();
		cout<<f++<<"\n";
		word.testAssignment();
		cout<<f++<<"\n";
		word.testSpl();
		cout<<f++<<"\n";
		word.testFnCall();
		cout<<f++<<"\n";
		word.testIntC();
		cout<<f++<<"\n";
		word.testCharC();
		cout<<f++<<"\n";
		word.testStringC();
		cout<<f++<<"\n";
		word.testPpd();
		cout<<f++<<"\n";
		word.allfail();
		cout<<f++<<"\n";
		cout<<"End\n";
	}
//	showtable();
	return 0;
}
