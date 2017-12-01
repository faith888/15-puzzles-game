#include "std_lib_facilities_5.h"
#include <algorithm>

struct Scores {
	string person_name;
	int score;

	Scores();
	Scores(string s, int i);
	void SetStr(string x);
	string getName();
	void SetScore(int y);
	string getScoresandName();
};


Scores::Scores() {
	person_name;
	score;
	return;
}

string Scores::getName() {
	return person_name;
}

Scores::Scores(string s, int i) {
	person_name = s;
	score = i;
}

string Scores::getScoresandName() {
	string score1 = to_string(score);
	string name_and_score = person_name + " " + score1;
	return name_and_score;
}

void Scores::SetStr(string x) {
	person_name = x;

}

void Scores::SetScore(int y) {
	score = y;

}


ostream& operator<<(ostream& strm, Scores z) {
	strm << z.person_name << " " << z.score << endl;
	return strm;
}

bool compareScore(Scores a, Scores b) {
	int numValue1 = a.score;
	int numValue2 = b.score;

	return numValue1 > numValue2;
}



vector<Scores> readScores(string fileName)
{

	ifstream file{ fileName };
	string name;
	string num;
	int num1;
	stringstream ss;
	vector<Scores> s;
	while (!file.eof()) {

		getline(file, name, ' ');
		getline(file, num, '\n');
		ss.clear();
		ss << num;
		ss >> num1;
		Scores score(name, num1);
		sort(s.begin(), s.end(), compareScore);
		s.push_back(score);

	}
	file.close();
	return s;
}

//writes scores to file 


string writeScores(vector<Scores>& s, String i, string name)
{
	ofstream file(i);

	for (int i = 0; i < s.size(); i++) {
	
		file << s[i].person_name << " " << s[i].score << '\n';

	}

	file << name << " " << 0 ;
	Scores new_score(name, 0);
	s.push_back(new_score);


	file.close();
	string final = s[s.size() - 1].person_name + " " + to_string(s[s.size() - 1].score);
	return final;
	
}

string writeScores(vector<Scores>& s, String i, string name, int ns)
{
	ofstream file(i);

	//loop writes intials to vector in this format

	for (int i = 0; i < s.size(); i++) {
			file << s[i].person_name << " " << s[i].score << '\n';
	
	}


	file << name << " " << ns ;
	Scores new_score(name, ns);
	new_score.SetScore(ns);
	s.push_back(new_score);


	file.close();
	string final = s[s.size() - 1].person_name + " " + to_string(s[s.size() - 1].score);
	return final;

}





 
 