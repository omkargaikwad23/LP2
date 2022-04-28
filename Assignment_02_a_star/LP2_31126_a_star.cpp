#include <bits/stdc++.h>
using namespace std;
typedef vector<int>vi;
typedef pair<int, int> pii;
#define mp make_pair

class Cell{
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
    friend class A_StarAlgorithm;
public:
    Cell(){}
};

class A_StarAlgorithm{
private:
    int row, col;
    vector<vi>path;
    pii src, dest;
public:
    A_StarAlgorithm(){}

    void setRowCol(int, int);
    void addObstacles(int, int);
    void displayPath();
    void setSource(int, int);
    void setDest(int, int);
    void resetPath(){path.clear();};
    bool isValidCell(int, int);
    bool isOpen(int, int);
    bool isDestination(int, int);
    double calculateHval(int r, int c);
    void aStarSearch();
    void tracePath(vector<vector<Cell>>);
};

void A_StarAlgorithm::setRowCol(int row, int col){
    this->row = row;
    this->col = col;
    path.resize(row, vi(col, 0));
}

void A_StarAlgorithm::addObstacles(int r, int c){
    path[r][c] = 1;
}

void A_StarAlgorithm::displayPath(){
    cout << "\n<<-----------PATH----------->>\n";
    cout << "\t---- " << row << "*" << col << " ----\n\n";
    cout << "\t | ";
    
    for(int i=0; i<col; i++){
        cout << i << " ";
    }
    cout << "\n";
    for(int i=0; i<row; i++){
        cout << "\t" << i << "| ";
        for(int j=0; j<col; j++){
            cout << path[i][j] << " ";
        }
        cout << "\n";
    }
}

void A_StarAlgorithm::setSource(int r, int c){
    if(!isValidCell(r, c) || !isOpen(r, c)){
        printf("Entered source is invalid\n");
        return;
    }
    src.first = r, src.second = c;
}

void A_StarAlgorithm::setDest(int r, int c){
    if(!isValidCell(r, c) || !isOpen(r, c)){
        printf("Entered destination cell is invalid\n");
        return;
    }
    dest.first = r, dest.second = c;
}

bool A_StarAlgorithm::isValidCell(int r, int c){
    return (r>=0 && r<row && c>=0 && c<col);
}

// return true if cell is not blocked
bool A_StarAlgorithm::isOpen(int r, int c){
    return path[r][c] == 1 ? false : true;
}

bool A_StarAlgorithm::isDestination(int r, int c){
    return (dest.first==r && dest.second==c);
}

double A_StarAlgorithm::calculateHval(int r, int c){
    return (double)sqrt((r-dest.first)*(r-dest.first) + (c-dest.second)*(c-dest.second));
}

