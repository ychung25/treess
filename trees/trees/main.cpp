#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"

int main()
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

        for (int i = 0; i < data.size(); i++)
        {
            tree.erase(data[i]);
        }




        printf("size after removval = %d\n", tree.size());


	return 0;
}