#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

#define PLAYER_MAXHP 5
#define OBJ_DENSITY 35

int getRand(int size){
   return rand()%size;
}

//자료형 선언 시작

char tile[] = {' ', '#', '@', 'E'};
char enemy[] = {'A', 'B', 'C'};
char potion[] = {'H', 'S', 'V'};

#define GETTILE(N) ((N<10)?(tile[N]):(N<20?enemy[N-10]:potion[N-20]))

typedef enum mData{
   empty = 0, //빈 공간 0
   wall, //벽 1
   player, //플레이어 2
   exitTile, //탈출 타일 3
   e1 = 10, //적 남은 체력에 따라 10, 11, 12
   e2,
   e3,
   p1 = 20, //포션 종류에 따라 20, 21, 22
   p2,
   p3 
}mData;

typedef mData map10[10][10];
typedef struct Player{
   int x;
   int y;
   int atk;
   int def;
   int hp;
   int potions[3];
} Player;

//자료형 선언 끝

map10 curMap;
Player curPlayer;
int enemyCount = 0;

#define NUMBER_OF_PRESETS 4
mData presets[NUMBER_OF_PRESETS][4][4] = {{
   {0, 0, 0, 0},
   {0, 1, 1, 0},
   {0, 1, 1, 0},
   {0, 0, 0, 0}
},{
   {0, 1, 0, 0},
   {0, 1, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 1, 0}
},{
   {0, 0, 0, 0},
   {0, 1, 0, 0},
   {1, 0, 0, 0},
   {1, 0, 1, 0}
},{
   {1, 0, 0, 0},
   {0, 0, 1, 0},
   {0, 0, 0, 0},
   {0, 1, 1, 0}
}};

void makeMap(){
   for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
         curMap[i][j] = (i == 0 || i == 9 || j == 0 || j == 9)?wall:empty;
      }

      for(int i = 0; i < 2; i++){
         for(int j = 0; j < 2; j++){
            int persetNo = getRand(NUMBER_OF_PRESETS);
            for(int x = 0; x < 4; x++){
               for(int y = 0; y < 4; y++){
                  curMap[1+i*4+x][1+j*4+y] = presets[persetNo][x][y];
               }
            }
         }
      }
   }
}

void initMap(){
   int isPcCreated = 0;
   for(int i = 1; i < 9; i++){
      for(int j = 1; j < 9; j++){
         if(curMap[i][j] == 0 && isPcCreated == 0){
            isPcCreated = 1;
            curPlayer.x = i;
            curPlayer.y = j;
         }else{
            int rValue = getRand(OBJ_DENSITY);
            if(rValue < 3){
               curMap[i][j] = rValue + 10;
               enemyCount ++;
            }else if(rValue < 6){
               curMap[i][j] = rValue + 17;
            }
         }
      }
   }
   curMap[8][8] = exitTile;
}

void printMap(){
   for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
         if(curPlayer.x == i && curPlayer.y == j) printf("%c ",GETTILE(player));
         else printf("%c ",GETTILE(curMap[i][j]));
      }
      printf("\n");
   }
}

void printMapDbg(){
   for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
         printf("%02d ",curMap[i][j]);
      }
      printf("\n");
   }
}

void initPlayer(){
   curPlayer.atk = 1;
   curPlayer.def = 0;
   curPlayer.potions[0] = 0;
   curPlayer.potions[1] = 0;
   curPlayer.potions[2] = 0;
   curPlayer.hp = PLAYER_MAXHP;
}

void printPlayer(){
   printf("HP : ");
   for(int i = 0; i < curPlayer.hp; i++){
      printf("[H] ");
   }
   printf("\natk : %d | def : %d | enemy : %d\n",curPlayer.atk, curPlayer.def, enemyCount);
   printf("Potion: %d | %d | %d", curPlayer.potions[0],curPlayer.potions[1],curPlayer.potions[2]);
}

void printDisc(){
   printf("이동 : wasd, 포션 사용: 1 2 3\n");
   printf("입력해주세용....");
}

int procInput(char input){
   switch (input){
   case 'w':
   case 'a':
   case 's':
   case 'd':
      {
         int afterX = curPlayer.x;
         int afterY = curPlayer.y;
         if(input == 'w') afterX --;
         if(input == 's') afterX ++;
         if(input == 'a') afterY --;
         if(input == 'd') afterY ++;

         mData afterTile = curMap[afterX][afterY];

         switch (afterTile){
         case empty:
            curPlayer.x = afterX;
            curPlayer.y = afterY;
            break;
         case wall:
            break;
         case exitTile:
            if(enemyCount == 0)return -1;
            printf("적을 다 죽여야지!!\n");
            system("pause");
            break;

         case e1:
         case e2:
         case e3:
            printf("%d", curPlayer.atk);
            curMap[afterX][afterY] -= curPlayer.atk;
            if(curMap[afterX][afterY] < e1){
               curMap[afterX][afterY] = empty;
               enemyCount --;
            }
            break;

         case p1:
         case p2:
         case p3:
            curMap[afterX][afterY] = empty;
            curPlayer.potions[afterTile - 20] ++;
            break;
         default:
            printf("제대로 입력하세요 나빠!\n");
            system("pause");
            break;
         }
      }
      break;

   case '1':
      if(curPlayer.potions[0] < 1){
         printf("포션이 없어...");
         system("pause");
         break;
      }
      curPlayer.potions[0]--;
      curPlayer.hp = PLAYER_MAXHP;
      break;
   case '2':
      if(curPlayer.potions[1] < 1){
         printf("포션이 없어...");
         system("pause");
         break;
      }
      curPlayer.potions[1]--;
      curPlayer.hp -= 2;
      for(int i = -1; i <= 1; i++){
         for(int j = -1; j <= 1; j++){
            mData tile = curMap[curPlayer.x + i][curPlayer.y + j];
            switch (tile){
            case e1:
            case e2:
               curMap[curPlayer.x + i][curPlayer.y + j] = empty;
               break;
            case e3:
               curMap[curPlayer.x + i][curPlayer.x + j] = 10;
               break;
            default:
               break;
            }
         }
      }
      break;
   case '3':
      if(curPlayer.potions[2] < 1){
         printf("포션이 없어...");
         system("pause");
         break;
      }
      curPlayer.potions[2]--;
      if(getRand(2)){
         curPlayer.atk ++;
      }else{
         curPlayer.def ++;
      }
      break;
   default:
      printf("입력을 제대로 해 줘요!!!\n");
         system("pause");
      break;
   }
   return 0;
}

int main() {
   char input;
   int result;

   srand(time(NULL));
   makeMap();
   initMap();
   initPlayer();
   //printMapDbg();
   while(TRUE){
      system("cls");
      printMap();
      printPlayer();
      printDisc();
      scanf(" %c",&input);
      result = procInput(input);
      if(result == -1) break;
   }
   system("cls");
   printf("공주는 다른 성에 있어!");
   return 0;
}