
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int **createboard(int **a, int rows, int col, int c);
int checkboard(int **a, int rows, int cols);
void showboard(int **a, int col, int row);
void destroyboard(int **a, int rows);
void menuchoice();
void sortboard(int **a, int rows, int cols);
int **add(int **a, int y1, int y2, int y3);
int **bomb(int **a, int y1, int y2, int rows, int cols);
int **pr(int **a, int rows,  int cols);
int **pl(int **a, int rows,  int cols);
void hammercheck(int **a, int rows, int cols, int y1, int y2);
void hammer(int rows, int cols, int y1, int y2, int ***a, int c);

int score=0;
int check=0;

int main (void)
{
	int **a, b, rows, cols, i, j, c,y1,y2,y3,lvl=1;
	char k[20]={0};
	
	srand(time(NULL));
	
	
		printf("Please give the number of the rows (they have to be between 3 and 20): ");
		scanf("%d", &rows);
		printf("Please give the number of the collumns (they have to be between 3 and 20): ");
		scanf("%d", &cols);
	
			
	while((cols<=2 || rows<=2) || (cols>20 || rows>20))
	{
		printf("Wrong option! Try again:");
		scanf("%d %d", &rows, &cols);
	}

	printf("Give a number of the colours of the tiles:");
	scanf("%d", &c);

	while(c>=10 || c<=2)
	{
		printf("Wrong option! Try again:");
		scanf("%d", &c);
	}

	printf("\n");
	a = createboard(a,rows,cols,c);
		/*for(i=0;i<rows;i++)
		{
			for(j=0;j<cols;j++)	
				a[i][j]=0;
		}
		a[0][0]=3;*/
	while(1)
	{
		printf("\n\n");
		showboard(a, cols, rows);
		printf("Level %d. \n",lvl);
		printf("Score:%d. \n",score);
		printf("\n");
		menuchoice();
		while(getchar()!='\n');												//check for the commands.
			scanf("%[^\n]", k);
		if(k[0]=='x')
		{
			if(k[1]=='\0')
				break;
			else
				printf("You gave wrong command! Please try again:");
		}
		else if(k[0]=='p' && k[1]=='l')
		{
			if(k[2]=='\0')
			{
				a=pl(a,rows,cols);
			}
			else
				printf("You gave wrong command! Please try again:");
		}
		else if(k[0]=='p' && k[1]=='r')
		{
			if(k[2]=='\0')
			{
				a=pr(a,rows,cols);
			}
			else
				printf("You gave wrong command! Please try again:");
		}
		else if(k[0]=='b')
		{
			if(strlen(k)>8 || strlen(k)<5)
				printf("You gave wrong command! Please try again:");
			if(k[1]==' ')
			{
				if((k[3]==',') && (k[2]>='1' && k[2]<='9') && (k[4]>='1' && k[4]<='9') && k[5]=='\0') 		//oneone
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+4))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						score=score+50;
						a=bomb(a, y1,y2,rows,cols);
					}

				}
				else if((k[3]==',') && (k[2]>='1' && k[2]<='9') && (k[4]>='1' && k[4]<='9') && (k[5]>='0' && k[5]<='9') && k[6]=='\0')     //onedouble
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+4))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						score=score+50;
						a=bomb(a, y1,y2,rows,cols);
					}

				}
				else if((k[4]==',') && (k[2]>='1' && k[2]<='9') && (k[3]>='0' && k[3]<='9') && (k[5]>='1' && k[5]<='9') && k[6]=='\0')     //doubleone
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+5))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						score=score+50;
						a=bomb(a, y1,y2,rows,cols);
					}

				}
				else if((k[4]==',') && (k[2]>='1' && k[2]<='9') && (k[3]>='0' && k[3]<='9') && (k[5]>='1' && k[5]<='9') && (k[6]>='0' && k[6]<='9') && k[7]=='\0')  //doubledouble
				{  
					y1 = atoi((k+2))-1;
					y2 = atoi((k+5))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						score=score+50;
						a=bomb(a, y1,y2,rows,cols);
					}

				}
				else
					printf("You gave wrong command! Please try again!");
			}
		}
		else if(k[0]=='a')
		{
			if(strlen(k)>10 || strlen(k)<7)
				printf("You gave wrong command! Please try again:");
			if(k[1]==' ')
			{
				if((k[3]==',') && (k[2]>='1' && k[2]<='9') && (k[4]>='1' && k[4]<='9') && (k[5]==' ') && (k[6]>='1' && k[6]<='9') && k[7]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+4))-1;
					y3 = atoi((k+6));
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(y3>c)
						printf("The colour does not exist in this game mode! Please try again!");
					else
					{
						a=add(a, y1, y2, y3);
					}
				}
				else if((k[3]==',') && (k[2]>='1' && k[2]<='9') && (k[4]>='1' && k[4]<='9') && (k[5]>='0' && k[5]<='9') && k[6]==' ' && (k[7]>='1' && k[7]<='9') && k[8]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+4))-1;
					y3 = atoi((k+7));
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(y3>c)
						printf("The colour does not exist in this game mode! Please try again!");
					else
					{
						a=add(a, y1, y2, y3);
					}
				}
				else if((k[4]==',') && (k[2]>='1' && k[2]<='9') && (k[3]>='0' && k[3]<='9') && (k[5]>='1' && k[5]<='9') && k[6]==' ' && (k[7]>='1' && k[7]<='9') && k[8]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+5))-1;
					y3 = atoi((k+7));
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(y3>c)
						printf("The colour does not exist in this game mode! Please try again!");
					else
					{
						a=add(a, y1, y2, y3);
					}
				}
				else if((k[4]==',') && (k[2]>='1' && k[2]<='9') && (k[3]>='0' && k[3]<='9') && (k[5]>='1' && k[5]<='9') && (k[6]>='0' && k[6]<='9') && k[7]==' ' && (k[8]>='1' && k[8]<='9') && k[9]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+5))-1;
					y3 = atoi((k+8));
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(y3>c)
						printf("The colour does not exist in this game mode! Please try again!");
					else
					{
						a=add(a, y1, y2, y3);
					}
				}
				else
					printf("You gave wrong command! Please try again!");
			}
		}
		else if(k[0]=='h')
		{
			if(strlen(k)>8 || strlen(k)<5)
				printf("You gave wrong command! Please try again:");
			if(k[1]==' ')
			{
				if((k[3]==',') && (k[2]>='1' && k[2]<='9') && (k[4]>='1' && k[4]<='9') && k[5]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+4))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						hammercheck(a, rows, cols, y1, y2);
						if(check==1)
							hammer(rows,cols,y1,y2,&a,a[y1][y2]);
					}
				}
				else if((k[3]==',') && (k[2]>='1' && k[2]<='9') && (k[4]>='1' && k[4]<='9') && (k[5]>='0' && k[5]<='9') && k[6]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+4))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						hammercheck(a, rows, cols, y1, y2);
						if(check==1)
							hammer(rows,cols,y1,y2,&a,a[y1][y2]);
					}
				}
				else if((k[4]==',') && (k[2]>='1' && k[2]<='9') && (k[3]>='0' && k[3]<='9') && (k[5]>='1' && k[5]<='9') && k[6]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+5))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						hammercheck(a, rows, cols, y1, y2);
						if(check==1)
							hammer(rows,cols,y1,y2,&a,a[y1][y2]);
					}
				}
				else if((k[4]==',') && (k[2]>='1' && k[2]<='9') && (k[3]>='0' && k[3]<='9') && (k[5]>='1' && k[5]<='9') && (k[6]>='0' && k[6]<='9') && k[7]=='\0')
				{
					y1 = atoi((k+2))-1;
					y2 = atoi((k+5))-1;
					if(y1>=rows || y2>=cols)
						printf("The directions are not in the board! Try again:");
					else if(a[y1][y2]==0)
						printf("The tile is broken! Please try again:");
					else
					{
						hammercheck(a, rows, cols, y1, y2);
						if(check==1)
							hammer(rows,cols,y1,y2,&a,a[y1][y2]);
					}
				}
				else
					printf("You gave wrong command! Please try again!");
			}
		}
		else
			printf("You gave wrong command! Please try again!");

	
		sortboard(a,rows,cols);
		b = checkboard(a,rows,cols);
		if(b==0)
		{
			printf("\nCongratulations! Please move on to the next round!");
			destroyboard(a,rows);
			rows++;
			cols++;
			lvl++;
			score=score+150;
			a = createboard(a,rows,cols,c);
		}

	}
	destroyboard(a,rows);
	printf("\nCongratulations, you have passed:%d levels\n", lvl-1);
	printf("You have finished the game with %d score!\n", score);
	printf("Thanks for playing! See you soon!\n");
	return 0;

}

