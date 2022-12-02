/***************************���ߣ��߽��������༶���ƿ�1704����ѧ�ţ�17110581107****************************/
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
    int id;                      //��ҵID����1��ʼ����
    int address;                 //�ڴ�����ַ
    int space;                   //�ڴ�ռ�
    bool flag;                   //�Ƿ���䣺falseδ���䣬true�ѷ���
};

list <node> Memory;              //˫������
int cnt;                         //�������֣���ֵ����ҵID
list <node>::iterator Buffer;    //NF�������������¼ÿ�η����λ�ã�Ϊ�´η������
int All_Space;                   //���ڴ�

void Welcome();
void Init();                     //��ʼ��
void Menu();                     //һ��Ŀ¼
void Distribution(string step);  //����Ŀ¼������
void Recycle();                  //����
void Look();                     //�鿴�ڴ����
void First_Fit();                //�״���Ӧ�㷨
void Next_Fit();                 //ѭ���״���Ӧ�㷨
void Best_Fit();                 //�����Ӧ�㷨
void Worst_Fit();                //���Ӧ�㷨
int GetSpace();                  //����ʱ��ÿռ�


void Welcome()
{
    cout<< "��------------------------------------------------------��" << endl;
    cout<< "��      ���ڶ�̬��������Ĵ洢������ϵͳ�������ʵ��    ��" << endl;
    cout<< "��------------------------------------------------------��" << endl;
    cout<< "��                                                      ��" << endl;
    cout<< "��                                                      ��" << endl;
    cout<< "��                         ���ߣ��߽���                 ��" << endl;
    cout<< "��                         �༶���ƿ�1704               ��" << endl;
    cout<< "��                         ѧ�ţ�17110581107            ��" << endl;
    cout<< "��                         E-Mail��gjm1998@foxmail.com  ��" << endl;
    cout<< "��                                                      ��" << endl;
    cout<< "��------------------------------------------------------��" << endl;
    Sleep(TIME * 1.5);
}
                                     /*****�����ڴ�*****/
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
        cout << "--------------------------��ѡ��--------------------------" << endl;
        cout << "                 ---1.�Զ�������ڴ��С------------------" << endl;
        cout << "                 ---2.�ֶ�������ڴ��С(����С��1000)----" << endl;
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
            cout << "----�������ڴ�----" << endl;
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

                                 /*****һ��Ŀ¼����ѡ���㷨*****/
void Menu()
{
    while (1)
    {
        printf("***************M**********E**********N**********U***************\n");
        printf("                                                                \n");
        printf("<-------------    1    ------    First_Fit����   -------------->\n");
        printf("<-------------    2    ------    Next_Fit����    -------------->\n");
        printf("<-------------    3    ------    Best_Fit����    -------------->\n");
        printf("<-------------    4    ------    Worst_Fit����   -------------->\n");
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
        cout << "��ת��......" << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        Sleep(TIME);
        Distribution(step);
    }
}

                                    /*****����Ŀ¼��������*****/
void Distribution( string key )
{
    while(1)
    {
        printf("***************M**********E**********N**********U***************\n");
        printf("                                                                \n");
        printf("<-------------    1    ------------    ����      -------------->\n");
        printf("<-------------    2    ------------    ����      -------------->\n");
        printf("<-------------    3    ------------    �鿴      -------------->\n");
        printf("<-------------    4    ------------    �˳�      -------------->\n");
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
            cout << "ллʹ��" << endl;
            Sleep(TIME / 2);
            cout << "�����˳�..." << endl;
            Sleep(TIME / 2);
            cout << "���˳�" << endl;
            exit(0);
        }
    }

}

                                        /*****����*****/
void Recycle()
{
    string R_ID;
    int ID = 0;
    cout << "�������ɾ������ҵID" << endl;
    while( ID <= 0 )
    {
        cout << "��ʾ��IDΪ������" << endl;
        cin >> R_ID;                                  //������յ���ҵID
        ID = atoi( R_ID.c_str() );
    }
    list <node>::iterator Ite;                        //������
    bool flag = false;
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        if ( (*Ite).id == ID )                        //�ҵ���Ҫ���յ���ҵID
        {
            list <node>::iterator Prev ;
            list <node>::iterator Next ;
            bool Pr = true;
            bool Ne = true;

            //����Ԥ����
            if ( Ite == Memory.begin() )              //�ж�����λ�ã���������ͷ���
            {
                Next = (++Ite)--;
                Pr = false;
            }
            else if ( Ite == Memory.end() )           //�ж�����λ�ã���������β���
            {
                Prev = (--Ite)++;
                Ne = false;
            }
            else                                      //һ��λ��
            {
                Prev = (--Ite)++;
                Next = (++Ite)--;
            }

            //���գ����������
            if ( Pr && !(*Prev).flag && (!Ne || (Ne && (*Next).flag)) )       //ǰ����������δ���䣬�޺�����������ѷ���
            {
                (*Prev).space += (*Ite).space;
                Memory.erase( Ite );
            }
            else if ( Ne && !(*Next).flag && (!Pr || (Pr && (*Prev).flag)) )  //�����������δ���䣬��ǰ������ǰ�����ѷ���
            {
                (*Ite).space += (*Next).space;
                (*Ite).id = InitID;
                (*Ite).flag = false;
                Memory.erase( Next );
            }
            else if ( Pr && !(*Prev).flag && Ne && !(*Next).flag )            //ǰ������������Ҷ�δ����
            {
                (*Prev).space += ( (*Ite).space + (*Next).space );
                Memory.erase( Ite );
                Memory.erase( Next );
            }
            else                                                              //ǰ�����������
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
            cout << "����ʧ�ܣ�û�д���ҵ" << endl;
}
                                        /*****�鿴*****/
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
    cout << "��------------��------------��------------��------------��" << endl;
    cout << "��   ��ҵID   ��   �׵�ַ   ��  �Ƿ����  ��  �ռ��С  ��" << endl;
    cout << "��------------��------------��------------��------------��" << endl;
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        node s = *Ite;
        if ( s.flag )
            printf("��     %2d           %04d          %d           %04d   ��\n", s.id, s.address, s.flag, s.space );
        else if ( s.space != 0 )
            printf("��    NULL          %04d          %d           %04d   ��\n", s.address, s.flag, s.space);
    }
    cout << "��------------��------------��------------��------------��" << endl;

    cout << endl << "�ڴ���������" << endl;
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

                           /*****�״���Ӧ�㷨����ÿ�δ�����˳�����*****/
