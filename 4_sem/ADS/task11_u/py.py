# Python3 program for the above approach

# Function that performs the DFS
# traversal to find cost to reach
# from vertex v to other vertexes
def dfs(v, p, t, h, ans):

	# Traverse the Adjacency list
	# of u
	for u in t[v]:
		if (u[0] == p):
			continue
		
		# Recursive Call
		dfs(u[0], v, t, h + u[1], ans)

	# Update ans[v]
	ans[v] = h

# Function to find the sum of
# weights of all paths
def solve(n, edges):

	# Stores the Adjacency List
	t = [[] for i in range(n)]
	
	# Store the edges
	for i in range(n - 1):
		t[edges[i][0]].append([edges[i][1],
							edges[i][2]])
		t[edges[i][1]].append([edges[i][0],
							edges[i][2]])

	# sum is the answer
	sum = 0

	# Calculate sum for each vertex
	for i in range(n):
		ans = [0 for i in range(n)]

		# Perform the DFS Traversal
		dfs(i, -1, t, 0, ans)

		# Sum of distance
		for j in range(n):
			sum += ans[j]

	# Return the final sum
	return sum
	
# Driver Code
if __name__ == "__main__":
	
	

	# Given Edges
	edges = [ 
        [0, 1, 1],
        [1, 2, 2],
		[2, 3, 3]
    ]

	# No of vertices
	N = len(edges) + 1

	# Function Call
	print(solve(N, edges))

# This code is contributed by rutvik_56
