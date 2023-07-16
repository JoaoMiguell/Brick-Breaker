#include "GnsTwo.h"

int main(void) {
	const int screenW{ 610 }, screenH{ 550 };
	InitWindow(screenW, screenH, "My game");
	SetTargetFPS(60);
	InitAudioDevice();

	Rectangle player{ (float)screenW / 2 - 30, (float)screenH - 50, 60.0f,20.f };
	int lastDirectionPlayer{ 1 };
	std::vector<Rectangle> bricks(50);
	Ball ball{ {screenW / 2, screenH / 2} };
	Rectangle deathArea{ 0, screenH - 45, screenW, 40 };
	std::string textLifes{std::format("Lifes: {}", ball.lifes)};
	bool exitWindow{ false };
	int noBricks{ 0 };
	int count{ 0 };
	Sound breakBrick{ LoadSound("assets/break.wav") };

	genScenario(bricks);

	while(!exitWindow) {
		if(WindowShouldClose()) exitWindow = true;

		// Moviments
		if(IsKeyDown(KEY_LEFT)) {
			player.x -= 5;
			lastDirectionPlayer = -1;
		}
		if(IsKeyDown(KEY_RIGHT)) {
			player.x += 5;
			lastDirectionPlayer = 1;
		}

		if(ball.lifes != 0)
			ball.move(screenW, screenH);

		// Objects Collisions
		if(CheckCollisionCircleRec(ball.position, ball.size, player))
			ball.collide('p', lastDirectionPlayer);

		for(auto i{ bricks.begin() }; i != bricks.end(); ++i) {
			if(CheckCollisionCircleRec(ball.position, ball.size, { i->x, i->y, i->width, i->height })) {
				i->x = 0;
				i->y = 0;
				i->width = 0;
				i->height = 0;
				ball.collide('b');
				noBricks++;
				PlaySound(breakBrick);
			}
		}

		if(CheckCollisionCircleRec(ball.position, ball.size, deathArea)) {
			ball.hit(screenW, screenH);
			textLifes = std::format("Lifes: {}", ball.lifes);
		}


		// Border Collisions
		if((ball.position.x >= (screenW - ball.size)) || (ball.position.x <= ball.size))
			ball.collide('w');
		if((ball.position.y >= (screenH - ball.size)) || (ball.position.y <= ball.size))
			ball.collide('b');

		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(20, 20);
		DrawText(textLifes.c_str(), screenW - 100, 20, 20, WHITE);
		if(noBricks != 50 && !(ball.lifes <= 0)) {
			for(const auto& b : bricks) {
				DrawRectangleRec(b, BLUE);
			}
			DrawRectangleRec(player, WHITE);
			DrawCircle(ball.position.x, ball.position.y, ball.size, RED);
		}
		else {
			std::string stateWL{};
			if(noBricks == 50) stateWL = "WIN";
			else stateWL = "LOSE";

			DrawText(stateWL.c_str(), screenW / 2 - 60, screenH / 2, 40, WHITE);

			count == 200 ? exitWindow = true : count++;
		}
		EndDrawing();
	}

	UnloadSound(ball.deathSound);
	UnloadSound(breakBrick);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

void genScenario(std::vector<Rectangle>& brics) {
	int ct{ 0 };
	float H{ 50.0f }, W{ 10.0f };
	for(int i{ 0 }; i < 50; i++) {
		if(ct == 10) {
			ct = 0;
			H += 30.0f;
			W = 10.0f;
		}
		brics[i].x = W;
		brics[i].y = H;
		brics[i].width = 50;
		brics[i].height = 20;
		W += 60.0f;
		ct++;
	}
}