# Hunt the Wumpus
![console output](https://github.com/cyberaktiv/colout/blob/master/test/output.png?raw=true)
Оne of my completed exercises from the book "Programming - Principles and Practice Using C ++" by Bjarne Stroustrup. 
This is project of Code::Blocks with FLTK Library (compiling options: **-std=c99**).

## Description
##### Player wins if:
- arrow hits in the Wumpus

##### Player lose if:
- he comes into the room with Wumpus
- he comes into the room with pit
- bat tosses him into the room with Wupmus
- bat tosses him into the room with pit
- Wupmus comes into the room with him

##### Feeling of player if near:
- Wumpus - "I smell the wumpus"
- pit - "I feel a breeze"
- bat - "I hear a bat"

##### Additionally:
- Wampus can not go into room with pit
- arrow can fly in three interconnected rooms
- after each shot, Wampus moves to a random next room
- Wampus moves if player comes into room with an even number		
- number of arrows - 3

## Notes
Directory "Graph_lib" was take from http://stroustrup.com/ with my some changes.