#include "ScoreList.h"

ScoreList::ScoreList() {     // Create an empty score list.
	m_scoreList;
}

bool ScoreList::add(unsigned long score) {
	// If the score is valid (a value from 0 to 100) and the score list
	// has room for it, add it to the score list and return true.
	// Otherwise, leave the score list unchanged and return false.

	if (score < 0 || score > 100)
		return false;
	return (m_scoreList.insert(m_scoreList.size(), score));
}

bool ScoreList::remove(unsigned long score) {
	// Remove one instance of the specified score from the score list.
	// Return true if a score was removed; otherwise false.

	int position;
	position = m_scoreList.find(score);
	return m_scoreList.erase(position);
}

int ScoreList::size() const {  // Return the number of scores in the list.
	return m_scoreList.size();
}

unsigned long ScoreList::minimum() const {
	// Return the lowest score in the score list.  If the list is
	// empty, return NO_SCORE.

	if (m_scoreList.empty())
		return NO_SCORE;
	ItemType min;
	m_scoreList.get(0, min);
	for (int i = 1; i < m_scoreList.size(); i++) {
		ItemType temp;
		m_scoreList.get(i, temp);
		if (min > temp)
			min = temp;
	}
	return min;
}

unsigned long ScoreList::maximum() const {
	// Return the highest score in the score list.  If the list is
	// empty, return NO_SCORE.

	if (m_scoreList.empty())
		return NO_SCORE;
	ItemType max;
	m_scoreList.get(0, max);
	for (int i = 1; i < m_scoreList.size(); i++) {
		ItemType temp;
		m_scoreList.get(i, temp);
		if (max < temp)
			max = temp;
	}
	return max;
}