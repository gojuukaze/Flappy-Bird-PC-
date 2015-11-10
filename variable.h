/***************************************************************

*
��Ȩ���� (C)2014, ��ʮ��

* 

*
�ļ����ƣ�head.h

*
����ժҪ�������õ���ȫ�ֱ���

*
����˵����

*
��ǰ�汾��v1.2

*
��    �ߣ���ʮ��

*
������ڣ�2014.11.14

*
����汾��v1.1

*
ԭ���ߣ� ��ʮ��

*
ԭ��������ڣ�2014.10.18
*


�޸ļ�¼1��  

*   
�޸����ڣ�2014.11.4

*   
�汾�ţ�v1.2

*   
�޸��ˣ���ʮ��

*   
�޸����ݣ�1.�������first1��first2��first3���ڼ�����ʾͼƬ
		  2.�������button_lift��button_right���ڵ����Ѷ�
		  3.�������button_soundon��button_soundoff=NULL������ʾ������ť
		  4.�������startbox,liftbox,rightbox,soundbox,helpbox,rankingbox�������ð�ť��λ��
		  5.�������fontcn_tip��theeasy ���ڼ�������
		  6.�������thehelp��theranking��thetip��theeasy ������ʾ�������߷ְ�С��ʾ���Ѷȵ�����
		  7.�������iseasy��easy���ڼ�¼�Ѷȣ��Լ����ڵ�ǰ�Ѷ�����ķ��и߶�
		  7.�ñ���scorea,scoreb�����temp���ڴ��ļ���ȡ����

*
�޸ļ�¼2��  

*   
�޸����ڣ�2014.11.18

*   
�汾�ţ�v1.2

*   
�޸��ˣ���ʮ��

*   
�޸����ݣ�1.�������type��
***************************************************************/

//ͼ
SDL_Surface *tips=NULL;
SDL_Surface *title=NULL;
SDL_Surface *background=NULL;
SDL_Surface *bird=NULL;
SDL_Surface *pipe_blank=NULL;//�ܵ��Ϳհ׺���
SDL_Surface *screen=NULL;
SDL_Surface *scorepic=NULL;
SDL_Surface *highpic=NULL;
SDL_Surface *engineer=NULL;
SDL_Surface *first1=NULL;
SDL_Surface *first2=NULL;
SDL_Surface *first3=NULL;

//��ť
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

int startTicks=0;//��ʱ��
const int FRAMES_PER_SECOND = 18;//֡Ƶ��

const int screen_h=660;
const int screen_w=540;
const int bird_w=40;
const int bird_h=30;
const int LEVEL_WIDTH=3580;
const int LEVEL_HEIGHT=660;

Mix_Chunk *pu = NULL;//��Ч���ۡ�
Mix_Chunk *dingdong= NULL;	//��Ч�����ˡ�
Mix_Chunk *pa = NULL;//��Ч��ž��

//����
TTF_Font *font = NULL;
TTF_Font *font2 = NULL;
TTF_Font *fontcn_tip = NULL;
TTF_Font *fontcn_easy = NULL;
SDL_Color textColor={91,64,75};
SDL_Color textColor2={0,0,0};
//�ֱ���
SDL_Surface *message = NULL;//������ʾ���յ÷�
SDL_Surface *thescore = NULL;//����Ϸ����ʾ�÷�
SDL_Surface *thetip = NULL;//С��ʾ
SDL_Surface *theeasy = NULL;
SDL_Surface *thehelp = NULL;
SDL_Surface *theranking = NULL;

//��ͼ���
//��1�ֹܵ����ϡ��¹ܵ��Ŀ���
const int top1_w = 59;
const int top1_h = 270;
const int btm1_w = 59;
const int btm1_h = 270;
//��2�ֹܵ����ϡ��¹ܵ��Ŀ���
const int top2_w = 59;
const int top2_h = 150;
const int btm2_w = 59;
const int btm2_h = 390;
//��3�ֹܵ����ϡ��¹ܵ��Ŀ���
const int top3_w = 59;
const int top3_h = 390;
const int btm3_w = 59;
const int btm3_h = 150;
//��4�ֹܵ����ϡ��¹ܵ��Ŀ���
const int top4_w = 59;
const int top4_h = 360;
const int btm4_w = 59;
const int btm4_h = 180;
//�հ׺��ӵĿ���
const int blank_w = 59;
const int blank_h = 120;

const int TOTAL_TILES = 60;//�õ�����ͼ����
const int TILE_SPRITES = 9;//��ͼ��������
//����ͼ���
const int top1= 0;
const int top2 = 1;
const int top3 = 2;
const int top4 = 3;
const int btm1 = 4;
const int btm2 = 5;
const int btm3 = 6;
const int btm4 = 7;
const int blank = 8;

SDL_Rect clips[ TILE_SPRITES ];//���е�ͼ

SDL_Rect camera = {0,0,screen_w, screen_h};//���

SDL_Event event;//�¼���

bool start=false;	
bool quit=false;

bool iseasy=false;//�Ѷ�
int easy=1;//������ķ��и߶�
bool issound=true;//������

int bgX = 0, bgY = 0;//��������
int score=0;
bool die=false;
bool showmenu=true;
int scorea,scoreb;
int scoreline=359;

int type;//�ܵ�������