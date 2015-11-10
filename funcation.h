/***************************************************************

*
版权所有 (C)2014, 五十风

* 

*
文件名称：function.h

*
内容摘要：FlappyBird用到的类以及函数

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
修改内容：1.修改openfile函数，并改名为firsttime
		  2.在加载错误的判断语句中加入弹窗提示。
		  3.修改Score函数
		  4.修改Button类
		  5.加入localeToUTF8函数用于字符的转码
		  6.修改Die函数
***************************************************************/


/**********************************************************************

* 类描述：贴图类，用于设置显示贴图，获取贴图种类

* 其它说明：无

* 修改日期      版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
class Tile
{
private:
    SDL_Rect box;
    int type;
public:
    Tile( int x, int y, int tileType );
    void show();
    int get_type();
    SDL_Rect get_box();
};
/**********************************************************************

* 类描述：鸟类，用于控制鸟的飞行

* 其它说明：无

* 修改日期      版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
* 2014.10.30      V1.1           五十风           增加变量ishit用于记录是否按下按键。

***********************************************************************/
class Bird
{
private:
    SDL_Rect box;
    int yVel,xVel;
	SDL_Rect dotbox;
	bool ishit;
public:
    Bird();
    void handle_input();
    void move(Tile *tiles[]);
    void show();
	void set_camera();
};
/**********************************************************************

* 类描述：按钮类，用于设置按钮，检测按钮是否按下

* 其它说明：无

* 修改日期      版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.11.4       V1.2           五十风           修改构造函数，并增加了重载的构造函数

***********************************************************************/
class Button
{
private:
    SDL_Rect box;
	SDL_Surface* button;
	
public:
	bool isdown_button;//是否按下按钮
	Button(SDL_Rect);
    Button(SDL_Rect ,SDL_Surface*);
    void handle_events();
    void show();
};

/**********************************************************************

* 功能描述：生成随机地图文件

* 输入参数：无

* 输出参数：无

* 返回值：0

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void builtmap()
{
	std::ofstream fout("map.map");
	if(fout==NULL)
	{
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 04-1"),TEXT("错误！"),MB_OK);
		return;
	}
	int a;
	double b,c;
	srand(unsigned(time(0)));
	for(int i=0;i<20;i++)
	{
		b=(0+(4-0)*rand()/(RAND_MAX+1.0));
		c=(0+(20-0)*rand()/(RAND_MAX+1.0));
		a=(int)b*c;
		a=a%4;
		fout<<0;
		fout<<a;
		fout<<" ";
		fout<<0<<8;
		fout<<" ";
		switch(a)
		{
		case 0:a=4;break;
		case 1:a=5;break;
		case 2:a=6;break;
		case 3:a=7;break;
		}
		fout<<0;
		fout<<a;
		fout<<" ";
		fout<<"\n";
	}
	fout.clear();
	fout.close();
}
/**********************************************************************

* 功能描述：用于字符编码转换

* 输入参数：char *src

* 输出参数：无

* 返回值：buf

* 其它说明：

*原作者：bombless（博客园网名）

*创建日期： 2010-11-21

*网址：http://www.cnblogs.com/bombless/archive/2010/11/21/SDL-using-chinese-character.html
***********************************************************************/
char *localeToUTF8(char *src)
{
    static char *buf = NULL;
    if(buf)
	{
        free(buf);
        buf = NULL;
    }
    wchar_t *unicode_buf;
    int nRetLen = MultiByteToWideChar(CP_ACP,0,src,-1,NULL,0);
    unicode_buf = (wchar_t*)malloc((nRetLen+1)*sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP,0,src,-1,unicode_buf,nRetLen);
    nRetLen = WideCharToMultiByte(CP_UTF8,0,unicode_buf,-1,NULL,0,NULL,NULL);
    buf = (char*)malloc(nRetLen+1);
    WideCharToMultiByte(CP_UTF8,0,unicode_buf,-1,buf,nRetLen,NULL,NULL);
    free(unicode_buf);
    return buf;
}
/**********************************************************************

* 功能描述：初始化sdl

* 输入参数：无

* 输出参数：无

* 返回值：true

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
* 2014.11.4       V1.2           五十风           加入MessageBox函数
***********************************************************************/
bool init()
{ 
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
    {	
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 01-1"),TEXT("错误！"),MB_OK);
		return false;    
	}  
    screen=SDL_SetVideoMode(screen_w,screen_h,32,SDL_SWSURFACE);
    if(screen==NULL)
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 02"),TEXT("错误！"),MB_OK);
		return false;
	}
	if(TTF_Init()==-1)
	{
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 01-2"),TEXT("错误！"),MB_OK);
		return false;
	}
	SDL_WM_SetCaption(localeToUTF8("flappy bird v1.2 by:五十风"), NULL );
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{			
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 01-3"),TEXT("错误！"),MB_OK);
		return false; 
	}
    return true;
}

