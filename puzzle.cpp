
#include "Window.h"
#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#include "Point.h"
#include "scoreboard.h"
#include <utility>
#include "std_lib_facilities_5.h"

int EASY_COUNT = 0;
string name("");
auto choice = "";
int NEW_SCORE;
string nameA = "";
string nameI = "";
string nameE = "";

///////////////////////////////////////////////
// EXPERT LEVEL TOP 5 SCORES **************************
///////////////////////////////////////////////


struct expert_scoresheet : Graph_lib::Window {
	expert_scoresheet(Point xy, int w, int h, const string& title);
	Text top5{ Point{ 306, 255 }, "Top 5 Scores" };

private:
	Button play;
	static void cb_play(Address, Address);
	void play_game();

	Button submit;
	static void cb_submit(Address, Address);
	void submit_button();

	vector<Scores> scoresE;
	Vector_ref<Text> textE;

	In_box name_inputE;

};


expert_scoresheet::expert_scoresheet(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	play{ Point{ x_max() - 100,40 }, 80, 35, "PLAY GAME",cb_play },
	submit{ Point{ x_max() - 200,200 }, 70, 20, "Submit",cb_submit },
	name_inputE{ Point{ x_max() - 260,200 }, 70, 20, "Add Name: " }
{
    Image Tomb{ Point{ 200, 230}, "tomb.jpeg" };
    attach(Tomb);
    Image Ghost{ Point{ -50,230 }, "ghost.jpeg" };
    attach(Ghost);
	top5.set_font_size(25);
	attach(play);
	attach(submit);
	attach(name_inputE);
	attach(top5);


	scoresE = readScores("expertScore.txt");


	for (int i = 0; i < 5; i++) {
		string a = scoresE.at(i).getScoresandName();
		int value = i * 30;
		textE.push_back(new Text{ Point{ 320, 305 + value }, a });
	}


	for (int i = 0; i < 5; i++) {
		textE[i].set_font_size(20);
		attach(textE[i]);
	}

	Fl::run();
	Fl::redraw();
}


void expert_scoresheet::cb_play(Address, Address pw2)
{
	reference_to<expert_scoresheet>(pw2).play_game();
}


void expert_scoresheet::play_game() {
	hide();
}


void expert_scoresheet::cb_submit(Address, Address pw2)
{
	reference_to<expert_scoresheet>(pw2).submit_button();
}


void expert_scoresheet::submit_button() {


	 nameE = name_inputE.get_string();

	string finalVal = writeScores(scoresE, "expertScore.txt", nameE);


	textE.push_back(new Text{ Point{ 320, 440 }, finalVal });
	textE[textE.size() - 1].set_font_size(20);
	attach(textE[textE.size() - 1]);


	sort(scoresE.begin(), scoresE.end(), compareScore);


	redraw();
}

////////////////////////////////////////////
// UPDATED TOP  5 SCORE LIST FOR EASY LEVEL END OF GAME ************
////////////////////////////////////////////


struct expert_scoresheetEnd : Graph_lib::Window {
	expert_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name);
	Text top5{ Point{ 100, 100 }, "" };

private:
	Button play_button;
	static void cb_play(Address, Address);
	void play();

	Button quit_button;
	static void cb_quit(Address, Address);
	void quit();

	int NEW_score_expert;
	vector<Scores> scoresE;
	Vector_ref<Text> textEEnd;
};

expert_scoresheetEnd::expert_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name)
	:Window{ xy,w,h,title },
	play_button{ Point{ 100,400 }, 75, 30, "PLAY AGAIN",cb_play },
	quit_button{ Point{ 300,400 }, 75, 30, "QUIT",cb_quit }

{
	top5.set_font_size(25);

	string scoreOutPut = name + " your Score is " + to_string(score);

	top5.set_label(scoreOutPut);

	NEW_score_expert = score;
    Image Open{ Point{ 0,100 }, "OPEN.jpeg" };
    attach(Open);
	attach(top5);
	attach(play_button);
	attach(quit_button);

	scoresE = readScores("expertScore.txt");

	string finalVal = writeScores(scoresE, "expertScore.txt", name, NEW_score_expert);


	for (int i = 0; i < 5; i++) {
		string a = scoresE.at(i).getScoresandName();
		int value = i * 30;
		textEEnd.push_back(new Text{ Point{ 320, 300 + value }, a });
	}


	sort(scoresE.begin(), scoresE.end(), compareScore);

	Fl::run();
	Fl::redraw();

}

void expert_scoresheetEnd::cb_play(Address, Address pw2)
{
	reference_to<expert_scoresheetEnd>(pw2).play();
}




void expert_scoresheetEnd::cb_quit(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<expert_scoresheetEnd>(pw2).quit();
}


void expert_scoresheetEnd::quit() {

	hide();
}




///////////////////////////////////////////////////////////////////
// EXPERT LEVEL GAME *********************************************
//////////////////////////////////////////////////////////////////


struct moves_80 : Graph_lib::Window {
    Image Door{ Point{ 500,100 }, "door.jpeg" };
    Image Crystal{ Point{ 100,0 }, "crystals.jpeg" };
	string description = "MOVES LEFT: 80";
	moves_80(Point xy, int w, int h, const string& title);
	Rectangle border_rect{ Point{ 100,100 }, 400, 400 };
	Text moveAmount{ Point{ 100, 600 }, "TRY AND SOLVE THE GAME IN 80 MOVES!  " };
	Text moveCount{ Point{ 600,100 },  description };
	Text moveOrder{ Point{ 100,650 }, "The red tiles are not in the correct position" };


private:
	Button b12;
	Button b11;
	Button b13;
	Button b15;
	Button b14;
	Button b10;
	Button b09;
	Button b03;
	Button b07;
	Button b06;
	Button b02;
	Button b04;
	Button b08;
	Button b05;
	Button b01;

	Out_box outBox;
	Button Hint;

	int moves80_count = 80;
	void decrement_count();

	pair<int, int>BL = make_pair(100, 100);  ///MOVE
	pair<int, int> coordinates(string str);
	void move_button(string str);
	void MOVE(string str, pair<int, int>Change);


	void COLOR(string str); //COLOR
	void START_COLOR();


	int COUNTER(); //COUNTER
	int COUNTER2(string str);

	string Choice(); //MD
	vector<string> FIND();
	int MD(string option, pair<int, int>optionInfo);
	int Calc(pair<int, int> var1, pair<int, int>var2);


	static void cb_b12(Address, Address);
	void button_b12();


	static void cb_b11(Address, Address);
	void button_b11();

	static void cb_b13(Address, Address);
	void button_b13();

	static void cb_b15(Address, Address);
	void button_b15();

	static void cb_b14(Address, Address);
	void button_b14();

	static void cb_b10(Address, Address);       // callback for next_button
	void button_b10();

	static void cb_b09(Address, Address);
	void button_b09();

	static void cb_b03(Address, Address);
	void button_b03();

	static void cb_b07(Address, Address);
	void button_b07();

	static void cb_b06(Address, Address);
	void button_b06();

	static void cb_b02(Address, Address);
	void button_b02();

	static void cb_b04(Address, Address);
	void button_b04();

	static void cb_b08(Address, Address);
	void button_b08();

	static void cb_b05(Address, Address);
	void button_b05();

	static void cb_b01(Address, Address);
	void button_b01();

	static void cb_Hint(Address, Address);
	void button_Hint();
};


moves_80::moves_80(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	b12{ Point{ 200,100 } , 100, 100, "12",cb_b12 },
	b11{ Point{ 300,100 }, 100, 100, "11",cb_b11 },
	b13{ Point{ 400,100 }, 100, 100, "13",cb_b13 },
	b15{ Point{ 100,200 }, 100, 100, "15",cb_b15 },
	b14{ Point{ 200,200 }, 100, 100, "14",cb_b14 },
	b10{ Point{ 300,200 }, 100, 100, "10",cb_b10 },
	b09{ Point{ 400,200 }, 100, 100, "09",cb_b09 },
	b03{ Point{ 100,300 }, 100, 100, "03",cb_b03 },
	b07{ Point{ 200,300 }, 100, 100, "07",cb_b07 },
	b06{ Point{ 300,300 }, 100, 100, "06",cb_b06 },
	b02{ Point{ 400,300 }, 100, 100, "02",cb_b02 },
	b04{ Point{ 100,400 }, 100, 100, "04",cb_b04 },
	b08{ Point{ 200,400 }, 100, 100, "08",cb_b08 },
	b05{ Point{ 300,400 }, 100, 100, "05",cb_b05 },
	b01{ Point{ 400,400 }, 100, 100, "01",cb_b01 },
	outBox{ Point{370,0}, 150, 40, "Move this Button:" },
	Hint{ Point{100,0}, 80, 100, "Hint", cb_Hint  }


{
	border_rect.set_style(Line_style{ Line_style::solid, 2 });
	attach(border_rect);
	moveAmount.set_font_size(25);
	moveCount.set_font_size(20);
	moveOrder.set_font_size(25);
	attach(moveAmount);
	attach(b12);
	attach(b11);
	attach(b13);
	attach(b15);
	attach(b14);
	attach(b10);
	attach(b09);
	attach(b03);
	attach(b07);
	attach(b06);
	attach(b02);
	attach(b04);
	attach(b08);
	attach(b05);
	attach(b01);
	attach(moveCount);
	attach(moveOrder);
	START_COLOR();
    attach(Crystal);
	attach(outBox);
	attach(Hint);
    attach(Door);

	Fl::run();
	Fl::redraw();
}


void moves_80::decrement_count() {
	moves80_count--;
	description = "MOVES LEFT: " + to_string(moves80_count);
	moveCount.set_label(description);

	if (moves80_count == 0) {
		// NEW WINDOW THAT SAYS GAME OVER AND THE SCORE THEY MADE 
		int expertScore = COUNTER() * 10;
		hide();
		expert_scoresheetEnd expertWindow(Point{ 300,300 }, 500, 500, "Game Results ", expertScore, nameE);

		moveCount.set_label("GAME OVER");
		
	}

	redraw();
}


////////////////////////////////////////////////COUNTER

int moves_80::COUNTER() {
	int C = 0;
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };
	for (int i = 0; i<Labels.size(); ++i) {
		C = C + COUNTER2(Labels[i]);
	}

	return C;
}


