#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2

void initRecordBoard(void); // 初始化记录棋型数组
void initCurrentBoard(void); // 初始化记录当下棋型的数组
void recordtoDisplayArray(void); // 将棋型数组copy到展示屏幕用的数组
void displayBoard(void); //将棋型展示到屏幕上
int error(int x, int y) ; //判断棋子是否到边界，有重复落到已有子的位置， 返回判断结果
int win_judge(int line, int col, int color) ; //判断胜负，胜则返回1

struct point{
		int line ;
		int col ;
} ; //定义结构，用于记录棋子位置
struct point comp(int role, int chess, int aRecordBoard[15][15]) ; //电脑下棋的函数，返回电脑下子位置
int forbidcheck(int aRecordBoard[SIZE][SIZE], int l, int c); //判断禁手的函数，返回判断结果

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//棋盘基本模板 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组用于显示棋盘 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";

//此数组用于记录棋盘格局
int aRecordBoard[SIZE][SIZE];
int CurrentBoard[SIZE][SIZE];

int main()
{
	int forbid ;
    int line, col ;
	char s[10] ;
	int role = 0 ; //记录下棋的局数
	int c ;
	int win ; //胜负结果记录
	int end ;
	int first ; //玩家选择是否先手记录
	initRecordBoard();
	initCurrentBoard();
   	recordtoDisplayArray();

	displayBoard(); 
	printf("work of 雷明宇\n") ;
	printf("即将开始五子棋比赛\n") ;
	printf("people first?Yes,1;No,0\t") ;
	scanf("%d", &first) ;
	if(first == 1)  //人先下子
		for(role = 1; (c = getchar()) != 'Q'; role ++)
		{
			printf("Role: %d\n", role) ;
			printf("PLAYER 1 : please input the position with the format of A,1:") ; //player 1 BLACK
			col = getchar() ;
			if(col == 'Q')
				break ;
			col = col -'A' ;
			getchar() ;
			scanf("%s",s) ;
			line = 15 - atof(s) ;
			getchar() ; //读取用户输入的下子位置
			for(;error(col, line) == 0;)
			{ 
				col = getchar()-'A' ;
				getchar() ;
				scanf("%s",s) ;
				line = 15 - atof(s) ;
				getchar() ;
			} //循环直到输入规范后停止
			//对人的禁手判断
			forbid =  forbidcheck(aRecordBoard, line, col) ;
			if(forbid != 0){
			printf("forbidden move! player2 ,the computer wins the game\n") ;
			return 0 ;}	
    		aRecordBoard[line][col]=1; 
			CurrentBoard[line][col]=3;
    		recordtoDisplayArray();
			printf("\n") ;
    		displayBoard();
			win = win_judge(line,col,1) ; //判断胜负
			if(win == 1)
			{
				printf("WINNER: PLAYER 1, the people\n") ;
				printf("END GAME? 1 for yes\n") ;
				scanf("%d", &end) ;
				if(end == 1)		
					return 0 ;
				else
					break ;
			}
			
			//人下子结束，电脑开始下棋
			struct point pt ;
			printf("PLAYER 2 : the computer:\n") ; //player2 WHITE 电脑下棋
			pt = comp(role, 2, aRecordBoard) ; //电脑思考后落子，返回电脑运算结果
			line = pt.line ;
			col = pt.col ;

			aRecordBoard[line][col]=2;
			CurrentBoard[line][col]=4;
    		recordtoDisplayArray();
			displayBoard();
			printf("computer move: %c, %d\n", 'A'+col, 15-line) ; //输出电脑落子位置

			win = win_judge(line,col,2) ; //判断胜负
			if(win == 1)
			{
				printf("WINNER: PLAYER 2, the computer\n") ;
				printf("END GAME? 1 for yes\n") ;
				scanf("%d", &end) ;
				if(end == 1)		
					return 0 ;
				else
					break ;
			}
     		initCurrentBoard();
		} 
	if(first == 0) //电脑先手
	{		
		for(role = 1; (c = getchar()) != 'Q'; role ++)
		{
			printf("Role: %d\n", role) ;
			struct point pt ; //用于记录电脑落子位置
			printf("PLAYER 1 : the computer:\n") ; //player1 BLACK
			pt = comp(role, 1, aRecordBoard) ;
			line = pt.line ;
			col = pt.col ;
			aRecordBoard[line][col]=1;
			CurrentBoard[line][col]=3;
    		recordtoDisplayArray();
			displayBoard();
			printf("computer move: %c, %d\n", 'A'+col, 15-line) ;

			win = win_judge(line,col,1) ;//判断胜负
			if(win == 1)
			{
				printf("WINNER: PLAYER 1, the computer\n") ;
				printf("END GAME? 1 for yes\n") ;
				scanf("%d", &end) ;
				if(end == 1)		
					return 0 ;
				else
					break ;
			}

			//电脑落子结束，下面读取人的决策
			printf("PLAYER 2 : please input the position with the format of A,1:") ; //player 2 WHITE
			col = getchar() ;
			if(col == 'Q')
				break ;
			col = col -'A' ;
			getchar() ;
			scanf("%s",s) ;
			line = 15 - atof(s) ; //读取完毕
			getchar() ;
			for(;error(col, line) == 0;)
			{ 
				col = getchar()-'A' ;
				getchar() ;
				scanf("%s",s) ;
				line = 15 - atof(s) ;
				getchar() ;
			} //循环直到输入规范后停止
		 
    		aRecordBoard[line][col]=2;
			CurrentBoard[line][col]=4;
    		recordtoDisplayArray();
			printf("\n") ;
    		displayBoard();
			win = win_judge(line,col,2) ;
			if(win == 1)
			{
				printf("WINNER: PLAYER 2, the people\n") ;
				printf("END GAME? 1 for yes\n") ;
				scanf("%d", &end) ;
				if(end == 1)		
					return 0 ;
				else
					break ;
			}
			
     		initCurrentBoard();
		} 
	}
	
	return 0;
 }