/**********************************************************************

* 功能描述：优化图片

* 输入参数：std::string name

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
***********************************************************************/
SDL_Surface *load_image(std::string name)
{
	SDL_Surface *loadedimage=NULL;
	SDL_Surface *optimizedimage=NULL;
	loadedimage=IMG_Load(name.c_str());
	if(loadedimage)
	{
		optimizedimage = SDL_DisplayFormat( loadedimage );
        SDL_FreeSurface( loadedimage );
		if(optimizedimage!=NULL )
        {
            
            Uint32 colorkey=SDL_MapRGB(optimizedimage->format,0xFE,0xFE,0xFE);
			SDL_SetColorKey(optimizedimage,SDL_SRCCOLORKEY,colorkey);
		}
    }     
    return optimizedimage; 
}
/**********************************************************************

* 功能描述：加载图片、字体、音乐

* 输入参数：无

* 输出参数：无

* 返回值：true

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           添加tips,font2加载的内容

* 2014.11.4       V1.2           五十风           添加button_lift,button_right,button_soundon,button_soundoff加载的内容
                                                  添加MessageBox函数

***********************************************************************/
bool load_files()
{
	//图片
    pipe_blank=load_image("pic/tiles.png" );
	bird=load_image("pic/bird.png" );
	title=load_image("pic/title.png" );
	background=load_image("pic/background.png" );
	button_start = load_image( "pic/start.png" );
	scorepic=load_image("pic/score.png" );
	highpic = load_image( "pic/high.png" );
	engineer=load_image( "pic/engineer.png" );
	tips=load_image( "pic/tips.png" );
	button_lift=load_image( "pic/2.png" );
	button_right=load_image( "pic/1.png" );
	button_soundon=load_image( "pic/soundon.png" );
	button_soundoff=load_image( "pic/soundoff.png" );
	if(background==NULL || bird==NULL || pipe_blank==NULL || title==NULL)
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}
	if(button_start==NULL || button_lift==NULL || button_right==NULL)
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}
	if(scorepic==NULL )
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}
	if(highpic==NULL )
	{
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}
	if(engineer==NULL )
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}
	if(tips==NULL || button_soundoff==NULL || button_soundon==NULL)
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}

	//声效
	pu=Mix_LoadWAV("sound/pu.wav");;
	dingdong= Mix_LoadWAV("sound/dingdong.wav");
	pa= Mix_LoadWAV( "sound/pa.wav" );

	if( (dingdong== NULL ) || (pa == NULL )|| (pu == NULL ))
	{
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-2"),TEXT("错误！"),MB_OK);
		return false; 
	}

	//字体
	font = TTF_OpenFont("font/segoeprb.ttf",30);
	font2 = TTF_OpenFont("font/segoeprb.ttf",15);
	fontcn_tip= TTF_OpenFont(localeToUTF8("font/ygyxsziti.ttf"),15);
	fontcn_easy=TTF_OpenFont(localeToUTF8("font/ygyxsziti.ttf"),25);
	if( font == NULL || font2 == NULL || (fontcn_tip == NULL ) || (fontcn_easy == NULL))
    { 
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-3"),TEXT("错误！"),MB_OK);
		return false;
	}


    return true;
}
/**********************************************************************

* 功能描述：加载图片到屏幕

* 输入参数：int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           输入参数增加SDL_Rect* clip
                                                  修改SDL_BlitSurface的参数
***********************************************************************/
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip = NULL)
{ 
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;   
    SDL_BlitSurface(source,clip,destination,&offset);
}

