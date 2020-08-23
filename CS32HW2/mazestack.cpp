#include<iostream>
#include<stack>

class Coord
{
public:
	Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
	int r() const { return m_row; }
	int c() const { return m_col; }
private:
	int m_row;
	int m_col;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	//creating a stack of coords 
	std::stack<Coord> coordStack;

	//saving the start and end as coords 
	Coord start(sr, sc);
	Coord end(er, ec);

	//Push the starting coordinate (sr,sc) onto the coordinate stack
	coordStack.push(start);
	
	//update maze[sr][sc] to indicate that the algorithm has encountered
	maze[sr][sc] = 'E';

	// While the stack is not empty
	while(!coordStack.empty()){
		//Pop the top coordinate off the stack. This gives you the current
		//(r, c) location that your algorithm is exploring.
		Coord current = coordStack.top();
		coordStack.pop(); 

		//If the current (r,c) coordinate is equal to the ending coordinate, then return true
		if (current.c() == end.c() && current.r() == end.r()) {
			return true;
		}

		//if not at the end coordinate,
		//Check each place you can move from the current cell

		//If you can move SOUTH and haven't encountered that cell yet
		if (maze[current.r() + 1][current.c()] == '.' && maze[current.r() + 1][current.c()] != 'E') {
			//push the coordinate (r+1,c) onto the stack
			Coord newCurrent(current.r() + 1, current.c());
			coordStack.push(newCurrent);
			//update maze[r + 1][c] to indicate the algorithm has encountered it.
			maze[current.r() + 1][current.c()] = 'E';
		}

		//If you can move WEST and haven't encountered that cell yet,
		if (maze[current.r()][current.c() -1] == '.' && maze[current.r()][current.c() -1] != 'E') {
			//push the coordinate (r,c-1) onto the stack 
			Coord newCurrent(current.r(), current.c() - 1);
			coordStack.push(newCurrent);
			//update maze[r][c - 1] to indicate the algorithm has encountered it.
			maze[current.r()][current.c() - 1] = 'E';
		}

		//If you can move NORTH and haven't encountered that cell yet,
		if (maze[current.r()-1][current.c()] == '.' && maze[current.r()-1][current.c()] != 'E') {
			//push the coordinate(r - 1, c) onto the stack
			Coord newCurrent(current.r()-1, current.c());
			coordStack.push(newCurrent);
			//update maze[r - 1][c] to indicate the algorithm has encountered it.
			maze[current.r() - 1][current.c()] = 'E';
		}

		//If you can move EAST and haven't encountered that cell yet,
		if (maze[current.r()][current.c() + 1] == '.' && maze[current.r()][current.c() + 1] != 'E') {
			//push the coordinate (r,c+1) onto the stack
			Coord newCurrent(current.r(), current.c() + 1);
			coordStack.push(newCurrent);
			//update maze[r][c + 1] to indicate the algorithm has encountered it.
			maze[current.r()][current.c() + 1] = 'E';
		}
	}

	//There was no solution
	return false; 
}

int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','.','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8,8))
		std::cout << "Solvable!" << std::endl;
	else
		std::cout << "Out of luck!" << std::endl;
}