int moves_80::COUNTER2(string str) {
	int C = 0;
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));
	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x; y = var.y;
			if (x == Final[i].first && y == Final[i].second) {
				C = C + 1;
			}
		}
	}
	return C;
}

//////////////////////////////////////////////////////////////////////////MD


string moves_80::Choice() {

	vector<string>VEC = FIND();
	vector<int>results;

	for (int i = 0; i<VEC.size(); ++i) {
		results.push_back(MD(VEC[i], BL)); //Gives MD of each option and stores in vector of ints
	}

	int min = results[0];
	string choice = VEC[0];

	for (int c = 1; c<results.size(); ++c) {
		if (results[c] < min) {
			min = results[c]; choice = VEC[c];
		}

	}

	return choice;

}


//////////////////////////////////////////////////HINT

void moves_80::cb_Hint(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_Hint();
	reference_to<moves_80>(pw2).Choice();
}

void moves_80::button_Hint() {
	outBox.put(Choice());
}


vector<string> moves_80::FIND() {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);

	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	vector<string>FOUND; string INFO;

	Point var; int x; int y;

	for (int i = 0; i<Bs.size(); ++i) {

		var = Bs[i].loc; x = var.x; y = var.y;
		if (x + 100 == BL.first && y == BL.second) { //checks to right
			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x - 100 == BL.first && y == BL.second) { //checks left

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y + 100 == BL.second) { //checks below

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y - 100 == BL.second) { //checks above

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}
	}

	return FOUND;
}


int moves_80::MD(string option, pair<int, int>optionInfo) {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));

	int sum = 0; Point point; pair<int, int>var1; pair<int, int>var2;

	for (int i = 0; i<Bs.size(); ++i) {

		point = Bs[i].loc; var1 = make_pair(point.x, point.y); var2 = make_pair(Final[i].first, Final[i].second);

		if (option == Bs[i].label) {

			sum = sum + Calc(optionInfo, var2);
		}

		else {

			sum = sum + Calc(var1, var2);
		}
	}

	return sum;
}

int moves_80::Calc(pair<int, int> var1, pair<int, int>var2) {

	int part1 = abs(var2.first - var1.first);
	int part2 = abs(var2.second - var1.second);
	int ans = part1 + part2;
	return ans;
}

////////////////////////////////////////////////BUTTON COLOR

void moves_80::START_COLOR() {
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };
	for (int i = 0; i<Labels.size(); ++i) {
		moves_80::COLOR(Labels[i]);
	}

	return;
}


void moves_80::COLOR(string str) {
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));
	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x; y = var.y;
			if (x == Final[i].first && y == Final[i].second) {
				Bs[i].pw->color(Color::green);
			}
			else {
				Bs[i].pw->color(Color::red);
			}
		}
	}
	return;
}

////////////////////////////////////////////////////////////////////MOVE FUNCTIONALITY

pair<int, int> moves_80::coordinates(string str) {
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04); Bs.push_back(b05); Bs.push_back(b06);
	Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09); Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	int x; int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x;
			y = var.y;
		}
	}
	pair<int, int>coordinate;
	coordinate = make_pair(x, y);
	return coordinate;
}


void moves_80::move_button(string str) {
	pair<int, int>Change;
	Change = make_pair(0, 0); //How much in each direction will the botton move?
	pair<int, int>Button = coordinates(str);

	if (Button.first + 100 == BL.first && Button.second == BL.second) { //checks to right
		Change.first = 100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first - 100 == BL.first && Button.second == BL.second) { //checks left
		Change.first = -100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first == BL.first && Button.second + 100 == BL.second) { //checks below
		Change.first = 0; Change.second = 100;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first == BL.first && Button.second - 100 == BL.second) { //checks above
		Change.first = 0; Change.second = -100;
		BL.first = Button.first; BL.second = Button.second;
	}
	else {  //If nothing matches, nothing happens
		Change.first = 0; Change.second = 0;
	}
	MOVE(str, Change); moves_80::COLOR(str);
	return;
}

void moves_80::MOVE(string str, pair<int, int>Change) {
	Vector_ref<Button>Bs;  //Find way to condense this
	Bs.push_back(b01);
	Bs.push_back(b02);
	Bs.push_back(b03);
	Bs.push_back(b04);
	Bs.push_back(b05);
	Bs.push_back(b06);
	Bs.push_back(b07);
	Bs.push_back(b08);
	Bs.push_back(b09);
	Bs.push_back(b10);
	Bs.push_back(b11);
	Bs.push_back(b12);
	Bs.push_back(b13);
	Bs.push_back(b14);
	Bs.push_back(b15);

	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			Bs[i].move(Change.first, Change.second);
		}
	}

	return;

}
/////////////////////////////////////////////////////////MOVE FUNCTIONALITY END


void moves_80::cb_b01(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b01();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("01");
}

void moves_80::button_b01() {

}


void moves_80::cb_b05(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b05();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("05");
}


void moves_80::button_b05() {
	
}

void moves_80::cb_b08(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b08();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("08");
}

void moves_80::button_b08() {
	
}

void moves_80::cb_b04(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b04();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("04");
}

void moves_80::button_b04() {
	
}

void moves_80::cb_b02(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b02();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("02");
}


void moves_80::button_b02() {

}


void moves_80::cb_b06(Address, Address pw2)

{
	reference_to<moves_80>(pw2).button_b06();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("06");
}


void moves_80::button_b06() {
	
}


void moves_80::cb_b07(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b07();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("07");
}

void moves_80::button_b07() {
	
}


void moves_80::cb_b03(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b03();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("03");
}


void moves_80::button_b03() {
	
}

void moves_80::cb_b09(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b09();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("09");
}


void moves_80::button_b09() {
	
}

void moves_80::cb_b10(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b10();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("10");
}


void moves_80::button_b10() {
	
}


void moves_80::cb_b14(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b14();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("14");
}


void moves_80::button_b14() {
	
}


void moves_80::cb_b15(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b15();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("15");
}


void moves_80::button_b15() {
	
}


void moves_80::cb_b13(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<moves_80>(pw2).button_b13();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("13");
}


void moves_80::button_b13() {

}


void moves_80::cb_b11(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<moves_80>(pw2).button_b11();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("11");
}


void moves_80::button_b11() {
	
}


void moves_80::cb_b12(Address, Address pw2)
{
	reference_to<moves_80>(pw2).button_b12();
	reference_to<moves_80>(pw2).decrement_count();
	reference_to<moves_80>(pw2).move_button("12");
}


void moves_80::button_b12() {
	
}

/////////////////////////////////////////////////
// ADVANCED LEVEL SCORE BOARD***********************
/////////////////////////////////////////////////
struct advanced_scoresheet : Graph_lib::Window {
	advanced_scoresheet(Point xy, int w, int h, const string& title);
	Text top5{ Point{ 306, 255 }, "Top 5 Scores" };

private:
	Button play;
	static void cb_play(Address, Address);
	void play_game();

	Button submit;
	static void cb_submit(Address, Address);
	void submit_button();

	vector<Scores> scoresA;
	Vector_ref<Text> textA;

	In_box name_inputA;
};


advanced_scoresheet::advanced_scoresheet(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	play{ Point{ x_max() - 100,40 }, 80, 35, "PLAY GAME",cb_play },
	submit{ Point{ x_max() - 200,200 }, 70, 20, "Submit",cb_submit },
	name_inputA{ Point{ x_max() - 260,200 }, 70, 20, "Add Name: " }
{
    Image Tomb{ Point{ 200, 230}, "tomb.jpeg" };
    attach(Tomb);
    Image Ghost{ Point{ -50,230 }, "ghost.jpeg" };
    attach(Ghost);
	top5.set_font_size(25);
	attach(play);
	attach(submit);
	attach(name_inputA);
	attach(top5);

	scoresA = readScores("advanceScore.txt");

	for (int i = 0; i < 5; i++) {
		string a = scoresA.at(i).getScoresandName();
		int value = i * 30;
		textA.push_back(new Text{ Point{ 320, 305 + value }, a });
	}

	for (int i = 0; i < 5; i++) {
		textA[i].set_font_size(20);
		attach(textA[i]);
	}

	Fl::run();
	Fl::redraw();

}


void advanced_scoresheet::cb_play(Address, Address pw2)
{
	reference_to<advanced_scoresheet>(pw2).play_game();
}

void advanced_scoresheet::play_game() {
	hide();
}

void advanced_scoresheet::cb_submit(Address, Address pw2)
{
	reference_to<advanced_scoresheet>(pw2).submit_button();
}

void advanced_scoresheet::submit_button() {

	 nameA = name_inputA.get_string();

	string finalVal = writeScores(scoresA, "advanceScore.txt", nameA);

	textA.push_back(new Text{ Point{ 320, 440 }, finalVal });
	textA[textA.size() - 1].set_font_size(20);
	attach(textA[textA.size() - 1]);

	sort(scoresA.begin(), scoresA.end(), compareScore);

	redraw();

}

////////////////////////////////////////////
// UPDATED TOP  5 SCORE LIST FOR ADVANCED LEVEL END OF GAME ************
////////////////////////////////////////////


struct advanced_scoresheetEnd : Graph_lib::Window {
	advanced_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name);
	Text top5{ Point{ 100, 100 }, "" };

private:
	Button play_button;
	static void cb_play(Address, Address);
	void play();

	Button quit_button;
	static void cb_quit(Address, Address);
	void quit();

	int NEW_score_advanced;
	vector<Scores> scoresA;
	Vector_ref<Text> textAEnd;
};