/**********************************************************************

* 功能描述：释放sdl

* 输入参数：Tile *tiles[]

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           输入参数增加Tile *tiles[]
                                                  增加释放tips，font2变量
***********************************************************************/
void clean_up(Tile *tiles[])
{
	//图片
    SDL_FreeSurface(background);
    SDL_FreeSurface(bird);	
	SDL_FreeSurface(pipe_blank);
	SDL_FreeSurface(first1);
	SDL_FreeSurface(first2);
	SDL_FreeSurface(first3);

	SDL_FreeSurface(title);
	SDL_FreeSurface(tips);
	SDL_FreeSurface(message);
	SDL_FreeSurface(thetip);
	SDL_FreeSurface(thescore);
	SDL_FreeSurface(thehelp);
	SDL_FreeSurface(theranking);
	
	SDL_FreeSurface(button_start);
	SDL_FreeSurface(button_lift);
	SDL_FreeSurface(button_right);
	SDL_FreeSurface(button_soundoff);
	SDL_FreeSurface(button_soundon);
	for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete tiles[ t ];
    }	
	//音乐
	Mix_FreeChunk(dingdong);
	Mix_FreeChunk(pa);
	Mix_FreeChunk(pu);
	Mix_CloseAudio();
	//字体
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_CloseFont(fontcn_tip);
	TTF_CloseFont(fontcn_easy);
    SDL_Quit();
}

