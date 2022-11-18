CC = gcc
EXEC = prog
# Fichiers sources = ceux finissant par .c
SRC = $(wildcard *.c)
# Fichiers objets = source en remplaçant .c par .o
OBJ = $(SRC:.c=.o)

all : $(EXEC) 

%.o : %.c
	$(CC) -g -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -g -o $@ $^

clean :
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC) *.zip debug

zip : 
	zip $(EXEC).zip *.c *.h Makefile *.csv *.txt

# COMMENT DEBUGGER AVEC GDB ?
# Dans %.o et $(EXEC) on rajoute une option -g dans la commande juste après $(CC)
# Ensuite on lance le debug avec la commande
# gdb prog
# Enfin on rentre "r" puis Entrée. 
# A la fin du debuggage, ne pas oublier d'enlever le -g
# afficher le contenu d'une variable : p <variable>

# UTILISATION DES VARIABLES AUTOMATIQUES :
# /!\ Attention l'ordre compte /!\
# $@ = target file 
# $< nom du premier prérequis (en gros)
# $^ nom(s) de tout(s) le(s) prérequis