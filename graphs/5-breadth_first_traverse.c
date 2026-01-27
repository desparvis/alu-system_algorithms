#include <stdlib.h>
#include "graphs.h"

/**
 * bfs_init - initialize BFS helper arrays
 * @graph: pointer to the graph
 * @queue: address of queue
 * @depths: address of depths array
 * @visited: address of visited array
 *
 * Return: 0 on success, 1 on failure
 */
static int bfs_init(const graph_t *graph, vertex_t ***queue,
		    size_t **depths, int **visited)
{
	*queue = calloc(graph->nb_vertices, sizeof(vertex_t *));
	*depths = calloc(graph->nb_vertices, sizeof(size_t));
	*visited = calloc(graph->nb_vertices, sizeof(int));

	if (*queue == NULL || *depths == NULL || *visited == NULL)
		return (1);

	return (0);
}

/**
 * bfs_free - free BFS helper arrays
 * @queue: BFS queue
 * @depths: depths array
 * @visited: visited array
 */
static void bfs_free(vertex_t **queue, size_t *depths, int *visited)
{
	free(queue);
	free(depths);
	free(visited);
}

/**
 * bfs_process - perform BFS traversal
 * @graph: pointer to the graph
 * @action: function to call
 * @queue: BFS queue
 * @depths: depths array
 *
 * Return: maximum depth reached
 */
static size_t bfs_process(const graph_t *graph,
			  void (*action)(const vertex_t *, size_t),
			  vertex_t **queue, size_t *depths)
{
	size_t front;
	size_t rear;
	size_t max_depth;
	size_t depth;
	vertex_t *v;
	edge_t *edge;
	int *visited;

	front = 0;
	rear = 0;
	max_depth = 0;

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (visited == NULL)
		return (0);

	queue[rear] = graph->vertices;
	depths[rear] = 0;
	visited[graph->vertices->index] = 1;
	rear++;

	while (front < rear)
	{
		v = queue[front];
		depth = depths[front];
		front++;

		action(v, depth);

		if (depth > max_depth)
			max_depth = depth;

		edge = v->edges;
		while (edge != NULL)
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				queue[rear] = edge->dest;
				depths[rear] = depth + 1;
				rear++;
			}
			edge = edge->next;
		}
	}

	free(visited);

	return (max_depth);
}

/**
 * breadth_first_traverse - traverses a graph using BFS
 * @graph: pointer to the graph to traverse
 * @action: function to call on each visited vertex
 *
 * Return: maximum depth reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *, size_t))
{
	vertex_t **queue;
	size_t *depths;
	int *visited;
	size_t max_depth;

	if (graph == NULL || graph->vertices == NULL || action == NULL)
		return (0);

	if (bfs_init(graph, &queue, &depths, &visited))
	{
		bfs_free(queue, depths, visited);
		return (0);
	}

	max_depth = bfs_process(graph, action, queue, depths);

	bfs_free(queue, depths, visited);

	return (max_depth);
}
