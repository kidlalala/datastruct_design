#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX 20
#define MAX_S 30
#define MAX_O 20
typedef struct student{
		char number[MAX];
		char name[MAX];
		char sex;
		int grade;
		char major[MAX];
		struct student *next;
		int order;
}STU;
typedef struct organization{
		int number;
		char name[MAX];
		char time[MAX];
		struct organization *next;
}ORG;
const int S=sizeof(STU);
const int O=sizeof(ORG);

//创建学生信息表
STU * creat_s()
{
		int i=1;
		FILE *fp;
		fp=fopen("student.txt","r");
		STU *head,*tail,*p;
		head=(STU *)malloc(S);
		strcpy(head->number,"");
		strcpy(head->name,"");
		strcpy(head->major,"");
		head->sex='N';
		head->grade=0;
		head->order=0;
		head->next=NULL;
		char number[MAX],name[MAX],major[MAX];
		int grade;
		char sex;
		while(fscanf(fp,"%s %s %c %d %s",number,name,&sex,&grade,major)!=EOF)
		{
 				p=(STU *)malloc(S);
				p->next=NULL;
				strcpy(p->number,number);
				strcpy(p->name,name);
				strcpy(p->major,major);
				p->grade=grade;
				p->sex=sex;
				p->order=i;
				if(!(head->next))
				{
						head->next=p;
						tail=p;
				}
				else
				{
						tail->next=p;
						tail=p;
				}
				i++;
		}
		fclose(fp);
		return head;
}

//学生个人信息显示
void display_s(STU *a)
{
	    printf("%s %s %c %d %s\n",a->number,a->name,a->sex,a->grade,a->major);
}
//整体学生信息表显示
void show_s(STU * a)
{
		STU *b=a->next;
		printf("学生信息为:\n学号 姓名 性别 年级 专业\n");
		while(b)
		{
				display_s(b);
				b=b->next;
		}
}

//根据学号寻找对应学生
STU * search_s(STU * a,char temp[])
{
		STU *b=a->next;
		while(b)
		{
				if(!strcmp(temp,b->number))
						return b;
				b=b->next;
		}
		return NULL;
}

//根据当前学生指针寻找前驱指针
STU * search_s_pre(STU *a,STU *b)
{
		STU *c=a;
		while(c)
		{
				if(c->next==b)
						return c;
				c=c->next;
		}
		return NULL;
}

//判断字符串是否为空
int isempty(char a[])
{
		if(!strcmp(a,""))
				return 1;
		else
				return 0;
}

//检验输入学号的合法性 空 不是数字 长度超过12位
int isnumber(char s[])
{
		
		if(strlen(s)>12)
				return 0;
		if(isempty(s))
				return 0;
		int flag=0;
		for(int i=0;i<strlen(s);i++)
		{
				if(s[i]-'0'>9||s[i]-'0'<0)
				{
						flag=1;
						break;
				}
		}
		if(flag) return 0;
		else return 1;
}

//判断是否重新输入
int yesorno()
{
		char buf[MAX];
		printf("输入y或yes表示确定，其他任意输入表示返回\n");
		scanf("%s",buf);
		int flag=0;
		if((!strcmp("yes",buf))||(!strcmp("YES",buf)))
				flag=1;
		if(!strcmp("Y",buf)||(!strcmp("y",buf)))
				flag=1;
		if(flag) return 1;
		else return 0;
}