advanced_scoresheetEnd::advanced_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name)
	:Window{ xy,w,h,title },
	play_button{ Point{ 100,400 }, 75, 30, "PLAY AGAIN",cb_play },
	quit_button{ Point{ 300,400 }, 75, 30, "QUIT",cb_quit }

{
	top5.set_font_size(25);

	string scoreOutPut = name + " Your Score is " + to_string(score);

	top5.set_label(scoreOutPut);

	NEW_score_advanced = score;
    Image Open{ Point{ 0,100 }, "OPEN.jpeg" };
    attach(Open);
	attach(top5);
	attach(play_button);
	attach(quit_button);

	scoresA = readScores("advanceScore.txt");

	string finalVal = writeScores(scoresA, "advanceScore.txt", name, NEW_score_advanced);


	for (int i = 0; i < 5; i++) {
		string a = scoresA.at(i).getScoresandName();
		int value = i * 30;
		textAEnd.push_back(new Text{ Point{ 320, 300 + value }, a });
	}


	sort(scoresA.begin(), scoresA.end(), compareScore);

	Fl::run();
	Fl::redraw();

}

void advanced_scoresheetEnd::cb_play(Address, Address pw2)
{
	reference_to<advanced_scoresheetEnd>(pw2).play();
}


void advanced_scoresheetEnd::cb_quit(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<advanced_scoresheetEnd>(pw2).quit();
}


void advanced_scoresheetEnd::quit() {
	hide();
}




///////////////////////////////////////////////////////
//ADVANCED LEVEL GAME**********************************
//////////////////////////////////////////////////////


struct moves_40 :Graph_lib::Window {
    
    Image Door{ Point{ 500,100 }, "door.jpeg" };
    Image Crystal{ Point{ 100,0 }, "crystals.jpeg" };
	string description = "Moves left: 40";
	moves_40(Point xy, int w, int h, const string& title);
	Rectangle border_rect{ Point{ 100,100 }, 400, 400 };
	Text moveAmount{ Point{ 100, 600 }, "TRY AND SOLVE THE GAME IN 40 MOVES!  " };
	Text moveCount{ Point{ 600,100 },  description };
	Text moveOrder{ Point{ 100,650 }, "The red tiles are not in the correct position" };

private:
	Button b06;
	Button b05;
	Button b11;
	Button b04;
	Button b10;
	Button b13;
	Button b02;
	Button b01;
	Button b09;
	Button b15;
	Button b07;
	Button b03;
	Button b14;
	Button b12;
	Button b08;

	Out_box outBox;
	Button Hint;

	int moves40_count = 40;
	void decrement_count();

	pair<int, int>BL = make_pair(200, 200);  //These lines are for move functionality
	pair<int, int> coordinates(string str);
	void move_button(string str);
	void MOVE(string str, pair<int, int>Change);

	void COLOR(string str); //COLOR
	void START_COLOR();

	int COUNTER(); //COUNTER
	int COUNTER2(string str);

	string Choice(); //MD
	vector<string> FIND();
	int MD(string option, pair<int, int>optionInfo);
	int Calc(pair<int, int> var1, pair<int, int>var2);

	static void cb_b06(Address, Address);       
	void button_b06(); 

	static void cb_b05(Address, Address);       // callback for next_button
	void button_b05();

	static void cb_b11(Address, Address);       // callback for next_button
	void button_b11();

	static void cb_b04(Address, Address);       // callback for next_button
	void button_b04();

	static void cb_b10(Address, Address);       // callback for next_button
	void button_b10();

	static void cb_b13(Address, Address);       // callback for next_button
	void button_b13();

	static void cb_b02(Address, Address);       // callback for next_button
	void button_b02();

	static void cb_b01(Address, Address);       // callback for next_button
	void button_b01();

	static void cb_b09(Address, Address);       // callback for next_button
	void button_b09();

	static void cb_b15(Address, Address);       // callback for next_button
	void button_b15();

	static void cb_b07(Address, Address);       // callback for next_button
	void button_b07();

	static void cb_b03(Address, Address);       // callback for next_button
	void button_b03();

	static void cb_b14(Address, Address);       // callback for next_button
	void button_b14();

	static void cb_b12(Address, Address);       // callback for next_button
	void button_b12();

	static void cb_b08(Address, Address);       // callback for next_button
	void button_b08();

	static void cb_Hint(Address, Address);       // callback for next_button
	void button_Hint();
};


moves_40::moves_40(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	b04{ Point{ 100,100 }, 100, 100, "04",cb_b04 },
	b08{ Point{ 200,100 }, 100, 100, "08",cb_b08 },
	b12{ Point{ 300,100 }, 100, 100, "12",cb_b12 },
	b15{ Point{ 400,100 }, 100, 100, "15",cb_b15 },
	b03{ Point{ 100,200 }, 100, 100, "03",cb_b03 },
	b07{ Point{ 300,200 }, 100, 100, "07",cb_b07 },
	b11{ Point{ 400,200 }, 100, 100, "11",cb_b11 },
	b09{ Point{ 100,300 }, 100, 100, "09",cb_b09 },
	b02{ Point{ 200,300 }, 100, 100, "02",cb_b02 },
	b01{ Point{ 300,300 }, 100, 100, "01",cb_b01 },
	b10{ Point{ 400,300 }, 100, 100, "10",cb_b10 },
	b13{ Point{ 100,400 }, 100, 100, "13",cb_b13 },
	b14{ Point{ 200,400 }, 100, 100, "14",cb_b14 },
	b05{ Point{ 300,400 }, 100, 100, "05",cb_b05 },
	b06{ Point{ 400,400 }, 100, 100, "06",cb_b06 },
	outBox{ Point{370,0}, 100, 20, "Move this Button:" },
	Hint{ Point{100, 0}, 80, 100, "Hint: ", cb_Hint }


{
	border_rect.set_style(Line_style{ Line_style::solid, 2 });
	attach(border_rect);
	moveAmount.set_font_size(25);
	moveCount.set_font_size(20);
	moveOrder.set_font_size(25);
	attach(moveAmount);
	attach(b12);
	attach(b11);
	attach(b13);
	attach(b15);
	attach(b14);
	attach(b10);
	attach(b09);
	attach(b03);
	attach(b07);
	attach(b06);
	attach(b02);
	attach(b04);
	attach(b08);
	attach(b05);
	attach(b01);
	attach(moveOrder);
    attach(Crystal);
    attach(Door);

	attach(outBox);
	attach(Hint);

	attach(moveCount);
	START_COLOR();
	Fl::run();
	Fl::redraw();
}


////////////////////////////////////////////////BUTTON COLOR

void moves_40::START_COLOR() {
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };
	for (int i = 0; i<Labels.size(); ++i) {
		moves_40::COLOR(Labels[i]);
	}

	return;
}


void moves_40::COLOR(string str) {
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));
	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x; y = var.y;
			if (x == Final[i].first && y == Final[i].second) {
				Bs[i].pw->color(Color::green);
			}
			else {
				Bs[i].pw->color(Color::red);
			}

		}
	}
	return;
}


////////////////////////////////////////////////MOVE FUNCTIONALITY
pair<int, int> moves_40::coordinates(string str) {
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04); Bs.push_back(b05); Bs.push_back(b06);
	Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09); Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	int x; int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x;
			y = var.y;
		}
	}


	pair<int, int>coordinate;
	coordinate = make_pair(x, y);


	return coordinate;
}






void moves_40::move_button(string str) {
	pair<int, int>Change;
	Change = make_pair(0, 0); //How much in each direction will the botton move?
	pair<int, int>Button = coordinates(str);

	if (Button.first + 100 == BL.first && Button.second == BL.second) { //checks to right
		Change.first = 100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first - 100 == BL.first && Button.second == BL.second) { //checks left
		Change.first = -100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first == BL.first && Button.second + 100 == BL.second) { //checks below
		Change.first = 0; Change.second = 100;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first == BL.first && Button.second - 100 == BL.second) { //checks above
		Change.first = 0; Change.second = -100;
		BL.first = Button.first; BL.second = Button.second;
	}
	else {  //If nothing matches, nothing happens
		Change.first = 0; Change.second = 0;
	}
	MOVE(str, Change); COLOR(str);
	return;
}


void moves_40::MOVE(string str, pair<int, int>Change) {

	Vector_ref<Button>Bs;  //Find way to condense this
	Bs.push_back(b01);
	Bs.push_back(b02);
	Bs.push_back(b03);
	Bs.push_back(b04);
	Bs.push_back(b05);
	Bs.push_back(b06);
	Bs.push_back(b07);
	Bs.push_back(b08);
	Bs.push_back(b09);
	Bs.push_back(b10);
	Bs.push_back(b11);
	Bs.push_back(b12);
	Bs.push_back(b13);
	Bs.push_back(b14);
	Bs.push_back(b15);

	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {

			Bs[i].move(Change.first, Change.second);
		}
	}

	return;


}


void moves_40::decrement_count() {
	moves40_count--;

	description = "MOVES LEFT: " + to_string(moves40_count);

	moveCount.set_label(description);

	if (moves40_count == 0) {

	int Advanced_score = COUNTER() * 10;

	hide();
	advanced_scoresheetEnd advancedWindow(Point{ 300,300 }, 500, 500, "Game Results ", Advanced_score, nameA);


		moveCount.set_label("GAME OVER");
	}

	redraw();
}


