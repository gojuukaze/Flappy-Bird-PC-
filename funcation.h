/***************************************************************

*
��Ȩ���� (C)2014, ��ʮ��

* 

*
�ļ����ƣ�function.h

*
����ժҪ��FlappyBird�õ������Լ�����

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
�޸����ݣ�1.�޸�openfile������������Ϊfirsttime
		  2.�ڼ��ش�����ж�����м��뵯����ʾ��
		  3.�޸�Score����
		  4.�޸�Button��
		  5.����localeToUTF8���������ַ���ת��
		  6.�޸�Die����
***************************************************************/


/**********************************************************************

* ����������ͼ�࣬����������ʾ��ͼ����ȡ��ͼ����

* ����˵������

* �޸�����      �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* �����������࣬���ڿ�����ķ���

* ����˵������

* �޸�����      �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
* 2014.10.30      V1.1           ��ʮ��           ���ӱ���ishit���ڼ�¼�Ƿ��°�����

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

* ����������ť�࣬�������ð�ť����ⰴť�Ƿ���

* ����˵������

* �޸�����      �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.11.4       V1.2           ��ʮ��           �޸Ĺ��캯���������������صĹ��캯��

***********************************************************************/
class Button
{
private:
    SDL_Rect box;
	SDL_Surface* button;
	
public:
	bool isdown_button;//�Ƿ��°�ť
	Button(SDL_Rect);
    Button(SDL_Rect ,SDL_Surface*);
    void handle_events();
    void show();
};

/**********************************************************************

* �������������������ͼ�ļ�

* �����������

* �����������

* ����ֵ��0

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

***********************************************************************/
void builtmap()
{
	std::ofstream fout("map.map");
	if(fout==NULL)
	{
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 04-1"),TEXT("����"),MB_OK);
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

* ���������������ַ�����ת��

* ���������char *src

* �����������

* ����ֵ��buf

* ����˵����

*ԭ���ߣ�bombless������԰������

*�������ڣ� 2010-11-21

*��ַ��http://www.cnblogs.com/bombless/archive/2010/11/21/SDL-using-chinese-character.html
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

* ������������ʼ��sdl

* �����������

* �����������

* ����ֵ��true

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
* 2014.11.4       V1.2           ��ʮ��           ����MessageBox����
***********************************************************************/
bool init()
{ 
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
    {	
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 01-1"),TEXT("����"),MB_OK);
		return false;    
	}  
    screen=SDL_SetVideoMode(screen_w,screen_h,32,SDL_SWSURFACE);
    if(screen==NULL)
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 02"),TEXT("����"),MB_OK);
		return false;
	}
	if(TTF_Init()==-1)
	{
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 01-2"),TEXT("����"),MB_OK);
		return false;
	}
	SDL_WM_SetCaption(localeToUTF8("flappy bird v1.2 by:��ʮ��"), NULL );
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{			
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 01-3"),TEXT("����"),MB_OK);
		return false; 
	}
    return true;
}

/**********************************************************************

* �����������Ż�ͼƬ

* ���������std::string name

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
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

* ��������������ͼƬ�����塢����

* �����������

* �����������

* ����ֵ��true

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           ���tips,font2���ص�����

* 2014.11.4       V1.2           ��ʮ��           ���button_lift,button_right,button_soundon,button_soundoff���ص�����
                                                  ���MessageBox����

***********************************************************************/
bool load_files()
{
	//ͼƬ
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
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
		return false;
	}
	if(button_start==NULL || button_lift==NULL || button_right==NULL)
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
		return false;
	}
	if(scorepic==NULL )
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
		return false;
	}
	if(highpic==NULL )
	{
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
		return false;
	}
	if(engineer==NULL )
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
		return false;
	}
	if(tips==NULL || button_soundoff==NULL || button_soundon==NULL)
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
		return false;
	}

	//��Ч
	pu=Mix_LoadWAV("sound/pu.wav");;
	dingdong= Mix_LoadWAV("sound/dingdong.wav");
	pa= Mix_LoadWAV( "sound/pa.wav" );

	if( (dingdong== NULL ) || (pa == NULL )|| (pu == NULL ))
	{
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-2"),TEXT("����"),MB_OK);
		return false; 
	}

	//����
	font = TTF_OpenFont("font/segoeprb.ttf",30);
	font2 = TTF_OpenFont("font/segoeprb.ttf",15);
	fontcn_tip= TTF_OpenFont(localeToUTF8("font/ygyxsziti.ttf"),15);
	fontcn_easy=TTF_OpenFont(localeToUTF8("font/ygyxsziti.ttf"),25);
	if( font == NULL || font2 == NULL || (fontcn_tip == NULL ) || (fontcn_easy == NULL))
    { 
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-3"),TEXT("����"),MB_OK);
		return false;
	}


    return true;
}
/**********************************************************************

* ��������������ͼƬ����Ļ

* ���������int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           �����������SDL_Rect* clip
                                                  �޸�SDL_BlitSurface�Ĳ���
***********************************************************************/
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip = NULL)
{ 
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;   
    SDL_BlitSurface(source,clip,destination,&offset);
}

