/*------------------iBank Encrypted Management Portal-------------------------
**
**	 -  Encrypted bank management system created in c++ for storing and managing
**  all bank data. All data is encrypted using a salt and saved so that there
**  is no data leak possible.
**   -  Developed as a CBSE project for the year 2014-2015
**
**---------DEVELOPED BY ROHIN G, ARKO KUNDU, VIKAS AND PRANJAL MEHTA-----------
*/

//header files
#include<iostream.h>
#include<fstream.h>
#include<process.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include<dos.h>


char* sEncrypt(char *a){

  for (int i =0; i < strlen(a); i++)
  a[i] = a[i] ^ 'x';

  return a;
}

char* sDecrypt(char *a){
for (int i=0; i < strlen(a); i++)
  a[i] = a[i] ^ 'x';
  return a;
}
//contains line shape and box shape functions
class shape
{
   public :
	    void line_hor(int, int, int, char);
	    void line_ver(int, int, int, char);
	    void box(int,int,int,int);
};



//controls all the menu  and boxes in the program
class control
{
  public :
		int login_box(void);
		void main_box(void);
		void startup_box(void);
		void main_menu(void);
		void startup_menu(void);
		void exit_menu(void);
  private:
		void edit_menu(void);
};




//contains functions related to initial deposit
class initial
{
	public :
			void encrypt();
			void decrypt();
			void add_to_file(int, char t_name[30], char t_address[60], float);
			void display_list(void);
			void delete_account(int);
			void update_balance(int, float);
			void modify(void);
			int  last_accno(void);
			int  found_account(int);
			char *return_name(int);
			char *return_address(int);
			float give_balance(int);
			int  recordno(int);
			void display(int);
	private :
			void  modify_account(int, char t_name[30], char t_address[60]);
			void  box_for_list(void);

			int   accno;
			char  *name, *address;
			float balance;
};


// contains functions related to transaction
class account
{
	public :
			void new_account(void);
			void close_account(void);
			void display_account(void);
			void transaction(void);
			void clear(int,int);
	private :
			void  add_to_file(int, int, int, int, char, char t_type[10], float, float, float);
			void  delete_account(int);
			int   no_of_days(int, int, int, int, int, int);
			float calculate_interest(int, float);
			void  display(int);
			void  box_for_display(int);

			int   accno;
			char  type[10];    // Cheque or Cash      
			int   dd, mm, yy;  // Date
			char  tran;	    // Deposit or Withdraw
			float interest, amount, balance;
};


//function to draw a box based on dos co-ordinates.
void shape :: box(int column1, int row1, int column2, int row2)
{
	char c1, c2, c3, c4;
	char l1=196, l2=179;
	c1=218;
	c2=191;
	c3=192;
	c4=217;
	gotoxy(column1,row1);
	cout<<c1;
	gotoxy(column2,row1);
	cout <<c2;
	gotoxy(column1,row2);
	cout <<c3;
	gotoxy(column2,row2);
	cout <<c4;
	column1++;
	column2--;
	line_hor(column1,column2,row1,l1);
	line_hor(column1,column2,row2,l1);
	column1--;
	column2++;
	row1++;
	row2--;
	line_ver(row1,row2,column1,l2);
	line_ver(row1,row2,column2,l2);
}



//function to draw horizontal line
void shape::line_hor(int column1,int column2,int row,char c)
{

 for(column1; column1<=column2; column1++)
    {
    gotoxy(column1,row);
    cout<<c;
    }
}

//function to draw vertical line
void shape::line_ver(int row1,int row2,int column,char c)
{
for(row1;row1<=row2;row1++)
   {

    gotoxy(column,row1);
    cout<<c;
   }
}




