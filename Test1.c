 //编程思想总结
 strncpy(output + output_col,input + columns[col],nchars);
 printf("hello world!\n");
 
 printf("i = %d\n",j);
 
 scanf("%d\n",&i);
 printf("%d\n",i);
 
typedef char *ptro_to_char;     //把标志符ptr_to_char 作为指向字符类型的新名字

int const a;
int const *pci;		//定义一个指向整型常量的指针
int * const cpi;	//定义一个指向整型的常量指针

switch(expression)
{
	case():
		break;
	case():
		break;
	default;
}

//位操作符 -- 将制定的位设置为1
value = value | 1 << bit_number;
// 将指定位置0
value = value & ~ (1 << bit_number);
//逻辑运算符
a >5 && a<10     //&&操作符的优先级比><操作符的优先级都要低
//条件操作符
 a > 5 ? 1:0;
//左值和右	--  左值可以作为右值，右值不能作为左值
//优先级和求值的顺序

#include <stdio.h>
void main()
{
	char buffer1[100] = {0};
	printf("请任意输入一串字符!\n");
}

//递归调用
long factorial(int n)
{
	if(n<=0)
		return 1;
	else
		return n*factorial(n-1);
}


#include <reg51.h>
sbit P10 = P1^0;
sbit P11 = P1^1;

void delay(unsigned int t)
{
	unsigned int i;
	for(i=0;i<t;i++);
}

main(void)
{
	while(1)
	{
		P10 = 0;		//阶段一
		P11 = 0;
		delay(749);
		
		P10 = 1;		//阶段二
		P11 = 0;
		delay(251);
		
		P10 = 0;		//阶段三
		P11 = 0;
		delay(749);
		
		P10 = 1;		//阶段四
		P11 = 1;
		delay(251);
	}
}


void delay(unsigned char d,unsigned int t)
{
	unsigned int i;
	P1 = P1 & 0xF0 | d;				//一次简化
	for(i=0;i<t;i++);
}

main(void)
{
	while(1)
	{
		delay(0x00,749);			//二次简化
		delay(0x01,251);
	}
}

//数据驱动程序
#define STAGES 16
unsigned char code P1_1234 = {0,1,0,3,0,1,0,7,0,1,0,3,0,1,0,15};
unsigned int code Dts[] = {749,251,749,251,749,251,749,251,749,251,749,251};

void delay(unsigned char d,unsigned int t)
{
	unsigned int i;
	P1 = P1 & 0xF0 | d;
	for(i=0;i<t;i++);
}

main(void)
{
	int i;
	while(1)
	{
		for(i=0;i<STAGES;i++)			//三次简化
			delay(P1_1234[i],Dts[i]);
	}
}

typedef struct _script					//四次简化 -- 规范播放器
{
	unsigned char d;
	unsigned int t;
}Script;

void play(unsigned char progress)
{
	unsigned int i;
	P1 = P1 & oxF0 | FourPluse[progress].d;
	for(i=0;i<FourPluse[progress].t;i++);
}

main (void)
{
	int i;
	while(1)
	{
		for(i=0;i<STAGES;i++);
		play(i);
	}
}

//多任务编程
#include <reg51.h>
//定义端口口线
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P20 = P2^0;
sbit P21 = P2^1;

//定义脚本内容
#define STAGES		16
#define STEPTIME	250

//定义延时时间
#define T_10MS		10000

//定义取按键宏
#define KEYS()		(~P1 & 0xF0)

//定义LED宏
#define LED1ON()	P20 = 0;
#define LED1OFF()	P20 = 1;
#define LED2ON()	P21 = 0;
#define LED2OFF()	P21 = 1;

//定义按键
unsigned char bdata keys;
sbit k_led1on		= keys^4;
sbit k_led1shine3	= keys^5;
sbit k_led2on		= keys^6;
sbit k_led2shine5	= keys^7;

//延时函数
void delay(unsigned int t)
{
	unsigned int i;
	for(i=0;i<t;i++);
}

//演播脚本的演播器
void play(unsigned char progress)
{
	P1 = P1 & 0xF0 | progress;
	delay(STEPTIME);
}

//LED1闪烁
void LED1Shine(unsigned char t)
{
	while(t--)
	{
		LED1ON()
		delay(8000);
		LED1OFF();
		delay(39877);
	}
}

//LED2闪烁
void LED2Shine(unsigned char t)
{
	while(t--)
	{
		LED2ON();
		delay(8000);
		LED2OFF();
		delay(25785);
	}
}

