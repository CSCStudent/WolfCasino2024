#pragma once
#include "Casino.h"
#include <iostream>
#include "S01505380B.h"
#include "S01505380C.h"

namespace S01505380 {

	class WarCardGame : public CSC2034::Casino {

	public:
		WarCardGame() {
		//intentionally left this empty
		};
		void start();
		static WarCardGame* makeGame();

	private:
		void thisIsWar(deck& deck1, deck& deck2, deck& middlePile);


	};
}