//学生数量统计
int getlength_s(STU *a)
{
		STU *b=a->next;
		int s=0;
		while(b)
		{
				b=b->next;
				s++;
		}
		return s;
}
//添加学生
STU * add_s(STU *a)
{
		STU *b=a->next,*c;
		while(b->next) b=b->next;
		c=(STU *)malloc(S);
		b->next=c;
		c->next=NULL;
		b=a;
		printf("请输入学生学号:\n");
		scanf("%s",c->number);
		while(!isnumber(c->number)) 
		{
				printf("学号格式错误!是否重新输入?\n");
				if(!yesorno())
				{
						free(c);
						return NULL;
				}
				printf("请输入学生学号\n");
				scanf("%s",c->number);
		}
		while(b!=c)
		{
				if(!strcmp(b->number,c->number))
				{
						free(c);
						printf("请勿添加重复的学生!\n");
						return NULL;
				}
				b=b->next;
		}
		printf("请输入学生姓名\n");
		scanf("%s",c->name);
		while(isempty(c->name))
		{
				printf("姓名不为空!是否重新输入?\n");
				if(!yesorno())
				{
						free(c);
						return NULL;
				}
				printf("请输入学生姓名\n");
				scanf("%s",c->name);
		}
		printf("请输入学生性别(男性为M，女性为F)\n");
		scanf("%*c%c",&(c->sex));
		while(c->sex!='F'&&c->sex!='M')
		{
				printf("性别格式错误,是否重新输入?\n");
				if(!yesorno())
				{
						free(c);
						return NULL;
				}
				printf("请输入学生性别\n");
			 	scanf("%*c%c",&(c->sex));
		}
		printf("请输入学生年级(入学年份)\n");
		scanf("%d",&(c->grade));
		while(c->grade>2017||c->grade<0)
		{
				printf("未输入正确学生年级(0~2017),是否重新输入?\n");
				if(!yesorno())
				{
						free(c);
						return NULL;
				}
				printf("请输入学生年级\n");
				scanf("%d",&(c->grade));
		}
		printf("请输入学生专业\n");
		scanf("%s",c->major);
		while(isempty(c->major))
		{
				printf("专业不为空!是否重新输入?\n");
				if(!yesorno())
				{
						free(c);
						return NULL;
				}
				printf("请输入学生专业\n");
				scanf("%s",c->major);
		}
		int t=getlength_s(a);
		c->order=t;
		return a;
}

//修改学生信息
void change_s(STU * a)
{
		system("clear");
		show_s(a);
		char temp[MAX];
		printf("请选择想修改学生的学号:\n");
		scanf("%s",temp);
		STU *b=search_s(a,temp);
		if(!b)
		{
				printf("查找不到此人！\n");
				return ; 
		}
		system("clear");
		display_s(b);
		int choose,n;
		char t;
		while(1)
		{
				printf("请输入想修改的数据序号\n");
				printf("1.学号 2.姓名 3.性别 4.年级 5.专业\n");
				scanf("%d",&choose);
				switch(choose)
				{
						case 1: printf("请输入修改后的学号\n");
							    scanf("%s",temp);
							    strcpy(b->number,"");
								if(isnumber(temp)&&(!search_s(a,temp))) 
							   			strcpy(b->number,temp);
							    else
								{
										printf("输入学号有误或重复\n");
										return ;
								}
								break;
			    case 2: printf("请输入修改后的姓名\n");
								scanf("%s",temp);
								if(!isempty(temp))
										strcpy(b->name,temp);
								else
								{
									    printf("姓名不为空\n");
						 				return ;
						    	}
								break;
					    case 3: printf("请输入修改后的性别\n");
							 	scanf("%*c%c",&t);
								if(t=='F'||t=='M')
										b->sex=t;
							else
								{
										printf("输入性别有误\n");
										return ;
								}
								break;
					    case 4: printf("请输入修改后的年级\n");
							 	scanf("%d",&n);
								if(n>0&&n<2017)
										b->grade=n;
								else
								{
										printf("输入年份有误\n");
										return ;
								}
								break;
						case 5: printf("请输入修改后的专业\n");
								scanf("%s",temp);
								if(!isempty(temp))
										strcpy(b->major,temp);
								else
								{
						     			printf("专业不为空\n");
										return ;
								}
								break;
						default:printf("请输入正确的操作项\n");
					}
					printf("是否继续修改?\n");
					if(!yesorno())
							return ;
					system("clear");
		}
}

