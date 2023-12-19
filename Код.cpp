#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string.h>
#include <fstream>
using namespace std;

class Bank
{
	public:
		Bank();
		~Bank();
		void input(void);
		void output(void);
		int getL(void);
		int getC(void);
		int getN(void);
		int setC(int);
	private:
		int number;
		char passport[30];
		char category[10];
		int current;
		char date[20];
};

class depositor
{
	public:
		depositor();
		~depositor();
		int push_back();
		int pop_back();
		int view();
		void resize(int);
		void task_output();
		void task_change();
		void save();
		int load();
	private:
		Bank *arr;
		int count;
};

Bank::Bank()
{
}

Bank::~Bank()
{
}

void Bank::input(void)
{
	cout << "Enter account number >";
	cin >> number;
	cout << "Enter passport >";
	cin >> passport;
	cout << "Category >";
	cin >> category;
	cout << "Current >";
	cin >> current;
	cout << "Date >";
	cin >> date;
}

void Bank::output(void)
{
	cout << "Number <" << number << "> Passport <" << passport << "> Category <" << category << "> Current <" << current << "> Date <" << date <<">"<<endl;
}

int Bank::getL(void)
{
	char flag[] = "Immediate";
	if(!strcmp(category, flag))
		return 1;
	return 0;
}

int Bank::getC(void)
{
	return current;
}

int Bank::getN(void)
{
	return number;
}
 
int Bank::setC(int t)
{
	current=t;
}

depositor::depositor()
{
	arr = NULL;
	count = 0;
}

depositor::~depositor()
{
	if (arr) delete [] arr;
}

int depositor::push_back()
{
	if (arr == NULL)
	{
		count = 1;
		arr = new Bank[count];
		arr[0].input();
	}
	else
	{
		resize(++count);
		arr[count-1].input();
	}
	return count;
}

void depositor::resize(int b)
{
	int i;
	if(arr)
	{
		Bank *newarr=new Bank[b];
		for( i = 0; (i < count && i < b); i++)
		newarr[i] = arr[i];
		delete [] arr;
		arr = newarr;
	}
	else
		arr=new Bank[b];
}


int depositor::pop_back()
{
	if(count <= 0) return 0;
		if(--count > 0)
			resize(count);
		else
	delete [] arr;
}

int depositor::view()
{
	for(int i = 0; i < count; i++)
		arr[i].output();
}

void depositor::task_output()
{
	int i, max = 0;
	for(i = 0; i < count; i++)
	{
		if (arr[i].getL())
		{
			if (arr[i].getC() > max)
				max = arr[i].getC();
		}
	}
	if (!max)
	{
		cout << "Nothing to view";
		return;
	}
	for (i = 0; i < count; i++)
		if (arr[i].getC() == max)
			break;
	cout << "Max is < " << max << ">";
}

void depositor::task_change()
{
	int i, c = -1, flag2, sum, number, t;
	cout << "Enter user number";
	cin >> number;
	for (i = 0; i < count; i++)
	{
		if (arr[i].getN() == number)
		{
			c = i;
			break;
		}
	}
	if(c!=-1)
	{
		cout << "If you want to put money press 1, if you want to take money press 2";
		cin >> flag2;
	if(flag2 == 1)
	{
		cout << "Enter sum";
		cin >> sum;
		t = arr[i].getC();
		t += sum;
		cout << "Now sum is <" << t << ">";
		arr[i].setC(t);
		t = 0;
	}
	else
		if(flag2 == 2)
		{
			cout << "Enter sum";
			cin >> sum;
			t = arr[i].getC();
			t -= sum;
			cout << "Now sum is <" << t << ">";
			t = 0;
			arr[i].setC(arr[i].getC() - sum) ;
		}
	}
	else
		cout<<"User is not found";
}

void depositor::save()
{
	ofstream out("output.bin", ios::binary);
	for(int i=0; i<count; i++)
	{
		out.write((char*)&arr[i], sizeof(Bank));
	}
}

int depositor::load()
{
	ifstream in("output.bin", ios::binary);
	in.seekg (0, ios::end);
	count = in.tellg() / sizeof(Bank);
	in.seekg (0, ios::beg);
	resize(count);
	for (int i=0; i<count; i++)
	{
		in.read((char*)&arr[i],sizeof(Bank));
	}
cout<<"Successful"<<endl;
}

int main()
{
	char menu;
	depositor my;
	do
	{
	system("cls");
	puts ("1. Load");
	puts ("2. Save");
	puts ("3. Add to the end ");
	puts ("4. Remove from end");
	puts ("5. View");
	puts ("6. Task");
	puts ("7. Task 2");
	puts ("8. Exit");
	menu = getchar();
	switch (menu)
	{
		case '1': my.load();system("PAUSE"); break;
		case '2': my.save();system("PAUSE"); break;
		case '3': my.push_back();system("PAUSE"); break;
		case '4': my.pop_back();system("PAUSE"); break;
		case '5': my.view();system("PAUSE"); break;
		case '6': my.task_output();system("PAUSE"); break;
		case '7':my.task_change();system("PAUSE"); break;
	}
	}while (menu!='8');
	return 0;
}