void main(void)
{
	unsigned char i;
	unsigned char stage = 0;
	P1 = 0xFF;
	while(1)
	{
		/*
		for(i=0;i<STAGES;i++)	//任务一实现
			play(i);
		*/
		play(stage);	
		stage++;
		if(stage>=STAGES)stage = 0;
		
		keys = KEYS();			//任务二：检查键盘动作
		if(keys)
		{
			delay(T_10ms);
			keys &= KEYS();
			if(keys)
			{
				if(k_led1on)
					LED1ON();
				if(k_led1shine3)
					LED1Shine(3);
				if(k_led2on)
					LED2ON();
				if(k_led2shine5)
					LED2Shine(5);
			}
		}
		P1 |= 0xF0;
	}
}

#include <stdlib.h>
const unsigned char code a1 = 9;
const unsigned char code b1 = 7;
const unsigned char code c1 = 18;

const unsigned char code a2 = 4;
const unsigned char code b2 = 13;
const unsigned char code c2 = 6;

main(void)
{
	//OS变量定义区   --   线程任务
	bit isTask_1_Living = 1;
	unsigned char Task1_Thread_Process = 0;
	//任务2OS变量
	bit isTask_2_Living = 1;
	unsigned char Task2_Thread_Process = 0;
	//任务1用户变量
	unsigned int x1;
	unsigned long y1;
	//任务2用户变量
	unsigned int x2;
	unsigned long y2;
	//自由变量区，此变量可被多任务使用
	unsigned int z;
	
	while(1)
	{
		if(isTask_1_Living)		//并行多任务执行
		{
			switch(Task1_Thread_Process)
			{
				case 0:
					x = rand();
					y = 3;
					break;
				case 1:
					y *=x;
					y *=x;
					break;
				case 2:
					z = 7;
					z *= a;
					break;
				case 3:
					z *= b;
					z *= x;
					break;
				case 4:
					y += z;
					y += c;
					isTask_1_Living = 0;	//让任务1die
			}
			Task1_Thread_Process++;
			if(Task1_Thread_Process>4) Task1_Thread_Process = 0;
		}
		
		if(isTask_2_Living)		//并行多任务执行
		{
			switch(Task2_Thread_Process)
			{
				case 0:
					x2 = rand();
					y2 = 3;
					break;
				case 1:
					y2*=x2;
					y2 *=x2;
					break;
				case 2:
					z2 = 7;
					z2 *= a2;
					break;
				case 3:
					z2 *= b2;
					z2 *= x2;
					break;
				case 4:
					y2 += z2;
					y2 += c2;
					isTask_2_Living = 0;	//让任务1die
			}
			Task2_Thread_Process++;
			if(Task2_Thread_Process>4) Task2_Thread_Process = 0;
		}
	}
}


//并行多任务多线程的数据与代码分离
//任务数据类型
typedef struct _myTask
{
	struct _coefficient
	{
		unsigned char a;
		unsigned char b;
		unsigned char c;
	}co;
	
	struct _variable
	{
		unsigned int x;
		unsigned long y;
	}v;
}myTask;
// 线程状态标记

#define THREAD_OVER   -1   //线程结束
#define THREAD_NOTOVER 0   //线程未结束

//线程函数
char myThread(myTask task,unsigned char *Process)
{
	unsigned int z;
	char ret = 0;
	switch(*Process)
	{
		case 0:
			Task.v.x = rand();	//取随机数
			Task.v.y = 3;
			break;
		case 1:
			Task.v.y *= Task.v.x;
			Task.v.y *= Task.v.x;
			break;
		case 2:
			z = 7;
			z *= Task.co.a;
			break;
		case 3:
			z *= Task.co.b;
			z *= Task.v.x;
			break;
		case 4:
			Task.v.y += z;
			Task.v.y +=Task.co.c;
	}
	(*Process)++;
	if(*Process > 4)
	{
		ret = -1;
		*Process = 0;
	}
	return ret;
}

//定义任务
myTask Task1,Task2;

//任务初始化
void InitTask(myTask Task,unsigned char a,unsigned char b,unsigned char c)
{
	Task.co.a = a;
	Task.co.b = b;
	Task.co.c = c;
}

main(void)
{
	//OS变量定义区   --   线程任务
	bit isTask_1_Living = 1;
	unsigned char Task1_Thread_Process = 0;
	//任务2OS变量
	bit isTask_2_Living = 1;
	unsigned char Task2_Thread_Process = 0;
	
	InitTask(Task1,9,7,19);
	InitTask(Task2,4,13,16);
	
	while(1)
	{
		if(isTask_1_Living)
		{
			isTask_1_Living = !myThread(Task1,&Task1_Thread_Process);
		}
		if(isTask_2_Living)
		{
			isTask_2_Living = !myThread(Task2,&Task1_Thread_Process);
		}
	}
}