////////////////////////////////////////////////COUNTER

int moves_40::COUNTER() {

	int C = 0;
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };
	for (int i = 0; i<Labels.size(); ++i) {
		C = C + COUNTER2(Labels[i]);
	}
	return C;
}

int moves_40::COUNTER2(string str) {

	int C = 0;

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));
	int x; int y; Point var;

	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;

			x = var.x; y = var.y;

			if (x == Final[i].first && y == Final[i].second) {
				C = C + 1;
			}
		}
	}
	return C;
}

//////////////////////////////////////////////////////////////////////////MD


string moves_40::Choice() {

	vector<string>VEC = FIND();
	vector<int>results;

	for (int i = 0; i<VEC.size(); ++i) {
		results.push_back(MD(VEC[i], BL)); //Gives MD of each option and stores in vector of ints
	}

	int min = results[0];
	string choice = VEC[0];

	for (int c = 1; c<results.size(); ++c) {
		if (results[c] < min) {
			min = results[c]; choice = VEC[c];
		}

	}

	return choice;
}

//////////////////////////////////////////////////HINT

void moves_40::cb_Hint(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_Hint();
	reference_to<moves_40>(pw2).Choice();
}

void moves_40::button_Hint() {
	outBox.put(Choice());
}


vector<string> moves_40::FIND() {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);

	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	vector<string>FOUND; string INFO;

	Point var; int x; int y;

	for (int i = 0; i<Bs.size(); ++i) {

		var = Bs[i].loc; x = var.x; y = var.y;
		if (x + 100 == BL.first && y == BL.second) { //checks to right
			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x - 100 == BL.first && y == BL.second) { //checks left

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y + 100 == BL.second) { //checks below

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y - 100 == BL.second) { //checks above

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}
	}

	return FOUND;
}


int moves_40::MD(string option, pair<int, int>optionInfo) {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));

	int sum = 0; Point point; pair<int, int>var1; pair<int, int>var2;

	for (int i = 0; i<Bs.size(); ++i) {

		point = Bs[i].loc; var1 = make_pair(point.x, point.y); var2 = make_pair(Final[i].first, Final[i].second);

		if (option == Bs[i].label) {

			sum = sum + Calc(optionInfo, var2);
		}

		else {
			sum = sum + Calc(var1, var2);
		}
	}

	return sum;
}

int moves_40::Calc(pair<int, int> var1, pair<int, int>var2) {

	int part1 = abs(var2.first - var1.first);
	int part2 = abs(var2.second - var1.second);
	int ans = part1 + part2;
	return ans;
}



void moves_40::cb_b08(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b08();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("08");

}


void moves_40::button_b08() {
	
}

void moves_40::cb_b12(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b12();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("12");
}

void moves_40::button_b12() {
	
}


void moves_40::cb_b14(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b14();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("14");
}


void moves_40::button_b14() {
	
}


void moves_40::cb_b03(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b03();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("03");
}


void moves_40::button_b03() {
	
}


void moves_40::cb_b07(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b07();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("07");
}


void moves_40::button_b07() {
	
}


void moves_40::cb_b15(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b15();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("15");
}


void moves_40::button_b15() {
	
}


void moves_40::cb_b09(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b09();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("09");
}


void moves_40::button_b09() {
	
}


void moves_40::cb_b01(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b01();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("01");
}


void moves_40::button_b01() {
	
}


void moves_40::cb_b02(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b02();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("02");
}


void moves_40::button_b02() {
	
}


void moves_40::cb_b13(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<moves_40>(pw2).button_b13();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("13");
}


void moves_40::button_b13() {

}


void moves_40::cb_b10(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b10();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("10");
}


void moves_40::button_b10() {

}


void moves_40::cb_b04(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b04();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("04");
}


void moves_40::button_b04() {

}


void moves_40::cb_b11(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b11();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("11");
}


void moves_40::button_b11() {
	
}


void moves_40::cb_b05(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b05();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("05");
}


void moves_40::button_b05() {
	
}


void moves_40::cb_b06(Address, Address pw2)
{
	reference_to<moves_40>(pw2).button_b06();
	reference_to<moves_40>(pw2).decrement_count();
	reference_to<moves_40>(pw2).move_button("06");
}


void moves_40::button_b06() {

}

//////////////////////////////////////////////////////////
// INTERMEDIATE SCORESHEET TOP 5 SCORES 
//////////////////////////////////////////////////////////

struct intermediate_scoresheet : Graph_lib::Window {
	intermediate_scoresheet(Point xy, int w, int h, const string& title);
	Text top5{ Point{ 306, 255 }, "Top 5 Scores" };

private:
	Button play;
	static void cb_play(Address, Address);
	void play_game();

	Button submit;
	static void cb_submit(Address, Address);
	void submit_button();

	vector<Scores> scoresI;
	Vector_ref<Text> textI;

	In_box name_inputI;
};


intermediate_scoresheet::intermediate_scoresheet(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	play{ Point{ x_max() - 100,40 }, 80, 35, "PLAY GAME",cb_play },
	submit{ Point{ x_max() - 200,200 }, 70, 20, "Submit",cb_submit },
	name_inputI{ Point{ x_max() - 260,200 }, 70, 20, "Add Name: " }
{
	top5.set_font_size(25);
    Image Tomb{ Point{ 200, 230}, "tomb.jpeg" };
    attach(Tomb);
    Image Ghost{ Point{ -50,230 }, "ghost.jpeg" };
    attach(Ghost);
	attach(top5);
	attach(play);
	attach(submit);
	attach(name_inputI);

	scoresI = readScores("intermediateScore.txt");

	for (int i = 0; i < 5; i++) {
		string a = scoresI.at(i).getScoresandName();
		int value = i * 30;
		textI.push_back(new Text{ Point{ 320, 300 + value }, a });
	}


	for (int i = 0; i < 5; i++) {
		textI[i].set_font_size(20);
		attach(textI[i]);
	}

	Fl::run();
	Fl::redraw();
}


void intermediate_scoresheet::cb_play(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<intermediate_scoresheet>(pw2).play_game();
}

void intermediate_scoresheet::play_game() {
	hide();
}


void intermediate_scoresheet::cb_submit(Address, Address pw2)
{
	reference_to<intermediate_scoresheet>(pw2).submit_button();
}


void intermediate_scoresheet::submit_button() {

	 nameI = name_inputI.get_string();

	string finalVal = writeScores(scoresI, "intermediateScore.txt", nameI);

	textI.push_back(new Text{ Point{ 320, 440 }, finalVal });
	textI[textI.size() - 1].set_font_size(20);
	attach(textI[textI.size() - 1]);

	sort(scoresI.begin(), scoresI.end(), compareScore);


	redraw();
}

////////////////////////////////////////////
// UPDATED TOP  5 SCORE LIST FOR INTERMEDIATE LEVEL END OF GAME ************
////////////////////////////////////////////


struct intermediate_scoresheetEnd : Graph_lib::Window {
	intermediate_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name);
	Text top5{ Point{ 100, 100 }, "" };

private:
	Button play_button;
	static void cb_play(Address, Address);
	void play();

	Button quit_button;
	static void cb_quit(Address, Address);
	void quit();

	int NEW_score_inter;
	vector<Scores> scoresI;
	Vector_ref<Text> textIEnd;
};

intermediate_scoresheetEnd::intermediate_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string nameI)
	:Window{ xy,w,h,title },
	play_button{ Point{ 100,400 }, 75, 30, "PLAY AGAIN",cb_play },
	quit_button{ Point{ 300,400 }, 75, 30, "QUIT",cb_quit }

{
	top5.set_font_size(25);

	string scoreOutPutI = nameI + " your Score is " + to_string(score);

	top5.set_label(scoreOutPutI);

	NEW_score_inter = score;
    Image Open{ Point{ 0,100 }, "OPEN.jpeg" };
    attach(Open);
	attach(top5);
	attach(play_button);
	attach(quit_button);

	scoresI = readScores("intermediateScore.txt");

	string finalVal = writeScores(scoresI, "intermediateScore.txt", nameI, NEW_score_inter);


	for (int i = 0; i < 5; i++) {
		string a = scoresI.at(i).getScoresandName();
		int value = i * 30;
		textIEnd.push_back(new Text{ Point{ 320, 300 + value }, a });
	}


	sort(scoresI.begin(), scoresI.end(), compareScore);


	Fl::run();
	Fl::redraw();


}

void intermediate_scoresheetEnd::cb_play(Address, Address pw2)
{
	reference_to<intermediate_scoresheetEnd>(pw2).play();
}


void intermediate_scoresheetEnd::cb_quit(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<intermediate_scoresheetEnd>(pw2).quit();
}


void intermediate_scoresheetEnd::quit() {

	hide();
}



///////////////////////////////////////////////////////////////////////////
// INTERMEDIATE LEVEL GAME *********************************************
////////////////////////////////////////////////////////////////////////


struct moves_20 : Graph_lib::Window {
    Image Door{ Point{ 500,100 }, "door.jpeg" };
    Image Crystal{ Point{ 100,0 }, "crystals.jpeg" };
	string description = "MOVES LEFT: 20";
	moves_20(Point xy, int w, int h, const string& title);
	Rectangle border_rect{ Point{ 100,100 }, 400, 400 };
	Text moveAmount{ Point{ 100, 600 }, "TRY AND SOLVE THE GAME IN 20 MOVES!  " };
	Text moveCount{ Point{ 600,100 },  description };
	Text moveOrder{ Point{ 100,650 }, "The red tiles are not in the correct order" };

private:
	Button b01;
	Button b06;
	Button b03;
	Button b04;
	Button b05;
	Button b02;
	Button b11;
	Button b09;
	Button b10;
	Button b14;
	Button b07;
	Button b13;
	Button b15;
	Button b12;
	Button b08;

