#pragma once
#include <stack>

struct Vector2
{
	float x;
	float y;
};

enum ActiveShape
{
	NONE,
	CIRCLE,
	AABB,
	LINESEGMENT,
};

struct Circle
{
	Vector2 position{0,0};
	float radius{0};
	Color color{};
};

struct Aabb
{
	Vector2 position{ 0,0 };
	Vector2 size{ 0,0 };
	Color color{};
};

struct LineSegment
{	
	Vector2 Startpoint{};
	Vector2 Endpoint{};
	Color color;
};



struct CollisionValues
{
	float collision_t;          // here t value stands for t_near on the shape
	Vector2 contact_normal;
};

struct Collision
{
	bool exit_collisionscreen = false;
	bool IsCollided = false;

	
	// Static Shapes
	Aabb staticAABB{ {(float)(GetRenderWidth() / 2), (float)(GetRenderHeight() / 2)},AABB_SIZE, BLUE };
	Circle staticcircle{(float)(GetRenderWidth()/2), (float)(GetRenderHeight()/2),CIRCLE_SIZE, GREEN};
	LineSegment staticline{ {(float)(GetRenderWidth() / 2), (float)(GetScreenHeight() / 2)}  , {(float)(GetRenderWidth() / 2), (float)(GetScreenHeight() / 4)}, YELLOW };


	// Cursor shapes
	Circle cursorcircle{ {(float)GetRenderWidth() / 3.f, (float)GetRenderHeight() / 2.f},CIRCLE_SIZE, GREEN };
	Aabb cursorAABB{ {GetMousePosition().x, GetMousePosition().y}, AABB_SIZE, BLUE };

	// Shape Types
	ActiveShape StaticShape{};
	ActiveShape CursorShape{};


	void ShapeChageingButtons();
	void ShapesPosUpdate();

	

	bool CircleVsCircleCollison(const Vector2 circle1, const Vector2 circle2, const float radius1, const float radius2);
	bool CircleVsAABB(const Circle circle, const Aabb aabb);
	bool CircleVsLineSegment(const Circle circle, const LineSegment line);

	// I have made this collision along with sweep testing. I am only using one for now.
	bool AABBVsAABB(const Aabb aabb1, const Aabb aabb2);


	// Sweep testing

	static bool SweptRayvsAABB(const Vector2 rayorigin, const Vector2 rayvector, const Vector2 rec_pos, const Vector2 rec_size, CollisionValues* collision);

	static bool SweptAABBvsAABB(const Vector2 pos1, const Vector2 size1, const Vector2 vel1, const Vector2 pos2, const Vector2 size2, CollisionValues* collison);



	



	void CollisonCheck();

	void collision_update();
	void collision_render();

};