#include "kdtree.h"
#include "sort.h"
#include "util.h"
#include "bruteforce.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
// construction of a k-d tree and performing k-NN lookups in the tree. The two struct definitions are
// given, and do not have to be modified (but you are allowed to modify
// them if you believe you can do better than us). Further, there is a
// function kdtree svg() that visualises the tree structure when called
// from knn-svg.c, which may be useful for debugging (or just pretty pictures).

struct node {
  // Index of this node's point in the corresponding 'indexes' array.
  int point_index;

  // Axis along which this node has been splot.
  int axis;

  // The left child of the node; NULL if none.
  struct node *left;

  // The right child of the node; NULL if none.
  struct node *right;
};

struct kdtree {
  int d;
  const double *points;
  struct node* root;
};

struct sort_env {
  int c;
  int d;
  double *points;
};

int cmp_indexes(const int *ip, const int *jp, struct sort_env* env) {
  int i = *ip;
  int j = *jp;
  double *x = &env->points[i*env->d];
  double *y = &env->points[j*env->d];
  int c = env->c;

  if (x[c] < y[c]) {
    return -1;
  } else if (x[c] == y[c]) {
    return 0;
  } else {
    return 1;
  }
}


void sort_indexes(int d, int axis,double *points,int *indexes,int n){
  struct sort_env env;
  env.points = points;
  env.d = d;
  env.c = axis;

  hpps_quicksort(indexes, n, sizeof(int),
                (int (*)(const void*, const void*, void*))cmp_indexes,
                &env);    
}

struct node* kdtree_create_node(int d, const double *points, int depth, int n, int *indexes) {
    struct node *node = malloc(sizeof(struct node));
    if (n <= 0) {
        return NULL;
    }
    int axis = depth%d;
    // Sort indexes based on the axis
    sort_indexes(d,axis,points,indexes,n);

    // Find median index
    int medianIndex = indexes[n / 2];
    int other_half = n-(n/2) -1;

    if(other_half == 1 && (n/2) == 0){
    other_half = 0;
    }

    // Create a new node
    node->axis = axis;
    node->point_index = medianIndex;

    // Recursively build the left and right subtrees
    node->left = kdtree_create_node(d, points, depth+1, n/2, indexes);
    node->right = kdtree_create_node(d, points, depth+1, other_half, &indexes[(n/2)+1]);

    return node;
}

struct kdtree *kdtree_create(int d, int n, const double *points) {
  struct kdtree *tree = malloc(sizeof(struct kdtree));
  tree->d = d;
  tree->points = points;

  int *indexes = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    indexes[i] = i;
  }

  tree->root = kdtree_create_node(d, points, 0, n, indexes);

  free(indexes);

  return tree;
}

void kdtree_free_node(struct node *node) {
  if (node->left != NULL) {
    kdtree_free_node(node->left);
  }
  if (node->right != NULL){
    kdtree_free_node(node->right);
  } 

  free(node);
}

void kdtree_free(struct kdtree *tree) {
  kdtree_free_node(tree->root);
  free(tree);
}

void kdtree_knn_node(const struct kdtree *tree, int k, const double* query,
                     int *closest, double *radius,
                     const struct node *node) {
  int check_index = node->point_index;
  int d = tree->d;

  int inserted = insert_if_closer(k, d, tree->points, closest, query, check_index);

  double *point = &tree->points[check_index*d];

  double diff = point[node->axis] - query[node->axis];

  if(inserted == 1){
    double highest = 0;

    for(int i = 0; i < k; i++){
      int ind = closest[i];
      if(ind != -1 && distance(d,&tree->points[ind*d],query) > highest){
        highest = distance(d,&tree->points[ind*d],query);
      }
    }

    *radius = highest;
  }

  if(diff >= 0 || *radius > fabs(diff)){
    if(node->left != NULL){
      kdtree_knn_node(tree,k,query,closest,radius,node->left);
    }
  }
  if(diff <= 0 || *radius > fabs(diff)){
    if(node->right != NULL){
      kdtree_knn_node(tree,k,query,closest,radius,node->right);
    }
  }

}

int* kdtree_knn(const struct kdtree *tree, int k, const double* query) {
  int* closest = malloc(k * sizeof(int));
  double radius = INFINITY;

  for (int i = 0; i < k; i++) {
    closest[i] = -1;
  }

  kdtree_knn_node(tree, k, query, closest, &radius, tree->root);

  return closest;
}

void kdtree_svg_node(double scale, FILE *f, const struct kdtree *tree,
                     double x1, double y1, double x2, double y2,
                     const struct node *node) {
  if (node == NULL) {
    return;
  }

  double coord = tree->points[node->point_index*2+node->axis];
  if (node->axis == 0) {
    // Split the X axis, so vertical line.
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
            coord*scale, y1*scale, coord*scale, y2*scale);
    kdtree_svg_node(scale, f, tree,
                    x1, y1, coord, y2,
                    node->left);
    kdtree_svg_node(scale, f, tree,
                    coord, y1, x2, y2,
                    node->right);
  } else {
    // Split the Y axis, so horizontal line.
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
            x1*scale, coord*scale, x2*scale, coord*scale);
    kdtree_svg_node(scale, f, tree,
                    x1, y1, x2, coord,
                    node->left);
    kdtree_svg_node(scale, f, tree,
                    x1, coord, x2, y2,
                    node->right);
  }
}

void kdtree_svg(double scale, FILE* f, const struct kdtree *tree) {
  assert(tree->d == 2);
  kdtree_svg_node(scale, f, tree, 0, 0, 1, 1, tree->root);
}