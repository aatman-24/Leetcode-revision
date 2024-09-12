### Simulation of Queue

In some of the queue questions, they are giving some situations (playing game, perform in this order). To solve such questions, use the queue
and simulate whatever they said it. Because it will not take more than O(NlogN) time. 

To identify, whether question can be solved using this approach or not, 

Calculate the time complexity roughly, each round how many elements got out of the game. If it is N/2 then we can solve this using O(NlogN).
If not enough elements got dropped then we can't use this approach. 
