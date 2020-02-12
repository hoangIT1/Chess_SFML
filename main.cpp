#include <SFML/Graphics.hpp>
#include <time.h>\
#include <iostream>
using namespace sf;
using namespace std;

Vector2f offset(28,28);
int selectpiece = -1;
int squaresize = 56;
Texture t1,t2;
int n = -1;
int turn = 1;

class chesspieces
{
public:
	Sprite piece;
	Texture t;
	int value;
	int coordx, coordy;
	int positivemoveboard[8][8] = {{0}};
	void setpieceposition(int x, int y);
	void setpieceTexture(Texture);
	void setvalue(int);
	void Move(int x,int y);
	void positivemove(int x,int y);
	void positivemoveKing(int x,int y);
	void positivemoveQueen(int x, int y);
	void positivemoveBishop(int x, int y);
	void positivemoveKnight(int x, int y);
	void positivemoveRook(int x, int y);
	void positivemovePawn(int x, int y);
	bool canmove(int x, int y);
};

chesspieces pieces[32];

int board[8][8] =
    {-1,-6,0,0,0,0,6,1,
    -2,-6,0,0,0,0,6,2,
    -3,-6,0,0,0,0,6,3,
    -5,-6,0,0,0,0,6,5,
    -4,-6,0,0,0,0,6,4,
    -3,-6,0,0,0,0,6,3,
    -2,-6,0,0,0,0,6,2,
    -1,-6,0,0,0,0,6,1,};


void chesspieces::setpieceposition(int x, int y)
{
    coordx = x;
    coordy = y;
    piece.setPosition(squaresize * coordx, squaresize * coordy);
}

void chesspieces::Move(int x, int y)
{
    board[coordx][coordy] = 0;

    coordx = x;
    coordy = y;

    board[x][y] = value;
    piece.setPosition(squaresize * coordx,squaresize * coordy);
}

void chesspieces::setpieceTexture(Texture tm)
{
    t = tm;
    piece.setTexture(t);
    int x = abs(value) - 1;
    int y = value > 0 ? 1 : 0;
    piece.setTextureRect(IntRect(squaresize * x, squaresize * y, squaresize, squaresize));
    piece.setPosition(squaresize * coordx,squaresize * coordy);
}

void chesspieces::setvalue(int val)
{
    value = val;
}

void chesspieces::positivemoveKing(int x,int y)
{
    int movex[] = { 1,1,1,0,0,-1,-1,-1 };
    int movey[] = { 1,0,-1,1,-1,1,0,-1 };
    int color = value / abs(value);
    for (int i = 0; i < 8; i++)
    {
        if ((x + movex[i]) >= 0 && (x + movex[i]) < 8 && (y + movey[i] >= 0) && (y + movey[i] )< 8)
        {
            if(board[x+movex[i]][y+movey[i]]/color==0)
            positivemoveboard[x + movex[i]][y + movey[i]] = 1;
            if (board[x + movex[i]][y + movey[i]] / color < 0)
            positivemoveboard[x + movex[i]][y + movey[i]] = 2;
        }
    }
}

void chesspieces::positivemoveRook(int x, int y)
{
    int color = value / abs(value);
    int a = x;
    int b = y;
    for (int i = b+1; i < 8; i++)
    {
        if (board[a][i] / color > 0)
        {
            break;
        }
        else if (board[a][i] / color < 0)
        {
            positivemoveboard[a][i] = 2;
            break;
        }
        else positivemoveboard[a][i] = 1;
    }
    for (int i = b - 1; i >= 0; i--)
    {
        if (board[a][i] / color > 0)
        {
            break;
        }
        else if (board[a][i] / color < 0)
        {
            positivemoveboard[a][i] = 2;
            break;
        }
        else positivemoveboard[a][i] = 1;
    }
    for (int i = a - 1; i >= 0; i--)
    {
        if (board[i][b] / color > 0)
        {
            break;
        }
        else if (board[i][b] / color < 0)
        {
            positivemoveboard[i][b] = 2;
            break;
        }
        else positivemoveboard[i][b] = 1;
    }
    for (int i = a + 1; i < 8; i++)
    {
        if (board[i][b] / color > 0)
        {
            break;
        }
        else if (board[i][b] / color < 0)
        {
            positivemoveboard[i][b] = 2;
            break;
        }
        else positivemoveboard[i][b] = 1;
    }
}

void chesspieces::positivemoveBishop(int x, int y)
{
    int a, b;
    int color = value / abs(value);

    a = x + 1;
    b = y + 1;
    while (a < 8 && b < 8)
    {
        if (board[a][b] / color > 0)
        {
            break;
        }
        else if (board[a][b] / color < 0)
        {
            positivemoveboard[a][b] = 2;
            break;
        }
        else positivemoveboard[a][b] = 1;
        a++;
        b++;
    }
    a = x - 1;
    b = y - 1;
    while (a >=0 && b >= 0)
    {
        if (board[a][b] / color > 0)
        {
            break;
        }
        else if (board[a][b] / color < 0)
        {
            positivemoveboard[a][b] = 2;
            break;
        }
        else positivemoveboard[a][b] = 1;
        a--;
        b--;
    }
    a = x + 1;
    b = y - 1;
    while (a <8  && b >= 0)
    {
        if (board[a][b] / color > 0)
        {
            break;
        }
        else if (board[a][b] / color < 0)
        {
            positivemoveboard[a][b] = 2;
            break;
        }
        else positivemoveboard[a][b] = 1;
        a++;
        b--;
    }
    a = x - 1;
    b = y + 1;
    while (a >= 0 && b <8)
    {
        if (board[a][b] / color > 0)
        {
            break;
        }
        else if (board[a][b] / color < 0)
        {
            positivemoveboard[a][b] = 2;
            break;
        }
        else positivemoveboard[a][b] = 1;
        a--;
        b++;
    }
}

