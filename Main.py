import os
import shutil
import sys
import tempfile


class Variables:
    deleted = 0
    cannot_delete = 0


def main():
    used_args_length = 1

    username = ""
    console = False

    # if len(sys.argv) > 1:
    #     if sys.argv.__contains__("-console"):
    #         console = True
    #
    #     if not console and len(sys.argv) == 3:
    #         if sys.argv[1] == "-console":
    #             username = sys.argv[2]
    #         else:
    #             username = sys.argv[1]
    #     elif len(sys.argv) > 3:
    #         print("Too much arguments!")
    #         exit(1)

    if len(sys.argv) > 1:
        if args_contains("-console"):
            console = True
            used_args_length += 1

        if args_contains("-username:"):
            username = load_flag_text("-username:")
            used_args_length += 1

        if args_contains("-block"):
            if os.path.exists(load_temp(username) + "/.blockfile.cleartemp"):
                print("Temp is already blocked.")
                exit(1)
            open(load_temp(username) + "/.blockfile.cleartemp", "w")
            print("Temp files blocked.")
            exit(0)

        if args_contains("-unblock"):
            if os.path.exists(load_temp(username) + "/.blockfile.cleartemp"):
                os.remove(load_temp(username) + "/.blockfile.cleartemp")
                print("Temp files unblocked.")
                exit(0)
            print("Temp isn't blocked.")
            exit(1)

        if len(sys.argv) != used_args_length:
            print("You used some incompatible arguments.")
            exit(1)

    if os.path.exists(load_temp(username) + "/.blockfile.cleartemp"):
        print("Temp files are blocked!")
        exit(1)

    temp_folder = load_temp(username)

    if not os.path.exists(temp_folder):
        print("The temp folder doesn't exist!")
        exit(1)

    temp_files = os.listdir(temp_folder)

    for file in temp_files:
        file = tempfile.gettempdir() + "/" + file

        try:
            if os.path.isfile(file):
                os.remove(file)
                Variables.deleted += 1
                print("Removed file: " + file)
            elif os.path.isdir(file):
                shutil.rmtree(file)
                Variables.deleted += 1
                print("Removed folder: " + file)
            else:
                print("Can't remove: " + file)
        except IOError as e:
            print("Can't remove: " + str(e))
            Variables.cannot_delete += 1

    print("\nSuccessfully deleted " + str(Variables.deleted) + " files, but " + str(Variables.cannot_delete) +
          " files are now probably used and they cannot be removed.")

    if console:
        os.system("pause")


def load_temp(username):
    try:
        if username == "":
            return tempfile.gettempdir()
        else:
            return "C:/Users/" + username + "/AppData/Local/Temp"
    except IOError:
        print("Wrong user.")
        exit(1)


def load_flag_text(text):
    for arg in sys.argv:
        if arg.startswith(text):
            return arg.replace(text, "")


def args_contains(text):
    for arg in sys.argv:
        if arg.__contains__(text):
            return arg
    return False


if __name__ == "__main__":
    main()
