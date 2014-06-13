using namespace System;
using namespace System::Threading;

#include <stdio.h>
#include <math.h>

#define WIDTH 120
#define HEIGHT 50

//------------------------------------------------------------------------------------
struct fase{
	char title[100];
	int SCREEN[HEIGHT][WIDTH];
	int BODE[8][WIDTH];
};

int pos_x = 3;
int pos_y = HEIGHT;
int tela = 0;

bool showText = false;
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void drawBode(int direction, int position, int x, int y);
void drawScreen(int SCREEN[HEIGHT][WIDTH]);
void drawScreenBode(int BODE[8][WIDTH]);
void nullScreenGame(int screen[HEIGHT][WIDTH]);
void nullScreenBode(int screen[5][WIDTH]);
void loadFase1();
void loadFase2();
void loadFase(int n);
void drawCloud(int x, int y, int d);
void jumpBode(int direction, int position);
void writeText(char text[255], int x, int y);
//------------------------------------------------------------------------------------

fase Fases[10];
ConsoleColor bgBode = ConsoleColor::DarkGreen;
ConsoleKeyInfo cki;

int main()
{
	const int height = HEIGHT;
	const int width = WIDTH;

	Console::SetWindowSize(width, height);
	Console::SetBufferSize(width, height);
	Console::CursorVisible = false;

	int backTela;
	int position = 1;
	int direction = 0;
	bool redrawBode = false;
	bool redrawTela = true;
	bool redrawFundoBode = false;
	bool textUp = false;

	for (int i = 0; i < 10; i++)
	{
		nullScreenBode(Fases[i].BODE);
		nullScreenGame(Fases[i].SCREEN);
	}

	do
	{
		switch (tela)
		{
		case 0:
			if (redrawTela)
			{
				Console::BackgroundColor = ConsoleColor::DarkBlue;
				Console::ForegroundColor = ConsoleColor::Cyan;
				Console::Clear();
				Console::SetCursorPosition(0, 3);

				Console::WriteLine("                                                 /   /");
				Console::WriteLine("                                              (\\/_ /`)");
				Console::WriteLine("                                              /     '/");
				Console::WriteLine("                                             0  0    \\");
				Console::WriteLine("                                            /         \\");
				Console::WriteLine("                                           /     __/   \\");
				Console::WriteLine("                                           /,  _/ \\      \\_");
				Console::WriteLine("                                           `-./ )  |        ~^~^~^~^~^~^~^~\\.");
				Console::WriteLine("                                               (   /                         \\__}");
				Console::WriteLine("                                                  |                   /      |");
				Console::WriteLine("                                                  ;       |          \\      /");
				Console::WriteLine("                                                  \\ /   ,/            \\    |");
				Console::WriteLine("                                                   /   /~~|~ |~~~~~~~|~|\\  |");
				Console::WriteLine("                                                  /   /   |  |       | |`\\  \\");
				Console::WriteLine("                                                 /   /    |  |       | |  \\  \\");
				Console::WriteLine("                                                /   (     |  |       | |   \\  \\");
				Console::WriteLine("                                               /,_  )    /__ )      /__)    /,_/");

				Console::ForegroundColor = ConsoleColor::White;
				Console::SetCursorPosition(5, 25);
				Console::WriteLine("");
				Console::WriteLine("                  OOOOOOOOO                  CCCCCCCCCCCCC");
				Console::WriteLine("                OO:::::::::OO             CCC::::::::::::C");
				Console::WriteLine("              OO:::::::::::::OO         CC:::::::::::::::C");
				Console::WriteLine("             O:::::::OOO:::::::O       C:::::CCCCCCCC::::C");
				Console::WriteLine("             O::::::O   O::::::O      C:::::C       CCCCCC   ooooooooooo xxxxxxx      xxxxxxx ooooooooooo");
				Console::WriteLine("             O:::::O     O:::::O     C:::::C               oo:::::::::::oox:::::x    x:::::xoo:::::::::::oo");
				Console::WriteLine("             O:::::O     O:::::O     C:::::C              o:::::::::::::::ox:::::x  x:::::xo:::::::::::::::o");
				Console::WriteLine("             O:::::O     O:::::O     C:::::C              o:::::ooooo:::::o x:::::xx:::::x o:::::ooooo:::::o");
				Console::WriteLine("             O:::::O     O:::::O     C:::::C              o::::o     o::::o  x::::::::::x  o::::o     o::::o");
				Console::WriteLine("             O:::::O     O:::::O     C:::::C              o::::o     o::::o   x::::::::x   o::::o     o::::o");
				Console::WriteLine("             O:::::O     O:::::O     C:::::C              o::::o     o::::o   x::::::::x   o::::o     o::::o");
				Console::WriteLine("             O::::::O   O::::::O      C:::::C       CCCCCCo::::o     o::::o  x::::::::::x  o::::o     o::::o");
				Console::WriteLine("             O:::::::OOO:::::::O       C:::::CCCCCCCC::::Co:::::ooooo:::::o x:::::xx:::::x o:::::ooooo:::::o");
				Console::WriteLine("              OO:::::::::::::OO         CC:::::::::::::::Co:::::::::::::::ox:::::x  x:::::xo:::::::::::::::o");
				Console::WriteLine("                OO:::::::::OO             CCC::::::::::::C oo:::::::::::oox:::::x    x:::::xoo:::::::::::oo");
				Console::WriteLine("                  OOOOOOOOO                  CCCCCCCCCCCCC   ooooooooooo xxxxxxx      xxxxxxx ooooooooooo");

				Console::SetCursorPosition(42, 45);
				Console::ForegroundColor = ConsoleColor::Yellow;
				Console::Write("Press <enter> to start a new game.");
				redrawTela = false;
			}
			break;
		case 1:
			if (redrawTela)
			{
				drawScreen(Fases[tela - 1].SCREEN);
				redrawTela = false;
			}
			if (redrawFundoBode)
			{
				drawScreenBode(Fases[tela - 1].BODE);
				redrawFundoBode = false;
			}
			if (redrawBode)
			{
				drawBode(direction, position, pos_x, pos_y);
				redrawBode = false;
			}
			if (showText)
			{
				writeText(" . . . ao lado de um coxo, eis que o Bode acorda.\n \nComeca a olhar em volta e repara\nque sua familia nao esta ali . . .\n \n \nEntao comeca a procurar . . .", 10, 10);
				showText = false;
				textUp = true;
			}
			break;
		case 2:
			if (redrawTela)
			{
				drawScreen(Fases[tela - 1].SCREEN);
				redrawTela = false;
			}
			if (redrawFundoBode)
			{
				drawScreenBode(Fases[tela - 1].BODE);
				redrawFundoBode = false;
			}
			if (redrawBode)
			{
				drawBode(direction, position, pos_x, pos_y);
				redrawBode = false;
			}
			break;
		case 100:
			if (redrawTela)
			{
				Console::BackgroundColor = ConsoleColor::DarkRed;
				Console::ForegroundColor = ConsoleColor::White;
				Console::Clear();
				Console::SetCursorPosition(5, 10);
				Console::WriteLine("");
				Console::WriteLine("           PPPPPPPPPPPPPPPPP        AAA           UUUUUUUU     UUUUUUUU   SSSSSSSSSSSSSSS EEEEEEEEEEEEEEEEEEEEEE");
				Console::WriteLine("           P::::::::::::::::P      A:::A          U::::::U     U::::::U SS:::::::::::::::SE::::::::::::::::::::E");
				Console::WriteLine("           P::::::PPPPPP:::::P    A:::::A         U::::::U     U::::::US:::::SSSSSS::::::SE::::::::::::::::::::E");
				Console::WriteLine("           PP:::::P     P:::::P  A:::::::A        UU:::::U     U:::::UUS:::::S     SSSSSSSEE::::::EEEEEEEEE::::E");
				Console::WriteLine("             P::::P     P:::::P A:::::::::A        U:::::U     U:::::U S:::::S              E:::::E       EEEEEE");
				Console::WriteLine("             P::::P     P:::::PA:::::A:::::A       U:::::D     D:::::U S:::::S              E:::::E");
				Console::WriteLine("             P::::PPPPPP:::::PA:::::A A:::::A      U:::::D     D:::::U  S::::SSSS           E::::::EEEEEEEEEE");
				Console::WriteLine("             P:::::::::::::PPA:::::A   A:::::A     U:::::D     D:::::U   SS::::::SSSSS      E:::::::::::::::E");
				Console::WriteLine("             P::::PPPPPPPPP A:::::A     A:::::A    U:::::D     D:::::U     SSS::::::::SS    E:::::::::::::::E");
				Console::WriteLine("             P::::P        A:::::AAAAAAAAA:::::A   U:::::D     D:::::U        SSSSSS::::S   E::::::EEEEEEEEEE");
				Console::WriteLine("             P::::P       A:::::::::::::::::::::A  U:::::D     D:::::U             S:::::S  E:::::E");
				Console::WriteLine("             P::::P      A:::::AAAAAAAAAAAAA:::::A U::::::U   U::::::U             S:::::S  E:::::E       EEEEEE");
				Console::WriteLine("           PP::::::PP   A:::::A             A:::::AU:::::::UUU:::::::U SSSSSSS     S:::::SEE::::::EEEEEEEE:::::E");
				Console::WriteLine("           P::::::::P  A:::::A               A:::::AUU:::::::::::::UU  S::::::SSSSSS:::::SE::::::::::::::::::::E");
				Console::WriteLine("           P::::::::P A:::::A                 A:::::A UU:::::::::UU    S:::::::::::::::SS E::::::::::::::::::::E");
				Console::WriteLine("           PPPPPPPPPPAAAAAAA                   AAAAAAA  UUUUUUUUU       SSSSSSSSSSSSSSS   EEEEEEEEEEEEEEEEEEEEEE");
				
				Console::SetCursorPosition(45, 40);
				Console::ForegroundColor = ConsoleColor::Yellow;
				Console::WriteLine("Press < E > to Exit");
				Console::SetCursorPosition(45, 42);
				Console::WriteLine("Press < ESC > to Continue");

				redrawTela = false;
			}
			break;
		}

		if (Console::KeyAvailable)
		{
			cki = Console::ReadKey();

			if (cki.Key == ConsoleKey::Enter)
			{
				if (tela == 0)
				{
					tela = 1;
					loadFase1();
					if (pos_x <= 20)
						showText = true;
					Console::Clear();
					redrawFundoBode = true;
					redrawTela = true;
					redrawBode = true;
				}
				else if (tela == 1)
				{
					if (textUp)
					{
						textUp = false;
						redrawFundoBode = true;
						redrawTela = true;
						redrawBode = true;
					}
					else if (pos_x <= 20)
					{
						showText = true;
					}
				}
			}
			else if (cki.Key == ConsoleKey::Escape)
			{
				if (tela == 0)
					return 0;
				else if (tela != 100)
				{
					backTela = tela;
					tela = 100;
					redrawTela = true;
				}
				else if (tela == 100)
				{
					tela = backTela;
					Console::Clear();
					redrawFundoBode = true;
					redrawTela = true;
					redrawBode = true;
				}
			}
			else if (cki.Key == ConsoleKey:: Spacebar)
			{
				if ((pos_x >= 7)&&(direction == 1))
				{
					position = 0;
					jumpBode(direction, position);
					if (pos_x <= 3)
					{
						pos_x = width - 10;
						pos_y = height;
						tela--;
						Console::Clear();
						loadFase(tela);
						redrawFundoBode = true;
						redrawTela = true;
						redrawBode = true;
					}
				}
				if ((pos_x <= width - 13)&&(direction == 0))
				{
					position = 0;
					jumpBode(direction, position);
					if (pos_x >= width - 9)
					{
						pos_x = 4;
						pos_y = height;
						tela++;
						Console::Clear();
						loadFase(tela);
						redrawFundoBode = true;
						redrawTela = true;
						redrawBode = true;
					} 
				}
			}
			else if (cki.Key == ConsoleKey::LeftArrow)
			{
				if (pos_x >= 3)
				{
					direction = 1;
					pos_x--;
					redrawBode = true;
				}
				if (tela > 1)
				{
					if (pos_x <= 3)
					{
						pos_x = width - 10;
						pos_y = height;
						tela--;
						Console::Clear();
						loadFase(tela);
						redrawFundoBode = true;
						redrawTela = true;
						redrawBode = true;
					}
				}
			}
			else if (cki.Key == ConsoleKey::RightArrow)
			{
				if (pos_x <= width - 9)
				{
					direction = 0;
					pos_x++;
					redrawBode = true;
				}
				if (pos_x >= width - 9)
				{
					pos_x = 4;
					pos_y = height;
					tela++;
					Console::Clear();
					loadFase(tela);
					redrawFundoBode = true;
					redrawTela = true;
					redrawBode = true;
				}
			}
			else if (cki.Key == ConsoleKey::UpArrow)
			{
				position = 0;
				redrawBode = true;
			}
			else if (cki.Key == ConsoleKey::DownArrow)
			{
				position = 1;
				redrawBode = true;
			}
			else if ((tela == 100) && (cki.Key == ConsoleKey::E))
			{
				return 0;
			}
		}
	} while (true);
	return 0;
}

