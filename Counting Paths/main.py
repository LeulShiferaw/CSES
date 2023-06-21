from collections import defaultdict

# Function to perform a depth-first search (DFS) to calculate depth and parent arrays
def dfs(node, parent, depth, parent_arr, adj_list):
    parent_arr[node] = parent
    depth[node] = depth[parent] + 1

    for child in adj_list[node]:
        if child != parent:
            dfs(child, node, depth, parent_arr, adj_list)

# Function to calculate the Lowest Common Ancestor (LCA) of two nodes
def lca(u, v, depth, parent_arr):
    # Make u the deeper node
    if depth[u] < depth[v]:
        u, v = v, u

    # Raise u to the same depth as v
    while depth[u] > depth[v]:
        u = parent_arr[u]

    # Find the LCA by raising both nodes simultaneously
    while u != v:
        u = parent_arr[u]
        v = parent_arr[v]

    return u

# Function to calculate the number of paths containing each node
def counting_paths(n, edges, paths):
    adj_list = defaultdict(list)

    # Create adjacency list from edges
    for u, v in edges:
        adj_list[u].append(v)
        adj_list[v].append(u)

    depth = [0] * (n+1)  # Depth of each node
    parent_arr = [0] * (n+1)  # Parent of each node

    # Perform DFS to calculate depth and parent arrays
    dfs(1, 0, depth, parent_arr, adj_list)

    diff_arr = [0] * (2 * n + 1)  # Difference array for path counting

    # Iterate through the given paths and update the difference array
    for a, b in paths:
        lca_node = lca(a, b, depth, parent_arr)

        # Increment the path count for node a
        diff_arr[depth[a]] += 1
        diff_arr[depth[a] + 1] -= 1

        # Increment the path count for node b
        diff_arr[depth[b]] += 1
        diff_arr[depth[b] + 1] -= 1

        # Decrement the path counts for the LCA node and its parent
        diff_arr[depth[lca_node]] -= 1
        diff_arr[depth[lca_node] + 1] += 1
        if parent_arr[lca_node] != 0:
            diff_arr[depth[parent_arr[lca_node]]] -= 1
            diff_arr[depth[parent_arr[lca_node]] + 1] += 1

    # Calculate the prefix sum of the difference array
    for i in range(1, len(diff_arr)):
        diff_arr[i] += diff_arr[i-1]

    # Return the path counts for each node
    return diff_arr[1:n+1]

# Read input
n, m = map(int, input().split())
edges = []
for _ in range(n-1):
    u, v = map(int, input().split())
    edges.append((u, v))

paths = []
for _ in range(m):
    a, b = map(int, input().split())
    paths.append((a, b))

# Solve the problem
result = counting_paths(n, edges, paths)

# Print the result
print(*result)
