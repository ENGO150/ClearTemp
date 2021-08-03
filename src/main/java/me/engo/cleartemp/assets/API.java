package me.engo.cleartemp.assets;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;
import java.util.Objects;

import static me.engo.cleartemp.assets.Tools.*;

public class API
{
    //API SETTINGS (!CHANGING ISN'T RECOMMENDED!)
    public static boolean console;
    public static boolean debug;
    public static boolean exit;
    public static String lang = "en";

    //API VOID
    public static void clearTemp(String[] args) throws IOException
    {
        if (!isOsCompatible())
        {
            printErrTranslate("not_compatible_os");
            exit(1);
        }

        if (getOs() == 3) // MAC OS
        {
            printTranslate("mac_beta");
            System.out.println("folder >>> " + System.getProperty("java.io.tmpdir"));

            console = true;
            exit = false;

            exit(0);
        }

        //VARS
        int cannotDelete = 0;
        int deleted = 0;
        int key = getEncryptionKey();

        File usedFile;
        String username = "";

        boolean excex = false;

        String[] compatibleArgs =
        {       //0        //1         //2      //3        //4      //5      //6     //7
                "console", "username", "block", "unblock", "excex", "debug", "exit", "language"
        };

        //CHECK FOR INVALID FLAGS
        loadInvalidFlags(compatibleArgs, args);

        //CHECK IF THERE'S SOME FLAGS
        if (args.length > 0)
        {
            //LANGUAGE FLAG - SET LANG
            if (argsContainsFlag(compatibleArgs[7], args) != null)
            {
                String language = Objects.requireNonNull(loadFlagText(compatibleArgs[7], args)).toLowerCase();

                loadInvalidArg(new String[]{"en", "cz"}, language);

                lang = language;

                printTranslate("using_lang");
            }

            //DEBUG FLAG - DOESN'T ACTUALLY DELETES FILES
            if (argsContainsFlag(compatibleArgs[5], args) != null)
            {
                printTranslate("debug");
                debug = true;
            }

            //CONSOLE FLAG
            if (argsContainsFlag(compatibleArgs[0], args) != null)
            {
                printTranslate("console");

                console = true;
            }

            //USERNAME FLAG - WINDOWS TEMP FOLDER FOR USER
            if (argsContainsFlag(compatibleArgs[1], args) != null)
            {
                //CHECK IF LINUX IS USED
                if (getOs() == 1)
                {
                    printErrTranslate("username_linux");
                    exit(2);
                }

                username = loadFlagText(compatibleArgs[1], args);
            }

            //BLOCK FLAG - PREVENTING TEMP FROM REMOVING BY THIS PROGRAM
            if (argsContainsFlag(compatibleArgs[2], args) != null)
            {
                usedFile = new File(loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS ALREADY BLOCKED
                if (usedFile.exists())
                {
                    printErrTranslate("temp_already_blocked");
                    exit(3);
                }

                //BLOCKING
                if (!debug)
                {
                    String password = loadFlagText(compatibleArgs[2], args);

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

                    hideFile(usedFile);
                }

                printTranslate("temp_blocked");
                exit(101);
            }

            //UNBLOCK FLAG - REMOVING BLOCK
            if (argsContainsFlag(compatibleArgs[3], args) != null)
            {
                usedFile = new File(loadTemp(username) + "/.blockfile.engo");

                //CHECK IF TEMP IS BLOCKED
                if (usedFile.exists())
                {
                    //UNBLOCKING
                    if (!debug)
                    {
                        showFile(usedFile);

                        String password = loadFlagText(compatibleArgs[3], args);
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
                            hideFile(usedFile);

                            printErrTranslate("wrong_password");
                            exit(4);
                        }

                        Files.delete(usedFile.toPath());
                    }

                    printTranslate("temp_unblocked");
                    exit(102);
                }

                printErrTranslate("temp_already_unblocked");
                exit(5);
            }

            //EXCEX FLAG - EXITING ON ANY DELETING EXCEPTION
            if (argsContainsFlag(compatibleArgs[4], args) != null)
            {
                printTranslate("excex");
                excex = true;
            }

            //EXIT FLAG - SHOWS WHY THE PROGRAM IS EXITING
            if (argsContainsFlag(compatibleArgs[6], args) != null)
            {
                printTranslate("exit");
                exit = true;
            }

            System.out.print("\n");
        }

        //CHECK IF TEMP IS BLOCKED
        usedFile = loadTemp(username);
        if ((new File(usedFile + "/.blockfile.engo")).exists())
        {
            printErrTranslate("temp_blocked_err");
            exit(6);
        }

        assert usedFile != null;

        //CHECK FOR TEMP FOLDER
        if (!usedFile.exists())
        {
            printErrTranslate("temp_folder_err");
            exit(7);
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

                    System.out.println(getTranslate("removed_file") + file.getName());
                    ++deleted;
                } else if (file.isDirectory()) //IS FOLDER
                {
                    if (!debug)
                    {
                        FileUtils.deleteDirectory(file);
                    }

                    System.out.println(getTranslate("removed_directory") + file.getName());
                    ++deleted;
                } else //CHECK FOR SOME SHIT :)
                {
                    System.out.println(getTranslate("cant_remove") + file.getName());
                    ++cannotDelete;
                }
            } catch (Exception e)
            {
                System.out.println(getTranslate("cant_remove") + file.getName());

                //EXCEX FLAG FUNCTION
                if (excex)
                {
                    exit(103);
                }

                ++cannotDelete;
            }
        }

        //FINAL MESSAGE
        System.out.println(getTranslate("final").replace("{DELETED}", String.valueOf(deleted)).replace("{CANNOT}", String.valueOf(cannotDelete)));

        exit(0);
    }
}