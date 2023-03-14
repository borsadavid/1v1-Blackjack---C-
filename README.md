# 1v1-Blackjack-C++

I.Blackjack plan:
1.Blackjack vs Computer by default rules.
2.Console interactive display : 
#############################
# Opponent:                 #
# *******  ********         #
# *4♠   *  *J♦    *         #
# *  ♦  *  *   ♦  *         #
# *   4♠*  *    J♦*         #
# *******  ********         #                  
# Score: 14                 #
#                           #
#                           #
#                           #
# Player:                   #
# -||- same as opponent     #
# Score:                    #
#                           #
# You Won!/You Lost!        #
# Reward: bet*2             #
#             Money: 20     #
#############################
3. Betting rules, starting currency, loosing when no more money.
4. Opponent percentage of winning (in case of a draw, ex: player score = opponent score = 18),
the computer will check a percentage based on available winning cards and decide if it's worth drawing another
card or leaving a tie, with player's bet returned.

Rules:  You can bet a sum and if you win you get double back, else you loose it.
	You can draw cards to reach 21 or hold.
	If either passes above 21 they lost.
	If you hold, the computer (dealer) will try to surpass your score.
	The cards are randomized and you cannot draw the same card twice.
	The Ace values either 11 or 1 favoring player's cards.

II.Blackjack current progress:

All logics implemented (in case of tie, if computer's odds of winning are over 30%, it will draw another card), 
you can "draw" as many cards as possible, computer tries to beat you after choosing "hold".
Track of Score.
Only text, no visual effects.
No betting implemented yet.
Code explained everywhere.
Simple menu (Play, Exit)
	    (Draw, Hold)

Example seen on console:
PRESS: 1 - DRAW CARD, 2 - HOLD

Player score: 17
8 of Spades
6 of Clubs
3 of Diamonds


Opponent score: 18
5 of Hearts
3 of Hearts
King of Spades
You Lost.

		