	Out_box outBox;
	Button Hint;

	int count = 20;
	void decrement_count();

	pair<int, int>BL = make_pair(200, 200);  //These lines are for move functionality
	pair<int, int> coordinates(string str);
	void move_button(string str);
	void MOVE(string str, pair<int, int>Change);

	int COUNTER(); //COUNTER
	int COUNTER2(string str);

	void COLOR(string str); //COLOR
	void START_COLOR();

	string Choice(); //MD
	vector<string> FIND();
	int MD(string option, pair<int, int>optionInfo);
	int Calc(pair<int, int> var1, pair<int, int>var2);


	static void cb_b02(Address, Address);
	void button_b02();

	static void cb_b05(Address, Address);
	void button_b05();

	static void cb_b01(Address, Address);
	void button_b01();

	static void cb_b04(Address, Address);
	void button_b04();

	static void cb_b10(Address, Address);
	void button_b10();

	static void cb_b07(Address, Address);
	void button_b07();

	static void cb_b03(Address, Address);
	void button_b03();

	static void cb_b08(Address, Address);
	void button_b08();

	static void cb_b13(Address, Address);
	void button_b13();

	static void cb_b11(Address, Address);
	void button_b11();

	static void cb_b12(Address, Address);
	void button_b12();

	static void cb_b06(Address, Address);
	void button_b06();

	static void cb_b09(Address, Address);
	void button_b09();

	static void cb_b14(Address, Address);
	void button_b14();

	static void cb_b15(Address, Address);
	void button_b15();

	static void cb_Hint(Address, Address);
	void button_Hint();


};

moves_20::moves_20(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	b01{ Point{ 100,100 }, 100, 100, "01",cb_b01 },
	b06{ Point{ 200,100 }, 100, 100, "06",cb_b06 },
	b03{ Point{ 300,100 }, 100, 100, "03",cb_b03 },
	b04{ Point{ 400,100 }, 100, 100, "04",cb_b04 },
	b05{ Point{ 100,200 }, 100, 100, "05",cb_b05 },
	b02{ Point{ 300,200 }, 100, 100, "02",cb_b02 },
	b11{ Point{ 400,200 }, 100, 100, "11",cb_b11 },
	b09{ Point{ 100,300 }, 100, 100, "09",cb_b09 },
	b10{ Point{ 200,300 }, 100, 100, "10",cb_b10 },
	b14{ Point{ 300,300 }, 100, 100, "14",cb_b14 },
	b07{ Point{ 400,300 }, 100, 100, "07",cb_b07 },
	b13{ Point{ 100,400 }, 100, 100, "13",cb_b13 },
	b15{ Point{ 200,400 }, 100, 100, "15",cb_b15 },
	b12{ Point{ 300,400 }, 100, 100, "12",cb_b12 },
	b08{ Point{ 400,400 }, 100, 100, "08",cb_b08 },
	outBox{ Point{ 370,0 }, 150, 40, "MOVE THIS BUTTON:" },
	Hint{ Point{ 100,0 }, 80, 100, "HINT" ,cb_Hint }


{
	
	border_rect.set_style(Line_style{ Line_style::solid, 2 });
	attach(border_rect);
	moveAmount.set_font_size(25);
	moveCount.set_font_size(20);
	moveOrder.set_font_size(20);
	attach(moveAmount);
	attach(b12);
	attach(b11);
	attach(b13);
	attach(b15);
	attach(b14);
	attach(b10);
	attach(b09);
	attach(b03);
	attach(b07);
	attach(b06);
	attach(b02);
	attach(b04);
	attach(b08);
	attach(b05);
	attach(b01);
	attach(outBox);
	attach(Hint);
	attach(moveOrder);
    attach(Crystal);
    attach(Door);

	attach(moveCount);

	START_COLOR();
	Fl::run();
	Fl::redraw();
}
//////////////////////////////////////////////////COLOR


void moves_20::START_COLOR() {
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };

	for (int i = 0; i<Labels.size(); ++i) {
		moves_20::COLOR(Labels[i]);
	}

	return;
}

void moves_20::COLOR(string str) {
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));
	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x; y = var.y;
			if (x == Final[i].first && y == Final[i].second) {
				Bs[i].pw->color(Color::green);
			}
			else {
				Bs[i].pw->color(Color::red);
			}
		}
	}
	return;
}

//////////////////////////////////////////////////////MOVE FUNCTIONALITY
pair<int, int> moves_20::coordinates(string str) {
	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04); Bs.push_back(b05); Bs.push_back(b06);
	Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09); Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	int x; int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x;
			y = var.y;
		}
	}

	pair<int, int>coordinate;
	coordinate = make_pair(x, y);

	return coordinate;
}


void moves_20::move_button(string str) {
	pair<int, int>Change;
	Change = make_pair(0, 0); //How much in each direction will the botton move?
	pair<int, int>Button = coordinates(str);

	if (Button.first + 100 == BL.first && Button.second == BL.second) { //checks to right
		Change.first = 100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first - 100 == BL.first && Button.second == BL.second) { //checks left
		Change.first = -100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first == BL.first && Button.second + 100 == BL.second) { //checks below
		Change.first = 0; Change.second = 100;
		BL.first = Button.first; BL.second = Button.second;
	}
	else if (Button.first == BL.first && Button.second - 100 == BL.second) { //checks above
		Change.first = 0; Change.second = -100;
		BL.first = Button.first; BL.second = Button.second;
	}
	else {  //If nothing matches, nothing happens
		Change.first = 0; Change.second = 0;
	}
	MOVE(str, Change); COLOR(str);
	return;
}

void moves_20::MOVE(string str, pair<int, int>Change) {

	Vector_ref<Button>Bs;  //Find way to condense this
	Bs.push_back(b01);
	Bs.push_back(b02);
	Bs.push_back(b03);
	Bs.push_back(b04);
	Bs.push_back(b05);
	Bs.push_back(b06);
	Bs.push_back(b07);
	Bs.push_back(b08);
	Bs.push_back(b09);
	Bs.push_back(b10);
	Bs.push_back(b11);
	Bs.push_back(b12);
	Bs.push_back(b13);
	Bs.push_back(b14);
	Bs.push_back(b15);

	int x;
	int y;
	Point var;
	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {

			Bs[i].move(Change.first, Change.second);
		}
	}

	return;
}


void moves_20::decrement_count() {

	count--;

	description = "MOVES LEFT: " + to_string(count);

	moveCount.set_label(description);
	if (count == 0) {
		int interScore = COUNTER() * 10;
		 hide();
		intermediate_scoresheetEnd interWindow(Point{ 300,300 }, 500, 500, "Game Results ", interScore, nameI);

		moveCount.set_label("GAME OVER");
	}
	redraw();
}

////////////////////////////////////////////////COUNTER

int moves_20::COUNTER() {

	int C = 0;
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };
	for (int i = 0; i<Labels.size(); ++i) {
		C = C + COUNTER2(Labels[i]);
	}
	return C;
}

int moves_20::COUNTER2(string str) {


	int C = 0;

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));
	int x; int y; Point var;

	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;

			x = var.x; y = var.y;

			if (x == Final[i].first && y == Final[i].second) {
				C = C + 1;
			}
		}
	}
	return C;
}



//////////////////////////////////////////////////////////////////////////MD


string moves_20::Choice() {

	vector<string>VEC = FIND();
	vector<int>results;

	for (int i = 0; i<VEC.size(); ++i) {
		results.push_back(MD(VEC[i], BL)); //Gives MD of each option and stores in vector of ints
	}

	int min = results[0];
	string choice = VEC[0];

	for (int c = 1; c<results.size(); ++c) {
		if (results[c] < min) {
			min = results[c]; choice = VEC[c];
		}

	}


	return choice;

}


//////////////////////////////////////////////////HINT

void moves_20::cb_Hint(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_Hint();
	reference_to<moves_20>(pw2).Choice();
}

void moves_20::button_Hint() {
	outBox.put(Choice());
}


vector<string> moves_20::FIND() {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);

	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	vector<string>FOUND; string INFO;

	Point var; int x; int y;

	for (int i = 0; i<Bs.size(); ++i) {

		var = Bs[i].loc; x = var.x; y = var.y;
		if (x + 100 == BL.first && y == BL.second) { //checks to right
			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x - 100 == BL.first && y == BL.second) { //checks left

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y + 100 == BL.second) { //checks below

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y - 100 == BL.second) { //checks above

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}
	}

	return FOUND;
}


int moves_20::MD(string option, pair<int, int>optionInfo) {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));

	int sum = 0; Point point; pair<int, int>var1; pair<int, int>var2;

	for (int i = 0; i<Bs.size(); ++i) {

		point = Bs[i].loc; var1 = make_pair(point.x, point.y); var2 = make_pair(Final[i].first, Final[i].second);

		if (option == Bs[i].label) {

			sum = sum + Calc(optionInfo, var2);
		}

		else {

			sum = sum + Calc(var1, var2);
		}
	}

	return sum;
}

int moves_20::Calc(pair<int, int> var1, pair<int, int>var2) {

	int part1 = abs(var2.first - var1.first);
	int part2 = abs(var2.second - var1.second);
	int ans = part1 + part2;
	return ans;
}


void moves_20::cb_b02(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b02();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("02");
}

void moves_20::button_b02() {

}


void moves_20::cb_b15(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b15();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("15");
}


void moves_20::button_b15() {
	
}

void moves_20::cb_b14(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b14();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("14");
}

void moves_20::button_b14() {

}

void moves_20::cb_b09(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b09();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("09");
}