//初始化棋盘格局 
void initRecordBoard(void){
//通过双重循环，将aRecordBoard清0
	int i, j ;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			aRecordBoard[i][j] = 0 ;
}

void initCurrentBoard(void){
//通过双重循环，将CurrentBoard清0
	int i, j ;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			CurrentBoard[i][j] = 0 ;
}

int error(int x, int y){
//判断输入是否违法
//违法返回0，不违法返回0
	if(x < 15 && x >= 0 && y < 15 && y >= 0 && aRecordBoard[y][x] == 0)
		return 1 ;
	else{
		printf("Please re-input: ") ;
		return 0 ;
	}
}
//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void)
{
	int i, j ;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE*CHARSIZE+1; j++)
		{
			aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j] ;
		}//第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
		{
		if(aRecordBoard[i][j] == 1)
			{
			aDisplayBoardArray[i][CHARSIZE*j] = play1Pic[0] ;
			aDisplayBoardArray[i][CHARSIZE*j + 1] = play1Pic[1] ;
			}
		if(aRecordBoard[i][j] == 2)
			{
			aDisplayBoardArray[i][CHARSIZE*j] = play2Pic[0] ;
			aDisplayBoardArray[i][CHARSIZE*j + 1] = play2Pic[1] ;
			}
		if(CurrentBoard[i][j] == 3)
			{
			aDisplayBoardArray[i][CHARSIZE*j] = play1CurrentPic[0] ;
			aDisplayBoardArray[i][CHARSIZE*j + 1] = play1CurrentPic[1] ;
			}
		if(CurrentBoard[i][j] == 4)
			{
			aDisplayBoardArray[i][CHARSIZE*j] = play2CurrentPic[0] ;
			aDisplayBoardArray[i][CHARSIZE*j + 1] = play2CurrentPic[1] ;
			}
		}				//第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
//注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
}


//显示棋盘格局 
void displayBoard(void){
	int i;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将aDisplayBoardArray输出到屏幕上
	for(i = 0; i < SIZE; i++)
		printf("%3d %s\n", SIZE-i, aDisplayBoardArray[i]) ;
		
	//第三步：输出最下面的一行字母A B .... 
	printf("    ") ;
	for(i = 0; i < SIZE; i++) 
		printf("%2c", 'A' + i) ;
	printf("\n") ;
} 

int win_judge(int line, int col, int color)
{
//判断胜负的函数
	//line judge
	int i = 1 ; //指向棋子
	int count = 1 ; //记录相同个数
	//每次换方向，要将count，i初始化
	while(i<5 && aRecordBoard[line][col-i] == color && col-i >= 0)
		i++, count++ ;
	 i = 1 ;
	while(i<5 && aRecordBoard[line][col+i] == color && col+i < 15)
		i++, count++ ;
	if(count == 5) //五子相连则胜利
		return 1 ;
	//column judge
	count = 1 ;//每次换方向，要将count，i初始化
	 i = 1 ;
	while(i<5 && aRecordBoard[line-i][col] == color && line-i >= 0)
		i++, count++ ;
	i = 1 ;
	while(i<5 && aRecordBoard[line+i][col] == color && line+i < 15)
		i++, count++ ;
	if(count == 5)//五子相连则胜利
		return 1 ;
	//cross\ judge
	count = 1 ;//每次换方向，要将count，i初始化
	 i = 1 ;
	while(i<5 && aRecordBoard[line-i][col-i] == color && col-i >= 0 && line-i >= 0)
		i++, count++ ;
	i = 1 ;
	while(i<5 && aRecordBoard[line+i][col+i] == color && col+i < 15 && line+i < 15)
		i++, count++ ;
	if(count == 5)//五子相连则胜利
		return 1 ;
	//cross\ judge
	count = 1 ;//每次换方向，要将count，i初始化
	i = 1 ;
	while(i<5 && aRecordBoard[line-i][col+i] == color && line-i >= 0 && col+i < 15)
		i++, count++ ;
	 i = 1 ;
	while(i<5 && aRecordBoard[line+i][col-i] == color && line+i < 15 && col-i >= 0)
		i++, count++ ;
	if(count == 5)//五子相连则胜利
		return 1 ;
	return 0 ;
}


