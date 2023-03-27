#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h> //used for sleep function
#include <fstream>
using namespace std;

ifstream fin("currency.txt");
ifstream fin2("highscore.txt");
ofstream fout("currency.txt", ios::app); //append mode so the values aren't deleted
ofstream fout2("highscore.txt",ios::app);

int start=0; //score value
int op_start=0;
double percentage;
int currency;
int bet;
int highscore;

struct Deck //Deck logic
{
protected: //because i need to acces those in Map class

    char colors[4][10]= {"Hearts", "Diamonds", "Clubs", "Spades"}; //cards colors
    char ranks[13][10] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}; //cards ranks

public:

    int colorIndex,rankIndex;
    int usedCards[4][13]= {0}; //variable for drawn cards
    int Card_Order_Counter=1; //this is used to memorize the order of appearance of the cards

    int k; //iterates trough all drawn cards to display them
    int k_limit=-1; //limits k so it knows the end of player's cards so computer's cards can be displayed

    bool hold=false; //checks if the player chose to hold
    //opponent score
    int k2; //opponent's iteration trough all it's cards for display
    double cards_left=0,favorable_cards=0; //we use those for percentage of winning


    void Randomize()
    {
        srand(time(0));  //setting seed to current time so we don't get same "random" results
        colorIndex=rand()%4;   //generate random pos of a color from arrray
        rankIndex = rand()% 13; //generate random pos of a rank from array
    }

    void DisplayCards()
    {
        system("cls"); // clear the screen
        printf("PRESS: 1 - DRAW CARD, 2 - HOLD, 3 - DOUBLE DOWN           Bet:%i\n\n",bet);
        if (hold==false)
        {
            printf("Player score: %i\n",start);

            for (k = 1; k <= Card_Order_Counter; k++) // loop through each drawn card
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (usedCards[i][j] == k)
                        {
                            printf("%s",ranks[j]);
                            switch (i)
                            {
                            case 0:
                                printf("♥");
                                break;
                            case 1:
                                printf("♦");
                                break;
                            case 2:
                                printf("♣");
                                break;
                            case 3:
                                printf("♠");
                                break;
                            }
                            printf("  "); // display the card
                        }
                    }
                }
            }
        }
        else
        {
            printf("Player score: %i\n",start);
            for (k=1; k<=k_limit; k++)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (usedCards[i][j] == k)
                        {
                            printf("%s",ranks[j]);
                            switch (i)
                            {
                            case 0:
                                printf("♥");
                                break;
                            case 1:
                                printf("♦");
                                break;
                            case 2:
                                printf("♣");
                                break;
                            case 3:
                                printf("♠");
                                break;
                            }
                            printf("  "); // display the card
                        }
                    }
                }
            }
            printf("\n\nOpponent score: %i\n",op_start);
            for (k=k_limit+1; k<=Card_Order_Counter; k++)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (usedCards[i][j] == k)
                        {
                            printf("%s",ranks[j]);
                            switch (i)
                            {
                            case 0:
                                printf("♥");
                                break;
                            case 1:
                                printf("♦");
                                break;
                            case 2:
                                printf("♣");
                                break;
                            case 3:
                                printf("♠");
                                break;
                            }
                            printf("  "); // display the card
                        }
                    }
                }
            }
        }
        printf("\n\n");
    }
    void AddPoints() //Here we add the drawn card points
    {
        //we apply rules for Ace (Either be 1 or 11 depending on player's favor)
        start=0;
        if (hold==false) //if it's the player we add the points normally
        {
            for(int i=0; i<4; i++)
            {
                for (int j=1; j<=12; j++) //we check all drawn cards except Ace
                {
                    if (usedCards[i][j]>=1)  //if the cards were drawn
                    {
                        if(j<=9)
                            start=start+j+1;
                        else if (j>9)
                            start=start+10; //we add all the points except the Ace
                    }
                }
            }
            for (int i=0; i<4; i++) //here we check drawn Ace cards
            {
                if (usedCards[i][0]>=1)
                {
                    if (start+11<=21) //if we can add 11 we use Ace's 11 value
                        start=start+11;
                    else
                        start=start+1; //else we use Ace's 1 value
                }

            }
        }
    }

    void Add_op_Points()
    {
        op_start=0;
        for(int i=0; i<4; i++)
        {
            for (int j=1; j<=12; j++) //we check all drawn cards except Ace
            {
                if (usedCards[i][j]>k_limit)  //if the cards were drawn and they are not the player's
                {
                    if(j<=9)
                        op_start=op_start+j+1;
                    else if (j>9)
                        op_start=op_start+10; //we add all the points except the Ace
                }
            }
        }
        for (int i=0; i<4; i++) //here we check drawn Ace cards
        {
            if (usedCards[i][0]>k_limit)
            {
                if (op_start+11<=21) //if we can add 11 we use Ace's 11 value
                    op_start=op_start+11;
                else
                    op_start=op_start+1; //else we use Ace's 1 value
            }

        }
    }

    void drawCard()  //add randomized elements to array
    {
        Randomize(); //need to randomize once first otherwise it crashes
        while(usedCards[colorIndex][rankIndex]>=1)  //making sure the card was not drawn more than once
        {
            Randomize();
        }
        //cout<<ranks[rankIndex]<<" of "<<colors[colorIndex]<<endl;

        usedCards[colorIndex][rankIndex]=Card_Order_Counter; //changing from 0 to 1 so it won't be drawn again
        Card_Order_Counter++;
        AddPoints(); //we call the function to add the points of the card drawn;
        DisplayCards();
    }

    double Percentage() //here we define percentage function
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                if (usedCards[i][j]==0)
                {
                    cards_left++;
                    if (j+1<=21-op_start)
                        favorable_cards++;
                }
            }
        }
        percentage=(favorable_cards/cards_left)*100;
        return percentage;
    }

    void Hold()  //what happens after we hold, computer start to draw it's card
    {
        hold=true;
        k_limit=Card_Order_Counter-1; //card order counter was raised by 1 even after last "draw card" so we have to remove 1
        while (op_start<=start)
        {
            if (op_start==start) //in case of draw, computer will think if it's right to draw another card
            {
                if(Percentage()<30) //checking if percentage of winning is over 30%
                {
                    break;
                }
            }

            Randomize();
            while(usedCards[colorIndex][rankIndex]>=1)  //making sure the card was not drawn more than once
            {
                Randomize();
            }

            usedCards[colorIndex][rankIndex]=Card_Order_Counter; //changing from 0 to 1 so it won't be drawn again
            Card_Order_Counter++;
            Add_op_Points();
            DisplayCards();
            Sleep(700); //if we don't put it to sleep it will draw cards too fast and the screen will be black until it finishes drawing
            //resulting in showing only the final result



        }
    }

    void Reset()
    {
        start = 0;
        op_start = 0;
        percentage = 0.0;
        bet = 0;
        Card_Order_Counter = 1;
        hold = false;
        k_limit = -1;
        cards_left = 0;
        favorable_cards = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                usedCards[i][j] = 0;
            }
        }
    }
};

