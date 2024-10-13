## Nudge - Like a touch...but more!

### `nudge` is a touch and mkdir alternative for creating files. It allows you to create files and their enclosing directories all with one command.

-   #### Ex: `nudge ./src/routes/Login.tsx` -> This creates any and all non-existent enclosing directories, then creates `Login.tsx`
-   #### Ex: `nudge -s src/roures/Upload.tsx` -> The `-s` argument runs nudge in "safe" mode, meaning any non-existent enclosing directories will not be made, emulating the default behavior of `mkdir`. Helpful to not make misspelled directories.
-   #### Ex: `nudge -s /home/luke/Photos/Wallpapers/` -> Ending a command with `/` will create the ending file as a directory