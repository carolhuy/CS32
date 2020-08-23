/*If the start location is equal to the ending location, then we've
solved the maze, so return true.
Mark the start location as visted.
For each of the four directions,
If the location one step in that direction(from the start
	location) is unvisited, and there is a path starting from that
	location(and ending at the same ending location as in the
		current call).
	then return true.
	Return false.*/
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	//If the start location is equal to the ending location, then we've
	//solved the maze, so return true.
	if (sr == er && sc == ec) {
		return true;
	}

	//Mark the start location as visted.
	maze[sr][sc] = 'E';

	//For each of the four directions, if step is unvisted and moving in direction is possible 
	//SOUTH 
	if (maze[sr + 1][sc] != 'E' && maze[sr + 1][sc] == '.') {
		//if path is found when reaching that step 
		if (pathExists(maze,sr+1,sc,er,ec)) {
			return true;
		}
	}

	//WEST
	if (maze[sr][sc-1] != 'E' && maze[sr][sc-1] == '.') {
		//if path is found when reaching that step 
		if (pathExists(maze, sr, sc-1, er, ec)) {
			return true;
		}
	}

	//NORTH
	if (maze[sr -1][sc] != 'E' && maze[sr -1][sc] == '.') {
		//if path is found when reaching that step 
		if (pathExists(maze, sr -1, sc, er, ec)) {
			return true;
		}
	}

	//EAST 
	if (maze[sr][sc+1] != 'E' && maze[sr][sc+1] == '.') {
		//if path is found when reaching that step 
		if (pathExists(maze, sr, sc+1, er, ec)) {
			return true;
		}
	}

	//all cases fail - no path found 
	return false;

}