void CheckHighScore()
{if (currency>highscore)
    {
     highscore=currency;
    fout2.open("highscore.txt");
    fout2<<highscore;
    fout2.close();

    }

}

struct Rules
{
private:

    int const PointLimit=21;

public:

    bool GameOver()  //rules when player wins and currency distribution
    {
        if (start > PointLimit)
        {
            printf("You Lost. Currency Left:%i\n\n",currency-bet);
            currency-=bet;
            fout.open("currency.txt");
            fout<<currency;
            fout.close();

            CheckHighScore();

            return true;
        }
        /*else if (start == PointLimit) //rule to instantly win if you reach 21 points
        {
            printf("You Won! Reward: %i.\n\n",bet);
            currency+=bet;
            return true;
        } */
        else if (op_start>start && op_start<=PointLimit) //if opponent reaches 21 or has higher points than user, you lost
        {
            printf("You Lost. Currency Left:%i\n\n",currency-bet);
            currency-=bet;
            fout.open("currency.txt");
            fout<<currency;
            fout.close();

            CheckHighScore();

            return true;
        }
        else if (op_start>PointLimit) //if opponent surpasses 21 you won
        {
            printf("You Won! Reward: %i.\n\n",bet);
            currency+=bet;
            fout.open("currency.txt");
            fout<<currency;
            fout.close();

            CheckHighScore();


            return true;
        }
        else if (op_start==start && start!=0 && percentage<30) //we have to add the percentage condition here too otherwise computer won't be able to decide
        {
            //because the game will just terminate
            printf("Tie\n\n");

            CheckHighScore();

            return true;
        }
        else
        {
            CheckHighScore();

            return false; //return false when score is less than 21
        }
    }

};

