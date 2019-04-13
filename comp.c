#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define BLACK 1
#define WHITE 2
//计算机下棋的函数
struct point{
		int line ;
		int col ;
} ;
struct point score( int chess, int opchess, int aRecordBoard[SIZE][SIZE]) ;		//记录全棋盘各个点分数的函数

struct point comp(int role, int chess, int aRecordBoard[SIZE][SIZE]){
		int i, j ;
		struct point pt ;
		int opchess ;
		if(chess == 1)
			opchess = 2 ;
		if(chess == 2)
			opchess = 1 ;

		if(role == 1 )   //第一轮电脑下子
		{
			for(i = 0; i < SIZE; i++)
				for(j = 0; j < SIZE; j++)	
					if(aRecordBoard[i][j] == opchess)  //如果人先下，电脑跟随
					{	
						//分如下几种情况，解决万一对手下在棋盘的边界的问题。
						if(error(j ,i+1) == 1){
							pt.line = i+1, pt.col = j ;
							return pt ;}						
						 if(error(j+1 , i+1) == 1){
							pt.line = i+1, pt.col = j-1 ;
							return pt ;}					
						if(error(j-1 , i-1) == 1){
							pt.line = i-1, pt.col = j-1 ;
							return pt ;}
						if(error(j+1 , i-1) == 1){
							pt.line = i-1, pt.col = j+1 ;
							return pt ;}
					}
					//如没有在上述函数中return，便是搜索完成，发现是电脑先下
					
						pt.line = 8 ;		//如果电脑先下，电脑下子在棋盘中央某一地方
						pt.col = 7 ;
						return pt ;

							
		}else{  //不是第一轮
				//第一步，扫描棋盘空白位置，搜索成五情况	
				for(i = 0; i < SIZE; i++)
					for(j = 0; j < SIZE; j++)			
						if(aRecordBoard[i][j] == 0)
						{
							//看自己有没有成五的点
							if(win_judge(i ,j ,chess) == 1)
							{
								pt.line = i, pt.col = j ;
								aRecordBoard[i][j] = 0 ;
								return pt ; //又成五的点就别犹豫赶快下
							}
					
							//阻止对方成五
							//虽然这种阻止可能来不及了
							if(win_judge(i, j, opchess) == 1)
							{
								pt.line = i, pt.col = j ;
								aRecordBoard[i][j] = 0 ;
								return pt ;
							}		
							aRecordBoard[i][j] = 0 ;			//若两种情况都没有，棋盘清零	
						}
				//没有成五情况，进行打分决策
				
				return score(chess, opchess, aRecordBoard) ;
			}
}						

struct point score( int chess, int opchess, int chessboard[SIZE][SIZE])  //用作打分的函数
{
	int myscore[SIZE][SIZE] ; //记录给自己棋盘每一处的打分
	int opscore[SIZE][SIZE] ; //记录给对手棋盘每一处的打分
	int i, j ;
	for(i = 0; i < SIZE; i++) //每次给打分数组清零
		for(j = 0; j < SIZE; j++)
		{
			myscore[i][j] = 0 ;
			opscore[i][j] = 0 ;
		}
	int mymax = 0 ;		//电脑最高分
	int opmax = 0 ;		//对手最高分
	struct point mypt ;		//记录电脑最高分位置
	mypt.line = 0, mypt.col = 0 ;
	struct point oppt ;		//记录对手最高分位置
	oppt.line = 0, oppt.col = 0 ;
	
	//开始打分了

