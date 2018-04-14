#pragma once

struct CellPosition {
	CellPosition(int x = 0.0f, int y = 0.0f) : x(x), y(y) {}
	int x, y;
};

struct Position {
	Position(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
	float x, y, z;
};
