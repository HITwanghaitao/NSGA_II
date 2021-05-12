#include "nsga_II.h"

void NSGA::Initialization()
{
	Population.resize(N);
	for (int j = 0; j < N; j++)
	{
		Population[j].flag = j;
		Population[j].X[0] = j;
		Population[j].X[1] = j+1;

		Population[j].Y = function(Population[j].X);
	}
	cout << "初始化完成" << endl;
}
void NSGA::Sort() //fsat-non_dominated-sort
{
	vector<double> F1;
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < N; k++)
		{
			if (j != k)
			{
				if (compare(Population[j], Population[k]) == true)
				{
					Population[j].S.push_back(k);
				}
				else
				{
					Population[j].np += 1;
				}
			}
		}
		//cout << "j=" << j << ";np=" << Population[j].np << endl;
		if (Population[j].np == 0)
		{
			F1.push_back(j);
			cout << "出现支配解" << endl;
		}
			
	}
	F.push_back(F1);
	//cout << "sort1完成" << endl;

	int i = 0;
	while (F[i].size() != 0)	
	{
		vector<double> Q;
		Node temp;
		for (int j = 0; j < F[i].size(); j++)
		{
			temp = Population[F[i][j]];
			for (int k = 0; k < temp.S.size(); k++)
			{
				Population[temp.S[k]].np -= 1;
				//cout << temp.S[k] << endl;
				if (Population[temp.S[k]].np == 0)
				{
					Q.push_back(temp.S[k]);
				}
			}
		}
		i = i + 1;
		//cout << "paleituo " << i << " over" << endl;
		F.push_back(Q);
	}
	cout << "共有" << F.size()-1 << "层帕累托前沿" << endl;
	//cout << "sort2完成" << endl;
	for (int j = 0; j < F.size()-1; j++)
	{
		cout << "第" << j + 1 << "层:";
		for (int k = 0; k < F[j].size(); k++)
		{
			cout << F[j][k] << " ";
		}
		cout << endl;
	}
}
bool NSGA::compare(Node node1, Node node2)
{
	bool flag = true;
	for (int j = 0; j < node1.Y.size(); j++)
	{
		if (node1.Y[j] > node2.Y[j])
		{
			flag = false;
			break;
		}
	}
	return flag;
}

vector<double> function(vector<double> x)
{
	vector<double> Y(2);
	Y[0] = x[0] + x[1];
	Y[1] = x[0] - x[1];
	//Y[1] = sin(x[0]) - sin(x[1]);
	//cout << Y[0] << " " << Y[1] << endl;
	return Y;
}