#include "OpenGL_func.h"


void reset_game()
{
	Sleep(500);
	Path.empty();
	P1.setDir(nulldir);
	P1.setPos(GRID_WIDTH / 2, GRID_HEIGHT / 2);
}


void init(int DIFFICULTY)
{
	life = 3;
	Zombies.clear();
	Zombie_position.empty();
	Path.empty();
	Territory.empty();
	score = 0;
	P1.setDir(nulldir);
	P1.setPos(GRID_WIDTH / 2, GRID_HEIGHT / 2);
	Territory.setRec(GRID_WIDTH / 2 + INIT_TERRITORY_LENGTH, GRID_WIDTH / 2 - INIT_TERRITORY_LENGTH,
		GRID_HEIGHT / 2 + INIT_TERRITORY_LENGTH, GRID_HEIGHT / 2 - INIT_TERRITORY_LENGTH, true);//초기 영토 지정
	P1.setBR(GRID_WIDTH / 2 + INIT_TERRITORY_LENGTH, GRID_WIDTH / 2 - INIT_TERRITORY_LENGTH,
		GRID_HEIGHT / 2 + INIT_TERRITORY_LENGTH, GRID_HEIGHT / 2 - INIT_TERRITORY_LENGTH);//초기 Boundary Rectangle 지정
	P1.FloodtoTerritory();
	int x, y;
	double temp;//modf에서 그냥 인자 하나가 더 필요해서 만든 임시 인수.
	float r, g, b;
	int diff;
	switch (DIFFICULTY)
	{
	case EASY:
		diff = 5;
		break;
	case HARD:
		diff = 8;
		break;
	case LUNATIC:
		diff = 15;
		break;
	}

	for (int i = 0; i < diff; i++)
	{
		srand((unsigned int)time(NULL)+i);
		x = (rand()*rand()) % (GRID_WIDTH-1)+1;
		r = modf(rand() / 1000.0, &temp);
		srand((unsigned int)time(NULL)-i);
		y = (rand()*rand()) % (GRID_HEIGHT-1)+1;
		g = modf(rand() / 1000.0, &temp);
		b = modf((rand()*rand()) / 1000.0, &temp);
		//
		if (r + g + b < 0.5 || Territory.isGrid(x, y) || Zombie_position.isGrid(x,y))
		{
			i--;
			continue;
		}
		Zombies.push_back(Zombie(x, y, r, g, b));
		Zombies[i].update_Zombie_pos();
	}

}

void processIdle()
{
	if (mode == PAUSE)
	{
		glutPostRedisplay();
		return;
	}
	if (mode==GAME_WIN)
	{
		glutPostRedisplay();
		return;
	}
	if (mode==GAME_OVER)
	{
		glutPostRedisplay();
		return;
	}
	if (mode == IN_GAME)
	{
		clock_end = clock();
		if (phase == 1&&clock_end - clock_start > 1000 / 16)
		{
			phase = 0;
			zombie_move_count++;
			P1.process_prev_dir();
			P1.move();

			int k = Zombies.size();
			for (int i = 0; i < k; i++)
			{

				Zombies[i].ProcessBPos();
				if (zombie_move_count == ZOMBIE_SPEED)
				{
					Zombies[i].Zombie_Think();
					Zombies[i].move();
				}

				if (Zombies[i].is_on(TERRITORY))
				{
					Zombies.erase(Zombies.begin() + i);
					k = Zombies.size();
				}
			}
			if (zombie_move_count == ZOMBIE_SPEED)
				zombie_move_count = 0;

	
			glutPostRedisplay();
		}
		if (clock_end - clock_start > 1000 / 8)
		{
			phase = 1;
			if (P1.is_on(PATH) && !P1.is_on(MAP_BOUND))
			{
				life--;
				if (life == 0)
					mode = GAME_OVER;
				else
					reset_game();
			}
			int k = Zombies.size();
			for (int i = 0; i < k; i++)
			{
				if (Zombies[i].is_on(PATH))
				{
					life--;
					if (life == 0)
						mode = GAME_OVER;
					else
						reset_game();
				}

			}

			if (P1.is_on(PATH) && P1.is_on(MAP_BOUND) && P1.enclosed_by_path())
			{
				life--;
				if (life == 0)
					mode = GAME_OVER;
				else
					reset_game();

			}
		
			if (!P1.is_on(TERRITORY))
			{
				P1.drawPath();
			}
			else
			{
				P1.PathToTer();
			}
			clock_start = clock_end;

			glutPostRedisplay();
		}
	}
}