//创建社团表
ORG * creat_o()
{
		FILE *fp;
		fp=fopen("organization.txt","r");
		ORG *head,*tail,*p;
		head=(ORG *)malloc(O);
		head->number=0;
		strcpy(head->name,"");
		strcpy(head->time,"");
		head->next=NULL;
		int i=1;
		char name[MAX],time[MAX];
		while(fscanf(fp,"%s %s",name,time)!=EOF)
		{
 				p=(ORG *)malloc(O);
				p->next=NULL;
				p->number=i;
				strcpy(p->name,name);
				strcpy(p->time,time);
				if(!(head->next))
				{
						head->next=p;
						tail=p;
				}
				else
				{
						tail->next=p;
						tail=p;
				}
				i++;
		}
		fclose(fp);
		return head;
}

//显示单个社团信息
void display_o(ORG * a)
{
		printf("%d %s %s\n",a->number,a->name,a->time);
}
//显示整个社团表信息
void show_o(ORG * a)
{
		ORG *b=a->next;
		printf("社团信息为:\n社团编号 社团名称 社团创建时间\n");
		while(b)
		{
				display_o(b);
				b=b->next;
		}
}

//查找社团
ORG * search_o(ORG * a,int t)
{
		ORG * b=a->next;
		while(b)
		{
				if(b->number==t)
						return b;
				b=b->next;
		}
		return NULL;
}
//通过已知社团指针，查找前驱指针
ORG * search_o_pre(ORG * a,ORG * b)
{
		ORG *c=a;
		while(c)
		{
				if(c->next==b)
						return c;
				c=c->next;
		}
		return NULL;
}

//统计社团数量
int getlength_o(ORG * a)
{
		ORG *b=a;
		int s=0;
		while(b)
		{
				b=b->next;
				s++;
		}
		return s;
}

//添加社团
ORG * add_o(ORG * a)
{
		ORG *b=a->next,*c;
		while(b->next)
				b=b->next;
		c=(ORG *)malloc(O);
		c->next=NULL;
		b->next=c;
		int t=getlength_o(a);
		c->number=t;
		printf("请输入社团名称\n");
		scanf("%s",c->name);
		while(isempty(c->name))
		{
				printf("名称不可为空!是否重新输入?\n");
				if(!yesorno())
				{
						free(c);
						return NULL;
				}
				printf("请输入社团名称\n");
				scanf("%s",c->name);
		}
		printf("请输入社团创建时间\n");
		int year,month,date,n;
		printf("请输入年份(2000~2017):\n");
		scanf("%d",&year);
		while(year<2000||year>2017)
		{
				printf("请重新输入正确的年份!\n");
				scanf("%d",&year);
		}
		printf("请输入月份(1~12):\n");
		scanf("%d",&month);
		while(month<1||month>12)
		{
				printf("请重新输入正确的月份!\n");
				scanf("%d",&month);
		}
		switch(month)
		{
				case 1:case 3:
				case 5:case 7:
				case 8:case 10:
				case 12:n=31;break;
				case 4:case 6:
				case 9:case 11:n=30;break;
				default:n=28;
		}
		if(((!year%100)||(year%100!=0&&year%4==0))&&n==28)
				n++;
		printf("请输入日期:\n");
		scanf("%d",&date);
		while(date<1||date>n)
		{
				printf("请重新输入正确的日期!\n");
				scanf("%d",&date);
		}
		char y[MAX]={0},m[MAX]={0},d[MAX]={0};
		sprintf(y,"%d",year);
		sprintf(m,"%d",month);
		sprintf(d,"%d",date);
		y[strlen(y)]='-';
		y[strlen(y)+1]='\0';
		strcat(y,m);
		y[strlen(y)]='-';
		y[strlen(y)+1]='\0';
		strcat(y,d);
		y[strlen(y)]='\0';
		strcpy(c->time,y);
		return a;
}

