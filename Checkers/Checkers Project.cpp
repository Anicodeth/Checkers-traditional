#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

struct Point {
	int x, y;
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int NUM_ROWS = 8;
const int NUM_COLS = 8;
const int TILE_SIZE = 75;
int prevRow = 0, prevCol = 0;

Point selected;
Point last;
vector<Point> possibleMoves;
int checkSecond = 0;
		
int grid[8][8]  = {	
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
};

int turn = 1;

bool legal(Point p){
	if (p.x >= 8 or p.x <0 or p.y >= 8 or p.y < 0 ){
		return false;
	}
	return true;
}

bool crown(){
	for(int i = 0; i < 8; i++){
		if (grid[0][i] == 2){
			grid[0][i] = 3;
		}
		
		if (grid[7][i] == 1){
			grid[7][i] = 4;
		}
		
	}
	
	
}


void generateMoves(Point p, RectangleShape board[NUM_ROWS][NUM_COLS]){
	if (grid[p.x][p.y] == 0){
		return;
	}
	
	for(int i = 0; i < possibleMoves.size(); i++){    
      board[possibleMoves[i].x][possibleMoves[i].y].setFillColor(Color::White);
	    }
	      
	possibleMoves.clear();
	
	int direction = -1;
	if (grid[p.x][p.y] == 1) direction = 1;
	
	Point move, eat;
	move.x = p.x + direction;
	move.y = p.y + direction;
		
	eat.x = move.x + direction;
	eat.y = move.y + direction;
		
	if (legal(move) && grid[p.x + direction][p.y + direction] == 0 && checkSecond == 0 && grid[p.x + direction][p.y + direction] != 3 && grid[p.x + direction][p.y + direction] !=4){
		possibleMoves.push_back(move);
	}
	
	if(legal(move) && grid[p.x + direction][p.y + direction] != turn && grid[p.x + direction][p.y + direction] != 0 && legal(eat) && grid[eat.x][eat.y] == 0 && grid[p.x + direction][p.y + direction] != 3 && grid[p.x + direction][p.y + direction] !=4){
		possibleMoves.push_back(eat);
	}
	
		move.x = p.x + direction;
		move.y = p.y - direction;
		eat.x = move.x + direction;
		eat.y = move.y - direction;
		
	if (legal(move) && grid[p.x + direction][p.y - direction] == 0 && checkSecond == 0 && grid[p.x + direction][p.y + direction] != 3 && grid[p.x + direction][p.y + direction] !=4){
		possibleMoves.push_back(move);
	}		
	
	if(legal(move) && grid[p.x + direction][p.y - direction] != turn && grid[p.x + direction][p.y - direction] != 0 && legal(eat) && grid[eat.x][eat.y] == 0 && grid[p.x + direction][p.y + direction] != 3 && grid[p.x + direction][p.y + direction] !=4){
		possibleMoves.push_back(eat);
	}
	
	
	if (grid[p.x][p.y] == 3){
		
		Point k;
		int tr= 0, tl =0, br=0, bl=0, atr = 0,atl = 0,abr = 0,abl = 0;
		
		for(int i = 1; i < 8; i++){
			
			k.x = p.x + i;
			k.y = p.y + i;
			
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && br == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 1){
				br = 1;
			}
			
						k.x = p.x - i;
			k.y = p.y + i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && bl == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 1){
				bl = 1;
			}
			
			k.x = p.x  - i;
			k.y = p.y - i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && tl == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 1){
				tl = 1;
			}
			
