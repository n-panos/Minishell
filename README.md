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

git commit -m "comment"

git status

git log
	git log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)' --all


## Referencias :

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf