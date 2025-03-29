
#include "iGraphics.h"
#include<windows.h>
#include<mmsystem.h>
#include<string.h>

int x = 300, y = 300, r = 15;
int dy_1 = 16,dy_2 = 18;
int henX=0;
int eggX[3]= {55,55,55};
int eggY[3]= {586,580,586};

int basket_x =30,basket_y=20;
int show_crack[3] = {0};
int crack_pos[] = {0};
char egg_file[][30]= {"normal_egg.bmp","normal_egg.bmp","egg_blu.bmp","normal_egg.bmp","golden_egg.bmp","normal_egg.bmp","Poop_white.bmp"};
char crack_file[][30]= {"eggc_nor.bmp","eggc_nor.bmp","eggc_b.bmp","eggc_nor.bmp","eggc_go.bmp","eggc_nor.bmp","poop_try.bmp"};

int n=0,m=1;
int score = 0,flagn ,flagm,flag1,flag2;
char t[20]= "1:00";
char s[20] ="0";
int fixed_time;
char bonus[20]= "0";
int sec =0, mn=1;

int input_name = 0;

int perk_x = 55,perk_y = 768,p,perk =0;
int perk_ara[3] = {0};

void timer();
void egg_move();
void hen_move();
void perk_move();
void perk_fall();

//show_different_page
int show_home = 1,show_play = 0,show_score = 0,show_help = 0,show_sound = 0;
int duration = 0;
int res = 1,new_game = 1;
int snd = 1,flag_start = 1,flag_poop,flag_catch,flag_miss;
int home_sound = 1;

int s_time = 0;
char str[100], str2[100];
int len =0;
int mode =0;

int lvl_1 =1,lvl_2=0,lvl_3 =0;
char  sco[20]="0";


typedef struct{
    char name[60];
    int point;
}player_1;
player_1 pl_1[10];

typedef struct{
    char name[60];
    int point;
}player_2;
player_2 pl_2[10];

typedef struct{
    char name[60];
    int point;
}player_3;
player_3 pl_3[10];

void resume()
{
    FILE *fp;
    fp = fopen("resume.txt","rb");
    fread(&dy_1,sizeof(dy_1),1,fp);
    fread(&dy_2,sizeof(dy_2),1,fp);
    fread(&eggX[0],sizeof(eggX[0]),1,fp);
    fread(&eggX[1],sizeof(eggX[1]),1,fp);
    fread(&eggY[0],sizeof(eggY[0]),1,fp);
    fread(&eggY[1],sizeof(eggY[1]),1,fp);
    fread(&henX,sizeof(henX),1,fp);
    fread(&basket_x,sizeof(basket_x),1,fp);
    fread(&n,sizeof(n),1,fp);
    fread(&m,sizeof(m),1,fp);
    fread(&score,sizeof(score),1,fp);
    fread(&sec,sizeof(sec),1,fp);
    fread(&mn,sizeof(mn),1,fp);
    fread(&perk_x,sizeof(perk_x),1,fp);
    fread(&perk_y,sizeof(perk_y),1,fp);
    fread(&perk,sizeof(perk),1,fp);
    fread(&s_time,sizeof(s_time),1,fp);
    fread(&fixed_time,sizeof(&fixed_time),1,fp);
    fread(&p,sizeof(p),1,fp);
    fclose(fp);
}

void pause()
{
     FILE *fp;
    fp = fopen("resume.txt","wb");
    fwrite(&dy_1,sizeof(dy_1),1,fp);
    fwrite(&dy_2,sizeof(dy_2),1,fp);
    fwrite(&henX,sizeof(henX),1,fp);
    fwrite(&basket_x,sizeof(basket_x),1,fp);
    fwrite(&eggX[0],sizeof(eggX[0]),1,fp);
     fwrite(&eggX[1],sizeof(eggX[1]),1,fp);
      fwrite(&eggY[0],sizeof(eggY[0]),1,fp);
       fwrite(&eggY[1],sizeof(eggY[1]),1,fp);
    fwrite(&n,sizeof(n),1,fp);
    fwrite(&m,sizeof(m),1,fp);
    fwrite(&score,sizeof(score),1,fp);
    fwrite(&sec,sizeof(sec),1,fp);
    fwrite(&mn,sizeof(mn),1,fp);
    fwrite(&perk_x,sizeof(perk_x),1,fp);
    fwrite(&perk_y,sizeof(perk_y),1,fp);
    fwrite(&perk,sizeof(perk),1,fp);
    fwrite(&s_time,sizeof(s_time),1,fp);
    fwrite(&fixed_time,sizeof(&fixed_time),1,fp);
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);

}