			k.x = p.x + i;
			k.y = p.y - i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && tr == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 1){
				tr = 1;
			}

			}
			
		
		}
		
	if (grid[p.x][p.y]==4){
		Point k;
		int tr= 0, tl =0, br=0, bl=0, atr = 0,atl = 0,abr = 0,abl = 0;
		for(int i = 1; i < 8; i++){
			k.x = p.x + i;
			k.y = p.y + i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && br == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 2){
				br = 1;
			}
			
			k.x = p.x - i;
			k.y = p.y + i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && bl == 0&& checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 2){
				bl = 1;
			}
			
			k.x = p.x  - i;
			k.y = p.y - i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && tl == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 2){
				tl = 1;
			}
			
			k.x = p.x + i;
			k.y = p.y - i;
			
			if(legal(k) && grid[k.x][k.y] != 1 && grid[k.x][k.y] != 2 && tr == 0 && checkSecond == 0){
				possibleMoves.push_back(k);}
			else if(legal(k) && grid[k.x][k.y] != 2){
				tr = 1;
			}
		
			}
			
				//Extra king moves
			


	}
	

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Checkers Board");
    
	sf::Texture texture;
    if (!texture.loadFromFile("./src/lightw.jpg")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture texture2;
    if (!texture2.loadFromFile("./src/darkw.jpg")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture checkers;
    if (!checkers.loadFromFile("./src/c1.jpg")) {
        return EXIT_FAILURE;
    }
    
	sf::Texture checkers1;
    if (!checkers1.loadFromFile("./src/c2.jpg")) {
        return EXIT_FAILURE;
    }
    
  	sf::Texture king1;
    if (!king1.loadFromFile("./src/k1.jpg")) {
        return EXIT_FAILURE;
    }
    
    	sf::Texture king2;
    if (!king2.loadFromFile("./src/k2.jpg")) {
        return EXIT_FAILURE;
    }
    
    // Create checkers board
    sf::RectangleShape board[NUM_ROWS][NUM_COLS];
    sf::RectangleShape background;
    
    background.setFillColor(Color::White);
    bool isRed[NUM_ROWS][NUM_COLS];
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            board[i][j].setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            board[i][j].setPosition(j * TILE_SIZE, i * TILE_SIZE);
            if ((i + j) % 2 == 0) {
               board[i][j].setTexture(&texture);
                isRed[i][j] = false;            }
            else {
              board[i][j].setTexture(&texture2);
                isRed[i][j] = true;
   
            }
        }
    }
    
        // Create checkers
    sf::CircleShape checker[NUM_ROWS][NUM_COLS];
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
        	if (grid[i][j] == 3 || grid[i][j] == 4){
        		continue;
					}
            if (i < 3 && (i + j) % 2 == 1) {
                checker[i][j].setRadius(TILE_SIZE / 2.0f - 5);
                checker[i][j].setPosition(j * TILE_SIZE + 5, i * TILE_SIZE + 5);
               // checker[i][j].setFillColor(sf::Color::White);
               
			    grid[i][j] = 1;
			    checker[i][j].setTexture(&checkers);
            }
            else if (i > 4 && (i + j) % 2 == 1) {
                checker[i][j].setRadius(TILE_SIZE / 2.0f - 5);
                checker[i][j].setPosition(j * TILE_SIZE + 5, i * TILE_SIZE + 5);
                grid[i][j] = 2;
                checker[i][j].setTexture(&checkers1);
            }
        }
    }
    
for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
        	cout<<grid[i][j]<<" ";
		}
		cout<<endl;
		}
		
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Check for mouse button presses
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int row = mousePosition.y / TILE_SIZE;
                    int col = mousePosition.x / TILE_SIZE;
                    std::cout << "Clicked on " << (isRed[row][col] ? "red" : "black") << " tile at row " << row << " and column " << col << std::endl;
                    

