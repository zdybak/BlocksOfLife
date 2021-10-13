#include "include/raylib.h"
#include <stdlib.h>

const char* getDownKey(void) {
    
    if(IsKeyDown(KEY_W)){
        return "W";
    } else {
        return "NO KEY";
    }
}