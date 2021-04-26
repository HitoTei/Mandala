#include <Siv3D.hpp>

using namespace std;
vector<pair<int, int>> make_position(int n,int r, Point center, double theta0 = 0) {
	vector<pair<int, int>> position(n);
	constexpr double PI = 3.141592653589793;
	for (int i = 0; i < n; i++) {
		double theta = (2 * PI / n) * i + theta0;
		int x = static_cast<int>(cos(theta) * r + center.x);
		int y = static_cast<int>(sin(theta) * r + center.y);
		position[i] = make_pair(x, y);
	}
	return position;
}

vector<Line> make_lines(int n, vector<pair<int,int>> position) {
	vector<Line> lines;
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n; j++) {
			auto from = position[j];
			auto to = position[(n / 2 + i + j) % n];
			auto line = Line(from.first, from.second, to.first, to.second);
			lines.push_back(line);
		}
	}
	return lines;
}

void Main(){
	Scene::SetBackground(ColorF(0, 0, 0));
	constexpr int SIZE = 20;
	constexpr int rest_time = 25000 / (SIZE * SIZE);
	constexpr int R = 300;

	const auto center = Scene::Center();
	auto position = make_position(SIZE, R, center);
	auto lines = make_lines(SIZE, position);

	while (System::Update()){
		static int count = 0;
		count++;
		if (count > lines.size()) {
			position = make_position(SIZE, R, center, count);
			lines = make_lines(SIZE, position);
			System::Sleep(50);
		}
		else {
			System::Sleep(rest_time);
		}
		for (int i = 0; i < min(count, (int)lines.size()); i++) {
			int r = static_cast<int>((lines.size() / 255) * (i / SIZE));
			int g = 255;
			int b = 0;
			lines[i].draw(1, Color(r, g, b));
		}
	}
}
