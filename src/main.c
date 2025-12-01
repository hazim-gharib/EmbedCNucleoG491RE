// Only include app and board public headers; HAL used inside board
#include "board/g491re/public_inc/board.h"
#include "app/public_inc/app.h"

// -----------------------------------------
// MAIN
// -----------------------------------------
int main(void)
{
    board_init();
    app_main();
}

