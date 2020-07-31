#include<iostream.h>
#include<dos.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
struct profile
{
	int user_id;
	char username[20];
	char password[20];
	float point[3];
	float total;
};
void table(int a,int b,char r[][60]);
void inside(profile ob);
void eula();
void create()
{
	_setcursortype(_NOCURSOR);
	eula();
	_setcursortype(_NORMALCURSOR);
	clrscr();
	char x[2][20],s[][60]={" Account created Succesfully","         Game on \2\2"};
	int y,i;
	profile ob,a;
	char r[][60]={"         CREATE AN ACCOUNT"," Enter Desired Username:"," Enter Password:"," Confirm Password:"};
	table(4,40,r);
	ofstream fout("USERDATA.DAT",ios::app|ios::binary);
	username:
	gotoxy(38,14);
	cout<<"                ";
	gotoxy(40,16);
	cout<<"                ";
	gotoxy(46,12);
	cout<<"              ";
	gotoxy(22,18);
	cout<<"                                               ";
	gotoxy(15,21);
	cout<<"                                                     ";
	gotoxy(46,12);
	cin>>x[0];
	ifstream fin;
	fin.open("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&ob,sizeof(ob)))
	{
		if(strcmp(ob.username,x[0])==0)
		{
			gotoxy(22,18);
			_setcursortype(_NOCURSOR);
			cout<<"Desired Username already exists!!!";
			getch();
			_setcursortype(_NORMALCURSOR);
			gotoxy(15,21);
			cout<<"Enter 1 to try again (and anything else to exit): ";
			cin>>y;
			if(y==1)
			goto username;
			else
			goto end;
		}
	}
	fin.close();
	strcpy(a.username,x[0]);
	password:
	gotoxy(38,14);
	cout<<"                ";
	gotoxy(40,16);
	cout<<"                ";
	gotoxy(38,14);
	cin>>x[0];
	gotoxy(22,18);
	cout<<"                                                              ";
	gotoxy(15,21);
	cout<<"                                                  ";
	if(strlen(x[0])<6)
	{
		gotoxy(22,18);
		cout<<"Password should be atleast 6 characters long!!!";
		goto password;
	}
	gotoxy(40,16);
	cin>>x[1];
	if(!strcmp(x[0],x[1])==0)
	{
		gotoxy(22,18);
		cout<<"Passwords do not match!!!";
		goto password;
	}
	strcpy(a.password,x[1]);
	do
	{
		y=0;
		for(i=0;i<4;i++)
		{
			y*=10;
			y+=(random(9)+1);
		}
		fin.open("USERDATA.DAT",ios::in|ios::binary);
		while(fin.read((char*)&ob,sizeof(ob)))
		{
			if(ob.user_id==y)
				y=0;
		}
	}while(y==0);
	a.user_id=y;
	a.total=0;
	for(i=0;i<3;i++)
	{
		a.point[i]=0;
		a.total+=a.point[i];
	}
	gotoxy(18,21);
	cout<<"Enter 1 to confirm(or anything else to exit): ";
	cin>>y;
	if(y!=1)
	goto username;
	fout.write((char*)&a,sizeof(a));
	fout.close();
	_setcursortype(_NOCURSOR);
	clrscr();
	table(2,30,s);
	getch();
	_setcursortype(_NORMALCURSOR);
	end:
}
void signin()
{
	get:
	clrscr();
	int flag=0,ch;
	profile ob;
	char r[][60]={"           SIGN IN"," Username: "," Password: "},a[20],b[20];
	table(3,30,r);
	gotoxy(36,13);
	cout<<"		    ";
	gotoxy(36,15);
	cout<<"		    ";
	gotoxy(37,13);
	cin>>a;
	gotoxy(23,17);
	cout<<"	         			       ";
	gotoxy(18,20);
	cout<<"                                                  ";
	gotoxy(37,15);
	cin>>b;
	ifstream fin("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&ob,sizeof(ob)))
	{
		if(strcmp(ob.username,a)==0)
		{
			if(strcmp(ob.password,b)==0)
			{
				flag=1;
				inside(ob);
			}
			else
			{
				gotoxy(27,17);
				flag=1;
				cout<<"Username and Password do not match!!!";
				getch();
				gotoxy(18,20);
				cout<<"Enter 1 to try again(and any number to go back): ";
				cin>>ch;
				if(ch==1)
				goto get;
			}
		}
	}
	fin.close();
	if(flag==0)
	{

		gotoxy(27,17);
		cout<<" Username does not exist!!!";
		getch();
		gotoxy(18,20);
		cout<<"Enter 1 to try again(and any number to go back): ";
		cin>>ch;
		if(ch==1)
		goto get;
	}
}
void filewrite(profile ob)
{
	profile m;
	ofstream fout("TEMP.DAT",ios::app|ios::binary);
	ifstream fin("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&m,sizeof(m)))
	{
		if(m.user_id!=ob.user_id)
		fout.write((char*)&m,sizeof(m));
	}
	fin.close();
	fout.close();
	remove("USERDATA.DAT");
	rename("TEMP.DAT","USERDATA.DAT");
	ofstream f("USERDATA.DAT",ios::app|ios::binary);
	f.write((char*)&ob,sizeof(ob));
	f.close();
}
void loading();
void ingamesignin(profile &ob)
{
	get:
	clrscr();
	int flag=0,ch;
	char r[][60]={"           SIGN IN"," Username: "," Password: "},a[20],b[20];
	table(3,30,r);
	gotoxy(36,13);
	cout<<"		    ";
	gotoxy(36,15);
	cout<<"		    ";
	gotoxy(37,13);
	cin>>a;
	gotoxy(23,17);
	cout<<"	         			       ";
	gotoxy(18,20);
	cout<<"                                                  ";
	gotoxy(37,15);
	cin>>b;
	ifstream fin("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&ob,sizeof(ob)))
	{
		if(strcmp(ob.username,a)==0)
		{
			flag=1;
			if(strcmp(ob.password,b)==0)
				break;
			else
			{
				gotoxy(27,17);
				cout<<"Username and Password do not match!!!";
				getch();
				gotoxy(18,20);
				cout<<"Enter 1 to try again(and any number to go back): ";
				cin>>ch;
				if(ch==1)
				goto get;
				strcpy(ob.username,"giratina");
				break;
			}
		}
	}
	fin.close();
	if(flag==0)
	{

		gotoxy(27,17);
		cout<<"Username does not exist!!!";
		getch();
		gotoxy(18,20);
		cout<<"Enter 1 to try again(and any number to go back): ";
		cin>>ch;
		if(ch==1)
		goto get;
	}
}
class tictactoe
{
	int x,c,i,j;
	public:
	int play(char a[50],char t[9],char b);
	void main(profile &pa,profile &pb);
	void inst();
};
int tictactoe::play(char a[20],char t[9],char b)
{
	x=0;
	again:
	cout<<"\n";
	for(i=0;i<9;i++)
	{
		cout<<t[i]<<" ";
		if(i==2 || i==5)
		cout<<"\n";
	}
	cout<<endl<<a<<"'s turn: ";
	cin>>x;
	if(x==0)
		inst();
	else if(t[--x]=='_')
		t[x]=b;
	else
	{
		cout<<"Try again";
		goto again;
	}
	x=0;
	for(i=0;i<9;i+=3)
	if(t[i]==b && t[i+1]==b && t[i+2]==b)
	x=1;
	for(i=0;i<3;i++)
	if(t[i]==b && t[i+3]==b && t[i+6]==b)
	x=1;
	if(t[0]==b && t[4]==b && t[8]==b)
	x=1;
	if(t[2]==b && t[4]==b && t[6]==b)
	x=1;
	return x;
}
void tictactoe::main(profile &pa,profile &pb)
{
	loading();
	c=-1;
	char t[9];
	_setcursortype(_NOCURSOR);
	cout<<"Welcome to Tic-Tac-Toe.\n";
	getch();
	cout<<"\nEnter 0 at any point of time during the game for instructions!\n";
	getch();
	_setcursortype(_NORMALCURSOR);
	again:
	for(i=0;i<9;i++)
	t[i]='_';
	clrscr();
	do
	{
		c++;
		if(c%2==0)
		{
			x=play(pa.username,t,'X');
			if(x==1)
			{
				clrscr();
				for(i=0;i<9;i++)
				{
					cout<<t[i]<<" ";
					if(i==2 || i==5)
					cout<<"\n";
				}
				getch();
				cout<<"\n\n"<<pa.username<<" is the winner\n";
				cout<<pa.username<<" gets 20 points";
				pa.point[0]+=20;
				break;
			}
			else
			{
				for(i=0;i<9;i++)
				if(t[i]=='_')
				{
					x=2;
					break;
				}
			}
			if(x!=2)
			{
				clrscr();
				for(int i=0;i<9;i++)
				{
					cout<<t[i]<<" ";
					if(i==2 || i==5)
					cout<<"\n";
				}
				getch();
				cout<<"\n\nMatch is a draw.";
				cout<<"\nBoth players get 10 points each.";
				pa.point[0]+=10;
				pb.point[0]+=10;
				getch();
				break;
			}
		}
		else
		{
			x=play(pb.username,t,'O');
			if(x==1)
			{
				clrscr();
				for(int i=0;i<9;i++)
				{
					cout<<t[i]<<" ";
					if(i==2 || i==5)
					cout<<"\n";
				}
				getch();
				cout<<"\n\n"<<pb.username<<" is the winner.";
				cout<<pb.username<<" gets 20 points";
				pb.point[0]+=20;
			}
		}
	}while(x!=1);
	getch();
	cout<<"\nThank you for Playing";
	getch();
}
void tictactoe::inst()
{
	cout<<"\n\t\t\t    HOW TO PLAY: TIC-TAC-TOE";
	cout<<"\n    1: Enter any number between 1 to 9 to insert into the table.";
	cout<<"\n    2: Now, let your opponent play.";
	cout<<"\n    3: If you manage to get your character consecutively in any row, column or         diagonal, you win the game.\n";
	getch();
}
class blackjack
{
	int x,p,q,s,deck[4][13],i,j,ps,qs;
	public:
	int play(char a[50],int d[4][13]);
	void main(profile &pa,profile &pb);
	void inst();
};
int blackjack::play(char a[50],int d[4][13])
{
	s=0;
	again:
	cout<<endl;
	cout<<a<<"'s turn. Enter 1 to hit and 2 to show: ";
	cin>>x;
	if(x==0)
		inst();
	else if(x==1)
	{
		repeat:
		p=random(4);
		q=random(13);
		if(d[p][q]!=0)
		{
			if(d[p][q]<=10)
			cout<<d[p][q];
			else if(d[p][q]==11)
			cout<<"Jack";
			else if(d[p][q]==12)
			cout<<"Queen";
			else if(d[p][q]==13)
			cout<<"King";
			s+=d[p][q];
			d[p][q]=0;
			if(p==0)
			cout<<" (Clubs)";
			else if(p==1)
			cout<<" (Spades)";
			else if(p==2)
			cout<<" (Hearts)";
			else if(p==3)
			cout<<" (Diamonds)";
		}
		else
		goto repeat;
	}
	else if(x==2)
	{
		cout<<"Your Sum is "<<s<<"\n";
		goto cont;
	}
	if(s==21)
	{
		cout<<"\nBlackjack!!!\n";
		goto cont;
	}
	if(s>21)
	goto end;
	else
	goto again;
	end:
	cout<<endl<<a<<" has been busted.("<<s<<")\n";
	s=0;
	cont:
	getch();
	return s;
}
void blackjack::main(profile &pa,profile &pb)
{
	randomize();
	loading();
	ps=0;
	qs=0;
	for(i=0;i<4;i++)
	for(j=0;j<13;j++)
	deck[i][j]=j+1;
	clrscr();
	cout<<"Welcome to Black-Jack.\n";
	getch();
	cout<<"\nEnter 0 at any point of time during the game for instructions!\n";
	getch();
	for(;;)
	{
		clrscr();
		p=play(pa.username,deck);
		ps+=p;
		q=play(pb.username,deck);
		qs+=q;
		if(p==0)
		ps-=5;
		if(q==0)
		qs-=5;
		if(p>q)
		ps+=5;
		else if(q>p)
		qs+=5;
		else if(p==q)
		{
			while(p!=0)
			{
				ps+=0;
				qs+=0;
			}
		}
		if(p==21)
		ps+=10;
		if(q==21)
		qs+=10;
		s=0;
		for(i=0;i<4;i++)
		for(j=0;j<13;j++)
		if(deck[i][j]!=0)
		s++;
		if(s>=10)
		{
			cout<<"\n\nEnter 1 to play again: ";
			cin>>s;
			if(s==0)
			inst();
			else if(s!=1)
			break;
		}
		else
		{
			cout<<"Game Over";
			getch();
			break;
		}
	}
	clrscr();
	cout<<pa.username<<": "<<ps;
	cout<<endl<<pb.username<<": "<<qs;
	cout<<endl;
	getch();
	if(ps>qs)
	{
		cout<<pa.username<<" is the winner.";
		ps+=5;
	}
	else if(qs>ps)
	{
		cout<<pb.username<<" is the winner.";
		qs+=5;
	}
	else
	cout<<"The match is a draw.";
	getch();
	pa.point[1]+=ps;
	pb.point[1]+=qs;
	/*ofstream fout("USERDATA.DAT",ios::app|ios::binary);
	fout.write((char*)&pb,sizeof(pb));
	fout.close(); */
	filewrite(pb);
	end:
}
void blackjack::inst()
{
	cout<<"\n\t\t\t      HOW TO PLAY: BLACKJACK\n";
	cout<<"\n 1: From a deck of 52 cards, the player can hit (take a random card) or show        (display the value of his cards)";
	cout<<"\n 2: The value of his cards add up to his total points ";
	cout<<"\n 3: If the player gets a sum of 21, he hits blackjack and gets 5 additional         points";
	cout<<"\n 4: But if the sum is above 21, the player gets busted and he gets no points";
	cout<<"\n 5: The player with the higher value per round gets 5 additional points";
	cout<<"\n 6: The game will stop when there are less than 10 cards in the deck.\n";
	getch();
}
class guess
{
	int bet,point;
	//point is the user's points taken from his dat file
	public:
	float play(float point);
	void inst();
	void main(profile pa)
	{
		clrscr();
		randomize();
		cout<<"Welcome to Guess!!!";
		pa.point[2]+=play(pa.total);
		getch();
	}
};
float guess::play(float point)
{
	cout<<"Enter Bet Amount: ";
	cin>>bet;
	if(point>=bet)
	{
		point-=bet;
		int x[5],y;
		x[0]=random(10)+1;
		cout<<"\nFirst Bet: ";
		cin>>y;
		if(y==x[0])
		{
			cout<<"Correct Guess!!!";
			getch();
			cout<<"\nYou get 6 times the bet amount!!!";
			point+=(bet*6);
		}
		else if(y==x[0]+1 || y==x[0]-1)
		{
			cout<<"Close Guess!!!";
			cout<<"Correct Number was "<<x[0];
			getch();
			cout<<"\nYou get 2 times the bet amount!!!";
			point+=(bet*2);
		}
		else
		{
			cout<<"Wrong guess!!!\nCorrect bet was "<<x[0];
		}
		getch();
		do
		{
			x[1]=random(10)+1;
			if(x[1]!=x[0])
			break;
		}while(1>0);
		cout<<"\nSecond Bet: ";
		cin>>y;
		if(y==x[1])
		{
			cout<<"Correct guess!!!\nYou get 4 times the bet amount!!!";
			point+=(bet*4);
		}
		else
		{
			cout<<"Wrong guess!!!\nCorrect bet was "<<x[1];
		}
		getch();
		do
		{
			x[2]=random(10)+1;
			if(x[2]!=x[0] && x[2]!=x[1])
			break;
		}while(1>0);
		cout<<"\nThird bet: ";
		cin>>y;
		if(y==x[2])
		{
			cout<<"Correct guess!!!\nYou get 2 times the bet amount!!!";
			point+=(bet*2);
		}
		else
		{
			cout<<"Wrong guess!!!\nCorrect bet was "<<x[2];
		}
		getch();
		do
		{
			x[3]=random(10)+1;
			if(x[3]!=x[0] && x[3]!=x[1] && x[3]!=x[2])
			break;
		}while(1>0);
		cout<<"\nFourth bet: ";
		cin>>y;
		if(y==x[3])
		{
			cout<<"Correct guess!!!\nYou get back the bet amount!!!";
			point+=(bet*2);
		}
		else if(y==x[3]+1 || y==x[3]-1)
		{
			cout<<"Close Guess!!!";
			cout<<"Correct Number was "<<x[3];
			getch();
		}
		else
		{
			cout<<"Wrong guess!!!\nCorrect bet was "<<x[3];
			cout<<"\nYou lose the bet amount!!!";
			point-=bet;
		}
		getch();
		do
		{
			x[4]=random(10)+1;
			if(x[4]!=x[0] && x[4]!=x[1] && x[4]!=x[2] && x[4]!=x[3])
			break;
		}while(1>0);
		cout<<"\nFifth bet: ";
		cin>>y;
		if(y==x[4])
		{
			cout<<"Correct guess!!!\nYou get back the bet amount!!!";
			point+=(bet*2);
		}
		else if(y==x[4]+1 || y==x[4]-1)
		{
			cout<<"Close Guess!!!";
			cout<<"\nCorrect Number was "<<x[4];
			getch();
			cout<<"\nYou lose the bet amount!!!";
			point-=bet;
		}
		else
		{
			cout<<"Wrong guess!!!\nCorrect bet was "<<x[4];
			cout<<"\nYou lose twice the bet amount!!!";
			point-=(bet*2);
		}
	}
	else
	{
		cout<<"You do not have enough points!!!";
	}
	getch();
	cout<<"\n\nYour Aggregate Point is "<<point;
	getch();
	return point;
}
void guess::inst()
{
	loading();
	cout<<"\t\t\t HOW TO PLAY GUESS ";
	cout<<"\n 1: A number between 1 and 10 is chosen at random without repetition.";
	cout<<"\n 2: In the first round, if the number you entered matches the number chosen, you    get 6 times the bet amount. If the number chosen is close to the number, you    get twice the bet amount. ";
	cout<<"\n 3: In the second round, if the number entered matches the chosen number, you       get 4 times the bet amount. ";
	cout<<"\n 4: In the third round, if the number entered matches the number chosen, you get    twice the bet amount. ";
	cout<<"\n 5: In the fourth round, if the number entered matches the number chosen, you       get back the bet amount. ";
	cout<<"\n 6: In the fifth round, if the number entered matches the number chosen, you get    back the bet amount. For a wrong guess, you lose the bet amount.\n";
	getch();
}
void loading()
{
	_setcursortype(_NOCURSOR);
	clrscr();
	randomize();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t  LOADING\n\t\t\t|";
	for(int i=1;i<=25;i++)
		cout<<" ";
	cout<<"|";
	for(i=1;i<=26;i++)
		cout<<"\b";
	int k=0,m=26;
	gotoxy(34,14);
	cout<<k<<"% completed";
	gotoxy(m,13);
	for(i=1;i<=25;i++)
	{
		delay((random(random(20)))*50);
		cout<<">";
		gotoxy(34,14);
		k+=4;
		cout<<"\b\b  "<<k<<"% completed";
		m++;
		gotoxy(m,13);
	}
	delay(200);
	clrscr();
	_setcursortype(_NORMALCURSOR);
}
void rights()
{
	gotoxy(40,25);
	cout<<"All rights reserved @ Triate Corporation";
}
void version()
{
	cout<<"Version 1.0";
}
void loading2(int a,int b)
{
	_setcursortype(_NOCURSOR);
	clrscr();
	randomize();
	cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t   Loading \n\t\t\t|";
	for(int i=1;i<=27;i++)
	{
		cout<<" ";
	}
	cout<<"|";
	for(i=1;i<=28;i++)
	{
		cout<<"\b";
	}
	for(int k=1;k<=a;k++)
	{
		for(i=1;i<=9;i++)
		{
			if((k!=1)&&(i==1))
			cout<<"\b\b\b   \b\b\b";
			if(i!=1)
			{
				delay(b);
				cout<<"\b\b\b";
				cout<<"   ";
			}
			cout<<">>>";

		}
		if(k==a)
		{
			delay(b);
			break;
		}
		else
		{

			for(int i=1;i<=9;i++)
			{
				delay(300);
				cout<<"\b\b\b";
				cout<<"   ";
				if(i==1)
				cout<<"\b\b\b";
				else
				cout<<"\b\b\b\b\b\b";
				cout<<"<<<";
			}
			delay(b);
		}
	}
	clrscr();
	_setcursortype(_NORMALCURSOR);
}
void alignl(int n)
{
	for(int i=0;i<(25-n)/2;i++)
	cout<<endl;

}
void aligns(int m)
{
	for(int i=0;i<(79-m)/2;i++)
	cout<<" ";
}
void table(int a,int b,char r[][60])
{
	version();
	rights();
	gotoxy(1,1);
	int size=0,m=0,k=0,n=a;
	char ch[60];
	m=b;
	n*=2;
	alignl(n);
	for(int i=0;i<=n;i++)
	{
		if(i!=0)
		cout<<endl;
		aligns(m);
		if((i==0)||(i==n))
		cout<<"+";
		else
		cout<<"|";
		if(i%2!=0)
		{
			strcpy(ch,r[k++]);
			size=strlen(ch);
		}
		else
		size=0;
		for(int j=0;j<m;j++)
		{
		  if((i==0)||(i==n))
		  cout<<"-";
		  else
		  {
			if((j==0)&&(i%2!=0))
		       {
				cout<<ch;

		       }
		       else
		       {
				if(!(j<=m-size))
				continue;
				cout<<" ";
		       }

		  }
		}
		if((i==0)||(i==n))
		cout<<"+";
		else
		cout<<"|";
	}
}
void player(profile &ob)
{
	clrscr();
	profile m;
	int ch;
	char r[][60]={"               MENU"," 1. Tic-Tac-Toe"," 2. Blackjack"," 3. Guess"," 4. Back To Previous Menu"," Enter Your Choice:"};
	table(6,30,r);
	gotoxy(46,18);
	cin>>ch;
	profile n;
	switch(ch)
	{
		case 1:
			cout<<"\n\t\t\tTic-Tac-Toe is a multiplayer game!!!\n\t\t\tPlease ask your partner to sign in!!";
			getch();
			ingamesignin(n);
			if(strcmp(n.username,"giratina")==0)
				break;
			tictactoe x;
			x.main(ob,n);
			filewrite(ob);
			filewrite(n);
			break;
		case 2:
			cout<<"\n\t\t\tBlackjack is a multiplayer game!!!\n\t\t\tPlease ask your partner to sign in!!";
			getch();
			ingamesignin(n);
			if(strcmp(n.username,"giratina")==0)
				break;
			blackjack y;
			y.main(ob,n);
			break;
		case 3:
			guess z;
			z.main(ob);
			break;
		default:
			if(ch!=4)
			{
				gotoxy(20,20);
				cout<<"Invalid choice!!!\nTry again with proper response";
				gotoxy(20,20);
				cout<<"  ";
			}
	}
	ofstream fout("TEMP.DAT",ios::app|ios::binary);
	ifstream fin("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&n,sizeof(n)))
	{
		if(n.user_id!=ob.user_id)
		fout.write((char*)&n,sizeof(n));
		else
		fout.write((char*)&m,sizeof(m));
	}
	remove("USERDATA.DAT");
	rename("TEMP.DAT","USERDATA.DAT");
	fin.close();
	fout.close();
}
void status(profile ob)
{
	int rank[4];
	for(int i=0;i<4;i++)
		rank[i]=1;
	ifstream fin;
	profile a;
	fin.open("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(a.point[0]>ob.point[0])
			rank[0]++;
		if(a.point[1]>ob.point[1])
			rank[1]++;
		if(a.point[2]>ob.point[2])
			rank[2]++;
		if(a.total>ob.total)
			rank[3]++;
	}
	clrscr();
	_setcursortype(_NOCURSOR);
	char r[][60]={"       YOUR POINT STATUS","              POINT     RANK"," Tic-Tac-Toe:"," Blackjack:"," Guess:"," Total:"};
	table(6,30,r);
	gotoxy(39,12);
	cout<<"   "<<ob.point[0];
	if(ob.point[0]>10)
	cout<<"\b";
	cout<<"        "<<rank[0];
	gotoxy(39,14);
	cout<<"   "<<ob.point[1];
	if(ob.point[1]>10)
	cout<<"\b";
	cout<<"        "<<rank[1];
	gotoxy(39,16);
	cout<<"   "<<ob.point[2];
	if(ob.point[2]>10)
	cout<<"\b";
	cout<<"        "<<rank[2];
	gotoxy(39,18);
	cout<<"   "<<ob.total;
	if(ob.total>10)
	cout<<"\b";
	if(ob.total>100)
	cout<<"\b";
	cout<<"        "<<rank[3];
	getch();
	_setcursortype(_NORMALCURSOR);
	filewrite(ob);
}
void account_settings(profile &ob)
{
	char r[][60]={"          PASSWORD SETTINGS"," Enter Current Password:"," Enter New Password:"," Confirm New Password:"},a[20],b[20],c[20];
	clrscr();
	table(4,40,r);
	get:
	gotoxy(42,14);
	cout<<"                 ";
	gotoxy(44,16);
	cout<<"                 ";
	gotoxy(46,12);
	cout<<"               ";
	gotoxy(46,12);
	cin>>a;
	gotoxy(22,18);
	cout<<"                                                                ";
	pass:
	gotoxy(42,14);
	cout<<"                 ";
	gotoxy(44,16);
	cout<<"                 ";
	if(strcmp(ob.password,a)==0)
	{
		gotoxy(42,14);
		cin>>b;
		if(strlen(b)<6)
		{
			gotoxy(22,18);
			cout<<"Password must be atleast 6 characters long!!!";
			goto pass;
		}
		gotoxy(22,18);
		cout<<"                                                 ";
		gotoxy(44,16);
		cin>>c;
		if(strcmp(b,c)!=0)
		{
			gotoxy(22,18);
			cout<<"You have entered the wrong password.";
			goto pass;
		}
		else
		{
			strcpy(ob.password,c);
			gotoxy(22,18);
			cout<<"                                    ";
			gotoxy(22,18);
			cout<<"Password changed successfully.";
			ofstream fout("TEMP.DAT",ios::app|ios::binary);
			ifstream fin("USERDATA.DAT",ios::in|ios::binary);
			profile x;
			while(fin.read((char*)&x,sizeof(x)))
			{
				if(x.user_id!=ob.user_id)
				fout.write((char*)&x,sizeof(x));
			}
			fout.write((char*)&ob,sizeof(ob));
			remove("USERDATA.DAT");
			rename("TEMP.DAT","USERDATA.DAT");
			getch();
		}
	}
	else
	{
		gotoxy(22,18);
		cout<<"Wrong password";
		gotoxy(46,12);
		cout<<"           ";
		goto get;
	}
}
void inside(profile a)
{
	int ch;
	profile ob;
	ifstream fin("USERDATA.DAT",ios::in|ios::binary);
	while(fin.read((char*)&ob,sizeof(ob)))
	{
		if(ob.user_id==a.user_id)
		break;
	}
	fin.close();
	do
	{
		get:
		ob.total=0;
		ob.total=ob.point[0]+ob.point[1]+ob.point[2];
		profile m;
		clrscr();
		char r[][60]={"              MENU"," 1. Play Area"," 2. Account Settings"," 3. My Status"," 4. Statistics"," 5. Log Out"," Enter Your Choice:"};
		table(7,35,r);
		gotoxy(44,19);
		cin>>ch;
		switch(ch)
		{
			case 1:
				player(ob);
				break;
			case 2:
				account_settings(ob);
				break;
			case 3:
			       status(ob);
			       break;
			case 5:
				_setcursortype(_NOCURSOR);
				clrscr();
				char r[][60]={"    Successfuly logged out","       Happy gaming \2\2"};
				table(2,30,r);
				getch();
				_setcursortype(_NORMALCURSOR);
				break;
			default:
				_setcursortype(_NOCURSOR);
				gotoxy(24,21);
				cout<<"Invalid choice!!!";
				gotoxy(24,22);
				cout<<"Try again with proper response";
				delay(2000);
				_setcursortype(_NORMALCURSOR);
				goto get;
		}
	}while(ch!=5);
}
void eula()
{
	clrscr();
	_setcursortype(_NOCURSOR);
	cout<<" The main terms of the license incorporated into the terms and conditions are as follows:";
	cout<<"\n Unless you have paid for the right to use the relevant document without a       credit and hyperlink, you must:";
	cout<<"\n (a): Retain the credit in the free legal document; and";
	cout<<"\n (b): If you publish the document on a website,include a link to Triate          Productions.";
	cout<<"\n Subject to this point, you may edit and amend the documents to render them      suitable for your purposes.";
	cout<<"\n\t You must not re-publish the free legal documents in the unamended form.All footnotes and brackets should be removed from the documents before publication.";
	cout<<"You must not sell or re-distribute the free legal documents or derivatives   thereof.";
	cout<<"We give no warranties or representations concerning the free legal      documents,and accept no liability in relation to the use of free legal documents";
	cout<<"\nLegal Information:";
	cout<<"\n Particular circumstances often radically affect the law that applies, and the   way that the law applies.";
	cout<<"\n You should therefore never apply the legal information to your own situation    without conducting additional research or engaging a lawyer. Nor should you     assume that all of the relevant legal material is included in the game.";
	cout<<"\n The law changes constantly, and legal information is always liable to become    out-of-date.";
	cout<<"\n Most of the legal information in this game is relates to the laws of India.";
	getch();
	_setcursortype(_NORMALCURSOR);
}
void credits()
{
	clrscr();
	_setcursortype(_NOCURSOR);
	int n=20;
	for(int i=0;i<22;i++)
	{
		gotoxy(1,n);
		cout<<"\n\t\t\t\tTRIATE TEAM\n";
		cout<<"\n\t\t\t\tAthul Shibu";
		cout<<"\n\t\t\t       Swarnim Yaduka";
		cout<<"\n\t\t\t\t  B Vishal";
		cout<<"\n\t\t\t\t\t  Class XII-B";
		delay(500);
		clrscr();
		n--;
	}
	_setcursortype(_NORMALCURSOR);
}
void main()
{
	int a,ch;
	textbackground(15);
	textcolor(0);
	profile ob;
	clrscr();
	_setcursortype(_NOCURSOR);
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t A TRIATE SOFTWARE PRODUCTION";
	delay(2000);
	_setcursortype(_NORMALCURSOR);
	loading2(2,300);
	char r[][60]={"        TRIATE GAMING"," 1.Already A User"," 2.Create A New Account"," 3.Exit"," Enter Your Choice:"};
	do
	{
		clrscr();
		table(5,30,r);
		gotoxy(46,17);
		cin>>ch;
		switch(ch)
		{
			case 1:
				signin();
				break;
			case 2:
				create();
				break;
			default:
				if(ch!=3)
				{
					cout<<"\nInvalid choice!!!\n  Try again\n\2\2\2";
					getch();
				}
		}
	}while(ch!=3);
	clrscr();
	credits();
}