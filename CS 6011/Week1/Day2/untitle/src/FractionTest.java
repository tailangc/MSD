import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
class FractionTest {
    @Test
    public void runATest() {
        // Qualify the assertEquals() with "Assertions." to say that it comes from the Assertions library.
        // Assertions library, as can be seen from the import, is: org.junit.jupiter.api.Assertions.
        Assertions.assertEquals(3, 3); // Dummy assert... put real code here.
//        testPlus();
//        testMinus();
//        testTimes();
//        testDivide();
//        testString();
    }

    @Test
    public void testPlus() {
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = f1.plus(f2);

        Assertions.assertEquals(f3.toString(), "5/6");
    }

    @Test
    public void testMinus() {
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = f1.minus(f2);

        Assertions.assertEquals(f3.toString(), "1/6");
    }


    @Test
    public void testTimes() {
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = f1.times(f2);

        Assertions.assertEquals(f3.toString(), "1/6");
    }

    @Test
    public void testDivide() {
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = f1.dividedBy(f2);

        Assertions.assertEquals(f3.toString(), "3/2");
    }

//    @Test
//    public void testDivide() {
//        Fraction f1 = new Fraction(1,2 );
//        Fraction f2 = new Fraction( 1, 3 );
//        Fraction f3 = f1.dividedBy( f2 );
//
//        Assertions.assertEquals( f3.toString(), "3/2" );
//    }

//    public void testString() {
//        Fraction f1 = new Fraction(1,-2 );
//        String str = f1.toString();
//        Assertions.assertEquals( str, "-1/2" );
//    }


}