void chesspieces::positivemoveQueen(int x, int y)
{
    positivemoveBishop(x, y);
    positivemoveRook(x, y);
}

void chesspieces::positivemoveKnight(int x, int y)
{
    int movex[] = { 1,1,-1,-1,2,2,-2,-2 };
    int movey[] = { 2,-2,2,-2,1,-1,1,-1 };
    int color = value / abs(value);
    for (int i = 0; i < 8; i++)
    {
        if ((x + movex[i]) >= 0 && (x + movex[i]) < 8 && (y + movey[i] >= 0) && (y + movey[i]) < 8)
        {
            if (board[x + movex[i]][y + movey[i]] / color == 0)
                positivemoveboard[x + movex[i]][y + movey[i]] = 1;
            if (board[x + movex[i]][y + movey[i]] / color < 0)
                positivemoveboard[x + movex[i]][y + movey[i]] = 2;
        }
    }
}

void chesspieces::positivemovePawn(int x, int y)
{
    int color = value / abs(value);
    if(y==1||y==6)
    for (int i = 1; i <= 2; i++)
    {
        if (board[x][y-i*color] / color > 0)
        {
            break;
        }
        else if (board[x][y - i * color] / color < 0)
        {
            break;
        }
        else positivemoveboard[x][y - i * color] = 1;
    }
    else if (board[x][y -  color] / color == 0)
         positivemoveboard[x][y - color] = 1;
    if (board[x + 1][y - color] / color < 0) positivemoveboard[x + 1][y - color] = 2;
    if (board[x - 1][y - color] / color < 0) positivemoveboard[x - 1][y - color] = 2;
}

void chesspieces::positivemove(int x, int y)
{
    switch (abs(value))
    {
    case 1: {
        positivemoveRook(x, y);
        break;
    }
    case 2: {
        positivemoveKnight(x, y);
        break;
    }
    case 3: {
        positivemoveBishop(x, y);
        break;
    }
    case 4: {
        positivemoveQueen(x, y);
        break;
    }
    case 5: {
        positivemoveKing(x, y);
        break;
    }
    case 6: {
        positivemovePawn(x, y);
        break;
          }
    }
}



bool chesspieces::canmove(int x, int y)
{
    if (positivemoveboard[x][y] != 0)
        return 1;
    else return 0;
}

void setup()
{
    int k = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (board[j][i] != 0)
            {
                pieces[k].setvalue(board[j][i]);
                pieces[k].setpieceposition(j, i);
                k++;
            }
        }
    for (int i=0;i<32;i++) pieces[i].setpieceTexture(t1);

}

void play(Vector2i pos)
{
    if (selectpiece == -1) {
        for (int i = 0; i < 32; i++)
            if (pieces[i].piece.getGlobalBounds().contains(pos.x, pos.y))
                if (pieces[i].value / turn > 0)
                {
                    selectpiece = 1;
                    pieces[i].positivemove(pieces[i].coordx, pieces[i].coordy);
                    n = i;

                }
    }
    else
        if (n >= 0) {
            if (pieces[n].canmove((pos.x) / squaresize, (pos.y) / squaresize)) {
                for (int i = 0; i < 32; i++)
                {
                    if (pieces[i].coordx == (pos.x) / squaresize && pieces[i].coordy == (pos.y) / squaresize && i != n)
                    {

                        pieces[i].piece.setPosition(-100, -100);
                        pieces[i].coordx = -1;
                        pieces[i].coordy = -1;
                    }
                }
                pieces[n].Move((pos.x) / squaresize, (pos.y) / squaresize);
                turn = -turn;
            }

            selectpiece = -1;
            n = -1;
        }
}

int main()
{
    RenderWindow window(VideoMode(504, 504), "The Chess! ");

    t1.loadFromFile("figures.png");
    t2.loadFromFile("board.png");
    setup();
    Sprite sBoard(t2);
    int n=0;
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            /////drag and drop///////
            if (e.type == Event::MouseButtonPressed)
                if (e.mouseButton.button == Mouse::Left)
                  for(int i=0;i<32;i++)
                  if (pieces[i].piece.getGlobalBounds().contains(pos.x,pos.y))
                      {
                          play(pos);
                      }

             if (e.type == Event::MouseButtonReleased)
                if (e.mouseButton.button == Mouse::Left)
                 {
                     play(pos);
                 }
        }

    ////// draw  ///////
    window.clear();
    window.draw(sBoard);
    for(int i=0;i<32;i++) pieces[i].piece.move(offset);
    for(int i=0;i<32;i++) window.draw(pieces[i].piece); window.draw(pieces[n].piece);
    for(int i=0;i<32;i++) pieces[i].piece.move(-offset);
    window.display();
    }

    return 0;
}
