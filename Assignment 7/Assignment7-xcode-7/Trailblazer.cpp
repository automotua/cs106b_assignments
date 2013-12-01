/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc> 
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world)) {
    
    HashMap<Loc, Color> colorMap;
    HashMap<Loc, Loc> parentMap;
    HashMap<Loc, double> distanceMap;
    TrailblazerPQueue<Loc> tpq;
    
    colorAllNodes(world, colorMap, GRAY);
    colorMap.put(start, YELLOW);
    colorCell(world, start, YELLOW);
    
    distanceMap.put(start, 0.0);
    tpq.enqueue(start, 0.0 + heuristic(start, end, world));
    
    while (!tpq.isEmpty()) {
        Loc curr = tpq.dequeueMin();
        colorMap.put(curr, GREEN);
        colorCell(world, curr, GREEN);
        if (curr == end) break;
        
        for (int row = curr.row - 1; row <= curr.row + 1; row++) {
            for (int col = curr.col - 1; col <= curr.col + 1; col++) {
                if (!isOutOfBound(row, col, world)) {
                    Loc node = makeLoc(row, col);
                    double distance = distanceMap.get(curr) + costFn(curr, node, world);
                    if (colorMap.get(node) == GRAY) {
                        colorMap.put(node, YELLOW);
                        colorCell(world, node, YELLOW);
                        distanceMap.put(node, distance);
                        parentMap.put(node, curr);
                        tpq.enqueue(node, distance + heuristic(node, end, world));
                    } else if (colorMap.get(node) == YELLOW && 
                               distance < distanceMap.get(node)) {
                        distanceMap.put(node, distance);
                        parentMap.put(node, curr);
                        tpq.decreaseKey(node, distance + heuristic(node, end, world));
                    }                    
                }
            }
        }
    }
	
    Vector<Loc> shortestPath;
    storePath(start, end, parentMap, shortestPath);
    	
    return shortestPath;
}

void colorAllNodes(Grid<double> & world, HashMap<Loc, Color> & colorMap, Color color) {
    for (int row = 0; row < world.nRows; row++) {
        for (int col = 0; col < world.nCols; col++) {
            Loc node = makeLoc(row, col);
            colorMap.put(node, GRAY);
        }
    }
}

bool isOutOfBound(int row, int col, Grid<double> & world) {
    return row < 0 || row >= world.nRows ||
           col < 0 || col >= world.nCols;
}

void storePath(Loc & start, Loc end, HashMap<Loc, Loc> & parentMap, Vector<Loc> & shortestPath) {
    if (start == end) {
        shortestPath.add(end);
        return;
    }
    storePath(start, parentMap.get(end), parentMap, shortestPath);
    shortestPath.add(end);
}

Set<Edge> createMaze(int numRows, int numCols) {
    Set<Edge> spanningTree;
    HashMap<Loc, Set<Loc> *> nodeClusters;
    int nClusters = numRows * numCols;
    createClusters(numRows, numCols, nodeClusters);
    TrailblazerPQueue<Edge> tpq;
    insertEdges(numRows, numCols, tpq);

    while (nClusters > 1) {
        Edge e = tpq.dequeueMin();
        if (!isSameCluster(e.start, e.end, nodeClusters)) {
            mergeClusters(e.start, e.end, nodeClusters);
            nClusters--;
            spanningTree.add(e);
        }
    }
    
    freeNodeClusters(nodeClusters);
    
    return spanningTree;
}

void createClusters(int numRows, int numCols, HashMap<Loc, Set<Loc> *> & nodeClusters) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Loc node = makeLoc(i, j);
            Set<Loc> * cluster = new Set<Loc>;
            cluster->add(node);
            nodeClusters.put(node, cluster);
        }
    }
}

void insertEdges(int numRows, int numCols, TrailblazerPQueue<Edge> & tpq) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (j + 1 < numCols) {
                Edge e = makeEdge(makeLoc(i, j), makeLoc(i, j + 1));
                tpq.enqueue(e, randomReal(0, 10));
            }
            
            if (i + 1 < numRows) {
                Edge e = makeEdge(makeLoc(i, j), makeLoc(i + 1, j));
                tpq.enqueue(e, randomReal(0, 10));
            }
        }
    }
}

bool isSameCluster(Loc & node1, Loc & node2, HashMap<Loc, Set<Loc> *> & nodeClusters) {
    return nodeClusters.get(node1) == nodeClusters.get(node2);
}

void mergeClusters(Loc & node1, Loc & node2, HashMap<Loc, Set<Loc> *> & nodeClusters) {
    Set<Loc> * cluster1 = nodeClusters.get(node1);
    Set<Loc> * cluster2 = nodeClusters.get(node2);
    Set<Loc> * mergedCluster = new Set<Loc>;
    mergeSets(cluster1, cluster2, mergedCluster);
    updateCluster(nodeClusters, mergedCluster);
    delete cluster1;
    delete cluster2;
}

void mergeSets(Set<Loc> * set1, Set<Loc> * set2, Set<Loc> * & mergedSet) {
    foreach(Loc node in *set1)
        mergedSet->add(node);
    
    foreach(Loc node in *set2)
        mergedSet->add(node);
}

void updateCluster(HashMap<Loc, Set<Loc> *> & nodeClusters, Set<Loc> * mergedCluster) {
    foreach(Loc node in *mergedCluster)
        nodeClusters.put(node, mergedCluster);
}

void freeNodeClusters(HashMap<Loc, Set<Loc> *> & nodeClusters) {
    Set<Loc> * cluster = nodeClusters.get(makeLoc(0, 0));
    delete cluster;
}