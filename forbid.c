#include <stdio.h>
#define NO_FORBIDDEN 0   //无禁手
#define THREE_THREE_FORBIDDEN 1	//活三禁手	
#define FOUR_FOUR_FORBIDDEN 2 	//活四，冲四禁手
#define LONG_FORBIDDEN 3 	//长连禁手

#define BLACK 1
#define SIZE 15
int pforbidcheck(int aRecordBoard[SIZE][SIZE], int i, int j, int same, int dir) ;

int forbidcheck(int aRecordBoard[SIZE][SIZE], int l, int c) 
{
	int same[8] ;			//记录连续相同黑棋
	int empty[8] ;		//跳过连续相同后的空白
	int jumpsame[8] ;		//跳过连续相同后的空白后的相同
	int jumpempty[8] ;		//跳过连续相同后的空白后的相同后的空白
	int jumpjumpsame[8] ;
//	int aRecordBoard1[15][15] ;

	int i = 0, j = 0 ;
	//复制棋形版
/*	for(i = 0; i < 15; i++)
		for(l = 0; j < 15; j++)
			aRecordBoard1[i][j] = aRecordBoard[i][j]	; */

	 i = 0 ;
	for(i = 0; i < 8; i++){
		same[i] = empty[i] = jumpsame[i] = 0 ;
		jumpempty[i] = jumpjumpsame[i] = 0 ;
	}
	
	aRecordBoard[l][c] = BLACK ;
	int x, y ;  //x for line searching, y for column searching

	//search leftwards 0
	for(y = c-1; y >= 0 && aRecordBoard[l][y] == BLACK; y--, same[0]++) ;
	for(;y >= 0 && aRecordBoard[l][y] == 0; y--, empty[0]++) ;
	for(;y >= 0 && aRecordBoard[l][y] == BLACK; y--, jumpsame[0]++) ;	
	for(;y >= 0 && aRecordBoard[l][y] == 0; y--, jumpempty[0]++) ;
	for(;y >= 0 && aRecordBoard[l][y] == BLACK; y--, jumpjumpsame[0]++) ;

	//search rightwards 4
	for(y = c+1; y < 15 && aRecordBoard[l][y] == BLACK; y++, same[4]++) ;
	for(;y < 15 && aRecordBoard[l][y] == 0; y++, empty[4]++) ;
	for(;y < 15 && aRecordBoard[l][y] == BLACK; y++, jumpsame[4]++) ;	
	for(;y < 15 && aRecordBoard[l][y] == 0; y++, jumpempty[4]++) ;
	for(;y < 15 && aRecordBoard[l][y] == BLACK; y++, jumpjumpsame[4]++) ;
	
	//search leftup 1
	for(y = c-1, x = l-1; y >= 0 && x >= 0 && aRecordBoard[x][y] == BLACK; y--, x--, same[1]++) ;
	for(;y >= 0 && x >= 0 && aRecordBoard[x][y] == 0; y--, x--, empty[1]++) ;
	for(;y >= 0 && x >= 0 && aRecordBoard[x][y] == BLACK; y--, x--, jumpsame[1]++) ;	
	for(;y >= 0 && x >= 0 && aRecordBoard[x][y] == 0; y--, x--, jumpempty[1]++) ;
	for(;y >= 0 && x >= 0 && aRecordBoard[x][y] == BLACK; y--, x--, jumpjumpsame[1]++) ;

	//search rightdown 5
	for(y = c+1, x = l+1; y < 15 && x < 15 && aRecordBoard[x][y] == BLACK; y++, x++, same[5]++) ;
	for(;y < 15 && x < 15 && aRecordBoard[x][y] == 0; y++, x++, empty[5]++) ;
	for(;y < 15 && x < 15 && aRecordBoard[x][y] == BLACK; y++, x++, jumpsame[5]++) ;	
	for(;y < 15 && x < 15 && aRecordBoard[x][y] == 0; y++, x++, jumpempty[5]++) ;
	for(;y < 15 && x < 15 && aRecordBoard[x][y] == BLACK; y++, x++, jumpjumpsame[5]++) ;

	//search upwards 2
	for(x = l-1; x >= 0 && aRecordBoard[x][c] == BLACK; x--, same[2]++) ;
	for(; x >= 0 && aRecordBoard[x][c] == 0; x--, empty[2]++) ;
	for(; x >= 0 && aRecordBoard[x][c] == BLACK; x--, jumpsame[2]++) ;
	for(; x >= 0 && aRecordBoard[x][c] == 0; x--, jumpempty[2]++) ;
	for(; x >= 0 && aRecordBoard[x][c] == BLACK; x--, jumpjumpsame[2]++) ;

	//search dowmwards 6
	for(x = l+1; x < 15 && aRecordBoard[x][c] == BLACK; x++, same[6]++) ;
	for(; x < 15 && aRecordBoard[x][c] == 0; x++, empty[6]++) ;
	for(; x < 15 && aRecordBoard[x][c] == BLACK; x++, jumpsame[6]++) ;
	for(; x < 15 && aRecordBoard[x][c] == 0; x++, jumpempty[6]++) ;
	for(; x < 15 && aRecordBoard[x][c] == BLACK; x++, jumpjumpsame[6]++) ;

	//search rightup 3
	for(x = l-1, y = c+1; x >= 0 && y < 15 && aRecordBoard[x][y] == BLACK; x--, y++, same[3]++) ;
	for(; x >= 0 && y < 15 && aRecordBoard[x][y] == 0; x--, y++, empty[3]++) ;
	for(; x >= 0 && y < 15 && aRecordBoard[x][y] == BLACK; x--, y++, jumpsame[3]++) ;
	for(; x >= 0 && y < 15 && aRecordBoard[x][y] == 0; x--, y++, jumpempty[3]++) ;
	for(; x >= 0 && y < 15 && aRecordBoard[x][y] == BLACK; x--, y++, jumpjumpsame[3]++) ;	

	//search leftdown 
	for(x = l+1, y = c-1; y >= 0 && x < 15 && aRecordBoard[x][y] == BLACK; x++, y--, same[7]++) ;
	for(; y >= 0 && x < 15 && aRecordBoard[x][y] == 0; x++, y--, empty[7]++) ;
	for(; y >= 0 && x < 15 && aRecordBoard[x][y] == BLACK; x++, y--, jumpsame[7]++) ;
	for(; y >= 0 && x < 15 && aRecordBoard[x][y] == 0; x++, y--, jumpempty[7]++) ;
	for(; y >= 0 && x < 15 && aRecordBoard[x][y] == BLACK; x++, y--, jumpjumpsame[7]++) ;	

	aRecordBoard[l][c] = 0 ;
	
	for(i = 0; i < 4; i++)
	{
		if(same[i] + same[i+4] == 4)
			return NO_FORBIDDEN ;
	}

	int threecount = 0, fourcount = 0 ;

	//禁手分析开始
	int isFour ;
	for (i = 0; i < 4; i++)
	{
		if(same[i] + same[i+4] >= 5) // 长连禁手判断
			return LONG_FORBIDDEN ;
		
		else if(same[i] + same[i+4] == 3)  // 如果是下了该棋子之后相连四个棋子
		{
			isFour = 0 ;
			/*如下示意类型中
				e……empty 空
				1……黑棋子
				x……非黑子				
			*/
			if(empty[i] > 0) //  xe1111x
			{
				if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
					isFour = 1 ;
			}
			
			if(empty[i+4] > 0) //  x1111ex
			{
				if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
					isFour = 1 ;
			}

			if(isFour)
				fourcount++ ;//累计成四的个数，如果成四的个数大于二，则形成禁手
		}
		else if(same[i] + same[i+4] == 2)  //如果2个子在当前棋子的附近   形成?111?
		{
			//check 活四，冲四
			if(empty[i] == 1 && jumpsame[i] == 1)// x1e111x
			{
				if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
					fourcount++ ;
			}

			if(empty[i+4] == 1 && jumpsame[i+4] == 1) // x111e1x
			{
				if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
					fourcount++ ;
			}		
		
		int isThree = 0 ;//累计活三的个数，如果个数大于二，则形成禁手

		if((empty[i]>2 || empty[i] == 2 && jumpsame[i] == 0)   //xee111ex 
				&& (empty[i+4] > 1 || empty[i+4] == 1 && jumpsame[i+4] == 0 ))
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
				isThree = 1;
		}

		if((empty[i+4]>2 || empty[i+4] == 2 && jumpsame[i+4] == 0)  //xe111eex
				&& (empty[i] > 1 || empty[i] == 1 && jumpsame[i] == 0 ))
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
				isThree = 1 ;
		}
		
		if(isThree)
			threecount++ ;
	}
	
	else if(same[i]+ same[i+4] ==1)  //相邻有1个棋子  ?11?
	{
		//活四，冲四判断
		if(empty[i] == 1 && jumpsame[i] == 2)	// x11e11x
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
			fourcount++ ;
		}
		if(empty[i+4] == 1 && jumpsame[i+4] == 2) // x11e11x
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
			fourcount++ ;
		}
		//活三判断
		if(empty[i] == 1 && jumpsame[i] == 1 && 
					(jumpempty[i] > 1 || jumpempty[i] == 1 && jumpjumpsame[i] == 0) &&
						(empty[i+4] > 1 || empty [i+4] == 1 && jumpsame[i+4] == 0))	//xe1e11ex
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
				threecount++ ;
		}

		if(empty[i+4] == 1 && jumpsame[i+4] == 1 && 
					(jumpempty[i+4] > 1 || jumpempty[i+4] == 1 && jumpjumpsame[i+4] == 0) &&
						(empty[i] > 1 || empty [i] == 1 && jumpsame[i] == 0)) //xe11e1ex
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
				threecount++ ;
		}
	}
	
	else if(same[i]+same[i+4] ==0)  //单独1个棋子 
	{
		//冲四和活四的判断		
		if(empty[i] == 1 && jumpsame[i] == 3) //x111e1x
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
				fourcount++ ;
		}
		if(empty[i+4] == 1 && jumpsame[i+4] == 3) //x1e111x
		{
			if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
				fourcount++ ;
		}
		
		//活三判断
		if(empty[i] == 1 && jumpsame[i] == 2 && 
					((jumpempty[i] > 1 || jumpempty[i] == 1) && jumpjumpsame[i] == 0) &&
						((empty[i+4] > 1 || empty[i+4] == 1) && jumpsame [i+4] == 0)) //xe11e1ex
				if(pforbiddencheck(aRecordBoard, l, c, same[i], i) == NO_FORBIDDEN)
					threecount++ ;

		if(empty[i+4] == 1 && jumpsame[i+4] == 2 && 
					((jumpempty[i+4] > 1 || jumpempty[i+4] == 1) && jumpjumpsame[i+4] == 0) &&
						((empty[i] > 1 || empty[i] == 1) && jumpsame [i] == 0)) 	//xw1e11ex
				if(pforbiddencheck(aRecordBoard, l, c, same[i+4], i+4) == NO_FORBIDDEN)
					threecount++ ;
	}
}

	//禁手分析结束
	//如果下过该子之后，会形成两个活三，就形成禁手了
	if(fourcount > 1){
		printf("四四禁手,先手输了\n")  ;		
		return FOUR_FOUR_FORBIDDEN ;}
	if(threecount > 1){
		printf("三三禁手,先手输了\n") ;
		return THREE_THREE_FORBIDDEN ;}

	return NO_FORBIDDEN ;
}

