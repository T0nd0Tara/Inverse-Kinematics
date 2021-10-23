#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define TARA_PGE_EXTENSION
#include <taraNS.h>
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
	uint8_t segmentNum = 8;

protected:
	bool OnUserCreate() override {
		vec.push_back(new Segment({ ScreenWidth() >> 1, ScreenHeight() >> 1 }, 20, 0));
		for (uint8_t i = 1; i < segmentNum; i++)
			vec.push_back(new Segment(vec.back(), 20, 0));

		return true;
	}

	bool OnUserUpdate(float elapsedTime) override {
		Clear(olc::BLACK);
		if (GetKey(olc::ESCAPE).bPressed) return false;

		vec.back()->Update(GetMousePos());
		vec.back()->MoveA(vec[0]->a - olc::vi2d{ ScreenWidth() >> 1, ScreenHeight() >> 1 });
		vec.back()->Draw(this);

		Sleep(20);
		//std::cout << a->angle << '\n';
		return true;
	}
};

int main() {
	InverseKinematics demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}