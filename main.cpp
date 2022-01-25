#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>

#include "Segment.h"

class InverseKinematics : public olc::PixelGameEngine
{
public:
	InverseKinematics() {
		sAppName = "InverseKinematics";
	}

private:
	std::vector<Segment*> vec;
	uint8_t segmentNum = 10;
	olc::vi2d LastMousePos = { 0,0 };

protected:
	bool OnUserCreate() override {
		vec.push_back(new Segment({ ScreenWidth() >> 1, ScreenHeight() >> 1 }, 40, 0));
		for (uint8_t i = 1; i < segmentNum; i++)
			vec.push_back(new Segment(vec.back(), 40, 0));

		return true;
	}

	bool OnUserUpdate(float elapsedTime) override {
		if (GetKey(olc::ESCAPE).bPressed) return false;
		if (LastMousePos == GetMousePos()) return true;
		LastMousePos = GetMousePos();
		Clear(olc::BLACK);
		
		vec.back()->Update(LastMousePos);
		vec.back()->MoveA(vec[0]->a - olc::vi2d{ ScreenWidth() >> 1, ScreenHeight() >> 1 });
		
		vec.back()->Draw(this);

		Sleep(50);
		
		//std::cout << a->angle << '\n';
		return true;
	}
};

int main() {
	uint8_t res = 1;
	InverseKinematics demo;
	if (demo.Construct(256 << res, 240 << res, 4 >> res, 4 >> res))
		demo.Start();
	return 0;
}