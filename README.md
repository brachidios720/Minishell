## Minishell — `README.md`

```md
# Minishell

Mini shell UNIX développé en C dans le cadre du cursus 42.

## À propos

`Minishell` reproduit une partie du comportement d’un shell comme Bash.

Le projet couvre notamment :
- le parsing d’une ligne de commande,
- l’exécution de commandes,
- la gestion des pipes,
- les redirections,
- les variables d’environnement,
- certains builtins.

## Fonctionnalités

- exécution de commandes simples
- support des pipes
- redirections d’entrée / sortie
- gestion de l’environnement
- builtins usuels (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- gestion des signaux selon l’implémentation

## Compilation

```bash
make
Lancement
./minishell