/**********************************************************************

* 功能描述：检测a,b是否方式碰撞

* 输入参数：SDL_Rect A, SDL_Rect B

* 输出参数：无

* 返回值：true,false

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
bool check_collision( SDL_Rect A, SDL_Rect B )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if( bottomA <= topB )
    {
        return false;
    }
    if( topA >= bottomB )
    {
        return false;
    }
    if( rightA <= leftB )
    {
        return false;
    }
    if( leftA >= rightB )
    {
        return false;
    }
    return true;
}
/**********************************************************************

* 功能描述：检测鸟是否到达得线

* 输入参数：SDL_Rect A

* 输出参数：无

* 返回值：true,false

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
bool check_score(SDL_Rect A)
{
    int rightA;
    rightA = A.x+A.w;
    if(rightA>=scoreline)
    {
		scoreline+=200;
        return true;
    }
    return false;
}
/**********************************************************************

* 功能描述：剪切贴图

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void clip_tiles()
{
   
    clips[ top1 ].x = 0;
    clips[ top1 ].y = 207;
    clips[ top1 ].w = 59;
    clips[ top1 ].h = 290;

    clips[ btm1 ].x = 99;
    clips[ btm1 ].y = 0;
    clips[ btm1 ].w = 59;
    clips[ btm1 ].h = 270;

	clips[ top2 ].x = 0;
    clips[ top2 ].y = 327;
    clips[ top2 ].w = 59;
    clips[ top2 ].h = 150;

    clips[ btm2 ].x = 99;
    clips[ btm2 ].y = 0;
    clips[ btm2 ].w = 59;
    clips[ btm2 ].h = 390;

	clips[ top3 ].x = 0;
    clips[ top3 ].y = 87;
    clips[ top3 ].w = 59;
    clips[ top3 ].h = 390;

    clips[ btm3 ].x = 99;
    clips[ btm3 ].y = 0;
    clips[ btm3 ].w = 59;
    clips[ btm3 ].h = 150;

	clips[ top4 ].x = 0;
    clips[ top4 ].y = 117;
    clips[ top4 ].w = 59;
    clips[ top4 ].h = 360;

    clips[ btm4 ].x = 99;
    clips[ btm4 ].y = 0;
    clips[ btm4 ].w = 59;
    clips[ btm4 ].h = 180;

    clips[ blank ].x = 198;
    clips[ blank ].y = 100;
    clips[ blank ].w = 59;
    clips[ blank ].h = 120;

}
/**********************************************************************

* 功能描述：根据贴图种类，返回空白盒子的y坐标

* 输入参数：int tileType

* 输出参数：无

* 返回值：y坐标

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
int tile_type(int tileType)
{
	if(tileType==0)
		return top1_h; 
	if(	tileType==1)
		return top2_h;
	if(	tileType==2)
		return top3_h;
	if(	tileType==3)
		return top4_h;
}
/**********************************************************************

* 功能描述：设置地图

* 输入参数：Tile *tiles[]

* 输出参数：无

* 返回值：true,false

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.18      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           添加MessageBox函数
***********************************************************************/
bool set_tiles( Tile *tiles[] )
{
    int x = 300, y = 0;
	int yy;
    std::ifstream map( "map.map" );
    if( map == NULL )
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 04-2"),TEXT("错误！"),MB_OK);
        return false;
    }
    //地图
    for( int t = 0; t < TOTAL_TILES;  )
    {
        int tileType = -1;
        map >> tileType;
        if( map.fail() == true )
        {
            map.close();
            return false;
        }
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
			yy=tile_type(tileType);
            tiles[ t ] = new Tile( x, y, tileType );
        }
		t++;
        
		map >> tileType;
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y+yy, tileType );
        }
			t++;
		map >> tileType;
		if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y+yy+blank_h, tileType );
        }
			t++;
			x+=200;
    }
    map.close();
    return true;
}
/**********************************************************************

* 功能描述：检测是否碰到管道

* 输入参数：SDL_Rect box, Tile *tiles[]

* 输出参数：无

* 返回值：true,false

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
bool touches_wall( SDL_Rect box, Tile *tiles[] )
{
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
       
        if( ( tiles[ t ]->get_type() >= top1 ) && ( tiles[ t ]->get_type() <= btm4 ) )
        {
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
				type=tiles[ t ]->get_type();
                return true;
            }
        }
    }
    return false;
}

/**********************************************************************

* 功能描述：根据柱子类型返回柱子的高

* 输入参数：int type

* 输出参数：无

* 返回值：柱子高

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
int Box_h(int type)
{
	if(type==0)
		return top1_h; 
	if(	type==1)
		return top2_h;
	if(type==2)
		return top3_h;
	if(type==3)
		return top4_h;

	if(type==4)
		return btm1_h; 
	if(type==5)
		return btm2_h;
	if(type==6)
		return btm3_h;
	if(type==7)
		return btm4_h;

	if(type==8)
		return blank_h;


}
/**********************************************************************

* 功能描述：初始化贴图类

* 输入参数：int x, int y, int tileType

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
Tile::Tile( int x, int y, int tileType )
{
    box.x = x;
    box.y = y;
	type = tileType;

    box.w = 78;
    box.h =Box_h(type);
}
/**********************************************************************

* 功能描述：根据相机位置显示柱子

* 输入参数：int x, int y, int tileType

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void Tile::show()
{
    if( check_collision( camera, box ) == true)
    {
        apply_surface( box.x - camera.x, box.y - camera.y, pipe_blank, screen, &clips[ type ] );
    }
}

/**********************************************************************

* 功能描述：返回柱子类型

* 输入参数：无

* 输出参数：无

* 返回值：type

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
int Tile::get_type()
{
    return type;
}
/**********************************************************************

* 功能描述：返回柱子的坐标，宽高

* 输入参数：无

* 输出参数：无

* 返回值：box

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
SDL_Rect Tile::get_box()
{
    return box;
}
/**********************************************************************

* 功能描述：初始化鸟的坐标，宽高，x,y轴速度，相机点的坐标，宽高，以及ishit=0。

* 输入参数：无

* 输出参数：无

* 返回值：box

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           加入对ishit的初始化

***********************************************************************/
Bird::Bird()
{
    box.x=100;
    box.y=300;
	box.w=bird_w;
	box.h=bird_h;

	dotbox.x=0;
    dotbox.y=0;
	dotbox.w=bird_w;
	dotbox.h=bird_h;    
	
	yVel =0;
	xVel =3;
	ishit=0;
}
/**********************************************************************

* 功能描述：根据按下的按键调整yVel

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
* 2014.10.30      V1.1           五十风           加入对ishit的赋值，按键被按下则ishit=1。
* 2014.11.4       V1.2           五十风           修改yVel的赋值，用于控制难度

***********************************************************************/
void Bird::handle_input()
{
	ishit=0;
    if( event.type == SDL_KEYDOWN )
    {

       if(event.key.keysym.sym ==SDLK_SPACE)
        {             
			yVel=-16+easy;
			ishit=1; 
			if(issound)
				if( Mix_PlayChannel(-1,pu,0)==-1)
				{
						return;    
				}

        }
    }
    else 
	{
		if( ishit==0 )
		{ 
			 yVel=10-easy;    
		}
	}
	
}
/**********************************************************************

* 功能描述：根据按下的按键调整yVel

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
* 2014.10.30      V1.1           五十风           加入对ishit的判断，等于1则yVel不做变化
* 2014.11.4       V1.2           五十风           修改ishit的判断下的yVel的赋值，用于控制难度
* 2014.11.20      V1.2           五十风           修改碰到柱子后对box.y的调整
***********************************************************************/
void Bird::move(Tile *tiles[])
{
	if( ishit==0 )
	{ 
			yVel=10-easy;    
	}
	box.y+=yVel;
	box.x+=xVel;
	dotbox.x+=xVel;	
	
	if(check_score(box)==true)
	{
		score+=5;
		if(issound)
			if( Mix_PlayChannel(-1,dingdong,0)==-1)
			{
				return;    
			}
	}
    if( ( box.y < 0 ) || ( box.y +bird_h>screen_h)|| touches_wall( box, tiles ) )
    {
		if(type>=top1 && type<=top4)
			box.y=clips[type].h-easy;
		else
			box.y=screen_h-clips[type].h-bird_h+easy;
		die=true;
		if(issound)
			if( Mix_PlayChannel(-1,pa,0)==-1)
			{
				return;    
			}
        
    }
	if( ( box.x < 0 ) || ( box.x +bird_w>LEVEL_WIDTH) || touches_wall( box, tiles ))
    {
		box.x -= 3;
		die=true;
		if(issound)
			if( Mix_PlayChannel(-1,pa,0)==-1)
			{
				return;    
			}
        
    }
	if(  (dotbox.x < 0 ) || ( dotbox.x +bird_w>LEVEL_WIDTH))
    {
        dotbox.x -= xVel;
    }


}
/**********************************************************************

* 功能描述：显示鸟

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void Bird::show()
{
    apply_surface( box.x - camera.x, box.y - camera.y,bird,screen);
}
/**********************************************************************

* 功能描述：根据电的位置移动相机

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void Bird::set_camera()
{

    camera.x =dotbox.x;
    camera.y =0;

    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
}
/**********************************************************************

* 功能描述：初始化按钮盒子

* 输入参数：SDL_Rect b

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
* 2014.11.4       V1.2           五十风           加入对isdown_button的初始化

***********************************************************************/
Button::Button(SDL_Rect b)
{
	isdown_button=false;
    box.x = b.x;
    box.y = b.y;
    box.w = b.w;
    box.h = b.h;
}
/**********************************************************************

* 功能描述：初始化按钮盒子

* 输入参数：SDL_Rect b,SDL_Surface* mybutton

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.11.4      V1.2           五十风           创建

***********************************************************************/
Button::Button(SDL_Rect b,SDL_Surface* mybutton)
{
	button=mybutton;
	isdown_button=false;
    box.x = b.x;
    box.y = b.y;
    box.w = b.w;
    box.h = b.h;
}
/**********************************************************************

* 功能描述：判断是否点击按钮

* 输入参数：SDL_Rect b

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建
* 2014.11.4       V1.2           五十风           点击按钮isdown_button=1

***********************************************************************/
void Button::handle_events()
{   
    int x = 0, y = 0;
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x;
            y = event.button.y;
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
				isdown_button=true;
            }
        }
    }
  
}
/**********************************************************************

* 功能描述：显示按钮

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void Button::show()
{
    apply_surface(box.x, box.y,button,screen);
}
/**********************************************************************

* 功能描述：加载游戏

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
bool load()
{

	if(init()==false )
    {
		return false;
	}
	if( load_files() == false )
    {
        return false;
	}
	clip_tiles();	
	
	return true;
}
/**********************************************************************

* 功能描述：滚动背景

* 输入参数：无

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

***********************************************************************/
void ScrollingBackground()
{		
	
	bgX -= 4;        
    if( bgX <= -background->w )
    { 
		bgX = 0;
    }	
	apply_surface( bgX, bgY, background, screen );
    apply_surface( bgX + background->w, bgY, background, screen );
}