void renderBitmapCharacter(float x, float y, void *font, string str)
{
	char *c;
	glRasterPos2f(x, y);
	int k = str.size();
	for (int i = 0; i<k; i++)
	{
		glutBitmapCharacter(font, str.at(i));
	}
}
void renderScene() {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mode == MAINMENU)
	{
		Curser t(GRID_WIDTH - 26, GRID_HEIGHT - 12, 1, 1, 1.0, 1.0, 0);
		glColor3f(1, 1, 0);
		renderBitmapCharacter(GRID_WIDTH - 20, GRID_HEIGHT - 1, GLUT_BITMAP_TIMES_ROMAN_24, "KILL & CONQUER!");
		renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 8, GLUT_BITMAP_HELVETICA_12, "(PRESS ENTER TO START)");
		renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 10, GLUT_BITMAP_TIMES_ROMAN_24, "SELECT MENU :");
		renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 12, GLUT_BITMAP_TIMES_ROMAN_24, "EASY");
		renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 14, GLUT_BITMAP_TIMES_ROMAN_24, "HARD");
		renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 16, GLUT_BITMAP_TIMES_ROMAN_24, "LUNATIC");
		renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 18, GLUT_BITMAP_TIMES_ROMAN_24, "QUIT");

		


		switch (menu_selection)
		{
		case EASY:
			t.setPos(GRID_WIDTH - 26, GRID_HEIGHT - 11.6);
			glColor3f(0, 1, 1);
			renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 12, GLUT_BITMAP_TIMES_ROMAN_24, "EASY");
			break;
		case HARD:
			t.setPos(GRID_WIDTH - 26, GRID_HEIGHT - 13.6);
			glColor3f(0, 1, 1);
			renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 14, GLUT_BITMAP_TIMES_ROMAN_24, "HARD");
			break;

		case LUNATIC:
			t.setPos(GRID_WIDTH - 26, GRID_HEIGHT - 15.6);
			glColor3f(0, 1, 1);
			renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 16, GLUT_BITMAP_TIMES_ROMAN_24, "LUNATIC");
			break;
		case MAINMENU_QUIT:
			t.setPos(GRID_WIDTH - 26, GRID_HEIGHT - 17.6);
			glColor3f(0, 1, 1);
			renderBitmapCharacter(GRID_WIDTH - 25, GRID_HEIGHT - 18, GLUT_BITMAP_TIMES_ROMAN_24, "QUIT");
		}


		t.draw();

	}


	if (mode == IN_GAME || mode == GAME_OVER || mode == GAME_WIN || mode==PAUSE)
	{

		//Show life
		renderBitmapCharacter(GRID_WIDTH - 15, GRID_HEIGHT + 4, GLUT_BITMAP_HELVETICA_12, "YOUR LEFT LIFE = "+to_string(life));
		Heart life_viewer_1(GRID_WIDTH - 15, GRID_HEIGHT + 2.5, 1, 1);
		Heart life_viewer_2(GRID_WIDTH - 13, GRID_HEIGHT + 2.5, 1, 1);
		Heart life_viewer_3(GRID_WIDTH - 11, GRID_HEIGHT + 2.5, 1, 1);
		




		if(life>=1)
			life_viewer_1.draw();
		if(life>=2)
			life_viewer_2.draw();
		if(life>=3)
			life_viewer_3.draw();

		Territory.draw();
		Path.draw();
		int k = Zombies.size();
		for (int i = 0; i < k; i++)
			Zombies[i].draw(phase);
		P1.draw(phase);


		//IN_GAME_MENU 처리 영역

		if (mode == GAME_WIN)
		{
			glColor3f(1, 1, 1);
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2, GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN");
		}
		if (mode == GAME_OVER)
		{
			glColor3f(1, 0,0 );
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2, GLUT_BITMAP_TIMES_ROMAN_24, "YOU DIED");
		}
		if(mode==GAME_OVER||mode==GAME_WIN)
		{
			Curser t(GRID_WIDTH / 2-1, GRID_HEIGHT / 2 - 1.7, 1, 1, 1.0, 0, 0);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 2, GLUT_BITMAP_TIMES_ROMAN_24, "RESTART");
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 3, GLUT_BITMAP_TIMES_ROMAN_24, "BACK TO MAIN MENU");
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 4, GLUT_BITMAP_TIMES_ROMAN_24, "QUIT");
			switch (menu_selection)
			{
			case RESTART:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 1.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 2, GLUT_BITMAP_TIMES_ROMAN_24, "RESTART");
				break;
			case BACK_MAIN:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 2.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 3, GLUT_BITMAP_TIMES_ROMAN_24, "BACK TO MAIN MENU");
				break;
			case QUIT:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 3.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 4, GLUT_BITMAP_TIMES_ROMAN_24, "QUIT");
				break;
			}
			t.draw();
			glColor3f(1, 1, 1);
		}
		if(mode==PAUSE)
		{
			Curser t(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 0.7, 1, 1, 1.0, 0, 0);
			glColor3f(1, 1, 1);
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 + 1, GLUT_BITMAP_TIMES_ROMAN_24, "PAUSE");
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 1, GLUT_BITMAP_TIMES_ROMAN_24, "RESUME");
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 2, GLUT_BITMAP_TIMES_ROMAN_24, "RESTART");
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 3, GLUT_BITMAP_TIMES_ROMAN_24, "BACK TO MAIN MENU");
			renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 4, GLUT_BITMAP_TIMES_ROMAN_24, "QUIT");
			switch (menu_selection)
			{
			case RESUME:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 0.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 1, GLUT_BITMAP_TIMES_ROMAN_24, "RESUME");
				break;
			case RESTART:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 1.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 2, GLUT_BITMAP_TIMES_ROMAN_24, "RESTART");
				break;
			case BACK_MAIN:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 2.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 3, GLUT_BITMAP_TIMES_ROMAN_24, "BACK TO MAIN MENU");
				break;
			case QUIT:
				t.setPos(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2 - 3.7);
				glColor3f(0, 1, 1);
				renderBitmapCharacter(GRID_WIDTH / 2, GRID_HEIGHT / 2 - 4, GLUT_BITMAP_TIMES_ROMAN_24, "QUIT");
				break;
			}
			t.draw();
			glColor3f(1, 1, 1);

		}



		//Interface 영역

		glColor3f(1, 1, 1);
		int score_percent = (score * 100) / (GRID_WIDTH*GRID_HEIGHT);
		if (score_percent >= 60 && mode != GAME_WIN)
			mode = GAME_WIN;
		renderBitmapCharacter(GRID_WIDTH - 3, GRID_HEIGHT + 2, GLUT_BITMAP_HELVETICA_18, to_string(score_percent)+"%");
		renderBitmapCharacter(GRID_WIDTH - 5, GRID_HEIGHT + 4, GLUT_BITMAP_HELVETICA_12, "SCORE:");
		renderBitmapCharacter(1, GRID_HEIGHT + 4, GLUT_BITMAP_HELVETICA_18, "DEBUG_INT:");//디버깅할때 쓰는 int 변수
		debugger_int = mode;//삭제필요
		renderBitmapCharacter(1, GRID_HEIGHT + 2, GLUT_BITMAP_HELVETICA_18, to_string(debugger_int));
		renderBitmapCharacter(GRID_WIDTH/2-3, GRID_HEIGHT + 0.5, GLUT_BITMAP_HELVETICA_12, "PAUSE: ESC KEY");//디버깅할때 쓰는 int 변수


		glLineWidth(10.0f);
		glBegin(GL_LINES);

		glVertex3f(0, GRID_HEIGHT, 0);
		glVertex3f(GRID_WIDTH, GRID_HEIGHT, 0);

		glVertex3f(GRID_WIDTH, GRID_WHOLE_WIDTH, 0);
		glVertex3f(0, GRID_WHOLE_WIDTH, 0);//WHOLE_WIDTH, HEIGHT 이름 바뀜..;

		glVertex3f(0, GRID_WHOLE_WIDTH, 0);
		glVertex3f(0,0, 0);
		
		glVertex3f(0, 0, 0);
		glVertex3f(GRID_WIDTH, 0, 0);
		
		glVertex3f(GRID_WIDTH, 0, 0);
		glVertex3f(GRID_WIDTH, GRID_WHOLE_WIDTH, 0);
		
		glVertex3f(10, GRID_HEIGHT, 0);
		glVertex3f(10, GRID_HEIGHT + 6, 0);
		
		glVertex3f(24, GRID_HEIGHT, 0);
		glVertex3f(24, GRID_HEIGHT + 6, 0);

		glEnd();

	}

	glutSwapBuffers();
}


