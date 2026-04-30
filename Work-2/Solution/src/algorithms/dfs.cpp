#include <iostream>

std::vector<int> dfs(const std::vector<std::vector<std::pair<int, int>>> &adj, int start) // Time: O(V + E) | Space: O(V)
{
    std::vector<bool> visited(adj.size(), false);
    std::stack<int> st;
    std::vector<int> visitOrder;

    st.push(start);

    while (!st.empty())
    {
        int vertex = st.top();
        st.pop();

        if (!visited[vertex])
        {
            visited[vertex] = true;
            visitOrder.push_back(vertex);

            for (const auto &[neighbor, weight] : adj[vertex])
            {
                if (!visited[neighbor])
                {
                    st.push(neighbor);
                }
            }
        }
    }

    return visitOrder;
}