	//扫描全局
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			if(chessboard[i][j] == 0 && (forbidcheck(chessboard, i, j) == 0))
			{
				chessboard[i][j] = 0 ;
				//1.可能构成活四，冲四的
				//1.1空我我我@空，给自己加分
				if( j - 4 >= 0  && chessboard[i][j+1] == 0 && chessboard[i][j-1] == chess && chessboard[i][j-2] == chess &&chessboard[i][j-3]== chess &&chessboard[i][j-4] == 0) 
					myscore[i][j] += 100 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1] == 0 && chessboard[i-1][j-1]== chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == chess && chessboard[i-4][j-4] == 0) 
					myscore[i][j] += 100 ;
                 if( i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== 0 && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == chess && chessboard[i-4][j] == 0)
					myscore[i][j] += 100 ;
                 if( i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 && chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == chess && chessboard[i-4][j+4] == 0) 
					myscore[i][j] += 100 ;
                 if( j + 4 < 15 && j-1>= 0 && chessboard[i][j-1] == 0 && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == chess && chessboard[i][j+4] == 0) 
					myscore[i][j] += 100;
                 if( i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == chess && chessboard[i+4][j+4] == 0) 
					myscore[i][j] += 100 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j] == 0 && chessboard[i+1][j]  == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == chess && chessboard[i+4][j] == 0) 
					myscore[i][j] += 100 ;
                 if( i + 4 < 15 && i-1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1]== chess && chessboard[i+2][j-2] == chess &&chessboard[i+3][j-3] == chess && chessboard[i+4][j-4] == 0) 
					myscore[i][j] += 100 ;

                 //空他他他@空，给对手加分
                 if( j - 4 >= 0  && chessboard[i][j+1]==0 && chessboard[i][j-1] == opchess &&chessboard[i][j-2] == opchess &&chessboard[i][j-3]== opchess && chessboard[i][j-4]==0) 
					opscore[i][j] += 100 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == opchess && chessboard[i-4][j-4]==0)
					 opscore[i][j] += 100 ;
                 if( i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== 0 && chessboard[i-1][j] == opchess && chessboard[i-2][j]== opchess && chessboard[i-3][j] == opchess  && chessboard[i-4][j] == 0) 
					opscore[i][j] += 100 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == opchess && chessboard[i-4][j+4] == 0) 
					opscore[i][j] += 100 ;
                 if( j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == 0 && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == opchess && chessboard[i][j+4] == 0) 
					opscore[i][j] += 100 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == opchess&&chessboard[i+2][j+2] == opchess &&chessboard[i+3][j+3] == opchess && chessboard[i+4][j+4]==0) 
					opscore[i][j] += 100 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j]==0 && chessboard[i+1][j] == opchess && chessboard[i+2][j]== opchess &&chessboard[i+3][j] == opchess && chessboard[i+4][j]==0) 
					opscore[i][j] += 100 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1] == opchess && chessboard[i+2][j-2] == opchess &&chessboard[i+3][j-3] == opchess && chessboard[i+4][j-4]==0) 
					opscore[i][j] += 100 ;

                 //1.2空我我@我空
				if( j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == 0 && chessboard[i][j+1] == chess && chessboard[i][j-1] == chess &&chessboard[i][j-2]== chess && chessboard[i][j-3]== 0) 
					myscore[i][j] += 100 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+2][j+2] == 0 && chessboard[i+1][j+1]== chess && chessboard[i-1][j-1] == chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == 0) 
					myscore[i][j] += 100 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]== 0 && chessboard[i+1][j] == chess && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == 0)
					myscore[i][j] += 100 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == 0 && chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == 0) 
					myscore[i][j] += 100 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == 0 && chessboard[i][j-1] == chess && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == 0) 
					myscore[i][j] += 100;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == 0 && chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == 0) 
					myscore[i][j] += 100 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == 0 && chessboard[i-1][j]  == chess && chessboard[i+1][j] == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == 0) 
					myscore[i][j] += 100 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == 0 && chessboard[i-1][j+1]== chess && chessboard[i+1][j-1] == chess &&chessboard[i+2][j-2] == chess && chessboard[i+3][j-3] == 0) 
					myscore[i][j] += 100 ;

                 //空他他@他空
				if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == 0 && chessboard[i][j+1] == opchess && chessboard[i][j-1] == opchess &&chessboard[i][j-2]== opchess && chessboard[i][j-3]== 0) 
					opscore[i][j] += 100 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+2][j+2] == 0 && chessboard[i+1][j+1]== opchess && chessboard[i-1][j-1] == opchess && chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == 0) 
					opscore[i][j] += 100 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]== 0 && chessboard[i+1][j] == opchess && chessboard[i-1][j] == opchess && chessboard[i-2][j] == opchess && chessboard[i-3][j] == 0)
					opscore[i][j] += 100 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == 0 && chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == 0) 
					opscore[i][j] += 100 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == 0 && chessboard[i][j-1] == opchess && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == 0) 
					opscore[i][j] += 100 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == 0 && chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == opchess && chessboard[i+2][j+2] == opchess && chessboard[i+3][j+3] == 0) 
					opscore[i][j] += 100 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == 0 && chessboard[i-1][j]  == opchess && chessboard[i+1][j] == opchess && chessboard[i+2][j] == opchess && chessboard[i+3][j] == 0) 
					opscore[i][j] += 100 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == 0 && chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1] == opchess &&chessboard[i+2][j-2] == opchess && chessboard[i+3][j-3] == 0) 
					opscore[i][j] += 100 ;

				//1.3他我我我@空
				if( j - 4 >= 0  && chessboard[i][j+1] == 0 && chessboard[i][j-1] == chess && chessboard[i][j-2] == chess &&chessboard[i][j-3]== chess &&chessboard[i][j-4] == opchess) 
					myscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 &&chessboard[i+1][j+1] == 0 && chessboard[i-1][j-1]== chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == chess && chessboard[i-4][j-4] == opchess) 
					myscore[i][j] += 11 ;
                 if(i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== 0 && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == chess && chessboard[i-4][j] == opchess)
					myscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == chess && chessboard[i-4][j+4] == opchess) 
					myscore[i][j] += 11 ;
                 if(j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == 0 && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == chess && chessboard[i][j+4] == opchess) 
					myscore[i][j] += 11 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == chess && chessboard[i+4][j+4] == opchess) 
					myscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j] == 0 && chessboard[i+1][j]  == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == chess && chessboard[i+4][j] == opchess) 
					myscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1]== chess && chessboard[i+2][j-2] == chess &&chessboard[i+3][j-3] == chess && chessboard[i+4][j-4] == opchess) 
					myscore[i][j] += 11 ;

				//我他他他@空
 				  if(j - 4 >= 0  && chessboard[i][j+1]==0 && chessboard[i][j-1] == opchess &&chessboard[i][j-2] == opchess &&chessboard[i][j-3]== opchess && chessboard[i][j-4] == chess) 
					opscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 &&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == opchess && chessboard[i-4][j-4]==chess)
					 opscore[i][j] += 11 ;
                 if( i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== 0 && chessboard[i-1][j] == opchess && chessboard[i-2][j]== opchess && chessboard[i-3][j] == opchess  && chessboard[i-4][j] == chess) 
					opscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == opchess && chessboard[i-4][j+4] == chess) 
					opscore[i][j] += 11 ;
                 if( j + 4 < 15 && j-1>=0&&chessboard[i][j-1] == 0 && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == opchess && chessboard[i][j+4] == chess) 
					opscore[i][j] += 11 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == opchess&&chessboard[i+2][j+2] == opchess &&chessboard[i+3][j+3] == opchess && chessboard[i+4][j+4]==chess) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j]==0 && chessboard[i+1][j] == opchess && chessboard[i+2][j]== opchess &&chessboard[i+3][j] == opchess && chessboard[i+4][j]==chess) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1] == opchess && chessboard[i+2][j-2] == opchess &&chessboard[i+3][j-3] == opchess && chessboard[i+4][j-4]==chess) 
					opscore[i][j] += 11 ;

 				 //1.4他我我@我空
				if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == 0 && chessboard[i][j+1] == chess && chessboard[i][j-1] == chess &&chessboard[i][j-2]== chess && chessboard[i][j-3]== opchess) 
					myscore[i][j] += 11 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+2][j+2] == 0 && chessboard[i+1][j+1]== chess && chessboard[i-1][j-1] == chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == opchess) 
					myscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 &&chessboard[i+2][j]== 0 && chessboard[i+1][j] == chess && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == opchess)
					myscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == 0 && chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == opchess) 
					myscore[i][j] += 11 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == 0 && chessboard[i][j-1] == chess && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == opchess) 
					myscore[i][j] += 11;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == 0 && chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == opchess) 
					myscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 &&chessboard[i-2][j] == 0 && chessboard[i-1][j]  == chess && chessboard[i+1][j] == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == opchess) 
					myscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 &&chessboard[i-2][j+2] == 0 && chessboard[i-1][j+1]== chess && chessboard[i+1][j-1] == chess &&chessboard[i+2][j-2] == chess && chessboard[i+3][j-3] == opchess) 
					myscore[i][j] += 11 ;

                 //我他他@他空
				if(j - 3 >= 0  && j + 2 < 15 &&chessboard[i][j+2] == 0 && chessboard[i][j+1] == opchess && chessboard[i][j-1] == opchess &&chessboard[i][j-2]== opchess && chessboard[i][j-3]== chess) 
					opscore[i][j] += 11 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+2][j+2] == 0 && chessboard[i+1][j+1]== opchess && chessboard[i-1][j-1] == opchess && chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == chess) 
					opscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]== 0 && chessboard[i+1][j] == opchess && chessboard[i-1][j] == opchess && chessboard[i-2][j] == opchess && chessboard[i-3][j] == chess)
					opscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 &&chessboard[i+2][j-2] == 0 && chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == chess) 
					opscore[i][j] += 11 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == 0 && chessboard[i][j-1] == opchess && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == chess) 
					opscore[i][j] += 11 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 &&chessboard[i-2][j-2] == 0 && chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == opchess && chessboard[i+2][j+2] == opchess && chessboard[i+3][j+3] == chess) 
					opscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == 0 && chessboard[i-1][j]  == opchess && chessboard[i+1][j] == opchess && chessboard[i+2][j] == opchess && chessboard[i+3][j] == chess) 
					opscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 &&chessboard[i-2][j+2] == 0 && chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1] == opchess &&chessboard[i+2][j-2] == opchess && chessboard[i+3][j-3] == chess) 
					opscore[i][j] += 11 ;
		
		//1.5空我我@我他
				if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == opchess && chessboard[i][j+1] == chess && chessboard[i][j-1] == chess &&chessboard[i][j-2]== chess && chessboard[i][j-3]== 0) 
					myscore[i][j] += 11 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+2][j+2] == opchess  && chessboard[i+1][j+1]== chess && chessboard[i-1][j-1] == chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == 0) 
					myscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 &&chessboard[i+2][j]== opchess  && chessboard[i+1][j] == chess && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == 0)
					myscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == opchess  && chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == 0) 
					myscore[i][j] += 11 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == opchess  && chessboard[i][j-1] == chess && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == 0) 
					myscore[i][j] += 11;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 &&chessboard[i-2][j-2] == opchess  && chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == 0) 
					myscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == opchess  && chessboard[i-1][j]  == chess && chessboard[i+1][j] == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == 0) 
					myscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 &&chessboard[i-2][j+2] == opchess  && chessboard[i-1][j+1]== chess && chessboard[i+1][j-1] == chess &&chessboard[i+2][j-2] == chess && chessboard[i+3][j-3] == 0) 
					myscore[i][j] += 11 ;

                 //空他他@他我
				if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == chess && chessboard[i][j+1] == opchess && chessboard[i][j-1] == opchess &&chessboard[i][j-2]== opchess && chessboard[i][j-3]== 0) 
					opscore[i][j] += 11 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+2][j+2] == chess && chessboard[i+1][j+1]== opchess && chessboard[i-1][j-1] == opchess && chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == 0) 
					opscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 &&chessboard[i+2][j] == chess && chessboard[i+1][j] == opchess && chessboard[i-1][j] == opchess && chessboard[i-2][j] == opchess && chessboard[i-3][j] == 0)
					opscore[i][j] += 11 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == chess && chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == 0) 
					opscore[i][j] += 11 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == chess && chessboard[i][j-1] == opchess && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == 0) 
					opscore[i][j] += 11 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == chess && chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == opchess && chessboard[i+2][j+2] == opchess && chessboard[i+3][j+3] == 0) 
					opscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == chess && chessboard[i-1][j]  == opchess && chessboard[i+1][j] == opchess && chessboard[i+2][j] == opchess && chessboard[i+3][j] == 0) 
					opscore[i][j] += 11 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == chess && chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1] == opchess &&chessboard[i+2][j-2] == opchess && chessboard[i+3][j-3] == 0) 
					opscore[i][j] += 11 ;
		
			//1.6空我我我@他，给自己加分
				if(j - 4 >= 0 && j + 1 < 15 && chessboard[i][j+1] == opchess && chessboard[i][j-1] == chess && chessboard[i][j-2] == chess &&chessboard[i][j-3]== chess &&chessboard[i][j-4] == 0) 
					myscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 &&chessboard[i+1][j+1] == opchess && chessboard[i-1][j-1]== chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == chess && chessboard[i-4][j-4] == 0) 
					myscore[i][j] += 11 ;
                 if( i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== opchess && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == chess && chessboard[i-4][j] == 0)
					myscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == chess && chessboard[i-4][j+4] == 0) 
					myscore[i][j] += 11 ;
                 if(j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == opchess && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == chess && chessboard[i][j+4] == 0) 
					myscore[i][j] += 11;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == chess && chessboard[i+4][j+4] == 0) 
					myscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j] == opchess && chessboard[i+1][j]  == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == chess && chessboard[i+4][j] == 0) 
					myscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1]== chess && chessboard[i+2][j-2] == chess &&chessboard[i+3][j-3] == chess && chessboard[i+4][j-4] == 0) 
					myscore[i][j] += 11 ;

                 //空他他他@我，给对手加分
                 if( j - 4 >= 0  && j + 1 < 15 &&chessboard[i][j+1]==chess && chessboard[i][j-1] == opchess &&chessboard[i][j-2] == opchess &&chessboard[i][j-3]== opchess && chessboard[i][j-4]==0) 
					opscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1]==chess&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == opchess && chessboard[i-4][j-4]==0)
					 opscore[i][j] += 11 ;
                 if(i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== chess && chessboard[i-1][j] == opchess && chessboard[i-2][j]== opchess && chessboard[i-3][j] == opchess  && chessboard[i-4][j] == 0) 
					opscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == opchess && chessboard[i-4][j+4] == 0) 
					opscore[i][j] += 11 ;
                 if( j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == chess && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == opchess && chessboard[i][j+4] == 0) 
					opscore[i][j] += 11 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 &&chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == opchess&&chessboard[i+2][j+2] == opchess &&chessboard[i+3][j+3] == opchess && chessboard[i+4][j+4]==0) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 &&chessboard[i-1][j]==chess && chessboard[i+1][j] == opchess && chessboard[i+2][j]== opchess &&chessboard[i+3][j] == opchess && chessboard[i+4][j]==0) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == chess && chessboard[i+1][j-1] == opchess && chessboard[i+2][j-2] == opchess &&chessboard[i+3][j-3] == opchess && chessboard[i+4][j-4]==0) 
					opscore[i][j] += 11 ;

 			//1.7他我我我@空，给自己加分
				if( j - 4 >= 0  && j + 1 < 15 && chessboard[i][j+1] == 0 && chessboard[i][j-1] == chess && chessboard[i][j-2] == chess &&chessboard[i][j-3]== chess &&chessboard[i][j-4] == opchess) 
					myscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 &&chessboard[i+1][j+1] == 0 && chessboard[i-1][j-1]== chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == chess && chessboard[i-4][j-4] == opchess) 
					myscore[i][j] += 11 ;
                 if( i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== 0 && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == chess && chessboard[i-4][j] == opchess)
					myscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == chess && chessboard[i-4][j+4] == opchess) 
					myscore[i][j] += 11 ;
                 if( j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == 0 && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == chess && chessboard[i][j+4] == opchess) 
					myscore[i][j] += 11;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == chess && chessboard[i+4][j+4] == opchess) 
					myscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 &&chessboard[i-1][j] == 0 && chessboard[i+1][j]  == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == chess && chessboard[i+4][j] == opchess) 
					myscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 &&chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1]== chess && chessboard[i+2][j-2] == chess &&chessboard[i+3][j-3] == chess && chessboard[i+4][j-4] == opchess) 
					myscore[i][j] += 11 ;

                 //我他他他@空，给对手加分
                 if( j - 4 >= 0  && j + 1 < 15 && chessboard[i][j+1]==0 && chessboard[i][j-1] == opchess &&chessboard[i][j-2] == opchess &&chessboard[i][j-3]== opchess && chessboard[i][j-4]==chess) 
					opscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == opchess && chessboard[i-4][j-4]==chess)
					 opscore[i][j] += 11 ;
                 if(i - 4 >= 0 && i+1 < 15 && chessboard[i+1][j]== 0 && chessboard[i-1][j] == opchess && chessboard[i-2][j]== opchess && chessboard[i-3][j] == opchess  && chessboard[i-4][j] == chess) 
					opscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 && chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == opchess && chessboard[i-4][j+4] == chess) 
					opscore[i][j] += 11 ;
                 if(j + 4 < 15 && j-1>=0 && chessboard[i][j-1] == 0 && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == opchess && chessboard[i][j+4] == chess) 
					opscore[i][j] += 11 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == opchess&&chessboard[i+2][j+2] == opchess &&chessboard[i+3][j+3] == opchess && chessboard[i+4][j+4]==chess) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j]==0 && chessboard[i+1][j] == opchess && chessboard[i+2][j]== opchess &&chessboard[i+3][j] == opchess && chessboard[i+4][j]==chess) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1] == opchess && chessboard[i+2][j-2] == opchess &&chessboard[i+3][j-3] == opchess && chessboard[i+4][j-4]==chess) 
					opscore[i][j] += 11 ;

				//1.8 我空@我我他
				if( j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == chess && chessboard[i][j+1] == 0 && chessboard[i][j-1] == chess &&chessboard[i][j-2]== chess && chessboard[i][j-3]== opchess) 
					myscore[i][j] += 9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+2][j+2] == chess && chessboard[i+1][j+1]== 0 && chessboard[i-1][j-1] == chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == opchess) 
					myscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]== chess && chessboard[i+1][j] == 0 && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == opchess)
					myscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == chess && chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == opchess) 
					myscore[i][j] += 9  ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == chess && chessboard[i][j-1] == 0 && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == opchess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == chess && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == opchess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == chess && chessboard[i-1][j]  == 0 && chessboard[i+1][j] == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == opchess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == chess && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1] == chess &&chessboard[i+2][j-2] == chess && chessboard[i+3][j-3] == opchess) 
					myscore[i][j] += 9 ;

                 //我他他@他空
				if( j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == opchess && chessboard[i][j+1] == 0 && chessboard[i][j-1] == opchess &&chessboard[i][j-2]== opchess && chessboard[i][j-3]== chess) 
					opscore[i][j] += 9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+2][j+2] == opchess && chessboard[i+1][j+1]== 0 && chessboard[i-1][j-1] == opchess && chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == chess) 
					opscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]== opchess && chessboard[i+1][j] == 0 && chessboard[i-1][j] == opchess && chessboard[i-2][j] == opchess && chessboard[i-3][j] == chess)
					opscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == opchess && chessboard[i+1][j-1] == 0 && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == chess) 
					opscore[i][j] += 9 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == opchess && chessboard[i][j-1] == 0 && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == chess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == opchess && chessboard[i-1][j-1] == 0 && chessboard[i+1][j+1] == opchess && chessboard[i+2][j+2] == opchess && chessboard[i+3][j+3] == chess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == opchess && chessboard[i-1][j]  == 0 && chessboard[i+1][j] == opchess && chessboard[i+2][j] == opchess && chessboard[i+3][j] == chess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == opchess && chessboard[i-1][j+1] == 0 && chessboard[i+1][j-1] == opchess &&chessboard[i+2][j-2] == opchess && chessboard[i+3][j-3] == chess) 
					opscore[i][j] += 9 ;

				//1.9 我空我@我他	
				if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == opchess && chessboard[i][j+1] == chess && chessboard[i][j-1] == chess &&chessboard[i][j-2]== 0 && chessboard[i][j-3]== chess) 
					myscore[i][j] += 9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+2][j+2] == opchess  && chessboard[i+1][j+1]== chess && chessboard[i-1][j-1] == chess && chessboard[i-2][j-2] == 0 && chessboard[i-3][j-3] == chess) 
					myscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]== opchess  && chessboard[i+1][j] == chess && chessboard[i-1][j] == chess && chessboard[i-2][j] == 0 && chessboard[i-3][j] == chess)
					myscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == opchess  && chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == 0 && chessboard[i-3][j+3] == chess) 
					myscore[i][j] += 9 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == opchess  && chessboard[i][j-1] == chess && chessboard[i][j+1] == chess && chessboard[i][j+2] == 0 && chessboard[i][j+3] == chess) 
					myscore[i][j] += 9;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == opchess  && chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == 0 && chessboard[i+3][j+3] == chess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == opchess  && chessboard[i-1][j]  == chess && chessboard[i+1][j] == chess && chessboard[i+2][j] == 0 && chessboard[i+3][j] == chess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == opchess  && chessboard[i-1][j+1]== chess && chessboard[i+1][j-1] == chess &&chessboard[i+2][j-2] == 0 && chessboard[i+3][j-3] == chess) 
					myscore[i][j] += 9 ;

                 //他空他@他我
				if( j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2] == chess && chessboard[i][j+1] == opchess && chessboard[i][j-1] == opchess &&chessboard[i][j-2]== 0 && chessboard[i][j-3]== opchess) 
					opscore[i][j] += 9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+2][j+2] == chess && chessboard[i+1][j+1]== opchess && chessboard[i-1][j-1] == opchess && chessboard[i-2][j-2] == 0&& chessboard[i-3][j-3] == opchess) 
					opscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j] == chess && chessboard[i+1][j] == opchess && chessboard[i-1][j] == opchess && chessboard[i-2][j] == 0 && chessboard[i-3][j] == opchess)
					opscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2] == chess && chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == 0 && chessboard[i-3][j+3] == opchess) 
					opscore[i][j] += 9 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2] == chess && chessboard[i][j-1] == opchess && chessboard[i][j+1] == opchess && chessboard[i][j+2] == 0 && chessboard[i][j+3] == opchess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2] == chess && chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == opchess && chessboard[i+2][j+2] == 0 && chessboard[i+3][j+3] == opchess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j] == chess && chessboard[i-1][j]  == opchess && chessboard[i+1][j] == opchess && chessboard[i+2][j] == 0 && chessboard[i+3][j] == opchess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2] == chess && chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1] == opchess &&chessboard[i+2][j-2] ==0 && chessboard[i+3][j-3] == opchess) 
					opscore[i][j] += 9 ;
		
				//1.10我空我我@他，给自己加分
				if( j - 4 >= 0  && j + 1 < 15 && chessboard[i][j+1] == opchess && chessboard[i][j-1] == chess && chessboard[i][j-2] == chess &&chessboard[i][j-3]== 0 &&chessboard[i][j-4] == chess) 
					myscore[i][j] += 9 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1] == opchess && chessboard[i-1][j-1]== chess && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == 0 && chessboard[i-4][j-4] == chess) 
					myscore[i][j] += 9 ;
                 if( i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]== opchess && chessboard[i-1][j] == chess && chessboard[i-2][j] == chess && chessboard[i-3][j] == 0 && chessboard[i-4][j] == chess)
					myscore[i][j] += 9 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == 0 && chessboard[i-4][j+4] == chess) 
					myscore[i][j] += 9 ;
                 if( j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == opchess && chessboard[i][j+1] == chess && chessboard[i][j+2] == chess && chessboard[i][j+3] == 0 && chessboard[i][j+4] == chess) 
					myscore[i][j] += 9;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == 0 && chessboard[i+4][j+4] == chess) 
					myscore[i][j] += 9 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j] == opchess && chessboard[i+1][j]  == chess && chessboard[i+2][j] == chess && chessboard[i+3][j] == 0 && chessboard[i+4][j] == chess) 
					myscore[i][j] += 9 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1]== chess && chessboard[i+2][j-2] == chess &&chessboard[i+3][j-3] == 0 && chessboard[i+4][j-4] == chess) 
					myscore[i][j] += 9 ;

                 //他空他他@我，给对手加分
                 if( j - 4 >= 0  && j + 1 < 15 && chessboard[i][j+1]==chess && chessboard[i][j-1] == opchess &&chessboard[i][j-2] == opchess &&chessboard[i][j-3]== 0 && chessboard[i][j-4]== opchess) 
					opscore[i][j] += 11 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1]==chess&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == 0 && chessboard[i-4][j-4]==opchess)
					 opscore[i][j] += 11 ;
                 if( i - 4 >= 0 && i+1 < 15 && chessboard[i+1][j]== chess && chessboard[i-1][j] == opchess && chessboard[i-2][j]== opchess && chessboard[i-3][j] == 0  && chessboard[i-4][j] == opchess) 
					opscore[i][j] += 11 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 && chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == opchess && chessboard[i-3][j+3] == 0 && chessboard[i-4][j+4] == opchess) 
					opscore[i][j] += 11 ;
                 if(j + 4 < 15 && j-1>=0&& chessboard[i][j-1] == chess && chessboard[i][j+1] == opchess && chessboard[i][j+2] == opchess && chessboard[i][j+3] == 0 && chessboard[i][j+4] == opchess) 
					opscore[i][j] += 11 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == opchess&&chessboard[i+2][j+2] == opchess &&chessboard[i+3][j+3] == 0 && chessboard[i+4][j+4]==opchess) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0 && chessboard[i-1][j]==chess && chessboard[i+1][j] == opchess && chessboard[i+2][j]== opchess &&chessboard[i+3][j] == 0 && chessboard[i+4][j]==opchess) 
					opscore[i][j] += 11 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1] == chess && chessboard[i+1][j-1] == opchess && chessboard[i+2][j-2] == opchess &&chessboard[i+3][j-3] == 0 && chessboard[i+4][j-4]==opchess) 
					opscore[i][j] += 11 ;

				//1.11 @我空我我 
				if(j-4 >= 0 && chessboard[i][j-1] == chess && chessboard[i][j-2] == 0 &&chessboard[i][j-3]== chess &&chessboard[i][j-4] == chess) 
					myscore[i][j] += 9;
                 if(i-4 >= 0 && j-4 >= 0 && chessboard[i-1][j-1]== chess && chessboard[i-2][j-2] == 0 && chessboard[i-3][j-3] == chess && chessboard[i-4][j-4] == chess) 
					myscore[i][j] += 9 ;
                 if(i-4 >= 0 && chessboard[i-1][j] == chess && chessboard[i-2][j] == 0 && chessboard[i-3][j] == chess && chessboard[i-4][j] == chess)
					myscore[i][j] += 9 ;
                 if(i-4 >= 0 && j+4<15 && chessboard[i-1][j+1] == chess && chessboard[i-2][j+2] == 0 && chessboard[i-3][j+3] == chess && chessboard[i-4][j+4] == chess) 
					myscore[i][j] += 9 ;
                 if( j+4<15 &&chessboard[i][j+1] == chess && chessboard[i][j+2] == 0 && chessboard[i][j+3] == chess && chessboard[i][j+4] == chess) 
					myscore[i][j] += 9;
                 if(j+4<15 && i+4<15 && chessboard[i+1][j+1] == chess && chessboard[i+2][j+2] == 0 && chessboard[i+3][j+3] == chess && chessboard[i+4][j+4] == chess) 
					myscore[i][j] += 9 ;
                 if( i+4<15 &&chessboard[i+1][j]  == chess && chessboard[i+2][j] == 0 && chessboard[i+3][j] == chess && chessboard[i+4][j] == chess) 
					myscore[i][j] += 9 ;
                 if( i+4<15 && j-4>=0 &&chessboard[i+1][j-1]== chess && chessboard[i+2][j-2] == 0 &&chessboard[i+3][j-3] == chess && chessboard[i+4][j-4] == chess) 
					myscore[i][j] += 9 ;

                 //@他空他他，给对手加分
                 if(j-4 >= 0 && chessboard[i][j-1] == opchess &&chessboard[i][j-2] == 0 &&chessboard[i][j-3]== opchess && chessboard[i][j-4]== opchess) 
					opscore[i][j] += 9 ;
                 if(i-4 >= 0 && j-4 >= 0 &&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2] == 0 && chessboard[i-3][j-3] == opchess && chessboard[i-4][j-4]==opchess)
					 opscore[i][j] += 9 ;
                 if(i-4 >= 0 && chessboard[i-1][j] == opchess && chessboard[i-2][j]== 0 && chessboard[i-3][j] == opchess  && chessboard[i-4][j] == opchess) 
					opscore[i][j] += 9 ;
                 if(i-4 >= 0 && j+4<15 && chessboard[i-1][j+1] == opchess && chessboard[i-2][j+2] == 0 && chessboard[i-3][j+3] == opchess && chessboard[i-4][j+4] == opchess) 
					opscore[i][j] += 9 ;
                 if(j+4<15 &&chessboard[i][j+1] == opchess && chessboard[i][j+2] == 0 && chessboard[i][j+3] == opchess && chessboard[i][j+4] == opchess) 
					opscore[i][j] += 9 ;
                 if(j+4<15 && i+4<15 &&chessboard[i+1][j+1] == opchess&&chessboard[i+2][j+2] == 0 &&chessboard[i+3][j+3] == opchess && chessboard[i+4][j+4]==opchess) 
					opscore[i][j] += 9 ;
                 if( i+4<15 &&chessboard[i+1][j] == opchess && chessboard[i+2][j]== 0 &&chessboard[i+3][j] == opchess && chessboard[i+4][j]==opchess) 
					opscore[i][j] += 9 ;
                 if( i+4<15 && j-4>=0 &&chessboard[i+1][j-1] == opchess && chessboard[i+2][j-2] == 0 &&chessboard[i+3][j-3] == opchess && chessboard[i+4][j-4]==opchess) 
					opscore[i][j] += 9 ;

 			//1.12 我@空我我
				if(j - 3 >= 0  && j + 2 < 15 &&chessboard[i][j+1] == chess && chessboard[i][j-1] == 0 &&chessboard[i][j-2]== chess && chessboard[i][j-3]== chess) 
					myscore[i][j] += 9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+1][j+1]== chess && chessboard[i-1][j-1] == 0 && chessboard[i-2][j-2] == chess && chessboard[i-3][j-3] == chess) 
					myscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 &&chessboard[i+1][j] == chess && chessboard[i-1][j] == 0 && chessboard[i-2][j] == chess && chessboard[i-3][j] == chess)
					myscore[i][j] += 9 ;
                 if( i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+1][j-1] == chess && chessboard[i-1][j+1] == 0 && chessboard[i-2][j+2] == chess && chessboard[i-3][j+3] == chess) 
					myscore[i][j] += 9 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-1] == chess && chessboard[i][j+1] == 0 && chessboard[i][j+2] == chess && chessboard[i][j+3] == chess) 
					myscore[i][j] += 9;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 &&chessboard[i-1][j-1] == chess && chessboard[i+1][j+1] == 0 && chessboard[i+2][j+2] == chess && chessboard[i+3][j+3] == chess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 &&chessboard[i-1][j]  == chess && chessboard[i+1][j] == 0 && chessboard[i+2][j] == chess && chessboard[i+3][j] == chess) 
					myscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-1][j+1]== chess && chessboard[i+1][j-1] == 0 &&chessboard[i+2][j-2] == chess && chessboard[i+3][j-3] == chess) 
					myscore[i][j] += 9 ;

                 //他@空他他
				if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+1] == opchess && chessboard[i][j-1] == 0 &&chessboard[i][j-2]== opchess && chessboard[i][j-3]== opchess) 
					opscore[i][j] += 9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 &&chessboard[i+1][j+1]== opchess && chessboard[i-1][j-1] == 0 && chessboard[i-2][j-2] == opchess && chessboard[i-3][j-3] == opchess) 
					opscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 &&chessboard[i+1][j] == opchess && chessboard[i-1][j] == 0 && chessboard[i-2][j] == 0 && chessboard[i-3][j] == opchess)
					opscore[i][j] += 9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 &&chessboard[i+1][j-1] == opchess && chessboard[i-1][j+1] == 0 && chessboard[i-2][j+2] == 0 && chessboard[i-3][j+3] == opchess) 
					opscore[i][j] += 9 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-1] == opchess && chessboard[i][j+1] == 0 && chessboard[i][j+2] == 0 && chessboard[i][j+3] == opchess) 
					opscore[i][j] += 9 ;
                 if(i - 2 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 &&chessboard[i-1][j-1] == opchess && chessboard[i+1][j+1] == 0 && chessboard[i+2][j+2] == 0 && chessboard[i+3][j+3] == opchess) 
					opscore[i][j] += 9 ;
                 if(i- 2>= 0 && i + 3 < 15 && chessboard[i-1][j]  == opchess && chessboard[i+1][j] == 0 && chessboard[i+2][j] == 0 && chessboard[i+3][j] == opchess) 
					opscore[i][j] += 9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 &&chessboard[i-1][j+1] == opchess && chessboard[i+1][j-1] == 0 &&chessboard[i+2][j-2] ==0 && chessboard[i+3][j-3] == opchess) 
					opscore[i][j] += 9 ;

				//活四，冲四完毕
				//检查活三

				//第一种情况    空@我我空
                 
                 if( j-1 >= 0 && j+3<15 && chessboard[i][j-1]==0 && chessboard[i][j+1]== chess &&chessboard[i][j+2]==chess &&chessboard[i][j+3]==0) 
					myscore[i][j] += 10 ;
                 if(j-1 >= 0 && i-1 >= 0 && i+3 <15 && j+3 < 15 && chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==chess &&chessboard[i+2][j+2]==chess &&chessboard[i+3][j+3]==0)
					myscore[i][j] += 10 ;
                 if(i-1>=0 && i+3<15 && chessboard[i-1][j]==0 && chessboard[i+1][j]==chess &&chessboard[i+2][j]==chess &&chessboard[i+3][j]==0) 
					myscore[i][j] += 10 ;
                 if(i-1>=0 && i+3<15 && j-3 >= 0 && j+1 < 15 && chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==chess &&chessboard[i+2][j-2]==chess &&chessboard[i+3][j-3]==0) 
					myscore[i][j] += 10 ;
                 if(j-3 >= 0 && j+1 < 15 && chessboard[i][j+1]==0&&chessboard[i][j-1]==chess &&chessboard[i][j-2]==chess &&chessboard[i][j-3]==0)
					myscore[i][j] += 10 ;
                 if(j-3 >= 0 && i-3 >= 0 && i+1 <15 && j+1 < 15 && chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==chess &&chessboard[i-2][j-2]==chess &&chessboard[i-3][j-3]==0) 
					myscore[i][j] += 10 ;
                 if(i-3>=0 && i+1<15 && chessboard[i+1][j]==0 &&chessboard[i-1][j]==chess &&chessboard[i-2][j]==chess &&chessboard[i-3][j]==0)
					myscore[i][j] += 10 ;
                 if(i-3>=0 && i+1<15 &&  j-1 >= 0 && j+3<15 && chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==chess &&chessboard[i-2][j+2]==chess &&chessboard[i-3][j+3]==0)
					myscore[i][j] += 10 ;
                 
					// 空@他他空
                 if(j-1 >= 0 && j+3<15 && chessboard[i][j-1]==0&&chessboard[i][j+1]== opchess &&chessboard[i][j+2]== opchess &&chessboard[i][j+3]==0)
					 opscore[i][j]+=20 ;
                 if(j-1 >= 0 && i-1 >= 0 && i+3 <15 && j+3 < 15 && chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]== opchess &&chessboard[i+2][j+2]== opchess &&chessboard[i+3][j+3]==0)
					 opscore[i][j]+=20 ;
                 if(i-1>=0 && i+3<15 && chessboard[i-1][j]==0&&chessboard[i+1][j]== opchess &&chessboard[i+2][j]== opchess &&chessboard[i+3][j]==0)
					 opscore[i][j]+=20 ;
                 if(i-1>=0 && i+3<15 && j-3 >= 0 && j+1 < 15 &&chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]== opchess &&chessboard[i+2][j-2]== opchess &&chessboard[i+3][j-3]==0)
					 opscore[i][j]+=20 ;
                 if(j-3 >= 0 && j+1 < 15 && chessboard[i][j+1]==0&&chessboard[i][j-1]== opchess &&chessboard[i][j-2]== opchess &&chessboard[i][j-3]==0)
					 opscore[i][j]+=20 ;
                 if(j-3 >= 0 && i-3 >= 0 && i+1 <15 && j+1 < 15 &&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2]== opchess &&chessboard[i-3][j-3]==0)
					 opscore[i][j]+=20;
                 if(i-3>=0 && i+1<15 && chessboard[i+1][j]==0&&chessboard[i-1][j]== opchess &&chessboard[i-2][j]== opchess &&chessboard[i-3][j]==0)
					 opscore[i][j]+=20 ;

 				//第二种情况   空我@我空
                 if(j+2<15 && j-2>=0 &&chessboard[i][j+1]== chess && chessboard[i][j-1]== chess && chessboard[i][j-2]==0&&chessboard[i][j+2]==0)
					 myscore[i][j]+=20 ;
                 if(i+2<15 && i-2>=0 && chessboard[i-1][j]== chess &&chessboard[i+1][j]== chess &&chessboard[i-2][j]==0&&chessboard[i+2][j]==0)
					 myscore[i][j]+=20;
                 if(j+2<15 && j-2>=0 && i+2<15 && i-2>=0 &&chessboard[i+1][j+1]== chess &&chessboard[i-1][j-1]== chess &&chessboard[i-2][j-2]==0&&chessboard[i+2][j+2]==0) 
					 myscore[i][j]+=20 ;
                 if(j+2<15 && j-2>=0 &&i+2<15 && i-2>=0 && chessboard[i-1][j+1]== chess &&chessboard[i+1][j-1]== chess &&chessboard[i+2][j-2]==0&&chessboard[i+2][j-2]==0)
					 myscore[i][j]+=20 ;
                 
				//空他@他空
                 if(j+2<15 && j-2>=0 &&chessboard[i][j+1]== opchess &&chessboard[i][j-1]== opchess &&chessboard[i][j-2]==0&&chessboard[i][j+2]==0) 
					 opscore[i][j]+=9 ;
                 if(i+2<15 && i-2>=0 && chessboard[i-1][j]== opchess &&chessboard[i+1][j]== opchess &&chessboard[i-2][j]==0&&chessboard[i+2][j]==0) 
					 opscore[i][j]+=9 ;
                 if(j+2<15 && j-2>=0 && i+2<15 && i-2>=0 &&chessboard[i+1][j+1]== opchess &&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2]==0&&chessboard[i+2][j+2]==0) 
					 opscore[i][j]+=9 ;
                 if(j+2<15 && j-2>=0 &&i+2<15 && i-2>=0 && chessboard[i-1][j+1]== opchess &&chessboard[i+1][j-1]== opchess &&chessboard[i+2][j-2]==0&&chessboard[i+2][j-2]==0)
					 opscore[i][j]+=9 ;

			 //第三种情况  空@空我我空
                 
                 if(j-1 >= 0 && j+4 < 15 && chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]== chess &&chessboard[i][j+3]== chess &&chessboard[i][j+4]==0) 
					 myscore[i][j]+=15 ;
                 if(j-1 >= 0 && j+4 < 15 && i-1 >= 0 && i+4 < 15 && chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]== chess &&chessboard[i+3][j+3]== chess &&chessboard[i+4][j+4]==0) 
					 myscore[i][j]+=15 ;
                 if(i-1 >= 0 && i+4 < 15 && chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]== chess &&chessboard[i+3][j]== chess &&chessboard[i+4][j]==0)
					 myscore[i][j]+=15 ;
                 if(i-1 >= 0 && i+4 < 15 && j-4 >= 0 && j+1 < 15 && chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]== chess &&chessboard[i+3][j-3]== chess &&chessboard[i+4][j-4]==0) 
					 myscore[i][j]+=15;
                 if( j-4 >= 0 && j+1 < 15 && chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]== chess &&chessboard[i][j-3]== chess &&chessboard[i][j-4]==0) 
					 myscore[i][j]+=15 ;
                 if(i-4 >= 0 && i+1 < 15 && j-4>= 0 && j+1 < 15 && chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]== chess &&chessboard[i-3][j-3]== chess &&chessboard[i-4][j-4]==0) 
					 myscore[i][j]+=15 ;
                 if(i-4 >= 0 && i+1 < 15 &&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]== chess &&chessboard[i-3][j]== chess &&chessboard[i-4][j]==0) 
					 myscore[i][j]+=15 ;
                 if(i-4 >= 0 && i+1 < 15 && j-1 >= 0 && j+4 < 15 && chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]== chess &&chessboard[i-3][j+3]== chess &&chessboard[i-4][j+4]==0) 
					 myscore[i][j]+=15 ;
                 
				//空@空他他空
                 if(j-1 >= 0 && j+4 < 15 && chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]== opchess &&chessboard[i][j+3]== opchess &&chessboard[i][j+4]==0) 
					 opscore[i][j]+=10 ;
                 if(j-1 >= 0 && j+4 < 15 && i-1 >= 0 && i+4 < 15 &&chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]== opchess &&chessboard[i+3][j+3]== opchess &&chessboard[i+4][j+4]==0) 
					 opscore[i][j]+=10 ;
                 if(i-1 >= 0 && i+4 < 15 && chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]== opchess &&chessboard[i+3][j]== opchess &&chessboard[i+4][j]==0) 
					 opscore[i][j]+=10 ;
                 if(i-1 >= 0 && i+4 < 15 && j-4 >= 0 && j+1 < 15 &&chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]== opchess &&chessboard[i+3][j-3]== opchess &&chessboard[i+4][j-4]==0) 
					 opscore[i][j]+=10 ;
                 if( j-4 >= 0 && j+1 < 15 &&chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]== opchess &&chessboard[i][j-3]== opchess &&chessboard[i][j-4]==0) 
					 opscore[i][j]+=10 ;
                 if(i-4 >= 0 && i+1 < 15 && j-4>= 0 && j+1 < 15 && chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]== opchess &&chessboard[i-3][j-3]== opchess &&chessboard[i-4][j-4]==0)
					 opscore[i][j]+=10 ;
                 if(i-4 >= 0 && i+1 < 15 &&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]== opchess &&chessboard[i-3][j]== opchess &&chessboard[i-4][j]==0) 
					 opscore[i][j]+=10 ;
                 if(i-4 >= 0 && i+1 < 15 && j-1 >= 0 && j+4 < 15 &&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]== opchess &&chessboard[i-3][j+3]== opchess &&chessboard[i-4][j+4]==0) 
					 opscore[i][j]+=10 ;

