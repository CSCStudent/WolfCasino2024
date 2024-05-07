#pragma once
using namespace std;

namespace S02710191 {
	class Die {
		private:

		public:
			int value = 0;
			Die();
			~Die();
			int getValue();
			int rollDie(); // randomizes die value
	};
}