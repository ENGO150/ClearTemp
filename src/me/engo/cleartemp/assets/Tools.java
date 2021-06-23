package me.engo.cleartemp.assets;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.LinkOption;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Tools
{
    static File loadTemp(String username)
    {
        //WINDOWS IS USED
        if (getOs() == 2)
        {
            if (username.equals(""))
            {
                //RETURNING DEFAULT TEMP FOLDER
                username = getUser();
            }

            //RETURNING TEMP FOLDER WITH USERNAME FLAG USED
            return new File("C:/Users/" + username + "/AppData/Local/Temp");
        } else if (getOs() == 1) //LINUX IS USED
        {
            //RETURNING DEFAULT LINUX TEMP FOLDER
            return new File("/tmp");
        }

        return null;
    }

    static String loadFlagText(String text, String[] args)
    {
        text = "-" + text;

        //GETS ARGS
        for (String arg : args)
        {
            //CHECK IF ARG STARTS WITH FLAG
            if (arg.startsWith(text))
            {
                //RETURNING FLAG TEXT
                String returning = arg.replace(text + ":", "");

                if (returning.equals("") || returning.equals(text))
                {
                    System.err.println("No flag text found!");
                    exit(1);
                }

                return returning;
            }
        }

        //ERR
        System.err.println("No flag found!");
        exit(1);
        return null;
    }

    @SuppressWarnings("all")
    static void exit(int code)
    {
        try
        {
            //CHECK IF CONSOLE IS ENABLED
            if (API.console)
            {
                System.out.println("\nPress ENTER to exit: ");
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

    static String argsContainsFlag(String text, String[] args)
    {
        text = "-" + text;
        boolean error = false;
        String returning = null;

        //GETS ARGS
        for (String arg : args)
        {
            //CHECK IF ARGS CONTAINS TEXT
            if (arg.contains(text))
            {
                //IS DOUBLE-USED
                if (error)
                {
                    System.err.println("The '" + text.substring(1) + "' flag is used more than once!");
                    exit(1);
                }

                //RETURNING USED ARG
                returning = arg;
                error = true;
            }
        }

        //RETURN
        return returning;
    }

    static int getEncryptionKey()
    {
        try
        {
            File configFile = null;

            //WINDOWS
            if (System.getProperty("os.name").startsWith("Windows"))
            {
                configFile = new File("C:/Users/" + getUser() + "/.hideconfig.engo");
            } else if (System.getProperty("os.name").equals("Linux")) //LINUX
            {
                configFile = new File("/home/" + getUser() + "/.hideconfig.engo");
            }

            assert configFile != null;
            //CREATING
            if (!configFile.exists())
            {
                System.out.println("Creating new config file.\n");

                Files.createFile(configFile.toPath());

                FileWriter fw = new FileWriter(configFile);

                int random = new Random().nextInt(100);

                fw.write(String.valueOf(random));
                fw.close();

                hideFile(configFile);

                return random;
            } else //GETTING
            {
                showFile(configFile);

                List<String> lines = Files.readAllLines(configFile.toPath());

                hideFile(configFile);

                return Integer.parseInt(lines.get(0));
            }
        } catch (IOException e)
        {
            e.printStackTrace();
        }

        return 0;
    }

    static void hideFile(File file)
    {
        editFile(file, true);
    }

    static void showFile(File file)
    {
        editFile(file, false);
    }

    static String getUser()
    {
        return System.getProperty("user.name");
    }

    static boolean isOsCompatible()
    {
        return getOs() != 0;
    }

    static int getOs()
    {
        String osName = System.getProperty("os.name").toLowerCase();
        if (osName.contains("linux"))
        {
            return 1;
        } else if (osName.contains("windows"))
        {
            return 2;
        } else
        {
            return 0;
        }
    }

    static void editFile(File file, boolean hide)
    {
        try
        {
            if (getOs() == 1)
            {
                boolean success;
                hide = !hide;

                success = file.setReadable(hide);
                if (!file.setExecutable(hide)) success = false;

                if (!success)
                {
                    System.err.println("Configuring file went wrong!");
                    exit(1);
                }
            } else if (getOs() == 2)
            {
                Files.setAttribute(file.toPath(), "dos:hidden", hide, LinkOption.NOFOLLOW_LINKS);
                Files.setAttribute(file.toPath(), "dos:readonly", hide, LinkOption.NOFOLLOW_LINKS);
            }
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    static void loadInvalidFlags(String[] allowed, String[] args)
    {
        //NO FLAGS
        if (args.length == 0) return;

        //INVALID
        if (Arrays.toString(args).contains("_"))
        {
            System.err.println("You used invalid character! ('_')");
            exit(1);
        }

        //VARS
        List<String> remainingArgs = new ArrayList<>(Arrays.asList(args));

        //REPLACING
        for (String allowedArg : allowed)
        {
            remainingArgs.removeIf(n -> (n.startsWith("-" + allowedArg)));
        }

        //TO STRING
        String invalidArg = remainingArgs.toString().substring(1, remainingArgs.toString().length() - 1);

        //WORKING FLAGS
        if (invalidArg.equals("")) return;

        //GET FIRST ERROR
        invalidArg = invalidArg.split(":")[0];

        //EXIT
        System.err.println("You used invalid flag(s)! ('" + invalidArg + "')");
        exit(1);
    }
}
