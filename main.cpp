/***************************作者：高金满——班级：计科1704——学号：17110581107****************************/
#include <iostream>
#include <cstdio>
#include <list>
#include <algorithm>
#include <windows.h>
#define SPACE 100
#define InitID -1
#define INF 0x3F3F3F3F
#define TIME 500
using namespace std;

struct node
{
    int id;                      //作业ID，从1开始自增
    int address;                 //内存块初地址
    int space;                   //内存空间
    bool flag;                   //是否分配：false未分配，true已分配
};

list <node> Memory;              //双向链表
int cnt;                         //自增数字，赋值给作业ID
list <node>::iterator Buffer;    //NF分配迭代器，记录每次分配的位置，为下次分配服务
int All_Space;                   //总内存

void Welcome();
void Init();                     //初始化
void Menu();                     //一级目录
void Distribution(string step);  //二级目录：分配
void Recycle();                  //回收
void Look();                     //查看内存分配
void First_Fit();                //首次适应算法
void Next_Fit();                 //循环首次适应算法
void Best_Fit();                 //最佳适应算法
void Worst_Fit();                //最坏适应算法
int GetSpace();                  //分配时获得空间


void Welcome()
{
    cout<< "┏------------------------------------------------------┓" << endl;
    cout<< "┃      基于动态分区分配的存储器管理系统的设计与实现    ┃" << endl;
    cout<< "┣------------------------------------------------------┫" << endl;
    cout<< "┃                                                      ┃" << endl;
    cout<< "┃                                                      ┃" << endl;
    cout<< "┃                         作者：高金满                 ┃" << endl;
    cout<< "┃                         班级：计科1704               ┃" << endl;
    cout<< "┃                         学号：17110581107            ┃" << endl;
    cout<< "┃                         E-Mail：gjm1998@foxmail.com  ┃" << endl;
    cout<< "┃                                                      ┃" << endl;
    cout<< "┗------------------------------------------------------┛" << endl;
    Sleep(TIME * 1.5);
}
                                     /*****分配内存*****/
void Init()
{
    string m;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    while(1)
    {
        cout << "--------------------------请选择--------------------------" << endl;
        cout << "                 ---1.自动添加总内存大小------------------" << endl;
        cout << "                 ---2.手动添加总内存大小(建议小于1000)----" << endl;
        cin >> m;
        if ( m.length() > 1 || ( m[0] != '1' && m[0] != '2' ) )
        {
            cout << "Input Error!" << endl;
            continue;
        }
        break;
    }
    struct node s;
    bool flag = false;
    All_Space = SPACE;
    switch ( m[0] )
    {
        case '1':
            s.space = All_Space;
            s.address = 1;
            s.flag = flag;
            s.id = InitID;
            Memory.push_back(s);
            break;
        case '2':
            cout << "----输入总内存----" << endl;
            All_Space = GetSpace();
            s.space = All_Space;
            s.address = 1;
            s.flag = flag;
            s.id = InitID;
            Memory.push_back(s);
            break;
    }
    Look();
    Buffer = Memory.begin();
}

                                 /*****一级目录——选择算法*****/
void Menu()
{
    while (1)
    {
        printf("***************M**********E**********N**********U***************\n");
        printf("                                                                \n");
        printf("<-------------    1    ------    First_Fit分配   -------------->\n");
        printf("<-------------    2    ------    Next_Fit分配    -------------->\n");
        printf("<-------------    3    ------    Best_Fit分配    -------------->\n");
        printf("<-------------    4    ------    Worst_Fit分配   -------------->\n");
        string step;
        cin >> step;
        if ( step.length() > 1 || step[0] < '1' || step[0] > '4' )
        {
            cout << "Input Error!" << endl;
            continue;
        }
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "跳转中......" << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        Sleep(TIME);
        Distribution(step);
    }
}

                                    /*****二级目录——分配*****/
void Distribution( string key )
{
    while(1)
    {
        printf("***************M**********E**********N**********U***************\n");
        printf("                                                                \n");
        printf("<-------------    1    ------------    分配      -------------->\n");
        printf("<-------------    2    ------------    回收      -------------->\n");
        printf("<-------------    3    ------------    查看      -------------->\n");
        printf("<-------------    4    ------------    退出      -------------->\n");
        string step;
        cin >> step;
        if ( step.length() > 1 || step[0] < '1' || step[0] > '4' )
        {
            cout << "Input Error!" << endl;
            continue;
        }
        switch( step[0] )
        {
        case '1':
            switch( key[0] )
            {
            case '1':
                First_Fit();
                break;
            case '2':
                Next_Fit();
                break;
            case '3':
                Best_Fit();
                break;
            case '4':
                Worst_Fit();
                break;
            default:
                cout << "Input Error" << endl;
                Menu();
                break;
            }
            break;
        case '2':
            Recycle();
            break;
        case '3':
            Look();
            break;
        case '4':
            cout << "谢谢使用" << endl;
            Sleep(TIME / 2);
            cout << "正在退出..." << endl;
            Sleep(TIME / 2);
            cout << "已退出" << endl;
            exit(0);
        }
    }

}

                                        /*****回收*****/
