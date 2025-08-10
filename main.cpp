#include "raylib.h"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Pong Game");

	Vector2 ballPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
	Vector2 ballSpeed = {5.0f, 5.0f};
	const float ballRadius = 10.0f;

	Rectangle leftPaddle = {50, screenHeight / 2 -50, 10, 100};
	Rectangle rightPaddle = {screenWidth -60, screenHeight /2 - 50, 10, 100};
	const float paddleSpeed = 5.0f;

	int leftScore = 0, rightScore = 0;

	SetTargetFPS(1000);

	while (!WindowShouldClose()){
		if(IsKeyDown(KEY_W) && leftPaddle.y > 0) leftPaddle.y -= paddleSpeed;
		if(IsKeyDown(KEY_S) && leftPaddle.y < screenHeight - leftPaddle.height)leftPaddle.y += paddleSpeed;
		if(IsKeyDown(KEY_UP) && rightPaddle.y > 0) rightPaddle.y -= paddleSpeed;
		if(IsKeyDown(KEY_DOWN) && rightPaddle.y < screenHeight-rightPaddle.height)rightPaddle.y += paddleSpeed;

		ballPosition.x += ballSpeed.x;
		ballPosition.y += ballSpeed.y;

		if (ballPosition.y - ballRadius <= 0 || ballPosition.y + ballRadius >= screenHeight)
			ballSpeed.y *= -1;

		if(CheckCollisionCircleRec(ballPosition, ballRadius, leftPaddle) && ballSpeed.x < 0) ballSpeed.x *= -1;
		if(CheckCollisionCircleRec(ballPosition, ballRadius, rightPaddle) && ballSpeed.x > 0) ballSpeed.x *= -1;

		if (ballPosition.x < 0) { rightScore++; ballPosition = {screenWidth / 2.0f, screenHeight / 2.0f}; ballSpeed.x = 5.0f;};
		if (ballPosition.x > screenWidth) {leftScore++; ballPosition = {screenWidth / 2.0f, screenHeight / 2.0f}; ballSpeed.x = -5.0f;};

		BeginDrawing();
		ClearBackground(BLACK);

		DrawCircleV(ballPosition, ballRadius, WHITE);
		DrawRectangleRec(leftPaddle, WHITE);
		DrawRectangleRec(rightPaddle, WHITE);

		DrawText(TextFormat("%d", leftScore), screenWidth / 4, 20, 40, WHITE);
		DrawText(TextFormat("%d", rightScore), screenWidth * 3/4, 20, 40, WHITE);

		EndDrawing();

	}
	CloseWindow();
	return 0;
}