//funciton to display main menu and call functions
//based on user input
void control :: main_menu(void)
{
	char ch;
	while (1)
	{
		clrscr();
		shape s;

		s.box(9,4,72,22);

		textcolor(LIGHTBLUE);
		textbackground(BLUE);
			gotoxy(32,7);
		cprintf(" B A N K I N G ");
		gotoxy(35,9);
		cprintf(" OPTIONS ");
		textcolor(MAGENTA);
		textbackground(BLACK);
		gotoxy(30,11);
		cout <<"1: SEE ACCOUNT";
		gotoxy(30,12);
		cout <<"2: LIST OF ACCOUNTS";
		gotoxy(30,13);
		cout <<"3: TRANSACTIONS";
		gotoxy(30,14);
		cout <<"4: OPEN NEW ACCOUNT";
		gotoxy(30,15);
		cout <<"5: EDIT ACCOUNTS";
		gotoxy(30,16);
		cout <<"6: HELP";
		gotoxy(30,17);
		cout <<"0: QUIT";
		gotoxy(30,19);
		cout <<"Enter your choice: ";
		ch = getche();
		if (ch == 27)
			break;
		else if (ch == '1')
		{
			account a;
			a.display_account();
		}
		else if (ch == '2')
		{
			initial ini;
			ini.display_list();
		}
		else if (ch == '3')
		{
			account a;
			a.transaction();
		}
		else if (ch == '4')
		{
			account a;
			a.new_account();
		}
		else if (ch == '5')
			edit_menu();
		else if (ch == '6')
		{
			control q;
			q.startup_menu();
			q.main_menu();
		}
		else if (ch == '0') break;
	}

	for (int i=25; i>=1; i--)
	{
		delay(40);
		gotoxy(1,i); clreol();
	}
}



//funciton to display edit sub-menu
void control :: edit_menu(void)
{
	char ch;
	while (1)
	{
		clrscr();
		shape s;
		s.box(9,4,72,22);
		textcolor(RED);
		textbackground(BLUE);
		gotoxy(34,10);
		cprintf(" EDIT MENU ");
		textcolor(YELLOW);
		textbackground(BLACK);
		gotoxy(31,12);
		cout <<"1: MODIFY ACCOUNT";
		gotoxy(31,13);
		cout <<"2: CLOSE ACCOUNT";
		gotoxy(31,14);
		cout <<"0: QUIT";
		gotoxy(31,16);
		cout <<"Enter your choice: ";
		ch = getche();
		if (ch == 27)
			break;
		else
		if (ch == '1')
		{
			initial ini;
			ini.modify();
			break;
		}
		else
		if (ch == '2')
		{
			account a;
			a.close_account();
			break;
		}
		else
		if (ch == '0')
			break;
	}
}


//function to draw startup box(main page)
void control::startup_box(void)
{
	clrscr();
	shape s;
	s.box(5, 2, 75, 24);
	gotoxy (22, 2);
	textbackground(LIGHTBLUE);
	textcolor(WHITE);
	cprintf("iBank Encrypted Management Portal");
}

//i forgot, have to seee what this funciton does
void control::main_box(void)
{
	clrscr();
	shape s;
	s.box(10, 2, 40, 24);
	gotoxy (22, 2);
	textbackground(LIGHTBLUE);
	textcolor(WHITE);
	cprintf("iBank Encrypted Management Portal");
}