/**********************************************************************

* 功能描述：首次运行显示操作提示

* 输入参数：无

* 输出参数：无

* 返回值：true false

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.30      V1.1           五十风           创建
* 2014.11.4       V1.2           五十风           修改函数名，增加了图片提示的显示，增加了highest文件的修改

***********************************************************************/
bool firsttime()
{
	int t=0;
	std::ifstream fin( "highest.dat" );
    if( fin == NULL )
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 04-3"),TEXT("错误！"),MB_OK);
        return false;
    }
	int t1,t2,t3,t4;
	fin>>t1;
	fin>>t2;
	fin>>t3;
	fin>>t4;
	fin.clear();
	fin.close();
	std::ofstream fout("highest.dat");
	if( fout == NULL )
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 04-3"),TEXT("错误！"),MB_OK);
        return false;
    }
	fout<<t1;
	fout<<" ";
	fout<<t2;
	fout<<" ";
	fout<<t3;
	fout<<" ";
	fout<<1;
	fout<<" ";
	fout.clear();
	fout.close();
	if(t4==0)
	{
		
		first1=IMG_Load("pic/first1.png" );
		first2=IMG_Load("pic/first2.png" );
		first3=IMG_Load("pic/first3.png" );
			if(first3==NULL )
    {
		MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 03-1"),TEXT("错误！"),MB_OK);
		return false;
	}
		while(1)
		{
			if( SDL_PollEvent( &event ))
			{
				if( event.type == SDL_MOUSEBUTTONDOWN )
					if( event.button.
						button == SDL_BUTTON_LEFT )
						t++;
				if( event.type == SDL_QUIT )	
					 return false;
			}
			if(t==0)
				apply_surface(0,0,first1,screen);
			if(t==1)
				apply_surface(0,0,first2,screen);
			if(t==2)
				apply_surface(0,0,first3,screen);
			if(t==3)
				return true;
			if( SDL_Flip(screen)==-1)//更新
			{
				MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 05"),TEXT("错误！"),MB_OK);
				 return false;
			}
			SDL_Delay(30);
				 
		}

	}
	return true;

}

