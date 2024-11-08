#include <unistd.h>
#include <stdio.h>
#include "SnakeC.h"

void print_a_frame(){
    
    int i, j;
    // printf("\033[2J\033[1;1H");
    REP(i, 0, 7){
        REP(j, 0, 7){
            if(field[i][j]){
                printf("%d\t", field[i][j]);
                // if(field[i][j] == apple)
                //     printf("x ");
                // else
                //     printf("# ");

            }else{
                printf("%d\t", field[i][j]);
                // printf("  ");
            }
        }
        printf("\n");
    }
}

int main(){
    snake_initial();
    char pressed;
    while( !is_dead ){
        printf("\033[2J\033[1;1H");
        printf("Head: %d %d\n", head_x, head_y);
        printf("C-Direct: %d\n", current_direction);
        print_a_frame();
        scanf(" %c", &pressed);
        switch (pressed)
        {
        case 'a':
            direction_change(to_left);
            break;
        case 'd':
            direction_change(to_right);
            break; 
        case 's':
            direction_change(to_down);
            break;
        case 'w':
            direction_change(to_up);
            break;
        }
        direction_update();
        snake_head_update();
        snake_body_update();
    }

}