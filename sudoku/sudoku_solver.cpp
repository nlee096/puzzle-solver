#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>
using namespace std;

int coord_to_sector[9][9] = 
    {{0,0,0,1,1,1,2,2,2},
     {0,0,0,1,1,1,2,2,2},
     {0,0,0,1,1,1,2,2,2},
     {3,3,3,4,4,4,5,5,5},
     {3,3,3,4,4,4,5,5,5},
     {3,3,3,4,4,4,5,5,5},
     {6,6,6,7,7,7,8,8,8},
     {6,6,6,7,7,7,8,8,8},
     {6,6,6,7,7,7,8,8,8}
    };

int sector_to_coord[9][9][2] = 
    {{{0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {2,2}},
     {{0,3}, {0,4}, {0,5}, {1,3}, {1,4}, {1,5}, {2,3}, {2,4}, {2,5}},
     {{0,6}, {0,7}, {0,8}, {1,6}, {1,7}, {1,8}, {2,6}, {2,7}, {2,8}},
     {{3,0}, {3,1}, {3,2}, {4,0}, {4,1}, {4,2}, {5,0}, {5,1}, {5,2}},
     {{3,3}, {3,4}, {3,5}, {4,3}, {4,4}, {4,5}, {5,3}, {5,4}, {5,5}},
     {{3,6}, {3,7}, {3,8}, {4,6}, {4,7}, {4,8}, {5,6}, {5,7}, {5,8}},
     {{6,0}, {6,1}, {6,2}, {7,0}, {7,1}, {7,2}, {8,0}, {8,1}, {8,2}},
     {{6,3}, {6,4}, {6,5}, {7,3}, {7,4}, {7,5}, {8,3}, {8,4}, {8,5}},
     {{6,6}, {6,7}, {6,8}, {7,6}, {7,7}, {7,8}, {8,6}, {8,7}, {8,8}},
    };

/*
print_board : 
prints the board.
Style 0 : space separated digits, no borders
Style 1 : space separated digits, with borders
*/
void print_board(int style, vector<vector<int> > &board){
    cout << endl;
    if(style == 0){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                cout << board.at(i).at(j) << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    cout << "+-------+-------+-------+" << endl;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(j%3 == 0){
                cout << "| ";
            }
            cout << board.at(i).at(j) << " ";
        }
        cout << "|" << endl;
        if (i %3 == 2){
            cout << "+-------+-------+-------+" << endl;
        }
    }
    cout << endl;
    return;
}

/*
spaced_intake:
single digit intake. inputs require spaces between inputs. 
print board and prompt for correctness. restart input if not.
print board at the end.
*/
void spaced_intake(vector<vector<int> > &board){
    bool confirm_board = false;
    bool confirm_input;
    string yn;
    while(confirm_board == false){
        cout << "type 1-9 for known tiles and 0 for blank tiles. Input row by row, left to right with spaces between numbers." << endl;
        for(int i = 0; i < 9; i++){
            cout << "row " << i+1 << ": " << endl;
            for(int j = 0; j < 9; j++){
                cin >> board.at(i).at(j);
            }
        }

        cout << endl << "current board : " << endl;
        print_board(1, board);
        confirm_input = false;
        while(confirm_input == false){
            cout << "Is this correct? (Y/N) : ";
            cin >> yn;
            cout << yn <<  endl;
            if(yn == "Y"){
                confirm_board = true;
                confirm_input = true;
            }
            else if(yn == "N"){
                confirm_board = false;
                confirm_input = false;
            }
            else{
                cout << endl<< "Unrecognized input. Try again." << endl;
                confirm_input = false;
            }
        }
    }
    print_board(0, board);
}

/*
line_intake:
intake has no spaces. 1 number where each digit is a single input. 
print board and prompt for correctness. restart input if not.
print board at the end.
*/
void line_intake(vector<vector<int> > &board){
    bool confirm_board = false;
    bool confirm_input;
    string yn;
    int n;
    int mask;
    while(confirm_board == false){
        cout << "type 1-9 for known tiles and 0 for blank tiles. Input row by row, left to right with NO spaces between numbers." << endl;
        for(int i = 0; i < 9; i++){
            cout << "row " << i+1 << ": " << endl;
            cin >> n; 
            mask = 10;
            for(int j = 0; j < 9; j++){
                board.at(i).at(8-j) = n%mask;
                n= n/10;
            }
        }

        cout << endl << "current board : " << endl;
        print_board(1, board);
        confirm_input = false;
        while(confirm_input == false){
            cout << "Is this correct? (Y/N) : ";
            cin >> yn;
            cout << yn <<  endl;
            if(yn == "Y"){
                confirm_board = true;
                confirm_input = true;
            }
            else if(yn == "N"){
                confirm_board = false;
                confirm_input = false;
            }
            else{
                cout << endl<< "Unrecognized input. Try again." << endl;
                confirm_input = false;
            }
        }
    }
    print_board(0, board);
}