int **createboard(int **a, int rows, int cols, int c)
{
	int i,j;
	a=(int**)malloc(rows*sizeof(int*)); /*creation of the board*/

	if(a==NULL)
		exit(1);

	for(i=0;i<rows;i++)
	{
		a[i]=(int*)malloc(cols*sizeof(int));

		if(a[i]==NULL)
			exit(1);
	}

	for(i=0;i<rows;i++) /*fill of the board*/ 
	{
		for(j=0;j<cols;j++)
		{
			a[i][j]= 1+rand()%c;
		}
	}
	return a;
}

void showboard(int **a, int col, int row) /*show of the board*/
{
	int i, j;

	printf("   ");

	for(i=0;i<col;i++)
		printf("%3d",i+1);

	printf("\n----");

	for(i=0;i<col;i++)
		printf("---");

	printf("\n");

	for(i=0;i<row;i++)
	{
		printf("%2d|",i+1);

		for(j=0;j<col;j++)
		{
			if(a[i][j]==0)
				printf("  .");
			else
				printf("%3d",a[i][j]);
		}

		printf("\n");
	}	
}

void destroyboard(int **a, int rows)
{
	int i;
	for(i=0;i<rows;i++)/*free the board*/
	{
		free(a[i]);
	}
	free(a);
}

