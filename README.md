# Advent-Of-Code-2024

## Day 1 
### Part 1
Not too bad, very good warm up, brain havent rot in NS yet XD
Solution is straight forward, just compare and add
### Part 2 
Still not too bad, involved more validation and checking as well as multiplication, data types is still not a concern

## Day 2
### Part 1 
Didnt read my input, coded based off the example input they gave which led me to using arrays as I initially thought that the numbers for each row would be fixed, READ YOUR INPUT BEFORE CODING ARGHHHHHH
### Part 2 
Took me forever to complete, brute force all the way, there has to be a wayyyyy more efficient solution to it...

## Day 3
### Part 1 
Might seem daunting but its very very doable
### Part 2
I hate regex, implemented the edge cases with the help of others, still no idea what went wrong ._.

## Day 4 
### Part 1
Very straightforward algorithm, quite a chill day 
### Part 2
Straightforward too, part 1 was harder XD

## Day 5 
### Part 1 
Different method of parsing in the input file, nothing too complicated. 
### Part 2 
Highlighted the usage and the idea of comparators, making a sorting algorithm within the puzzle's domain, nothing too tough

## Day 6 
### Part 1 
Rather straightforward, just turn the guard direction when needed to and mark out the visited points, tally up the visited the points and voila 
### Part 2 
Brtually brute force the path of the guard by adding a wall infront of the guard path which is stored int a queue, and the testing if the guard is stuck in a loop or it can exit.

## Day 7 
### Part 1 
Quite easy, need to be careful with the data typing, used long long -- numbers are too big
### Part 1 
Changed the operators configuration to base 3 instead of only using 2 and brute force the numbers all the way, filtered the ones that are valid first then carry one with the rejected pile

## Day 8 
### Part 1 
Question phrasing was rather confusing. Mostly involved nodes and combinatorics principles. Used directional vectors concepts to find the location of antinodes as well as inbuilt cpp algorithm header to sort and eliminate duplicate antinodes
### Part 2 
Not too hard either, just considered the antenna itself was an antinode and eliminated all duplicate antinode coordinates

## Day 9 
### Part 1
Not too hard, hard is about to store the actual value in a point
### Part 2
Manipulation of the vector got a little confusing, had to redo a few times

## Day 10
All about depth first search in this problem cuh
### Part 1 
Implemented a depth first search algorithm to find how many 9s can each0 reach, using a set to make each path unique so that i don't count more than one when a 0 reached a 9 
### Part 2 
Same as part 1 but easier, just needed to count the amount of paths each 0 took to find a 9 and tallied up the amount of paths.

## Day 11 
### Part 1 
Used a vector and stack to process the numbers before pushing it back to the vector then compute the size to get the total amunt of stones after blinking 25 times 
### Part 2 
Vector size scaled exponentially, with the help of online redditors, i changed to use a map to store the total amount of numbers seen in a map and then compute the total amount of stones, since the order of the stones in the container doesnt really matter 
