#include<iostream>
#include<bits/stdc++.h>
#include<vector>
using namespace std;

struct player
{
	char choice;
	int num;
}player1,player2;

class board
{
	public:
	char grid[6][7];
	int rows=6,cols=7;
	board()
	{
		make_board();
	}
	//fills the board with empty spaces
	void make_board()
	{
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<7;j++)
			{
				grid[i][j]=' ';		
			}
		}
	}	
	
	//checks if the board is full
	bool check_full()
	{
		bool flag;
//		int col_check=0;
		for(int i=0;i<7;i++)
		{
			if(grid[0][i]==' ')
			{
				flag=false;
				break;
			}
			else 
			flag=true;
		}
		if(flag)
		{
			cout<<"OH NO!!!\nThere's no more space on the board.\n";
			return true;
		}
		return false;
	}
	
	
	//displays the board
	void display_board()
	{
		system("cls");
		cout<<"--------------------------\n";
		cout<<"\tConnect Four\t |\n";	
		cout<<"--------------------------\n";
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<7;j++)
			{
				cout<<"|"<<grid[i][j]<<"|";
			}
			cout<<endl;
		}
		cout<<"---------------------\n";
		for(int i=1;i<8;i++)
		cout<<"|"<<i<<"|";
		cout<<endl;
		cout<<"---------------------\n";
		
	}
	
	//places the chip inside the board
	void move(char chip,int drop_input)
	{
		drop_input=check_cols(drop_input);
		int drop_row=5;
//		drop_input-=1;
		bool flag=false;
		
		do
		{
			if(grid[drop_row][drop_input]!='X'&&grid[drop_row][drop_input]!='O')
			{
//				cout<<"drop_input"<<drop_input<<endl;
				grid[drop_row][drop_input]=chip;
				flag=true;
			}
			else
			drop_row--;
		}while(!flag);
	}
	
	//checks if the columns are full
	int check_cols(int drop_input)
	{
		drop_input-=1;
		while(grid[0][drop_input]=='X'||grid[0][drop_input]=='O')
		{
			cout<<"Column is FULL!!!!!, try another column\n";
			cin>>drop_input;
			drop_input-=1;
		}
		return drop_input;
	}
	
	//checks for four in a row 
	bool horizontal(char c)
	{
		//start from last row and first column and increases column by one
		for(int i=rows-1;i>=0;i--)//row
		{	string res = "";
			for(int j=0;j<cols;j++)//column
			{
				if(grid[i][j]!=' ') 	//if the cell has chip add it to result
				res+=grid[i][j];
			}
//					cout<<"Res "<<res<<endl;
					//if result includes winning string
					if(res.find("XXXX")!=string::npos)
					{
//						cout<<"here";
						if(c=='X')
						cout<<"Hooray!!!!\nPlayer 1 is the WINNER.\n";
						else
						cout<<"Hooray!!!!\nPlayer 2 is the WINNER.\n";
						return true;
					}
					else if(res.find("OOOO")!=string::npos)
					{
						
						if(c=='O')
						cout<<"Hooray!!!!\nPlayer 1 is the WINNER.\n";
						else
						cout<<"Hooray!!!!\nPlayer 2 is the WINNER.\n";
						return true;
					}
		}

		return false;
	}
	//checks for four in a column
	bool vertical(char c)
	{
		//starts from last row and first column and goes up in the same column by reducing rows
		
		for(int i=cols-1;i>=0;i--)	//row
		{	string res = "";
			for(int j=0;j<rows;j++)	//column
			{
				if(grid[j][i]!=' ')	//if the cell has chip add it to result
				res+=grid[j][i];
			}
//					cout<<"Res "<<res<<endl;

					//if result includes winning string
					if(res.find("XXXX")!=string::npos)
					{
						if(c=='X')
						cout<<"Hooray!!!!\nPlayer 1 is the WINNER.\n";
						else
						cout<<"Hooray!!!!\nPlayer 2 is the WINNER.\n";
						
						return true;
					}
					else if(res.find("OOOO")!=string::npos)
					{
						if(c=='O')
						cout<<"Hooray!!!!\nPlayer 1 is the WINNER.\n";
						else
						cout<<"Hooray!!!!\nPlayer 2 is the WINNER.\n";
						return true;
					}
		}
		return false;
	}
	
	//checks for four in diagonal
	bool diagonal(char c)
	{
		
		
		//start from 4th column and last row
		for(int i=rows-1;i>=0;i--)
		{
			for(int j=cols-4;j>=0;j--)
			{
				//lower left
				if( grid[i][j] == c   &&
				grid[i-1][j-1] == c &&
				grid[i-2][j-2] == c &&
				grid[i-3][j-3] == c )
				{
//					cout<<"first if";
						if(c=='X')
						cout<<"Hooray!!!!\nPlayer 1 is the WINNER.\n";
						else
						cout<<"Hooray!!!!\nPlayer 2 is the WINNER.\n";
						
						return true;
				}
				//lower right	
				if( grid[i][j] == c     &&
				grid[i-1][j+1] == c &&
				grid[i-2][j+2] == c &&
				grid[i-3][j+3] == c )
				{
//						cout<<"second if";
//						cout<<"i= " <<i<<" j="<<j<<endl;
						if(c=='X')
						cout<<"Hooray!!!!\nPlayer 1 is the WINNER.\n";
						else
						cout<<"Hooray!!!!\nPlayer 2 is the WINNER.\n";
						
						return true;
				}

			}
		}
		return false;
	}
	

};