void drawBode(int direction, int position, int x, int y)
{
	Console::BackgroundColor = bgBode;
	Console::ForegroundColor = ConsoleColor::White;
	//SetConsoleTextAttribute(h, 8);
	if (direction == 0) //Direita
	{
		if (position == 0) //Normal
		{
			Console::SetCursorPosition(x - 1, y);

			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("     %c", 192);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c", 220);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("%c \n", 217);

			y++;

			//SetConsoleTextAttribute(h, 7 | bgbode);
			Console::SetCursorPosition(x, y);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf(" %c", 218);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c%c%c", 219, 219, 219);
			//SetConsoleTextAttribute(h, 9 | bgbode);
			printf("| \n");
			//SetConsoleTextAttribute(h, 7 | bgbode);
			y++;

			Console::SetCursorPosition(x + 1, y);
			printf(" | | ");
		}
		else if (position == 1) //Agaixado
		{
			Console::SetCursorPosition(x - 1, y);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("         \n");
			y++;

			Console::SetCursorPosition(x - 1, y);

			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("     %c", 192);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c", 220);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("%c \n", 217);

			y++;

			//SetConsoleTextAttribute(h, 7 | bgbode);
			Console::SetCursorPosition(x, y);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf(" %c", 218);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c%c%c", 219, 219, 219);
			//SetConsoleTextAttribute(h, 9 | bgbode);
			printf("| ");
			//SetConsoleTextAttribute(h, 7 | bgbode);
		}
	}
	else if (direction == 1) //Esquerda
	{
		if (position == 0) //Normal
		{
			Console::SetCursorPosition(x - 1, y);

			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf(" %c", 192);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c", 220);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("%c     \n", 217);

			y++;

			//SetConsoleTextAttribute(h, 7 | bgbode);
			Console::SetCursorPosition(x , y);
			//SetConsoleTextAttribute(h, 9 | bgbode);
			printf(" |");
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c%c%c", 219, 219, 219);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("%c \n", 191);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			y++;

			Console::SetCursorPosition(x + 1, y);
			printf(" | | ");
		}
		else if (position == 1) //Agaixado
		{
			Console::SetCursorPosition(x - 1, y);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("         \n");
			y++;

			Console::SetCursorPosition(x - 1, y);

			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf(" %c", 192);
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c", 220);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("%c     \n", 217);

			y++;

			//SetConsoleTextAttribute(h, 7 | bgbode);
			Console::SetCursorPosition(x , y);
			//SetConsoleTextAttribute(h, 9 | bgbode);
			printf(" |");
			//SetConsoleTextAttribute(h, 7 | bgbode);
			printf("%c%c%c", 219, 219, 219);
			//SetConsoleTextAttribute(h, 8 | bgbode);
			printf("%c ", 191);
		}
	}
}

