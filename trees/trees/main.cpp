#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"
#include <string>

using namespace std;

int main()
{
	for (int ii = 0; ii < 100; ii++)
	{
		AVLTree<int> tree;

		srand(time(NULL));

		for (unsigned int i = 0; i < 1000; i++)
		{
			unsigned int randomNumber = rand() % 1000;
			tree.insert(randomNumber);
			if (tree.find(randomNumber) == false)
			{
				throw "number inserted is not found";
			}
		}

		vector<int> data = tree.getData();
		for (int i = 0; i < data.size(); i++)
		{
			if (i < (data.size() - 1))
			{
				if (data[i] > data[i + 1])
				{
					throw "number is not orderd";
				}
				printf("%d ", data[i]);
			}
		}
		printf("\n\n");

	}

	return 0;
}