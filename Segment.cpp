#include "Segment.h"


Segment::Segment(olc::vi2d a_, float len_, float angle_) {
	a = a_;
	len = len_;
	angle = angle_;
}
Segment::Segment(Segment* parent_, float len_, float angle_) {
	parent = parent_;
	len = len_;
	angle = angle_;

	a = parent->b();
}
olc::vi2d Segment::b() {
	return olc::vi2d(
	a.x + len * cosf(angle),
	a.y + len * sinf(angle)
	);
}

void Segment::Update(olc::vi2d point) {
	LookAt(point);
	MoveTo(point);
	if (parent != nullptr) parent->Update(a);
}
void Segment::LookAt(olc::vi2d point) {
	float
		dx = a.x - point.x,
		dy = a.y - point.y;

	if (dx == 0.0f) return;

	angle = atan(dy / dx);
	if (dx > 0.0f) angle += 3.14159f;
}

void Segment::MoveTo(olc::vi2d point) {
	a = olc::vi2d{
		point.x - int(len * cosf(angle)),
		point.y - int(len * sinf(angle))
	};
}

void Segment::MoveA(olc::vi2d diff) {
	a = a - diff;
	if (parent != nullptr) parent->MoveA(diff);
}

void Segment::Draw(olc::PixelGameEngine* pge) {
	pge->DrawLine(a, b());
	if (parent != nullptr) parent->Draw(pge);
}