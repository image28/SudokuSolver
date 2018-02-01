#include <stdio.h>

typedef struct tables
{
	int bit[9][9];
};

int main(int argc, char *argv[])
{
	if ( argc < 81 )
	{
		printf("Incorrect number of arguments\n");
		exit(-1);
	}

	int x,y,d,e,l;
	int count=0;
	int temp=0;
	int prev=0;
	int combo=0;
	struct tables bits[9];
	int intable[9][9];

	// Initialize All Tables
	zero(&intable);
	for(d=0;d<9;d++)
	{
		zero(&bits[d].bit);
	}

	// Fill intable Table With Arguments
	count=1;

	for(x=0;x<9;x++)
	{
		for(y=0;y<9;y++)
		{
			temp=atoi(argv[count]);
			intable[x][y]=temp;
			count++;
		}
	}

	// Print intable Table
	printf("input Table\n-----------------\n");
	print(&intable);

	// Fill bit tables
	while ( ( done(&intable) ) && ( done(&intable) != prev ) )
	{
		prev=done(&intable);

		/*for(d=0;d<9;d++)
		{
			zero(&bits[d].bit);
		}*/
		fillbits(&intable,&bits);

		fillnums(&intable,&bits);
	}

	// Print bit tables ( DEBUG )
	for(d=0;d<9;d++)
	{
		printf("Table %d\n-----------------\n",d+1);
		print(&bits[d].bit);
	}

	printf("Solved\n---------------\n");
	print(&intable);

	return(0);
}

int done(int *table)
{
	int x,y;
	int done=0;

	for(x=0;x<9;x++)
	{
		for(y=0;y<9;y++)
		{
			if ( *(table+((y*9)+x)) == 0 )
			{
				done++;
			}
		}
	}

	return(done);
}

int fillnums(int *table, struct tables *box)
{
	int x,y,d,e;
	int count=1;
	int posx=0;
	int posy=0;
	int zeros=0;

	while ( count < 10 )
	{

		for(d=0;d<9;d=d+3)
		{
			for(e=0;e<9;e=e+3)
			{
				for(x=0;x<3;x++)
				{
					for(y=0;y<3;y++)
					{
						if ( box[count-1].bit[e+y][d+x] == 0 )
						{
							zeros++;
							posx=d+x;
							posy=e+y;
						}
					}
				}

				if ( zeros == 1 )
				{
					*(table+((posy*9)+posx))=count;
				}

				zeros=0;

			}
		}
		count++;
	}

}

int fillbits(int *table, struct tables *box)
{
	int x,y,d,e;
	int startx=0;
	int starty=0;
	int count=1;
	int zeros=0;

	while ( count < 10 )
	{
		for ( x=0; x < 9 ; x++ )
		{

			for ( y=0; y < 9; y++ )
			{

				// set current table to 1 or 0 if the number is > 0
				if ( *(table+((y*9)+x)) == count )
				{
					if ( x < 3 )
					{
						startx=0;
					}else if ( x < 6 ){
						startx=3;
					}else if ( x < 9 ){
						startx=6;
					}

					if ( y < 3 )
					{
						starty=0;
					}else if ( y < 6 ){
						starty=3;
					}else if ( y < 9 ){
						starty=6;
					}

					for(d=0;d<9;d++)
					{
						box[d].bit[y][x]=1;
					}

					for(d=startx;d<startx+3;d++)
					{
						for(e=starty;e<starty+3;e++)
						{
							box[count-1].bit[e][d]=1;
						}
					}


					for(d=0;d<9;d++)
					{
						box[count-1].bit[y][d]=1;
					}

					for(e=0;e<9;e++)
					{
						box[count-1].bit[e][x]=1;
					}

				}
			}
		}

		count++;
	}count=1;

	// Find numbers with two places in a column or row, fill rest with ones
	while ( count < 10 )
	{
		for(x=0;x<9;x=x+3)
		{
			for(y=0;y<9;y=y+3)
			{
				for(d=0;d<3;d++)
				{
					for(e=0;e<3;e++)
					{
						if ( box[count-1].bit[y+e][x+d] == 0 )
						{
							zeros++;
						}
					}

				}

				if ( zeros == 2 )
				{


					zeros=0;
					for(d=0;d<3;d++)
					{
						for(e=0;e<3;e++)
						{
							if ( box[count-1].bit[y+e][x+d] == 0 )
							{
								zeros++;
							}
						}

						// fill vertical box
						if ( zeros == 2 )
						{
							for(e=0;e<9;e++)
							{
								if ( ( e < y ) || ( e > y+2 ) )
								{

									box[count-1].bit[e][x+d]=1;
								}
							}
						}

						zeros=0;
					}

					zeros=0;
					for(d=0;d<3;d++)
					{
						for(e=0;e<3;e++)
						{
							if ( box[count-1].bit[y+d][x+e] == 0 )
							{
								zeros++;
							}
						}

						// fill horizontaly
						if ( zeros == 2 )
						{
							if ( count == 6 )
								printf("%d %d %d %d\n",x,y,d,e);
							for(e=0;e<9;e++)
							{
								if ( ( e < x ) || ( e > x+2 ) )
								{

									box[count-1].bit[y+d][e]=1;
								}
							}
						}

						zeros=0;
					}
				}

				zeros=0;
			}
		}
		count++;
	}
}

int argsin(char *argv, int *table)
{
	int x,y;
	int count=0;

	for(y=0;y<9;y++)
	{
		for(x=0;x<9;x++)
		{
			if ( atoi(*(argv+count)) != 0 )
			{
				*(table+((y*9)+x))=atoi(*(argv+count));
			}
			count++;
		}
	}

}

int zero(int *table)
{
	int x,y;

	for(y=0;y<9;y++)
	{
		for(x=0;x<9;x++)
		{
			*(table+((y*9)+x))=0;
			//printf("%d",*(table+((y*10)+x)));
		}//printf("\n");
	}
}

int print(int *table)
{
	int x,y;
	int space=0;
	int space2=0;

	for(y=0;y<9;y++)
	{
		for(x=0;x<9;x++)
		{
			printf("%d", *(table+((y*9)+x)));
			space++;

			if ( space == 3 )
			{
				printf(" ");
				space=0;
			}
		}printf("\n");
		space2++;

		if ( space2 == 3 )
		{
			printf("\n");
			space2=0;
		}
	}
}
