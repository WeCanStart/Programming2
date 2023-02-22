#include <iostream>

void solve() {
	int n;
	std::cin >> n;
	bool cr(0), cb(0);
	for (int i = 0; i < n; ++i) {
		char l = 0;
		std::cin >> l;
		if (l == 'W') {
			if (cr != cb) {
				std::cout << "NO" << std::endl;
				for (int j = i + 1; j < n; ++j) {
					std::cin >> l;
				}
				return;
			}
			cr = 0;
			cb = 0;
		}
		if (l == 'R') {
			cr = 1;
		}
		if (l == 'B') {
			cb = 1;
		}
	}
	if (cr != cb) {
		std::cout << "NO" << std::endl;
		return;
	}
	std::cout << "YES" << std::endl;
	return;
}

int main()
{
	int t(0);
	std::cin >> t;
	while (t--) {
		solve();
	}
  return 0;
}