//function to draw login box and authenticate
int control::login_box(void)
{
	start:
	shape s;
	startup_box();
	s.box(25, 11, 55, 16);
	gotoxy(28, 11);
	cout << "Enter Login Credentials";
	textcolor(WHITE);
	gotoxy(30, 13);
	cout << "USERNAME: ";
	gotoxy(30, 14);
	cout << "PASSWORD: ";
	gotoxy (41, 13);
	char a[20];
	gets(a);
	gotoxy (41, 14);
	char b[20];
	gets(b);
	if (!strcmp(a, "Rohin") && !(strcmp(b, "password")))
	{
		gotoxy(24, 18);
		textcolor(GREEN);
		textbackground(BLACK);
		cprintf("LOGIN SUCCESSFULL!, TRANSFERRING... ");
		delay(1000);
		textcolor(WHITE);
		textbackground(BLACK);
		for(int i=25;i>=1;i--)
   		{
   			delay(20);
   			gotoxy(1,i);clreol();
   		}
		return 1;
	}
	else
	{
		gotoxy(24, 18);
		textcolor(RED);
		textbackground(BLACK);
		cprintf("LOGIN UNSUCCESSFULL!, TRY AGAIN... ");
		textcolor(BLINK+RED);
		delay(1000);
		goto start;
	}
}

 
//function display initial help, and startup
void control::startup_menu(void)
{
clrscr();
startup_box();
gotoxy(24, 4);
textcolor(GREEN);
textbackground(BLACK);
cprintf("WELCOME TO THE PROJECT BANKING ");
gotoxy(8, 6);
cout << "* This is secured banking system project which allows unlimited";
gotoxy(8, 7);
cout << "  record entries and encrypts each entry using a salt.";
gotoxy(8, 9);
cout << "* In the first option you can view details of an account";
gotoxy(8, 11);
cout << "* In the second option you can list all accounts";
gotoxy(8, 13);
cout << "* Bank transactions can be made through the third option";
gotoxy(8, 15);
cout << "* You can open a new account in the fourth option";
gotoxy(8, 17);
cout << "* You can modify/delete accounts in the fifth option";
gotoxy(8, 19);
cout << "* Last option is to quit the program";
gotoxy(8, 22);
textcolor(GREEN);
cprintf( " ---DEVELOPED BY ROHIN G, ARKO KUNDU, VIKAS AND PRANJAL MEHTA---");
gotoxy(25, 24);
textcolor(BLUE+BLINK);
cprintf ("PRESS ANY KEY TO CONTINUE");
getch();
for(int i=25;i>=1;i--)
   {
   delay(20);
   gotoxy(1,i);clreol();
   }
textcolor(WHITE);
}




//return last account number in initial.dat
int initial :: last_accno(void)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	int count=0;
	while (file.read((char *) this, sizeof(initial)))
	{   
		decrypt();
		count = accno;
	}
	file.close();
	return count;
}



//function returns record position of the account number, account number is always equal to record number
//except incase of no record created and initial record it auto-created by code.
int initial :: recordno(int t_accno)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	int count=0;

	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		count++;
		if (t_accno == accno)
			break;
	}
	file.close();
	return count;
}


//display all parameters of the account number is initial.dat
void initial :: display(int t_accno)
{
	shape s;
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		if (t_accno == accno)
		{
			gotoxy(8,5);
			cout <<"ACCOUNT NO. " <<accno;
			gotoxy(10,8);
			cout <<"Name    : "<<name;
			gotoxy(10,9);
			cout <<"Address : " <<address;
			gotoxy(10,10);
			cout <<"Balance : " <<balance;
			break;
		}
	}
	file.close();
}



//return name for given account number
char *initial :: return_name(int t_accno)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	char t_name[30];
	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		if (accno == t_accno)
		{
			strcpy(t_name,name);
			break;
		}
	}
	file.close();
	return t_name;
}


//return address for the given account number
char *initial :: return_address(int t_accno)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	char t_address[60];
	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		if (accno == t_accno)
		{
			strcpy(t_address,address);
			break;
		}
	}
	file.close();
	return t_address;
}


// return balance for the given account
float initial :: give_balance(int t_accno)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	float t_balance;
	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		if (accno == t_accno)
		{
			t_balance = balance;
			break;
		}
	}
	file.close();
	return t_balance;
}


// check if given account exists #return 1 if true, else 0#
int initial :: found_account(int t_accno)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	file.seekg(0,ios::beg);
	int found=0;
	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		if (accno == t_accno)
		{
			found = 1;
			break;
		}
	}
	file.close();
	return found;
}

//draws box for list
void initial :: box_for_list()
{
	shape s;
	s.box(2,1,79,25);
	s.line_hor(3,78,3,196);
	s.line_hor(3,78,5,196);
	s.line_hor(3,78,23,196);
	textbackground(WHITE);
	gotoxy(3,4);
	for (int i=1; i<=76; i++) cprintf(" ");
	textbackground(BLACK);
	textcolor(RED); textbackground(WHITE);
	gotoxy(4,4);
	cprintf("ACCOUNT NO.          NAME OF PERSON                  BALANCE");
	textcolor(YELLOW); textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(4,2);
	cout <<"Date: " <<d1 <<"/" <<m1 <<"/" <<y1;
}


