#include <bits/stdc++.h>
using namespace std;

// max number of vertices (I am lazy)
const int N = 32;


void addIfGraceful(map<int, set<int>> & tree, int n, set<set<set<int>>> & gLabels)
{	
	int i, vertexA;
	bool graceful;

	//int label[n]; // [0,|E(tree)|] => [0,n-1]
	bool diff[n]; // [1, n-1], so disregard diff[0]
	
	// reset diff
	// TODO optimize
	for (i=0; i < n; i++)
		diff[i] = false;

	// traverse tree
	graceful = true;
	for (auto pair : tree)
	{
		vertexA = pair.first;
		for (auto vertexB : pair.second)
		{
			if (diff[vertexB - vertexA])
			{
				graceful = false;
				break;
			}
			diff[vertexB - vertexA] = true;
		}
		if (!graceful)
			break;
	}

	if (graceful)
	{
		set<set<int>> gLabel;
		for (auto pair : tree)
		{
			vertexA = pair.first;
			for (auto vertexB : pair.second)
			{
				set<int> pair;
				pair.insert(vertexA);
				pair.insert(vertexB);
				gLabel.insert(move(pair));
			}
		}
		gLabels.insert(move(gLabel));
	}
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

		// count graceful tree
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
void treeFromPruefer(map<int, set<int>> & tree, int n, int pruefer[])
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
				if (pruefer[i] > j)
					tree[j].insert(pruefer[i]);
				else
					tree[pruefer[i]].insert(j);
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
				tree[last].insert(j);
				break;
			}
		}
	}
}

// O(n * n**n)
bool permutePruefer(int *pruefer, int n)
{
	int num, i;
	bool last;

	// print pruefer
	/*
	for (i=0; i < n-2; i++)
		cout << setw(2) << pruefer[i] << " ";
	cout << endl;
	*/

	// convert pruefer into single int
	num = 0;
	for (i=0; i < n-2; i++)
		num += pruefer[i] * pow(n,i);

	// check if input is last permutation
	last = true;
	for (i=0; i < n-2; i++)
		if (pruefer[i] != n-1)
		{
			last = false;
			break;
		}
	if (last)
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
	int n;
	set<set<set<int>>> gLabels;
	
	// user gives number of vertices (n)
	if (argc != 2)
	{
		cout << "please enter number of vertices" << endl;
		exit(1);
	}
	n = atoi(argv[1]); // len pruefer + 2; must be less/equal to N
	
	int pruefer[n-2] = {0};
	do
	{
		map<int, set<int>> tree;	
		treeFromPruefer(tree, n, pruefer);
		addIfGraceful(tree, n, gLabels);
	}
	while (permutePruefer(pruefer, n));

	cout << "num vertices: " << n << endl;
	cout << "num labelled trees:    " << pow(n, n-2) << endl;
	cout << "num g-labels: " << gLabels.size() << endl;

	return 0;
}
