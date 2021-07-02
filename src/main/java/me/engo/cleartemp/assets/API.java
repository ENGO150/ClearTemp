package me.engo.cleartemp.assets;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;

public class API
{
    //API SETTINGS (!CHANGING ISN'T RECOMMENDED!)
    public static boolean console;
    public static boolean debug;
    public static boolean exit;

    //API VOID
    public static void clearTemp(String[] args) throws IOException
    {
        if (!Tools.isOsCompatible())
        {
            System.err.println("Sorry, but it seems this OS isn't supported. If you are using supported OS (Windows, Linux), report it here: https://github.com/ENGO150/ClearTemp/issues");
            Tools.exit(1);
        }

        //VARS
        int cannotDelete = 0;
        int deleted = 0;
        int key = Tools.getEncryptionKey();

        File usedFile;
        String username = "";

        boolean excex = false;

        String[] compatibleArgs =
                {       //0        //1         //2      //3        //4      //5      //6
                        "console", "username", "block", "unblock", "excex", "debug", "exit"
                };

        //CHECK FOR INVALID FLAGS
        Tools.loadInvalidFlags(compatibleArgs, args);

        //CHECK IF THERE'S SOME FLAGS
        if (args.length > 0)
        {
            //DEBUG FLAG - DOESN'T ACTUALLY DELETES FILES
            if (Tools.argsContainsFlag(compatibleArgs[5], args) != null)
            {
                System.out.println("Entered debugging mode.");
                debug = true;
            }

            //CONSOLE FLAG
            if (Tools.argsContainsFlag(compatibleArgs[0], args) != null)
            {
                console = true;
            }

            //USERNAME FLAG - WINDOWS TEMP FOLDER FOR USER
            if (Tools.argsContainsFlag(compatibleArgs[1], args) != null)
            {
                //CHECK IF LINUX IS USED
                if (Tools.getOs() == 1)
                {
                    System.err.println("Username feature cannot be used on Linux!");
                    Tools.exit(2);
                }

                username = Tools.loadFlagText(compatibleArgs[1], args);
            }

            //BLOCK FLAG - PREVENTING TEMP FROM REMOVING BY THIS PROGRAM
            if (Tools.argsContainsFlag(compatibleArgs[2], args) != null)
            {
                usedFile = new File(Tools.loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS ALREADY BLOCKED
                if (usedFile.exists())
                {
                    System.err.println("Temp is already blocked!");
                    Tools.exit(3);
                }

                //BLOCKING
                if (!debug)
                {
                    String password = Tools.loadFlagText(compatibleArgs[2], args);

                    Files.createFile(usedFile.toPath());

                    FileWriter fw = new FileWriter(usedFile);
                    StringBuilder newPasswordBuilder = new StringBuilder();

                    assert password != null;
                    for (char character : password.toCharArray())
                    {
                        character += key;
                        newPasswordBuilder.append(character);
                    }

                    fw.write(String.valueOf(newPasswordBuilder));

                    fw.close();

                    Tools.hideFile(usedFile);
                }

                System.out.println("Temp files blocked.");
                Tools.exit(101);
            }

            //UNBLOCK FLAG - REMOVING BLOCK
            if (Tools.argsContainsFlag(compatibleArgs[3], args) != null)
            {
                usedFile = new File(Tools.loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS BLOCKED
                if (usedFile.exists())
                {
                    //UNBLOCKING
                    if (!debug)
                    {
                        Tools.showFile(usedFile);

                        String password = Tools.loadFlagText(compatibleArgs[3], args);
                        List<String> usedPassword = Files.readAllLines(usedFile.toPath());
                        StringBuilder usedPasswordBuilder = new StringBuilder();

                        for (char character : usedPassword.get(0).toCharArray())
                        {
                            character -= key;
                            usedPasswordBuilder.append(character);
                        }

                        assert password != null;
                        if (!(password.equals(String.valueOf(usedPasswordBuilder))))
                        {
                            Tools.hideFile(usedFile);

                            System.err.println("Wrong password!");
                            Tools.exit(4);
                        }

                        Files.delete(usedFile.toPath());
                    }

                    System.out.println("Temp files unblocked.");
                    Tools.exit(102);
                }

                System.err.println("Temp files aren't blocked.");
                Tools.exit(5);
            }

            //EXCEX FLAG - EXITING ON ANY DELETING EXCEPTION
            if (Tools.argsContainsFlag(compatibleArgs[4], args) != null)
            {
                System.out.println("Exiting on exception.");
                excex = true;
            }

            //EXIT FLAG - SHOWS WHY THE PROGRAM IS EXITING
            if (Tools.argsContainsFlag(compatibleArgs[6], args) != null)
            {
                System.out.println("Showing exit reasons.");
                exit = true;
            }

            System.out.print("\n");
        }

        //CHECK IF TEMP IS BLOCKED
        usedFile = Tools.loadTemp(username);
        if ((new File(usedFile + "/.blockfile.engo")).exists())
        {
            System.err.println("Temp files are blocked!");
            Tools.exit(6);
        }

        assert usedFile != null;

        //CHECK FOR TEMP FOLDER
        if (!usedFile.exists())
        {
            System.err.println("The temp folder doesn't exist!");
            Tools.exit(7);
        }

        File[] tempFiles = usedFile.listFiles();

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
                    Tools.exit(103);
                }

                ++cannotDelete;
            }
        }

        //FINAL MESSAGE
        System.out.println("\nSuccessfully deleted " + deleted + " files, " + cannotDelete + " files are now probably used and they cannot be removed.");

        Tools.exit(0);
    }
}