/**********************************************************************

* 功能描述：菜单

* 输入参数：无

* 输出参数：无

* 返回值：true false

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.11.4      V1.2           五十风           增加新添按钮的显示，增加MessageBox函数

***********************************************************************/
bool menu()
{
	bgX = 0;
	bgY = 0;	
	while(start==false)
	{
		startTicks = SDL_GetTicks();
		ScrollingBackground();

		Button start_button(startbox,button_start);
		Button lift_button(liftbox,button_lift);
		Button right_button(rightbox,button_right);
		Button soundon_button(soundbox,button_soundon);
		Button soundoff_button(soundbox,button_soundoff);
		Button help_button(helpbox);
		Button ranking_button(rankingbox);
		start_button.show();
		lift_button.show();
		right_button.show();
		if(issound)
			soundon_button.show();
		else
			soundoff_button.show();
		apply_surface(170,150,title,screen);
		apply_surface(410,628,engineer,screen);
		if(iseasy==false)
			theeasy=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("困难"),textColor);
		else
			theeasy=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("简单"),textColor);

		thehelp=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("说明"),textColor);
		theranking=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("高分榜"),textColor);

		apply_surface(240,310,theeasy,screen);
		apply_surface(150,500,thehelp,screen);
		apply_surface(320,500,theranking,screen);
		if( SDL_Flip(screen)==-1)
		 {
			MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 05"),TEXT("错误！"),MB_OK);
			 return true;
		 }
		startTicks = SDL_GetTicks()-startTicks;
		if( startTicks< 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay(( 1000 / FRAMES_PER_SECOND ) -startTicks);
		 }

		if( SDL_PollEvent( &event ) )
        {
            start_button.handle_events();
			lift_button.handle_events();
			right_button.handle_events();
			help_button.handle_events();
			ranking_button.handle_events();
			if(issound)
				soundon_button.handle_events();
			else
				soundoff_button.handle_events();
			
			if(start_button.isdown_button==true)
				start=true;
			if(lift_button.isdown_button==true || right_button.isdown_button==true)
				iseasy=!iseasy;
			if(soundon_button.isdown_button==true || soundoff_button.isdown_button==true)
				issound=!issound;
			if(help_button.isdown_button==true)
				ShellExecute(NULL,"open","说明.txt",NULL,NULL,SW_SHOW);
			if(ranking_button.isdown_button==true)
			{
				ShellExecute(NULL,"open","高分榜.txt",NULL,NULL,SW_SHOW);
			}

            if( event.type == SDL_QUIT )
            {	

                return true;
            }
        }
	}
	bgX = 0;
	bgY = 0;
	return false;
}
/**********************************************************************

* 功能描述：更新最高分榜

* 输入参数：int a,int b

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.11.4      V1.2           五十风           创建

***********************************************************************/
void updateranking(int a,int b)
{
	std::ofstream fout( "高分榜.txt" );
	fout<<"第一名";
	fout<<" ";
	fout<<score;
	fout<<"\n";
	fout<<"第二名";
	fout<<" ";
	fout<<a;
	fout<<"\n";
	fout<<"第三名";
	fout<<" ";
	fout<<b;
	fout<<"\n";
	
	fout.close();
}
/**********************************************************************

* 功能描述：死亡后计算得分，并显示得分界面

* 输入参数：int t

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           加入图片tips的显示

* 2014.11.4      V1.2           五十风           加入新加文字的显示，
												  加入p键截图功能，
												  更改highest文件的读取修改内容
												  加入updateranking函数


***********************************************************************/
void Score(int t)
{
//	int b=-1;
	std::stringstream s;
	s<<score;	
	if(t==0)
	{
		std::ifstream fin( "highest.dat" );

		if( fin == NULL)
		{
			MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 04-3"),TEXT("错误！"),MB_OK);
			  return;
		}	
		fin>>scorea;
		fin>>scoreb;
		fin.close();
	}
	
	if(scorea<score)
	{
		if(t==0)
		{
			std::ofstream fout( "highest.dat" );
			fout<<score;
			fout<<" ";
			fout<<scorea;
			fout<<" ";
			fout<<scoreb;
			fout<<" ";
			fout<<1;
			fout<<" ";
			fout.close();
		}
		apply_surface(120,200,highpic,screen);
		updateranking(scorea,scoreb);
	}
	else
	{
		apply_surface(120,200,scorepic,screen);

	}
	apply_surface(96,380,tips,screen);
	message= TTF_RenderText_Solid( font, s.str().c_str(), textColor );
	thetip= TTF_RenderUTF8_Solid(fontcn_tip,localeToUTF8("小提示: 按住“空格”可以一直上升"),textColor2);
	apply_surface(240,290,message,screen);
	apply_surface(0,0,thetip,screen);
}
/**********************************************************************

* 功能描述：更新最高分榜

* 输入参数：Bird mybird,Tile *tiles[TOTAL_TILES]

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.10.30      V1.1           五十风           修改mybird.move(tiles);
												  加入mybird.set_camera()函数

* 2014.11.4      V1.2           五十风           加入对iseasy的判断，用于难度控制

***********************************************************************/

