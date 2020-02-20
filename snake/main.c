#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct
{
int x;
int y;
} snake;
typedef struct
{
int score;
char name[15];
} score_name;

void mapzero(int map_size,int *map)
{
    for(int i=1;i<map_size-1;i++)
    {
        for(int j=1;j<map_size-1;j++)
        {
            *(map+i*map_size+j)=0;
        }
    }
}
void mapone(int map_size,int *map)
{
    for(int i=0;i<map_size;i++)
    {
        for(int j=0;j<map_size;j++)
        {
            *(map+i*map_size+j)=1;
        }
    }
}

void printmap(int map_size,int *map)
{
    for(int i=0;i<map_size;i++)
    {
        for(int j=0;j<map_size;j++)
        {
            printf("%d ",*(map+i*map_size+j));
        }
        printf("\n");
    }
}

snake move(snake p,int key)
{
    switch(key)
    {
    case'w': p.y--; break;
    case's': p.y++; break;
    case'a': p.x--; break;
    case'd': p.x++; break;
    case'W': p.y--; break;
    case'S': p.y++; break;
    case'A': p.x--; break;
    case'D': p.x++; break;

    default: break;
    }
    return p;
}

snake move1(snake p,int key)
{
    switch(key)
    {
    case'i': p.y--; break;
    case'k': p.y++; break;
    case'j': p.x--; break;
    case'l': p.x++; break;
    case'I': p.y--; break;
    case'K': p.y++; break;
    case'J': p.x--; break;
    case'L': p.x++; break;

    default: break;
    }
    return p;
}

void game_over(int map_size,int *map)
{
        for(int i=0;i<map_size;i++)
        {
            for(int j=0;j<map_size;j++)
            {
                printf("%d ",*(map+i*map_size+j));
                if(i==map_size/2 && j==map_size/2-3)
                {
                    printf("GAME OVER ");
                    j+=5;
                }

            }
        printf("\n");
        }
}

void socres(int s,int s1,int ile)
{
    FILE *fp;
    fp=fopen("scoretabela.txt", "w+");
    if(fp==NULL)
    {
        system("cls");
        printf("not working");
    }
    score_name name, name1;
    system("cls");
    if (ile == 1)
    {
        name.score=s;
        printf("Your score is: %d\nPlease write your name:",name.score);
        scanf("%s",name.name);
        fprintf (fp, "%s %d\n",name.name,name.score);
    }
    if (ile == 2)
    {
        name.score=s;
        name1.score=s1;
        printf("Player 1 score is: %d\nPlayer 2 score is: %d\nPlease write Player 1 name:",name.score,name1.score);
        scanf("%s",name.name);
        printf("Please write Player 2 name:");
        scanf("%s",name1.name);
        fprintf (fp, "%s %d\n", name.name,name.score);
    }
    fclose(fp);
}

void apple_map(snake p,int *map,int x)
{
    *(map+p.y*x+p.x)=2;
}

void snake_map(snake p,int *map,int x)
{
        *(map+p.y*x+p.x)=1;
}


void tail_map(snake p,int *map,int x)
{
    *(map+(p.y)*x+p.x)=1;
}