void moves_20::button_b09() {

}


void moves_20::cb_b06(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b06();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("06");
}


void moves_20::button_b06() {
	
}


void moves_20::cb_b12(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b12();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("12");
}


void moves_20::button_b12() {

}


void moves_20::cb_b11(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b11();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("11");
}


void moves_20::button_b11() {

}


void moves_20::cb_b13(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b13();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("13");
}


void moves_20::button_b13() {

}


void moves_20::cb_b08(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b08();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("08");
}


void moves_20::button_b08() {
	
}


void moves_20::cb_b03(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b03();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("03");
}


void moves_20::button_b03() {
	//hide();
	// Function definition
}


void moves_20::cb_b07(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b07();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("07");
}


void moves_20::button_b07() {

}


void moves_20::cb_b10(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b10();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("10");
}

void moves_20::button_b10() {

}


void moves_20::cb_b04(Address, Address pw2)
{
	reference_to<moves_20>(pw2).button_b04();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("04");
}


void moves_20::button_b04() {

}


void moves_20::cb_b01(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<moves_20>(pw2).button_b01();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("01");
}


void moves_20::button_b01() {

}


void moves_20::cb_b05(Address, Address pw2)

{
	reference_to<moves_20>(pw2).button_b05();
	reference_to<moves_20>(pw2).decrement_count();
	reference_to<moves_20>(pw2).move_button("05");
}


void moves_20::button_b05() {
	//hide();
	// Function definition
}


////////////////////////////////////////////
// TOP  5 SCORE LIST FOR EASY LEVEL************
////////////////////////////////////////////

struct easy_scoresheet : Graph_lib::Window {
	easy_scoresheet(Point xy, int w, int h, const string& title);
	Text top5{ Point{ 306, 255 }, "Top 5 Scores" };

private:
	Button play;
	static void cb_play(Address, Address);       // callback for next_button
	void play_game();  // action to be done when next_button is pressed

	Button submit_button;
	static void cb_submit(Address, Address);
	void submit();

	vector<Scores> scores;
	Vector_ref<Text> text;

	In_box name_input;

};

easy_scoresheet::easy_scoresheet(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	play{ Point{ x_max() - 100,40 }, 80, 35, "PLAY GAME",cb_play },
	submit_button{ Point{ x_max() - 200,200 }, 70, 20, "Submit",cb_submit },
	name_input{ Point{ x_max() - 260, 200 }, 70, 20, "Add Name: " }

{
    Image Tomb{ Point{ 200, 230}, "tomb.jpeg" };
    attach(Tomb);
    Image Ghost{ Point{ -50,230 }, "ghost.jpeg" };
    attach(Ghost);
	top5.set_font_size(25);
	attach(play);
	attach(name_input);
	attach(submit_button);
	attach(top5);

	scores = readScores("beginnerScore.txt");

	for (int i = 0; i < 5; i++) {
		string a = scores.at(i).getScoresandName();
		int value = i * 30;
		text.push_back(new Text{ Point{ 320, 300 + value }, a });
	}

	sort(scores.begin(), scores.end(), compareScore);

	for (int i = 0; i < 5; i++) {
		text[i].set_font_size(20);
		attach(text[i]);
	}

	Fl::run();
	Fl::redraw();
}


void easy_scoresheet::cb_play(Address, Address pw2)
{
	reference_to<easy_scoresheet>(pw2).play_game();
}


void easy_scoresheet::play_game() {
	hide();
}


void easy_scoresheet::cb_submit(Address, Address pw2)
{
	reference_to<easy_scoresheet>(pw2).submit();
}


void easy_scoresheet::submit() {

	sort(scores.begin(), scores.end(), compareScore);

	name = name_input.get_string();

	string finalVal = writeScores(scores, "beginnerScore.txt", name);


	text.push_back(new Text{ Point{ 320, 440 }, finalVal });
	text[text.size() - 1].set_font_size(20);
	attach(text[text.size() - 1]);

	sort(scores.begin(), scores.end(), compareScore);

	redraw();


}


////////////////////////////////////////////
// UPDATED TOP  5 SCORE LIST FOR EASY LEVEL END OF GAME ************
////////////////////////////////////////////


struct easy_scoresheetEnd : Graph_lib::Window {
	easy_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name);
	Text top5{ Point{ 100, 100 }, "" };

private:
	Button play_button;
	static void cb_play(Address, Address);
	void play();

	Button quit_button;
	static void cb_quit(Address, Address);
	void quit();

	int NEW_score_easy;
	vector<Scores> scores;
	Vector_ref<Text> textEnd;
};

easy_scoresheetEnd::easy_scoresheetEnd(Point xy, int w, int h, const string& title, int score, string name)
	:Window{ xy,w,h,title },
	play_button{ Point{ 100,400 }, 75, 30, "PLAY AGAIN",cb_play },
	quit_button{ Point{ 300,400 }, 75, 30, "QUIT",cb_quit }

{
	top5.set_font_size(25);

	string scoreOutPut = name + " Your Score is " + to_string(score);

    Image Open{ Point{ 0,100 }, "OPEN.jpeg" };
    attach(Open);
    
	top5.set_label(scoreOutPut);

	NEW_score_easy = score;
	attach(top5);
	attach(play_button);
	attach(quit_button);

	scores = readScores("beginnerScore.txt");


	string finalVal = writeScores(scores, "beginnerScore.txt", name, NEW_score_easy);


	for (int i = 0; i < 5; i++) {
		string a = scores.at(i).getScoresandName();
		int value = i * 30;
		textEnd.push_back(new Text{ Point{ 320, 300 + value }, a });
	}



	sort(scores.begin(), scores.end(), compareScore);


	Fl::run();
	Fl::redraw();


}

void easy_scoresheetEnd::cb_play(Address, Address pw2)
{
	reference_to<easy_scoresheetEnd>(pw2).play();
}




void easy_scoresheetEnd::cb_quit(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<easy_scoresheetEnd>(pw2).quit();
}


void easy_scoresheetEnd::quit() {

	hide();
}


////////////////////////////////////////////////////////////////
// EASY LEVEL GAME ******************************************************
///////////////////////////////////////////////////////////////

struct moves_10 : Graph_lib::Window {
    Image Ghost{ Point{ 300,600 }, "ghost.jpg" };
    Image Door{ Point{ 500,100 }, "door.jpeg" };
    Image Crystal{ Point{ 100,0 }, "crystals.jpeg" };
	string description = "Moves Left: 10";
	moves_10(Point xy, int w, int h, const string& title);
	Rectangle border_rect{ Point{ 100,100 }, 400, 400 };
	Text moveAmount{ Point{ 100, 600 }, "TRY AND SOLVE THE GAME IN 10 MOVES!  " };
	Text moveCount{ Point{ 600,100 },  description };
	Text moveOrder{ Point{ 100,650 }, "The red tiles are not in the correct order" };

private:
	Button b01;
	Button b02;
	Button b03;
	Button b04;
	Button b05;
	Button b06;
	Button b12;
	Button b07;
	Button b09;
	Button b10;
	Button b15;
	Button b13;
	Button b14;
	Button b08;
	Button b11;
	Out_box outBox;
	Button Hint;

	int moves10_count = 10;

	void decrement_count();

	pair<int, int>BL = make_pair(300, 300);  ////MOVE
	pair<int, int> coordinates(string str);
	void move_button(string str);
	void MOVE(string str, pair<int, int>Change);

	void COLOR(string str); //COLOR
	void START_COLOR();

	int COUNTER(); //COUNTER
	int COUNTER2(string str);

	string Choice(); //MD
	vector<string>FIND();
	int MD(string option, pair<int, int>optionInfo);
	int Calc(pair<int, int> var1, pair<int, int>var2);

	static void cb_b12(Address, Address);
	void button_b12();

	static void cb_b11(Address, Address);
	void button_b11();

	static void cb_b13(Address, Address);
	void button_b13();

	static void cb_b15(Address, Address);
	void button_b15();

	static void cb_b14(Address, Address);
	void button_b14();

	static void cb_b10(Address, Address);
	void button_b10();

	static void cb_b09(Address, Address);
	void button_b09();

	static void cb_b03(Address, Address);
	void button_b03();

	static void cb_b07(Address, Address);
	void button_b07();

	static void cb_b06(Address, Address);
	void button_b06();

	static void cb_b02(Address, Address);
	void button_b02();

	static void cb_b04(Address, Address);
	void button_b04();

	static void cb_b08(Address, Address);
	void button_b08();

	static void cb_b05(Address, Address);
	void button_b05();

	static void cb_b01(Address, Address);
	void button_b01();

	static void cb_Hint(Address, Address);
	void button_Hint();

};


