import std.stdio;
import std.math;
import std.algorithm;
import std.range;

import common;

struct KDTree(size_t Dim) {
    alias PD = Point!Dim;
    Node!0 root;

    this(PD[] points) {
        root = new Node!0(points);
    }

    class Node(size_t splitDimension) {
        enum thisLevel = splitDimension;
        enum nextLevel = (splitDimension + 1) % Dim;
        Node!nextLevel left, right;
        PD splitPoint;

        // build the node by finding the median point along the thisLevel dimension.
        this(PD[] pts) {
            PD[] leftPoints = pts.medianByDimension!thisLevel;
            writeln(leftPoints);
            PD[] rightPoints = pts[leftPoints.length + 1 .. $];

            splitPoint = pts[leftPoints.length];

            // Recursive create left and right children node if there are points to the left and right of the median.
            if (leftPoints.length > 0) {
                left = new Node!nextLevel(leftPoints);
            }
            if (rightPoints.length > 0) {
                right = new Node!nextLevel(rightPoints);
            }
        }
    }

    PD[] rangeQuery(PD queryPt, float r) {
        //  find all points within distance r from queryPt
        PD[] ret;
        void recurse(NodeType)(NodeType n) {
            if (distance(n.splitPoint, queryPt) < r) {
                ret ~= n.splitPoint;
            }
            if (n.left && (queryPt[n.thisLevel] - r < n.splitPoint[n.thisLevel])) {
                recurse(n.left);
            }
            if (n.right && (queryPt[n.thisLevel] + r > n.splitPoint[n.thisLevel])) {
                recurse(n.right);
            }
        }
        recurse(root);
        return ret;
    }

    PD[] knnQuery(PD queryPt, int k) {
        auto priorityQueue = makePriorityQueue(queryPt);

        void recurse(size_t Dimension, size_t Dim)(Node!Dimension n, AABB!Dim aabb) {
            // priority queue maintains the k nearest points found so far
            if (priorityQueue.length < k) {
                priorityQueue.insert(n.splitPoint);
            } else if (distance(n.splitPoint, queryPt) < distance(queryPt, priorityQueue.front)) {
                priorityQueue.popFront;
                priorityQueue.insert(n.splitPoint);
            }

            AABB!Dim leftAABB, rightAABB;

            leftAABB.min = aabb.min.dup;
            leftAABB.max = aabb.max.dup;
            rightAABB.min = aabb.min.dup;
            rightAABB.max = aabb.max.dup;

            leftAABB.max[n.thisLevel] = n.splitPoint[n.thisLevel];
            rightAABB.min[n.thisLevel] = n.splitPoint[n.thisLevel];

            if (n.left && ((priorityQueue.length < k) || distance(closest(leftAABB, queryPt), queryPt) < distance(queryPt, priorityQueue.front))) {
                recurse(n.left, leftAABB);
            }

            if (n.right && ((priorityQueue.length < k) || distance(closest(rightAABB, queryPt), queryPt) < distance(queryPt, priorityQueue.front))) {
                recurse(n.right, rightAABB);
            }
        }

        AABB!Dim rootAABB;
        rootAABB.min[] = -float.infinity;
        rootAABB.max[] = float.infinity;
        recurse(root, rootAABB);

        return priorityQueue.release;
    }
}




// unittest {
  
//     auto points = [Point!2([0.5, 0.5]),Point!2([1, 1]),Point!2([0.75, 0.4]),Point!2([0.4, 0.74]),Point!2([0.2, 0.2]),Point!2([0.9, 0.9]),Point!2([0.8, 0.3])
//     ];

//     auto kdtree = KDTree!2(points);

//     // Define the query point and radius for the range query
//     Point!2 queryPt = Point!2([0.75, 0.75]);
//     float radius = 0.3;

//     // Perform a range query
//     writeln("KDTree range query:");
//     auto rangeResults = kdtree.rangeQuery(queryPt, radius);
//     foreach(p; rangeResults) {
//         writeln(p);
//     }
//     writeln("Number of points within radius ", radius, ": ", rangeResults.length);

//     // Verify the range query results
//     assert(rangeResults.length == 3); // Expected: 3 points within the radius

//     int k = 4;

//     // Perform a k-nearest neighbors query
//     writeln("KDTree k-nearest neighbors query:");
//     auto knnResults = kdtree.knnQuery(queryPt, k);
//     foreach(p; knnResults) {
//         writeln(p);
//     }
//     writeln("Number of nearest neighbors found: ", knnResults.length);

//     // Verify the k-nearest neighbors query results
//     assert(knnResults.length == k); // Expected: k points
// }

