#include <iostream> 
#include <math.h> 
using namespace std; 
  
#define COMPUTER 1 
#define HUMAN 2 
  
struct move 
{ 
    int index; 
    int stones_removed; 
}; 
  
void printPiles (int piles[], int n) 
{ 
    int i; 
    cout <<"Current Game Status"; 
    for (i=0; i<n; i++) 
        cout << " " << piles[i]; 
    cout <<"\n"; 
    return; 
} 
  

bool gameOver(int piles[], int n) 
{ 
    int i; 
    for (i=0; i<n; i++) 
        if (piles[i]!=0) 
            return (false); 
  
    return (true); 
} 
  
void declareWinner(int whoseTurn) 
{ 
    if (whoseTurn == COMPUTER) 
        cout <<"\nHUMAN won\n\n"; 
    else
        cout <<"\nCOMPUTER won\n\n"; 
    return; 
} 
  

int nimSumCalculation(int piles[], int n) 
{ 
    int i, nimsum = piles[0]; 
    for (i=1; i<n; i++) 
        nimsum = nimsum ^ piles[i]; 
    return(nimsum); 
} 
  
void makeMove(int piles[], int n, struct move * moves) 
{ 
    int i, nim_sum = nimSumCalculation(piles, n); 
  
    // The player having the current turn is on a winning 
    // position. So he/she/it play optimally and tries to make 
    // Nim-Sum as 0 
    if (nim_sum != 0) 
    { 
        for (i=0; i<n; i++) 
        { 
            // If this is not an illegal move 
            // then make this move. 
            if ((piles[i] ^ nim_sum) < piles[i]) 
            { 
                (*moves).index = i; 
                (*moves).stones_removed = 
                                piles[i]-(piles[i]^nim_sum); 
                piles[i] = (piles[i] ^ nim_sum); 
                break; 
            } 
        } 
    } 
  
    else
    { 
        // Create an array to hold indices of non-empty piles 
        int non_zero_indices[n], count; 
  
        for (i=0, count=0; i<n; i++) 
            if (piles[i] > 0) 
                non_zero_indices [count++] = i; 
  
        (*moves).index = (rand() % (count)); 
        (*moves).stones_removed = 
                1 + (rand() % (piles[(*moves).index])); 
        piles[(*moves).index] = 
        piles[(*moves).index] - (*moves).stones_removed; 
  
        if (piles[(*moves).index] < 0) 
            piles[(*moves).index]=0; 
    } 
    return; 
} 

void playGame(int piles[], int n, int whoseTurn) 
{ 
    cout <<"\nGAME STARTS\n\n"; 
    struct move moves; 
  
    while (gameOver (piles, n) == false) 
    { 
        printPiles(piles, n); 
  
        makeMove(piles, n, &moves); 
  
        if (whoseTurn == COMPUTER) 
        { 
            cout <<"COMPUTER removes" << moves.stones_removed << "stones from pile at index " 
             << moves.index << endl; 
            whoseTurn = HUMAN; 
        } 
        else
        { 
            cout <<"HUMAN removes"<< moves.stones_removed << "stones from pile at index " 
            << moves.index << endl; 
            whoseTurn = COMPUTER; 
        } 
    } 
  
    printPiles(piles, n); 
    declareWinner(whoseTurn); 
    return; 
} 
  
void knowWinnerBeforePlaying(int piles[], int n, 
                            int whoseTurn) 
{ 
    cout <<"Prediction before playing the game -> "; 
  
    if (nimSumCalculation(piles, n) !=0) 
    { 
        if (whoseTurn == COMPUTER) 
            cout <<"COMPUTER will win\n"; 
        else
            cout <<"HUMAN will win\n"; 
    } 
    else
    { 
        if (whoseTurn == COMPUTER) 
            cout <<"HUMAN will win\n"; 
        else
            cout <<"COMPUTER will win\n"; 
    } 
  
    return; 
} 
  
int main() 
{ 

    int piles[] = {3, 4, 2}; 
    int n = sizeof(piles)/sizeof(piles[0]); 

    knowWinnerBeforePlaying(piles, n, COMPUTER); 

    playGame(piles, n, COMPUTER); 
  
    return(0); 
} 