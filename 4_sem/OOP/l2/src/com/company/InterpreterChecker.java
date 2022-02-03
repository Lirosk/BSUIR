package com.company;

import com.company.Client.Client;
import com.company.Complex.Complex;

import java.util.Scanner;

public class InterpreterChecker {
    static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("Enter expression: ");
        String expression = scanner.nextLine();

        Client interpreter = new Client(expression);
        Complex res = interpreter.calculate();

        System.out.println("[ " + expression + " ] = " + res);
    }
}
