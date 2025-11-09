#include <bits/stdc++.h>
using namespace std;

int main()
{
	int i, j, n, labellings;
	bool graceful;

	n = 6; // number of vertices
	
	int label[n]; // [0,|E(tree)|] => [0,n-1]
	bool diff[n]; // [1, n-1], so disregard diff[0]
	bool tree[n][n];

	// initialize label
	for (i=0; i < n; i++)
		label[i] = i;

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

	cout << "# labellings: " << labellings << endl;

	return 0;
}