//displays list of account in initital.dat
void initial :: display_list(void)
{
	clrscr();
	box_for_list();
	int row=6, flag;
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	while (file.read((char *) this, sizeof(initial)))
	{
		decrypt();
		flag = 0;
		delay(10);
		gotoxy(7,row);
		cout <<accno;
		gotoxy(25,row);
		cout <<name;
		gotoxy(57,row);
		cout <<balance;
		row++;
		if (row == 23)
		{
			flag = 1;
			row = 6;
			gotoxy(4,24);
			cout <<"Press any key to continue...";
			getch();
			clrscr();
			box_for_list();
		}
	}
	file.close();
	if (!flag)
	{
		gotoxy(4,24);
		cout <<"Press any key to continue...";
		getch();
	}
}



// appends given data into initital.dat
void initial :: add_to_file(int t_accno, char t_name[30], char t_address[60], float t_balance)
{
	accno = t_accno;
	strcpy(name,t_name);
	strcpy(address,t_address);
	balance = t_balance;
	fstream file;
	file.open("INITIAL.DAT", ios::out | ios::app);
	encrypt();
	file.write((char *) this, sizeof(initial));
	file.close();
	decrypt();
}


//deletes the record for given account number
void initial :: delete_account(int t_accno)
{
	fstream file;
	file.open("INITIAL.DAT", ios::in);
	fstream temp;
	temp.open("temp.dat", ios::out);
	file.seekg(0,ios::beg);
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(initial)); decrypt();
		if ( file.eof() )
			break;
		if ( accno != t_accno )
		{
			encrypt();
			temp.write((char *) this, sizeof(initial));
			decrypt();
		}
	}
	file.close();
	temp.close();
	file.open("INITIAL.DAT", ios::out);
	temp.open("temp.dat", ios::in);
	temp.seekg(0,ios::beg);
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(initial)); decrypt();
		if ( temp.eof() )
			break;
		encrypt();
		file.write((char *) this, sizeof(initial));
		decrypt();
	}
	file.close();
	temp.close();
}


//function to update outstanding balance
void initial :: update_balance(int t_accno, float t_balance)
{
	int recno;
	recno = recordno(t_accno);
	fstream file;
	file.open("INITIAL.DAT", ios::out | ios::ate);
	balance = t_balance;
	int location;
	location = (recno-1) * sizeof(initial);
	file.seekp(location);
	encrypt();
	file.write((char *) this, sizeof(initial));
	decrypt();
	file.close();
}

//modifies the data based on parameters from user for initial.dat
void initial :: modify_account(int t_accno, char t_name[30], char t_address[60])
{
	int recno;
	recno = recordno(t_accno);
	fstream file;
	file.open("INITIAL.DAT", ios::out | ios::ate);
	strcpy(name,t_name);
	strcpy(address,t_address);
	int location;
	location = (recno-1) * sizeof(initial);
	file.seekp(location);
	encrypt();
	file.write((char *) this, sizeof(initial));
	decrypt();
	file.close();
}

