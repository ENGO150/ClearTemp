package me.engo.cleartemp;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Main {
    //API SETTINGS - CAN BE CHANGED
    public static boolean console = false;
    public static boolean debug = false;

    public static void main(String[] args)
    {
        try
        {
            clearTemp(args);
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    //API VOID
    public static void clearTemp(String[] args) throws IOException
    {
        //VARS
        int usedArgsLength = 0;
        String username = "";
        boolean excex = false;
        int cannotDelete = 0;
        int deleted = 0;
        File blockFile;

        //CHECK IF THERE'S SOME FLAGS
        if (args.length > 0)
        {
            //CONSOLE FLAG
            if (argsContains("-console", args) != null)
            {
                console = true;
                ++usedArgsLength;
            }

            //USERNAME FLAG - WINDOWS TEMP FOLDER FOR USER
            if (argsContains("-username", args) != null)
            {
                //CHECK IF LINUX IS USED
                if (System.getProperty("os.name").equals("Linux"))
                {
                    System.err.println("Username feature cannot be used on Linux!");
                    exit(1);
                }

                username = loadFlagText("-username", args);
                ++usedArgsLength;
            }

            //BLOCK FLAG - PREVENTING TEMP FROM REMOVING BY THIS PROGRAM
            if (argsContains("-block", args) != null)
            {
                blockFile = new File(loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS ALREADY BLOCKED
                if (blockFile.exists())
                {
                    System.err.println("Temp is already blocked!");
                    exit(1);
                }

                //BLOCKING
                Files.createFile(blockFile.toPath());
                System.out.println("Temp files blocked.");
                exit(0);
            }

            //UNBLOCK FLAG - REMOVING BLOCK
            if (argsContains("-unblock", args) != null)
            {
                blockFile = new File(loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS BLOCKED
                if (blockFile.exists())
                {
                    //BLOCKING
                    Files.delete(blockFile.toPath());
                    System.out.println("Temp files unblocked.");
                    exit(0);
                }

                System.err.println("Temp files aren't blocked.");
                exit(1);
            }

            //EXCEX FLAG - EXITING ON ANY DELETING EXCEPTION
            if (argsContains("-excex", args) != null)
            {
                System.out.println("Exiting on exception.\n");
                excex = true;
                ++usedArgsLength;
            }

            //CHECK IF THERE'S SOME BAD ARGS
            if (args.length != usedArgsLength)
            {
                System.err.println("You used some incompatible arguments.");
                exit(1);
            }
        }

        //CHECK IF TEMP IS BLOCKED
        blockFile = loadTemp(username);
        if ((new File(blockFile + "/.blockfile.engo")).exists())
        {
            System.err.println("Temp files are blocked!");
            exit(1);
        }

        assert blockFile != null;

        //CHECK FOR TEMP FOLDER
        if (!blockFile.exists())
        {
            System.err.println("The temp folder doesn't exist!");
            exit(1);
        }

        File[] tempFiles = blockFile.listFiles();

        assert tempFiles != null;

        //GETTING TEMP FILES FROM FOLDER
        for (File file : tempFiles)
        {
            try
            {
                //IS FILE
                if (file.isFile())
                {
                    if (!debug)
                    {
                        Files.delete(file.toPath());
                    }

                    System.out.println("Removed file: " + file.getName());
                    ++deleted;
                } else if (file.isDirectory()) //IS FOLDER
                {
                    if (!debug)
                    {
                        FileUtils.deleteDirectory(file);
                    }

                    System.out.println("Removed directory: " + file.getName());
                    ++deleted;
                } else //CHECK FOR SOME SHIT :)
                {
                    System.out.println("Can't remove: " + file.getName());
                    ++cannotDelete;
                }
            } catch (Exception e)
            {
                System.out.println("Can't remove: " + file.getName());

                //EXCEX FLAG FUNCTION
                if (excex)
                {
                    exit(0);
                }

                ++cannotDelete;
            }
        }

        //FINAL MESSAGE
        System.out.println("\nSuccessfully deleted " + deleted + " files, " + cannotDelete + " files are now probably used and they cannot be removed.");
        exit(0);
    }

    private static File loadTemp(String username)
    {
        //WINDOWS IS USED
        if (System.getProperty("os.name").equals("Windows"))
        {
            if (username.equals(""))
            {
                //RETURNING DEFAULT TEMP FOLDER
                username = System.getProperty("user.name");
            }

            //RETURNING TEMP FOLDER WITH USERNAME FLAG USED
            return new File("C:/Users/" + username + "/Local/Temp");
        } else if (System.getProperty("os.name").equals("Linux")) //LINUX IS USED
        {
            //RETURNING DEFAULT LINUX TEMP FOLDER
            return new File("/tmp");
        } else
        {
            //NOT SUPPORTED OS (PROBABLY MAC)
            System.err.println("Sorry, but this OS isn't supported.");
            exit(0);
            return null;
        }
    }

    private static String loadFlagText(String text, String[] args)
    {
        //GETS ARGS
        for (String arg : args)
        {
            //CHECK IF ARG STARTS WITH FLAG
            if (arg.startsWith(text))
            {
                //RETURNING FLAG TEXT
                return arg.replace(text, "");
            }
        }

        //ERR
        System.err.println("No flag found!");
        exit(1);
        return null;
    }

    private static void exit(int code)
    {
        try
        {
            //CHECK IF CONSOLE IS ENABLED
            if (console)
            {
                System.out.println("\nPress ENTER key to exit: ");
                //WAIT FOR ENTER
                System.in.read();
            }

            //EXIT
            System.exit(code);
        } catch (IOException e)
        {
            e.printStackTrace();
        }

    }

    private static String argsContains(String text, String[] args)
    {
        //GETS ARGS
        for (String arg : args)
        {
            //CHECK IF ARGS CONTAINS TEXT
            if (arg.contains(text))
            {
                //RETURNING USED ARG
                return arg;
            }
        }

        //FALSE
        return null;
    }
}