void menuchoice()
{
	printf("In order to play, you have 4 choices:\n");
	printf("\t(h_row,collumn) to hammer a number of blocks,\n");
	printf("\t(b_row,collumn) to bomb a specific amount of blocks,\n");
	printf("\t(a_row,collumn_the number of the colour you want) to add a block of tile,\n");
	printf("\t(pl or pr) to unite the board\n");
	printf("In order to exit the game, just press 'x'\n");
	printf("Make your move:");
}

int checkboard(int **a, int rows, int cols)								//check the board so as to reallocate the board
{
	int i,j,check=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			if(a[i][j] != 0)
				check=1;
		}
	}
	return check;
}

void sortboard(int **a, int rows, int cols)								//sort form top to bottom
{
	int i,j,tmp,k=0;
	while(k<rows)
	{
		for(j=0;j<cols;j++)
		{
			for(i=1;i<rows;i++)
			{
				if(a[i][j]==0 && a[i-1][j]!=0)
				{
					tmp=a[i-1][j];
					a[i-1][j]=a[i][j];
					a[i][j]=tmp;
				}
			}
		}
		k++;
	}
}

int **add(int **a, int y1, int y2, int y3)								//add tile
{
	if(a[y1][y2]==0)
		a[y1][y2]=y3;
	else 
		printf("There is already a tile with colour! Please try again:");
	return a;
}

int **bomb(int **a, int y1, int y2, int rows, int cols)							//bomb tile
{
	int w=1;

	if(y1-1<0 || y2-1<0)
	{
		w=0;
		printf("You can't bomb the tile, it's out of the area!");
		score=score-50;
	}
	if(y1+1>=rows || y2+1>=cols)
	{
		w=0;
		printf("You can't bomb the tile, it's out of the area!");
		score=score-50;
	}
	
	if(w==1)
	{
		a[y1-1][y2-1]=0;
		a[y1-1][y2]=0;
		a[y1-1][y2+1]=0;
		a[y1][y2-1]=0;
		a[y1][y2]=0;
		a[y1][y2+1]=0;
		a[y1+1][y2-1]=0;
		a[y1+1][y2]=0;
		a[y1+1][y2+1]=0;
	}

	return a;	
}

int **pr(int **a, int rows,  int cols)									//push right
{
	int q=1,i,j,k=0,tmp;
	for(j=0;j<cols;j++)
	{
		if(a[rows-1][j]==0)
		{
			q=0;
			k=j;
		}
	}
	if(q==1)
		printf("You can't shift right the board! Please try other option:");
	else
	{
		
		while(k<cols*2)
		{
			for(i=0;i<rows;i++)
			{
				for(j=1;j<cols;j++)
				{
					if(a[rows-1][j]==0)
					{
						tmp=a[i][j-1];
						a[i][j-1]=a[i][j];
						a[i][j]=tmp;
					}
				}
			}	
			k++;
		}
	}
	return a;
}