//修改社团信息
void change_o(ORG *a)
{
		system("clear");
		show_o(a);
		printf("请输入想要修改的社团编号\n");
		int t;
		scanf("%d",&t);
		ORG *b=search_o(a,t);
		if(!b)
		{
				printf("未找到相应社团\n");
				return ;
		}
		display_o(b);
		int choose;
		char temp[MAX];
		while(1)
		{
				printf("请输入想修改的数据项\n");
				printf("1.社团名称 2.社团创建时间\n");
				scanf("%d",&choose);
				switch(choose)
				{
						case 1: printf("请输入修改后的社团名称\n");
								scanf("%s",temp);
								if(!isempty(temp))
										strcpy(b->name,temp);
								else
								{
										printf("名称不为空\n");
										return ;
								}
							    break;
						case 2: printf("请输入修改后的创建时间\n");
								int year,month,date,n;
								printf("请输入年份(2000~2017):\n");
								scanf("%d",&year);
								while(year<2000||year>2017)
								{
										printf("请重新输入正确的年份!\n");
										scanf("%d",&year);
								}	
								printf("请输入月份(1~12):\n");
								scanf("%d",&month);
								while(month<0||month>12)
								{
										printf("请重新输入正确的月份!\n");
										scanf("%d",&month);
								}
								switch(month)
								{
										case 1:case 3:
										case 5:case 7:
										case 8:case 10:
										case 12:n=31;break;
										case 4:case 6:
										case 9:case 11:n=30;break;
										default:n=28;
								}
								if(((!year%100)||(year%100!=0&&year%4==0))&&n==28)
										n++;
								printf("请输入日期:\n");
								scanf("%d",&date);
								while(date<0||date>n)
								{
										printf("请重新输入正确的日期!\n");
										scanf("%d",&date);
								}
								char y[MAX]={0},m[MAX]={0},d[MAX]={0};
								sprintf(y,"%d",year);
								sprintf(m,"%d",month);
								sprintf(d,"%d",date);
								y[strlen(y)]='-';
								strcat(y,m);
								y[strlen(y)]='-';
								strcat(y,d);
								strcpy(b->time,y);
							    break;
						default:printf("请输入正确的操作项\n");
				}
				printf("是否继续修改?\n");
				if(!yesorno())
						return ;
		}
}

//创建关系表
void creat_rela(int index[][MAX_S])
{
		FILE *fp=fopen("relation.txt","r");
		for(int i=0;i<MAX_O;i++)
				for(int j=0;j<MAX_S;j++)
						fscanf(fp,"%d",&index[i][j]);
		fclose(fp);

}

//根据序号寻找学生
STU *search_by_order(STU *a,int order)
{
		STU *b=a->next;
		while(b)
		{
				if(b->order==order)
						return b;
				b=b->next;
		}
		return NULL;
}

//删除学生
STU * delete_s(STU *a,ORG *c,int index[][MAX_S])
{
		char temp[MAX];
		show_s(a);
		printf("请输入想要删除的学生学号\n");
		scanf("%s",temp);
		STU *b=search_s(a,temp);
		if(!b)
		{
				printf("未找到相关用户!\n");
				return NULL;
		}
		STU *d=search_s_pre(a,b);
		d->next=b->next;
		int t=getlength_o(c);
		for(int i=0;i<t;i++)
				index[i][b->order-1]=0;
		free(b);
		return a;
}

//删除社团
ORG * delete_o(ORG *a,STU *c,int index[][MAX_S])
{
		int n;
		show_o(a);
		printf("请输入想要删除的社团编号\n");
		scanf("%d",&n);
		ORG *b=search_o(a,n);
		if(!b)
		{
				printf("未找到相关社团\n");
				return NULL;
		}
		ORG *d=search_o_pre(a,b);
		d->next=b->next;
		int t=getlength_s(c);
		for(int i=0;i<t;i++)
				index[n-1][i]=0;
		free(b);
		return a;
}