void sound()
{

     if(snd && flag_miss){
        PlaySound(TEXT("missing_egg#.WAV"), NULL, SND_ASYNC);
       snd =0;
       flag_miss = 0;
    }
    else if(snd && flag_catch){
        PlaySound(TEXT("falling#.WAV"), NULL, SND_ASYNC);
       snd =0;
       flag_catch = 0;
    }

}
void bonus_time()
{
    if(s_time!=0){
        s_time --;
    }
}
void name()

{
  iShowBMP(0,0,"play_bg2.bmp");
   iSetColor(177,234,71);
   iFilledRectangle(380,345,370,210);

   iSetColor(0,0,0);
   iRectangle(380,345,370,210);
   sprintf(s,"SCORE : %d",score);
   iText(450,480,s,GLUT_BITMAP_TIMES_ROMAN_24);
   iText(420,420,"ENTER YOUR NAME :",GLUT_BITMAP_TIMES_ROMAN_24);
   iSetColor(0,0,0);
   iRectangle(390,368,340,40);
   if(mode == 1)
	{
		iSetColor(0, 0, 0);
		iText(400, 378, str,GLUT_BITMAP_HELVETICA_18);

	}

	iSetColor(0,0,0);
	iText(390,200,"Click in the box to write name,press Enter to finish");

     if(mode== 2){
        //printf("WORKING\n");
       if( fixed_time == 2){
            //printf("NOT WORKING\n");
        FILE *fp =NULL;
        fp = fopen("store_1.txt","rb");
         int i,j;
        for(i=0;i<10;i++){
            fread(&pl_1[i],sizeof(pl_1[0]),1,fp);
        }
        fclose(fp);

        for(i=0;i<10;i++){
            if(score>pl_1[i].point){
                for( j=10;j>i;j--){
                    pl_1[j].point = pl_1[j-1].point;
                    strcpy( pl_1[j].name,pl_1[j-1].name );
                }
                pl_1[i].point = score;
                strcpy(pl_1[i].name,str2);
                fp = fopen("store_1.txt","wb");
                for(j =0;j<10;j++){
                    fwrite(&pl_1[j],sizeof(pl_1[0]),1,fp);
                }
                fclose(fp);
                break;
            }
        }
       }
       else if( fixed_time == 3){
            //printf("NOT WORKING\n");
        FILE *fp =NULL;
        fp = fopen("store_2.txt","rb");
         int i,j;
        for(i=0;i<10;i++){
            fread(&pl_2[i],sizeof(pl_2[0]),1,fp);
        }
        fclose(fp);

        for(i=0;i<10;i++){
            if(score>pl_2[i].point){
                for( j=10;j>i;j--){
                    pl_2[j].point = pl_2[j-1].point;
                    strcpy( pl_2[j].name,pl_2[j-1].name );
                }
                pl_2[i].point = score;
                strcpy(pl_2[i].name,str2);
                fp = fopen("store_2.txt","wb");
                for(j =0;j<10;j++){
                    fwrite(&pl_2[j],sizeof(pl_2[0]),1,fp);
                }
                fclose(fp);
                break;
            }
        }
       }
        else if( fixed_time == 5){
            //printf("NOT WORKING\n");
        FILE *fp =NULL;
        fp = fopen("store_3.txt","rb");
         int i,j;
        for(i=0;i<10;i++){
            fread(&pl_3[i],sizeof(pl_3[0]),1,fp);
        }
        fclose(fp);

        for(i=0;i<10;i++){
            if(score>pl_3[i].point){
                for( j=10;j>i;j--){
                    pl_3[j].point = pl_3[j-1].point;
                    strcpy( pl_3[j].name,pl_3[j-1].name );
                }
                pl_3[i].point = score;
                strcpy(pl_3[i].name,str2);
                fp = fopen("store_3.txt","wb");
                for(j =0;j<10;j++){
                    fwrite(&pl_3[j],sizeof(pl_3[0]),1,fp);
                }
                fclose(fp);
                break;
            }
        }
       }

     mode = 0;
     input_name =0;
     show_home =1;

	}




}
void print_score()
{
     iShowBMP(0,0,"duration.bmp");
    // if(fixed_time==2){
        iSetColor(249,191,0);
        iFilledRectangle(70,690,180,50);
        iSetColor(0,0,0);
        iRectangle(70,690,180,50);
        iSetColor(0,0,0);
        iText(90,706,"Home Page",GLUT_BITMAP_TIMES_ROMAN_24);
                 if(lvl_1){
                  FILE *fs;
                  fs=fopen("store_1.txt","rb");
                  int k,i;

                  for(k=0;k<10;k++)
                  {
                        fread(&pl_1[k],sizeof(pl_1[0]),1,fs);
                  }
                  fclose(fs);

                  iSetColor(38,48,21);
                  iFilledRectangle(255,656,320,50);
                  iSetColor(0,0,0);
                  iRectangle(255,656,320,50);

                   iSetColor(255,255,255);
                  iText(270,670,"DURATION : 2 MINUTE",GLUT_BITMAP_TIMES_ROMAN_24);

                  iSetColor(158,176,105);
                  iFilledRectangle(150,50,560,600);


                  iSetColor(0,0,0);
                  iRectangle(150,50,560,600);
                   iLine(150,600,710,600);
                   iLine(490,80,490,650);
                  iText(200,612,"NAME",GLUT_BITMAP_TIMES_ROMAN_24);
                   iText(520,612,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
                   int px1 = 200,py = 550,px2 =570;
                   for(i = 0;i<10;i++){
                         iText(px1,py,pl_1[i].name,GLUT_BITMAP_HELVETICA_18);
                          sprintf(sco,"%d",pl_1[i].point);
                          iText(px2,py,sco,GLUT_BITMAP_HELVETICA_18);
                          iLine(px1,py-10,690,py-10);
                          py -=50;
                   }
                   iSetColor(249,191,0);
                   iFilledRectangle(900,190,180,50);
                   iSetColor(0,0,0);
                   iRectangle(900,190,180,50);
                   iSetColor(0,0,0);
                   iText(920,200,"Next Page",GLUT_BITMAP_TIMES_ROMAN_24);
                 }
                 else if(lvl_2){
                  FILE *fs;
                  fs=fopen("store_2.txt","rb");
                  int k,i;

                  for(k=0;k<10;k++)
                  {
                        fread(&pl_2[k],sizeof(pl_2[0]),1,fs);
                  }
                  fclose(fs);
                  iSetColor(38,48,21);
                  iFilledRectangle(255,656,320,50);
                  iSetColor(0,0,0);
                  iRectangle(255,656,320,50);

                   iSetColor(255,255,255);
                  iText(270,670,"DURATION : 3 MINUTE",GLUT_BITMAP_TIMES_ROMAN_24);


                  iSetColor(158,176,105);
                  iFilledRectangle(150,50,560,600);


                  iSetColor(0,0,0);
                  iRectangle(150,50,560,600);
                   iLine(150,600,710,600);
                   iLine(490,80,490,650);
                  iText(200,612,"NAME",GLUT_BITMAP_TIMES_ROMAN_24);
                   iText(520,612,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
                   int px1 = 200,py = 550,px2 =570;
                   for(i = 0;i<10;i++){
                         iText(px1,py,pl_2[i].name,GLUT_BITMAP_HELVETICA_18);
                          sprintf(sco,"%d",pl_2[i].point);
                          iText(px2,py,sco,GLUT_BITMAP_HELVETICA_18);
                          iLine(px1,py-10,690,py-10);
                          py -=50;
                   }
                   iSetColor(249,191,0);
                   iFilledRectangle(900,190,180,50);
                   iSetColor(0,0,0);
                   iRectangle(900,190,180,50);
                   iSetColor(0,0,0);
                   iText(920,200,"Previous Page",GLUT_BITMAP_TIMES_ROMAN_24);

                   iSetColor(249,191,0);
                   iFilledRectangle(900,125,180,50);
                   iSetColor(0,0,0);
                   iRectangle(900,125,180,50);
                   iSetColor(0,0,0);
                   iText(920,135,"Next Page",GLUT_BITMAP_TIMES_ROMAN_24);

                 }
                 if(lvl_3){
                  FILE *fs;
                  fs=fopen("store_3.txt","rb");
                  int k,i;

                  for(k=0;k<10;k++)
                  {
                        fread(&pl_3[k],sizeof(pl_3[0]),1,fs);
                  }
                  fclose(fs);
                  iSetColor(38,48,21);
                  iFilledRectangle(255,656,320,50);
                  iSetColor(0,0,0);
                  iRectangle(255,656,320,50);

                   iSetColor(255,255,255);
                  iText(270,670,"DURATION : 5 MINUTE",GLUT_BITMAP_TIMES_ROMAN_24);


                  iSetColor(158,176,105);
                  iFilledRectangle(150,50,560,600);


                  iSetColor(0,0,0);
                  iRectangle(150,50,560,600);
                   iLine(150,600,710,600);
                   iLine(490,80,490,650);
                  iText(200,612,"NAME",GLUT_BITMAP_TIMES_ROMAN_24);
                   iText(520,612,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
                   int px1 = 200,py = 550,px2 =570;
                   for(i = 0;i<10;i++){
                         iText(px1,py,pl_3[i].name,GLUT_BITMAP_HELVETICA_18);
                          sprintf(sco,"%d",pl_3[i].point);
                          iText(px2,py,sco,GLUT_BITMAP_HELVETICA_18);
                          iLine(px1,py-10,690,py-10);
                          py -=50;
                   }
                   iSetColor(249,191,0);
                   iFilledRectangle(900,125,180,50);
                   iSetColor(0,0,0);
                   iRectangle(900,125,180,50);
                   iSetColor(0,0,0);
                   iText(920,135,"Previous Page",GLUT_BITMAP_TIMES_ROMAN_24);

                 }

}
void setting()
{
    iShowBMP(0,0,"duration.bmp");

         //iShowBMP(0,0,"home_page.bmp");
         iShowBMP2(220,40,"download.bmp",0xffffff);
          iShowBMP2(90,250,"billboard_2.BMP",0xffffff);


        iSetColor(249,118,0);
        iFilledRectangle(600,300,250,200);
        iSetColor(0,0,0);

        iLine(600,366,850,366);
         iLine(600,365,850,365);
        iLine(600,432,850,432);
         iLine(600,433,850,433);

          iSetColor(106,89,77);
        iFilledRectangle(600,433,250,69);

        iSetColor(0,0,0);

        iRectangle(600,433,250,70);
         iRectangle(601,434,248,68);
         iSetColor(0,0,0);
         iRectangle(600,300,250,200);
        iRectangle(601,301,248,198);
         iText(670,320,"Sound OFF",GLUT_BITMAP_TIMES_ROMAN_24);
         iSetColor(0,0,0);
         iText(670,386,"Sound ON",GLUT_BITMAP_TIMES_ROMAN_24);
         iSetColor(255,255,255);
         iText(658,453,"SOUND SETTING",GLUT_BITMAP_HELVETICA_18);
         iSetColor(0,0,0);

         iSetColor(12,244,244);
         iFilledRectangle(70,690,100,50);
         iSetColor(0,0,0);
        iRectangle(70,690,100,50);
        iSetColor(0,0,0);
         iText(90,706,"Back",GLUT_BITMAP_TIMES_ROMAN_24);


}
void help()
{
     iShowBMP(0,0,"duration.bmp");
     iSetColor(183,133,18);
     iFilledRectangle(200,120,850,580);
     iSetColor(0,0,0);
     iRectangle(200,120,850,580);
     iSetColor(0,0,0);
      iSetColor(12,244,244);
         iFilledRectangle(70,690,100,50);
         iSetColor(0,0,0);
        iRectangle(70,690,100,50);
        iSetColor(0,0,0);

         iText(90,706,"Back",GLUT_BITMAP_TIMES_ROMAN_24);


     iText(220,655,"-> Player can be able to play the game for a limited amount of time.One should",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,615,"gain as much point during this time.",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,575,"** GOLDEN EGG : 10 point",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,535,"** BLUE EGG : 5 point",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,495,"** NORMAL EGG : 1 point",GLUT_BITMAP_TIMES_ROMAN_24);

     iText(220,455,"** POOP : -10 point ",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,410,"-> Basket can be operated using both mouse & keyboard(left & right arrow",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,365,"-> Catching perks :",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,325,"** +speed: Increase the speed of egg falling ",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,285,"** -speed: Decrease the speed of egg falling",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,245,"** +10s: Bonus 10s",GLUT_BITMAP_TIMES_ROMAN_24);
     iText(220,205,"** 2.GOLDEN EGG: Bonus 20 point",GLUT_BITMAP_TIMES_ROMAN_24);
}
void show_duration()
{
    iShowBMP(0,0,"duration.bmp");

         //iShowBMP(0,0,"home_page.bmp");
         iShowBMP2(220,40,"download.bmp",0xffffff);
          iShowBMP2(90,250,"billboard_2.BMP",0xffffff);
        iSetColor(106,89,77);
        iFilledRectangle(600,500,250,70);
        iSetColor(0,0,0);
        iRectangle(600,500,250,70);
         iRectangle(601,501,248,68);
        iSetColor(255,255,255);
        iText(620,520,"Select Time Duration",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(233,123,47);
        iFilledRectangle(600,300,250,200);
        iSetColor(0,0,0);
        iRectangle(600,300,250,200);
        iRectangle(601,301,248,198);
        iLine(600,366,850,366);
         iLine(600,365,850,365);
        iLine(600,432,850,432);
         iLine(600,433,850,433);
         iSetColor(0,0,0);
         iText(670,320,"5 Minute",GLUT_BITMAP_TIMES_ROMAN_24);
         iText(670,386,"3 Minute",GLUT_BITMAP_TIMES_ROMAN_24);
         iText(670,453,"2 Minute",GLUT_BITMAP_TIMES_ROMAN_24);
         iSetColor(0,0,0);
        // iFilledCircle(850,432,5);
        // iFilledCircle(600,367,5);


}
void home_page()
{


    iShowBMP(0,0,"home_page.bmp");
    iShowBMP2(220,40,"download.bmp",0xffffff);
    iShowBMP2(1000,560,"play.bmp",0xffffff);
    iShowBMP2(1000,450,"resume.bmp",0xffffff);
    iShowBMP2(1000,335,"score.bmp",0xffffff);
    iShowBMP2(1000,230,"sound_final.bmp",0xffffff);
    iShowBMP2(1000,130,"help.bmp",0xffffff);
    iShowBMP2(1000,23,"exit.bmp",0xffffff);

    iShowBMP2(90,250,"billboard_2.BMP",0xffffff);
    iShowBMP2(40,500,"hen_up.BMP",0);
    iShowBMP2(700,120,"hen_middle_2.bmp",0);
    iShowBMP2(380,120,"hen_middle_2 - Copy.bmp",0);


}
void cnt1()
{
     if(flagn == 2 && flag1 ==1){
            score +=5;
            flag1 =0;
     }
     else if(flagn==4 && flag1==1){
                score +=10;
                flag1 =0;
     }
            else if(flagn==6 &&flag1==1){
                score-=10;
                flag1 = 0;
            }
            else if( (flagn == 0 || (flagn%2==1)) &&flag1==1 ){
                score++;
                flag1 =0;
            }
            else
                flag1= 0;
}
void cnt2()
{
     if(flagm == 2 && flag2 ==1){
            score +=5;
            flag2 =0;
     }
     else if(flagm==4 && flag2==1){
                score +=10;
                flag2 =0;
     }
            else if(flagm==6 &&flag2==1){
                score-=10;
                flag2 = 0;
            }
            /*else if((flagm == 0 || flagm == 1||flagm == 3||flagm == 5)&&flag2==1 ){
                score++;
                flag2=0;
            } */
               else if( (flagm == 0 || (flagm%2==1)) &&flag2==1 ){
                score++;
                flag2 =0;
            }
            else
                flag2=0;
}


void play_page()
{

    iShowBMP(0,0,"play_bg2.bmp");
    iSetColor(0,0,0);
    iLine(0,565,1400,565);
    iLine(0,566,1400,566);
    iLine(0,567,1400,567);
    iLine(0,568,1400,568);
    res = 0;
    //iFilledCircle(0,85,5);

        //iText()
   // }
     if(show_play){
     res= 0;
     sound();
    iShowBMP2(basket_x,30,"basket_2.bmp",0);
    if(eggY[0]>=110){
        iShowBMP2(eggX[0],eggY[0],egg_file[n],0xffffff);
         snd = 1;
    }
    else{
        if(eggX[0] <= basket_x+140 && eggX[0] >= basket_x){
             iShowBMP2(eggX[0],eggY[0],egg_file[n],0xffffff);
             flagn = n;
             flag_catch = 1;
        }
        else{
            iShowBMP2(eggX[0]-20,55,crack_file[n],0);
            flagn = -1;
            flag_miss = 1;
        }

       // printf("%d\n",n);
    }
    if(eggY[1]>=110){
        iShowBMP2(eggX[1],eggY[1],egg_file[m],0xffffff);
        snd =1;
    }
    else{
        if(eggX[1] <= basket_x+140 && eggX[1] >= basket_x ){
             iShowBMP2(eggX[1],eggY[1],egg_file[m],0xffffff);
             flagm = m;
             flag_catch =1;
        }
        else{
            iShowBMP2(eggX[1]-20,55,crack_file[m],0);
            flagm = -1;
            flag_miss =1;
        }
    }

    if(perk_y>=100){



        if(p==0){
                 iSetColor(224,130,64);
             iFilledRectangle(perk_x,perk_y,85,40);
         iSetColor(0,0,0);
           iText(perk_x+10,perk_y+10,"+Speed",GLUT_BITMAP_HELVETICA_18);
           iRectangle(perk_x,perk_y,85,40);
        }
        else if(p==1){
                iSetColor(184,224,96);
                 iFilledRectangle(perk_x,perk_y,80,40);
                  iSetColor(0,0,0);
           iText(perk_x+10,perk_y+10,"-Speed",GLUT_BITMAP_HELVETICA_18);
          iRectangle(perk_x,perk_y,80,40);
        }
        else if(p==3){
            iSetColor(200,160,136);
                 iFilledRectangle(perk_x,perk_y,60,40);
                  iSetColor(0,0,0);
                   iRectangle(perk_x,perk_y,60,40);

            iText(perk_x+10,perk_y+10,"2X",GLUT_BITMAP_HELVETICA_18);
            iSetColor(254,230,60);
            iFilledEllipse(perk_x+45,perk_y+20,8,11);
            iSetColor(0,0,0);
            iEllipse(perk_x+45,perk_y+20,8,11);

        }
        else if(p==2){
            iSetColor(221,79,129);
                 iFilledRectangle(perk_x,perk_y,55,40);
                  iSetColor(0,0,0);
            iText(perk_x+10,perk_y+10,"+10s",GLUT_BITMAP_HELVETICA_18);
        iRectangle(perk_x,perk_y,55,40);
        }

    }
     else {
            if(perk_x <= basket_x+90 && perk_x >= basket_x && p==0){
           //iSetColor(0,0,0);
            //iText(1000,300,"NOT Working",GLUT_BITMAP_HELVETICA_18);
            dy_1 = dy_1 +8;
             dy_2 = dy_2 +8;

             s_time = 10;
             bonus_time();


        }
      else if(perk_x <= basket_x+90 && perk_x >= basket_x && p==1)
     {
         // iSetColor(0,0,0);
           // iText(1000,300,"NOT Working",GLUT_BITMAP_HELVETICA_18);
           dy_1 = dy_1 -6;
             dy_2 = dy_2 -6;

               s_time = 10;
             bonus_time();

     }
     else if(perk_x <= basket_x+90 && perk_x >= basket_x && p==2){
             //iSetColor(0,0,0);
            //iText(1000,300,"NOT Working",GLUT_BITMAP_HELVETICA_18);
             sec = sec + 10;

     }
      else if(perk_x <= basket_x+90 && perk_x >= basket_x && p==3){
            // iSetColor(0,0,0);
            //iText(1000,300,"NOT Working",GLUT_BITMAP_HELVETICA_18);
             score = score + 20;

     }

     }
     if(s_time)
     {
          iSetColor(229,181,233);
      iFilledRectangle(1000,687,40,55);
      iSetColor(0,0,0);
       sprintf(bonus,"%d",s_time);
        iText(1015,705,bonus,GLUT_BITMAP_TIMES_ROMAN_24);

      iRectangle(1000,687,40,55);

     }

    cnt1();
    cnt2();
    iShowBMP2(henX,547,"FINAL_HEN.bmp",0);
    sprintf(t,"Time: %d : %02d",mn,sec);
  //  iText(50,100,t,GLUT_BITMAP_TIMES_ROMAN_24);
      iSetColor(120,248,255);
      iFilledRectangle(38,687,150,65);
      iSetColor(0,0,0);
      iRectangle(38,687,150,65);
      iText(50,700,t,GLUT_BITMAP_TIMES_ROMAN_24);
      sprintf(s,"Score : %d",score);
      iSetColor(120,248,255);
      iFilledRectangle(1167,687,150,55);
      iSetColor(0,0,0);
      iRectangle(1167,687,150,55);
      iText(1190,700,s,GLUT_BITMAP_TIMES_ROMAN_24);

      iSetColor(120,248,255);
      iFilledRectangle(1050,687,105,55);
      iSetColor(0,0,0);
      iText(1075,700,"Pause",GLUT_BITMAP_TIMES_ROMAN_24);
      iRectangle(1050,687,105,55);
      if(sec== 0 && mn == 0){
        show_play = 0;
        input_name = 1;
        //input_name = 1;
      }

    }


}

void iDraw()
{
    //place your drawing codes here
    iClear();

    if(show_home)
        home_page();
     if(show_play)
        play_page();

     if(duration)
            show_duration();
     if(show_sound)
                setting();
     if(input_name )
                name();
     if( show_score)
        print_score();
         if(show_help)
        help();

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    basket_x = mx;

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      if(show_home==1){
          PlaySound(TEXT("chicken_disco.WAV"), NULL, SND_LOOP|SND_ASYNC);
      if( mx <= 1235 && mx >= 1025 && my <= 748  && my >= 647){

            show_home = 0;
            //show_play = 1;
           // new_game = 1;
           score =0;
           duration = 1;

      }
     else  if( mx <= 1235 && mx >= 1025 && my <=642   && my >= 550){
            if(res==1){
                resume();
            }

            show_play = 1;
            show_home = 0;

            //resume = 1;
      }
    else if( mx <= 1235 && mx >= 1025 && my <= 549  && my >= 442){
            show_score = 1;
            show_home = 0;
      }
     else if( mx <= 1235 && mx >= 1025 && my <= 440  && my >= 342){
            show_sound = 1;
            show_home = 0;
      }
     else if( mx <= 1235 && mx >= 1025 && my <= 340  && my >= 232){
            show_help = 1;
            show_home = 0;
      }
     else if( mx <= 1235 && mx >= 1025 && my <= 230  && my >= 120){

            exit(0);
      }
    }
    else if(duration==1){
        if(mx <= 850 && mx >= 600 && my <= 366  && my >= 300){

            mn = 5;
            sec = 0;
            score = 0;
            duration = 0;
           // show_home = 0;
            show_play = 1;
            fixed_time = 5;

        }
        else if(mx <= 850 && mx >= 600 && my <= 432  && my >= 367){

                mn = 3;
            sec = 0;
            score = 0;
            duration = 0;
           // show_home = 0;
            show_play = 1;
             fixed_time = 3;

        }
        else if(mx <= 850 && mx >= 600 && my <= 500  && my >= 433){

                mn = 2;
            sec = 0;
            score = 0;
             duration = 0;

            show_play = 1;
             fixed_time = 2;


        }
    }
     else if(show_play==1){
        if(mx <= 1155 && mx >= 1050 && my <= 742  && my >= 687){
            res = 0;
            show_play = 0;
            show_home = 1;
            pause() ;
             PlaySound(TEXT("chicken_disco.WAV"), NULL, SND_LOOP|SND_ASYNC);
        }
       /* if(mx <= 1040 && mx >= 950 && my <= 742  && my >= 687){
            show_play = 0;
            show_home = 1;
        } */
    }
    else if(show_sound){
        if(mx <= 850 && mx >= 600 && my <= 366  && my >= 300){
            //show_sound = 0;
            //show_home = 1;
          PlaySound(TEXT("silence.WAV"), NULL, SND_LOOP|SND_ASYNC);

        }
        else if(mx <= 850 && mx >= 600 && my <= 432  && my >= 367){
            //show_sound = 0;
            //show_home = 1;
        PlaySound(TEXT("chicken_disco.WAV"), NULL, SND_LOOP|SND_ASYNC);
        }
         else if(mx <= 170 && mx >= 70 && my <= 740  && my >= 690){
            show_sound = 0;
            show_home = 1;

        }
    }
    else if(input_name){
        if(mx <= 730 && mx >= 390 && my <= 408  && my >= 368){
            mode = 1;
        }
    }
    else if(show_score){
            if(mx <= 250 && mx >= 70 && my <= 740  && my >= 690 ){
                    show_home = 1;
            show_score =0;

            }
            else if(mx <= 1080 && mx >= 900 && my <= 240  && my >= 190 && lvl_1){
                lvl_1 =0;
                lvl_2 = 1;

            }
          else if(mx <= 1080 && mx >= 900 && my <= 240  && my >= 190 && lvl_2){
                lvl_1 =1;
                lvl_2 = 0;

            }
             else if(mx <= 1080 && mx >= 900 && my <= 175  && my >= 125 && lvl_2){
                lvl_3 = 1;
                lvl_2 = 0;

            }
            else if(mx <= 1080 && mx >= 900 && my <= 175  && my >= 125 && lvl_3){
                lvl_3 = 0;
                lvl_2 = 1;

            }

    }
    else if(show_help){
        if(mx <= 170 && mx >= 70 && my <= 740  && my >= 690){
              show_help = 0;
              show_home = 1;
        }
    }

    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        x -= 5;
        y -= 5;
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    int i;
    if(input_name){

	if(mode == 1)
	{
        if(key == '\r')
		{
			mode = 2;
			strcpy(str2,str);
			printf("%s\n", str);
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}



    }
    if(key == 'q')
    {
        exit(0);
    }
    //place your codes for other keys here
}

/*	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key == GLUT_KEY_LEFT){

        basket_x -=30;
        if(basket_x<=0)
            basket_x = 0;
    }
    if(key == GLUT_KEY_RIGHT){
        basket_x += 30;
        if(basket_x>=1400-160)
           basket_x = 1400-190;
    }
    //place your codes for other keys here
}
/*void time()
{
    t--;
    if(t==0)
        exit(0);
} */
void timer()
{
    if(show_play){

    if(sec==0){
        sec = 60;
        mn --;

    }
    sec--;
    }

}
void perk_move()
{
    if(show_play){
        perk = rand()% 1250 ;
    }
}
void perk_fall()
{
    if(show_play){
        perk_y -= 15;
        if(perk_y<=80){
            perk_y  = 768;
            perk_x = perk + 70;
            p = rand()%4;
        }
    }
}
void hen_move()
{
    if(show_play){
    henX=rand()%1250;
    }
}
void egg_move()
{
    if(s_time==0){
        dy_1 = 14;
        dy_2 = 16;
    }
    eggY[0]-=dy_1;
    eggY[1]-=dy_2;
    if(eggY[0]<=80)
    {
        flag_start = 1;
        n=rand()%7;
        flag1=1;
        eggY[0]=586;
        eggX[0]=henX+55;
    }
    if(eggY[1]<=80)
    {
        m=rand()%7;
        flag2 =1;
        eggY[1]=580;
        eggX[1]=henX+55;
    }
}
int main()
{
    //place your own initialization codes here.

    iSetTimer(1000,timer);
    iSetTimer(800,hen_move);
    iSetTimer(2,egg_move);
    iSetTimer(10000,perk_move);
    iSetTimer(2,perk_fall);
    iSetTimer(1000,bonus_time);
    PlaySound(TEXT("chicken_disco.WAV"), NULL, SND_LOOP|SND_ASYNC);
    iInitialize(1400, 768, "Catch_The_Egg!");
    return 0;
}
