import std.stdio;
import std.math;
import std.algorithm;
import std.range;

import common;

struct QuadTree(NumDims) {
    alias Point2D = Point!2;

    Node rootNode;

    this(Point2D[] dataPoints) {
        auto boundingBox = computeBoundingBox(dataPoints);
        rootNode = new Node(dataPoints, boundingBox);
    }

    class Node {
        bool isLeafNode;
        Point2D[] containedPoints;
        AABB!2 nodeBoundingBox;
        Node[4] children;
        // Point2D center;

        this(Point2D[] points, AABB!2 boundingBox) {
            if (points.length < 2) {
                isLeafNode = true;
                containedPoints = points.dup;
                nodeBoundingBox = boundingBox;
            } else {
                Point2D center = (boundingBox.max + boundingBox.min) / 2;

                auto rightHalfPoints = points.partitionByDimension!0(center[0]);
                auto leftHalfPoints = points[0 .. $ - rightHalfPoints.length];

                auto rightTopPoints = rightHalfPoints.partitionByDimension!1(center[1]);
                auto rightBottomPoints = rightHalfPoints[0 .. $ - rightTopPoints.length];
                auto leftTopPoints = leftHalfPoints.partitionByDimension!1(center[1]);
                auto leftBottomPoints = leftHalfPoints[0 .. $ - leftTopPoints.length];

                AABB!2 rightTopBox, leftTopBox, rightBottomBox, leftBottomBox;
                // NE quadrant
                rightTopBox.min = center.dup;
                rightTopBox.max = boundingBox.max.dup;

                // NW quadrant
                leftTopBox.min = Point2D([boundingBox.min[0], center[1]]);
                leftTopBox.max = Point2D([center[0], boundingBox.max[1]]);

                // SE quadrant
                rightBottomBox.min = Point2D([center[0], boundingBox.min[1]]);
                rightBottomBox.max = Point2D([boundingBox.max[0], center[1]]);

                // SW quadrant
                leftBottomBox.min = Point2D([boundingBox.min[0], boundingBox.min[1]]);
                leftBottomBox.max = center.dup;

                // Instantiate child nodes
                children[0] = new Node(leftTopPoints, leftTopBox);
                children[1] = new Node(rightTopPoints, rightTopBox);
                children[2] = new Node(leftBottomPoints, leftBottomBox);
                children[3] = new Node(rightBottomPoints, rightBottomBox);
            }
        }
    }

    Point2D[] rangeQuery(Point2D queryPoint, float radius) {
        Point2D[] results;
        
        void search(Node currentNode) {
            if (currentNode.isLeafNode) {
                foreach(const ref pt; currentNode.containedPoints) {
                    if (distance(pt, queryPoint) < radius) {
                        results ~= pt;
                    }
                }
            } else {
                foreach(childNode; currentNode.children) {
                    if (distance(closest(childNode.nodeBoundingBox, queryPoint), queryPoint) < radius) {
                        search(childNode);
                    }
                }
            }
        }
        
        search(rootNode);
        return results;
    }

    Point2D[] knnQuery(Point2D queryPoint, int k) {
        auto nearestNeighbors = createPriorityQueue(queryPoint);

        void search(Node currentNode) {
            if (currentNode.isLeafNode) {
                foreach(pt; currentNode.containedPoints) {
                    if (nearestNeighbors.length < k) {
                        nearestNeighbors.insert(pt);
                    } else if (distance(pt, queryPoint) < distance(queryPoint, nearestNeighbors.front)) {
                        nearestNeighbors.popFront;
                        nearestNeighbors.insert(pt);
                    }
                }
            } else {
                foreach(childNode; currentNode.children) {
                    if (nearestNeighbors.length < k || distance(closest(childNode.nodeBoundingBox, queryPoint), queryPoint) < distance(queryPoint, nearestNeighbors.front)) {
                        search(childNode);
                    }
                }
            }
        }

        search(rootNode);
        return nearestNeighbors.release;
    }
}

// unittest {
//     auto singlePoint = [Point!2([.5, .5])];
//     auto singlePointTree = QuadTree!2(singlePoint);

//     writeln("Testing QuadTree construction!");
//     assert(singlePointTree.rootNode.isLeafNode == true);

//     auto multiplePoints = [Point!2([.5, .5]), Point!2([1, 1]),
//                            Point!2([0.75, 0.4]), Point!2([0.4, 0.74])];

//     auto tree = QuadTree!2(multiplePoints);
    
//     writeln(tree);
//     writeln("QuadTree range query results:");
//     foreach(pt; tree.rangeQuery(Point!2([1,1]), .7)) {
//         writeln(pt);
//     }
//     writeln("Number of points within radius: ", tree.rangeQuery(Point!2([1,1]), .7).length);
//     assert(tree.rangeQuery(Point!2([1,1]), .7).length == 3);
//     writeln("QuadTree k-nearest neighbors results:");
//     foreach(pt; tree.knnQuery(Point!2([1,1]), 3)) {
//         writeln(pt);
//     }
// }
