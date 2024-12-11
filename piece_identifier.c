#include "piece_identifier.h" //for linking
#include "constants.h" //for BOARD_SIZE

int piece_is_pawn(char piece){
    if(piece == 'P' || piece == 'p'){return TRUE;}
    return FALSE;
}

int piece_is_rook(char piece){
    if(piece == 'R' || piece == 'r'){return TRUE;}
    return FALSE;
}

int piece_is_knight(char piece){
    if(piece == 'N' || piece == 'n'){return TRUE;}
    return FALSE;
}

int piece_is_bishop(char piece){
    if(piece == 'B' || piece == 'b'){return TRUE;}
    return FALSE;
}

int piece_is_queen(char piece){
    if(piece == 'Q' || piece == 'q'){return TRUE;}
    return FALSE;
}

int piece_is_king(char piece){
    if(piece == 'K' || piece == 'k'){return TRUE;}
    return FALSE;
}