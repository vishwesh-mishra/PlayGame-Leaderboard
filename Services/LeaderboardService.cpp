#include "LeaderboardService.h"

void LeaderboardService::insertUserScore(int userId, int score) {
	list<pii>::iterator it;
	it = userAndScore.begin();
	while (it != userAndScore.end() && it->second >= score)
		it++;
	userAndScore.insert(it, { userId, score });
	--it;
	userScoreMap[userId] = it;
}

void LeaderboardService::play(int userId, int score, int timeStamp) {
	if (userScoreMap.find(userId) == userScoreMap.end()) {
		insertUserScore(userId, score);
	}
	else {
		if (score > userScoreMap[userId]->second) {
			list<pii>::iterator eraseIt;
			eraseIt = userScoreMap[userId];
			eraseIt = userAndScore.erase(eraseIt);
			insertUserScore(userId, score);
		}
	}
}

vector<pii> LeaderboardService::topNLeaderboard(int n) {
	vector<pii> topN;
	list<pii>::iterator it = userAndScore.begin();
	int i = 0;
	while (i < n  && it != userAndScore.end()) {
		topN.push_back({ it->first, it->second });
		it++;
		i++;
	}

	return topN;
}

vector<pii> LeaderboardService::localLeaderboard(int userId, int n) {
	vector<pii> localN;
	list<pii>::iterator it;

	if (userScoreMap.find(userId) == userScoreMap.end()) return localN;

	it = userScoreMap[userId];

	// Storing left part along with user as below
	int i = 0;
	while (i <= n) {
		localN.push_back({ it->first,it->second });
		it--;
		i++;
		if (i < n && it == userAndScore.begin()) {
			localN.push_back({ it->first,it->second });
			break;
		}
	}

	reverse(localN.begin(), localN.end()); // since left part has been stored in reverse order


	// Storing right part of user as below
	it = userScoreMap[userId];
	it++;

	i = 0;
	while (it != userAndScore.end() && i < n) {
		localN.push_back({ it->first,it->second });
		it++;
		i++;
	}

	return localN;
}