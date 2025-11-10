#include <bits/stdc++.h>
using namespace std;

// max number of vertices
const int N = 999;




struct Tree
{
	bool arr[N][N];
	int size;
};


// TODO
// given two trees, a and b, are they isomorphic?
bool areIsomorphic(bool a[N][N], bool b[N][N])
{
	return false;
}

// generates every possible tree on n vertices
void generateTrees(int n)
{

}

// return the number of possible labellings for a given tree
int numLabellings(bool tree[N][N], int n)
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

// i've elected for the code to range from [0,n-1] rather than [1,n]
void treeFromPruefer(bool tree[N][N], int n, int pruefer[])
{
	int i, j, k, last;
	int considered;
	bool valid;

	bool label[n];
	for (i=0; i < n; i++)
		label[i] = true;

	// loop through sequence
	for (i=0; i < n-2; i++)
	{
		// loop through potential labels
		for (j=0; j < n; j++)
		{
			if (!label[j])
				continue;

			// check if label is not in remaining sequence
			valid = true;
			for (k=i+1; k < n-2; k++)
			{
				if (j == pruefer[k])
				{
					valid = false;
					break;
				}
			}
			if (valid)
			{
				//cout << pruefer[i] << "-" << j << " ";
				if (pruefer[i] > j)
					tree[j][pruefer[i]] = true;
				else
					tree[pruefer[i]][j] = true;
				label[j] = false;
				break;
			}
		}
	}

	// pair last two labels
	last = -1;
	for (j=0; j < n; j++)
	{
		if (label[j])
		{
			if (last == -1)
				last = j;
			else
			{
				//cout << last << "-" << j;
				tree[last][j] = true;
				break;
			}
		}
	}
}

void printTree(bool tree[N][N], int n)
{
	int i, j;

	cout << "   ";
	for(j=0; j < n; j++)
		cout << setw(3) << j;
	cout << endl;

	cout << "   ";
	for(j=0; j < n; j++)
		cout << "---";
	cout << endl;

	for (i=0; i < n; i++)
	{
		cout << setw(2) << i << '|';
		for (j=0; j < n; j++)
		{
			if (tree[i][j])
				cout << setw(3) << "X";
			else
				cout << setw(3) << " ";
		}
		cout << endl;
	}
}


int main()
{
	int i, j, n;

	/*
	n = 6; // number of vertices, must be less/equal to N

	bool tree[N][N];

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
	*/


	n = 6; // len pruefer + 2
	int pruefer[] = {3,3,3,4}; 

	bool tree[N][N];
	treeFromPruefer(tree, n, pruefer);

	printTree(tree, n);

	// loop through every permutation
	//cout << "# labellings: " << numLabellings(tree, n) << endl;

	return 0;
}