//定时器与延时器
#include <reg51.h>
#include <intrins.h>

#define ST_0_5S		2500
#define ST_1S		5000

bit SoftTimer0Enable;
unsigned SoftTimer0Counter = 0;
bit SoftTimer0Over = 0;

main(void)
{
	TMOD = 0x02;	//定时器0工作于方式2
	TH0 = TL0 = 0x38;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
	
	SoftTimer0Counter = ST_0_5S;
	SoftTimer0Enable = 1;
	
	while(1)
	{
		if(_testbit_(SoftTimer0Over))
		{
			SoftTimer0Counter = ST_0_5S;
			P2 = ~P2;
		}
	}
}

void TimeBaseByTimer0(void)	interrupt 1
{
	if(SoftTimer0Enable)
	{
		if(SoftTimer0Counter)
		{
			SoftTimer0Counter--;
			if(!SoftTimer0Counter) SoftTimer0Over = 1;
		}
	}
}

//延时器
#include <reg51.h>

//定义时间常数
#define ST_0_5S		92601
#define ST_1S		185201

//定义延时器
bit Delay0Open = 0;
unsigned long Delay0Counter = 0;
bit Delay0Over = 0;

main(void)
{
	//初始化并打开延时器
	Delay0Counter = ST_0_5S;
	Delay0Open = 1;
	while(1)
	{
		if(Delay0Open)
		{
			if(Delay0Counter)
			{
				Delay0Counter--;
				if(!Delay0Counter) Delay0Over = 1;
			}
		}
		if(_testbit_(Delay0Over))
		{
			Delay0Counter = ST_0_5S;
			P2 = ~P2;
		}
	}
}

//消息处理 
//小规模的消息处理中，使用不同的变量来收发不同类型的消息
#include <stdlib.h>
//定义消息
#define MSG_TASK1_RUN		1
#define MSG_TASK1_STOP		2
#define MSG_TASK2_RUN		1
#define MSG_TASK2_STOP		2

main(void)
{
	unsigned RandTaskGennel;
	unsigned char message1;
	unsigned RandTaskGenne2;
	unsigned char message2;
	
	while(1)
	{
		RandTaskGennel = rand();
		RandTaskGennel %= 2;
		if(RandTaskGennel)
		{
			message1 = MSG_TASK1_RUN;	//产生消息
		}
		else
		{
			message1 = MSG_TASK1_STOP;	//产生消息
		}
		
		RandTaskGenne2 = rand();
		if(RandTaskGenne2>1000)
		{
			message2 = MSG_TASK2_RUN;	//产生消息 
		}
		else
		{
			message2 = MSG_TASK2_STOP;	//产生消息
		}
		
		if(message1)	//消息检索
		{
			switch(message1)
			{
				case MSG_TASK1_RUN:
				//任务1运行处理
				break;
				case MSG_TASK1_STOP:
				//任务1停止处理
				break;
			}
		}
		
		if(message2)	//消息检索
		{
			switch(message2)
			{
				case MSG_TASK2_RUN:
				//任务2运行处理
				break;
				case MSG_TASK2_STOP:
				//任务2停止处理
				break;
			}
		}
	}
}

//大规模消息种类时，需要用到另一种消息收发检索策略 -- 消息队列
#include <stdlib.h>
typedef unsigned char message;
//定义消息
#define MSG_NONE			0	//无消息的消息
#define MSG_TASK1_RUN		1
#define MSG_TASK1_STOP		2
#define MSG_TASK2_RUN		3
#define MSG_TASK2_STOP		4

/* 消息处理机制定义 */
#define QUEUELEN			5		//消息队列缓冲区大小
unsigned char Messages[QUEUELEN];	//消息队列缓冲区
unsigned char MessageHead = 0;		//消息队列列头 
unsigned char MessageTail = 0;		//消息队列列尾

/* 队列处理函数 */
/* 消息发布 */
void PutMessage(message m)
{
	Message[MessageTail] = m;
	if(++MessageTail>=QUEUELEN) MessageTail = 0;
}

/* 消息检索 */
message GetMessage(void)
{
	message m = Messaegs[MessageHead];
	if(++MessageHead>=QUEUELEN) MessageHead = 0;
	return m;
}

/*判断队列是否为空*/
bit QueueEmptOrError(void)
{
	return (MessageHead == MessageTail)?1:0;
}

