#include "CollisionDetection.h"


using namespace GUI;

void Collision::collision_render()
{
	switch (StaticShape)
	{
	case(ActiveShape::CIRCLE):
	{
		DrawCircleV(staticcircle.position, staticcircle.radius, staticcircle.color);
	}
	break;
	case(ActiveShape::AABB):
	{
		DrawRectangleV(staticAABB.position, staticAABB.size, staticAABB.color);
	}
	break;

	case(ActiveShape::LINESEGMENT):
	{
		DrawLineV(staticline.Startpoint, staticline.Endpoint, staticline.color);
	}
	break;
	}

	if (CursorShape == ActiveShape::CIRCLE)
	{
		DrawCircleV(cursorcircle.position, cursorcircle.radius, cursorcircle.color);
	}
	
	if (CursorShape == ActiveShape::AABB)
	{
		DrawRectangleV(cursorAABB.position, cursorAABB.size, cursorAABB.color);
	}
	
	if (IsCollided)
	{
		DrawText("Collision Happened!", GetRenderWidth()/2, GetRenderHeight() - 60, 40, WHITE);
	}
}



void Collision::ShapeChageingButtons()
{
	const Vector2 button_size = Vector2(200, 50);
	const int button_margin_y = 10;
	const int button_count = 4;

	Rectangle button_rect;
	button_rect.x = (GetRenderWidth() - button_size.x) / 20;
	button_rect.y = (GetRenderHeight() - (button_size.y * button_count) - (button_count - 1) * button_margin_y) / 10;
	button_rect.width = button_size.x;
	button_rect.height = button_size.y;


	if (gui_button(button_rect, "Circle vs Circle", 20))
	{
		CursorShape = ActiveShape::CIRCLE;
		StaticShape = ActiveShape::CIRCLE;

	}

	button_rect.y += button_size.y + button_margin_y;

	if (gui_button(button_rect, "Circle vs AABB", 20))
	{
		CursorShape = ActiveShape::CIRCLE;
		StaticShape = ActiveShape::AABB;
	}

	button_rect.y += button_size.y + button_margin_y;

	if (gui_button(button_rect, "Circle VS Line", 20))
	{
		CursorShape = ActiveShape::CIRCLE;
		StaticShape = ActiveShape::LINESEGMENT;
	}

	button_rect.y += button_size.y + button_margin_y;

	if (gui_button(button_rect, "AABB vs AABB", 20))
	{
		CursorShape = ActiveShape::AABB;
		StaticShape = ActiveShape::AABB;
	}

	button_rect.y += button_size.y + button_margin_y;

	if (gui_button(button_rect, "BACK", 20))
	{
		exit_collisionscreen = true;
	}
}




bool Collision::CircleVsCircleCollison(const Vector2 circle1, const Vector2 circle2, const float radius1, const float radius2)
{
	float a = (circle2.x - circle1.x);
	float b = (circle2.y - circle1.y);
	float r = radius2 + radius1;

	if (pow(r,2) >= pow(a,2) +  pow(b,2))
	{
		return true;
	}
	else
	{
		return false;
	}


}


bool Collision::CircleVsLineSegment(const Circle circle, const LineSegment line)
{
	Vector2 A = line.Startpoint;
	Vector2 B = line.Endpoint;
	Vector2 C = circle.position;

	// Vector AB
	Vector2 AB = (B - A);

	// Vector AC
	Vector2 AC = { C - A };

	// Vector BC
	Vector2 BC = { C - B };

	// Finding t. t is the constant value which determines the closest point of line with center of the circle

	float t = Vector2DotProduct(AC,AB)/Vector2DotProduct(AB,AB);



	if (t < 0)      // if true, then start of line is closest point from circle
	{
	    // Magnitude of AC
		double magnitudeAC = sqrt((pow(AC.x, 2) + pow(AC.y, 2)));


		if (magnitudeAC <= circle.radius)
		{
			return true;
		}
	}
	else if (t > 1)  // If true, end is the closest point from the circle
	{
		// Magnitude of vector BC

		double magnitudeBC = sqrt(pow(BC.x, 2) + pow(BC.y, 2));


		if (magnitudeBC <= circle.radius)
		{
			return true;
		}
	}
	else   // otherwise the closest point lies on the line
	{
		// Here I calculate the closest point on the line from the center of circle. the point is P

		Vector2 P = A + AB * t;

		// CP, the vector between center of circle and point P.

		Vector2 CP = (P - C);

		// Magnitude of CP

		double magnitudeofCP = sqrt(pow(CP.x,2) + pow(CP.y,2)) ;

		if (magnitudeofCP <= circle.radius)
		{
			return true;

		}
	
	}

	return false;
}


