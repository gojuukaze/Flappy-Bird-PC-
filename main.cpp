/***************************************************************

*
版权所有 (C)2014, 五十风

* 

*
文件名称：main.cpp

*
内容摘要：FlappyBird主函数文件

*
其它说明：无

*
当前版本：v1.2

*
作    者：五十风

*
完成日期：2014.11.4

*
代替版本：v1.1

*
原作者： 五十风

*
原版完成日期：2014.10.18


* 

*
修改记录1：  
*   
修改日期：2014.11.4

*   
版本号：v1.2

*   
修改人：五十风

*   
修改内容：1.修改了main函数
		  2.加入宏定义#pragma

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

* 功能描述：主函数

* 输入参数：int argc,char*args[]

* 输出参数：无	

* 返回值：0

* 其它说明：无

* 修改日期      版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.11.4      V1.2           五十风           修改openfile函数的名称为firsttime，
                                                 把load函数放到firsttime前面，
												 load函数，firsttime函数增加了返回值，返回bool类型的值，改回false退出程序。

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