package me.engo.cleartemp.assets;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.LinkOption;
import java.util.List;
import java.util.Random;

public class Tools
{
    static File loadTemp(String username)
    {
        //WINDOWS IS USED
        if (System.getProperty("os.name").equals("Windows"))
        {
            if (username.equals(""))
            {
                //RETURNING DEFAULT TEMP FOLDER
                username = getUser();
            }

            //RETURNING TEMP FOLDER WITH USERNAME FLAG USED
            return new File("C:/Users/" + username + "/Local/Temp");
        } else if (System.getProperty("os.name").equals("Linux")) //LINUX IS USED
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

    static int getEncryptionKey()
    {
        try
        {
            File configFile = null;

            if (System.getProperty("os.name").equals("Windows"))
            {
                configFile = new File("C:/Users/" + getUser() + "/.hideconfig.engo");
            } else if (System.getProperty("os.name").equals("Linux"))
            {
                configFile = new File("/home/" + getUser() + "/.hideconfig.engo");
            }

            assert configFile != null;
            if (!configFile.exists())
            {
                Files.createFile(configFile.toPath());
                hideFile(configFile);

                FileWriter fw = new FileWriter(configFile);
                int random = new Random().nextInt(100);

                fw.write(String.valueOf(random));
                fw.close();

                return random;
            } else
            {
                makeFileReadable(configFile);

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
        try
        {
            Files.setAttribute(file.toPath(), "dos:hidden", Boolean.TRUE, LinkOption.NOFOLLOW_LINKS);
            boolean success = file.setReadable(false);

            if (!success)
            {
                System.err.println("Configuring file went wrong!");
                exit(1);
            }
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    static void makeFileReadable(File file)
    {
        boolean success = file.setReadable(true);

        if (!success)
        {
            System.err.println("Configuring file went wrong!");
            exit(1);
        }
    }

    static String getUser()
    {
        return System.getProperty("user.name");
    }

    static boolean isOsCompatible()
    {
        return System.getProperty("os.name").equals("Windows") || System.getProperty("os.name").equals("Linux");
    }
}
