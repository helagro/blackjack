#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Card{
    char deno;
    int value;
    bool used;
}Card;

void prepCards();
void start();
void dealerMove();
int playerMove();
Card getCard();
int countPoints(Card *arr, int arrI);
char *cardToStr(Card *arr, int size);

int decks = 4;

Card *cards;
int cardsSize;
Card *playerCards;
int playerI = 0;
Card *dealerCards;
int dealerI = 0;

int main(int argc, char *argv[]){
    srand(time(NULL));
    prepCards();
    printf("VÄLKOMMEN TILL HENRIKS BLACKJACK-SPEL\n");
    start();

    return 0;
}

//Creates arr of Card
void prepCards(){
    char *denos = "23456789XkDKE";
    cardsSize = 13*4*decks;
    cards = (Card *) malloc(cardsSize*sizeof(Card));

    int denoI;
    int i = 1;


    for(int deckI = 1; deckI <= decks*4; deckI++){
       for(denoI = 0; denoI < 13; denoI++){
            cards[i].deno = denos[denoI];
            cards[i].value = denoI+2 > 10 ? 10: denoI+2;
            i++;
        }
        cards[i-1].value = 11;
    }
}   


void start(){
    dealerCards = (Card *)malloc(21*sizeof(Card));
    playerCards = (Card *)malloc(21*sizeof(Card));

    dealerMove(0);
    int playP = playerMove();
    dealerMove(playP);

    //calcs res
    int dealP = countPoints(dealerCards, dealerI);
    if(dealP > 21 || playP > dealP){
        printf("\nDu vann!\n");
    }
    else if(dealP > playP){
        printf("\nDu förlorade!\n");
    }
    else{
        if(dealP > 16 && dealP < 20){
            printf("\nDu förlorade!\n");
        }
        else{
            printf("\nOavgjort!\n");
        }
    }

}

//draws until higher than pPoints
void dealerMove(int pPoints){
    int points;
    do{
        dealerCards[dealerI] = getCard();
        dealerI++;
        points = countPoints(dealerCards, dealerI);
    }while(points < pPoints);

    printf("\nDealern har: %s\n",cardToStr(dealerCards, dealerI));
}

int playerMove(){
    int points;
    do{
        playerCards[playerI] = getCard();
        playerI++;
        points = countPoints(playerCards, playerI);
        printf("\nDu har:%s\n", cardToStr(playerCards, playerI));

        if (points > 21){
            printf("Du förlorade!\n");
            exit(0);
        }
        printf("\n Vill du (s)tanna eller (f)ortsätta?\n");
        char input;
        scanf(" %c",&input);
        if(input == 's'){
            break;
        }
    }while(true);
    return points;
}

//if points > 21, E = 1
int countPoints(Card *arr, int arrI){
    int eAt = -1;
    int points = 0;
    int i;
    for(i = 0; i < arrI; i++){
        points += arr[i].value;
        if(arr[i].value == 11){  ;eAt = i;   }
    }
    if(points > 21 && eAt != -1){
        arr[eAt].value = 1;
        return countPoints(arr,arrI);
    }
    return points;
}

//returns random card
Card getCard(){
    Card randCard;
    int rnd;
    do{
        rnd = rand()%cardsSize;
        randCard = cards[rnd];
    }while(randCard.used);
    cards[rnd].used = true;
    return randCard;
}

//toString() function for Card array
char *charArr;
char *cardToStr(Card *arr, int size){
    charArr = (char *) malloc(size * 2 * sizeof(char));
    int addI = 0;
    for(int i = 0; i < size;  i++){
        charArr[addI] = arr[i].deno;
        addI++;
        charArr[addI] = ' ';
        addI++;
    }
    charArr[addI] = 0;
    return charArr;
}


