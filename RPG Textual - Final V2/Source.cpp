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
	bool status;
};

int pos_x = 3;
int pos_y = HEIGHT;
int tela = 0;

int npc_x = 90;
int npc_y = 44;

bool showText = false;
bool showNPC = false;
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void drawBode(int direction, int position, int x, int y, ConsoleColor clBode);
void drawScreen(int SCREEN[HEIGHT][WIDTH]);
void drawScreenBode(int BODE[8][WIDTH]);
void drawScreenCoxo(int SCREEN[HEIGHT][WIDTH]);
void nullScreenGame(int screen[HEIGHT][WIDTH]);
void nullScreenBode(int screen[5][WIDTH]);
void loadFase1();
void loadFase2();
void loadFase3();
void loadFase4();
void loadFase5();
void drawCoxo(int tela, int x, int y);
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
	bool bodeAnda = false;

	for (int i = 0; i < 10; i++)
		Fases[i].status = false;

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
				drawBode(1, 0, 90, 30, ConsoleColor::Gray);
				drawBode(0, 0, 50, 25, ConsoleColor::Yellow);
				redrawTela = false;
			}
			if (redrawFundoBode)
			{
				drawScreenBode(Fases[tela - 1].BODE);
				redrawFundoBode = false;
			}
			if (redrawBode)
			{
				drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
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
				if (showNPC && !(Fases[tela - 1].status))
					drawBode(1, 0, npc_x, npc_y, ConsoleColor::White);
				redrawFundoBode = false;
			}
			if (redrawBode)
			{ 
				if (showNPC && !(Fases[tela - 1].status))
					drawBode(1, 0, npc_x, npc_y, ConsoleColor::White);
	
				drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
				redrawBode = false;
			}
			if (!Fases[tela - 1].status)
			{
				if (showText)
				{
					writeText("O Bode: Mee!\n \nBodezinho: Mee! Mee!\n \nO Bode: Mee! Mee! Mee! Mee! Meee?            \n \nBodezinho: Meeeeee!\n \nBodezinho: Mee!", 70, 10);
					showText = false;
					textUp = true;
				}
				if (bodeAnda)
				{
					while (npc_x <= width - 9)
					{
						Thread::Sleep(50);
						drawBode(0, 0, npc_x, npc_y, ConsoleColor::White);
						npc_x++;
					}
					drawScreenBode(Fases[tela - 1].BODE);
					drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
					bodeAnda = false;
					showNPC = false;
					Fases[tela - 1].status = true;
				}
			}
			break;
		case 3:
			if (redrawTela)
			{
				drawScreen(Fases[tela - 1].SCREEN);
				redrawTela = false;
			}
			if (redrawFundoBode)
			{
				if (showNPC && !(Fases[tela - 1].status))
				{
					drawBode(1, 0, npc_x, npc_y, ConsoleColor::White);
					drawBode(0, 0, npc_x - 7, npc_y + 2, ConsoleColor::Yellow);
				}
				drawScreenBode(Fases[tela - 1].BODE);
				redrawFundoBode = false;
			}
			if (redrawBode)
			{
				if (showNPC && !(Fases[tela - 1].status))
				{
					drawBode(1, 0, npc_x, npc_y, ConsoleColor::White);
					drawBode(0, 0, npc_x - 7, npc_y + 1, ConsoleColor::Yellow);
				}
				drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
				redrawBode = false;
			}
			if (!Fases[tela - 1].status)
			{
				if (showText)
				{
					writeText(" Outro Bode: Ouvi falar que voce esta procurando sua mae?!\n \n Outro Bode: Ela passou aqui mais cedo pedindo agua e comida,\ncontinua andando pra direita que voce deve alcanca-la", 55, 10);
					showText = false;
					textUp = true;
				}
			}
			break;
		case 4:
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
				drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
				redrawBode = false;
			}
		case 5:
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

				if (showNPC && !(Fases[tela - 1].status))
				{
					int w = 0;
					while (w <= 8)
					{
						drawBode(1, 0, 79 - w, 37, ConsoleColor::Magenta);
						drawScreenCoxo(Fases[tela - 1].SCREEN);
						Thread::Sleep(100);
						w++;
					}
					showNPC = false;
					Fases[tela - 1].status = true;
				}
				if (!showNPC && Fases[tela - 1].status)
				{
					drawBode(1, 0, 71, 37, ConsoleColor::Magenta);
				}
				drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
				redrawBode = false;
			}
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
					loadFase(tela);
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
				else if (tela == 2)
				{
					if (textUp)
					{
						textUp = false;
						redrawFundoBode = true;
						redrawTela = true;
						redrawBode = true;
						bodeAnda = true;
					}
					else if (pos_x >= 78)
					{
						showText = true;
					}
				}
				else if (tela == 3)
				{
					if (textUp)
					{
						textUp = false;
						redrawFundoBode = true;
						redrawTela = true;
						redrawBode = true;
						bodeAnda = true;
					}
					else if (pos_x >= 75)
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

						if (textUp)
							textUp = false;

						if (showText)
							showText = false;
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

					if (pos_x == 78 && tela == 2 && showNPC)
					{
						showText = true;
					}

					if (pos_x == 75 && tela == 3 && showNPC)
					{
						showText = true;
					}

					if (pos_x == 50 && tela == 5 && !showNPC)
					{
						showNPC = true;
					}

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

					if (textUp)
						textUp = false;

					if (showText)
						showText = false;
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

void drawBode(int direction, int position, int x, int y, ConsoleColor clBode)
{
	Console::SetCursorPosition(1, 1);
	printf("Pos X: %3d", pos_x);
	Console::BackgroundColor = bgBode;
	Console::ForegroundColor = clBode;
	
	if (direction == 0) //Direita
	{
		if (position == 0) //Normal
		{
			Console::SetCursorPosition(x - 1, y);

			printf("     %c", 192);
			printf("%c", 220);
			printf("%c \n", 217);

			y++;

			Console::SetCursorPosition(x, y);
			printf(" %c", 218);
			printf("%c%c%c", 219, 219, 219);
			printf("| \n");
			y++;

			Console::SetCursorPosition(x + 1, y);
			printf(" | | ");
		}
		else if (position == 1) //Agaixado
		{
			Console::SetCursorPosition(x - 1, y);
			printf("         \n");
			y++;

			Console::SetCursorPosition(x - 1, y);

			printf("     %c", 192);
			printf("%c", 220);
			printf("%c \n", 217);

			y++;

			Console::SetCursorPosition(x, y);
			printf(" %c", 218);
			printf("%c%c%c", 219, 219, 219);
			printf("| ");
		}
	}
	else if (direction == 1) //Esquerda
	{
		if (position == 0) //Normal
		{
			Console::SetCursorPosition(x - 1, y);

			printf(" %c", 192);
			printf("%c", 220);
			printf("%c     \n", 217);

			y++;

			Console::SetCursorPosition(x , y);
			printf(" |");
			printf("%c%c%c", 219, 219, 219);
			printf("%c \n", 191);
			y++;

			Console::SetCursorPosition(x + 1, y);
			printf(" | | ");
		}
		else if (position == 1) //Agaixado
		{
			Console::SetCursorPosition(x - 1, y);
			printf("         \n");
			y++;

			Console::SetCursorPosition(x - 1, y);

			printf(" %c", 192);
			printf("%c", 220);
			printf("%c     \n", 217);

			y++;

			Console::SetCursorPosition(x , y);
			printf(" |");
			printf("%c%c%c", 219, 219, 219);
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
			else if (SCREEN[i][j] == 14)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::DarkCyan;
				Console::BackgroundColor = ConsoleColor::DarkGreen;
				printf("%c", 219);
			}
			else if (SCREEN[i][j] == 15)
			{
				Console::SetCursorPosition(j, i);
				Console::ForegroundColor = ConsoleColor::DarkBlue;
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
			else if (BODE[i][j] == 1)
			{
				Console::SetCursorPosition(j, (HEIGHT - 8) + i);
				Console::ForegroundColor = ConsoleColor::DarkYellow;
				printf("%c", 219);
			}
		}
	}
	Console::BackgroundColor = ConsoleColor::Black;
}

void drawScreenCoxo(int SCREEN[HEIGHT][WIDTH])
{
	Console::BackgroundColor = ConsoleColor::Black;
	Console::ForegroundColor = ConsoleColor::White;
	
	Console::SetCursorPosition(0, 0);

	for (int i = 0; i < HEIGHT - 5; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (SCREEN[i][j] == 7)
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
		}
	}
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
	drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
	pos_y--;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
	pos_y++;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
	pos_y++;
	pos_x = pos_x + (1 * (pow(-1.0, direction)));
	Thread::Sleep(100);
	drawScreenBode(Fases[tela - 1].BODE);
	drawBode(direction, position, pos_x, pos_y, ConsoleColor::White);
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

	drawCoxo(0, 38, 9);
	
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

	bgBode = ConsoleColor::DarkGreen;
}

