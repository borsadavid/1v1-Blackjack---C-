#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h> //used for sleep function
using namespace std;


class Deck //Deck logic
{
protected: //because i need to acces those in Map class

    char colors[4][10]= {"Hearts", "Diamonds", "Clubs", "Spades"}; //cards colors
    char ranks[13][10] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"}; //cards ranks

public:

    int colorIndex,rankIndex;
    int usedCards[4][13]= {0}; //variable for drawn cards
    int Card_Order_Counter=1; //this is used to memorize the order of appearance of the cards
    int start=0; //score value
    int k; //iterates trough all drawn cards to display them
    int k_limit=-1; //limits k so it knows the end of player's cards so computer's cards can be displayed

    bool hold=false; //checks if the player chose to hold
    int op_start=0; //opponent score
    int k2; //opponent's iteration trough all it's cards for display
    double cards_left=0,favorable_cards=0,percentage; //we use those for percentage of winning


    void Randomize()
    {
        srand(time(0));  //setting seed to current time so we don't get same "random" results
        colorIndex=rand()%4;   //generate random pos of a color from arrray
        rankIndex = rand()% 13; //generate random pos of a rank from array
    }

    void DisplayCards()
    {
        system("cls"); // clear the screen
        cout<<"PRESS: 1 - DRAW CARD, 2 - HOLD"<<endl<<endl;
        if (hold==false)
        {
            cout<<"Player score: "<<start<<endl;

            for (k = 1; k <= Card_Order_Counter; k++) // loop through each drawn card
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (usedCards[i][j] == k)
                        {
                            cout << ranks[j] << " of " << colors[i] << endl; // display the card
                        }
                    }
                }
            }
        }
        else
        {
            cout<<"Player score: "<<start<<endl;
            for (k=1; k<=k_limit; k++)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (usedCards[i][j] == k)
                        {
                            cout << ranks[j] << " of " << colors[i] << endl; // display the card
                        }
                    }
                }
            }
            cout<<endl<<endl<<"Opponent score: "<<op_start<<endl;
            for (k=k_limit+1; k<=Card_Order_Counter; k++)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 13; j++)
                    {
                        if (usedCards[i][j] == k)
                        {
                            cout << ranks[j] << " of " << colors[i] << endl; // display the card
                        }
                    }
                }
            }
        }
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
                {  cards_left++;
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

    };

    class Map : public Deck   //This Represents the look of the console
    {
    private:

        int width=30;
        int height=20;

    public:

        void Draw()
        {
            int i,j;

            for (i=0; i<width; i++)   //default map bounds
                cout<<"#";
            cout<<endl;
            for (i=0; i<height; i++)    //default map bounds
            {
                for(j=0; j<width; j++)
                {
                    if (j==0 || j==width-1 || i==height-1)
                        cout<<"#";
                    else cout<<" ";
                }
                cout<<endl;
            }
        }

    };

    class Rules: public Deck //Points logic  //Inheritance
    {
    private:

        int const PointLimit=21;

    public:

        bool GameOver()
        {
            if (start > PointLimit)
            {
                cout << "You Lost.";
                return true;
            }
            else if (start == PointLimit) //
            {
                cout << "You Won.";
                return true;
            }
            else if ((op_start>start && op_start<PointLimit) || op_start==PointLimit) //if opponent reaches 21 or has higher points than user, you lost
            {
                cout<< "You Lost.";
                return true;
            }
            else if (op_start>PointLimit) //if opponent surpasses 21 you won
            {
                cout<<"You Won";
                return true;
            }
            else if (op_start==start && start!=0 && Percentage()<30) //we have to add the percentage condition here too otherwise computer will be able to decide
            {                                                        //because the game will just terminate
                cout<<"Tie";
                return true;
            }
            else
            {
                return false; //return false when score is less than 21
            }
        }

    };

    int main()
    {
        Map m;
        Rules r;
        int x;

        cout<<"PRESS: ANY - START, ESC - EXIT"; //Default screen

        x = getch();

        switch(x) //menu buttons
        {
        case 27: //exit on esc
        {
            return 0;
        }

        default: //start game
        {
            system ("cls"); //clear screen:

            cout<<"PRESS: 1 - DRAW CARD, 2 - HOLD"<<endl<<endl;

            while(r.GameOver()==false) //game goes on as long as you don't have over 21 points
            {

                x = getch(); // to read a single character from the keyboard without it being displayed on screen

                switch(x)
                {
                case '1': // by pressing 1 u draw another card;
                {
                    r.drawCard();
                    break;
                }
                case '2': //by pressing 2 u hold
                {
                    if(r.start==0) //cannot hold without having any points
                    { cout<<"Draw at least a card first!"<<endl;
                      break;
                    }
                    else
                    {r.Hold();
                    break;
                    }

                }
                }
            }
        }

        }

        return 0;
    }