main(void)
{
	unsigned RandTaskGene;
	while(1)
	{
		RandTaskGennel = rand();
		RandTaskGennel %= 2;
		if(RandTaskGennel)
		{
			PutMessage(MSG_TASK1_RUN);	//产生消息
		}
		else
		{
			PutMessage(MSG_TASK1_STOP);		//产生消息
		}
		
		RandTaskGenne2 = rand();
		if(RandTaskGenne2>3000)
		{
			PutMessage(MSG_TASK2_RUN);		//产生消息 
		}
		else
		{
			PutMessage(MSG_TASK2_STOP);		//产生消息
		}
		
		while(!QueueEmptOrError)		//一次性消息检索
		{
			switch(GetMessage())
			{
				case MSG_TASK1_RUN:
				//任务1运行处理
				break;
				case MSG_TASK1_STOP:
				//任务1停止处理
				break;
				case MSG_TASK2_RUN:
				//任务2运行处理
				break;
				case MSG_TASK2_STOP:
				//任务2停止处理
				break;
			}
		}
	}
}

//广播消息 ------------------
#include <stdlib.h>
typedef unsigned char message;
//定义消息
#define MSG_NONE			0	//无消息的消息
#define MSG_TASK1_RUN		1
#define MSG_TASK1_STOP		2
#define MSG_TASK2_RUN		3
#define MSG_TASK2_STOP		4

/* 消息处理机制定义 */
#define QUEUELEN			5		//消息队列缓冲区大小
unsigned char Messages[QUEUELEN];	//消息队列缓冲区
unsigned char MessageHead = 0;		//消息队列列头 
unsigned char MessageTail = 0;		//消息队列列尾

/* 队列处理函数 */
/* 消息发布 */
void PutMessage(message m)
{
	Message[MessageTail] = m;
	if(++MessageTail>=QUEUELEN) MessageTail = 0;
}

/* 消息检索 */
message GetMessage(void)
{
	message m = Messaegs[MessageHead];
	if(++MessageHead>=QUEUELEN) MessageHead = 0;
	return m;
}

/*判断队列是否为空*/
bit QueueEmptOrError(void)
{
	return (MessageHead == MessageTail)?1:0;
}

#define BroadCase(m)	PutMessage(m)	//广播第一条消息
#define AMessage()		Messages[MessageHead]	//获取第一条消息
#define DelMessage		GetMEessage()	//删除第一条消息
/*休闲俱乐部事物定义*/
void Club_Recreation(message m)
{
	switch(m)
	{
		case MSG_SING:
			//唱歌
			break;
		case MSG_DANCE:
			//跳舞
			break;
		case MSG_PLAYTHEPIANO:
			//弹钢琴
			break;
		case MSG_GOTOGAME:
			//参赛
			break;
		case MSG_ATTENDMEETING:
			//参加会议
			break;
	}
}
/*体育俱乐部*/
void Club_Sport(message m)
{
	switch(m)
	{
		case MSG_PLAYFOOTBAL:
			//足球
			break;
		case MSG_PLAYBASKETBAL:
			//篮球
			break;
		case MSG_GOTOGAME:
			//参赛
			break;
		case MSG_ATTENDMEETING:
			//会议
			break;
	}
}

main(void)
{
	unsigned RandTaskGene;
	while(1)
	{
		RandTaskGennel = rand();
		RandTaskGennel %= 2;
		if(RandTaskGennel)
		{
			BroadCase(MSG_SING);	//产生消息
		}
		else
		{
			BroadCase(MSG_GOTOGAME);		//产生消息
		}
		
		RandTaskGenne2 = rand();
		if(RandTaskGenne2>3000)
		{
			BroadCase(MSG_PLAYBASKETBAL);		//产生消息 
		}
		else
		{
			BroadCase(MSG_ATTENDMEETING);		//产生消息
		}
		
		while(!QueueEmptOrError)		//一次性消息检索
		{
			Club_Recreation(AMessage());//娱乐俱乐部检索消息
			Club_Sport(AMessage());		//体育俱乐部检索消息
			DelMessage();				//检索完毕，删除消息
		}
	}
}


//多任务+消息机智+任务嵌套 
#include <reg51.h>
//定义端口口线
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P20 = P2^0;
sbit P21 = P2^1;

typedef unsigned char message;
//定义消息
#define MSG_LED1SHINE3		3
#define MSG_LED2SHINE5		5

//定义脚本内容
#define STAGES		16
#define STEPTIME	250