//Reset blue active
				   board[prevRow][prevCol].setFillColor(sf::Color::White);
				   
				   
				   //movement
				   selected.x = row;
           selected.y = col;
				   for(int i = 0; i < possibleMoves.size(); i++){
        	            if ((selected.x == possibleMoves[i].x ) && (selected.y == possibleMoves[i].y) ){
													 if (turn == 1){
													 	 checker[selected.x][selected.y].setRadius(TILE_SIZE / 2.0f - 5);
							               checker[selected.x][selected.y].setPosition(selected.y * TILE_SIZE + 5, selected.x * TILE_SIZE + 5);
													 	 checker[selected.x][selected.y].setTexture(&checkers);
														 checker[last.x][last.y].setRadius(0);
														 
							 							 grid[selected.x][selected.y] = 1;
							 							 
							 							 if(grid[last.x][last.y]==3){
							 							 	grid[selected.x][selected.y] = 3;
															}
															
															if(grid[last.x][last.y]==4){
							 							 	grid[selected.x][selected.y] = 4;
															}
							 							 grid[last.x][last.y] = 0;
							 							 	if(abs(last.y - selected.y) == 2){
														    		int x = (last.x + selected.x) / 2;
														    		int y = (last.y + selected.y) / 2 ;
														    		checker[x][y].setRadius(0);
														    		grid[x][y] = 0;
														    		checkSecond = 1;
														    		generateMoves(selected, board );
														    		

														    		if(possibleMoves.size() == 0){
														    		   checkSecond = 0;	
																	  }
																	
																	  board[x][y].setFillColor(Color::White);
															  }
															  
															  if(abs(last.y -selected.y) > 2){
															  	
																	int dx = 1;
															  	int dy = 1;
															  	
															  	if ((selected.x - last.x ) < 0){
															  		dx = -1;
																	}
																	
																	if ((selected.y - last.y ) < 0){
															  		dy = -1;
																	}
																	
																	
																	for(int i  = 1 ; i < (last.y); i++){
																		int x = (selected.x)  - dx;
														    		int y = (selected.y)  -  dy ;
														    		checker[x][y].setRadius(0);
														    		grid[x][y] = 0;
														    		checkSecond = 1;
														    		generateMoves(selected, board );
														    		

														    		if(possibleMoves.size() == 0){
														    		   checkSecond = 0;								  
																	  
													        }
																	
																	  board[x][y].setFillColor(Color::White);
																		
																		
																	}
															  
									//Generate king eats
																
																}
										    
													
 															  board[row][col].setFillColor(Color::Blue);
										               
										            for(int i = 0; i < possibleMoves.size(); i++){        
										                  board[possibleMoves[i].x][possibleMoves[i].y].setFillColor(Color::White);
												            }
												        possibleMoves.clear();
												            
												            
												        if (checkSecond != 1){
												            if(turn == 1) turn = 2;
																 	 else turn = 1;
															  }
													 
													 }else{
															  checker[selected.x][selected.y].setRadius(TILE_SIZE / 2.0f - 5);
										            checker[selected.x][selected.y].setPosition(selected.y * TILE_SIZE + 5, selected.x * TILE_SIZE + 5);
															  checker[selected.x][selected.y].setTexture(&checkers1);
													   		checker[last.x][last.y].setRadius(0);
													    	
													    	
													    	grid[selected.x][selected.y] = 2;
													    	
													    	if(grid[last.x][last.y]==3){
							 							 	  grid[selected.x][selected.y] = 3;
															   }
															
															if(grid[last.x][last.y]==4){
							 							 	grid[selected.x][selected.y] = 4;
															}
							 							 grid[last.x][last.y] = 0;
													    	//Write the eating part here
													    	if(abs(last.y - selected.y) == 2){
														    		int x = (last.x + selected.x) / 2;
														    		int y = (last.y + selected.y) / 2 ;
														    		checker[x][y].setRadius(0);
														    		grid[x][y] = 0;
														    	 		checkSecond = 1;
														    		generateMoves(selected, board );
														    		

														    		if(possibleMoves.size() == 0){
														    		   checkSecond = 0;	
																	  }
																	
																	  board[x][y].setFillColor(Color::White);
															  }
															  
															    
															  if(abs(last.y -selected.y) > 2){
															  	
																	int dx = 1;
															  	int dy = 1;
															  	
															  	if ((selected.x - last.x ) < 0){
															  		dx = -1;
																	}
																	
																	if ((selected.y - last.y ) < 0){
															  		dy = -1;
																	}
																	
																	
																	for(int i  = 1 ; i < (selected.y - last.y); i++){
																		int x = (selected.x)  - dx;
														    		int y = (selected.y)  -  dy ;
														    		checker[x][y].setRadius(0);
														    		grid[x][y] = 0;
														    		checkSecond = 1;
														    		generateMoves(selected, board );
														    		

														    		if(possibleMoves.size() == 0){
														    		   checkSecond = 0;	
																	  }
																	
																	  board[x][y].setFillColor(Color::White);
																		
																		
																	}}
													    	
													    	
													    
													    
													      board[row][col].setFillColor(Color::Blue);
										               
										            for(int i = 0; i < possibleMoves.size(); i++){        
										                  board[possibleMoves[i].x][possibleMoves[i].y].setFillColor(Color::White);
												            }
												        possibleMoves.clear();
												        
												            
												            
												        if (checkSecond != 1){
												            if(turn == 1) turn = 2;
																 	 else turn = 1;
															  }
															  
																 	 
													  } 
					            } 
		             }
	
					          board[selected.x][selected.y].setFillColor(Color::White);
					
                    if(turn == grid[row][col] || grid[row][col] == (turn % 2) + 3 ){
                    generateMoves(selected, board);
                            
                    last.x = selected.x;
                    last.y = selected.y;
                    prevRow = row;
                    prevCol = col;
                }
                }
            }
        }
        
        crown();
        
        for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (grid[i][j] == 3) {
                checker[i][j].setRadius(TILE_SIZE / 2.0f - 5);
                checker[i][j].setPosition(j * TILE_SIZE + 5, i * TILE_SIZE + 5);
								checker[i][j].setTexture(&king1);}
								
						if (grid[i][j] == 4) {
                checker[i][j].setRadius(TILE_SIZE / 2.0f - 5);
                checker[i][j].setPosition(j * TILE_SIZE + 5, i * TILE_SIZE + 5);
								checker[i][j].setTexture(&king2);}
								}}
        

        window.clear(sf::Color::White);

        // Draw checkers board
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                window.draw(board[i][j]);
            }
        }
        
                for(int i = 0; i < possibleMoves.size(); i++){
        	cout<<possibleMoves[i].x<<endl;
              board[possibleMoves[i].x][possibleMoves[i].y].setFillColor(Color::Blue);
              
		}
        
                 for (int i = 0; i < NUM_ROWS;i++) {
	        for (int j = 0; j < NUM_COLS; j++) {
	           
	                window.draw(checker[i][j]);}
}
        window.display();
    } 

    return 0;
}