int **pl(int **a, int rows,  int cols)									//push left
{
	int q=1,i,j,k=0,tmp;
	for(j=0;j<cols;j++)
	{
		if(a[rows-1][j]==0)
		{
			q=0;
			k=j;
		}
	}
	if(q==1)
		printf("You can't shift left the board! Please try other option:");
	else
	{
		
		while(k<cols*2)
		{
			for(i=0;i<rows;i++)
			{
				for(j=cols-1;j>=0;j--)
				{
					if(a[rows-1][j]==0)
					{
						tmp=a[i][j+1];
						a[i][j+1]=a[i][j];
						a[i][j]=tmp;
					}
				}
			}	
			k++;
		}
	}
	return a;
}

void hammercheck(int **a, int rows, int cols, int y1, int y2)
{

	check=0;									//check for lonely tile
	if(y1==0 && y2==0)
	{
		if(a[y1][y2+1]==a[y1][y2]) check=1;
		if(a[y1+1][y2]==a[y1][y2]) check=1;
	}
	else if(y1==rows-1 && y2==cols)
	{
		if(a[y1-1][y2]==a[y1][y2]) check=1;
		if(a[y1][y2-1]==a[y1][y2]) check=1;
	}
	else if(y1==0 && y2==cols)
	{
		if(a[y1][y2-1]==a[y1][y2]) check=1;
		if(a[y1+1][y2]==a[y1][y2]) check=1;
	}
	else if(y1==rows-1 && y2==0)
	{
		if(a[y1-1][y2]==a[y1][y2]) check=1;
		if(a[y1][y2+1]==a[y1][y2]) check=1;
	}
	else if(y1==rows-1)
	{
		if(a[y1-1][y2]==a[y1][y2]) check=1;
		if(a[y1][y2-1]==a[y1][y2]) check=1;
		if(a[y1][y2+1]==a[y1][y2]) check=1;
	}
	else if(y1==0)
	{
		if(a[y1][y2-1]==a[y1][y2]) check=1;
		if(a[y1][y2+1]==a[y1][y2]) check=1;
		if(a[y1+1][y2]==a[y1][y2]) check=1;
	}
	else if(y2==cols)
	{
		if(a[y1-1][y2]==a[y1][y2]) check=1;
		if(a[y1][y2-1]==a[y1][y2]) check=1;
		if(a[y1+1][y2]==a[y1][y2]) check=1;
	}
	else if(y2==0)
	{
		if(a[y1-1][y2]==a[y1][y2]) check=1;
		if(a[y1][y2+1]==a[y1][y2]) check=1;
		if(a[y1+1][y2]==a[y1][y2]) check=1;
	}
	else
	{
		if(a[y1-1][y2]==a[y1][y2]) check=1;
		if(a[y1][y2-1]==a[y1][y2]) check=1;
		if(a[y1][y2+1]==a[y1][y2]) check=1;
		if(a[y1+1][y2]==a[y1][y2]) check=1;
	}

	if(check==0)
	{
		printf("You do not play fair, please give other option!");
	}
}

void hammer(int rows, int cols, int y1, int y2, int ***a, int c)
{
	printf("ERROR: %d\n", c);
	if(*a[y1][y2]!=c)
		return;
	
	if(y1+1<=rows)
	{
		if(*a[y1+1][y2]==*a[y1][y2])
			hammer(rows,cols,y1+1,y2,a,c);
	}
	if(y1-1>=0)
	{
		if(*a[y1-1][y2]==*a[y1][y2])
			hammer(rows,cols,y1-1,y2,a,c);
	}
	if(y2+1<=cols)
	{
		if(*a[y1][y2+1]==*a[y1][y2])
			hammer(rows,cols,y1,y2+1,a,c);
	}
	if(y2-1>=0)
	{
		if(*a[y1][y2-1]==*a[y1][y2])
			hammer(rows,cols,y1,y2-1,a,c);
	}
	
	*a[y1][y2]=0;
}




