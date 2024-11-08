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
## Abstract
In folder With_C, SnakeC.h is written for reuse in final project of COOL course. In final project, you need add some libs like led-maxtrix-8x8 to display game in matrix led and game-control (matrix-button, IR-reading, ...) to control this game. I just dev for people who have registered =)) But i also published it as public.
## Snake console
To use this lib, at begin, you need run Snake_Initial(), this function set-up some variable of this lib. In an update cycle, the function call order must be followed in the order below:
+    direction_change()
+    direction_update()    
+    snake_head_update()
+    snake_body_update()

Currently, ```direction_change()``` only appcept one parameter is **turn_left** or **turn_right** (both are enum type is defined in SnakeC.h).