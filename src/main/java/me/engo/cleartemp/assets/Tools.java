package me.engo.cleartemp.assets;

import com.google.gson.JsonParser;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.LinkOption;
import java.util.*;

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
                    printErrTranslate("no_flag_text");
                    exit(8);
                }

                return returning;
            }
        }

        //ERR
        printErrTranslate("no_flag");
        exit(9);
        return null;
    }

    @SuppressWarnings("all")
    static void exit(int code)
    {
        if (API.exit)
        {
            //VAR
            String reason = "";

            //GETTING REASON
            switch (code)
            {
                //GOOD
                case 103:
                    reason = getTranslate("excex_exit");
                    break;
                case 102:
                    reason = getTranslate("temp_unblocked_exit");
                    break;
                case 101:
                    reason = getTranslate("temp_blocked_exit");
                    break;
                case 0:
                    reason = getTranslate("temp_deleted_exit");
                    break;

                //BAD
                case 1:
                    reason = getTranslate("not_compatible_os_exit");
                    break;
                case 2:
                    reason = getTranslate("username_linux_exit");
                    break;
                case 3:
                    reason = getTranslate("temp_already_blocked_exit");
                    break;
                case 4:
                    reason = getTranslate("wrong_password_exit");
                    break;
                case 5:
                    reason = getTranslate("temp_already_unblocked_exit");
                    break;
                case 6:
                    reason = getTranslate("temp_blocked_err_exit");
                    break;
                case 7:
                    reason = getTranslate("temp_folder_err_exit");
                    break;
                case 8:
                    reason = getTranslate("no_flag_text_exit");
                    break;
                case 9:
                    reason = getTranslate("no_flag_exit");
                    break;
                case 10:
                    reason = getTranslate("flag_used_exit");
                    break;
                case 11:
                    reason = getTranslate("edit_file_exit");
                    break;
                case 12:
                    reason = getTranslate("invalid_flag_exit");
                    break;
                case 13:
                    reason = getTranslate("invalid_arg_exit");
                    break;
                case 14:
                    reason = getTranslate("invalid_json_exit");
                    break;

                //ELSE
                default:
                    reason = getTranslate("reason_exit");
                    break;
            }

            //MESSAGE
            System.out.println(getTranslate("console_exit").replace("{CODE}", String.valueOf(code)) + reason);
        }

        if ((new Random().nextInt(100) > 75) && (code == 0 || code > 100))
        {
            System.out.print(getTranslate("thanks"));

            if (new Random().nextInt(1000) == 420)
            {
                printTranslate("look");
            }
        }

        try
        {
            //CHECK IF CONSOLE IS ENABLED
            if (API.console)
            {
                printTranslate("press_enter");
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
                    System.err.println(getTranslate("flag_used").replace("{FLAG}", text.substring(1)));
                    exit(10);
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
            if (Tools.getOs() == 2)
            {
                configFile = new File("C:/Users/" + getUser() + "/.hideconfig.engo");
            } else if (Tools.getOs() == 1) //LINUX
            {
                configFile = new File("/home/" + getUser() + "/.hideconfig.engo");
            }

            assert configFile != null;
            //CREATING
            if (!configFile.exists())
            {
                printTranslate("creating_config");

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
        } else if (osName.contains("mac")) //JUST BETA
        {
            return 3;
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
                    printErrTranslate("edit_file");
                    exit(11);
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
            printErrTranslate("invalid_char");
            exit(12);
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
        System.err.println(getTranslate("invalid_flag").replace("{FLAG}", invalidArg));
        exit(12);
    }

    //GET TRANSLATE
    static String getTranslate(String object)
    {
        String returning = null;

        try
        {
            returning = JsonParser.parseReader(new InputStreamReader(Objects.requireNonNull(Thread.currentThread().getContextClassLoader().getResourceAsStream(API.lang + ".json")))).getAsJsonObject().get(object).getAsString();
        } catch (NullPointerException e)
        {
            System.err.println(getTranslate("invalid_json").replace("{OBJECT}", object));
            exit(14);
        }

        return returning;
    }

    //PRINT TRANSLATE
    static void printTranslate(String object)
    {
        System.out.println(getTranslate(object));
    }

    //PRINT ERR TRANSLATE
    static void printErrTranslate(String object)
    {
        System.err.println(getTranslate(object));
    }

    //CHECK IF ARG IS IN ALLOWED
    static void loadInvalidArg(String[] allowed, String arg)
    {
        List<String> allowedList = Arrays.asList(allowed);
        if (!allowedList.contains(arg))
        {
            System.out.println(getTranslate("invalid_arg").replace("{ARG}", arg));
            exit(13);
        }
    }
}