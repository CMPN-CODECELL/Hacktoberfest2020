import java.util.Arrays;
import java.util.Random;A

public class CountingSort {
  
  //Implementation of Counting Sort
  public static int[] sort(int[] inputArray) {
    int[] countArray = new int[100000];
    int[] sortedArray = new int[inputArray.length];
    Arrays.fill(countArray, 0);
    for (int i = 0; i < inputArray.length; i++) {
      countArray[inputArray[i] - 1]++;
    }
    for (int i = 1; i < countArray.length; i++) {
      countArray[i] += countArray[i - 1];
    }
    for (int i = inputArray.length - 1; i >= 0; i--) {
      sortedArray[countArray[inputArray[i] - 1] - 1] = inputArray[i];
      countArray[inputArray[i] - 1]--;
    }
    return sortedArray;
  }
  
  //Calling sort() function to test Counting Sort
  public static void main(String[] args) {
    Random rd = new Random();
    int[] inputArray = new int[100];
    System.out.println("Input Array:");
    for (int i = 0; i < inputArray.length; i++) {
      inputArray[i] = rd.nextInt(100000) + 1;
      System.out.print(inputArray[i] + " ");
    }
    System.out.println("\nSorted Array:");
    int[] sortedArray = sort(inputArray);
    for (int i = 0; i < sortedArray.length; i++) {
      System.out.print(sortedArray[i] + " ");
    }
  }
  
}
