#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <ctype.h>

void displayBoard(wchar_t board[8][8]);
int moveChoice(wchar_t board[8][8]);
int checkIfMoveOnBoard(char mF1, char mFA, char mT1, char mTA);
int pieceChosen(char fromX, char fromY, wchar_t board[8][8]);
void convertToCo(char originalMoveList[4], int newMoveList[4]);
int takingOwnPiece(int toX, int toY, wchar_t board[8][8]);
int ownsPieceMoving(int fromX, int fromY, wchar_t board[8][8]);
int differentSquaresChosen(int fromX, int fromY, int toX, int toY);


int turnCounter = 0;

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
        wprintf(L"   %lc\n", lazyList[i]);
    }
    wprintf(L"    A   B   C   D   E   F   G   H\n");
    return;
}

int moveChoice(wchar_t board[8][8]){
    char moveFromA, moveFrom1, moveToA, moveTo1;
    int validMove = 0;

    while (!validMove){
        if (turnCounter % 2==0){
            wprintf(L"White Choose A Move (e.g A2 A3): ");
            scanf(" %c %c %c %c", &moveFromA,&moveFrom1,&moveToA,&moveTo1);
        }
        else{
            wprintf(L"Black Choose A Move (e.g A2 A3): ");
            scanf(" %c %c %c %c", &moveFromA,&moveFrom1,&moveToA,&moveTo1);
        }

        moveFromA = toupper(moveFromA);
        moveToA = toupper(moveFromA);

        /* Checking if move is valid before anything happens with the move choices */

        /* First check is if the entered spaces even exist on the board */

        if (!checkIfMoveOnBoard(moveFrom1, moveFromA, moveTo1, moveToA)){
            wprintf(L"Not a valid move\n");
            continue;
        }


        /* Convert input to co-ordinates */
        char originalCo[4] = {moveFrom1, moveFromA, moveTo1, moveToA};
        int newCo[4];
        convertToCo(originalCo, newCo);

        /* Convert back from list to singular co-ordinates */
        int fromX, fromY, toX, toY;
        fromX = newCo[0];
        fromY = newCo[1];
        toX = newCo[2];
        toY = newCo[3];


        /* Check if the same square is entered twice */

        if (!differentSquaresChosen(fromX, fromY, toX, toY)){
            wprintf(L"You have to move a piece\n");
            continue;
        }

        /* Check if there is a piece on the chosen square */

        if(!pieceChosen(fromX, fromY, board)){
            wprintf(L"No piece chosen\n");
            continue;
        }

        /* Check is a piece of yours is on the square you are moving to */

        if(!takingOwnPiece(toX, toY, board)){
            wprintf(L"You cannot take your own piece\n");
            continue;
        }

        /* Check if you own the piece you are moving */

        if(!ownsPieceMoving(fromX, fromY, board)){
            wprintf(L"You dont own the piece you are moving\n");
            continue;
        }


        /* Repeat what was done above with different kinds of checks (will take a long time) */


        validMove = 1;
    }
    
    return 1;
}



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

int pieceChosen(char fromX, char fromY, wchar_t board[8][8]){
    if (board[fromX][fromY] == '-'){
        return 0;
    }
    else{
        return 1;
    }
}

void convertToCo(char originalMoveList[4],int newMoveList[4]){
    char rowIF, columnIF, rowOF, columnOF, rowIT, columnIT, rowOT, columnOT;

    for (int i = 0; i < 4; i++){
        if (originalMoveList[i] == 'A'){originalMoveList[i] = 1;}
        else if (originalMoveList[i] == 'B'){originalMoveList[i] = 2;}
        else if (originalMoveList[i] == 'C'){originalMoveList[i] = 3;}
        else if (originalMoveList[i] == 'D'){originalMoveList[i] = 4;}
        else if (originalMoveList[i] == 'E'){originalMoveList[i] = 5;}
        else if (originalMoveList[i] == 'F'){originalMoveList[i] = 6;}
        else if (originalMoveList[i] == 'G'){originalMoveList[i] = 7;}
        else if (originalMoveList[i] == 'H'){originalMoveList[i] = 8;}
    }

    
    for (int i = 0; i < 4; i++){
        if (isdigit(originalMoveList[i])){
            originalMoveList[i] = originalMoveList[i] - '0';
        }
        originalMoveList[i]--;
    }
    

    rowIF = originalMoveList[0];
    columnIF = originalMoveList[1];
    rowIT = originalMoveList[2];
    columnIT = originalMoveList[3];



    rowOF =  7 - rowIF;
    columnOF = columnIF;
    rowOT = 7 - rowIT;
    columnOT = columnIT;

    newMoveList[0] = rowOF;
    newMoveList[1] = columnOF;
    newMoveList[2] = rowOT;
    newMoveList[3] = columnOT;

    return;
    
}

int takingOwnPiece(int toX, int toY, wchar_t board[8][8]){
    //White move
    if (turnCounter % 2==0){
        wchar_t whitePieces[6] = {L'♟', L'♜', L'♞', L'♝', L'♛', L'♚'};
        for (int i=0; i < 6; i++){
            if (board[toX][toY] == whitePieces[i]){
                return 0;
            }
        }
    }
    else{
        wchar_t blackPieces[6] = {L'♕', L'♔', L'♗', L'♘', L'♖', L'♙'};
        for (int i=0; i < 6; i++){
            if (board[toX][toY] == blackPieces[i]){
                return 0;
            }
        }
    }
    return 1;
}

int differentSquaresChosen(int fromX, int fromY, int toX, int toY){
    if (fromX == toX && fromY && toY){
        return 0;
    }
    else{
        return 1;
    }
}

int ownsPieceMoving(int fromX, int fromY, wchar_t board[8][8]){
    //White move
    if (turnCounter % 2==0){
        wchar_t blackPieces[6] = {L'♕', L'♔', L'♗', L'♘', L'♖', L'♙'};
        for (int i=0; i < 6; i++){
            if (board[fromX][fromY] == blackPieces[i]){
                return 0;
            }
        }
    }
    else{
        wchar_t whitePieces[6] = {L'♟', L'♜', L'♞', L'♝', L'♛', L'♚'};        
        for (int i=0; i < 6; i++){
            if (board[fromX][fromY] == whitePieces[i]){
                return 0;
            }
        }
    }
    return 1;
}