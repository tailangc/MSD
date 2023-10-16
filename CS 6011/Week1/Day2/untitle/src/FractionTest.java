import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

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


    @Test
    public void compareTo(){
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        int num1 = f1.compareTo(f2);
        Assertions.assertEquals(num1, 1);
    }

    @Test
    public void testSort(){
        ArrayList<Fraction> fraction = new ArrayList<>();
        Fraction f1 = new Fraction(1, 2);
        Fraction f2 = new Fraction(1, 3);
        Fraction f3 = new Fraction(-3, 9);
        fraction.add(f1);
        fraction.add(f2);
        fraction.add(f3);
        Collections.sort(fraction);
        System.out.println("Sorted list: " + fraction);






    }

}