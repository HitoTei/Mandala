
	#include <Siv3D.hpp> 

	void Main(){
		using namespace std;
		Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
		constexpr int SIZE = 40;
		constexpr int R = 300;
		constexpr double PI = 3.141592653589793;
		const auto center = Scene::Center();

		vector<pair<int, int>> position(SIZE);
		for (int i = 0; i < SIZE; i++){
			double theta = (2 * PI / SIZE) * i;
			int x = cos(theta) * R + center.x;
			int y = sin(theta) * R + center.y;
			position[i] = make_pair(x, y);
		}
	
		vector<Line> lines;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				auto from = position[j];
				auto to = position[(i + j + 1) % SIZE];
				auto line = Line(from.first, from.second, to.first, to.second);
				lines.push_back(line);
			}
		}
		while (System::Update()){
			System::Sleep(100);
			static int count = 0;
			count++;
			for (int i = 0; i < min(count, (int)lines.size()); i++) {
				int tmp = (255 * 255) / lines.size();
				int r = (i * tmp) / 255 / 255;
				int g = ((i * tmp) / 255) % 255;
				int b = (i * tmp) % 255;
				lines[i].draw(1, Color(r, g, b));
			}
		}
	}
