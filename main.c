#include <stdio.h>
#include <locale.h>
#include <wchar.h>

void displayBoard(wchar_t board[8][8]);
void moveChoice(wchar_t board[8][8]);
int checkIfMoveOnBoard(char mF1, char mFA, char mT1, char mTA);
int pieceChosen(char fromA, char from1, wchar_t board[8][8]);
void convertToCo(char originalMoveList[4], char newMoveList[4]);


int turnCounter = 0;
int inCheck = 0;

int main(void){

    /* Note: 0,0 is a8 on a normal board */

    /* This allows UNICODE to be used */
    setlocale(LC_ALL, "");

    wchar_t chessboard[8][8] = {
        {L'♖', L'♘', L'♗', L'♕', L'♔', L'♗', L'♘', L'♖'},
        {L'♙', L'♙', L'♙', L'♙', L'♙', L'♙', L'♙', L'♙'},
        {L'-', L'-', L'-', L'-', L'-', L'-', L'-', L'-'},
        {L'-', L'-', L'-', L'-', L'-', L'-', L'-', L'-'},
        {L'-', L'-', L'-', L'-', L'-', L'-', L'-', L'-'},
        {L'-', L'-', L'-', L'-', L'-', L'-', L'-', L'-'},
        {L'♟', L'♟', L'♟', L'♟', L'♟', L'♟', L'♟', L'♟'},
        {L'♜', L'♞', L'♝', L'♛', L'♚', L'♝', L'♞', L'♜'}
    };

    displayBoard(chessboard);

    moveChoice(chessboard);


    return 0;
}

void displayBoard(wchar_t board[8][8]){
    wchar_t lazyList[8] = {L'8', L'7', L'6', L'5', L'4', L'3', L'2', L'1'};
    for (int i = 0; i < 8; i++){
        wprintf(L"%lc", lazyList[i]);
        for (int j=0; j < 8; j++){
            wprintf(L"   %lc", board[i][j]);
        }
        wprintf(L"\n");
    }
    wprintf(L"    A   B   C   D   E   F   G   H\n");
    return;
}

void moveChoice(wchar_t board[8][8]){
    char moveFromA, moveFrom1, moveToA, moveTo1;
    int validMove = 0;

    while (!validMove){
        if (turnCounter % 2==0){
            wprintf(L"White Choose A Move In The Format A2 A3: ");
            scanf(" %c%c %c%c", &moveFromA,&moveFrom1,&moveToA,&moveTo1);
        }
        else{
            wprintf(L"Black Choose A Move In The Format A2 A3: ");
            scanf(" %c%c %c%c", &moveFromA,&moveFrom1,&moveToA,&moveTo1);
        }

        /* Checking if move is valid before anything happens with the move choices */

        /* First check is if the entered spaces even exist on the board */

        if (!checkIfMoveOnBoard(moveFrom1, moveFromA, moveTo1, moveToA)){
            wprintf(L"Not a valid move\n");
            continue;
        }

        /* Check if the same square is entered twice */


        /* Convert input to co-ordinates */


        /* Convert back from list to singular co-ordinates */
        char originalCo[4] = {moveFrom1, moveFromA, moveTo1, moveToA};
        char newCo[4];
        convertToCo(originalCo, newCo);


        /* Check if there is a piece on the chosen square */

        if(!pieceChosen(moveFromA, moveFrom1, board)){
            wprintf(L"No piece chosen\n");
            continue;
        }

        /* Repeat what was done above with different kinds of checks (will take a long time) */


        /* Move is valid */
        validMove = 1;
    }
    
    return;
}

/* Checks if user inputted squares are on the board */
int checkIfMoveOnBoard(char mF1, char mFA, char mT1, char mTA){
    char tilesA[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    char tiles1[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    int realMoveFromA = 0, realMoveFrom1 = 0, realMoveToA = 0, realMoveTo1 = 0;

    for (int i = 0; i < 8; i++){

        if (mFA == tilesA[i]){realMoveFromA = 1;}
        if (mF1 == tiles1[i]){realMoveFrom1 = 1;}
        if (mTA == tilesA[i]){realMoveToA = 1;}
        if (mT1 == tiles1[i]){realMoveTo1 = 1;}
        
    }
    if (realMoveFrom1 && realMoveFromA && realMoveTo1 && realMoveToA){
            return 1;
        }
    else{
            return 0;
        }
}

int pieceChosen(char fromA, char from1, wchar_t board[8][8]){
    return 1;
}

void convertToCo(char originalMoveList[4],char newMoveList[4]){
    char rowIF, columnIF, rowOF, columnOF, rowIT, columnIT, rowOT, columnOT;


    rowIF = originalMoveList[0];
    columnIF = originalMoveList[1];
    rowIT = originalMoveList[2];
    columnIT = originalMoveList[3];

    wprintf(L"%c\n", columnIF);
    wprintf(L"%c\n", rowIF);
    wprintf(L"%c\n", columnOF);
    wprintf(L"%c\n", rowOF);

    //rowOF = 
}
