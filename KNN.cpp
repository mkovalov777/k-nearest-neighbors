#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

struct listParameters {
	int width;
	int height;
	listParameters(int height, double width)
	{
		this->height = height;
		this->width = width;
	}
};

struct distanceToClasses
{
	int clNum;
	int distanceDifference;
	distanceToClasses(int id, int Difference)
	{
		clNum = id;
		distanceDifference = Difference;
	}
};

bool fForSort(distanceToClasses elem1, distanceToClasses elem2) {
	return elem1.distanceDifference < elem2.distanceDifference;
}

map<int, vector<listParameters>> objectsWithClasses;
vector<listParameters> objectsToClassify;
vector<int> output;

int main() {
	int N, K, M, h, w;
	cin >> N >> K >> M;
	for (int i = 1; i < N + 1; i++) {
		vector<listParameters> inputVector;
		cin >> w >> h;
		inputVector.push_back(listParameters(h, w));
		objectsWithClasses.insert({ i, inputVector });
	}

	for (int i = 0; i < M; i++) {
		cin >> w >> h;
		objectsToClassify.push_back(listParameters(h, w));
		output.push_back(0);
	}

	int k1 = 0, n1 = N,max = 0,maxNum = 0,clNum = 0;
	vector<listParameters> objectToCompareWith;
	vector<distanceToClasses> differencesAndIDs;
	vector<int> maxClosestsForEachClass(N + 1);
	for (int i = 0; i < M; i++) {
		if (K > n1) 
			k1 = n1;
		else 
			k1 = K;
		k1--;
		for (int i1 = 0; i1 < maxClosestsForEachClass.size(); i1++) {
			maxClosestsForEachClass[i1] = 0;
		}
		differencesAndIDs.clear();
		maxNum = 0;
		for (int j = 1; j <= objectsWithClasses.size(); j++) {
			objectToCompareWith = objectsWithClasses.find(j)->second;
			for (int t = 0; t < objectToCompareWith.size(); t++)
			{
				if (abs(objectsToClassify[i].height - objectToCompareWith[t].height) > fabs(objectsToClassify[i].width - objectToCompareWith[t].width))
				{
					max = abs(objectsToClassify[i].height - objectToCompareWith[t].height);
				}
				else
				{
					max=abs(objectsToClassify[i].width - objectToCompareWith[t].width);
				}
				differencesAndIDs.push_back(distanceToClasses(j, max));
			}
		}
		sort(differencesAndIDs.begin(), differencesAndIDs.end(), fForSort);
		while (k1 + 2 < differencesAndIDs.size() && differencesAndIDs[k1].distanceDifference == differencesAndIDs[k1 + 1].distanceDifference) {
			k1++;
		}
		for (int i1 = 0; i1 <= k1; i1++) {
			int id = differencesAndIDs[i1].clNum;
			maxClosestsForEachClass[id]++;
		}
		for (int i1 = N; i1 > 0; i1--) {
			if (maxClosestsForEachClass[i1] >= maxNum) {
				maxNum = maxClosestsForEachClass[i1];
				clNum = i1;
			}
		}
		n1++;
		objectsWithClasses.find(clNum)->second.push_back(objectsToClassify[i]);
		output[i] = clNum;
	}

	for (int i = 0; i < M; i++) {
		cout << output[i] << " ";
	}
	system("pause");
	return 0;
}