#include "Cube.hpp"
#include "Cross.hpp"
#include "Corners.hpp"
#include "Edges.hpp"
#include "OLL.hpp"
#include "PLL.hpp"

#include "Rubik.hpp"

string Rubik::solve (string moves) {
	Cube myCube (false);
	string scramble = format (moves);
	myCube.moves (scramble);
	myCube._moves = "";
	cout << "Step 1: Solve Cross\n";
	Cross::solveCross (myCube);
	myCube.movesStep[0] = myCube._moves;
	myCube.n_movesStep[0] = myCube.n_moves;
	myCube._moves = "";
	myCube.n_moves = 0;
	//cout << "Number of movements: " << myCube.n_movesStep[0] << endl;
	//cout << "Moves: " << myCube.movesStep[0] << endl << endl;

	cout << "Step 2: Solve Corners\n";
	Corners::solveCorners (myCube);

	myCube.movesStep[1] = myCube._moves;
	myCube.n_movesStep[1] = myCube.n_moves;
	myCube._moves = "";
	myCube.n_moves = 0;
	//cout << "Number of movements: " << myCube.n_movesStep[1] << endl;
	//cout << "Moves: " << myCube.movesStep[1] << endl << endl;

	cout << "Step 3: Solve Edges\n";
	Edges::solveEdges (myCube);

	myCube.movesStep[2] = myCube._moves;
	myCube.n_movesStep[2] = myCube.n_moves;
	myCube._moves = "";
	myCube.n_moves = 0;
	//cout << "Number of movements: " << myCube.n_movesStep[2] << endl;
	//cout << "Moves: " << myCube.movesStep[2] << endl << endl;


	cout << "Step 4: Solve OLL\n";
	OLL::solveOLL (myCube);
	myCube.movesStep[3] = myCube._moves;
	myCube.n_movesStep[3] = myCube.n_moves;
	myCube._moves = "";
	myCube.n_moves = 0;
	//cout << "Number of movements: " << myCube.n_movesStep[3] << endl;
	//cout << "Moves: " << myCube.movesStep[3] << endl << endl;


	cout << "Step 5: Solve PLL\n";
	PLL::solvePLL (myCube);
	myCube.movesStep[4] = myCube._moves;
	myCube.n_movesStep[4] = myCube.n_moves;
	myCube._moves = "";
	myCube.n_moves = 0;
	//cout << "Number of movements: " << myCube.n_movesStep[4] << endl;
	//cout << "Moves: " << myCube.movesStep[4] << endl<<endl;

	//cout << "End of solution " << endl;
	//cout <<"Total moves: "<< myCube.n_movesStep[0] + myCube.n_movesStep[1] + myCube.n_movesStep[2] + myCube.n_movesStep[3]+ myCube.n_movesStep[4] << endl;
	return myCube.movesStep[0] + myCube.movesStep[1] + myCube.movesStep[2] + myCube.movesStep[3] + myCube.movesStep[4];
	// myCube.output();
}

string Rubik::format (string s) {
	string formatted;

	for ( int i = 0; i < s.length (); ++i ) {
		if ( s[i] == '\'' ) {
			formatted += s[i - 1];
			formatted += s[i - 1];
		} else if ( s[i] == '2' ) {
			formatted += s[i - 1];
		} else if ( s[i] == ' ' ) {
		} else {
			formatted += s[i];
		}
	}

	return formatted;
}