package com.example.thread;

//class MyRunnable implements Runnable {
//    @Override
//    public void run() {
////        System.out.println("hello number " + Thread.currentThread().getId());
//    }
//}

public class ThreadExample {
    static int answer;
    public static void main(String[] args) {
//        sayHello();
        badSum(1); // 用一个线程测试
        badSum(10); // 用多线程测试
    }
    public static void badSum(int numThreads){
        answer = 0;
        int maxValue = 4000;
        Thread[] threads = new Thread[numThreads];
        for(int i = 0; i < numThreads; i++){
            final int finalI = i;
            threads[i] = new Thread(()->{
                for (int count = finalI * maxValue / numThreads; count < Math.min((finalI + 1) * maxValue / numThreads, maxValue); count++) {
                    answer += count;
                }
            });
            threads[i].start();
        }
        for(int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        int correctAnswer = (maxValue * (maxValue + 1)) / 2; // 因为包括了maxValue，所以使用+1，而不是-1。
        System.out.println("Computed answer: " + answer);
        System.out.println("Correct answer: " + correctAnswer);

    }
    public static void sayHello(){
        // 使用循环创建并启动线程
        final int NUM_THREADS = 10;  // 你可以根据需要更改这个值
        final int MAX_COUNT = 100;
        Thread[] threads = new Thread[NUM_THREADS];
        for (int i = 0; i < NUM_THREADS; i++) {
            threads[i] = new Thread(() ->{ //lambda
                for (int j = 1; j <= MAX_COUNT; j++) {
                    System.out.println("hello number " + j + " from thread number " + Thread.currentThread().getId());
                    // 每10个hello之后打印一个换行符
                    if (j % 10 == 0) {
                        System.out.print("\n");
                    } else {
                        System.out.print(" ");  // 使用print而不是println
                    }
                }
            });
            System.out.println("hello number " + i + Thread.currentThread().getId());
            threads[i].start();
        }

        // 等待所有线程运行结束
        for (int i = 0; i < NUM_THREADS; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}