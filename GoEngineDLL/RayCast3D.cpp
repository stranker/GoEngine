#include "RayCast3D.h"

void RayCast3D::Draw() {
	if (!CanBeDrawed()) { return Node3D::Draw(); }
	if (line) {
		line->Draw(globalTransform);
	}
}

bool RayCast3D::IsColliding() const {
	return isColliding;
}

Node3D* RayCast3D::GetCollider() {
	return nodeColliding;
}

RayCast3D::RayCast3D() {
	className = "RayCast3D";
	SetDefaultName(className);
	origin = Vector3();
	end = Vector3();
	direction = Vector3().Right();
	lenght = 2;
	color = Color().Magenta();
	line = new Line3D(origin, end, color);
	ray = Ray(origin, direction);
}

RayCast3D::RayCast3D(Vector3 _origin, Vector3 _end, Color _color) : RayCast3D() {
	origin = _origin;
	end = _end;
	color = _color;
	direction = (_end - _origin).Normalize();
	lenght = (_end - _origin).Length();
	color = _color;
	line->SetLine(origin, end, color);
	ray = Ray(origin, direction);
}

RayCast3D::RayCast3D(Vector3 _origin, Vector3 _dir, float _lenght, Color _color) : RayCast3D() {
	origin = _origin;
	lenght = _lenght;
	direction = _dir;
	end = origin + direction * lenght;
	color = _color;
	line->SetLine(origin, end, color);
	ray = Ray(origin, direction);
}
