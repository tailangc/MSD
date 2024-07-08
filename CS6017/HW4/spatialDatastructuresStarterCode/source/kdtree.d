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

        this(PD[] pts) {
            PD[] leftPoints = pts.medianByDimension!thisLevel;
            writeln(leftPoints);
            PD[] rightPoints = pts[leftPoints.length + 1 .. $];

            splitPoint = pts[leftPoints.length];
            if (leftPoints.length > 0) {
                left = new Node!nextLevel(leftPoints);
            }
            if (rightPoints.length > 0) {
                right = new Node!nextLevel(rightPoints);
            }
        }
    }

    PD[] rangeQuery(PD queryPt, float r) {
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

unittest {
    auto kdtree = KDTree!2([Point!2([.5, .5]), Point!2([1, 1]),
    Point!2([0.75, 0.4]), Point!2([0.4, 0.74])]);

    writeln(kdtree);

    writeln("kdtree range query!");
    foreach(p; kdtree.rangeQuery(Point!2([1,1]), .7)) {
        writeln(p);
    }
    writeln(kdtree.rangeQuery(Point!2([1,1]), .7).length);
    assert(kdtree.rangeQuery(Point!2([1,1]), .7).length == 3);

    writeln("kdtree knn query!");
    foreach(p; kdtree.knnQuery(Point!2([1,1]), 3)) {
        writeln(p);
    }
}
