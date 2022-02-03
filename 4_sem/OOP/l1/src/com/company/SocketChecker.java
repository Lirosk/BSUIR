package com.company;

import com.company.Devices.Device;
import com.company.Factory.DeviceFactory;
import com.company.Factory.DeviceCreator;
import com.company.Factory.Devices;

import java.util.Locale;
import java.util.Scanner;

public class SocketChecker {
    static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        DeviceCreator dc = new DeviceFactory();
        Socket sc = new Socket();

        String buf;
        boolean isGoing = true;
        Device instance;
        Devices chosen;
        float cons;
        int i;

        while (isGoing)
        {
            System.out.println("""
                    'a' to add the device.
                    'n' to switch on the device.
                    'f' to switch off the device.
                    'd' to delete the device.
                    'c' to count the consumption.
                    's' to show all.
                    'q' to exit.
                    """);

            buf = scanner.nextLine().trim().toLowerCase(Locale.ROOT);

            if (!buf.equals(""))
            switch (buf.charAt(0)) {
                case ('a'):
                    System.out.println("""
                            Enter 'f' for flashlight.
                            Enter 'k' for kettle.
                            Enter 'd' for drill
                            """);

                    buf = scanner.nextLine().trim().toLowerCase(Locale.ROOT);
                    chosen = null;

                    switch (buf.charAt(0)) {
                        case ('f') -> chosen = Devices.Flashlight;
                        case ('k') -> chosen = Devices.Kettle;
                        case ('d') -> chosen = Devices.Drill;
                        default -> System.out.println("Wrong input.\n");
                    }

                    if (chosen != null)
                    {
                        System.out.println("Enter consumption: ");
                        buf = scanner.nextLine().trim().toLowerCase(Locale.ROOT);

                        try
                        {
                            cons = Float.parseFloat(buf);
                        }
                        catch (NumberFormatException e)
                        {
                            System.out.println("Wrong format!\n");
                            break;
                        }

                        instance = dc.create(chosen);
                        instance.setConsumption(cons);

                        sc.connected.add(instance);
                        System.out.println("Added.\n");
                    }
                    break;
                case('n'):
                    if (sc.connected.isEmpty())
                    {
                        System.out.println("No connected devices!\n");
                        break;
                    }

                    System.out.println(sc + "\n\n" +
                            "Print number of device to switch on: ");

                    buf = scanner.nextLine();

                    try
                    {
                        i = Integer.parseInt(buf);
                        sc.connected.get(i).switchOn();
                    }
                    catch (NumberFormatException e)
                    {
                        System.out.println("Wrong number format!\n");
                        break;
                    }
                    catch (Exception ex)
                    {
                        System.out.println(ex + "\n");
                        break;
                    }

                    break;
                case ('f'):
                    if (sc.connected.isEmpty())
                    {
                        System.out.println("No connected devices!\n");
                        break;
                    }

                    System.out.println(sc + "\n\n" +
                            "Print number of device to switch off: ");

                    buf = scanner.nextLine();

                    try
                    {
                        i = Integer.parseInt(buf);
                        sc.connected.get(i).switchOff();
                    }
                    catch (NumberFormatException e)
                    {
                        System.out.println("Wrong number format!\n");
                        break;
                    }
                    catch (Exception ex)
                    {
                        System.out.println(ex + "\n");
                        break;
                    }

                    break;
                case('d'):
                    if (sc.connected.isEmpty())
                    {
                        System.out.println("No connected devices!\n");
                        break;
                    }

                    System.out.println(sc + "\n\n" +
                            "Print number of element to delete: ");

                    buf = scanner.nextLine();

                    try
                    {
                        i = Integer.parseInt(buf);
                        sc.connected.remove(i);
                    }
                    catch (NumberFormatException e)
                    {
                        System.out.println("Wrong number format!\n");
                        break;
                    }
                    catch (Exception ex)
                    {
                        System.out.println(ex);
                    }

                    break;
                case('c'):
                    System.out.println("The current energy consumption is: " + sc.calculateConsumption() + "\n");
                    break;
                case ('s'):
                    buf = sc.toString();
                    System.out.println(buf + "\n");
                    break;
                case('q'):
                    isGoing = false;
                    break;
                default:
                    break;
            }

            System.out.println("\n\nPress enter to continue...");
            scanner.nextLine();
        }
    }
}
