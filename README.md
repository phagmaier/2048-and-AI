# 2048 AI

## DESCRIPTION
create 2048 and try to create an AI for the game. 
One of the problems I've always had with chess engines is 
that it is not what I think of when i think of AI since for 
the most part humans tell the machine what is valuable. I will 
begin with somewhat the same same strategy but i will hope to develop 
some form of self play with a dynamic algo that will learn what to value 
without any clue and then also give it the ability to dynamically update the values 
of just how important each of these things are. If all else fails i'll at least 
build a NN from scratch in c++ with a working crappy copy of 2048

## WORK IN PROGRESS
Currently I'm doing something dumb and just seeing if i can give a very dumb algorithm some of the most 
obvious and possibly useless information about the game and initially give it a uniform weight to each 
of these pieces of information and then also a model with skewed weights and compare and then essentially
doing a kind of form of regret in order to determine what to weigh more and see if we can get a half decent 
algorithm out of a very dumb approach. It's a pretty straighforward game so gonna see just how easy and simple
and algoithm is needed to actually achieve some form of intellegence or sucess in this game. It's just a fun
project i'm playing around with as i rewrite my very bad poker solver


## File Table

| File | Descripton |
| --------- | --------------------- |
| [brain.cpp](brain.cpp) | functions for the 'AI' |
| [main.cpp](main.cpp) | all the logic for the 2048 game |


