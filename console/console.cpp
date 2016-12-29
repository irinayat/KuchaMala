// console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

	using EDGES = vector<pair<int, int>>;

	class CGraph
	{
		unordered_map<int /*vertex*/, unordered_set<int> /*incident vertices*/> m_vs;
		int m_root = -1;
		int m_edges_count = 0;

	public:
		CGraph() {}
		CGraph(const EDGES& edges)
		{
			m_root = edges.front().first; // doesn't matter which vertex is asigned to be the root
			m_edges_count = edges.size();
			for (auto& e : edges)
			{
				m_vs[e.first].insert(e.second);
				m_vs[e.second].insert(e.first);
			}
		}
		size_t VertexCount() const { return m_vs.size(); }
		void AddEdge(int v1, int v2)
		{
			m_root = v1;
			m_edges_count++;
			m_vs[v1].insert(v2);
			m_vs[v2].insert(v1);
		}

		bool IsTree()
		{
			if (m_vs.size() != m_edges_count + 1) return false;

			// check connectedness
			queue<int> in_progress;
			in_progress.push(m_root);

			unordered_set<int> seen;
			seen.insert(m_root);

			while (!in_progress.empty())
			{
				auto cur = in_progress.front();
				for (auto v : m_vs[cur])
				{
					if (seen.count(v) == 0)
					{
						in_progress.push(v);
						seen.insert(v);
					}
				}

				in_progress.pop();
			}
			return seen.size() == m_vs.size();
		}
	};

int main()
{
	int v_count, e_count;
	cin >> v_count;
	cin >> e_count;
	bool sureNotATree = (v_count - 1 != e_count);

	CGraph g;
	for (int i = 0; i < e_count; i++)
	{
		int v1, v2;
		cin >> v1;
		cin >> v2;
		if (!sureNotATree) g.AddEdge(v1, v2);
	}

	cout << (sureNotATree ? "NO" : (e_count == 0 ? "YES" : (g.IsTree() ? "YES" : "NO"))) << endl;

	char q;
	cin >> q;
	return 0;
}

