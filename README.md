# lem-in

• Algorithmic project which finds all the shortest possible paths in a graph

• The program will receive the data describing the ant farm from the standard output in the following format:
number_of_ants
the_rooms
the_links


• The ant farm is defined by the following links:

##start


Which corresponds to the following representation:

             _______________
            /               \
      _____[5]----[3]---[1] |
     /             |    /   |
    [6]----[0]----[4   /    |
     \    ________/|  /     |
      \  /         [2]_____/
       [7]_________/

• There are two parts:
◦ The rooms, which are defined by: name coord_x coord_y ◦ The links, which are defined by: name1-name2
◦ All of it is broken by comments, which start with #

• Lines that start with ## are commands modifying the properties of the line that comes right after (no other commands are supported for now).
• For example, ##start signals the ant farm’s entrance and ##end its exit.
• If there isn’t enough data to process normally or there are any non compliant or empty lines my program displays an ERROR and an appropriate message

• The goal is to read the farm correctly, make a graph out of it and to find the shortest way to send all the ants across the farm from ##start room to ##end room.
Quickest way means the solution with the least number of lines, respecting theo utput format requested below.
• At the beginning, all the ants are in the ##start room.
• Each room can only contain one ant at a time. (except at ##start and ##end which can contain as many ants as necessary.)
• At each turn I will only display the ants that moved.
• At each turn I can move each ant only once and through a tube (the room at the receiving end must be empty
• The result must be displayed on the standard output in the following format:
  number_of_ants
  the_rooms
  the_links
  Lx-y Lz-w Lr-o ...
  
  x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

NOTE: my program works well with finding several possible paths, but works poorly in case of intersection as in following example:
     
      [start]
       / |
     [3] [1]--[5]
     /    |    |
    [4]--[2]   [6]
          |    /
          [end]
In this case, my program will find the shortest path (start-1-2-end) and send the ants across the farm via this path, although it would be better to send them via 2 paths:
(start-3-4-2-end) (start-1-5-6-end).
Planning to add this possibility in the future