//判断构成活三，活四，冲四的关键点是否是禁手点】
//即跳过一样的点之后的空白处是否是禁手点
int pforbiddencheck(int aRecordBoard[15][15], int x, int y ,int same, int dir)
{
	int i, j ;
	same++ ;
	if(dir >= 4)
		same = -same ; //棋盘是对称的，数字代表了方向
	/*  
		1  2  3
		0  x  4
		7  6  5

			(i-1, j-1) 	(i-1, j)  (i-1, j+1)
			
			(i, j-1)      (i, j)  (i, j+1)
			
			(i+1, j-1)  (i+1, j)  (i+1, j+1)
	*/	
	switch(dir % 4) //找出关键点
	{
		case 0 :
			i = x ;
			j = y - same ;
			break ;
		case 1 :
			i = x - same ;
			j = y - same ;
			break ;
		case 2 :
			i = x - same ;
			j = y ;
			break ;
		default :
			i = x - same ;
			j = y + same ;
			break ;
}

	aRecordBoard[i][j] = BLACK ;
	aRecordBoard[x][y] = BLACK ;
	
	int result ;
	result = forbidcheck(aRecordBoard, i, j) ; //调用forbidcheck函数，判断i，j是否是禁手点

	aRecordBoard[i][j] = 0 ;
	aRecordBoard[x][y] = 0 ;		//避免对棋盘的改变

	return result ;
}














