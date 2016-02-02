#include "graph.h"
#include "min_heap.h"
#include "b_tree.h"
#include "hashmap.h"

#define DEFAULT_CLOSED_SET_SIZE

//need to return a list -> ints, size of list
void a_star(graph* graph, int start, int goal){
	bnode* closed_set = NULL;
	hashmap* came_from = hashmapCreate(11);
	minHeap open_set = initMinHeap();

	//insertNode(open_set, )
//
//	while(open_set.size > 0) {
//
//	}


	printf("couldn't find a path");
}
/*
 *
 *
 * Openlist.Clear(); ClosedList.Clear();
	currentNode = nil;
	startNode.g(x) = 0;
	Openlist.Push(startNode);aa
While currentNode != goalNode
	currentNode = OpenList.Pop();
	for each s in currentNode.Children[]
		s.g(x) = currentNode.g(x) + c(currentNode, s);
		OpenList.Push(s);
	end for each
	ClosedList.Push(currentNode);
End while
 */
/*
function A*(start,goal)
    ClosedSet := {}    	  // The set of nodes already evaluated.
    OpenSet := {start}    // The set of tentative nodes to be evaluated, initially containing the start node
    Came_From := the empty map    // The map of navigated nodes.

    g_score := map with default value of Infinity
    g_score[start] := 0    // Cost from start along best known path.
    // Estimated total cost from start to goal through y.
    f_score := map with default value of Infinity
    f_score[start] := heuristic_cost_estimate(start, goal)

    while OpenSet is not empty
        current := the node in OpenSet having the lowest f_score[] value
        if current = goal
            return reconstruct_path(Came_From, goal)

        OpenSet.Remove(current)
        ClosedSet.Add(current)
        for each neighbor of current
            if neighbor in ClosedSet
                continue		// Ignore the neighbor which is already evaluated.
            tentative_g_score := g_score[current] + dist_between(current,neighbor) // length of this path.
            if neighbor not in OpenSet	// Discover a new node
                OpenSet.Add(neighbor)
            else if tentative_g_score >= g_score[neighbor]
                continue		// This is not a better path.

            // This path is the best until now. Record it!
            Came_From[neighbor] := current
            g_score[neighbor] := tentative_g_score
            f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)

    return failure

function reconstruct_path(Came_From,current)
    total_path := [current]
    while current in Came_From.Keys:
        current := Came_From[current]
        total_path.append(current)
    return total_path
 */