void drawScreen(int SCREEN[HEIGHT][WIDTH])
{
	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = ConsoleColor::White;
	Console::Clear();
	
	Console::SetCursorPosition(0 , 0);

	for (int i = 0; i < HEIGHT - 5; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (SCREEN[i][j] == 1)
			{
				Console::SetCursorPosition(j, i);
				printf("%c", 179);
			}
			else if (SCREEN[i][j] == 4)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::DarkGreen;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 5)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Blue;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 6)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::White;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 7)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Gray;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 8)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Gray;
				Console::BackgroundColor = ConsoleColor::DarkGreen;
				printf("%c", 220);
			}
			else if (SCREEN[i][j] == 9)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Gray;
				Console::BackgroundColor = ConsoleColor::DarkGray;
				printf("%c", 223);
			}
			else if (SCREEN[i][j] == 10)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Cyan;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 11)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Black;
				Console::BackgroundColor = ConsoleColor::DarkGreen;
				printf("%c", 193);
			}
			else if (SCREEN[i][j] == 12)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::DarkMagenta;
				Console::BackgroundColor = ConsoleColor::DarkGreen;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 13)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::Green;
				Console::BackgroundColor = ConsoleColor::DarkGreen;
				printf("%c", 219);
			}
		}
	}
}

void drawScreenBode(int BODE[8][WIDTH])
{
	Console::BackgroundColor = bgBode;
	Console::ForegroundColor = ConsoleColor::White;
	
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (BODE[i][j] == 0)
			{
				Console::SetCursorPosition(j,(HEIGHT - 8) + i);
				printf(" ");
			}
		}
	}
	Console::BackgroundColor = ConsoleColor::Black;
}