void play(Bird mybird,Tile *tiles[ TOTAL_TILES ])
{
	if(iseasy)
		easy=3;
	else
		easy=1;

	builtmap();
	if( set_tiles(tiles)==false)
    {
        return ;
    }
	while(die==false)
	{
		while(SDL_PollEvent(&event))
        {
			if( event.type == SDL_QUIT )
            {
                quit=true;
				return;
            }  
			mybird.handle_input();	 			 
        }
		ScrollingBackground();
		mybird.move(tiles);
		mybird.set_camera();
		for( int t = 0; t < TOTAL_TILES; t++ )
        {
            tiles[ t ]->show();
        }
		mybird.show();
		std::stringstream s;
		s<<"scores: "<<score;
		thescore=TTF_RenderText_Solid(font2,s.str().c_str(),textColor2);
		apply_surface(460,0,thescore,screen);
  		if( SDL_Flip(screen)==-1)//更新
        {
			MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 05"),TEXT("错误！"),MB_OK);
            return;
        }
		SDL_Delay(35);
	}

}
/**********************************************************************

* 功能描述：更新最高分榜

* 输入参数：Bird mybird,Tile *tiles[TOTAL_TILES]

* 输出参数：无

* 返回值：无

* 其它说明：无

* 修改日期       版本号          修改人           修改内容

*--------------------------------------------------------------------

* 2014.10.19      V1.0           五十风           创建

* 2014.11.4      V1.2           五十风           去除temp变量，加入对scorea，scoreb的赋值

***********************************************************************/
void Die()
{
	bgX = 0;
	bgY = 0;
	int t;
	t=0;
	scorea=scoreb=-1;
	while(die==true)
	{	
		ScrollingBackground();
		Score(t);		
		while(SDL_PollEvent(&event))
		{

			if( event.type == SDL_QUIT )
			{
				 quit=true;	
				 return;
			}  
			if( event.type == SDL_KEYDOWN )
			{
				if(event.key.keysym.sym==SDLK_r)
				{                 
					die=false;
				}
				if(event.key.keysym.sym==SDLK_ESCAPE)
				{             
					start=false;
					showmenu=true;
					die=false;
				}
				if(event.key.keysym.sym==SDLK_p)
				{  
					SDL_SaveBMP(screen,"SavePic.bmp") ;
					MessageBox(NULL,TEXT("图片已保存到游戏目录"),TEXT("保存成功"),MB_OK);
				}
			}				
		}
		if( SDL_Flip(screen)==-1)//更新
		{
			MessageBox(NULL,TEXT("糟糕，游戏发生了错误。\n错误: 05"),TEXT("错误！"),MB_OK);
			return;
		}
		SDL_Delay(35);
		t=1;
	}
}