int snake_game_2()
{
    int map_size=15,score=0,score1=0;
    int map[map_size*map_size];
    int key=0,lenght=1,lenght1=1;
    snake *tail=malloc((lenght+2) * sizeof (int ));
    snake *tail1=malloc((lenght1+2) * sizeof (int ));
    snake pozition={rand()%(map_size-2)+1,rand()%(map_size-2)+1};
    snake pozition1={rand()%(map_size-2)+1,rand()%(map_size-2)+1};
    snake fruit={rand()%(map_size-2)+1,rand()%(map_size-2)+1};
    mapone(map_size,map);

    while(1)
    {
        key=getch();
        system("CLS");
        if(!(tail[0].x==pozition.x && tail[0].y==pozition.y))
        {
            for(int i=lenght;i>0;i--)
            {
            tail[i+1]=tail[i];
            tail[0]=pozition;
            }
        }
        else;
        if(!(tail1[0].x==pozition1.x && tail1[0].y==pozition1.y))
        {
            for(int i=lenght1;i>0;i--)
            {
            tail1[i+1]=tail1[i];
            tail1[0]=pozition1;
            }
        }
        else;

        pozition=move(pozition,key);
        pozition1=move1(pozition1,key);
        mapzero(map_size,map);
        apple_map(fruit,map,map_size);
        snake_map(pozition,map,map_size);
        snake_map(pozition1,map,map_size);
        for(int i=0;i<lenght;i++)
        tail_map(tail[i],map,map_size);
        for(int i=0;i<lenght;i++)
        tail_map(tail1[i],map,map_size);
        if(fruit.x==pozition.x && fruit.y==pozition.y)
        {
            lenght++;
            realloc(tail,(lenght+2) * sizeof (snake ));
            score+=10;
            fruit.x=rand()%(map_size-2)+1;
            fruit.y=rand()%(map_size-2)+1;
            apple_map(fruit,map,map_size);
        }
        if(fruit.x==pozition1.x && fruit.y==pozition1.y)
        {
            lenght1++;
            realloc(tail1,(lenght1+2) * sizeof (snake ));
            score1+=10;
            fruit.x=rand()%(map_size-2)+1;
            fruit.y=rand()%(map_size-2)+1;
            apple_map(fruit,map,map_size);
        }
        for(int i=lenght;i>=1;i--)
        {
            if(tail[i].x==pozition.x && tail[i].y==pozition.y){
            game_over(map_size,map);
            return 0;
            }
        }
        if(pozition.x==0 || pozition.x==map_size-1 || pozition.y==map_size-1 || pozition.y==0)
        {
            game_over(map_size,map);
            return 0;
        }
        for(int i=lenght;i>=1;i--)
        {
            if(tail1[i].x==pozition1.x && tail1[i].y==pozition1.y){
            game_over(map_size,map);
            free(tail1);
            free(tail);
            socres(score,score1,2);
            return 0;
            }
        }
        if(pozition1.x==0 || pozition1.x==map_size-1 || pozition1.y==map_size-1 || pozition1.y==0)
        {
            socres(score,score1,2);
            free(tail);
            free(tail1);
            game_over(map_size,map);
            return 0;
        }


        printmap(map_size,map);
        printf("PLAYER 1 SCORE: %d\ndPLAYER 2 SCORE: %d",score,score1);
    }
    return 0;
}
int snake_game()
{
    int map_size=15,score=0;
    int map[map_size*map_size];
    int key=0,lenght=0;
    snake *tail;
    tail=malloc((lenght+2) * sizeof (snake ));
    snake pozition={rand()%(map_size-2)+1,rand()%(map_size-2)+1};
    snake fruit={rand()%(map_size-2)+1,rand()%(map_size-2)+1};
    mapone(map_size,map);

    while(1)
    {
        key=getch();
        system("CLS");
        for(int i=lenght;i>=0;i--)
            {
            tail[i+1]=tail[i];
            tail[0]=pozition;
            }
        pozition=move(pozition,key);
        mapzero(map_size,map);
        apple_map(fruit,map,map_size);
        snake_map(pozition,map,map_size);
        for(int i=0;i<lenght;i++)
        tail_map(tail[i],map,map_size);
        if(fruit.x==pozition.x && fruit.y==pozition.y)
        {
            lenght++;
            realloc(tail,(lenght+2) * sizeof (snake ));
            score+=10;
            fruit.x=rand()%(map_size-2)+1;
            fruit.y=rand()%(map_size-2)+1;
            apple_map(fruit,map,map_size);
        }
        for(int i=lenght;i>=1;i--)
        {
            if(tail[i].x==pozition.x && tail[i].y==pozition.y){
            game_over(map_size,map);
            free(tail);
            Sleep(2000);
            socres(score,score,1);
            return 0;
            }
        }
        if(pozition.x==0 || pozition.x==map_size-1 || pozition.y==map_size-1 || pozition.y==0)
        {
            free(tail);
            game_over(map_size,map);
            Sleep(2000);
            socres(score,score,1);
            return 0;
        }


        printmap(map_size,map);
        printf("score: %d",score);
    }
    return 0;
}


void scoreboard()
{
    FILE *sc = fopen("scoreboard.txt","r+");
    score_name board[12];
    int entryCount=0 ,i = 0 ,ch,temp;
    char empo[15];
    FILE *input = fopen("scoretabela.txt", "r+");
    while ((ch = fgetc(input)) != EOF)
    {
        if (ch == '\n')
        entryCount++;
    }
    for (; i < entryCount; i++)
    {
        fscanf(input, "%s%d", board[i].name,&board[i].score);
    }

    for (; i < 12; i++)
    {
        fscanf(input, "%s %d", board[i].name,&board[i].score);
    }
    fclose(sc);

     for (i = 0; i < entryCount; i++)
    {
        for (int j = 0; j < entryCount; j++)
        {
            if (i == j) continue;
            if (board[i].score < board[j].score)
            {
                temp = board[i].score;
                board[i].score = board[j].score;
                board[j].score = temp;
                strcpy(empo, board[i].name);
                strcpy(board[i].name, board[j].name);
                strcpy(board[j].name, empo);
            }
        }
    }


    sc=fopen("scoreboard.txt","w+");
    for (i = 0; i < 10; i++)
    {
        fprintf(sc,"%s %d\n",board[i].name,board[i].score);
    }
    fclose(input);
    fclose(sc);
}
int main()
{

    printf("Press any key!");
    int c=getch();
    while(c!=9)
    {
        system("cls");
        printf("Snake\n\n1.single player\n2.vs mode(not avalible)\n3.scoreboard\n9.exit");
        switch(c)
        {
        case '1':snake_game(); break;
        case '2':snake_game_2(); scoreboard(); break;
        case '3':scoreboard(); break;
        default: break;
        }
        c=getch();
    }

    return 0;
}
