#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2

void initRecordBoard(void); // ��ʼ����¼��������
void initCurrentBoard(void); // ��ʼ����¼�������͵�����
void recordtoDisplayArray(void); // ����������copy��չʾ��Ļ�õ�����
void displayBoard(void); //������չʾ����Ļ��
int error(int x, int y) ; //�ж������Ƿ񵽱߽磬���ظ��䵽�����ӵ�λ�ã� �����жϽ��
int win_judge(int line, int col, int color) ; //�ж�ʤ����ʤ�򷵻�1

struct point{
		int line ;
		int col ;
} ; //����ṹ�����ڼ�¼����λ��
struct point comp(int role, int chess, int aRecordBoard[15][15]) ; //��������ĺ��������ص�������λ��
int forbidcheck(int aRecordBoard[SIZE][SIZE], int l, int c); //�жϽ��ֵĺ����������жϽ��

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//���̻���ģ�� 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = 
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������������ʾ���� 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼���̸��
int aRecordBoard[SIZE][SIZE];
int CurrentBoard[SIZE][SIZE];

int main()
{
	int forbid ;
    int line, col ;
	char s[10] ;
	int role = 0 ; //��¼����ľ���
	int c ;
	int win ; //ʤ�������¼
	int end ;
	int first ; //���ѡ���Ƿ����ּ�¼
	initRecordBoard();
	initCurrentBoard();
   	recordtoDisplayArray();

	displayBoard(); 
	printf("work of ������\n") ;
	printf("������ʼ���������\n") ;
	printf("people first?Yes,1;No,0\t") ;
	scanf("%d", &first) ;
	if(first == 1)  //��������
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
			getchar() ; //��ȡ�û����������λ��
			for(;error(col, line) == 0;)
			{ 
				col = getchar()-'A' ;
				getchar() ;
				scanf("%s",s) ;
				line = 15 - atof(s) ;
				getchar() ;
			} //ѭ��ֱ������淶��ֹͣ
			//���˵Ľ����ж�
			forbid =  forbidcheck(aRecordBoard, line, col) ;
			if(forbid != 0){
			printf("forbidden move! player2 ,the computer wins the game\n") ;
			return 0 ;}	
    		aRecordBoard[line][col]=1; 
			CurrentBoard[line][col]=3;
    		recordtoDisplayArray();
			printf("\n") ;
    		displayBoard();
			win = win_judge(line,col,1) ; //�ж�ʤ��
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
			
			//�����ӽ��������Կ�ʼ����
			struct point pt ;
			printf("PLAYER 2 : the computer:\n") ; //player2 WHITE ��������
			pt = comp(role, 2, aRecordBoard) ; //����˼�������ӣ����ص���������
			line = pt.line ;
			col = pt.col ;

			aRecordBoard[line][col]=2;
			CurrentBoard[line][col]=4;
    		recordtoDisplayArray();
			displayBoard();
			printf("computer move: %c, %d\n", 'A'+col, 15-line) ; //�����������λ��

			win = win_judge(line,col,2) ; //�ж�ʤ��
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
	if(first == 0) //��������
	{		
		for(role = 1; (c = getchar()) != 'Q'; role ++)
		{
			printf("Role: %d\n", role) ;
			struct point pt ; //���ڼ�¼��������λ��
			printf("PLAYER 1 : the computer:\n") ; //player1 BLACK
			pt = comp(role, 1, aRecordBoard) ;
			line = pt.line ;
			col = pt.col ;
			aRecordBoard[line][col]=1;
			CurrentBoard[line][col]=3;
    		recordtoDisplayArray();
			displayBoard();
			printf("computer move: %c, %d\n", 'A'+col, 15-line) ;

			win = win_judge(line,col,1) ;//�ж�ʤ��
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

			//�������ӽ����������ȡ�˵ľ���
			printf("PLAYER 2 : please input the position with the format of A,1:") ; //player 2 WHITE
			col = getchar() ;
			if(col == 'Q')
				break ;
			col = col -'A' ;
			getchar() ;
			scanf("%s",s) ;
			line = 15 - atof(s) ; //��ȡ���
			getchar() ;
			for(;error(col, line) == 0;)
			{ 
				col = getchar()-'A' ;
				getchar() ;
				scanf("%s",s) ;
				line = 15 - atof(s) ;
				getchar() ;
			} //ѭ��ֱ������淶��ֹͣ
		 
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

//��ʼ�����̸�� 
void initRecordBoard(void){
//ͨ��˫��ѭ������aRecordBoard��0
	int i, j ;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			aRecordBoard[i][j] = 0 ;
}

void initCurrentBoard(void){
//ͨ��˫��ѭ������CurrentBoard��0
	int i, j ;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			CurrentBoard[i][j] = 0 ;
}

int error(int x, int y){
//�ж������Ƿ�Υ��
//Υ������0����Υ������0
	if(x < 15 && x >= 0 && y < 15 && y >= 0 && aRecordBoard[y][x] == 0)
		return 1 ;
	else{
		printf("Please re-input: ") ;
		return 0 ;
	}
}
//��aRecordBoard�м�¼������λ�ã�ת����aDisplayBoardArray��
void recordtoDisplayArray(void)
{
	int i, j ;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE*CHARSIZE+1; j++)
		{
			aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j] ;
		}//��һ������aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��
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
		}				//�ڶ�����ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����
//ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
}