//定义延时时间
#define T_10MS		10000

//定义取按键宏
#define KEYS()		(~P1 & 0xF0)

//定义LED宏
#define LED1ON()	P20 = 0;
#define LED1OFF()	P20 = 1;
#define LED2ON()	P21 = 0;
#define LED2OFF()	P21 = 1;

//定义按键
unsigned char bdata keys;
sbit k_led1on		= keys^4;
sbit k_led1shine3	= keys^5;
sbit k_led2on		= keys^6;
sbit k_led2shine5	= keys^7;

//延时函数
unsigned Delay0Counter = 1;
unsigned Delay1Counter = 0;
unsigned Delay2Counter = 0;
unsigned Delay3Counter = 0;

//演播脚本的演播器
void play(unsigned char progress)
{
	P1 = P1 & 0xF0 | progress;
}

void main(void)
{
	unsigned char i;
	unsigned char stage = 0;
	unsigned char led1shinetimes = 0;
	unsigned char led2shinetimes = 0;
		
	P1 = 0xFF;
	
	while(1)
	{
		if(Delay0Counter)
		{
			Delay0Counter--;
			if(!Delay0Counter)
			{
				play(stage);	//任务一的实现
				Delay0Counter = STEMPTIME;
				stage++;
				if(stage>=STAGES) stage = 0;
			}
		}
		
		if(!Delay1Counter)
		{
			keys = KEYS();
			if(keys)
			{
				Delay0Counter = T_10ms;
			}
		}
		else
		{
			Delay1Counter--;
			if(!Delay1Counter)
			{
				keys &= KEYS();
				if(keys)
				{
					if(k_led1on)	
						LED1ON();
					if(k_led1shine3)
					{
						LED1OFF();
						Delay2Counter = T_10ms;
						led1shinetimes = MSG_LED1SHINE3;
					}
					if(k_led2on)
					{
						LED2ON();
					}
					if(k_led1shine5)
					{
						LED2OFF();
						Delay3Counter = T_10ms;
						led2shinetimes = MSG_LED2SHINE5;
					}
				}
			}
		}
		P1 |= 0xF0;
	}
}

//面向对象编程
typedef struct _TRabbit
{
	const unsigned food;
}TRabbit;

//定义颜色
#define CL_BLACK		0
#define CL_WHITE		1
#define CL_GRAY			2

//定义物种身份ID
#define ID_GRASS				0x0001
#define ID_CARROT				0x0002
#define ID_GREENVEGETABLE		0x0004
#define ID_RABBIT				0x0010
#define ID_FISH					0x0020
#define ID_WOLF					0x0100

#define NIL				0

//定义函数指针
typedef bit (*teat)(unsigned food);
typedef void(*trun)(void);

//兔子类
typedef struct _TRabbit
{
	const unsigned food;
	const unsigned enemy;
	unsigned char color;
	float weight;
	unsigned char age;
	teat Eat;
	trun Run;
}TRabbit;

bit rabbitEat(unsigned food)
{
	return (food & 0x0007);
}

void rabbitRun(void)
{
	//可以蹦，跳，跑
}

main (void)
{
	//创建兔子
	TRabbit Rabbit1 = {0x0007,0x0100,CL_WHITE,1.03,3,rabbitEat,rabbitRun};
	TRabbit Rabbit2 = {0x0007,0x0100,CL_GRAY,1.23,4,rabbitEat,rabbitRun};
	Rabbit1.Eat(ID_CARROT);
	Rabbit2.Run();
	while(1)
	{
		
	}
}

//面向对象升级版
#define class(c)		struct c
//定义函数指针
typedef bit (*teat)(unsigned food);
typedef void(*trun)(void);
//兔子类
class(TRabbit)
{
	const unsigned food;
	const unsigned enemy;
	unsigned char color;
	float weight;
	unsigned char age;
	teat Eat;
	trun Run;
};

#define object(c,o)		struct c o

//创建兔子
object(TRabbit,Rabbit1) = {0x0007,0x0100,CL_WHITE,1.03,3,rabbitEat,rabbitRun};
object(TRabbit,Rabbit2) = {0x0007,0x0100,CL_GRAY,1.23,4,rabbitEat,rabbitRun};

//用函数替代原来的const成员
typedef unsigned (*species)(void);

#define create(m,o)		m(o)

//分类标识符
#define Const
#define Variable
#define Method

//兔子类
class(TRabbit)
{
	Const	
		species id;
		species food;
		species enemy;
	Variable
		unsigned char color;
		float weight;
		unsigned char age;
	Method	
		teat Eat;
		trun Run;
}