void nullScreenGame(int screen[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			screen[i][j] = 0;
		}
	}
}

void nullScreenBode(int screen[5][WIDTH])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			screen[i][j] = 0;
		}
	}
}

void jumpBode(int direction, int position)
{
	pos_y--;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y);
	pos_y--;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y);
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y);
	pos_y++;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y);
	pos_y++;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y);
}

//----------DESENHANDO AS FASES------------------------------------------

void loadFase1()
{
	pos_y = pos_y - 6;
	for (int j = 0; j < 7; j++)
		for (int i = 0; i < WIDTH; i++)
			Fases[0].SCREEN[j][i] = 5;

	//Nuvem 01
	drawCloud(2, 1, 8);

	//Nuvem 02
	drawCloud(15, 3, 12);

	//Nuvem 03
	drawCloud(30, 2, 6);

	for (int j = 7; j < HEIGHT; j++)
		for (int i = 0; i < WIDTH; i++)
			Fases[0].SCREEN[j][i] = 4;

	Fases[0].SCREEN[38][9] = 7;
	
	for (int j = 0; j <= 11; j++)
		Fases[0].SCREEN[39][9 + j] = 9;

	for (int j = 1; j <= 10; j++)
		Fases[0].SCREEN[38][9 + j] = 10;
	
	for (int j = 0; j <= 11; j++)
		Fases[0].SCREEN[37][9+j] = 8;

	Fases[0].SCREEN[38][20] = 7;

	Fases[0].SCREEN[40][10] = 11;
	Fases[0].SCREEN[40][19] = 11;
	
	for(int i = 0; i < 8; i++)
		Fases[0].SCREEN[39 - i][26] = 12;
	
	for(int i = 0; i < 8; i++)
		Fases[0].SCREEN[39 - i][27] = 12;

	for(int i = 0; i < 4; i++)
		Fases[0].SCREEN[31][25 + i] = 13;
	
	for(int i = 0; i < 8; i++)
		Fases[0].SCREEN[30][23 + i] = 13;
	
	for(int i = 0; i < 12; i++)
		Fases[0].SCREEN[29][21 + i] = 13;

	for(int i = 0; i < 14; i++)
		Fases[0].SCREEN[28][20 + i] = 13;
	
	for(int i = 0; i < 10; i++)
		Fases[0].SCREEN[27][22 + i] = 13;
	
	for(int i = 0; i < 6; i++)
		Fases[0].SCREEN[26][24 + i] = 13;
	
	for(int i = 0; i < 4; i++)
		Fases[0].SCREEN[25][25 + i] = 13;
}

