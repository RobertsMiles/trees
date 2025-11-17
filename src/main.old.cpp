#include <bits/stdc++.h>
using namespace std;

// max number of vertices (lazy)
const int N = 999;


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

void generateLabels(bool tree[N][N], int n, set<set<set<int>>> &gLabels)
{
	int numLabels, i, j;
	bool graceful;

	int label[n]; // [0,|E(tree)|] => [0,n-1]
	bool diff[n]; // [1, n-1], so disregard diff[0]
	
	// initialize label
	for (i=0; i < n; i++)
		label[i] = i;
	
	numLabels = 0;
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
			numLabels++;

		// print graceful tree
		if (graceful)
		{
			set<set<int>> gLabel;
			//cout << "    ";
			for (i=0; i < n; i++)
			{
				for (j=0; j < n; j++)
				{
					if (tree[i][j])
					{
						//cout << label[i] << "-" << label[j] << " ";	
						set<int> pair;
						pair.insert(label[i]);
						pair.insert(label[j]);
						gLabel.insert(move(pair));
					}
				}
			}
			//cout << endl;
			gLabels.insert(move(gLabel));
		}
	}
	while (next_permutation(label, label+n));

	// I highly doubt I have disproved an unsolved conjecture in graph theory,
	// this should never happen
	if (!numLabels)
	{
		cout << "WARNING, SOMETHING WRONG!!!" << endl;
		exit(2);
	}
}

// i've elected for the code to range from [0,n-1] rather than [1,n]
void treeFromPruefer(bool tree[N][N], int n, int pruefer[])
{
	int i, j, k, last;
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
			if (!label[j] || j==pruefer[i])
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
				//cout << pruefer[i]+1 << "-" << j+1 << " ";
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
				//cout << last+1 << "-" << j+1;
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

bool permutePruefer(int *pruefer, int n)
{
	int maxNum, num, i;

	/*
	// print pruefer
	for (i=0; i < n-2; i++)
		cout << pruefer[i] << " ";
	cout << endl;
	*/

	// convert pruefer into single int
	num = 0;
	for (i=0; i < n-2; i++)
		num += pruefer[i] * pow(n,i);

	// check if input is last permutation
	maxNum = 0;
	for (i=0; i < n-2; i++)
		maxNum += (n-1) * pow(n,i);
	if (num >= maxNum)
		return false;

	// incriment int
	num++;

	// convert new int back into pruefer
	for (i=0; i < n-2; i++)
	{
		pruefer[i] = num % n;
		num /= n;
	}

	return true;
}


int main(int argc, char **argv)
{
	int i, j, n;
	bool newPruefer;


	if (argc != 2)
	{
		cout << "please enter number of vertices" << endl;
		exit(1);
	}
	n = atoi(argv[1]); // len pruefer + 2; must be less/equal to N
	//int pruefer[] = {0,1,0,2,2,4}; // [0,n-1]
	int pruefer[n-2] = {0};// = {0,1,0,2,2,4};
	
	set<set<set<int>>> gLabels;

	newPruefer = true;
	while(newPruefer)
	{
		bool tree[N][N];
		for (i=0; i < n; i++)
			for (j=0; j < n; j++)
				tree[i][j] = false;

		treeFromPruefer(tree, n, pruefer);

		/*
		for (i=0; i < n-2; i++)
			cout << pruefer[i] << " ";
		cout << "  ";
		for (i=0; i < n; i++)
			for (j=0; j < n; j++)
			{
				if (tree[i][j])
					cout << i << "-" << j << " ";
			}
		*/
		//cout << "  ";
		//cout << "g-labels: " << generateLabels(tree, n) << endl;
		//cout << endl;
		generateLabels(tree, n, gLabels);
		//cout << endl << endl;

		newPruefer = permutePruefer(pruefer, n);
	}

	/*
	cout << "g-labels: " << endl;
	for (auto gLabel : gLabels)
	{
		for (auto edge : gLabel)
		{
			for (auto vertex : edge)
				cout << vertex << " ";
			cout << "    ";
		}
		cout << endl;
	}
	cout << endl;
	*/

	cout << "num vertices: " << n << endl;
	cout << "num trees:    " << pow(n, n-2) << endl;
	cout << "num g-labels: " << gLabels.size() << endl;
	
	return 0;
}