//gives(displays) the data to modify in the modify_accnt function
void initial :: modify(void)
{
	clrscr();
	char t_acc[10];
	int t, t_accno;
	gotoxy(71,1);
	cout <<"<0>=Exit";
	gotoxy(5,5);
	cout <<"Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	if (!found_account(t_accno))
	{
		gotoxy(5,5);
		cout <<"\7Account not found";
		getch();
		return;
	}
	shape s;
	s.box(2,2,79,24);
	s.line_hor(3,78,4,196);
	s.line_hor(3,78,22,196);
	gotoxy(71,1);
	cout <<"<0>=Exit";
	textbackground(BLUE);
	gotoxy(3,3);
	for (int i=1; i<=76; i++) cprintf(" ");
	textbackground(BLACK);
	textcolor(RED+BLINK); textbackground(BLUE);
	gotoxy(30,3);
	cprintf("MODIFY ACCOUNT SCREEN");
	textcolor(YELLOW); textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(62,5);
	cout <<"Date: "<<d1 <<"/" <<m1 <<"/" <<y1;
	char ch;
	display(t_accno);
	account a;
	do
	{
		a.clear(5,13);
		gotoxy(5,13);
		cout <<"Modify this account (y/n): ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	} while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	int modified=0, valid;
	char t_name[30], t_address[60];
	gotoxy(5,15);
	cout <<"Name    : ";
	gotoxy(5,16);
	cout <<"Address : ";
	do
	{
		a.clear(15,15);
		a.clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER NAME ";
		valid = 1;
		gotoxy(15,15);
		gets(t_name);
		strupr(t_name);
		if (t_name[0] == '0')
			return;
		if (strlen(t_name) > 25)
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7NAME SHOULD NOT GREATER THAN 25");
			getch();
		}
	} while (!valid);
	if (strlen(t_name) > 0)
		modified = 1;
	do
	{
		a.clear(15,16);
		a.clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER ADDRESS ";
		valid = 1;
		gotoxy(15,16);
		gets(t_address);
		strupr(t_address);
		if (t_address[0] == '0')
			return;
		if (strlen(t_address) > 55)
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7SHOULD NOT BLANK OR GREATER THAN 55");
			getch();
		}
	} while (!valid);
	if (strlen(t_address) > 0)
		modified = 1;
	if (!modified)
		return;
	a.clear(5,23);
	do
	{
		a.clear(5,18);
		gotoxy(5,18);
		cout <<"Do you want to save changes (y/n): ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	} while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	modify_account(t_accno,t_name,t_address);
	gotoxy(5,21);
	cout <<"\7Record Modified";
	gotoxy(5,23);
	cout <<"Press any key to continue...";
	getch();
}

// will encrpyt all string data members
void initial :: encrypt(){;
//	name = sEncrypt(name);
//	address = sEncrypt(address);
}

//will decrypt all string data members
void initial :: decrypt(){;
	//name = sDecrypt(name);
	//address = sDecrypt(address);
}




//clear given row and column except for the box 
void account :: clear(int col, int row)
{
	for (int i=col; i<=78; i++)
	{
		gotoxy(i,row);
		cout <<" ";
	}
}


//function to write data to banking.dat
void account :: add_to_file(int t_accno, int d1, int m1, int y1, char t_tran, char t_type[10], float t_interest, float t_amount, float t_balance)
{
	fstream file;
	file.open("BANKING.DAT", ios::app);
	accno = t_accno;
	dd = d1;
	mm = m1;
	yy = y1;
	tran = t_tran;
	strcpy(type,t_type);
	interest = t_interest;
	amount = t_amount;
	balance = t_balance;
	file.write((char *) this, sizeof(account));
	file.close();
}



//function to delete record no from banking.dat
void account :: delete_account(int t_accno)
{
	fstream file;
	file.open("BANKING.DAT", ios::in);
	fstream temp;
	temp.open("temp.dat", ios::out);
	file.seekg(0,ios::beg);
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(account));
		if ( file.eof() )
			break;
		if ( accno != t_accno )
			temp.write((char *) this, sizeof(account));
	}
	file.close();
	temp.close();
	file.open("BANKING.DAT", ios::out);
	temp.open("temp.dat", ios::in);
	temp.seekg(0,ios::beg);
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(account));
		if ( temp.eof() )
			break;
		file.write((char *) this, sizeof(account));
	}
	file.close();
	temp.close();
}