moves_10::moves_10(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	b01{ Point{ 100,100 }, 100, 100, "01",cb_b01 },
	b02{ Point{ 200,100 }, 100, 100, "02",cb_b02 },
	b03{ Point{ 300,100 }, 100, 100, "03",cb_b03 },
	b04{ Point{ 400,100 }, 100, 100, "04",cb_b04 },
	b05{ Point{ 100,200 }, 100, 100, "05",cb_b05 },
	b06{ Point{ 200,200 }, 100, 100, "06",cb_b06 },
	b12{ Point{ 300,200 }, 100, 100, "12",cb_b12 },
	b07{ Point{ 400,200 }, 100, 100, "07",cb_b07 },
	b09{ Point{ 100,300 }, 100, 100, "09",cb_b09 },
	b10{ Point{ 200,300 }, 100, 100, "10",cb_b10 },
	b15{ Point{ 400,300 }, 100, 100, "15",cb_b15 },
	b13{ Point{ 100,400 }, 100, 100, "13",cb_b13 },
	b14{ Point{ 200,400 }, 100, 100, "14",cb_b14 },
	b08{ Point{ 300,400 }, 100, 100, "08",cb_b08 },
	b11{ Point{ 400,400 }, 100, 100, "11",cb_b11 },
	outBox{ Point{ 370,0 }, 150, 40, "MOVE THIS BUTTON:" },
	Hint{ Point{ 100,0 }, 80, 100, "HINT" ,cb_Hint }

{
	border_rect.set_style(Line_style{ Line_style::solid, 2 });
	attach(border_rect);
	moveAmount.set_font_size(25);
	moveCount.set_font_size(20);
	moveOrder.set_font_size(25);
	attach(moveAmount);
	attach(b12);
	attach(b11);
	attach(b13);
	attach(b15);
	attach(b14);
	attach(b10);
	attach(b09);
	attach(b03);
	attach(b07);
	attach(b06);
	attach(b02);
	attach(b04);
	attach(b08);
	attach(b05);
	attach(b01);
	attach(outBox);
	attach(Hint);
	attach(moveOrder);
    attach(Crystal);
    attach(Door);

	attach(moveCount);

	START_COLOR();

	Fl::run();
	Fl::redraw();

}
////////////////////////////////////////////////COUNTER

int moves_10::COUNTER() {


	int C = 0;
	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };
	for (int i = 0; i<Labels.size(); ++i) {
		C = C + COUNTER2(Labels[i]);
	}
	return C;
}

int moves_10::COUNTER2(string str) {

	int C = 0;

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);
	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));


	int x;
	int y;

	Point var;

	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			var = Bs[i].loc;

			x = var.x; y = var.y;

			if (x == Final[i].first && y == Final[i].second) {
				C = C + 1;
			}
		}
	}


	return C;
}


////////////////////////////////////////////////BUTTON COLOR

void moves_10::START_COLOR() {


	vector<string>Labels = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15" };

	for (int i = 0; i<Labels.size(); ++i) {

		moves_10::COLOR(Labels[i]);

	}
	return;


}

void moves_10::COLOR(string str) {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);

	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);

	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));

	int x;

	int y;

	Point var;

	for (int i = 0; i<15; i++) {

		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x; y = var.y;

			if (x == Final[i].first && y == Final[i].second) {
				Bs[i].pw->color(Color::green);
			}
			else {
				Bs[i].pw->color(Color::red);
			}
		}
	}

	return;
}


//////////////////////////////////////////////////////////////////////MOVE FUNCTIONALITY


pair<int, int> moves_10::coordinates(string str) {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04); Bs.push_back(b05); Bs.push_back(b06);

	Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09); Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	int x; int y;

	Point var;

	for (int i = 0; i<15; i++) {

		if (str == Bs[i].label) {
			var = Bs[i].loc;
			x = var.x;
			y = var.y;
		}

	}
	pair<int, int>coordinate;

	coordinate = make_pair(x, y);

	return coordinate;
}


void moves_10::move_button(string str) {
	pair<int, int>Change;

	Change = make_pair(0, 0); //How much in each direction will the botton move?

	pair<int, int>Button = coordinates(str);

	if (Button.first + 100 == BL.first && Button.second == BL.second) { //checks to right

		Change.first = 100; Change.second = 0;

		BL.first = Button.first; BL.second = Button.second;
	}

	else if (Button.first - 100 == BL.first && Button.second == BL.second) { //checks left
		Change.first = -100; Change.second = 0;
		BL.first = Button.first; BL.second = Button.second;
	}

	else if (Button.first == BL.first && Button.second + 100 == BL.second) { //checks below
		Change.first = 0; Change.second = 100;
		BL.first = Button.first; BL.second = Button.second;
	}


	else if (Button.first == BL.first && Button.second - 100 == BL.second) { //checks above
		Change.first = 0; Change.second = -100;
		BL.first = Button.first; BL.second = Button.second;
	}

	else {  //If nothing matches, nothing happens

		Change.first = 0; Change.second = 0;
	}

	MOVE(str, Change); COLOR(str);

	return;
}

void moves_10::MOVE(string str, pair<int, int>Change) {

	Vector_ref<Button>Bs;  //Find way to condense this

	Bs.push_back(b01);
	Bs.push_back(b02);
	Bs.push_back(b03);
	Bs.push_back(b04);
	Bs.push_back(b05);
	Bs.push_back(b06);
	Bs.push_back(b07);
	Bs.push_back(b08);
	Bs.push_back(b09);
	Bs.push_back(b10);
	Bs.push_back(b11);
	Bs.push_back(b12);
	Bs.push_back(b13);
	Bs.push_back(b14);
	Bs.push_back(b15);

	for (int i = 0; i<15; i++) {
		if (str == Bs[i].label) {
			Bs[i].move(Change.first, Change.second);
		}
	}

	return;
}


/////////////////////////////////////////////////////////////////////////MOVE FUNCTIONALITY -END

void moves_10::decrement_count() {
	moves10_count--;
	description = "MOVES LEFT: " + to_string(moves10_count);
	moveCount.set_label(description);

	if (moves10_count == 0) {
		int NEW_SCORE = COUNTER() * 10;
		hide();
		easy_scoresheetEnd easyWindow(Point{ 300,300 }, 500, 500, "Game Results", NEW_SCORE, name);
	
		moveCount.set_label("GAME OVER");
		
	}

	redraw();

}

//////////////////////////////////////////////////////////////////////////MD


string moves_10::Choice() {

	vector<string>VEC = FIND();
	vector<int>results;

	for (int i = 0; i<VEC.size(); ++i) {
		results.push_back(MD(VEC[i], BL)); //Gives MD of each option and stores in vector of ints
	}

	int min = results[0];
	string choice = VEC[0];

	for (int c = 1; c<results.size(); ++c) {
		if (results[c] < min) {
			min = results[c]; choice = VEC[c];
		}

	}

	return choice;
}


//////////////////////////////////////////////////HINT

void moves_10::cb_Hint(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_Hint();
	reference_to<moves_10>(pw2).Choice();
}

void moves_10::button_Hint() {
	outBox.put(Choice());
}


vector<string> moves_10::FIND() {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);

	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	vector<string>FOUND; string INFO;

	Point var; int x; int y;

	for (int i = 0; i<Bs.size(); ++i) {

		var = Bs[i].loc; x = var.x; y = var.y;
		if (x + 100 == BL.first && y == BL.second) { //checks to right
			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x - 100 == BL.first && y == BL.second) { //checks left

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y + 100 == BL.second) { //checks below

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}

		else if (x == BL.first && y - 100 == BL.second) { //checks above

			INFO = Bs[i].label; FOUND.push_back(INFO);
		}
	}

	return FOUND;
}


int moves_10::MD(string option, pair<int, int>optionInfo) {

	Vector_ref<Button>Bs;  Bs.push_back(b01);  Bs.push_back(b02); Bs.push_back(b03); Bs.push_back(b04);
	Bs.push_back(b05); Bs.push_back(b06); Bs.push_back(b07); Bs.push_back(b08); Bs.push_back(b09);
	Bs.push_back(b10); Bs.push_back(b11); Bs.push_back(b12); Bs.push_back(b13); Bs.push_back(b14); Bs.push_back(b15);

	Vector<pair<int, int>>Final; Final.push_back(make_pair(100, 100)); Final.push_back(make_pair(200, 100));
	Final.push_back(make_pair(300, 100)); Final.push_back(make_pair(400, 100)); Final.push_back(make_pair(100, 200));
	Final.push_back(make_pair(200, 200)); Final.push_back(make_pair(300, 200)); Final.push_back(make_pair(400, 200));
	Final.push_back(make_pair(100, 300)); Final.push_back(make_pair(200, 300)); Final.push_back(make_pair(300, 300));
	Final.push_back(make_pair(400, 300)); Final.push_back(make_pair(100, 400)); Final.push_back(make_pair(200, 400));
	Final.push_back(make_pair(300, 400)); Final.push_back(make_pair(400, 400));

	int sum = 0; Point point; pair<int, int>var1; pair<int, int>var2;

	for (int i = 0; i<Bs.size(); ++i) {

		point = Bs[i].loc; var1 = make_pair(point.x, point.y); var2 = make_pair(Final[i].first, Final[i].second);

		if (option == Bs[i].label) {

			sum = sum + Calc(optionInfo, var2);
		}

		else {

			sum = sum + Calc(var1, var2);
		}
	}

	return sum;
}

int moves_10::Calc(pair<int, int> var1, pair<int, int>var2) {

	int part1 = abs(var2.first - var1.first);
	int part2 = abs(var2.second - var1.second);
	int ans = part1 + part2;
	return ans;
}

void moves_10::cb_b01(Address, Address pw2)

{
	reference_to<moves_10>(pw2).button_b01();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("01");
}

void moves_10::button_b01() {
}

void moves_10::cb_b05(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b05();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("05");
}

void moves_10::button_b05() {

}

void moves_10::cb_b08(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b08();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("08");
}

void moves_10::button_b08() {

}

void moves_10::cb_b04(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b04();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("04");
}

void moves_10::button_b04() {

}

void moves_10::cb_b02(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b02();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("02");
}

void moves_10::button_b02() {

}

void moves_10::cb_b06(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b06();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("06");

}

void moves_10::button_b06() {

}

void moves_10::cb_b07(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b07();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("07");
}

void moves_10::button_b07() {

}


void moves_10::cb_b03(Address, Address pw2)

{
	reference_to<moves_10>(pw2).button_b03();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("03");
}

void moves_10::button_b03() {

}

void moves_10::cb_b09(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b09();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("09");
}

void moves_10::button_b09() {
}
void moves_10::cb_b10(Address, Address pw2)

{
	reference_to<moves_10>(pw2).button_b10();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("10");
}


