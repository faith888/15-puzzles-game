# 15-puzzles-game

### Video demonstartion can be found here 
https://www.youtube.com/embed/IRfkBXDmmdM

###

We had to create an arcade-like version of the 15 puzzles game. This included making a presentation screen, instructions, and various levels for each type of player skill level. We also decided to go with the medieval team for a theme was required for the game. The game also had to have a hint button that would tell the user which button to click next. Also, the scoreboard had to be updated for each person that plays the game.


## Explanation of our approach 

We decided to work on the project together so that putting the entire thing together would be much easier. The move function proved to be the most difficult step, so we approached it similar to the Manhattan Distance  process where we would use the move function and create another function that would find the dx and dy. Once the dx and dy were found the move function would switch the button to where the empty space is therefore switching the places and thus moving the button. For the scoreboard, we used ostreams and istreams to read and write the scores onto a text file which would then be read and shown on the window. We set these scores as a vector of scores so that we could manipulate the scores so only the top five would show up. The Hint button was used with the  Manhattan Distance function indicating that the next button that should be moved is the one with the smallest  Manhattan Distance. The buttons also have a featured that they are green if in the right coordinates and red if they aren’t and we set it up so that the buttons that turn green are added to the score and multiplied by 10. Then after the game is over a new window is opened and the scores are displayed with the user’s name and score in its respective spot


## Conclusions 

This project helped us learn and comprehend the subject since we had to understand it to get the project to work. The utilization of buttons helped us learn how to create the buttons and to understand what functions like the callback do. We also learn how to create Classes and structs. 

## How our program could be improved 

The program could be made better by adding the music on the background and also making the game playable through the arrow keys. We could have attached keys so that when the player touches a specific key the button selected would move in that direction. Our game could be also used for a virtual reality test for young students. Kids in grade school would be able to play their game as if it is in front of them and help them learn critical learning skills.





