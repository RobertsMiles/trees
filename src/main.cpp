#include <bits/stdc++.h>
using namespace std;

// given two trees, a, and b, are they isomorphic?
bool areIsomorphic(bool **a, bool **b)
{
	return false;
}

// return the number of possible labellings for a given tree
int numLabellings(bool **tree, int n)
{
	int labellings, i, j;
	bool graceful;
		
	int label[n]; // [0,|E(tree)|] => [0,n-1]
	bool diff[n]; // [1, n-1], so disregard diff[0]
	
	// initialize label
	for (i=0; i < n; i++)
		label[i] = i;
	
	labellings = 0;
	do
	{
		// print label
		/*
		for (i=0; i < n; i++)
			cout << label[i] << " ";
		cout << endl;
		*/

		// reset diff
		for (i=0; i < n; i++)
			diff[i] = false;

		// traverse tree
		graceful = true;
		for (i=0; i < n; i++) 
		{
			for (j=0; j < n; j++)
			{
				if (tree[i][j])
				{
					if (diff[abs(label[i]-label[j])])
					{
						graceful = false;
						break;
					}
					diff[abs(label[i]-label[j])] = true;
				}
			}
			if (!graceful)
				break;
		}

		if (graceful)
			labellings++;

		// print graceful tree
		/*
		if (graceful)
		{
			for (i=0; i < n; i++)
			{
				for (j=0; j < n; j++)
				{
					if (tree[i][j])
						cout << label[i] << "--" << label[j] << " ";	
				}
			}
			cout << endl;
		}
		*/
	}
	while (next_permutation(label, label+n));

	return labellings;
}

int main()
{
	int i, j, n;

	n = 6; // number of vertices

	bool tree[n][n];



	// initialize tree
	// [lower][higher]
	for (i=0; i < n; i++)
		for (j=0; j < n; j++)
			tree[i][j] = false;
	tree[0][3] = true;
	tree[1][3] = true;
	tree[2][3] = true;
	tree[3][4] = true;
	tree[4][5] = true;

	// loop through every permutation
	cout << "# labellings: " << numLabellings(tree, n) << endl;
	
	return 0;
}