void loadFase2()
{
	pos_y = pos_y - 6;
	npc_x = 90;
	npc_y = 44;
	
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

	showNPC = true;
	bgBode = ConsoleColor::DarkGreen;
}

void loadFase3()
{
	pos_y = pos_y - 6;
	npc_x = 90;
	npc_y = 43;

	for (int j = 0; j < HEIGHT; j++)
		for (int i = 0; i < WIDTH; i++)
		{
			Fases[2].SCREEN[j][i] = 5;
			if (j >= 0 && j <= 6)
				Fases[2].SCREEN[j][i] = 10;
			if (j == 8 || j == 11 || j == 16)
				Fases[2].SCREEN[j][i] = 15;
		}

	drawCloud(2, 1, 8);
	drawCloud(40, 3, 12);
	drawCloud(55, 2, 6);
	showNPC = true;
	bgBode = ConsoleColor::DarkYellow;
}

void loadFase4()
{
	pos_y = pos_y - 6;

	for (int j = 0; j < HEIGHT; j++)
		for (int i = 0; i < WIDTH; i++)
		{
		Fases[3].SCREEN[j][i] = 5;
		if (j >= 0 && j <= 6)
			Fases[2].SCREEN[j][i] = 10;
		if (j == 8 || j == 11 || j == 16)
			Fases[3].SCREEN[j][i] = 15;
		}

	drawCloud(2, 1, 8);
	drawCloud(40, 3, 12);
	drawCloud(55, 2, 6);
	showNPC = true;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][4+i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][13 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][22 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][31 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][40 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][49 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][58 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][67 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][76 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][85 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][94 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][103 + i] = 1;

	for (int i = 0; i < 7; i++)
		Fases[3].BODE[5][112 + i] = 1;
	bgBode = ConsoleColor::Blue;
}