//function to add new data to banking.dat
void account :: new_account(void)
{
	char ch;
	int i, valid;
	clrscr();
	initial ini;
	shape s;
	s.box(2,2,79,24);
	s.line_hor(3,78,4,196);
	s.line_hor(3,78,22,196);
	gotoxy(71,1);
	cout <<"<0>=Exit";
	textbackground(BLUE);
	gotoxy(3,3);
	for (i=1; i<=76; i++) cprintf(" ");
	textbackground(BLACK);
	textcolor(RED+BLINK); textbackground(BLUE);
	gotoxy(32,3);
	cprintf("OPEN NEW ACCOUNT");
	textcolor(YELLOW); textbackground(BLACK);

	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	int t_accno;
	t_accno = ini.last_accno();
	t_accno++;
	if (t_accno == 1)
	{
		ini.add_to_file(t_accno,"abc","xyz",1.1);
		ini.delete_account(t_accno);
		add_to_file(t_accno,1,1,1997,'D',"INITIAL",1.1,1.1,1.1);
		delete_account(t_accno);
	}
	char t_name[30], t[10], t_address[60];
	float t_bal=0.0, t_balance=0.0;

	gotoxy(5,6);
	cout <<"Date : "<<d1 <<"/" <<m1 <<"/" <<y1;
	gotoxy(5,8);
	cout <<"Account no. # " <<t_accno;
	gotoxy(5,10);
	cout <<"Name    : ";
	gotoxy(5,11);
	cout <<"Address : ";
	gotoxy(5,12);
	cout <<"Name of Verifying person : ";
	gotoxy(5,14);
	cout <<"Initial Deposit : ";
	do
	{
		clear(15,10);
		clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER NAME OF THE PERSON";
		valid = 1;
		gotoxy(15,10);
		gets(t_name);
		strupr(t_name);
		if (t_name[0] == '0')
			return;
		if (strlen(t_name) == 0 || strlen(t_name) > 25)
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7NAME SHOULD NOT BLANK OR GREATER THAN 25");
			getch();
		}
	} while (!valid);
	do
	{
		clear(15,11);
		clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER ADDRESS OF THE PERSON";
		valid = 1;
		gotoxy(15,11);
		gets(t_address);
		strupr(t_address);
		if (t_address[0] == '0')
			return;
		if (strlen(t_address) == 0 || strlen(t_address) > 55)
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7SHOULD NOT BLANK OR GREATER THAN 55");
			getch();
		}
	} while (!valid);
	do
	{
		char vari[30];
		clear(31,12);
		clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER NAME OF THE VERIFYING PERSON";
		valid = 1;
		gotoxy(31,12);
		gets(vari);
		strupr(vari);
		if (vari[0] == '0')
			return;
		if (strlen(vari) == 0 || strlen(vari) > 25)
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7SHOULD NOT BLANK OR GREATER THAN 25");
			getch();
		}
	} while (!valid);
	do
	{
		clear(23,14);
		clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER INITIAL AMOUNT TO BE DEPOSIT";
		valid = 1;
		gotoxy(23,14);
		gets(t);
		t_bal = atof(t);
		t_balance = t_bal;
		if (t[0] == '0')
			return;
		if (t_balance < 500)
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7SHOULD NOT LESS THAN 500          ");
			getch();
		}
	} while (!valid);
	clear(5,23);
	do
	{
		clear(5,17);
		valid = 1;
		gotoxy(5,17);
		cout <<"Do you want to save the record (y/n) : ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	} while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	float t_amount, t_interest;
	t_amount = t_balance;
	t_interest = 0.0;
	char t_tran, t_type[10];
	t_tran = 'D';
	strcpy(t_type,"INITIAL");
	ini.add_to_file(t_accno,t_name,t_address,t_balance);
	add_to_file(t_accno,d1,m1,y1,t_tran,t_type,t_interest,t_amount,t_balance);
}


//draws box for 
void account :: box_for_display(int t_accno)
{
	shape s;
	s.box(2,1,79,25);
	s.line_hor(3,78,4,196);
	s.line_hor(3,78,6,196);
	s.line_hor(3,78,23,196);
	textbackground(BLUE);
	gotoxy(3,5);
	for (int i=1; i<=76; i++) cprintf(" ");
	textbackground(BLUE);
	textcolor(RED); textbackground(BLUE);
	gotoxy(4,5);
	cprintf("DATE        PARTICULAR    DEPOSIT     WITHDRAW    INTEREST    BALANCE");
	textcolor(YELLOW); textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(63,2);
	cout <<"Date: " <<d1 <<"/" <<m1 <<"/" <<y1;
	gotoxy(4,2);
	cout <<"Account no. " <<t_accno;
	initial ini;
	char t_name[30];
	strcpy(t_name,ini.return_name(t_accno));
	char t_address[60];
	strcpy(t_address,ini.return_address(t_accno));
	gotoxy(25,2);
	cout <<t_name;
	gotoxy(25,3);
	cout <<t_address;
}