/*
update : 
updates the potential values for each tile (easier to remove data than add it)
*/
void update(vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    int curr;
    int sector;
    int r,c;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            curr = board.at(i).at(j);
            if(curr != 0){
                if(potential.at(i).at(j).size() == 0){
                    continue;
                }
                potential.at(i).at(j).clear(); 
                //clear row
                for(int row = 0; row < 9; row++){
                    potential.at(row).at(j).erase(curr);
                }
                //clear col
                for(int col = 0; col < 9; col++){
                    potential.at(i).at(col).erase(curr);
                }
                //clear sector
                sector = coord_to_sector[i][j];
                
                for(int ind = 0; ind < 9; ind++){
                    r = sector_to_coord[sector][ind][0];
                    c = sector_to_coord[sector][ind][1];
                    potential.at(r).at(c).erase(curr);
                }
            }
        }
    }
}

/*
easy_picks_row
helper function for easy_picks()
checks the row to find potential values that appear only once in that row.
*/
bool easy_picks_row(int row_num, vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    bool change = false;
    int avail[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    for(int tile = 0; tile < 9; tile++){
        for (auto it = potential.at(row_num).at(tile).begin(); it != potential.at(row_num).at(tile).end(); it++ ){
            if(avail[*it-1] == -1){
                avail[*it-1] = tile;
            }
            else if(avail[*it-1] == -2){
                continue;
            }
            else{
                avail[*it-1] = -2;
            }
        }
    }  
    for(int i = 0; i < 9; i++){
        if(avail[i] != -1 && avail[i] != -2){
            board.at(row_num).at(avail[i]) = i+1;
            change = true;
        }
    }
    update(board, potential);   
    return change;
}

/*
easy_picks_col
helper function for easy_picks()
checks the col to find potential values that appear only once in that col.
*/
bool easy_picks_col(int col_num, vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    bool change = false;
    int avail[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    for(int tile = 0; tile < 9; tile++){
        for (auto it = potential.at(tile).at(col_num).begin(); it != potential.at(tile).at(col_num).end(); it++ ){
            if(avail[*it-1] == -1){
                avail[*it-1] = tile;
            }
            else if(avail[*it-1] == -2){
                continue;
            }
            else{
                avail[*it-1] = -2;
            }
        }
    }  
    for(int i = 0; i < 9; i++){
        if(avail[i] != -1 && avail[i] != -2){
            board.at(avail[i]).at(col_num) = i+1;
            change = true;
        }
    }
    update(board, potential);
    return change;
}

/*
easy_picks_sector
helper function for easy_picks()
checks each sector to find potential values that appear only once in that sector.
*/
bool easy_picks_sector(int sect_num, vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    bool change = false;
    int avail_r[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int avail_c[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int r,c;
    for(int ind = 0; ind < 9; ind++){
        r = sector_to_coord[sect_num][ind][0];
        c = sector_to_coord[sect_num][ind][1];
        for (auto it = potential.at(r).at(c).begin(); it != potential.at(r).at(c).end(); it++ ){
            if(avail_r[*it-1] == -1){
                avail_r[*it-1] = r;
                avail_c[*it-1] = c;
            }
            else if(avail_r[*it-1] == -2){
                continue;
            }
            else{
                avail_r[*it-1] = -2;
            }
        }
    }  
    for(int i = 0; i < 9; i++){
        if(avail_r[i] != -1 && avail_r[i] != -2){
            board[avail_r[i]][avail_c[i]] = i+1;
            change = true;
        }
    }
    update(board, potential);
    return change;
}
/*
easy_picks : fills in information that is easily determined by process of elim or uniqueness
1) if there is a tile with only 1 potential, fill it in
2) check each row for unique numbers and fill them in + update potentials
3) check each col for unique numbers and fill them in + update potentials
3) check each sector for unique numbers and fill them in + update potentials
*/
void easy_picks(vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    bool change = true;
    
    while(change == true){
        change = false;
        // single potentials
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(potential.at(i).at(j).size() == 1){
                    board.at(i).at(j) = *potential.at(i).at(j).begin();
                    change = true;
                    update(board, potential);
                    // cout << "single potential: at " << i+1 << " , " << j+1 << " -> " << board[i][j] << endl;
                }
            }
        }
        // row
        for(int row = 0; row < 9; row++){
            change = change || easy_picks_row(row, board, potential);
        }
        // col
        for(int col = 0; col < 9; col++){
            change = change || easy_picks_col(col, board, potential);
        }
        // sector
        for(int sect = 0; sect < 9; sect++){
            change = change || easy_picks_sector(sect, board, potential);
        }
    }
}

/*
potentials_elim : updates the potentials 2d array until no changes are made
1) check each row for pairs. update row
2) check each col for pairs. update row
3) check each sector for pairs. update row
*) consider triplets, quadruplets, and/or pentuplets
4) if changes made, call easy_picks again. else return
*/
void set_finder(){
    return;
}

/*
is_full : 
checks if the board is full (no 0s on board)
*/
bool is_full(vector<vector<int> > &board){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board.at(i).at(j) == 0){
                return false;
            }
        }
    }
    return true;
}

