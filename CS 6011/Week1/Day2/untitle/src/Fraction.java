public class Fraction {
    long numerator;
    long denominator;

    public Fraction(){
        numerator = 0;
        denominator = 1;
    }

    
    public Fraction(long n, long d){
        numerator = n;
        denominator = d;
        reduce();
    }

    public Fraction plus(Fraction rhs){
        long newNum, newDeno;
        newNum = numerator * rhs.denominator + denominator * rhs.numerator;
        newDeno = denominator * rhs.denominator;
        return new Fraction (newNum, newDeno);
    }

    public Fraction minus(Fraction rhs){
        long newNum, newDeno;
        newNum = numerator * rhs.denominator - denominator * rhs.numerator;
        newDeno = denominator * rhs.denominator;
        return new Fraction (newNum, newDeno);
    }

    public Fraction times(Fraction rhs){
        long newNum, newDeno;
        newNum = numerator * rhs.numerator;
        newDeno = denominator * rhs.denominator;
        return new Fraction (newNum, newDeno);
    }

    public Fraction dividedBy(Fraction rhs){
        long newNum, newDeno;
        newNum = numerator * rhs.denominator;
        newDeno = denominator * rhs.numerator;
        return new Fraction (newNum, newDeno);
    }

    public Fraction reciprocal(){
        long newNum, newDeno;
        newNum = denominator;
        newDeno = numerator;
        return new Fraction (newNum, newDeno);
    }

    public long GCD(){
        long gcd = numerator;
        long remainder = denominator;
        while( remainder != 0 ) {
            long temp = remainder;
            remainder = gcd % remainder;
            gcd = temp;
        }
        return gcd;
    }

    public void reduce(){
        long gcd = GCD();
        numerator = numerator / gcd;
        denominator = denominator / gcd;
    }

    public String toString(){
        reduce();
        String strFrac = "";
        if (numerator < 0 && denominator > 0){
            strFrac = "-";
        } else if (numerator > 0 && denominator < 0) {
            strFrac = "-";
            denominator = -denominator;
        }
        strFrac = strFrac + numerator + "/" + denominator;
        return strFrac;
    }

    public double toDouble(){
        double doubleFrac;
        doubleFrac = numerator / denominator;
        return doubleFrac;
    }


}
