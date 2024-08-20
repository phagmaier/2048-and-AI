# 2048 AI

## DESCRIPTION
CREATE A PLAYABLE 2048 and try to create an AI for the game. 
One of the problems I've always had with chess engines is 
that it is not what I think of when i think of AI since for 
the most part humans tell the machine what is valuable it is their intellegence from my understanding that constitutes the 
intellegence which is the engine and the machine is just 
used to evalue states quicker and go through the game tree. 
Currently my algorithm is incredibly stupid. I was lazy and didn't 
want to install pytorch or download my own autograd so I just 
have the computer play 100 games on each decision for each possible move 
and then it makes the move that yeilds the heighst score.
The logic of the algo is in the file [nn (not really a NN)](Engine/src/nn.cpp)
and the actual shitty version of the game made using raylib
can be found in [main.cpp](src/main.cpp)
or you can check in bin and just run the cmake file

## WORK IN PROGRESS
CURRENTLY IT IS INCREDIBLY SLOW AND NOT OPTIMAL BUT IT
DOES USUALLY BEAT THE GAME EVEN IF 100 iterations per 
decision is a lot.
</br>
I also created a auto grad Value class so that we can create a hand made neural network trained 
originally on my search results and then once we have decent starting weights we'll use those for the 
initial weights to essentially do a search and bootstrap of our neural network and see how good we can 
make this thing

## File Table

| File | Descripton |
| --------- | --------------------- |
| [main](src/main.cpp) | Simple bad GUI for 2048 made in raylib |
| [nn](Engine/src/nn.cpp) | The actual dumb solver (not currently a NN)|
| [game](Engine/src/game.cpp) | The logic for the game of 2048 and some helper functions |

## HOW TO RUN

You can run the really bad GUI of 2048 by either manually compiling 
[main](src/main.cpp)
which requires raylib or you can run the cmake file in the root dir.
<br/>
To run the 'solver' you can either manually compile 
[main](Engine/src/main.cpp) in the Engine directory or run the cmake 
file which is in the root directory of Engine


