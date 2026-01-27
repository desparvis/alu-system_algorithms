#include "graphs.h"

/**
 * graph_delete - completely deallocates a graph_t
 * @graph: pointer to the graph_t to be deleted
 */
void graph_delete(graph_t *graph)
{
	vertex_t *v;
	vertex_t *v_tmp;
	edge_t *e;
	edge_t *e_tmp;

	if (graph == NULL)
		return;

	v = graph->vertices;
	while (v != NULL)
	{
		e = v->edges;
		while (e != NULL)
		{
			e_tmp = e->next;
			free(e);
			e = e_tmp;
		}
		v_tmp = v->next;
		free(v->content);
		free(v);
		v = v_tmp;
	}

	free(graph);
}
