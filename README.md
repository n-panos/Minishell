# Minishell
Minishell 42 proyect

## Git guide & commands

Comandos necesarios para trabajar en varias branch en git.


### Commands:

git branch	-> check de la rama en la que estás.

git checkout 'name'	-> cambias de branch. Name puede ser main o el nombre de branch,
                    	la flag "-b 'name' " crea branch nueva.

### Basicos:

git push origin 'name'->	push a una branch	

git add

git reset "filename" ->		deshacer git add "file"

git commit -m "comment"

git status

git log

.gitignore

### Bash test

heredoc:

<<eof >salida -> no saca nada, heredoc es un almacen temporal

cat <<eof >salida	-> mete a salida lo estrito en el heredoc

ls <<eof >salida	->obvia heredoc y saca por salida solo ls

->heredoc es la combinacion de cat + <<

## Referencias :

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf