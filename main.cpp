#include <bits/stdc++.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Snake.h"
using namespace std;

inline void print_a_frame(Snake &s){
    cout << "\033[2J\033[1;1H";
    rep(i, 0, 7){
        rep(j, 0, 7){
            cout << ((s.is_snake(i, j))?('*'):('.')) << " ";
        }
        cout << endl;
    }
    Sleep(700);
}

int main(){
    Snake s;
    char pressed;
    while( s.is_alive() ){
        if(kbhit()) pressed = getch();
        switch (pressed)
        {
        case 'a':
            s.left();
            break;
        case 'd':
            s.right();
            break; 
        case 's':
            s.down();
            break;
        case 'w':
            s.up();
            break;      
        }
        s.increase_snake_size();
        pressed = '0';
        s.next_step();
        print_a_frame(s);
    }

}