//类的空间申请
object(TRabbit,Rabbit1);
object(TRabbit,Rabbit2);

//类的常量函数与类的创建
unsigned rabbitId(void)
{
	return ID_RABBIT;
}

unsigned rabbitFood(void)
{
	return ID_GRASS|ID_CARROT|ID_GREENVEGETABLE;
}

unsigned rabbitEnemy(void)
{
	return ID_WOLF;
}

void rabbitCreate(object(TRabbit,obj))
{
	obj.id = rabbitId;
	obj.food = rabbitFood;
	obj.enemy = rabbitEnemy;
	obj.Eat = rabbitEat;
	obj.Run = rabbitRun;
}

create(rabbitCreate,Rabbit1);
Rabbit1.color = CL_WHITE;
Rabbit1.weight = 1.03;
Rabbit1.age = 3;
create(rabbitCreate,Rabbit2);
Rabbit2.color = CL_GRAY;
Rabbit2.weight = 1.23;
Rabbit2.age = 4;


//最终实现
#include <reg51.h>

//分类标识符
#define Const
#define Variable
#define Method

#define object(c,o)		struct c o

#define class(c)		struct c

#define create(m,o)		m(o)

//定义颜色
#define CL_BLACK		0
#define CL_WHITE		1
#define CL_GRAY			2

//定义物种身份ID
#define ID_GRASS				0x0001
#define ID_CARROT				0x0002
#define ID_GREENVEGETABLE		0x0004
#define ID_RABBIT				0x0010
#define ID_FISH					0x0020
#define ID_WOLF					0x0100

#define NIL				0

//定义函数指针
typedef bit (*teat)(unsigned food);
typedef void(*trun)(void);
typedef unsigned (*species)(void);
//兔子类
class(TRabbit)
{
	Const	
		species id;
		species food;
		species enemy;
	Variable
		unsigned char color;
		float weight;
		unsigned char age;
	Method	
		teat Eat;
		trun Run;
}

//类的常量函数与类的创建
unsigned rabbitId(void)
{
	return ID_RABBIT;
}

unsigned rabbitFood(void)
{
	return ID_GRASS|ID_CARROT|ID_GREENVEGETABLE;
}

unsigned rabbitEnemy(void)
{
	return ID_WOLF;
}

bit rabbitEat(unsigned food)
{
	return (food & 0x0007);
}

void rabbitRun(void)
{
	//可以蹦，跳，跑
}

void rabbitCreate(object(TRabbit,obj))
{
	obj.id = rabbitId;
	obj.food = rabbitFood;
	obj.enemy = rabbitEnemy;
	obj.Eat = rabbitEat;
	obj.Run = rabbitRun;
}

main(void)
{
	object(TRabbit,Rabbit1);
	object(TRabbit,Rabbit2);
	
	create(rabbitCreate,Rabbit1);
	Rabbit1.color = CL_WHITE;
	Rabbit1.weight = 1.03;
	Rabbit1.age = 3;
	
	create(rabbitCreate,Rabbit2);
	Rabbit2.color = CL_GRAY;
	Rabbit2.weight = 1.23;
	Rabbit2.age = 4;
	
	Rabbit1.Eat(ID_CARROT);
	Rabbit2.Run();
	
	while(1)
	{
		
	}
}

//例二
class(TWave)
{
	Const	
		waveid Id;
		delayconst BaseDelayTime;
	Variable
		unsigned char code *BaseWave;  //基波数组指针
		char PlayState;
		int BwqProgress;	//基波播放进度
		...
	Method
		tplay play;
		tstop stop;
		tpause pause;
		trun run;
}

//对象的归宿
//鸟类的设计
class(_TBird)
{
	Const
	Variable
	Method
		taction look;
		taction fly;
		taction swing;
		taction run;
};
//鸟类的行为
typedef void(*taction)(void);

typedef class(_TBird) TBird;
typedef TBird *PBird;

extern void birdCreate(PBird obj,bit CanLock,bit CanFly,bit CanSwing,bit CanRun);

//编程思想总结 -- 硬件层，接口层，协议层，应用层
//编程规范+代码架构+代码质量 构成稳定的产品
//嵌入式系统的基本架构 