int main()
{
    fin2>>highscore;
    fin2.close();
    fin>>currency;
    fin.close();
    system("chcp 65001  > nul"); //we need this line of code so the terminal will recognize cards symbols
    Rules r;
    Deck d;
    int x;

    CheckHighScore();

    printf("PRESS: ANY - START, 0 - RULES, ESC - EXIT\n\nHIGHSCORE:%i\n",highscore); //Default screen

    x = getch();

    switch(x) //menu buttons
    {
    case 27: //exit on esc
    {
        return 0;
    }
    case '0':
    {
        system("cls");
        printf("Rules of the game:\nThe game ends when you have no currency left. If you reach 100 or more currency you win.\nEvery round you must defeat the opponent by getting more points than it.\nWinning with exactly 21 points raises the reward by a half.\nIn game you have 3 options:\n 1.Draw a card and add it's points.\n 2.Hold, stop and wait for the opponent to draw.\n 3.Double Down, in wich you double the bet and draw only one more card, then automatically hold.\nThe opponent tries to defeat you based on a specific percentage of winning.\nIf you pass over 21 points, you loose the round.\nIn case of tie you get the bet back.\nAce values either 11 or 1 depending on your favor.\nOther cards value based on their number while 10,J,Q,K all value 10.\nAfter completely loosing the currency, the next time you restart the game you will start back with 30.\nGOOD LUCK!\n\n");
        printf("Press any to start.");
        getch();

    }
    default: //start game
    {
        do
        {
            d.Reset();
            system ("cls"); //clear screen:

            printf("Currency:%i\nPlace a bet: ",currency);
            scanf("%i",&bet);
            while (bet > currency || bet<1)
            {
                system("cls");
                printf("Currency:%i \n\n",currency);
                printf("Place a valid bet!\n\n");
                printf("Place a bet: ");
                scanf("%i",&bet);
            }

            system("cls");
            printf("PRESS: 1 - DRAW CARD, 2 - HOLD, 3 - DOUBLE DOWN           Bet:%i\n\n",bet);

            while(r.GameOver()==false) //game goes on as long as you don't have over 21 points
            {

                x = getch(); // to read a single character from the keyboard without it being displayed on screen

                switch(x)
                {
                case '1': // by pressing 1 u draw another card;
                {
                    d.drawCard();
                    if (start==21)
                        {   bet*=1.5;
                            d.Hold();
                        }
                    break;
                }
                case '2': //by pressing 2 u hold
                {
                    if(start==0) //cannot hold without having any points
                    {
                        printf("Draw at least a card first!\n");
                        break;
                    }
                    else
                    {
                        d.Hold();
                        break;
                    }

                }
                case '3':
                    if (currency>=bet*2)
                    {
                        bet+=bet; //double the bet and draw one more card ONLY
                        d.drawCard();
                        if (start>21)
                            break;
                        d.Hold();
                    }
                    else
                        printf("You don't have enough currency to double the bet.\n");
                    break;
                }
            }

            CheckHighScore();

            if (currency<=0)
            {   fout.open("currency.txt");
                fout<<30;
                fout.close();
                printf("\nGAME OVER! No currency left.\n\n\n\n");
            }
            if (currency>0)
            {   fout.open("currency.txt");
                fout<<currency;
                fout.close();
                printf("Do you want to play another game? (Y - YES/N - NO): ");
                d.Reset();
                x = getch();

            }

        }
        while(currency>0 && x=='y');
    }

    }

    return 0;
}
