package assign01;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GrayscaleImageTest {

    private GrayscaleImage smallSquare;
    private GrayscaleImage smallWide;
    private GrayscaleImage allZero;

    @BeforeEach
    void setUp() {
        smallSquare = new GrayscaleImage(new double[][]{{1,2},{3,4}});
        smallWide = new GrayscaleImage(new double[][]{{1,2,3},{4,5,6}});
        allZero = new GrayscaleImage(new double[][]{{0,0},{0,0}});
    }

    @Test
    void testGetPixel(){
        assertEquals(smallSquare.getPixel(0,0), 1);
        assertEquals(smallSquare.getPixel(1,0), 2);
        assertEquals(smallSquare.getPixel(0,1), 3);
        assertEquals(smallSquare.getPixel(1,1), 4);

    }

    @Test
    void testEquals() {
        assertEquals(smallSquare, smallSquare);
        var equivalent = new GrayscaleImage(new double[][]{{1,2},{3,4}});
        assertEquals(smallSquare, equivalent);
    }

    @Test
    void averageBrightness() {
        assertEquals(smallSquare.averageBrightness(), 2.5, 2.5*.001);
        var bigZero = new GrayscaleImage(new double[1000][1000]);
        assertEquals(bigZero.averageBrightness(), 0);
    }

    @Test
    void normalized() {
        var smallNorm = smallSquare.normalized();
        assertEquals(smallNorm.averageBrightness(), 127, 127*.001);
        var scale = 127/2.5;
        var expectedNorm = new GrayscaleImage(new double[][]{{scale, 2*scale},{3*scale, 4*scale}});
        for(var row = 0; row < 2; row++){
            for(var col = 0; col < 2; col++){
                assertEquals(smallNorm.getPixel(col, row), expectedNorm.getPixel(col, row),
                        expectedNorm.getPixel(col, row)*.001,
                        "pixel at row: " + row + " col: " + col + " incorrect");
            }
        }
    }


    @Test
    void mirrored() {
        var expected = new GrayscaleImage(new double[][]{{2,1},{4,3}});
        assertEquals(smallSquare.mirrored(), expected);
    }


    @Test
    void cropped() {
        var cropped = smallSquare.cropped(1,1,1,1);
        assertEquals(cropped, new GrayscaleImage(new double[][]{{4}}));
    }

    @Test
    void squarified() {
        var squared = smallWide.squarified();
        var expected = new GrayscaleImage(new double[][]{{1,2},{4,5}});
        assertEquals(squared, expected);
    }//test odd

    @Test
    void testGetPixelThrowsOnNegativeX(){
        assertThrows(IllegalArgumentException.class, () -> { smallSquare.getPixel(-1,0);});
    }
    @Test
    void testCroppedThrowsOutBound(){
        assertThrows(IllegalArgumentException.class, () -> { smallSquare.cropped(2,2,6,6);});
    }
    @Test
    void testConstructorWithJaggedArray() {
        // input jagged array to test constructor
        assertThrows(IllegalArgumentException.class, () -> {
            new GrayscaleImage(new double[][]{{1.0, 2.0}, {3.0}});
        });
    }
    @Test
    void normalizedEdgedCase() {
        var smallNorm = allZero.normalized();
        // Assuming that normalization of an all-zero image should result in another all-zero image
        var expectedNorm = new GrayscaleImage(new double[][]{{0, 0}, {0, 0}});

        for (var row = 0; row < 2; row++) {
            for (var col = 0; col < 2; col++) {
                assertEquals(smallNorm.getPixel(col, row), expectedNorm.getPixel(col, row),
                        expectedNorm.getPixel(col, row) * .001,
                        "pixel at row: " + row + " col: " + col + " incorrect");
            }
        }
    }
}
