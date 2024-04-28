#pragma once
#include <string>
using namespace std;

// CSC2034 C++ class project
//Header file for class Casino XXX

//defined namespace for project
namespace CSC2034 {
	class Casino {
	public:
		static void play(string);
		virtual void start();
		~Casino();

	};

	class NoGame {
	public:
		NoGame(string s) {
			msg = s;
		}
		string getMsg() { return msg; }
		friend ostream& operator << (ostream& out, NoGame& e);
	private:
		string msg;
	};
}