void processSpecialKey(int key, int x, int y)
{
	static int prev_dir=nulldir;
	switch (key)
	{
	case GLUT_KEY_UP:
		if (mode == MAINMENU)
		{
			menu_selection--;
			if (menu_selection < 0)
				menu_selection += MENU_COUNT;
			glutPostRedisplay();
			break;
		}
		if (mode == GAME_OVER || mode == GAME_WIN)
		{
			menu_selection--;
			if (menu_selection < 0)
				menu_selection += GAME_END_MENU_COUNT;
			glutPostRedisplay();
			break;
		}
		if (mode == PAUSE)
		{
			menu_selection--;
			if (menu_selection < 0)
				menu_selection += PAUSE_MENU_COUNT;
			glutPostRedisplay();
			break;
		}
		if (!P1.is_backward(NORTH))
			P1.setDir(NORTH);
		break;
	case GLUT_KEY_DOWN:
		if (mode == MAINMENU)
		{
			menu_selection++;
			if (menu_selection >= MENU_COUNT)
				menu_selection -= MENU_COUNT;
			glutPostRedisplay();
			break;
		}
		if (mode == GAME_OVER||mode==GAME_WIN)
		{
			menu_selection++;
			if (menu_selection >= GAME_END_MENU_COUNT)
				menu_selection -= GAME_END_MENU_COUNT;
			glutPostRedisplay();
			break;
		}
		if (mode == PAUSE)
		{
			menu_selection++;
			if (menu_selection >= PAUSE_MENU_COUNT)
				menu_selection -= PAUSE_MENU_COUNT;
			glutPostRedisplay();
			break;
		}

		if (!P1.is_backward(SOUTH))
			P1.setDir(SOUTH);
		break;
	case GLUT_KEY_LEFT:
		if (mode == PAUSE)
			break;

		if (!P1.is_backward(WEST))
			P1.setDir(WEST);
		break;
	case GLUT_KEY_RIGHT:
		if (mode == PAUSE)
			break;

		if (!P1.is_backward(EAST))
			P1.setDir(EAST);
		break;
	}

}

void processNormalKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 13://ENTER
		if (mode == MAINMENU)
		{
			switch (menu_selection)
			{
			case EASY:
			case HARD:
			case LUNATIC:

				mode = IN_GAME;
				init(menu_selection);
				difficulty = menu_selection;
				menu_selection = 0;
				break;
			case MAINMENU_QUIT:
				exit(0);
				break;
			}

		}
		if (mode == GAME_OVER || mode == GAME_WIN)
		{
			switch (menu_selection)
			{
			case RESTART:
				mode = IN_GAME;
				init(difficulty);
				glutPostRedisplay();
				break;
			case BACK_MAIN:
				Zombies.clear();
				mode = MAINMENU;
				glutPostRedisplay();
				menu_selection = 0;
				break;
			case QUIT:
				exit(0);
			
				break;
			}
		}
		if (mode == PAUSE)
		{
			switch (menu_selection)
			{
			case RESUME:
				mode = IN_GAME;
				break;

			case RESTART:
				mode = IN_GAME;
				init(difficulty);
				glutPostRedisplay();
				break;
			case BACK_MAIN:
				Zombies.clear();
				mode = MAINMENU;
				glutPostRedisplay();
				menu_selection = 0;
				break;
			case QUIT:
				exit(0);

				break;
			}
		}

		break;
	case 27://Esc key
		if (mode == IN_GAME)
		{
			mode = PAUSE;
			menu_selection = PAUSE_MENU_COUNT-1;
		}
		break;




	}

}


void resize(int width, int height) 
{
	// we ignore the params and do:
	glutInitWindowSize(WIDTH, HEIGHT);
}
