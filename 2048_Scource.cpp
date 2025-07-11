#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

class Game2048 {
private:
    const int exp2[19]= {0,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,9999};
    
    char a[6][6]={
        {18,18,18,18,18,18},
        {18, 0, 0, 0, 0,18},
        {18, 0, 0, 0, 0,18},
        {18, 0, 0, 0, 0,18},
        {18, 0, 0, 0, 0,18},
        {18,18,18,18,18,18},
        };
    int score;
    bool flag= 0;
    bool ifcls;
    
    void slide(char op, char rlab, char clab){
        char rplus , cplus;
        
    //    char rlab=0 , clab=0;

        switch (op){
            case 's': 
                rplus= 1;
                cplus= 0;
                break;
            case 'a': 
                rplus= 0;
                cplus= -1;
                break;
            case 'w': 
                rplus= -1;
                cplus= 0;
                break;
            case 'd': 
                rplus= 0;
                cplus= 1;
                break;
        }

        while(a[rlab+rplus][clab+cplus] == 0){
            
                a[rlab+rplus][clab+cplus]= a[rlab][clab];
                a[rlab][clab]= 0;
    //            &k[0][0] = &k[0][0] + int(cplus);
    //            k+=rplus*6;
                rlab+= rplus;
                clab+= cplus;

                flag= 1;
    //    printf("\nHere");
        //print(k,14132);
        }
        if (a[rlab+rplus][clab+cplus] == a[rlab][clab]){
        //print(k,114514);
            a[rlab+rplus][clab+cplus]++;
            a[rlab][clab]=0;
        //print(k,1919810);
            score+= exp2[ a[rlab+rplus][clab+cplus] ];
            flag= 1;
        }
    }
     
    void optionW(){
        for(int c=1; c<=4; c++){
            for (int r=1; r<=4; r++){
                if(a[r][c]){
                    slide('w',r,c);
                }
                //printf("\n%d,%d",r,c);
            }
        }
    }
    void optionS(){
        for(int c=1; c<=4; c++){
            for (int r=4; r>=1; r--){
                if(a[r][c]){
                    slide('s',r,c);
                }
                //printf("\n%d,%d",r,c);
            }
        }
    }
    void optionA(){
        for(int r=1; r<=4; r++){
            for (int c=1; c<=4; c++){
                if(a[r][c]){
                    slide('a',r,c);
                }
                //printf("\n%d,%d",r,c);
            }
        }
    }
    void optionD(){
        for(int r=1; r<=4; r++){
            for (int c=4; c>=1; c--){
                if(a[r][c]){
                    slide('d',r,c);
                }
                //printf("\n%d,%d",r,c);
            }
        }
    }
    
    void generate(){//Wrong HERE ->removed the "srand"
        char x=rand()%4 + 1 , y=rand()%4 + 1;
        if (a[x][y] != 0){
            generate ();
        }
        else{
            a[x][y]= rand()%2+1;
            //printf("%d %d %d\n",a[x][y], x, y);
        }
    }
    //Not safe: May struck when the box is full
    
    void print(){
        if(ifcls)system("cls");
        printf("\n|      Your Score : %8d     |\n\n",score);
        //20 charchs
        printf("o--------------------------------o");
        printf("\n|                                |");
        for(int i=1; i<=4; i++){//debug usage
            printf("\n|");
            for(int j=1; j<=4; j++){
                printf("%7d",exp2[ a[i][j] ]);
            }
            printf("    |\n|                                |");
            //total 31 charachs
        }
        printf("\no--------------------------------o");
    }
    void quit(){
        system("cls");
        ifcls= 0;
        printf("------------GAME OVER!------------\n");
        print();
        printf("\n");
        system("pause");
    }

    bool checkfull(){
    for(int i=0; i<=4; i++){
        for(int j=0;j<=4;j++){
            if (a[i][j] == 0) return false;
        }
    }
    return true;
    }//when full return true
    bool checkslide(){
        char CopyA[6][6];
        int CopyScore= score;
        for(int i=0; i<=5; i++){
            for(int j=0; j<=5; j++){
                CopyA[i][j]= a[i][j];
            }
        }

        flag= 0;
        optionW();
        optionA();
        optionS();
        optionD();
        //flag == 1 when slided

        score= CopyScore;
        for(int i=0; i<=5; i++){
            for(int j=0; j<=5; j++){
                a[i][j]= CopyA[i][j];
            }
        }

        return !flag;

    }//retrun 1 when unable to slide

    char getoption(){
        char op;
        printf("\nInput your option Here(wasd+Enter): \n");
        op=getchar();
        fflush(stdin);
        if( (op == 'w') || (op == 'a') || (op == 's') || (op == 'd') ){
            
            return op;
        }
        else{
            printf("\nInvalid Input!");
            return getoption();
        }
    }
    //not safe
    
public:
    Game2048(){
        score= 0;
        ifcls= 1;
        srand(time(0));
        generate();
    }
    
    void run(){
        char op;
        flag= 1;

        while(1) {

            if(flag ){
                generate();
                flag= 0;
            }
            //else
            {
                if(checkfull()){//checkfull only when unable to slide, but cannot judge  the over of game at once,so deleted"else".
                    if (checkslide()){//checkslide only when full
                        quit();
                        break;
                    }
                }
            }

            flag= 0;
            print();
            
            
            op=getoption();
            switch (op)
            {
            case 'w':
                optionW();
                break;
            case 'a':
                optionA();
                break;
            case 's':
                optionS();
                break;
            case 'd':
                optionD();
                break;
            }

        }
    }
    void test(){
    /*
        char Testplate[6][6]={
        {18,18,18,18,18,18},
        {18,1,2,3,4,18},
        {18,4,3,2,1,18},
        {18,1,2,3,4,18},
        {18,4,3,2,2,18},
        {18,18,18,18,18,18},
        };
        when option'd' : the row 4 turn to "0 0 0 5" which is not wanted
    */
        ifcls= 0;
        char op;
        char Testplate[6][6]={
        {18,18,18,18,18,18},
        {18,1,2,3,4,18},
        {18,4,3,2,1,18},
        {18,1,2,3,4,18},
        {18,6,5,3,3,18},
        {18,18,18,18,18,18},
        };
        for(int i=0; i<=5; i++){
            for(int j=0; j<=5; j++){
                a[i][j]= Testplate[i][j];
            }
        }
        flag= 0;//flag == 1 means the ability to move

        while(1) {

            if(flag ){
                generate();
                flag= 0;
            }
            //else
            {
                if(checkfull()){//checkfull only when unable to slide, but cannot judge  the over of game at once,so deleted"else".
                    if (checkslide()){//checkslide only when full
                        quit();
                        break;
                    }
                }
            }

            flag= 0;
            print();
            
            
            op=getoption();
            switch (op)
            {
            case 'w':
                optionW();
                break;
            case 'a':
                optionA();
                break;
            case 's':
                optionS();
                break;
            case 'd':
                optionD();
                break;
            }

        }

    }
};

int main() {
    printf("Initializing......");
    Game2048 game;

//    game.test();
    game.run();
    return 0;
}