//显示社团学生信息
void show(ORG *a,STU *c,int index[][MAX_S])
{
		int n;
		show_o(a);
		printf("请输入想查看的社团编号\n");
		scanf("%d",&n);
		ORG *b=search_o(a,n);
		if(!b)
		{
				printf("未找到相应社团!\n");
				return ;
		}
		int t=getlength_s(c);
		for(int i=0;i<t;i++)
		{
				if(index[n-1][i]==1)
				{
						STU *d=search_by_order(c,i+1);
						display_s(d);
						printf("职务:会员\n");
				}
				else if(index[n-1][i]==2)
				{
						STU *d=search_by_order(c,i+1);
						display_s(d);
						printf("职务:秘书\n");
				}
				else if(index[n-1][i]==3)
				{
						STU *d=search_by_order(c,i+1);
						display_s(d);
						printf("职务:会长\n");
				}
		}
		printf("是否修改学生职位信息?\n");
		if(!yesorno())
				return ;
		int flag=1;
		while(flag)
		{
				printf("请输入想修改的学生的学号\n");
				char temp[MAX];
				scanf("%s",temp);
				STU *m=search_s(c,temp);
				if(!m)
				{
						printf("未找到相应学生\n");
						return ;
				}
				printf("请输入修改后的职位(会员 秘书 会长)\n");
				printf("输入'无'表示将从社团中删除该学生\n");
				scanf("%s",temp);
				if(!strcmp(temp,"会员"))
						index[n-1][m->order-1]=1;
				else if(!strcmp(temp,"秘书"))
						index[n-1][m->order-1]=2;
				else if(!strcmp(temp,"会长"))
						index[n-1][m->order-1]=3;
				else if(!strcmp(temp,"无"))
						index[n-1][m->order-1]=0;
				printf("是否继续修改学生?\n");
				if(!yesorno()) flag=0;
		}
}

//通过职位在社团中查询学生信息
void search_by_post(STU *a,ORG *b,int index[][MAX_S])
{
		int n,p=0;
		char temp[MAX];
		show_o(b);
		printf("请输入想查看的社团编号\n");
		scanf("%d",&n);
		ORG *c=search_o(b,n);
		if(!c)
		{
				printf("未找到相关社团\n");
				return ;
		}
		printf("请输入想查找的职位信息\n");
		scanf("%s",temp);
		if(!strcmp(temp,"会员"))
				p=1;
		else if(!strcmp(temp,"秘书"))
				p=2;
		else if(!strcmp(temp,"会长"))
				p=3;
		else 
		{
				printf("输入职位有误!\n");
				return ;
		}
		int t=getlength_s(a);
		for(int i=0;i<t;i++)
				if(index[n-1][i]==p)
				{
						STU *d=search_by_order(a,i+1);
						display_s(d);
				}
}

//学生加入社团
void join(STU *a,ORG *b,int index[][MAX_S])
{
		char temp[MAX];
		int n;
		show_s(a);
		printf("请输入想操作学生的学号\n");
		scanf("%s",temp);
		STU *c=search_s(a,temp);
		if(!c)
		{
				printf("未找到相应学生\n");
				return ;
		}
		show_o(b);
		while(1)
		{
				printf("请输入想加入的社团编号\n");
				scanf("%d",&n);
				ORG *d=search_o(b,n);
				if(!d)
				{
						printf("未找到相应社团\n");
						return ;
				}
				printf("请输入学生职位(会员 秘书 会长)\n");
				scanf("%s",temp);
				if(!strcmp(temp,"会员"))
						index[n-1][c->order-1]=1;
				else if(!strcmp(temp,"秘书"))
						index[n-1][c->order-1]=2;
				else if(!strcmp(temp,"会长"))
						index[n-1][c->order-1]=3;
				else
				{
						printf("输入职务错误!\n");
						return ;
				}
				printf("是否继续加入社团\n");
				if(!yesorno())
						return ;
		}
}