void loadFase2()
{
	pos_y = pos_y - 6;
	for (int j = 0; j < 7; j++)
		for (int i = 0; i < WIDTH; i++)
			Fases[1].SCREEN[j][i] = 5;

	//Nuvem 01
	drawCloud(2, 1, 8);

	//Nuvem 02
	drawCloud(40, 3, 12);

	//Nuvem 03
	drawCloud(55, 2, 6);

	for (int j = 7; j < HEIGHT; j++)
		for (int i = 0; i < WIDTH; i++)
			Fases[1].SCREEN[j][i] = 4;
}

void loadFase(int n)
{
	if (n == 1)
		loadFase1();
	else if (n == 2)
		loadFase2();
}

void drawCloud(int x, int y, int d)
{
	int tam = x + d;
	for (int i = x + 1; i <= tam - 2; i++)
		Fases[tela - 1].SCREEN[y][x + i] = 6;
	for (int i = x; i <= tam; i++)
		Fases[tela - 1].SCREEN[y + 1][x + i] = 6;
	for (int i = x + 1; i <= tam - 1; i++)
		Fases[tela - 1].SCREEN[y + 2][x + i] = 6;
}

void writeText(char text[255], int x, int y)
{
	int j = 0;
	int line = 1;
	int col = 1;
	int colMax = 1;

	int xBox = x - 2;
	int yBox = y - 2;

	Console::SetCursorPosition(xBox , yBox);
	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = ConsoleColor::Yellow;

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == '\n')
		{
			line++;
			if (col >= colMax)
				colMax = col;

			col = 0;
		}
		col++;
	}

	line += 5;
	colMax += 3;

	for (int i = 0; i <= line; i++)
	{
		for (int h = 0; h <= colMax; h++)
		{
			if (i == 0 || i == line || h == 0 || h == colMax)
			{
				if (i == 0 && h == 0)
				{
					printf("%c", 201);
				}
				else if (i == 0 && h == colMax)
				{
					printf("%c", 187);
				}
				else if (i == line && h == 0)
				{
					printf("%c", 200);
				}
				else if (i == line && h == colMax)
				{
					printf("%c", 188);
				}
				else if (h == 0 || h == colMax)
				{
					printf("%c", 186);
				}
				else
				{
					printf("%c", 205);
				}
			}
			else
			{
				printf(" ");
			}
		}
		yBox++;
		Console::SetCursorPosition(xBox, yBox);
	}

	Console::SetCursorPosition(x, y);
	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = ConsoleColor::White;

	while (text[j] != '\0')
	{
		Thread::Sleep(20);
		if (text[j] == '\n')
		{
			y++;
			j++;
			Console::SetCursorPosition(x, y);
		}

		printf("%c", text[j]);

		j++;
	}

	Console::SetCursorPosition(xBox+2, yBox-2);
	Console::ForegroundColor = ConsoleColor::DarkCyan;
	printf("Press <Enter> to clean.");
	Console::ForegroundColor = ConsoleColor::White;
}

/*
4 = Grama;
5 = Céu;
6 = Nuvem;
7 = Parede Coxo = 219
8 = Parede Superior Coxo = 220
9 = Fundo Coxo = 223
10 = Agua Coxo = 176
11 = Pé Coxo = 293
12 = Tronco das Arveres
13 = Folha das Arveres
*/
//----------DESENHANDO AS FASES------------------------------------------