void loadFase5()
{
	pos_y = pos_y - 6;
	for (int j = 0; j < 7; j++)
		for (int i = 0; i < WIDTH; i++)
			Fases[4].SCREEN[j][i] = 5;

	//Nuvem 01
	drawCloud(2, 1, 8);

	//Nuvem 02
	drawCloud(15, 3, 12);

	//Nuvem 03
	drawCloud(30, 2, 6);

	for (int j = 7; j < HEIGHT; j++)
		for (int i = 0; i < WIDTH; i++)
			Fases[4].SCREEN[j][i] = 4;

	drawCoxo(4, 38, 79);

	Fases[4].SCREEN[40][80] = 11;
	Fases[4].SCREEN[40][89] = 11;

	for (int i = 0; i < 8; i++)
		Fases[4].SCREEN[39 - i][96] = 12;

	for (int i = 0; i < 8; i++)
		Fases[4].SCREEN[39 - i][97] = 12;

	for (int i = 0; i < 4; i++)
		Fases[4].SCREEN[31][95 + i] = 13;

	for (int i = 0; i < 8; i++)
		Fases[4].SCREEN[30][93 + i] = 13;

	for (int i = 0; i < 12; i++)
		Fases[4].SCREEN[29][91 + i] = 13;

	for (int i = 0; i < 14; i++)
		Fases[4].SCREEN[28][90 + i] = 13;

	for (int i = 0; i < 10; i++)
		Fases[4].SCREEN[27][92 + i] = 13;

	for (int i = 0; i < 6; i++)
		Fases[4].SCREEN[26][94 + i] = 13;

	for (int i = 0; i < 4; i++)
		Fases[4].SCREEN[25][95 + i] = 13;

	bgBode = ConsoleColor::DarkGreen;
	showNPC = false;
}

void drawCoxo(int n, int x, int y)
{
	Fases[n].SCREEN[x][y] = 7;

	for (int j = 0; j <= 11; j++)
		Fases[n].SCREEN[x+1][y + j] = 9;

	for (int j = 1; j <= 10; j++)
		Fases[n].SCREEN[x][y + j] = 10;

	for (int j = 0; j <= 11; j++)
		Fases[n].SCREEN[x-1][y + j] = 8;

	Fases[n].SCREEN[x][y+11] = 7;

	Fases[n].SCREEN[x+2][y+1] = 11;
	Fases[n].SCREEN[x+2][y+10] = 11;
}

void loadFase(int n)
{
	if (n == 1)
	{
		loadFase1();
	}
	else if (n == 2)
	{
		loadFase2();
	}
	else if (n == 3)
	{
		loadFase3();
	}
	else if (n == 4)
	{
		loadFase4();
	}
	else if (n == 5)
	{
		loadFase5();
	}
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
	printf("Press <Enter> to continue.");
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
14 = Mar 1
15 = Mar 2
*/
//----------DESENHANDO AS FASES------------------------------------------