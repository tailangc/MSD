package assignment09;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

class BSPTreeTest {

    private BSPTree tree;
    private ArrayList<Segment> segments;
    @BeforeEach
    void setUp(){
        segments = new ArrayList<>();
        segments.add(new Segment(0,0,1,1));
        segments.add(new Segment(1,0,2,1));
        segments.add(new Segment(3,0,4,1));
        tree = new BSPTree(segments);
    }
    @Test
    void insert() {
        Segment newSegment = new Segment(0,1,1,2);
        tree.insert(newSegment);
        ArrayList<Segment> traversedSegments = new ArrayList<>();
        tree.traverseFarToNear(0,1,traversedSegments::add);
        assertEquals(4, traversedSegments.size());
    }

    @Test
    void traverseFarToNear() {
        Segment segment1 = new Segment(0, 0, 1, 1);
        Segment segment2 = new Segment(1, 0, 2, 1);
        Segment segment3= new Segment(3, 0, 4, 1);
        BSPTree tree = new BSPTree();
        tree.insert(segment1);
        tree.insert(segment2);
        tree.insert(segment3);


        ArrayList<Segment> traversedSegments = new ArrayList<>();
        tree.traverseFarToNear(0,1,traversedSegments::add);
        // 检查是否按照预期顺序遍历

        assertEquals(3, traversedSegments.size());
        ArrayList<Segment> expected = new ArrayList<>(List.of(segment3, segment2, segment1));
        assertEquals(expected, traversedSegments);
    }

    @Test
    void collision() {
        Segment querySegment = new Segment(0.5,0.5,0.5,1.5);
        Segment result = tree.collision(querySegment);
        assertNotNull(result);
    }

}