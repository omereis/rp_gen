#
#    ABSim.PY
# Alpha / Beta signal simulator
#
#import os, sys, zipfile
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
def print_menu (aszMenu):
    for opt in aszMenu:
        print(opt)
#------------------------------------------------------------------------------
def main ():
    main_menu = ['1 - Setup','2 - Generate','3 - Start', 'q - Quit','']
    cmd = ''
    while (cmd != '4'):
        print_menu (main_menu)
        cmd = input()
        
#------------------------------------------------------------------------------
if __name__ == "__main__":
    main ()
