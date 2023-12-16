package assignment09;
//import javax.swing.text.Segment;

import java.util.ArrayList;
import java.util.Random;

public class BSPTree {
    private Node root;

    public BSPTree() {
        this.root = null;
    }

    private static class Node {
        private Segment segment;
        private Node left;
        private Node right;

        public Node(Segment segment) {
            this.segment = segment;
            this.left = null;
            this.right = null;
        }
    }

    public BSPTree(ArrayList<Segment> segments) {
        if (segments != null && !segments.isEmpty()) {
            this.root = buildTree(segments);
        }
    }

    private Node buildTree(ArrayList<Segment> segments) {
        if(segments.isEmpty()){
            return null;
        }

        if (segments.size() == 1) {
            // Base case: if only one segment is left, create a leaf node
            return new Node(segments.get(0));
        }

        // Choose the first segment randomly
        Random random = new Random();
        int pivotIndex = random.nextInt(segments.size());
        Segment pivot = segments.get(pivotIndex);
        segments.remove(pivot);


        // Split the segments into two lists: those on the positive side and those on the negative side
        ArrayList<Segment> positiveSide = new ArrayList<>();
        ArrayList<Segment> negativeSide = new ArrayList<>();

        for (Segment current : segments) {
            int side = pivot.whichSide(current);

            if (side > 0) {
                positiveSide.add(current);
            } else if (side < 0) {
                negativeSide.add(current);
            } else {
                Segment[] halves = pivot.split(current);
                // Put one half in positive side and the other in negative side
                positiveSide.add(halves[0]);
                negativeSide.add(halves[1]);
            }
        }

        // Recursively build the left and right subtrees
        Node leftChild = buildTree(negativeSide);
        Node rightChild = buildTree(positiveSide);

        //WHAT IS THIS PART DOING
        // Create the current node with the chosen pivot and children
        Node currentNode = new Node(pivot);
        currentNode.left = leftChild;
        currentNode.right = rightChild;

        return currentNode;
    }

    public void insert(Segment segment) {
        if (segment != null) {
            root = insertHelper(root, segment);
        }
    }

    // Recursive helper method for inserting a segment into the tree
    private Node insertHelper(Node currentNode, Segment segment) {
        if (currentNode == null) {
            return new Node(segment);
        }

        // Determine which side of the current node the new segment belongs to
        int side = currentNode.segment.whichSide(segment);

        if (side > 0) {
            currentNode.right = insertHelper(currentNode.right, segment);
        } else if (side < 0) {
            // Insert into the left subtree
            currentNode.left = insertHelper(currentNode.left, segment);
        } else {
            Segment[] halves = segment.split(currentNode.segment);
            currentNode.right = insertHelper(currentNode.right, halves[1]);
            currentNode.left = insertHelper(currentNode.left, halves[0]);
        }

        return currentNode;
    }



    public void traverseFarToNear(double x, double y, SegmentCallback callback) {
        traverseFarToNearHelper(root, x, y, callback);
    }

    // Recursive helper method for traversing the BSP tree in "far to near" order
    private void traverseFarToNearHelper(Node node, double x, double y, SegmentCallback callback) {
        if (node == null) {
            return;
        }

        // Determine which side of the current node the point (x, y) is on
        int side = node.segment.whichSidePoint(x, y);


        // Traverse the far side first (based on "far to near" order)
        if (side > 0) {
            traverseFarToNearHelper(node.left, x, y, callback);
        } else {
            traverseFarToNearHelper(node.right, x, y, callback);
        }

        callback.callback(node.segment);

        // Traverse the near side
        if (side > 0) {
            traverseFarToNearHelper(node.right, x, y, callback);
        } else {
            traverseFarToNearHelper(node.left, x, y, callback);
        }
    }



    public Segment collision(Segment query) {
        return collisionHelper(root, query);
    }

    // Recursive helper method for collision detection
    private Segment collisionHelper(Node node, Segment query) {
        if (node == null) {
            return null;
        }

        // Determine which side of the current node the query segment is on
        int side = node.segment.whichSide(query);

        // Traverse the side where the query segment is located
        if (side > 0) {
            return collisionHelper(node.right, query);
        } else if (side < 0) {
            return collisionHelper(node.left, query);
        } else {
            // Check if the current segment intersects with the query segment
            if (node.segment.intersects(query)) {
                return node.segment;  // Return the intersecting segment
            }
            // Query segment is collinear or overlaps with the current segment
            // Handle as needed, e.g., check both sides for intersections
            Segment collisionOnRight = collisionHelper(node.right, query);
            if (collisionOnRight != null) {
                return collisionOnRight;
            }

            Segment collisionOnLeft = collisionHelper(node.left, query);
            return collisionOnLeft;
        }
    }

}