//display account with box_for_display template.
void account :: display_account(void)
{
	clrscr();
	char t_acc[10];
	int t, t_accno;
	gotoxy(71,1);
	cout <<"<0>=Exit";
	gotoxy(5,5);
	cout <<"Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc); // converts alphabet input to integer to pass as parameter
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();

	initial ini;
	
	box_for_display(t_accno);
	int row=7, flag;
	fstream file;
	file.open("BANKING.DAT", ios::in);
	while (file.read((char *) this, sizeof(account)))
	{
		if (accno == t_accno)
		{
			flag = 0;
			delay(10);
			gotoxy(4,row);
			cout <<dd <<"/" <<mm <<"/" <<yy;
			gotoxy(16,row);
			cout <<type;
			if (tran == 'D')
				gotoxy(30,row);
			else
				gotoxy(42,row);
			cout <<amount;
			gotoxy(56,row);
			cout <<interest;
			gotoxy(66,row);
			cout <<balance;
			row++;
			//will only work for a max of 23 records - should include for more
		}
	}
	file.close();
	if (!flag)
	{
		gotoxy(4,24);
		cout <<"Press any key to continue...";
		getch();
	}

}



//function to return difference in days between to dates.
int account :: no_of_days(int d1, int m1, int y1, int d2, int m2, int y2)
{
	static int month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int days = 0;
	while (d1 != d2 || m1 != m2 || y1 != y2)
	{
		days++;
		d1++;
		if (d1 > month[m1-1])
		{
			d1 = 1;
			m1++;
		}
		if (m1 > 12)
		{
			m1 = 1;
			y1++;
		}
	}
	return days;
}


//interest calculator
float account :: calculate_interest(int t_accno, float t_balance)
{
	fstream file;
	file.open("BANKING.DAT", ios::in);
	file.seekg(0,ios::beg);
	int d1, m1, y1, days;
	while (file.read((char *) this, sizeof(account)))
	{
		if (accno == t_accno)
		{
			d1 = dd;
			m1 = mm;
			y1 = yy;
			break;
		}
	}
	int d2, m2, y2;
	struct date d;
	getdate(&d);
	d2 = d.da_day;
	m2 = d.da_mon;
	y2 = d.da_year;
	float t_interest=0.0;
	if ((y2<y1) || (y2==y1 && m2<m1) || (y2==y1 && m2==m1 && d2<d1))
		return t_interest;
	days = no_of_days(d1,m1,y1,d2,m2,y2);
	int months=0;
	if (days >= 30)
	{
		months = days/30;
		t_interest = ((t_balance*2)/100) * months;
	}
	file.close();
	return t_interest;
}



