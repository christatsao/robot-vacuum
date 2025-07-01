
# Overview
Design and implement a basic algorithm for an automated robot that must clean a rectangular area that is populated with random obstacles.  Your robot is so powerful that it can sweep up both garbage and obstacles, but you do not want to sweep up obstacles if you want to receive full credit.  Your robot can only move 1  square at a time in any direction (including diagonally), but only using the moveTo() function provide.



# Background
A grid is filled with garbage and obstacles.  Your robot is so powerful that it can sweep up both!  But you only want to sweep up the garbage.  Our "room" is just a square grid represented by a 2D grid array of single characters.  A piece of garbage is denoted by the period character '.'  (note we use single quotes in cpp for characters!).  An obstacle is denoted by a the star character '*'.   Your grid goes from row zero to row numrows-1 and from column zero to numcols-1.  Your robot can only move 1 square at any time in any direction (it can move diagonally).  But be careful not to move out of the valid range of the grid - you could crash your program.

 
# Example Output
HW - Robot Vacuum (starter)
```
Dirty Room before sweeping:
--------------------------------------------------------------
| .  .  .  *  .  .  .  .  .  *  .  .  .  .  .  .  .  .  .  . |
| *  .  .  .  .  .  .  *  .  .  .  *  *  .  .  .  .  .  *  . |
| .  .  *  *  .  .  .  *  *  .  *  .  .  .  .  .  .  .  .  . |
| *  .  .  .  .  *  .  .  *  .  *  .  .  .  *  .  .  .  .  . |
| .  *  .  .  .  .  *  .  .  .  .  .  .  .  .  *  .  .  .  . |
| .  .  .  .  .  *  .  *  *  .  .  .  *  .  .  .  .  .  .  * |
| .  .  .  *  .  .  .  .  *  .  .  .  .  .  .  .  *  .  *  * |
| .  .  .  .  *  *  .  .  *  *  .  .  .  *  *  .  .  .  *  . |
| .  .  .  .  .  .  .  *  .  .  *  *  .  .  .  .  .  .  .  . |
| .  .  .  .  .  *  .  *  .  .  .  .  .  .  *  .  .  *  .  . |
| .  *  .  .  *  .  *  .  *  *  .  .  .  *  *  .  *  .  .  . |
| .  .  .  .  .  .  *  .  .  .  .  .  .  .  .  *  .  *  .  * |
| *  .  .  .  .  .  .  *  *  *  *  *  .  .  .  *  *  .  .  . |
| *  .  *  *  .  .  *  .  .  *  *  .  .  .  .  .  .  .  .  . |
| .  .  .  .  .  .  .  .  .  .  .  .  *  .  .  .  .  .  .  . |
| .  .  .  .  .  *  .  .  .  *  .  *  .  .  .  *  .  *  .  . |
| *  *  *  .  *  .  *  .  *  *  .  *  .  .  *  .  .  .  .  . |
| *  *  *  .  .  .  .  .  .  .  .  .  .  .  *  .  .  .  .  * |
| .  .  *  .  *  .  *  .  .  .  .  *  .  .  .  .  .  .  .  . |
| .  .  .  *  *  .  *  *  .  .  .  .  .  *  *  *  .  *  .  . |
--------------------------------------------------------------

Clean Room after sweeping:
--------------------------------------------------------------
| .  .  .  *  .  .  .  .  .  *  .  .  .  .  .  .  .  .  .  . |
| *     .  .  .  .  .  *  .  .  .  *  *  .  .  .  .  .  *  . |
| .  .  *  *  .  .  .  *  *  .  *  .  .  .  .  .  .  .  .  . |
| *  .  .  .  .  *  .  .  *  .  *  .  .  .  *  .  .  .  .  . |
| .  *  .  .  .  .  *  .  .  .  .  .  .  .  .  *  .  .  .  . |
| .  .  .  .  .  *  .  *  *  .  .  .  *  .  .  .  .  .  .  * |
| .  .  .  *  .  .  .  .  *  .  .  .  .  .  .  .  *  .  *  * |
| .  .  .  .  *  *  .  .  *  *  .  .  .  *  *  .  .  .  *  . |
| .  .  .  .  .  .  .  *  .  .  *  *  .  .  .  .  .  .  .  . |
| .  .  .  .  .  *  .  *  .  .  .  .  .  .  *  .  .  *  .  . |
| .  *  .  .  *  .  *  .  *  *  .  .  .  *  *  .  *  .  .  . |
| .  .  .  .  .  .  *  .  .  .  .  .  .  .  .  *  .  *  .  * |
| *  .  .  .  .  .  .  *  *  *  *  *  .  .  .  *  *  .  .  . |
| *  .  *  *  .  .  *  .  .  *  *  .  .  .  .  .  .  .  .  . |
| .  .  .  .  .  .  .  .  .  .  .  .  *  .  .  .  .  .  .  . |
| .  .  .  .  .  *  .  .  .  *  .  *  .  .  .  *  .  *  .  . |
| *  *  *  .  *  .  *  .  *  *  .  *  .  .  *  .  .  .  .  . |
| *  *  *  .  .  .  .  .  .  .  .  .  .  .  *  .  .  .  .  * |
| .  .  *  .  *  .  *  .  .  .  .  *  .  .  .  .  .  .  .  . |
| .  .  .  *  *  .  *  *  .  .  .  .  .  *  *  *  .  *  .  . |
--------------------------------------------------------------
SCORE:
----------------------
Total squares in grid = 400
Garbage total (original): 298
Obstacles total (original): 102
Garbage swept up: 1
Garbage Missed = 297 (minus 297 points)
Obstacles Missing = 0 out of 102 (minus 0 points)
Total Moves taken = 1
Cleaning efficiency = garbage swept up/totalMoves = %100)
Final normalized score out of 100 possible = 25  (this is your final score)
Hmmm - might want to call in some iRobot back-up for help.  Let me know if you have questions!

```


 

 


Points
100
Submitting
a text entry box, a website url, or a file upload
