#include<SDL3/SDL.h>
#include<cstdlib>
#include<ctime>
#include<cstdio>

#define width 20
#define height 15
#define cell 32

#define win_width (width * cell)
#define win_height (height * cell)

#define max_snake 100

typedef struct  point {
    int x;
    int y;
} point;


point snake[max_snake];

int snake_lenght=3;

int food_x;
int food_y;

int dir_x=1;
int dir_y=0;

int score=0;

void reset(SDL_Window* window){

}

void move_snake(SDL_Window* window){

    for(int i=snake_lenght-1;i>0;i--)
    {
        snake[i]=snake[i-1];
    }

    snake[0].x+=dir_x;
    snake[0].y+=dir_y;

    if(snake[0].x<0)        snake[0].x=width-1;
    if(snake[0].x>width-1)  snake[0].x=0;
    if(snake[0].y<0)        snake[0].y=height-1;
    if(snake[0].y>height-1) snake[0].y=0;

    if(snake[0].x == food_x && snake[0].y==food_y)
    {
        if(snake_lenght<max_snake)
        {
            snake[snake_lenght] = snake[snake_lenght-1];

            snake_lenght++;
        }

        score++;




    }

    for(int i=1;i<snake_lenght;i++)
    {
        if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)
        {
            SDL_Delay(500);

            return;
        }
    }


}

int main(int argc,char* argv[]){

    if(!SDL_Init(SDL_INIT_VIDEO)){
        return 1;
    }

    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;

    if(!SDL_CreateWindowAndRenderer(
          "Snake Game",
          win_width,
          win_height,
          0,
          &window,
          &renderer))
    {
        SDL_Quit();
        return 1;
    }

    int running = 1;

    while(running)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_EVENT_QUIT)
            {
                running =0;
            }

            if(event.type==SDL_EVENT_KEY_DOWN){
                
                switch(event.key.scancode){
                    case SDL_SCANCODE_UP:{
                        if(dir_y !=1){
                            dir_x=0;
                            dir_y=-1;
                        }
                        break;
                    }
                    case SDL_SCANCODE_DOWN:{
                        if(dir_y !=-1){
                            dir_x=0;
                            dir_y=1;
                        }
                        break;
                    }
                    case SDL_SCANCODE_LEFT:{
                        if(dir_x !=1){
                            dir_x=-1;
                            dir_y=0;
                        }
                        break;
                    }
                    case SDL_SCANCODE_RIGHT:{
                        if(dir_x !=-1){
                            dir_x=1;
                            dir_y=0;
                        }
                        break;
                    }
                }

            }
        }

        









        SDL_SetRenderDrawColor(renderer,20,20,20,SDL_ALPHA_OPAQUE);

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,35,35,35,SDL_ALPHA_OPAQUE);

        for(int x=0;x<win_width;x+=cell){
            SDL_RenderLine(renderer,x,0,x,win_width);
        }

        for(int y=0;y<win_height;y+=cell){
            SDL_RenderLine(renderer,0,y,win_height,y);
        }


        


    }


    
}
