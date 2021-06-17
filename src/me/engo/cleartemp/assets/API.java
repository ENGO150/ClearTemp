package me.engo.cleartemp.assets;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;

public class API
{
    //API SETTINGS - CAN BE CHANGED
    public static boolean console = false;
    public static boolean debug = false;

    //API VOID
    public static void clearTemp(String[] args) throws IOException
    {
        if (!Tools.isOsCompatible())
        {
            System.err.println("Sorry, but it seems this OS isn't supported. If you are using supported OS (Windows, Linux), report it here: https://github.com/ENGO150/ClearTemp/issues");
            Tools.exit(1);
        }

        //VARS
        int usedArgsLength = 0;
        String username = "";
        boolean excex = false;
        int cannotDelete = 0;
        int deleted = 0;
        File blockFile;
        int key = Tools.getEncryptionKey();

        //CHECK IF THERE'S SOME FLAGS
        if (args.length > 0)
        {
            //CONSOLE FLAG
            if (Tools.argsContainsFlag("console", args) != null)
            {
                console = true;
                ++usedArgsLength;
            }

            //USERNAME FLAG - WINDOWS TEMP FOLDER FOR USER
            if (Tools.argsContainsFlag("username", args) != null)
            {
                //CHECK IF LINUX IS USED
                if (System.getProperty("os.name").equals("Linux"))
                {
                    System.err.println("Username feature cannot be used on Linux!");
                    Tools.exit(1);
                }

                username = Tools.loadFlagText("username", args);
                ++usedArgsLength;
            }

            //BLOCK FLAG - PREVENTING TEMP FROM REMOVING BY THIS PROGRAM
            if (Tools.argsContainsFlag("block", args) != null)
            {
                blockFile = new File(Tools.loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS ALREADY BLOCKED
                if (blockFile.exists())
                {
                    System.err.println("Temp is already blocked!");
                    Tools.exit(1);
                }

                //BLOCKING
                String password = Tools.loadFlagText("block", args);

                Files.createFile(blockFile.toPath());
                Tools.hideFile(blockFile);

                FileWriter fw = new FileWriter(blockFile);
                StringBuilder newPasswordBuilder = new StringBuilder();

                assert password != null;
                for (char character : password.toCharArray())
                {
                    character += key;
                    newPasswordBuilder.append(character);
                }

                fw.write(String.valueOf(newPasswordBuilder));

                fw.close();

                System.out.println("Temp files blocked.");
                Tools.exit(0);
            }

            //UNBLOCK FLAG - REMOVING BLOCK
            if (Tools.argsContainsFlag("unblock", args) != null)
            {
                blockFile = new File(Tools.loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS BLOCKED
                if (blockFile.exists())
                {
                    //BLOCKING
                    Tools.makeFileReadable(blockFile);

                    String password = Tools.loadFlagText("unblock", args);
                    List<String> usedPassword = Files.readAllLines(blockFile.toPath());
                    StringBuilder usedPasswordBuilder = new StringBuilder();

                    for (char character : usedPassword.get(0).toCharArray())
                    {
                        character -= key;
                        usedPasswordBuilder.append(character);
                    }

                    assert password != null;
                    if (!(password.equals(String.valueOf(usedPasswordBuilder))))
                    {
                        Tools.hideFile(blockFile);

                        System.err.println("Wrong password!");
                        Tools.exit(1);
                    }

                    Files.delete(blockFile.toPath());
                    System.out.println("Temp files unblocked.");
                    Tools.exit(0);
                }

                System.err.println("Temp files aren't blocked.");
                Tools.exit(1);
            }

            //EXCEX FLAG - EXITING ON ANY DELETING EXCEPTION
            if (Tools.argsContainsFlag("excex", args) != null)
            {
                System.out.println("Exiting on exception.\n");
                excex = true;
                ++usedArgsLength;
            }

            //DEBUG FLAG - DOESN'T ACTUALLY DELETES FILES
            if (Tools.argsContainsFlag("debug", args) != null)
            {
                System.out.println("Entered debugging mode.\n");
                debug = true;
                ++usedArgsLength;
            }

            //CHECK IF THERE'S SOME BAD ARGS
            if (args.length != usedArgsLength)
            {
                System.err.println("You used some incompatible arguments.");
                Tools.exit(1);
            }
        }

        //CHECK IF TEMP IS BLOCKED
        blockFile = Tools.loadTemp(username);
        if ((new File(blockFile + "/.blockfile.engo")).exists())
        {
            System.err.println("Temp files are blocked!");
            Tools.exit(1);
        }

        assert blockFile != null;

        //CHECK FOR TEMP FOLDER
        if (!blockFile.exists())
        {
            System.err.println("The temp folder doesn't exist!");
            Tools.exit(1);
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
                    Tools.exit(0);
                }

                ++cannotDelete;
            }
        }

        //FINAL MESSAGE
        System.out.println("\nSuccessfully deleted " + deleted + " files, " + cannotDelete + " files are now probably used and they cannot be removed.");
        Tools.exit(0);
    }
}