void Recycle()
{
    string R_ID;
    int ID = 0;
    cout << "请输入待删除的作业ID" << endl;
    while( ID <= 0 )
    {
        cout << "提示：ID为正整数" << endl;
        cin >> R_ID;                                  //请求回收的作业ID
        ID = atoi( R_ID.c_str() );
    }
    list <node>::iterator Ite;                        //迭代器
    bool flag = false;
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        if ( (*Ite).id == ID )                        //找到需要回收的作业ID
        {
            list <node>::iterator Prev ;
            list <node>::iterator Next ;
            bool Pr = true;
            bool Ne = true;

            //回收预处理
            if ( Ite == Memory.begin() )              //判断特殊位置，回收区是头结点
            {
                Next = (++Ite)--;
                Pr = false;
            }
            else if ( Ite == Memory.end() )           //判断特殊位置，回收区是尾结点
            {
                Prev = (--Ite)++;
                Ne = false;
            }
            else                                      //一般位置
            {
                Prev = (--Ite)++;
                Next = (++Ite)--;
            }

            //回收，分四种情况
            if ( Pr && !(*Prev).flag && (!Ne || (Ne && (*Next).flag)) )       //前分区存在且未分配，无后分区或后分区已分配
            {
                (*Prev).space += (*Ite).space;
                Memory.erase( Ite );
            }
            else if ( Ne && !(*Next).flag && (!Pr || (Pr && (*Prev).flag)) )  //后分区存在且未分配，无前分区或前分区已分配
            {
                (*Ite).space += (*Next).space;
                (*Ite).id = InitID;
                (*Ite).flag = false;
                Memory.erase( Next );
            }
            else if ( Pr && !(*Prev).flag && Ne && !(*Next).flag )            //前后分区都存在且都未分配
            {
                (*Prev).space += ( (*Ite).space + (*Next).space );
                Memory.erase( Ite );
                Memory.erase( Next );
            }
            else                                                              //前后分区都分配
            {
                (*Ite).flag = false;
                (*Ite).id = InitID;
            }
            cout << "SUCCESS!" << endl;
            flag = true;
            Sleep(TIME / 2);
            break;
        }
    }
    if ( false == flag )
            cout << "回收失败，没有此作业" << endl;
}
                                        /*****查看*****/
void Look()
{
    list <node>::iterator Ite;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "┏------------┳------------┳------------┳------------┓" << endl;
    cout << "┃   作业ID   ┃   首地址   ┃  是否分配  ┃  空间大小  ┃" << endl;
    cout << "┣------------╋------------╋------------╋------------┫" << endl;
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        node s = *Ite;
        if ( s.flag )
            printf("┃     %2d           %04d          %d           %04d   ┃\n", s.id, s.address, s.flag, s.space );
        else if ( s.space != 0 )
            printf("┃    NULL          %04d          %d           %04d   ┃\n", s.address, s.flag, s.space);
    }
    cout << "┗------------┻------------┻------------┻------------┛" << endl;

    cout << endl << "内存分配情况：" << endl;
    cout << "--------------------------------------------------" << endl;
    int n = 5;
    while( n-- )
    {
        for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
        {
            node s = *Ite;

            int x = s.space * 50 / All_Space;
            if ( s.id != InitID )
            {
                while ( x-- )
                    cout << "#" ;
            }
            else
            {
                while ( x-- )
                    cout << " " ;
            }
        }
        cout << endl;
    }
    cout << "--------------------------------------------------" << endl << endl;
    Sleep(TIME);
}

                           /*****首次适应算法——每次从链首顺序查找*****/