/**********************************************************************

* �����������ͷ�sdl

* ���������Tile *tiles[]

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           �����������Tile *tiles[]
                                                  �����ͷ�tips��font2����
***********************************************************************/
void clean_up(Tile *tiles[])
{
	//ͼƬ
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
	//����
	Mix_FreeChunk(dingdong);
	Mix_FreeChunk(pa);
	Mix_FreeChunk(pu);
	Mix_CloseAudio();
	//����
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_CloseFont(fontcn_tip);
	TTF_CloseFont(fontcn_easy);
    SDL_Quit();
}

/**********************************************************************

* �������������a,b�Ƿ�ʽ��ײ

* ���������SDL_Rect A, SDL_Rect B

* �����������

* ����ֵ��true,false

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ����������������Ƿ񵽴����

* ���������SDL_Rect A

* �����������

* ����ֵ��true,false

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ����������������ͼ

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ����������������ͼ���࣬���ؿհ׺��ӵ�y����

* ���������int tileType

* �����������

* ����ֵ��y����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* �������������õ�ͼ

* ���������Tile *tiles[]

* �����������

* ����ֵ��true,false

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.18      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           ���MessageBox����
***********************************************************************/
bool set_tiles( Tile *tiles[] )
{
    int x = 300, y = 0;
	int yy;
    std::ifstream map( "map.map" );
    if( map == NULL )
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 04-2"),TEXT("����"),MB_OK);
        return false;
    }
    //��ͼ
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

* ��������������Ƿ������ܵ�

* ���������SDL_Rect box, Tile *tiles[]

* �����������

* ����ֵ��true,false

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ���������������������ͷ������ӵĸ�

* ���������int type

* �����������

* ����ֵ�����Ӹ�

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ������������ʼ����ͼ��

* ���������int x, int y, int tileType

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* �����������������λ����ʾ����

* ���������int x, int y, int tileType

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

***********************************************************************/
void Tile::show()
{
    if( check_collision( camera, box ) == true)
    {
        apply_surface( box.x - camera.x, box.y - camera.y, pipe_blank, screen, &clips[ type ] );
    }
}

/**********************************************************************

* ����������������������

* �����������

* �����������

* ����ֵ��type

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

***********************************************************************/
int Tile::get_type()
{
    return type;
}
/**********************************************************************

* �����������������ӵ����꣬���

* �����������

* �����������

* ����ֵ��box

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

***********************************************************************/
SDL_Rect Tile::get_box()
{
    return box;
}
/**********************************************************************

* ������������ʼ��������꣬��ߣ�x,y���ٶȣ����������꣬��ߣ��Լ�ishit=0��

* �����������

* �����������

* ����ֵ��box

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           �����ishit�ĳ�ʼ��

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

* �������������ݰ��µİ�������yVel

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
* 2014.10.30      V1.1           ��ʮ��           �����ishit�ĸ�ֵ��������������ishit=1��
* 2014.11.4       V1.2           ��ʮ��           �޸�yVel�ĸ�ֵ�����ڿ����Ѷ�

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

* �������������ݰ��µİ�������yVel

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
* 2014.10.30      V1.1           ��ʮ��           �����ishit���жϣ�����1��yVel�����仯
* 2014.11.4       V1.2           ��ʮ��           �޸�ishit���ж��µ�yVel�ĸ�ֵ�����ڿ����Ѷ�
* 2014.11.20      V1.2           ��ʮ��           �޸��������Ӻ��box.y�ĵ���
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

* ������������ʾ��

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

***********************************************************************/
void Bird::show()
{
    apply_surface( box.x - camera.x, box.y - camera.y,bird,screen);
}
/**********************************************************************

* �������������ݵ��λ���ƶ����

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ������������ʼ����ť����

* ���������SDL_Rect b

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
* 2014.11.4       V1.2           ��ʮ��           �����isdown_button�ĳ�ʼ��

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

* ������������ʼ����ť����

* ���������SDL_Rect b,SDL_Surface* mybutton

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.11.4      V1.2           ��ʮ��           ����

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

* �����������ж��Ƿ�����ť

* ���������SDL_Rect b

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����
* 2014.11.4       V1.2           ��ʮ��           �����ťisdown_button=1

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

* ������������ʾ��ť

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

***********************************************************************/
void Button::show()
{
    apply_surface(box.x, box.y,button,screen);
}
/**********************************************************************

* ����������������Ϸ

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* ������������������

* �����������

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

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

* �����������״�������ʾ������ʾ

* �����������

* �����������

* ����ֵ��true false

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.30      V1.1           ��ʮ��           ����
* 2014.11.4       V1.2           ��ʮ��           �޸ĺ�������������ͼƬ��ʾ����ʾ��������highest�ļ����޸�

***********************************************************************/
bool firsttime()
{
	int t=0;
	std::ifstream fin( "highest.dat" );
    if( fin == NULL )
    {
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 04-3"),TEXT("����"),MB_OK);
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
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 04-3"),TEXT("����"),MB_OK);
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
		MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 03-1"),TEXT("����"),MB_OK);
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
			if( SDL_Flip(screen)==-1)//����
			{
				MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 05"),TEXT("����"),MB_OK);
				 return false;
			}
			SDL_Delay(30);
				 
		}

	}
	return true;

}