/*
is_possible :
checks if there is an empty tile with no potential values. This means the board has no solution
*/
bool is_possible(vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board.at(i).at(j) == 0 && potential.at(i).at(j).size() == 0){
                return false;
            }
        }
    }
    return true;
}

/*
is_solved : checks if the board is full and solved
1) check if board is full by calling is_full
2) check each row
3) check each col
4) check each sector
5) return true if solved, else false
*/
bool is_solved(vector<vector<int> > &board){
    if(is_full(board) == false){
        cout << "Error : Attempted solution check when board not filled." << endl;
        return false;
    }

    int prod;
    for(int row = 0; row < 9; row++){
        prod = 1;
        for(int tile = 0; tile < 9; tile++){
            prod *= board.at(row).at(tile);
        }
        if(prod != 362880){
            return false;
        }
    }

    vector<int> products(9, 1);
    for(int col = 0; col < 9; col++){
        for(int tile = 0; tile < 9; tile++){
            products.at(col) = products.at(col) * board.at(col).at(tile);
        }
    }
    for(int i = 0; i < 9; i++){
        if(products.at(i) != 362880){
            return false;
        }
    }

    int r,c;
    for(int sector = 0; sector < 9; sector++){
        prod = 1;
        for(int ind = 0; ind < 9; ind++){
            r = sector_to_coord[sector][ind][0];
            c = sector_to_coord[sector][ind][1];
            prod *= board.at(r).at(c);
        }  
        if(prod != 362880){
            return false;
        }
    }
    return true;
}

/*
solve : finds the solution if there is one
uses DFS (recursion) using the potentials. 
Base cases :  
1) the current tile is the last tile, return is_solved. (print solution if solved)
2) the tile is filled, return recursion of next tile
recursion process:
- each recursion iterates the board. (left to right, top to bottom)
- for each empty tile try the first potential, then recurse. 
- if false is returned, try the next potential
- if true is returned, return true 
*/
bool solve(int ind, vector<vector<int> > &board, vector<vector<unordered_set<int> > > &potential){
    int r = ind/9;
    int c = ind%9;

    if(ind > 80){
        if(is_solved(board) == true){
            cout << "Solution : " << endl;
            print_board(1, board);
            return true;
        }
        return false;
    }
    else if(board.at(r).at(c) != 0){
        return solve(ind+1, board, potential);
    }
    else{
        vector<vector<int> > temp_b = board;
        for(auto it = potential.at(r).at(c).begin(); it != potential.at(r).at(c).end(); ++it){
            vector<vector<unordered_set<int> > > temp_p = potential;
            temp_b.at(r).at(c)= *it;
            update(temp_b, temp_p);
            
            // for(int row = 0; row < 9; row++){
            //     for(int col = 0; col < 9; col++){
            //         cout << "row " << row << " col " << col << " : ";
            //         for(auto it = temp_p.at(row).at(col).begin(); it != temp_p.at(row).at(col).end(); ++it){
            //             cout << *it << " ";
            //         }
            //         cout << endl;
            //     }
            // }
            if(is_possible(temp_b, temp_p) == false){
                continue;
            }

            if(solve(ind+1, temp_b, temp_p) == true){
                board.at(r).at(c) = *it;
                return true;
            }
        }
        return false;
    }
}


int main(){
    vector<vector<int> > board ( 9, vector<int> (9,0));

    int temp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    // vector<int> options(vector<int>(temp, temp+sizeof(temp)/sizeof(temp[0]))); 
    unordered_set<int> options(begin(temp), end(temp));
    vector<vector<unordered_set<int> > > potential (9, vector<unordered_set<int> >(9, options));

    spaced_intake(board);
    update(board, potential);
    easy_picks(board, potential);

    if(solve(0, board, potential) == false){
        cout << "No solution found" << endl;
    }
    return 0;
}