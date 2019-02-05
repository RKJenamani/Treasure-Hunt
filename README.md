# Treasure-Hunt

## Problem Statement

You are given an mXn grid with a resource in any one of the cells. You need to collect the resource using two agents ( use ROS turtlesim simulator ). Once a resource is exhausted it automatically generates another resource at any other random point. Repeat the same procedure again and again.

You are given a black-box that returns the following parameters on function call:

-> No of rows and columns in the grid.\
-> 0 or 1 depending on the status of the cell ( if it contains resource or not ).\
You can only ping for neighbouring nodes. Eg. if an agent is at (2,2) it can only check the status of neighbouring 4 cells. ( (1,2), (2,1), (2,3),  (3,2) ). It returns -1 for invalid calls.\
-> In order to collect the resource, you need to move to the corresponding cell.\
-> Once a resource is selected, it shall be guaranteed that the next resource is not present in a 3x3 grid, centered at the previous resource.\
For better judgement : What about a fix set of resources and collecting them in minimum number of steps? Count will be maintained by black box.

### BlackBox Description:

Import the code and create a class object say obj (Blackbox obj;) and use the following functions.

-> get_rows(): returns no of rows\
-> get_cols(): returns no of cols\
-> move_1(int): to move turtle1. (0,1,2,3) = (up, down, left, right)\
-> move_2(int): to move turtle2. Same mapping.\
-> get_turtle_pos1(): returns a pair of integers for turtle1 positions.\
-> get_turtle_pos2(): returns a pair of integers for turtle2 positions.\
-> check_status(int x, int y): returns the status of corresponding cell. (-1: invalid call, 0: not a resource, 1: resource).

### Important Instructions:

1. The above movement is just to update the positions in blackbox. Make sure to display the movements in turtlesim using ros messages.\
2. Get the header file and shared object file for the blackbox from this [link](https://drive.google.com/drive/folders/1Ky_dTvCQnW8TIkmUbL1RVwj98w7f2RYg)\
3. To compile and link your code: include the above mentioned header file in your source code and while compiling run the following command:\
g++ your_file.cpp -L/path/to/\
folder/of/shared/object/file -ltask\
4. For linking the .so file: put the .so and your program (check.cpp here) in the same folder, then add the path to that folder in LD_LIBRARY_PATH.\
export LD_LIBRARY_PATH=/path/to/shared/object/file:$LD_LIBRARY_PATH


For current folder simply put “.” in place of “/path/to/shared/object/file” (in both 3 and 4) and run ./a.out from there only.\
