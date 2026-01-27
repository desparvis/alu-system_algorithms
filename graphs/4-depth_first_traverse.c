#include <stdbool.h>
#include <stdlib.h>
#include "graphs.h"

/**
 * dfs_traverse_rec - recursive helper for depth_first_traverse
 * @v: pointer to a vertex_t in a graph_t's vertices list
 * @visited: bool array for visited flags
 * @depth: current depth in the traversal
 * @action: function called for each visited vertex
 *
 * Return: deepest depth reached from this vertex
 */
static size_t dfs_traverse_rec(const vertex_t *v, bool *visited, size_t depth,
			       void (*action)(const vertex_t *, size_t))
{
	edge_t *e;
	size_t max_depth;
	size_t curr_depth;

	max_depth = depth;
	visited[v->index] = true;
	action(v, depth);

	e = v->edges;
	while (e != NULL)
	{
		if (e->dest != NULL && !visited[e->dest->index])
		{
			curr_depth = dfs_traverse_rec(e->dest,
						      visited,
						      depth + 1,
						      action);
			if (curr_depth > max_depth)
				max_depth = curr_depth;
		}
		e = e->next;
	}

	return (max_depth);
}

/**
 * depth_first_traverse - depth-first traversal of a graph_t
 * @graph: pointer to the graph_t to traverse
 * @action: function to call for each visited vertex
 *
 * Return: deepest depth reached, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *, size_t))
{
	bool *visited;
	size_t depth;

	if (graph == NULL || action == NULL || graph->nb_vertices == 0)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(bool));
	if (visited == NULL)
		return (0);

	depth = dfs_traverse_rec(graph->vertices, visited, 0, action);

	free(visited);

	return (depth);
}