class game
{
	public:
		char choice;
		int drop_input;
		bool valid;
		board b;
	game()
	{
		welcome_message();
		player_choice();
		player1.num=1;
		player2.num=2;
		play();
	}
	//Welcomes the user
	void welcome_message()
	{
		cout<<"Hello\n";
		cout<<"------------------------\n";
		cout<<"Welcome to Connect Four|\n";	
		cout<<"------------------------\n";
	}
	
	//asks for chip choice
	void player_choice()
	{
		do
		{
			cout<<"Enter your choice of chip\nX or O\n";
			cin>>choice;
			if(choice==120||choice==111)
			{
				choice=choice-32;
				valid=true;
			}
			else if (choice==88||choice==79)
			{
				valid=true;
			}
			else
			{
			cout<<"Invalid input\n";
			valid=false;	
			}
			
		}while(!valid);
		player1.choice=choice;
		if(choice=='X')
		player2.choice='O';
		else if(choice=='O')
		player2.choice='X';
		cout<<"Player 1's Choice: "<<player1.choice<<" Player 2's Choice: "<<player2.choice<<endl;
		cout<<"-----------------------\n";
	}

	//play until either game over or board full
	void play()
	{
		do
		{
			b.display_board();
			player_move(player1);
			b.display_board();
			
			if(game_over())
				break;	
			
			player_move(player2);
			b.display_board();
				
			if(game_over())
				break;	
		}while(!game_over());
	}
	
	//check for winner and board full
	bool game_over()
	{
		if (b.horizontal(player1.choice))
		return true;	
		
		if (b.vertical(player1.choice))
			return true;
		if (b.diagonal(player1.choice))
			return true;
		if (b.diagonal(player2.choice))
			return true;
		if (b.check_full())
		{
			cout<<"Board is FULL!!!!!\n";
			return true;
		}
		return false;
	}
	
	//asks for player input 
	void player_move(player p)
	{
	
		b.display_board();
		do
		{
			cout<<"Player "<<p.num<<"'s turn ("<<p.choice<<")\n";
//			cout<<"Player 1's Choice: |"<<player1.choice<<"| Player 2's Choice: |"<<player2.choice<<"|\n";
			cout<<"Enter the column you want to put your chip in (1-7)\n";
			cin>>drop_input;	
			valid=true;
			if(drop_input>7||drop_input<1)
			{
				cout<<"The value must be between 1 - 7\n";
				valid=false;
			}
		}while(!valid);
		b.move(p.choice,drop_input);
	}

	
};

int main()
{
	game g;
	return 0;
}