//��ʾ���̸�� 
void displayBoard(void){
	int i;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������aDisplayBoardArray�������Ļ��
	for(i = 0; i < SIZE; i++)
		printf("%3d %s\n", SIZE-i, aDisplayBoardArray[i]) ;
		
	//������������������һ����ĸA B .... 
	printf("    ") ;
	for(i = 0; i < SIZE; i++) 
		printf("%2c", 'A' + i) ;
	printf("\n") ;
} 

int win_judge(int line, int col, int color)
{
//�ж�ʤ���ĺ���
	//line judge
	int i = 1 ; //ָ������
	int count = 1 ; //��¼��ͬ����
	//ÿ�λ�����Ҫ��count��i��ʼ��
	while(i<5 && aRecordBoard[line][col-i] == color && col-i >= 0)
		i++, count++ ;
	 i = 1 ;
	while(i<5 && aRecordBoard[line][col+i] == color && col+i < 15)
		i++, count++ ;
	if(count == 5) //����������ʤ��
		return 1 ;
	//column judge
	count = 1 ;//ÿ�λ�����Ҫ��count��i��ʼ��
	 i = 1 ;
	while(i<5 && aRecordBoard[line-i][col] == color && line-i >= 0)
		i++, count++ ;
	i = 1 ;
	while(i<5 && aRecordBoard[line+i][col] == color && line+i < 15)
		i++, count++ ;
	if(count == 5)//����������ʤ��
		return 1 ;
	//cross\ judge
	count = 1 ;//ÿ�λ�����Ҫ��count��i��ʼ��
	 i = 1 ;
	while(i<5 && aRecordBoard[line-i][col-i] == color && col-i >= 0 && line-i >= 0)
		i++, count++ ;
	i = 1 ;
	while(i<5 && aRecordBoard[line+i][col+i] == color && col+i < 15 && line+i < 15)
		i++, count++ ;
	if(count == 5)//����������ʤ��
		return 1 ;
	//cross\ judge
	count = 1 ;//ÿ�λ�����Ҫ��count��i��ʼ��
	i = 1 ;
	while(i<5 && aRecordBoard[line-i][col+i] == color && line-i >= 0 && col+i < 15)
		i++, count++ ;
	 i = 1 ;
	while(i<5 && aRecordBoard[line+i][col-i] == color && line+i < 15 && col-i >= 0)
		i++, count++ ;
	if(count == 5)//����������ʤ��
		return 1 ;
	return 0 ;
}


