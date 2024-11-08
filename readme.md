## Directory tree
    Snake_8x8_Console
    ├── With_C
    │   ├── Base_Lib.h
    │   ├── main
    │   ├── main.c
    │   └── SnakeC.h
    └── With_C++
        ├── main.cpp
        ├── main.exe
        └── Snake.h

## Map value

                         UP (90)
                         ↑
                   0 1 2 3 4 5 6 7 8 y 
                 0 # # # # # # # # 
                 1 # # # # # # # # 
                 2 # # # # # # # # 
                 3 # # # # # # # #
    (180) LEFT ← 4 # # # # # # # # → RIGHT (0)
                 5 # # # # # # # # 
                 6 # # # # # # # # 
                 7 # # # # # # # # 
                 8       ↓
                 x       Down (270)

    apple : 19
    snake{
        + HEAD: 3
        + BODY: 15(RIGHT), 105(UP), 195(LEFT), 285(DOWN)
        + TAIL: 27
    }

## Abstract
In folder With_C, SnakeC.h is written for reuse in final project of COOL course. In final project, you need add some libs like led-maxtrix-8x8 to display game in matrix led and game-control (matrix-button, IR-reading, ...) to control this game. I just dev for people who have registered =)) But i also published it as public.
## SnakeC
To use this lib, at begin, you need run Snake_Initial(), this function set-up some variable of this lib. In an update cycle, the function call order must be followed in the order below:
+    direction_change()
+    direction_update()    
+    snake_head_update()
+    snake_body_update()

Currently, ```direction_change()``` only appcept one parameter is **to_ward**, **to_left**,  **to_right**, **to_up** or **to_down** (all of these are enum type is defined in SnakeC.h).