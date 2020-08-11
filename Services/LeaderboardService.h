#pragma once
#include<list>
#include<map>
#include<vector>

using namespace std;

typedef pair<int, int> pii;

class LeaderboardService {
public:
	list<pii> userAndScore;
	map<int, list<pii>::iterator> userScoreMap;

	void play(int userId, int score, int timeStamp);
	void insertUserScore(int userId, int score);
	vector<pii> topNLeaderboard(int n);
	vector<pii> localLeaderboard(int userId, int n);
};