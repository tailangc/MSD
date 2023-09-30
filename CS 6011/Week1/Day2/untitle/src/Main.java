// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {

    public static void main(String[] args) {
        try {
            Fraction fraction1 = new Fraction(8, 12);
            Fraction fraction2 = new Fraction(2, 4);
            System.out.println("Fraction 1 is :" + fraction1);
            System.out.println("Fraction 2 is :" + fraction2);
            System.out.println("sum is : " + fraction1.plus(fraction2));
            System.out.println("if Fraction 1 minus Fraction 2:" + fraction1.minus(fraction2));
            System.out.println("if Fraction 1 times Fraction 2:" + fraction1.times(fraction2));
            System.out.println("if Fraction 1 dividedBy Fraction 2:" + fraction1.dividedBy(fraction2));
            System.out.println("reciprocal:" + fraction1.reciprocal() + " " + fraction2.reciprocal());
            System.out.println("change to string :" + fraction1.toString() + " " + fraction2.toString());
            System.out.println("Double value:" + fraction1.toDouble() + " " + fraction2.toDouble());
        }
        catch (RuntimeException e){
            System.out.println("Exception message:" + e.getMessage());
        }
    }
}