void First_Fit()
{
    cout << "��������������ڴ��С" << endl;
    int R_M;
    R_M = GetSpace();                                //�������ռ��С
    cnt++;                                           //��ҵID����
    node Piece;                                      //�����������ڲ���
    list <node>::iterator Ite;                       //������
    for ( Ite = Memory.begin(); Ite != Memory.end(); Ite++ )
    {
        if ( R_M <= (*Ite).space && !(*Ite).flag )   //�ҵ�δ����ķ����ҿռ��㹻
        {
            Piece.address = (*Ite).address;          //��������������
            Piece.flag = true;
            Piece.id = cnt;
            Piece.space = R_M;
            (*Ite).address += R_M;
            (*Ite).space -= R_M;
            Memory.insert(Ite, Piece);               //������
            cout << "SUCCESS!" << endl;
            Sleep(TIME / 2);
            break;
        }
    }
    if ( Ite == Memory.end() )
        cout << "�ռ䲻�㣬����ʧ��" << endl;
}

                    /*****ѭ���״���Ӧ�㷨����ÿ�δ��ϴε���һ�����з�������*****/
void Next_Fit()
{
    cout << "��������������ڴ��С" << endl;
    int R_M;
    R_M = GetSpace();                                //�������ռ��С
    cnt++;                                           //��ҵID����
    node Piece;                                      //�����������ڲ���
    list <node>::iterator Ite;                       //������
    for ( Ite = Buffer; Ite != Memory.end(); Ite++ )
    {
        if ( R_M <= (*Ite).space && !(*Ite).flag )   //�ҵ�δ����ķ����ҿռ��㹻
        {
            Piece.address = (*Ite).address;          //��������������
            Piece.flag = true;
            Piece.id = cnt;
            Piece.space = R_M;
            (*Ite).address += R_M;
            (*Ite).space -= R_M;
            Memory.insert(Ite, Piece);               //������
            cout << "SUCCESS" << endl;
            Buffer = Ite;
            Sleep(TIME / 2);
            break;
        }
    }
    if ( Ite == Memory.end() )
        cout << "�ռ䲻�㣬����ʧ��" << endl;
}

                            /*****�����Ӧ�㷨����ÿ������С*****/
void Best_Fit()
{
    cout << "��������������ڴ��С" << endl;
    int R_M;
    R_M = GetSpace();                                //�������ռ��С
    cnt++;                                           //��ҵID����
    node Piece;                                      //�����������ڲ���
    list <node>::iterator Ite;                       //������
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

    if ( flag && R_M <= (*Ans).space )                //�ҵ�δ����ķ����ҿռ��㹻
    {
        Piece.address = (*Ans).address;               //��������������
        Piece.flag = true;
        Piece.id = cnt;
        Piece.space = R_M;
        (*Ans).address += R_M;
        (*Ans).space -= R_M;
        Memory.insert(Ans, Piece);                    //������
        cout << "SUCCESS" << endl;
        Sleep(TIME / 2);
    }
    else
        cout << "�ռ䲻�㣬����ʧ��" << endl;
}

                           /*****���Ӧ�㷨����ÿ�������*****/
void Worst_Fit()
{
    cout << "��������������ڴ��С" << endl;
    int R_M;
    R_M = GetSpace();                                //�������ռ��С
    cnt++;                                           //��ҵID����
    node Piece;                                      //�����������ڲ���
    list <node>::iterator Ite;                       //������
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

    if ( flag && R_M <= (*Ans).space )               //�ҵ�δ����ķ����ҿռ��㹻
    {
        Piece.address = (*Ans).address;              //��������������
        Piece.flag = true;
        Piece.id = cnt;
        Piece.space = R_M;
        (*Ans).address += R_M;
        (*Ans).space -= R_M;
        Memory.insert(Ans, Piece);                   //������
        cout << "SUCCESS" << endl;
        Sleep(TIME / 2);
    }
    else
        cout << "�ռ䲻�㣬����ʧ��" << endl;
}

                                     /*****����ռ�*****/
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
            cout << "������������" << endl;
            continue;
        }
        if ( IntRM >= 10000)
        {
            cout << "���ֹ�������������" << endl;
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
/***************************���ߣ��߽��������༶���ƿ�1704����ѧ�ţ�17110581107****************************/
