/***************************************************************

*
��Ȩ���� (C)2014, ��ʮ��

* 

*
�ļ����ƣ�main.cpp

*
����ժҪ��FlappyBird�������ļ�

*
����˵������

*
��ǰ�汾��v1.2

*
��    �ߣ���ʮ��

*
������ڣ�2014.11.4

*
����汾��v1.1

*
ԭ���ߣ� ��ʮ��

*
ԭ��������ڣ�2014.10.18


* 

*
�޸ļ�¼1��  
*   
�޸����ڣ�2014.11.4

*   
�汾�ţ�v1.2

*   
�޸��ˣ���ʮ��

*   
�޸����ݣ�1.�޸���main����
		  2.����궨��#pragma

***************************************************************/

#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include<string>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<ctime>
#include<windows.h>
#include "resource.h"
#include"variable.h"
#include"funcation.h"

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

Bird mybird;
Tile *tiles[ TOTAL_TILES ];

/**********************************************************************

* ����������������

* ���������int argc,char*args[]

* �����������	

* ����ֵ��0

* ����˵������

* �޸�����      �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.11.4      V1.2           ��ʮ��           �޸�openfile����������Ϊfirsttime��
                                                 ��load�����ŵ�firsttimeǰ�棬
												 load������firsttime���������˷���ֵ������bool���͵�ֵ���Ļ�false�˳�����

***********************************************************************/
int main(int argc,char*args[])
{	

	if(load()==false)
		return 0;
	if(firsttime()==false)
		return 0;
	while(quit==false)
    {		
		if(showmenu==true)
		{	
			quit=menu();		
			showmenu=false;
		}
		if(die==false && quit==false)
		{play(mybird,tiles);}
		if(die==true && quit==false)
		{
			Die();
			score=0;
			scoreline=359;
		}
    }
	clean_up(tiles);
	return 0;
}