/*编程模式*/
/*工厂模式*/
class Program
{
	static void Main(string[] args)
	{
		Console.Write("请输入数字A：");
		string strNmuberA = Console.ReadLine;
		Console("请输入运算符(+、-、*、/)：");
		string strOperate = Console.ReadLine();
		Console.Write("请输入数字B：");
		string strNmuberB = Console.ReadLine();
		String strResult = "";
		
		switch(strOperate)
		{
			case"+":
				strResult = Convert.ToString(Convert.ToDouble(strNmuberA))+
				Convert.ToDouble(strNmuberB);
				break;
			case"-":
				strResult = Convert.ToString(Convert.ToDouble(strNmuberA))-
				Convert.ToDouble(strNmuberB);
				break;
			case"*":
				strResult = Convert.ToString(Convert.ToDouble(strNmuberA))*
				Convert.ToDouble(strNmuberB);
				break;
			case"/":
				if(strNmuberB !=0)
				strResult = Convert.ToString(Convert.ToDouble(strNmuberA))/
				Convert.ToDouble(strNmuberB);
				
				else
					strResult = "除数不能为0";
				break;
		}
		Console.WriteLine("结果是：" + strResult);
		Console.ReadLine();
	}
	catch(Exception ex)
	{
		Console.WriteLine("您的输入有错："+ ex.Message);
	}
}

//业务的封装
public class Operation
{
	public static double GetResult(double numberA,double numberB,string opreate)
	{
		double result = 0d;
		switch(opreate)
		{
			case "+":
				result = numberA + numberB;
				break;
			case "-":
				result = numberA - numberB;
				break;
			case "*":
				result = numberA * numberB;
				break;
			case "/":
				result = numberA / numberB;
				break;
		}
		return result;
	}
}

static void Main(string[] args)
{
	try
	{
		Console.Write("请输入数字A：");
		string strNmuberA = Console.ReadLine;
		Console("请输入运算符(+、-、*、/)：");
		string strOperate = Console.ReadLine();
		Console.Write("请输入数字B：");
		string strNmuberB = Console.ReadLine();
		String strResult = "";
		strResult = Convert.ToString(Operation.GetResult(Convert.ToDouble(strNmuberA),
		Convert.ToDouble(strNmuberB),strOperate));
		Console.WriteLine("结果是："+ strResult);
		Console.ReadLine();
	}
	catch(Exception ex)
	{
		Console.WriteLine("您的输入有错："+ ex.Messaeg);
	}
}

//高内聚低耦合 -- 继承+多态
public class Operation
{
	private double _numberA = 0;
	private double _numberB = 0;
	
	public double NumberA
	{
		get { return _numberA;}
		set { _numberA = value;};
	}
	
	public double NumberB
	{
		get { return _numberB;}
		set { _numberA = value;};
	}
	//虚方法，继承后重写部分
	public virtual double GetResult()
	{
		double result = 0;
		return result;
	}
}

class OperationAdd : Operation
{
	public override double GetResult()
	{
		double result = 0;
		result = NumberA + NumberB;
		return result;
	}
}

class OperationSub : Operation
{
	public override double GetResult()
	{
		double result = 0;
		result = NumberA + NumberB;
		return result;
	}
}

class OperationSub : Operation
{
	public override double GetResult()
	{
		double result = 0;
		result = NumberA * NumberB;
		return result;
	}
}

class OperationSub : Operation
{
	public override double GetResult()
	{
		double result = 0;
		if(NumberB==0)
			throw new Exception("除数不能为0");
		result = NumberA / NumberB;
		return result;
	}
}

//简单工厂模式  --  通过多态返回父类的方式实现计算器的结果。
public class OperationFactory
{
	public static Operation createOperate(string operate)
	{
		Operation oper = null;
		switch(operate)
		{
			case "+":
			oper = new OperationAdd();
			break;
			case "-":
			oper = new OperationSub();
			break;
			case "*":
			oper = new OperationMul();
			break;
			case "/":
			oper = new OperationDiv();
			break;
		}
		return oper;
	}
}

Operation oper;
oper = OperationFactory.createOperate("+");
oper.NumberA = 1;
oper.NumberB = 2;
double result = oper.GetResult();

//商场促销--策略模式
double total = 0.0d;
private void btn0k_Click(object sender,EventArgs e)
{
	double totalPrices = Convert.ToDouble(txtPrice.Text)*Convert.ToDouble(txtNum.Text);
	total = total + totalPrices;
	
	lbxList.Items.Add("单价："+txtPrice.Txtt+"数量："+txtNum.Text"合计："+totalPrices.ToString());
	
	lblResult.Text = total.ToString();
}

double total = 0.0d;
private void Form1_Load(object sender,EventArgs e)
{
	cbxType.Items.AddRange(new object[]{"正常收费"，"打八折","打七折","打五折"});
	cbxType.SelectedIndex = 0;
}