/**********************************************************************

* �����������˵�

* �����������

* �����������

* ����ֵ��true false

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.11.4      V1.2           ��ʮ��           ��������ť����ʾ������MessageBox����

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
			theeasy=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("����"),textColor);
		else
			theeasy=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("��"),textColor);

		thehelp=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("˵��"),textColor);
		theranking=TTF_RenderUTF8_Solid(fontcn_easy,localeToUTF8("�߷ְ�"),textColor);

		apply_surface(240,310,theeasy,screen);
		apply_surface(150,500,thehelp,screen);
		apply_surface(320,500,theranking,screen);
		if( SDL_Flip(screen)==-1)
		 {
			MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 05"),TEXT("����"),MB_OK);
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
				ShellExecute(NULL,"open","˵��.txt",NULL,NULL,SW_SHOW);
			if(ranking_button.isdown_button==true)
			{
				ShellExecute(NULL,"open","�߷ְ�.txt",NULL,NULL,SW_SHOW);
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

* ����������������߷ְ�

* ���������int a,int b

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.11.4      V1.2           ��ʮ��           ����

***********************************************************************/
void updateranking(int a,int b)
{
	std::ofstream fout( "�߷ְ�.txt" );
	fout<<"��һ��";
	fout<<" ";
	fout<<score;
	fout<<"\n";
	fout<<"�ڶ���";
	fout<<" ";
	fout<<a;
	fout<<"\n";
	fout<<"������";
	fout<<" ";
	fout<<b;
	fout<<"\n";
	
	fout.close();
}
/**********************************************************************

* �������������������÷֣�����ʾ�÷ֽ���

* ���������int t

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           ����ͼƬtips����ʾ

* 2014.11.4      V1.2           ��ʮ��           �����¼����ֵ���ʾ��
												  ����p����ͼ���ܣ�
												  ����highest�ļ��Ķ�ȡ�޸�����
												  ����updateranking����


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
			MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 04-3"),TEXT("����"),MB_OK);
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
	thetip= TTF_RenderUTF8_Solid(fontcn_tip,localeToUTF8("С��ʾ: ��ס���ո񡱿���һֱ����"),textColor2);
	apply_surface(240,290,message,screen);
	apply_surface(0,0,thetip,screen);
}
/**********************************************************************

* ����������������߷ְ�

* ���������Bird mybird,Tile *tiles[TOTAL_TILES]

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.10.30      V1.1           ��ʮ��           �޸�mybird.move(tiles);
												  ����mybird.set_camera()����

* 2014.11.4      V1.2           ��ʮ��           �����iseasy���жϣ������Ѷȿ���

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
  		if( SDL_Flip(screen)==-1)//����
        {
			MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 05"),TEXT("����"),MB_OK);
            return;
        }
		SDL_Delay(35);
	}

}
/**********************************************************************

* ����������������߷ְ�

* ���������Bird mybird,Tile *tiles[TOTAL_TILES]

* �����������

* ����ֵ����

* ����˵������

* �޸�����       �汾��          �޸���           �޸�����

*--------------------------------------------------------------------

* 2014.10.19      V1.0           ��ʮ��           ����

* 2014.11.4      V1.2           ��ʮ��           ȥ��temp�����������scorea��scoreb�ĸ�ֵ

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
					MessageBox(NULL,TEXT("ͼƬ�ѱ��浽��ϷĿ¼"),TEXT("����ɹ�"),MB_OK);
				}
			}				
		}
		if( SDL_Flip(screen)==-1)//����
		{
			MessageBox(NULL,TEXT("��⣬��Ϸ�����˴���\n����: 05"),TEXT("����"),MB_OK);
			return;
		}
		SDL_Delay(35);
		t=1;
	}
}