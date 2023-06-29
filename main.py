import solver
import time
import pywinauto.keyboard as keyboard


if __name__ == "__main__":
    solver.init()
    w = input("Enter the word: ")
    if len(w) != 6 and not w.isalpha():
        print("Word must be 6 characters long")
        exit(1)
    l = sorted(solver.findall(w), key=len)
    print("Found {} words".format(len(l)))
    print("Please switch to the game window in 10 seconds")
    time.sleep(10)
    for i in l:
        for j in i:
            keyboard.send_keys(j)
            time.sleep(0.2)
        keyboard.send_keys("{ENTER}")
        time.sleep(0.2)
