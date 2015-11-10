/***************************************************************

*
版权所有 (C)2014, 五十风

* 

*
文件名称：head.h

*
内容摘要：定义用到的全局变量

*
其它说明：

*
当前版本：v1.2

*
作    者：五十风

*
完成日期：2014.11.14

*
代替版本：v1.1

*
原作者： 五十风

*
原版完成日期：2014.10.18
*


修改记录1：  

*   
修改日期：2014.11.4

*   
版本号：v1.2

*   
修改人：五十风

*   
修改内容：1.加入变量first1，first2，first3用于加载提示图片
		  2.加入变量button_lift，button_right用于调节难度
		  3.加入变量button_soundon，button_soundoff=NULL用于显示静音按钮
		  4.加入变量startbox,liftbox,rightbox,soundbox,helpbox,rankingbox用于设置按钮的位置
		  5.加入变量fontcn_tip，theeasy 用于加载字体
		  6.加入变量thehelp，theranking，thetip，theeasy 用于显示帮助，高分榜，小提示，难度的文字
		  7.加入变量iseasy，easy用于记录难度，以及调节当前难度下鸟的飞行高度
		  7.用变量scorea,scoreb替代了temp用于从文件读取分数

*
修改记录2：  

*   
修改日期：2014.11.18

*   
版本号：v1.2

*   
修改人：五十风

*   
修改内容：1.加入变量type。
***************************************************************/

//图
SDL_Surface *tips=NULL;
SDL_Surface *title=NULL;
SDL_Surface *background=NULL;
SDL_Surface *bird=NULL;
SDL_Surface *pipe_blank=NULL;//管道和空白盒子
SDL_Surface *screen=NULL;
SDL_Surface *scorepic=NULL;
SDL_Surface *highpic=NULL;
SDL_Surface *engineer=NULL;
SDL_Surface *first1=NULL;
SDL_Surface *first2=NULL;
SDL_Surface *first3=NULL;

//按钮
SDL_Surface *button_start = NULL;
SDL_Surface *button_lift = NULL;
SDL_Surface *button_right = NULL;
SDL_Surface *button_soundon=NULL;
SDL_Surface *button_soundoff=NULL;
SDL_Rect startbox={187,350,166,100};
SDL_Rect liftbox={205,310,22,30};
SDL_Rect rightbox={310,311,22,30};
SDL_Rect soundbox={0,630,30,30};
SDL_Rect helpbox={150,500,40,30};
SDL_Rect rankingbox={320,500,50,30};

int startTicks=0;//计时器
const int FRAMES_PER_SECOND = 18;//帧频率

const int screen_h=660;
const int screen_w=540;
const int bird_w=40;
const int bird_h=30;
const int LEVEL_WIDTH=3580;
const int LEVEL_HEIGHT=660;

Mix_Chunk *pu = NULL;//声效“噗”
Mix_Chunk *dingdong= NULL;	//声效“叮咚”
Mix_Chunk *pa = NULL;//声效“啪”

//字体
TTF_Font *font = NULL;
TTF_Font *font2 = NULL;
TTF_Font *fontcn_tip = NULL;
TTF_Font *fontcn_easy = NULL;
SDL_Color textColor={91,64,75};
SDL_Color textColor2={0,0,0};
//字表面
SDL_Surface *message = NULL;//用于显示最终得分
SDL_Surface *thescore = NULL;//在游戏中显示得分
SDL_Surface *thetip = NULL;//小提示
SDL_Surface *theeasy = NULL;
SDL_Surface *thehelp = NULL;
SDL_Surface *theranking = NULL;

//地图相关
//第1种管道的上、下管道的宽、高
const int top1_w = 59;
const int top1_h = 270;
const int btm1_w = 59;
const int btm1_h = 270;
//第2种管道的上、下管道的宽、高
const int top2_w = 59;
const int top2_h = 150;
const int btm2_w = 59;
const int btm2_h = 390;
//第3种管道的上、下管道的宽、高
const int top3_w = 59;
const int top3_h = 390;
const int btm3_w = 59;
const int btm3_h = 150;
//第4种管道的上、下管道的宽、高
const int top4_w = 59;
const int top4_h = 360;
const int btm4_w = 59;
const int btm4_h = 180;
//空白盒子的宽、高
const int blank_w = 59;
const int blank_h = 120;

const int TOTAL_TILES = 60;//用到的贴图数量
const int TILE_SPRITES = 9;//贴图种类数量
//给贴图标号
const int top1= 0;
const int top2 = 1;
const int top3 = 2;
const int top4 = 3;
const int btm1 = 4;
const int btm2 = 5;
const int btm3 = 6;
const int btm4 = 7;
const int blank = 8;

SDL_Rect clips[ TILE_SPRITES ];//剪切的图

SDL_Rect camera = {0,0,screen_w, screen_h};//相机

SDL_Event event;//事件体

bool start=false;	
bool quit=false;

bool iseasy=false;//难度
int easy=1;//调整鸟的飞行高度
bool issound=true;//打开音乐

int bgX = 0, bgY = 0;//背景坐标
int score=0;
bool die=false;
bool showmenu=true;
int scorea,scoreb;
int scoreline=359;

int type;//管道的类型