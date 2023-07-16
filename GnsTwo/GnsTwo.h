// GnsTwo.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vector>
#include <format>
#include <string>
#include <iostream>
#include "raylib.h"

struct Ball {
	Vector2 position{};
	float size{ 10 };
	int lifes{ 5 },
		xdirection{ 1 },
		ydirection{ 1 };
	Sound deathSound{ LoadSound("death.wav") };

	void move(int screenW, int screenH) {
		position.x += xdirection * 2;
		position.y += ydirection * 2;
	}

	void collide(char who, int direction = 0) {
		if(who == 'p') {
			if(direction != 0) xdirection = direction;
			else xdirection == 1 ? xdirection = -1 : xdirection = 1;
			
			ydirection == 1 ? ydirection = -1 : ydirection = 1;
		}
		else if(who == 'b') {
			ydirection == 1 ? ydirection = -1 : ydirection = 1;
		}
		else if(who == 'w') {
			xdirection == 1 ? xdirection = -1 : xdirection = 1;
		}
	}

	void hit(int screenW, int screenH) {
		lifes--;
		position.x = screenW / 2;
		position.y = screenH / 2;
		PlaySound(deathSound);
	}
};

void genScenario(std::vector<Rectangle>&);