// Program to display the Fibonacci Series in Java

import java.io.*;

public class Fibonacci {
    public static void main (String args[]) throws IOException {
        InputStreamReader read = new InputStreamReader(System.in);
        BufferedReader in = new BufferedReader(read);

        System.out.println("Enter the value of 'n'");
        int n = Integer.parseInt(in.readLine());

        int c=0; // Counter variable
        int n1=0, n2=1; // First two numbers of the series
        int n_sum; // Temporary variable for storing the sum of n1 and n2

        if (n <= 0) {
            System.out.println("Invalid! Enter a positive number");
        }
        else if (n == 1) {
            System.out.println("Fibonacci series upto " + n + " : " + n1);
        }
        else {
            System.out.println("Fibonacci series :");
            while (c < n) {
                System.out.println(n1);
                n_sum = n1 + n2;
                n1 = n2; n2 = n_sum;
                c += 1;
            }
        }
    }
}