private void btnOk_Click(object sender,EventArgs e)
{
	double totalPrices = 0d;
	switch(cbxType.SelectedIndex)
	{
		case 0:
			totalPrices = Convert.ToDouble(txtPrice.Text)*Convert.ToDouble(txtNum.Text);
			break;
		case 1:
			totalPrices = Convert.ToDouble(txtPrice.Text)*Convert.ToDouble(txtNum.Text)*0.8;
			break;
		case 2:
			totalPrices = Convert.ToDouble(txtPrice.Text)*Convert.ToDouble(txtNum.Text)*0.7;
			break;
		case 3:
			totalPrices = Convert.ToDouble(txtPrice.Text)*Convert.ToDouble(txtNum.Text)*0.5;
			break;
	}
	total = total + totalPrices;
	lbxList.Items.Add("单价："+txtPrice.Txtt+"数量："+txtNum.Text + " "+cbxType.SelectedItem + "合计："+totalPrices.ToString());
	lblResult.Text = total.ToString();
}

//现金收费抽象类
abstruct class CashSuper
{
	public abstruct double acceptCash(double money);
}

//正常收费子类
class CashNormal : CashSuper
{
	public override double acceptCash(double money);
	{
		return money;
	}
}

//打折收费子类
class CashRebate : CashSuper
{
	private double moneyRebate = 1d;
	public CashRebate(string moneyRebate)
	{
		this.moneyRebate = double.Parse(moneyRebate);
	}
	
	public override double acceptCash(double money)
	{
		return money*moneyRebate;
	}
}

//返利收费子类
class CashReturn : CashSuper
{
	private double moneyCondition = 0.0d;
	private double monyeReturn = 0.0d;

	public CashReturn(string moneyCondition,string monyeReturn)
	{
		this.moneyCondition = double.Parse(moneyCondition);
		this.moneyReturn = double.Parse(moneyReturn);
	}
	
	public override double acceptCash(double money)
	{
		double result = money;
		if(money>=moneyCondition)
			result = money - Math.Floor(money / moneyCondition) * moneyReturn;
		return result;
	}
}

//现金收费工厂类
class CashFactory
{
	public static CashSuper createCashAccept(string type)
	{
		CashSuper cs = null;
		switch(type)
		{
			case "正常收费":
				cs = new CashNormal();
				break;
			case "满300返100":
				CashReturn cr1 = new CashReturn("300","100"); 
				cs = cr1;
				break;
			case "打8折":
				CashRebate cr2 = new CashRebate("0.8");
				cs = cr2;
				break;
		}
	}
}

double total = 0.0d;
private void btnOk_Click(object sender,EventArgs e)
{
	CashSuper csuper = CashFactory.createCashAccept(cbxType.SelectedItem.ToString());
	double totalPrices = 0d;
	totalPrices = csuper.acceptCash(Convert.ToDouble(txtPrice.Text))
	* Convert.ToDouble(txtNum.Text);
	total = total + totalPrices;
	lbxList.Item.Add("单价：" + txtPrice.Text + "数量：" + txtNum.Text + " "
		+ cbxType.SelectedItem + "合计：" + totalPrices.ToString());
	lblResult.Text = total.ToString();
}

//策略模式实现
abstruct class Strategy
{
	//算法方法
	public abstruct void AlgorithmInterface();
}

//具体算法A
class ConcreteStrategyA : Strategy
{
	//算法A实现方法
	public overvide void AlgorithmInterface()
	{
		Console.WriteLine("算法A实现");
	}
}

//具体算法B
class ConcreteStrategyB : Strategy
{
	//算法A实现方法
	public overvide void AlgorithmInterface()
	{
		Console.WriteLine("算法B实现");
	}
}

//具体算法C
class ConcreteStrategyC : Strategy
{
	//算法A实现方法
	public overvide void AlgorithmInterface()
	{
		Console.WriteLine("算法C实现");
	}
}

class Context
{
	Strategy strategy;
	public Context(Strategy strategy) 	//初始化时传入具体的策略对象
	{
		this.strategy = strategy;
	}
	//上下文
	public void ContextInterface()
	{
		stratege.AlgorithmInterface();	//根据具体的策略对象，调用其算法的方法
	}
}

static void Main(string[] args)
{
	Context context;
	context = new Context(new ConcreteStrategyA());
	context.ContextInterface();
	
	context = new Context(new ConcreteStrategyB());
	context.ContextInterface();
	
	context = new Context(new ConcreteStrategyC());
	context.ContextInterface();
	
	Console.Read();
}



























