bool Collision:: CircleVsAABB(const Circle circle, const Aabb aabb)
{

	Vector2 half_size = {aabb.size/2};

	Vector2 aabb_center = { aabb.position + half_size };

	// The vector between center of circle and center of aabb
	Vector2 center_vector = circle.position - aabb_center;

	 Vector2 clamp_aabb = Vector2Clamp(center_vector, Vector2Negate(half_size), half_size);

	// The closest point on box from circle

	 Vector2 closest_point = aabb_center + clamp_aabb;


	 Vector2 distancefromcircle = closest_point - circle.position;

	 if (Vector2Length(distancefromcircle) < circle.radius)
	 {
		 return true;
	 }

	 return false;


}


bool Collision::AABBVsAABB(const Aabb aabb1, const Aabb aabb2)
{
	bool CollisionX = aabb1.position.x + aabb1.size.x >= aabb2.position.x && aabb2.position.x + aabb2.size.x >= aabb1.position.x;

	bool CollisionY = aabb1.position.y + aabb1.size.y >= aabb2.position.y && aabb2.position.y + aabb2.size.y >= aabb1.position.y;

	return CollisionX && CollisionY;
}




bool Collision::SweptRayvsAABB(const Vector2 rayorigin, const Vector2 rayvector, const Vector2 rec_pos, const Vector2 rec_size, CollisionValues* collision)
{
	Vector2 t_near = (rec_pos - rayorigin) / rayvector;   // Gives the near point on rectangle
	Vector2 t_far = (rec_pos + rec_size - rayorigin) / rayvector;  // Gives the far point on rectangle



	if (t_near.x > t_far.x)
	{
		std::swap(t_near.x, t_far.x);
	}
	if (t_near.y > t_far.y)
	{
		std::swap(t_near.y, t_far.y);
	}


	if (t_near.x > t_far.y || t_near.y > t_far.x)
	{
		return false;
	}



	if (t_near.x > t_near.y)
	{
		if (rayvector.x < 0)
		{
			collision->contact_normal = { 1,0 };
		}
		else
		{
			collision->contact_normal = { -1, 0 };
		}
	}
	else if (t_near.x < t_near.y)
	{
		if (rayvector.y < 0)
		{
			collision->contact_normal = { 0,1 };
		}
		else
		{
			collision->contact_normal = { 0,-1 };
		}
	}

	collision->collision_t = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0)
	{
		return false;
	}

	if (collision->collision_t > 1.0f)
	{
		return false;
	}




	return true;

}

bool Collision::SweptAABBvsAABB(const Vector2 pos1, const Vector2 size1, const Vector2 vel1, const Vector2 pos2, const Vector2 size2, CollisionValues* collision)
{
	// Increasing size of static box

	Vector2 Expandedrec_pos = pos2 - (size1 / 2);
	Vector2 Expandedrec_size = size2 + size1;


	if (SweptRayvsAABB(pos1 + (size1 / 2), vel1, Expandedrec_pos, Expandedrec_size, &(*collision)))
	{
		if (collision->collision_t < 1.0f && collision->collision_t >= 0)
		{
			return true;
		}
	}

	return false;
}

void Collision::CollisonCheck()
{
	if (StaticShape == CIRCLE && CursorShape == CIRCLE)
	{
		cursorcircle.color = GREEN;
		staticcircle.color = GREEN;
		if (CircleVsCircleCollison(cursorcircle.position, staticcircle.position, cursorcircle.radius, staticcircle.radius))
		{
			IsCollided = true;

			cursorcircle.color = RED;
			staticcircle.color = RED;


		}
		

	}
	else if (StaticShape == AABB && CursorShape == AABB)
	{
		cursorAABB.color = BLUE;
		staticAABB.color = BLUE;


		if (AABBVsAABB(cursorAABB ,staticAABB))
		{
			IsCollided = true;

			cursorAABB.color = RED;
			staticAABB.color = VIOLET;
		}
	}
	else if (StaticShape == LINESEGMENT && CursorShape == CIRCLE)
	{
		cursorcircle.color = GREEN;
		staticline.color = YELLOW;

		if (CircleVsLineSegment(cursorcircle, staticline))
		{
			IsCollided = true;

			cursorcircle.color = RED;
			staticline.color = GREEN;
		}
	}
	else if (StaticShape == AABB && CursorShape == CIRCLE)
	{
		cursorcircle.color = GREEN;
		staticAABB.color = BLUE;
		if (CircleVsAABB(cursorcircle, staticAABB))
		{
			IsCollided = true;

			cursorcircle.color = RED;
			staticAABB.color = VIOLET;
		}
	}
	
}



void Collision::ShapesPosUpdate()
{
	cursorcircle.position = GetMousePosition();
	cursorAABB.position = GetMousePosition();
	
}


void Collision::collision_update()
{
	IsCollided = false;

	ShapeChageingButtons();
	ShapesPosUpdate();
	CollisonCheck();

	
}