// function to make transactions
void account :: transaction(void)
{
	clrscr();
	char t_acc[10];
	int t, t_accno, valid;
	gotoxy(71,1);
	cout <<"<0>=Exit";
	gotoxy(5,5);
	cout <<"Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5,5);
		cout <<"\7Account not found";
		getch();
		return;
	}
	shape s;
	s.box(2,2,79,24);
	s.line_hor(3,78,4,196);
	s.line_hor(3,78,22,196);
	gotoxy(71,1);
	cout <<"<0>=Exit";
	textbackground(BLUE);
	gotoxy(3,3);
	for (int i=1; i<=76; i++) cprintf(" ");
	textbackground(BLACK);
	textcolor(RED+BLINK); textbackground(BLUE);
	gotoxy(29,3);
	cprintf("TRANSACTION IN ACCOUNT");
	textcolor(YELLOW); textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(5,6);
	cout <<"Date : "<<d1 <<"/" <<m1 <<"/" <<y1;
	gotoxy(5,8);
	cout <<"Account no. # " <<t_accno;
	char t_name[30];
	char t_address[60];
	float t_balance;
	strcpy(t_name,ini.return_name(t_accno));
	strcpy(t_address,ini.return_address(t_accno));
	t_balance = ini.give_balance(t_accno);
	s.box(25,10,75,13);
	gotoxy(27,11);
	cout <<"Name   : " <<t_name;
	gotoxy(27,12);
	cout <<"Address: " <<t_address;
	gotoxy(5,15);
	cout <<"Last Balance : Rs." <<t_balance;
	char  t_tran, t_type[10], tm[10];
	float t_amount, t_amt;
	do
	{
		clear(5,18);
		valid = 1;
		gotoxy(5,18);
		cout <<"Deposit or Withdraw (D/W) : ";
		t_tran = getche();
		if (t_tran == '0')
			return;
		t_tran = toupper(t_tran);
	} while (t_tran != 'D' && t_tran != 'W');
	do
	{
		clear(5,19);
		clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER TRANSACTION BY CASH OR CHEQUE";
		valid = 1;
		gotoxy(5,19);
		cout <<"(Cash/Cheque) : ";
		gets(t_type);
		strupr(t_type);
		if (t_type[0] == '0')
			return;
		if (strcmp(t_type,"CASH") && strcmp(t_type,"CHEQUE"))
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7ENTER CORRECTLY                       ");
			getch();
		}
	} while (!valid);
	do
	{
		clear(5,21);
		clear(5,23);
		gotoxy(5,23);
		cout <<"ENTER AMOUNT FOR TRANSACTION";
		valid = 1;
		gotoxy(5,21);
		cout <<"Amount : Rs.";
		gets(tm);
		t_amt = atof(tm);
		t_amount = t_amt;
		if (tm[0] == '0')
			return;
		if ((t_tran == 'W' && t_amount > t_balance) || (t_amount < 1))
		{
			valid = 0;
			gotoxy(5,23);
			cprintf("\7INVALID DATA ENTERED               ");
			getch();
		}
	} while (!valid);
	char ch;
	clear(5,23);
	do
	{
		clear(40,20);
		valid = 1;
		gotoxy(40,20);
		cout <<"Save transaction (y/n): ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	} while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	float t_interest;
	t_interest = calculate_interest(t_accno,t_balance);
	if (t_tran == 'D')
		t_balance = t_balance + t_amount + t_interest;
	else
		t_balance = (t_balance - t_amount) + t_interest;
	ini.update_balance(t_accno,t_balance);
	add_to_file(t_accno,d1,m1,y1,t_tran,t_type,t_interest,t_amount,t_balance);
}


//function to delete account
void account :: close_account(void)
{
	clrscr();
	char t_acc[10];
	int t, t_accno;
	gotoxy(71,1);
	cout <<"<0>=Exit";
	gotoxy(5,5);
	cout <<"Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5,5);
		cout <<"\7Account not found";
		getch();
		return;
	}
	shape s;
	s.box(2,2,79,24);
	s.line_hor(3,78,4,196);
	s.line_hor(3,78,22,196);
	gotoxy(71,1);
	cout <<"<0>=Exit";
	textbackground(BLUE);
	gotoxy(3,3);
	for (int i=1; i<=76; i++) cprintf(" ");
	textbackground(BLACK);
	textcolor(RED+BLINK); textbackground(BLUE);
	gotoxy(30,3);
	cprintf("CLOSE ACCOUNT SCREEN");
	textcolor(YELLOW); textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(62,5);
	cout <<"Date: "<<d1 <<"/" <<m1 <<"/" <<y1;
	char ch;
	ini.display(t_accno);
	do
	{
		clear(5,15);
		gotoxy(5,15);
		cout <<"Close this account (y/n): ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	} while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	ini.delete_account(t_accno);
	delete_account(t_accno);
	gotoxy(5,20);
	cout <<"\7Record Deleted";
	gotoxy(5,23);
	cout <<"Press any key to continue...";
	getch();
}


//displays exit box
void control::exit_menu(){
	startup_box();
	gotoxy(19, 12);
	textcolor(GREEN); textbackground(BLACK);
	cprintf("Thanks for using our Encrypted Banking System.");
	gotoxy(24, 13);
	cprintf("We hope to see you soon =)");
	textcolor(BLINK + LIGHTBLUE); textbackground(BLACK);
	gotoxy(30, 24);
	cprintf("HAVE A GREAT DAY!");
	getch();

}

//************************************************************
// THIS IS MAIN FUNCTION CALLING HELP AND MAIN MENU FUNCTIONS
//************************************************************

void main(){

	control a;
	a.startup_menu();
	a.login_box();
	a.main_menu();
	a.exit_menu();

}