void moves_10::button_b10() {

}


void moves_10::cb_b14(Address, Address pw2)

{
	reference_to<moves_10>(pw2).button_b14();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("14");
}


void moves_10::button_b14() {

}

void moves_10::cb_b15(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b15();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("15");
}

void moves_10::button_b15() {

}

void moves_10::cb_b13(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b13();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("13");
}

void moves_10::button_b13() {
}

void moves_10::cb_b11(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b11();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("11");
}

void moves_10::button_b11() {

}
void moves_10::cb_b12(Address, Address pw2)
{
	reference_to<moves_10>(pw2).button_b12();
	reference_to<moves_10>(pw2).decrement_count();
	reference_to<moves_10>(pw2).move_button("12");
}

void moves_10::button_b12() {

}
///////////////////////////////////////////////
// DIFFUCULTY LEVEL BUTTON************************
//////////////////////////////////////////////

struct difficultyLevel : Graph_lib::Window {
	difficultyLevel(Point xy, int w, int h, const string& title);

private:
	Button beginner;
	Button intermediate;
	Button advanced;
	Button expert;

	static void cb_beginner(Address, Address);
	void beginner_button();
	static void cb_intermediate(Address, Address);
	void intermediate_button();

	static void cb_advanced(Address, Address);
	void advanced_button();

	static void cb_expert(Address, Address);
	void expert_button();


};

difficultyLevel::difficultyLevel(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	beginner{ Point{ 200,200 }, 300, 80, "PAGE",cb_beginner },
	intermediate{ Point{ 200,300 }, 300, 80, "SQUIRE",cb_intermediate },
	advanced{ Point{ 200,400 }, 300, 80, "KNIGHT",cb_advanced },
	expert{ Point{ 200,500 }, 300, 80, "CHAMPION",cb_expert }
{
	//  b.set_fill();
	attach(beginner);
	attach(intermediate);
	attach(advanced);
	attach(expert);
	Fl::run();
	Fl::redraw();
}

void difficultyLevel::cb_expert(Address, Address pw2)
{
	reference_to<difficultyLevel>(pw2).expert_button();
}


void difficultyLevel::cb_advanced(Address, Address pw2)
{
	reference_to<difficultyLevel>(pw2).advanced_button();
}


void difficultyLevel::cb_intermediate(Address, Address pw2)
{
	reference_to<difficultyLevel>(pw2).intermediate_button();
}


void difficultyLevel::cb_beginner(Address, Address pw2)
// call Simple_window::next() for the window located at pw
{
	reference_to<difficultyLevel>(pw2).beginner_button();
}


void difficultyLevel::expert_button() {
	hide();
	expert_scoresheet window4{ Point{ 100,100 },600,600,"Expert Score sheet" };
	moves_80 win6{ Point{ 50,50 },800,800,"CHAMPION" };
}

void difficultyLevel::advanced_button() {
	hide();
	advanced_scoresheet window3{ Point{ 100,100 },600,600,"Advanced Score sheet" };
	moves_40 win5{ Point{ 50,50 },800,800,"KNIGHT" };
}


void difficultyLevel::intermediate_button() {
	hide();
	intermediate_scoresheet window2{ Point{ 10,10 },600,600,"Intermediate Score sheet" };
	moves_20 win4{ Point{ 50,50 },800,800,"SQUIRE" };
}


void difficultyLevel::beginner_button() {
	hide();


	easy_scoresheet window1{ Point{ 200,10 },600,600,"Beginner Score sheet" };
	moves_10 win3{ Point{ 50,50 },800,800,"PAGE" };


}

////////////////////////////////////// Difficulty LEVEL CALL FOR EXPERT GAME 
//************************************************************************

void expert_scoresheetEnd::play() {
	hide();
	difficultyLevel win2{ Point{ 50,50 },800,800,"game instructions" };

}


////////////////////////////////////// Difficulty LEVEL CALL FOR ADVANCED GAME 
//************************************************************************

void advanced_scoresheetEnd::play() {
	hide();
	difficultyLevel win2{ Point{ 50,50 },800,800,"game instructions" };
}


////////////////////////////////////// Difficulty LEVEL CALL FOR INTERMEDIATE GAME 
//************************************************************************

void intermediate_scoresheetEnd::play() {
	hide();
	difficultyLevel win2{ Point{ 50,50 },800,800,"game instructions" };
}


////////////////////////////////////// Difficulty LEVEL CALL FOR EASY GAME 
//************************************************************************

void easy_scoresheetEnd::play() {
	hide();
	difficultyLevel win2{ Point{ 50,50 },800,800,"game instructions" };
}

/////////////////////////////////////////
//GAME INFO SCREEN****************************
/////////////////////////////////////////


struct gameInfo : Graph_lib::Window {
	gameInfo(Point xy, int w, int h, const string& title);
	Image Scroll{ Point{ 0,0 }, "Scroll3.jpg" };
	Text item1{ Point{ 46, 150 }, "An evil sorceror has cast a spell over the castle, trapping the King inside!" };
	Text item2{ Point{ 46, 180 }, "It is up to you to save him and the kingdom by traversing through the" };
	Text item3{ Point{ 46, 210 }, "castle's secret passage ways and avoiding the monsters that now roam" };
	Text item4{ Point{ 46, 240 }, "within. To do this, you must solve puzzles to unlock each secret passage." };
	Text item5{ Point{ 46, 270 }, "You must arrange each puzzle so the numbers 1-15 are in order." };
	Text item6{ Point{ 46, 300 }, "Remember that some puzzles are harder than others and take more" };
	Text item7{ Point{ 46, 330 }, "time to complete. Do not take too long however, or the creatures that" };
	Text item8{ Point{ 46, 360 }, "now haunt the castle halls will catch up to you sooner rather than later..." };
	Text item9{ Point{ 46, 420 }, "Click on a number to move it to the blank spot above, below or to the" };
	Text item10{ Point{ 46, 450 }, "left or right. Numbers cannot move diagonally. Numbers cannot switch" };
	Text item11{ Point{ 46, 480 }, "spots with other numbers. Keep an eye on how many moves you have" };
	Text item12{ Point{ 46, 510 }, "left available before a monster gets you and it is Game Over. If you" };
	Text item13{ Point{ 46, 540 }, " need help, click on the crystal ball (hint button). GOOD LUCK HEROES!" };
	Text item14{ Point{ 46, 570 }, "~Court Wizards" };


	Image Me{ Point{ 46, 590 }, "Me4.jpg" };
    
    Image Enrique{ Point{ 250, 550 }, "Enrique.jpeg" };
    Image Ledet{ Point{ 450, 550 }, "Ledet.jpeg" };
private:
	Button next;
	static void cb_next1(Address, Address);       // callback for next_button


	void next1();  // action to be done when next_button is pressed
};
gameInfo::gameInfo(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next{ Point{ x_max() - 100,10 }, 70, 30, "NEXT",cb_next1 }
{
	item1.set_font_size(20);
	item2.set_font_size(20);
	item3.set_font_size(20);
	item4.set_font_size(20);
	item5.set_font_size(20);
	item6.set_font_size(20);
	item7.set_font_size(20);
	item8.set_font_size(20);
	item9.set_font_size(20);
	item10.set_font_size(20);
	item11.set_font_size(20);
	item12.set_font_size(20);
	item13.set_font_size(20);
	item14.set_font_size(20);
	attach(Scroll);
	attach(item1);
	attach(item2);
	attach(item3);
	attach(item4);
	attach(item5);
	attach(item6);
	attach(item7);
	attach(item8);
	attach(item9);
	attach(item10);
	attach(item11);
	attach(item12);
	attach(item13);
	attach(item14);
	attach(Me);
	attach(next);
    attach(Enrique);
    attach(Ledet);


	Fl::run();
	Fl::redraw();
}

void gameInfo::cb_next1(Address, Address pw2)
{
	reference_to<gameInfo>(pw2).next1();
}


void gameInfo::next1() {
	hide();
	difficultyLevel win2{ Point{ 50,50 },800,800,"game instructions" };
}

/////////////////////////////////////////////////////////////////
// SPLASH SCREEN BELOW *****************************************
/////////////////////////////////////////////////////////////////

struct splashScreen : Graph_lib::Window {
	splashScreen(Point xy, int w, int h, const string& title);
	Text gameTitle{ Point{ 150, 100 }, "15 puzzles to save the Kingdom" };
	Text teamInfo{ Point{ 20, 140 }, "By team #42: Ledet Awano, Enrique Baqueiro & Kristen Arias " };
	Image castle{ Point{ 0,0 }, "Start.jpg" };

private:
	Button start;
	bool button_pushed;
	static void cb_start(Address, Address);       // callback for next_button
	void start1();  // action to be done when next_button is pressed
};


splashScreen::splashScreen(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	start{ Point{ 290, 550 }, 300, 280, "start",cb_start },
	button_pushed{ false }
{
	gameTitle.set_font_size(35);
	teamInfo.set_font_size(25);
	attach(castle);
	attach(gameTitle);
	attach(teamInfo);
	attach(start);
}

void splashScreen::cb_start(Address, Address pw)
// call Simple_window::next() for the window located at pw
{
	reference_to<splashScreen>(pw).start1();
}


void splashScreen::start1() {
	hide();
	gameInfo win1{ Point{ 50,50 },800,800,"game instructions" };
}


int main()
{
	try {
		splashScreen win{ Point{ 50,50 },800,750,"Project" };
		//PlaySound("song.mp3", NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);   ((For the background music))

		return gui_main();
	}
	catch (exception& e) { //catches range errors and run_time_errors
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) { //catch any exception
		cerr << "Exception: something went wrong \n";
		return 2;
	}
}