void First_Fit()
{
    cout << "请输入请求分配内存大小" << endl;
    int R_M;
    R_M = GetSpace();                                //请求分配空间大小
    cnt++;                                           //作业ID自增
    node Piece;                                      //缓冲区，用于插入
    list <node>::iterator Ite;                       //迭代器
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        if ( R_M <= (*Ite).space && !(*Ite).flag )   //找到未分配的分区且空间足够
        {
            Piece.address = (*Ite).address;          //缓冲区参数配置
            Piece.flag = true;
            Piece.id = cnt;
            Piece.space = R_M;
            (*Ite).address += R_M;
            (*Ite).space -= R_M;
            Memory.insert(Ite, Piece);               //插入结点
            cout << "SUCCESS!" << endl;
            Sleep(TIME / 2);
            break;
        }
    }
    if ( Ite == Memory.end() )
        cout << "空间不足，分配失败" << endl;
}

                    /*****循环首次适应算法——每次从上次的下一个空闲分区查找*****/
void Next_Fit()
{
    cout << "请输入请求分配内存大小" << endl;
    int R_M;
    R_M = GetSpace();                                //请求分配空间大小
    cnt++;                                           //作业ID自增
    node Piece;                                      //缓冲区，用于插入
    list <node>::iterator Ite;                       //迭代器
    for ( Ite = Buffer; Ite != Memory.end(); Ite++ )
    {
        if ( R_M <= (*Ite).space && !(*Ite).flag )   //找到未分配的分区且空间足够
        {
            Piece.address = (*Ite).address;          //缓冲区参数配置
            Piece.flag = true;
            Piece.id = cnt;
            Piece.space = R_M;
            (*Ite).address += R_M;
            (*Ite).space -= R_M;
            Memory.insert(Ite, Piece);               //插入结点
            cout << "SUCCESS" << endl;
            Buffer = Ite;
            Sleep(TIME / 2);
            break;
        }
    }
    if ( Ite == Memory.end() )
        cout << "空间不足，分配失败" << endl;
}

                            /*****最佳适应算法——每次找最小*****/
void Best_Fit()
{
    cout << "请输入请求分配内存大小" << endl;
    int R_M;
    R_M = GetSpace();                                //请求分配空间大小
    cnt++;                                           //作业ID自增
    node Piece;                                      //缓冲区，用于插入
    list <node>::iterator Ite;                       //迭代器
    list <node>::iterator Ans;
    int Min = INF;
    bool flag = false;
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        if ( !(*Ite).flag && (*Ite).space < Min )
        {
            Min = (*Ite).space;
            Ans = Ite;
            flag = true;
        }
    }

    if ( flag && R_M <= (*Ans).space )                //找到未分配的分区且空间足够
    {
        Piece.address = (*Ans).address;               //缓冲区参数配置
        Piece.flag = true;
        Piece.id = cnt;
        Piece.space = R_M;
        (*Ans).address += R_M;
        (*Ans).space -= R_M;
        Memory.insert(Ans, Piece);                    //插入结点
        cout << "SUCCESS" << endl;
        Sleep(TIME / 2);
    }
    else
        cout << "空间不足，分配失败" << endl;
}

                           /*****最坏适应算法——每次找最大*****/
void Worst_Fit()
{
    cout << "请输入请求分配内存大小" << endl;
    int R_M;
    R_M = GetSpace();                                //请求分配空间大小
    cnt++;                                           //作业ID自增
    node Piece;                                      //缓冲区，用于插入
    list <node>::iterator Ite;                       //迭代器
    list <node>::iterator Ans;
    int Max = 0;
    bool flag = false;
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        if ( !(*Ite).flag && (*Ite).space > Max )
        {
            Max = (*Ite).space;
            Ans = Ite;
            flag = true;
        }
    }

    if ( flag && R_M <= (*Ans).space )               //找到未分配的分区且空间足够
    {
        Piece.address = (*Ans).address;              //缓冲区参数配置
        Piece.flag = true;
        Piece.id = cnt;
        Piece.space = R_M;
        (*Ans).address += R_M;
        (*Ans).space -= R_M;
        Memory.insert(Ans, Piece);                   //插入结点
        cout << "SUCCESS" << endl;
        Sleep(TIME / 2);
    }
    else
        cout << "空间不足，分配失败" << endl;
}

                                     /*****申请空间*****/
int GetSpace()
{
    while(1)
    {
        string RM;
        int IntRM;
        cin >> RM;
        IntRM = atoi( RM.c_str() );
        if ( IntRM <= 0 )
        {
            cout << "请输入正整数" << endl;
            continue;
        }
        if ( IntRM >= 10000)
        {
            cout << "数字过大，请重新输入" << endl;
            continue;
        }
        return IntRM;
    }
}

int main()
{
    Welcome();
    Init();
    Menu();
    return 0;
}
/***************************作者：高金满——班级：计科1704——学号：17110581107****************************/
