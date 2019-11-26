#include<stdio.h>
#include<stdlib.h>
typedef struct {
    unsigned int first;
    unsigned int second;
    unsigned int weight;
} weighted_edge;

/* Check if the tour already contains an edge */
static unsigned int tour_contains(const weighted_edge *tour, unsigned int t,
        const weighted_edge *edge)
{
    unsigned int contains = 0;
    unsigned int i;
    for (i = 0; i < t && !contains; i++) {
        contains = tour[i].first == edge->first
            && tour[i].second == edge->second;
    }
    return contains;
}

/* Find the edge to v's nearest neighbour not in the tour already */
static unsigned int nearest_neighbour_edge(const weighted_edge *edges, unsigned int size,
        const weighted_edge *tour, unsigned int t, unsigned int v)
{
    unsigned int min_distance = 0;
    unsigned int nearest_neighbour;
    unsigned int i;
    for (i = 0; i < size; i++) {
        if ((edges[i].first == v || edges[i].second == v)
                && (min_distance == 0 || edges[i].weight < min_distance)
                && !tour_contains(tour, t, &edges[i]))
        {
            min_distance = edges[i].weight;
            nearest_neighbour = i;
        }
    }
    return nearest_neighbour;
}

weighted_edge *repetitive_nearest_neighbour_tsp(const weighted_edge *edges, unsigned int size,
        unsigned int order)
{
    unsigned int best_tour_distance = 0;
    weighted_edge *best_tour = NULL;
    unsigned int v;
    for (v = 0; v < order; v++) {
        unsigned int t;
        unsigned int distance = 0;
        weighted_edge *tour = malloc(order * sizeof(weighted_edge));
        if (tour == NULL) {
            return NULL;
        }
        for (t = 0; t < order; t++) {
            unsigned int e = nearest_neighbour_edge(edges, size, tour, t, v);
            tour[t] = edges[e];
            distance += edges[e].weight;
            v = edges[e].first == v ? edges[e].second : edges[e].first;
        }
        if (best_tour_distance == 0 || distance < best_tour_distance) {
            best_tour_distance = distance;
            free(best_tour);
            best_tour = tour;
        }
        else {
            free(tour);
        }
    }
    return best_tour;
}
void weighted_edge_connect(weighted_edge *edges, unsigned int first, unsigned int second,
        unsigned int weight, unsigned int *pos)
{
    edges[*pos].first = first;
    edges[*pos].second = second;
    edges[*pos].weight = weight;
    (*pos)++;
}

void print_edges(const weighted_edge *edges, unsigned int n)
{
    unsigned int e;
    for (e = 0; e < n; e++) {
        printf("Edge: %u, %u; Weight:  %u\n", edges[e].first, edges[e].second, edges[e].weight);
    }
}

int main(int argv, char argc[]){

  unsigned int iter = 0;
  int i, j, n;
  printf("Enter number of nodes: ");
  scanf("%d", &n);

  int graph[n][n];
  const unsigned int size = (n*(n-1))/2; /* Edges */
  const unsigned int order = n; /* Vertices */
  weighted_edge *edges = malloc(size * sizeof(weighted_edge));
  weighted_edge *tour;

  for(i=0; i<n-1; i++){
    for(j=i+1; j<n; j++){
      scanf("%d", &graph[i][j]);
    }
  }

  for(i=0; i<n-1; i++){
    for(j=i+1; j<n; j++){
      weighted_edge_connect(edges, i, j, graph[i][j], &iter);
    }
  }

  // for(i=0; i<6-1; i++){
  //   for(j=i+1; j<6; j++){
  //     printf("%d ", graph[i][j]);
  //   }
  //   printf("\n");
  // }

  tour = repetitive_nearest_neighbour_tsp(edges, size, order);
  for(i=0; i<)
  // print_edges(tour, order);

  free(tour);
  free(edges);
  return 0;
}