//第四种情况    空我@我空
                 
                 if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2]==0&&chessboard[i][j+1]== chess &&chessboard[i][j-1]==0 && chessboard[i][j-2]== chess  && chessboard[i][j-3]==0) 
					myscore[i][j] += 15 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]== chess &&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]== chess &&chessboard[i-3][j-3]==0) 
					myscore[i][j] += 15;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]==0&&chessboard[i+1][j]== chess  &&chessboard[i-1][j]==0&&chessboard[i-2][j]== chess  &&chessboard[i-3][j]==0) 
					myscore[i][j] += 15;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0)
					myscore[i][j] += 15 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) 
					myscore[i][j] += 15 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) 
					myscore[i][j] += 15 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) 
					myscore[i][j] += 15 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) 
					myscore[i][j] += 15 ;
 
				//空他@他空                
                 if(j - 3 >= 0  && j + 2 < 15 && chessboard[i][j+2]==0&&chessboard[i][j+1]== opchess &&chessboard[i][j-1]==0&&chessboard[i][j-2]== opchess &&chessboard[i][j-3]==0) 
						opscore[i][j]+=9 ;
                 if(j - 3 >= 0 && i - 3 >= 0 && i+2 < 15 && j+2 < 15 && chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]== opchess &&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]== opchess &&chessboard[i-3][j-3]==0) 
						opscore[i][j]+=9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && chessboard[i+2][j]==0&&chessboard[i+1][j]== opchess &&chessboard[i-1][j]==0&&chessboard[i-2][j]== opchess &&chessboard[i-3][j]==0) 
						opscore[i][j]+=9 ;
                 if(i - 3 >= 0 && i + 2 < 15 && j + 3 < 15 && j - 2 >= 0 && chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]== opchess &&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]== opchess &&chessboard[i-3][j+3]==0) 
						opscore[i][j]+=9 ;
                 if(j - 2>= 0 && j + 3 < 15 && chessboard[i][j-2]==0&&chessboard[i][j-1]== opchess &&chessboard[i][j+1]==0&&chessboard[i][j+2]== opchess &&chessboard[i][j+3]==0) 
						opscore[i][j]+=9 ;
                 if(i-2 >= 0 && j-2 >= 0 && i +3 < 15 && j+3 < 15 && chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]== opchess &&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]== opchess &&chessboard[i+3][j+3]==0) 
						opscore[i][j]+=9 ;
                 if(i-2 >= 0 && i+3 < 15 && chessboard[i-2][j]==0&&chessboard[i-1][j]== opchess &&chessboard[i+1][j]==0&&chessboard[i+2][j]== opchess &&chessboard[i+3][j]==0) 
						opscore[i][j]+=9 ;
                 if(i-2 >= 0 && i+3 < 15 && j - 3>= 0 && j + 2 < 15 && chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]== opchess &&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]== opchess &&chessboard[i+3][j-3]==0) 
						opscore[i][j]+=9 ;
                 
               //第五种情况     空我空我@空
                 
                 if(j - 4 >= 0  && j + 1 < 15 && chessboard[i][j+1]==0&&chessboard[i][j-1]== chess &&chessboard[i][j-2]==0&&chessboard[i][j-3]== chess &&chessboard[i][j-4]==0) 
					myscore[i][j] += 15 ;
                 if(j - 4 >= 0 && i - 4 >= 0 && i+1 < 15 && j+1 < 15 && chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== chess &&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]== chess &&chessboard[i-4][j-4]==0) 
					myscore[i][j] += 15 ;
                 if(i - 4 >= 0 && i+1 < 15 &&chessboard[i+1][j]==0&&chessboard[i-1][j]== chess &&chessboard[i-2][j]==0&&chessboard[i-3][j]== chess &&chessboard[i-4][j]==0) 
					myscore[i][j] += 15 ;
                 if(i - 4 >= 0 && j + 4 < 15 && i + 1 < 15 && j-1 >= 0 &&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]== chess &&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]== chess &&chessboard[i-4][j+4]==0) 
					myscore[i][j] += 15 ;
                 if(j + 4 < 15 && j-1>=0&& chessboard[i][j-1]==0&&chessboard[i][j+1]== chess &&chessboard[i][j+2]==0&&chessboard[i][j+3]== chess &&chessboard[i][j+4]==0) 
					myscore[i][j] += 15 ;
                 if(i - 1 >= 0 && j - 1 >= 0 && i + 4 < 15 && j+4 < 15 && chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]== chess &&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]== chess &&chessboard[i+4][j+4]==0) 
					myscore[i][j] += 15 ;
                 if(i + 4 < 15 && i - 1 >= 0 &&chessboard[i-1][j]==0&&chessboard[i+1][j]== chess &&chessboard[i+2][j]==0&&chessboard[i+3][j]== chess &&chessboard[i+4][j]==0) 
					myscore[i][j] += 15 ;
                 if(i + 4 < 15 && i - 1 >= 0  && j - 4 >= 0 && j +1 < 15 && chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]== chess &&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]== chess &&chessboard[i+4][j-4]==0) 
					myscore[i][j] += 15 ;
               
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]== opchess &&chessboard[i][j-2]==0&&chessboard[i][j-3]== opchess &&chessboard[i][j-4]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== opchess &&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]== opchess &&chessboard[i-4][j-4]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]== opchess &&chessboard[i-2][j]==0&&chessboard[i-3][j]== opchess &&chessboard[i-4][j]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]== opchess &&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]== opchess &&chessboard[i-4][j+4]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]== opchess &&chessboard[i][j+2]==0&&chessboard[i][j+3]== opchess &&chessboard[i][j+4]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]== opchess &&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]== opchess &&chessboard[i+4][j+4]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]== opchess &&chessboard[i+2][j]==0&&chessboard[i+3][j]== opchess &&chessboard[i+4][j]==0) 
					opscore[i][j] += 9 ;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]== opchess &&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]== opchess &&chessboard[i+4][j-4]==0)
					opscore[i][j] += 9 ;
                 
  

				//活三检查完毕，判断两个
				//第一种情况  空空@我空空
				    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]== chess &&chessboard[i][j+2]==0&&chessboard[i][j+3]==0)
				 		 myscore[i][j] += 5 ;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]== chess &&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==0) 
						 myscore[i][j] += 5 ;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]== chess &&chessboard[i+2][j]==0&&chessboard[i+3][j]==0)
						 myscore[i][j] += 5 ;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]== chess &&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==0) 
						 myscore[i][j] += 5 ;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]== chess &&chessboard[i][j-2]==0&&chessboard[i][j-3]==0) 
						 myscore[i][j] += 5 ;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]== chess &&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==0) 
						 myscore[i][j] += 5 ;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]== chess &&chessboard[i-2][j]==0&&chessboard[i-3][j]==0) 
						 myscore[i][j] += 5 ;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]== chess &&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==0) 
						 myscore[i][j] += 5 ;
	
					//不检查对方的了
					//第二种情况，空空@空我空
            	    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]== chess &&chessboard[i][j+3]==0) 
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]== chess &&chessboard[i+3][j+3]==0) 
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]== chess &&chessboard[i+3][j]==0) 
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]== chess &&chessboard[i+3][j-3]==0) 
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]== chess &&chessboard[i][j-3]==0) 
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]== chess &&chessboard[i-3][j-3]==0)
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]== chess &&chessboard[i-3][j]==0) 
				 		 myscore[i][j] += 4 ;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]== chess &&chessboard[i-3][j+3]==0)
				 		 myscore[i][j] += 4 ;

					//评分完毕！！！！！！撒花！！！！！！
			}
             //下面开始比较分数
 			//分别筛选电脑和玩家的最高分，并保存其坐标 
      		 for( i = 0; i < 15; i++)
           		 for( j = 0; j < 15; j++)
					{
                  	  if(myscore[i][j] > mymax){
                                                 mymax = myscore[i][j] ;
                                                 mypt.line = i ;
                                                 mypt.col = j ;
                                               }
                    if(opscore[i][j] > opmax){
                                                 opmax = opscore[i][j] ;
                                                 oppt.line = i;
                                                 oppt.col = j;
                                               }
                    } 
                    
       //分析两个最高分，决定攻还是防
       
       if(mymax >= 100)                                  //电脑能成四，当然自己成四
                       return mypt ;
  
       if(opmax >= 100)                            //阻止玩家四 
                       return oppt ;

       if(mymax >= 20)                            //电脑能成双三 （或更多） 
                       return mypt ;
     
       if(opmax >= 18)                                    //阻止玩家双三 （或更多）   
                       return oppt ;    
       
       if(mymax == 19 || mymax == 16)                                  //另一种不能取胜双三
                        return mypt ;
     
       if(opmax == 17 || opmax ==16)
                       return oppt ;
                       
       if(mymax < 16 && mymax >= 10)                                   //3,3+1 ,3+2，单4 
                       return mypt ;
   
       if(opmax < 16 && opmax >= 10)                                      
                        return oppt ;
                            

       //其他情况不管玩家，电脑走最好的
       return mypt ;
} 


