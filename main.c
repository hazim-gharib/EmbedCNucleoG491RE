// Only include app and board public headers; HAL used inside board
#include "board/g491re/board.h"
#include "app/app.h"

// -----------------------------------------
// MAIN
// -----------------------------------------
int main(void)
{
    board_init();
    app_main();
}

