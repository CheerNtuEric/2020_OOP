#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#define INFINITY 10000
using namespace std;
int mazeRowSize = 0, mazeColSize = 0;

vector <vector<char> > GetMazeInfo(fstream& file, pair<int, int>& StartPos, pair<int, int>& EndPos) {
	vector< vector<char> > Maze;


	file >> mazeRowSize >> mazeColSize;

	for (int i = 0; i < mazeRowSize; i++) {
		vector<char> row;
		for (int j = 0; j < mazeColSize; j++) {
			char temp;
			file >> temp;

			row.push_back(temp);

			if (temp == 'S') {
				StartPos.first = i;
				StartPos.second = j;
			}
			if (temp == 'E') {
				EndPos.first = i;
				EndPos.second = j;
			}
		}
		Maze.push_back(row);
	}

	return Maze;
}

vector< vector<int> > DistanceInfo(const vector< vector<char> >& Maze, int *d[31]) {
	// TODO:
	// Create a 2D vector to store the corresponding distance of the maze.
	// Initialize the distance to infinity
	vector< vector<int> > DisMaze;
    for(int i = 0 ; i < mazeRowSize ; i++)
    {
        vector<int> row;
        for(int j = 0 ; j< mazeColSize ; j++)
        {
            if(d[i][j] != INFINITY && Maze[i][j] != '#')
                row.push_back(d[i][j]);
            else
                row.push_back(Maze[i][j]);
        }
    }

}


int main() {
    //open the file
	fstream  file;
	file.open("input.txt");
	if (!file.is_open()) {
		cout << "Failed to open file!" << endl;
		return 0;
	}

	int TestCase = 0;
	file >> TestCase;


	while (TestCase) {
		pair<int, int> StartPos, EndPos;
		vector< vector<char> > Maze = GetMazeInfo(file, StartPos, EndPos);

		// Calculate the shortest path of the starting point and the ending point.
		// You should print something out here according to the output sample format.
        int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
        int d[30+1][30+1];
        //int Total =mazeRowSize * mazeColSize;
        bool succeed = false;
        queue< pair<int,int> > que;

        for(int i = 0 ; i < 30 ; i++)
            for(int j =0 ; j < 30 ; j++)
                d[i][j] = INFINITY;

        que.push(pair<int, int>(StartPos.first, StartPos.second ) ) ;
		d[StartPos.first][StartPos.second] = 0;

		while(que.size() )
        {
            pair<int , int > p = que.front();
            que.pop();
            int i ;
            for(i = 0 ; i < 4 ; i++)
            {
                int nx = p.first + dx[i];
                int ny = p.second + dy[i];
                if(nx < 0 || ny < 0 || nx >= mazeRowSize || ny >=mazeColSize)
                    continue;
                /*cout<<nx<<" "<<ny<<" ";
                cout<<d[nx][ny]<<endl;*/
                //cout<<mazeColSize<< " " <<mazeRowSize<<" "<<endl;
                if(Maze[nx][ny] != '#'
                   && 0<=nx && nx <mazeRowSize
                   && 0<=ny && ny <mazeColSize
                   &&d[nx][ny] == INFINITY)
                {
                    //cout<<nx<<" "<<ny<<endl;
                    que.push( pair<int, int>(nx, ny) );
                    //cout<<"*"<<endl;
                    d[nx][ny] =d[p.first][p.second]+1;
                   // cout<<"*"<<endl;
                    if(nx == EndPos.first && ny ==EndPos.second){
                        succeed = true;
                        break;

					}

                }
            }
            if(i != 4) break;
        }
        //print out

        if(succeed)
        {
            int k = d[EndPos.first][EndPos.second];
            int l = EndPos.first, m = EndPos.second;
            k--;
            Maze[EndPos.first][EndPos.second] = 'o';
            Maze[StartPos.first][StartPos.second] = 'o';
            while(k){
                for(int i = 0 ; i < 4 ; i++)
                {
                    int nx = l + dx[i];
                    int ny = m + dy[i];
                    if(nx < 0 || ny < 0 || nx >= mazeRowSize || ny >=mazeColSize)
                        continue;
                    if(d[nx][ny] == k && Maze[nx][ny] !='#')
                    {
                        k--;
                        Maze[nx][ny] = 'o';
                        //cout<<"k";
                        l = nx;
                        m = ny;
                        break;
                    }
                }
            }
            for(int i = 0 ; i < mazeRowSize ; i++)
            {
                for(int j = 0 ; j< mazeColSize ; j++)
                    cout<<Maze[i][j];
                cout<<endl;
            }
        }
        else
            cout <<"Trapped !"<<endl;

        cout<<endl;
		TestCase--;
	}

	return 0;

}