//显示学生所加入的社团
void display(STU *a,ORG *b,int index[][MAX_S])
{
		char temp[MAX];
		show_s(a);
		printf("请输入想查看的学生学号\n");
		scanf("%s",temp);
		STU *c=search_s(a,temp);
		if(!c)
		{
				printf("未找到相应学生!\n");
				return ;
		}
		int t=getlength_o(b);
		for(int i=0;i<t;i++)
		{
				if(index[i][c->order-1]>0)
				{
						ORG *d=search_o(b,i+1);
						display_o(d);
				}
		}
		printf("\n是否退出社团?\n");
		if(!yesorno())
				return ;
		int flag=1;
		while(flag)
		{
				printf("请输入想退出的社团的编号\n");
				int n;
				scanf("%d",&n);
				ORG *m=search_o(b,n);
				if(!m)
				{
						printf("未找到相应社团\n");
						return ;
				}
				index[n-1][c->order-1]=0;
				printf("是否继续退出社团?\n");
				if(!yesorno()) flag=0;
		}
}

//将学生信息写回文件
void save_s(STU *a)
{
		FILE *fp=fopen("student.txt","w");
		STU *b=a->next;
		while(b)
		{
				fprintf(fp,"%s %s %c %d %s\n",b->number,b->name,b->sex,b->grade,b->major);
				b=b->next;
		}
		fclose(fp);
}

//将设团信息写回文件
void save_o(ORG *a)
{
		FILE *fp=fopen("organization.txt","w");
		ORG *b=a->next;
		while(b)
		{
				fprintf(fp,"%s %s\n",b->name,b->time);
				b=b->next;
		}
		fclose(fp);
}

//将关系表写入文件
void save(STU *a,ORG *b,int index[][MAX_S])
{
		FILE *fp=fopen("relation.txt","w");
		for(int i=0;i<MAX_O;i++)
		{
				for(int j=0;j<MAX_S;j++)
						fprintf(fp,"%d ",index[i][j]);
				fprintf(fp,"\n");
		}
		fclose(fp);
		save_s(a);
		save_o(b);
}
//菜单
void menu()
{
		printf("欢迎使用学生成绩管理系统\n");
		printf("1.显示学生信息\n");
		printf("2.添加学生\n");
		printf("3.删除学生\n");
		printf("4.修改学生\n");
		printf("5.显示社团信息\n");
		printf("6.添加社团\n");
		printf("7.删除社团\n");
		printf("8.修改社团\n");
		printf("9.学生加入社团\n");
		printf("10.查看学生所加入的社团\n");
		printf("11.查看社团中的学生信息\n");
		printf("12.查看社团中相关职位的学生\n");
		printf("13.保存\n");
		printf("14.退出系统\n");
}

int main()
{
		STU *s=creat_s();
		ORG *o=creat_o();
		int index[MAX_O][MAX_S];
		creat_rela(index);
		while(1)
		{
				menu();
				int choose;
				printf("请选择想执行的选项\n");
				scanf("%d",&choose);
				switch(choose)
				{
						case 1:show_s(s);break;
						case 2:add_s(s);break;
						case 3:delete_s(s,o,index);break;
						case 4:change_s(s);break;
						case 5:show_o(o);break;
						case 6:add_o(o);break;
						case 7:delete_o(o,s,index);break;
						case 8:change_o(o);break;
						case 9:join(s,o,index);break;
						case 10:display(s,o,index);break;
						case 11:show(o,s,index);break;
						case 12:search_by_post(s,o,index);break;
						case 13:save(s,o,index);break;
						case 14:return 0;
						default:printf("请选择正确选项\n");
				}
				printf("\n是否继续使用系统?\n");
				if(!yesorno())
						return 0;
				system("clear");
		}
		return 0;
}
