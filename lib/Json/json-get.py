import json
import sys

def main():
    with open("../../res/" + sys.argv[1] + ".json", "r") as f:
        data = f.read()

    obj = json.loads(data)

    print(str(obj[sys.argv[2]])) #TODO: Implement

if __name__ == "__main__":
    main();
