// #include <Arduino.h>
#include <bits/stdc++.h>
#define rep(i,a,b) for( unsigned int i=a; i<=b; i++)
#define rev(i,b,a) for( unsigned int i=b; i>=a; i--)
#define outpin(PIN) pinMode(PIN, OUTPUT)
#define inpin(PIN) pinMode(PIN, INPUT)
#define on(PIN) digitalWrite(PIN, HIGH)
#define off(PIN) digitalWrite(PIN, LOW)

class Snake{
    int arr[8][8];
    bool alive;
    int curX, curY;
    int increase_size;
    int AppleX, AppleY;
    char curDirection;
    inline bool to_left(){return curY > 0;}
    inline bool to_right(){return curY < 7;}
    inline bool to_up(){return curX > 0;}
    inline bool to_down(){return curX < 7;}
    void reset_snake(){
        rep(i, 0, 7) rep(j,0,7) arr[i][j] = 0;
    }

    public:
    #define HEAD 7
    #define TAIL 11
    #define  UP 1
    #define  LEFT  2
    #define  DOWN 3
    #define  RIGHT 4
    void initialize_position();
    Snake(){
        initialize_position();
    }
    void update_snake(int x, int y);
    bool next_step();
    void sync_screen(bool screen[8][8]);
    bool is_snake(int x, int y){
       if( x < 0 || x > 7 || y < 0 || y > 7) return false;
        return bool(arr[x][y]);
    }
    void restart(){
        if(alive == false) initialize_position();
    }
    void increase_snake_size(){
        increase_size = 1;
    }
    bool is_head(int row, int col){
        return (arr[row][col] == HEAD);
    }
    bool is_tail(int row, int col){
        return (arr[row][col] == TAIL);
    }
    bool is_alive(){return alive;}
    void turn_left();
    void turn_right();
    void continue_straight();
    void up();
    void down();
    void left();
    void right();
};

void Snake::initialize_position(){
    static int count_ = 0; 
    count_ = (count_*count_-count_*987)%1000;
    alive = true;
    reset_snake();
    srand(count_++);
    increase_size = 1;
    curX = rand()%8, curY = rand()%8;
    arr[curX][curY] = TAIL;
    switch (rand()%4){
    case 0:
        curDirection = UP;
        break;
    case 1:
        curDirection = DOWN;
        break;
    case 2:
        curDirection = LEFT;
        break;
    default:
        curDirection = RIGHT;
        break;
    }
}

//without change of size
bool Snake::next_step(){
    switch (curDirection)
    {
    case UP:
        if( curX - 1 < 0  || arr[curX -1][curY] ){
            //die :))
            return alive = false; 
        }  
        arr[curX-1][curY] = DOWN;
        curX--;
        if( increase_size ) increase_size = 0;
        else  update_snake(curX, curY);
    break;

    case DOWN:
        if( curX + 1 > 7 || arr[curX + 1][curY]){
            //die :))
            return alive = false;
        }  
        arr[curX + 1][curY] = UP;
        curX++;
        if( increase_size ) increase_size = 0;
        else  update_snake(curX, curY);
    break;

    case LEFT:
        if( curY - 1 < 0 || arr[curX][curY -1] ){
            //die :))
            return alive = false;
        }  
        arr[curX][curY-1] = RIGHT;
        curY--;
        if( increase_size ) increase_size = 0;
        else  update_snake(curX, curY);
    break;
    
    case RIGHT:
        if( curY + 1 > 7|| arr[curX][ curY + 1 ] ){
            //die :))
            return alive = false;
        }  
        arr[curX][curY+1] = LEFT;
        curY++;
        if( increase_size ) increase_size = 0;
        else  update_snake(curX, curY);
    break;
    }
    return alive;
}

//update the position of snake
void Snake::update_snake(int x, int y){
    if( x < 0 || x > 7 || y < 0 || y > 7) return;
    switch ( arr[x][y] ){
    case UP:
        if( is_tail(x-1, y) ) arr[x][y] = TAIL, arr[x-1][y] = 0;
        else update_snake(x-1, y);
        break;
    case DOWN:
        if( is_tail(x+1, y) ) arr[x][y] = TAIL, arr[x+1][y] = 0;
        else update_snake(x+1, y);
        break;
    case LEFT:
        if( is_tail(x, y-1) ) arr[x][y] = TAIL, arr[x][y-1] = 0;
        else update_snake(x, y-1);
        break;
    case RIGHT:
        if( is_tail(x, y+1) ) arr[x][y] = TAIL, arr[x][y+1] = 0;
        else update_snake(x, y+1);
        break;
    } 
};

void Snake::sync_screen(bool screen[8][8]){
    rep(i, 0, 7) rep(j,0,7) screen[8][8] = bool(arr[i][j]);
};


void Snake::turn_left(){
    switch (curDirection)
    {
    case UP:
        curDirection = LEFT;
        break;
    case DOWN:
        curDirection = RIGHT;
        break;
    case LEFT:
        curDirection = DOWN;
        break;
    case RIGHT:
        curDirection = UP;
        break;
    }
}

void Snake::turn_right(){
    switch (curDirection)
    {
    case UP:
       curDirection = RIGHT;
        break;
    case DOWN:
        curDirection = LEFT;
        break;
    case LEFT:
        curDirection = UP;
        break;
    case RIGHT:
        curDirection = DOWN;
        break;
    }
}


void Snake::up(){
    if( curDirection == DOWN ) return;
    curDirection = UP;
}

void Snake::down(){
    if(curDirection == UP) return;
    curDirection = DOWN;
}

void Snake::left(){
    if(curDirection == RIGHT) return;
    curDirection = LEFT;
}

void Snake::right(){
    if(curDirection == LEFT) return;
    curDirection = RIGHT;
}

void Snake::continue_straight(){
    /*nothin' happened*/
}

