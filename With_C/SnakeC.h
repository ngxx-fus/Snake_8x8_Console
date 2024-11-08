#include <time.h>
#include <stdlib.h>

#include "Base_Lib.h"

/*

                    UP
                    ↑
              0 1 2 3 4 5 6 7 8 y 
            0 # # # # # # # # 
            1 # # # # # # # # 
            2 # # # # # # # # 
            3 # # # # # # # #
    LEFT ←  4 # # # # # # # # → RIGHT
            5 # # # # # # # # 
            6 # # # # # # # # 
            7 # # # # # # # # 
            8       ↓
            x       Down

apple : 19
snake{
    + HEAD: 3
    + BODY: 7(RIGHT), 11(UP), 17(LEFT), 23(DOWN)
    + TAIL: 27
}

*/
enum enum_Apple{apple=19};
enum enum_Snake{head=3, body_r=15, body_u=105, body_l=195, body_d=285, tail=7};
enum enum_NextDirection{to_ward=0, turn_left=90, turn_right=-90, u_turn=360};
enum enum_CurrDirection{right=0, up=90, left=180, down=270};

#define _360_bounded(x) (((x)+360)%360)
#define _mod8_bounded(x) ((((x)+8)%8))
#define _point_eq(Ax,Ay,Bx,By) ((((Ax)==(Bx))&&((Ay)==(By)))?(1):(0))

//This will avail for 1-8 and 0->7 :>
int field[9][9];
//Game is paused?
int is_paused = 0;
//Game over?
int is_dead = 0;
//next direction from current
//to-ward: +0, turn-left: +90, turn-right: +270, u-turn: +180
int next_direction = 0; 
//current direction
//UP: 90, LEFT: 180, RIGHT: 0, DOWN: 270
int current_direction = 0;
//snake's head
int head_x = 0;
int head_y = 0;
//apple
int apple_x = 0;
int apple_y = 0;

void random_XY(int* X, int* Y){

    srand(time(0));
    do{
        *X = _mod8_bounded(random());
        *Y = _mod8_bounded(random());
    } while(field[*X][*Y] != 0);
}

void random_apple(){
    int X, Y;
    random_XY(&apple_x, &apple_y);
    field[apple_x][apple_y] = apple;
}

void direction_change(int new_direction){
    next_direction = new_direction;
}

void direction_update(){
    current_direction += next_direction;
    current_direction = _360_bounded(current_direction);
    next_direction = 0;
}

int is_myself(){
    return (field[head_x][head_y]==body_d) ||
            (field[head_x][head_y]==body_u) ||
            (field[head_x][head_y]==body_l) ||
            (field[head_x][head_y]==body_r) ||
            (field[head_x][head_y]==tail);
}

void snake_head_update(){
    if(is_dead) return;
    switch (current_direction) {
        case up:
            head_x = _mod8_bounded(head_x-1);
            head_y = head_y;
            if(is_myself()) is_dead = 1;
            field[head_x][head_y] = _360_bounded(body_u-180);
            break;
        case right:
            head_x = head_x;
            head_y = _mod8_bounded(head_y+1);
            if(is_myself()) is_dead = 1;
            field[head_x][head_y] = _360_bounded(body_r-180);
            break;
        case down:
            head_x = _mod8_bounded(head_x+1);
            head_y = head_y;
            if(is_myself()) is_dead = 1;
            field[head_x][head_y] = _360_bounded(body_d-180);
            break;
        case left:
            head_x = head_x;
            head_y = _mod8_bounded(head_y-1);
            if(is_myself()) is_dead = 1;
            field[head_x][head_y] = _360_bounded(body_l-180);
            break;
    }
}


void snake_body_update(){
    if(is_dead) return;
    int x=head_x, y=head_y, x_temp, y_temp, i;
    //Just update snake's body
    //snake_head_update() have to be called before!
    if(_point_eq(apple_x, apple_y, head_x, head_y)){
        // increase lenght of snake :v
        random_apple();
        return;
    }
    //go to tail and remove tail
    REP(i, 1, 64){//the lengh of snake must less than 64 :v 
        x_temp = x, y_temp = y;
        switch (field[x][y]) {
            case body_r:
                x = x;
                y = _mod8_bounded(y+1);
                break;
            case body_l:
                x = x;
                y = _mod8_bounded(y-1);
                break;
            case body_u:
                x = _mod8_bounded(x-1);
                y = y;
                break;
            case body_d:
                x = _mod8_bounded(x+1);
                y = y;
                break;
        }
        if(field[x][y] == tail || field[x][y] == head){
            //(x, y) is tail  --> remove
            field[x][y] = 0;
            //(x_temp, y_temp) --> new tail :v assign to ZERO
            if(_point_eq(x_temp, y_temp, head_x, head_y))
                field[x_temp][y_temp] = head;
            else
                field[x_temp][y_temp] = tail;
            //done
            break; 
        }
    }
}  

void snake_initial(){
    random_XY(&head_x, &head_y);
    field[head_x][head_y]=head;
    random_apple();
    current_direction = (random()%3)*90;
    next_direction = 0;
}