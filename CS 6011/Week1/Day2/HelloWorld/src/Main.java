import java.util.ArrayList;
import java.util.Scanner;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        // Press Opt+Enter with your caret at the highlighted text to see how
        // IntelliJ IDEA suggests fixing it.
        System.out.println("Hello World!");

        int [] numbers = {1,12,14,54,34,65,32,3,5,6};
        int sum = 0;
        for (int i = 0; i<9 ; i++){
            sum += numbers[i];
            System.out.println(numbers[i]);
        }
        System.out.println("The sum of the array is " + sum);

        Scanner n = new Scanner(System.in);
        System.out.println("Please input your name:");
        String name = n.nextLine();
        Scanner a = new Scanner(System.in);
        System.out.println("Please enter your age:");
        int age = a.nextInt();
        if(age < 18){
            System.out.println("You are an iGen. You are not old enough to vote.");
        } else if (age >= 18 && age <= 24) {
            System.out.println("You are an iGen. You are old enough to vote.");
        } else if (age > 24 && age <= 40) {
            System.out.println("You are a millennial. You are old enough to vote.");
        } else if (age > 40 && age <=56) {
            System.out.println("You are an gen X. You are old enough to vote.");
        } else {
            System.out.println("You are a boomer. You are old enough to vote.");
        }





        // Press Ctrl+R or click the green arrow button in the gutter to run the code.
//        for (int i = 1; i <= 5; i++) {

            // Press Ctrl+D to start debugging your code. We have set one breakpoint
            // for you, but you can always add more by pressing Cmd+F8.
//            System.out.println("i = " + i);
    }
}