void A_StarAlgorithm::aStarSearch(){
    bool closedList[row][col];
    //no cell has been included in closed list
    memset(closedList, false, sizeof(closedList));
    // <f, <i, j>> where f = g + h
    set<pair<double, pii>>openList;

    //stores the details of that cell
    vector<vector<Cell>>cellInfo;
    cellInfo.resize(row, vector<Cell>(col));
    int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			cellInfo[i][j].f = FLT_MAX;
			cellInfo[i][j].g = FLT_MAX;
			cellInfo[i][j].h = FLT_MAX;
			cellInfo[i][j].parent_i = -1;
			cellInfo[i][j].parent_j = -1;
		}
	}

    // starting node
    i = src.first, j = src.second;
    cellInfo[i][j].f = 0.0;
    cellInfo[i][j].g = 0.0;
    cellInfo[i][j].h = 0.0;
    cellInfo[i][j].parent_i = i;
    cellInfo[i][j].parent_j = j;

    openList.insert(mp(0.0, mp(i, j)));

    bool foundDest = false;

    while(!openList.empty()){
        auto p = openList.begin();
        openList.erase(openList.begin());

        i = p->second.first;
        j = p->second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
        /*
        Cell-->Popped Cell (i, j)
		N --> North	 (i-1, j)
		S --> South	 (i+1, j)
		E --> East	 (i, j+1)
		W --> West	 (i, j-1)
        */

        //TODO: North
        if(isValidCell(i-1, j)){
            // If destination cell is same as the current successor
            if(isDestination(i-1, j)){
                cellInfo[i-1][j].parent_i = i;
                cellInfo[i-1][j].parent_j = j;
				printf("The milk is found\n");
                tracePath(cellInfo);
                foundDest = true;
                return;
            }
            // If successor is not on closed list or blocked then--
            else if(closedList[i-1][j]==false && isOpen(i-1, j)){
                gNew = cellInfo[i][j].g + 1.0;
                hNew = calculateHval(i-1, j);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
				// the open list or if it is better then update it
                if(cellInfo[i-1][j].f==FLT_MAX || cellInfo[i-1][j].f > fNew){
                    openList.insert(mp(fNew, mp(i-1, j)));
                    cellInfo[i - 1][j].g = gNew;
                    cellInfo[i - 1][j].h = hNew;
                    cellInfo[i - 1][j].f = fNew;
                    cellInfo[i - 1][j].parent_i = i;
                    cellInfo[i - 1][j].parent_j = j;
                }
            }
        }

        //TODO: South
        if(isValidCell(i+1, j)){
            if(isDestination(i+1, j)){
                cellInfo[i+1][j].parent_i = i;
                cellInfo[i+1][j].parent_j = j;
				printf("The milk is found\n");
                tracePath(cellInfo);
                foundDest = true;
                return;
            } 
            else if(closedList[i+1][j]==false && isOpen(i+1, j)){
                gNew = cellInfo[i][j].g + 1.0;
                hNew = calculateHval(i, j+1);
                fNew = gNew + hNew;

                if(cellInfo[i+1][j].f==FLT_MAX || cellInfo[i+1][j].f > fNew){
                    openList.insert(mp(fNew, mp(i+1, j)));
                    cellInfo[i + 1][j].g = gNew;
                    cellInfo[i + 1][j].h = hNew;
                    cellInfo[i + 1][j].f = fNew;
                    cellInfo[i + 1][j].parent_i = i;
                    cellInfo[i + 1][j].parent_j = j;
                }
            }
        }
        //TODO: East
        if(isValidCell(i, j+1)){
            if(isDestination(i, j+1)){
                cellInfo[i][j+1].parent_i = i;
                cellInfo[i][j+1].parent_j = j;
				printf("The milk is found\n");
                tracePath(cellInfo);
                foundDest = true;
                return;
            }
            else if(!closedList[i][j+1] && isOpen(i, j+1)){
                gNew = cellInfo[i][j].g + 1.0;
                hNew = calculateHval(i, j+1);
                fNew = gNew + hNew;

                if(cellInfo[i][j+1].f == FLT_MAX || cellInfo[i][j+1].f > fNew){
                    openList.insert(mp(fNew, mp(i, j+1)));
                    cellInfo[i][j + 1].f = fNew;
					cellInfo[i][j + 1].g = gNew;
					cellInfo[i][j + 1].h = hNew;
					cellInfo[i][j + 1].parent_i = i;
					cellInfo[i][j + 1].parent_j = j;
                }
            }
        }

        //TODO: West
        if(isValidCell(i, j-1)){
            if(isDestination(i, j-1)){
                cellInfo[i][j - 1].parent_i = i;
				cellInfo[i][j - 1].parent_j = j;
				printf("The milk is found\n");
				tracePath(cellInfo);
				foundDest = true;
				return;
            }
            else if(!closedList[i][j-1] && isOpen(i, j-1)){
                gNew = cellInfo[i][j].g + 1.0;
				hNew = calculateHval(i, j - 1);
				fNew = gNew + hNew;

                if (cellInfo[i][j - 1].f == FLT_MAX
					|| cellInfo[i][j - 1].f > fNew) {
					openList.insert(make_pair(
						fNew, make_pair(i, j - 1)));

					// Update the details of this cell
					cellInfo[i][j - 1].f = fNew;
					cellInfo[i][j - 1].g = gNew;
					cellInfo[i][j - 1].h = hNew;
					cellInfo[i][j - 1].parent_i = i;
					cellInfo[i][j - 1].parent_j = j;
				}
            }
        }
    }
    if(foundDest == false)
        printf("Cat failed to find the milk\n");
    return;
}

void A_StarAlgorithm::tracePath(vector<vector<Cell>> cellInfo){
    int di = dest.first;
    int dj = dest.second;
    stack<pii>Path;

    while (!(cellInfo[di][dj].parent_i == di && cellInfo[di][dj].parent_j == dj)) {
		Path.push(make_pair(di, dj));
		int temp_row = cellInfo[di][dj].parent_i;
		int temp_col = cellInfo[di][dj].parent_j;
		di = temp_row;
		dj = temp_col;
	}

	Path.push(make_pair(di, dj));

    cout << "Path length of the route is: " << Path.size()-1 << "\n";
    cout << "The Path is:" << "\n";

	while (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		cout << " ->(" << p.first << ", " << p.second << ")";
	}
    cout << "\n";
    return;
}

int main()
{
    int choice, row, col, n;
    A_StarAlgorithm obj;

    do{
        cout << "\n\n<<-----------MENU----------->>\n";
        cout << "1. Provide dimention of matrix" << "\n";
        cout << "2. Add obstacles to the path" << "\n";
        cout << "3. Display path" << "\n";
        cout << "4. Place the position of cat" << "\n";
        cout << "5. Place the position of milk" << "\n";
        cout << "6. Find optimal path using A star algo" << "\n";
        cout << "7. Reset the path" << "\n";
        cout << "8. Exit the game" << "\n";
        cout << "<<-------------------------->>" << endl;
		cout << "\nEnter your choice (1-6): ";
		cin >> choice;

        switch(choice){
            case 1:
                cout << "\nEnter dimention of matrix (row*col): ";
                cin >> row >> col;
                obj.setRowCol(row, col);
                break;
            case 2:
                cout << "\nEnter the number of obstacles: ";
                cin >> n;
                for(int i=0; i<n; i++){
                    cout << "enter position(r, c): ";
                    cin >> row >> col;
                    obj.addObstacles(row, col);
                }
                cout << "Obstacles has been created";
                break;
            case 3:
                obj.displayPath();
                break;
            case 4:
                cout << "Enter cat's initial position (r, c): ";
                cin >> row >> col;
                obj.setSource(row, col);
                break;
            case 5:
                cout << "Enter coordinates of milk position (r, c):";
                cin >> row >> col;
                obj.setDest(row, col);
                break;
            case 6:
                obj.aStarSearch();
                break;
            case 7:
                obj.resetPath();
                break;
            default:
                break;
        }
    } while (choice != 8);
    cout << "Good Bye!\n";
    return 0;
}